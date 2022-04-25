#include "wga_structuregenerator_cpu.h"

#include <iostream>
#include <format>

#include "main.h"

#include "util/scopeexit.h"
#include "util/tracyutils.h"
#include "util/iterators.h"
#include "util/valueguard.h"

#include "worldgen/base/supp/wga_rule.h"
#include "worldgen/base/supp/wga_ruleexpansion.h"
#include "worldgen/base/supp/wga_component.h"
#include "worldgen/base/supp/wga_componentnode.h"

#include "worldgen_cpu_utils.h"
#include "worldgen/cpu/worldgenapi_cpu.h"
#include "wga_value_cpu.h"
#include "wga_valuewrapper_cpu.h"

WGA_StructureGenerator_CPU::WGA_StructureGenerator_CPU(WorldGenAPI_CPU &api) :
	api_(api) {

}

void WGA_StructureGenerator_CPU::setup(WGA_Rule *entryRule, const BlockWorldPos &origin, Seed seed) {
	ZoneScoped;
	bind();
	SCOPE_EXIT(unbind());

	areas_.clear();
	componentExpansions_ = {};
	ruleExpansions_ = {};
	stateStack_ = {};

	seed_ = WorldGen_CPU_Utils::hash(origin.to<uint32_t>(), seed);
	expansionCount_ = 0;
	queuedRuleExpansions_ = {};
	currentDataContext_ = {};

	expandRule(entryRule, origin, BlockOrientation(), nullptr);
}

bool WGA_StructureGenerator_CPU::process() {
	ZoneScoped;
	bind();
	SCOPE_EXIT(unbind());

	if(queuedRuleExpansions_.empty())
		return false;

	addBranch();
	ruleExpansions_.push_back(queuedRuleExpansions_.front());
	queuedRuleExpansions_.pop_front();

	while(true) {
		if(ruleExpansions_.empty()) {
			std::cerr << std::format("Failed to spawn structure: no solution found, tried all possible expansions. ({})", expansionCount_);
			return false;
		}

		expansionCount_++;
		if(expansionCount_ >= maxExpansionCount_) {
			std::cerr << std::format("Failed to spawn structure: maximum expansion count exceeded ({})", maxExpansionCount_);
			return false;
		}

		if(ruleExpansions_.size() > maxStackDepth_) {
			std::cerr << std::format("Failed to spawn structure: maximum stack depth exceeded ({})", maxStackDepth_);
			return false;
		}

		auto ex = ruleExpansions_.back();

		// We've trued all options for this expansion, and have failed
		if(!ex) {
			failBranch();
			continue;
		}

		const auto ps = ex->superState->expansionData->localToWorldMatrix() * BlockWorldPos();
		const std::string pss = std::format("({},{},{})", ps.x(), ps.y(), ps.z());

		{
			std::unique_lock _ml(dbgFileMutex);
			dbgFile << std::format("{} {}/{} {}/{} {} {}\n", ruleExpansions_.size(), ex->superState->expansionIndex, ex->superState->context->possibleExpansions.size(), ex->optionIndex, ex->superState->possibleOptions.size(), pss, ex->superState->expansionData->seed());
		}

		// Set the expansion to the next state/option before processing, so that the addBranch() already stores correct data
		ruleExpansions_.back() = nextRuleExpansionOption(ex->superState->context, ex.get());

		// Expansion failed -> try again the next option
		if(!processExpansion(*ex))
			continue;

		// Everything succeeded, no queued expansions -> success
		if(queuedRuleExpansions_.empty())
			return true;

		// Expansion succeded -> put another expansion to process
		ruleExpansions_.push_back(queuedRuleExpansions_.front());
		queuedRuleExpansions_.pop_front();

		/*TracyPlot("structureGenerator.stackSize", static_cast<float>(stateStack_.size()));
		TracyPlot("structureGenerator.componentExpansions", static_cast<float>(componentExpansions_.size()));
		TracyPlot("structureGenerator.ruleExpansions", static_cast<float>(ruleExpansions_.size()));
		TracyPlot("structureGenerator.expansionCount", static_cast<float>(expansionCount_));*/
	}
}

WGA_StructureOutputData_CPUPtr WGA_StructureGenerator_CPU::generateOutput() {
	ZoneScoped;
	bind();
	SCOPE_EXIT(unbind());

	WGA_StructureOutputData_CPUPtr result(new WGA_StructureOutputData_CPU());

	// Expand all components
	for(const ComponentExpansionStatePtr &cex: componentExpansions_) {
		currentDataContext_ = cex->data;
		SCOPE_EXIT(currentDataContext_ = {});
		DataContext &dcx = *currentDataContext_;

		for(const WGA_Component::Blocks &bar: cex->component->blockAreas()) {
			ZoneScopedN("processArea");

			auto blockv = WGA_ValueWrapper_CPU<WGA_Value::ValueType::Block>(bar.block);

			if(bar.startPos) {
				const BlockWorldPos worldPos1 = dcx.mapToWorld(blockPosValue(bar.startPos, dcx.constSamplePos()));
				const BlockWorldPos worldPos2 = bar.endPos ? cex->data->mapToWorld(blockPosValue(bar.endPos, dcx.constSamplePos())) : worldPos1;

				const BlockWorldPos worldStartPos = worldPos1.min(worldPos2);
				const BlockWorldPos worldEndPos = worldPos1.max(worldPos2);

				auto it = vectorIterator<BlockWorldPos>(worldStartPos & ~0xf, worldEndPos & ~0xf, 16);
				for(const BlockWorldPos &subChunkPos: it) {
					WGA_DataHandle_CPU<WGA_Value::ValueType::Block> blockh;

					blockh = blockv.dataHandle(subChunkPos);
					auto &srr = result->subChunkRecords[subChunkPos];

					const BlockWorldPos start = worldStartPos.max(subChunkPos) - subChunkPos;
					const BlockWorldPos end = worldEndPos.min(subChunkPos + 15) - subChunkPos;

					const auto volv = (end - start + 1);
					const BlockWorldPos_T volume = volv.x() * volv.y() * volv.z();

					// Flat data filling
					if(srr.shouldUseFlat(volume)) {
						auto resh = srr.flatData.data();

						for(const BlockWorldPos &pos: vectorIterator(start, end)) {
							const int i = pos.x() | (pos.y() << 4) | (pos.z() << 8);
							ASSERT(i < srr.flatData.size());

							const BlockID blockv = blockh[i];
							if(blockv != blockID_undefined)
								resh[i] = blockv;
						}
					}
						// Associative data filling
					else {
						for(const BlockWorldPos &pos: vectorIterator(start, end)) {
							const int i = pos.x() | (pos.y() << 4) | (pos.z() << 8);

							const BlockID blockv = blockh[i];
							if(blockv != blockID_undefined)
								srr.associativeData.emplace_back(i, blockv);
						}
					}
				}
			}

			if(!bar.positions.empty()) {
				BlockWorldPos offset;
				if(bar.positionsOffset)
					offset = blockPosValue(bar.startPos, dcx.constSamplePos());

				for(const BlockWorldPos &pos: bar.positions) {
					const BlockWorldPos worldPos = dcx.mapToWorld(pos + offset);

					const BlockID block = blockv.sampleAt(worldPos);
					if(block == blockID_undefined)
						continue;

					const BlockWorldPos subChunkPos = worldPos & ~(chunkSize - 1);

					auto &srr = result->subChunkRecords[subChunkPos];
					const ChunkBlockIndex six = worldPos.subChunkBlockIndex(0);

					if(srr.shouldUseFlat(1)) {
						ASSERT(six < srr.flatData.size());
						srr.flatData[six] = block;
					}
					else
						srr.associativeData.emplace_back(six, block);
				}
			}

			result->dataSize = iterator(result->subChunkRecords).mapx(sizeof(WGA_StructureOutputData_CPU::SubChunkRecord) + (x.second.flatData.empty() ? 0 : sizeof(BlockID) * chunkVolume) + x.second.associativeData.size() * 4).sum();
		}
	}

	return result;
}

WGA_DataRecord_CPU::Ptr WGA_StructureGenerator_CPU::getDataRecord(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor) {
	ASSERT(key.symbol->isContextual());
	ASSERT(currentDataContext_);

	return currentDataContext_->getDataRecord(key, ctor);
}

WGA_Value::Dimensionality WGA_StructureGenerator_CPU::getValueDimensionality(const WGA_Value *val) {
	ASSERT(val->isContextual());
	ASSERT(currentDataContext_);

	return currentDataContext_->getValueDimensionality(val);
}

WGA_Value::Dimensionality WGA_StructureGenerator_CPU::getInputParamDimensionality(WGA_Symbol *symbol) {
	ASSERT(symbol->isContextual());
	ASSERT(currentDataContext_);

	return currentDataContext_->getInputParamDimensionality(symbol);
}

void WGA_StructureGenerator_CPU::bind() {
	ASSERT(!api_.structureGen);
	api_.structureGen = this;
}

void WGA_StructureGenerator_CPU::unbind() {
	ASSERT(api_.structureGen == this);
	api_.structureGen = nullptr;
}

bool WGA_StructureGenerator_CPU::expandRule(WGA_Rule *rule, const BlockWorldPos &localOrigin, const BlockOrientation &orientation, const DataContextPtr &data) {
	// ZoneScoped;

	RuleExpansionContextPtr rex(new RuleExpansionContext{
		.rule = rule,
		.orientation = orientation,
		.ruleData = DataContext::create(&api_, data, rule, BlockTransformMatrix::translation(localOrigin)),
	});
	currentDataContext_ = rex->ruleData;
	SCOPE_EXIT(currentDataContext_ = {});

	// Check rule conditions
	if(!checkConditions(rule))
		return false;

	Seed seed = WorldGen_CPU_Utils::hash(13713, rex->ruleData->seed());

	// Create list of all possible rule -> expansion
	// Go from the lowest priority to the highest, randomly reorder expansions for the same priority based on their probability ratio
	const WGA_Rule::CompiledExpansionList &cel = rule->compiledExpansionList();
	for(const auto &ci: cel.subLists) {
		std::vector<WGA_Rule::CompiledExpansion> unprocessedExpansions = ci.second.expansions;

		if(unprocessedExpansions.empty())
			std::cerr << "Rule has no possible expansions";

		// Randomly order the same priority expansions, follow probability Ratios
		float unprocessedProbabilityRatioSum = ci.second.probabilityRatioSum;

		while(!unprocessedExpansions.empty()) {
			seed = WorldGen_CPU_Utils::hash(seed);
			const float randomPos = (static_cast<float>(seed & 0xffff) / 0xffff) * unprocessedProbabilityRatioSum;

			float sum = 0;
			for(auto i = unprocessedExpansions.begin(), end = unprocessedExpansions.end(); i != end; i++) {
				const WGA_Rule::CompiledExpansion &cex = *i;

				sum += cex.probabilityRatio;
				if(randomPos <= sum) {
					unprocessedProbabilityRatioSum -= cex.probabilityRatio;
					rex->possibleExpansions.push_back(cex);
					unprocessedExpansions.erase(i);
					sum = -1;

					{
						std::unique_lock _ml(dbgFileMutex);
						const auto pos = currentDataContext_->constSamplePos();
						dbgFile << std::format("possibleExpansion {} -> {}\n", cex.expansion->description(), cex.expansion->component() ? cex.expansion->component()->description() : cex.expansion->targetRule() ? cex.expansion->targetRule()->description() : "void");
					}
					break;
				}
			}

			// Check that we hit break
			ASSERT(sum == -1);
		}
	}

	// No possible expansions -> fail
	if(rex->possibleExpansions.empty())
		return false;

	ASSERT(currentDataContext_ == rex->ruleData);

	// Process param sets
	rex->ruleData->setParams();

	RuleExpansionStatePtr res = nextRuleExpansionOption(rex, nullptr);
	ASSERT(res);

	// Add the rule to the expansion list
	bool doDepthFirst = false;
	if(!ruleExpansions_.empty() && !stateStack_.empty()) {
		const float prob = std::get<float>(rule->pragma("depthFirstProbability"));
		doDepthFirst = float(WorldGen_CPU_Utils::hash(136841, rex->ruleData->seed()) % 1000) < float(prob * 1000);
	}

	// Insert the rule expansion after currently expanded rule, but it must still be after the last state rules list end so that if we potentially fail the branch and revert to the state, the rule expansion list doesn't get screwed up
	if(doDepthFirst)
		queuedRuleExpansions_.push_front(res);
	else
		queuedRuleExpansions_.push_back(res);

	return true;
}

bool WGA_StructureGenerator_CPU::processExpansion(WGA_StructureGenerator_CPU::RuleExpansionState &res) {
	RuleExpansionSuperState &ss = *res.superState;
	RuleExpansionContext &ctx = *ss.context;

	const WGA_Rule::CompiledExpansion &crex = ctx.possibleExpansions[ss.expansionIndex];
	WGA_RuleExpansion *rex = crex.expansion;

	using TT = WGA_RuleExpansion::TargetType;
	TT tt = rex->targetType();

	// Expands to nothing -> instant success
	if(tt == TT::expandsToVoid)
		return true;

		// Expands to rule -> we just expand it
	else if(tt == TT::expandsToRule) {
		addBranch();

		if(!expandRule(rex->targetRule(), BlockWorldPos(), ctx.orientation, ss.expansionData)) {
			failBranch();
			return false;
		}

		return true;
	}

		// Expands to component -> we generate a list of possible component nodes it can join to and then iterate them
	else if(rex->targetType() == TT::expandsToComponent) {
		WGA_Component *comp = rex->component();
		const auto &opt = ss.possibleOptions[res.optionIndex];
		WGA_ComponentNode *node = opt.node;

		ComponentExpansionStatePtr cex(new ComponentExpansionState{
			.component = comp,
			.entryNode = node,
			.data = DataContext::create(&api_, ss.expansionData, comp),
		});
		currentDataContext_ = cex->data;
		SCOPE_EXIT(currentDataContext_ = {});
		auto &dcx = *currentDataContext_;

		// Calculate component transform matrix
		{
			int transformFlags = 0;
			if(std::get<bool>(node->pragma("horizontalEdge")))
				transformFlags |= +BlockOrientation::TransformFlags::horizontalEdge;

			if(std::get<bool>(node->pragma("verticalEdge")))
				transformFlags |= +BlockOrientation::TransformFlags::verticalEdge;

			if(std::get<bool>(node->pragma("adjacent")))
				transformFlags |= +BlockOrientation::TransformFlags::adjacent;

			if(crex.mirror)
				transformFlags |= +BlockOrientation::TransformFlags::mirror;

			dcx.localToWorldMatrix() *= opt.orientation.transformToMatch(ctx.orientation.adjacent(), transformFlags);
			dcx.localToWorldMatrix() *= BlockTransformMatrix::translation(-blockPosValue(node->config().position, ss.expansionData->constSamplePos()));

			// We've changed the transaltion matrix, so we shall update the seed
			dcx.updateMatrix();
		}

		// Check component conditions
		if(!checkConditions(comp))
			return false;

		// Create branch - now we can start changing the structure generator state
		addBranch();
		componentExpansions_.push_back(cex);

		// Generate and check areas
		for(const WGA_Component::Area &arc: comp->areas()) {
			int &nameID = areaNameMapping_[arc.name];
			if(!nameID)
				nameID = areaNameMapping_.size();

			const BlockWorldPos pos1 = dcx.mapToWorld(blockPosValue(arc.startPos, dcx.constSamplePos()));
			const BlockWorldPos pos2 = dcx.mapToWorld(blockPosValue(arc.endPos, dcx.constSamplePos()));

			Area area{
				.nameID = nameID,
				.startPos = pos1.min(pos2),
				.endPos = pos1.max(pos2),
			};

			// Check if the area is not overlapping other areas with the same name
			if(!arc.canOverlap || arc.mustOverlap) {
				const bool overlaps =
					iterator(areas_)
						.filterx(area.nameID == x.nameID)
						.mapx((x.endPos >= area.startPos).all() && (x.startPos <= area.endPos).all())
						.any();

				if(overlaps != arc.mustOverlap) {
					failBranch();
					return false;
				}
			}

			// Overlap areas are just for checking
			if(!arc.isVirtual)
				areas_.push_back(area);
		}

		// Process param sets
		dcx.setParams();

		auto nodes = comp->nodes();

		// Randomize the order of the nodes using Fisher-Yates shuffle
		if(0) {
			const size_t sz = nodes.size();
			const Seed seed = WorldGen_CPU_Utils::hash(dcx.seed() ^ 1531, seed_);
			for(int i = 0; i < sz; i++) {
				const int j = i + (WorldGen_CPU_Utils::hash(i, seed) % (sz - i));
				std::swap(nodes[i], nodes[j]);
			}
		}

		// Expand the component node rules
		for(const WGA_ComponentNode *node: nodes) {
			if(!node->config().rule || node == cex->entryNode)
				continue;

			// expandRule modifies the currentDataContext_, so we have to reset it
			currentDataContext_ = cex->data;

			// If the expansion fails, expandRule calls failBranch, so we just return
			if(!expandRule(node->config().rule, blockPosValue(node->config().position, dcx.constSamplePos()), node->config().orientation, cex->data)) {
				failBranch();
				return false;
			}
		}

		return true;
	}
	else
		throw;
}

WGA_StructureGenerator_CPU::RuleExpansionStatePtr WGA_StructureGenerator_CPU::nextRuleExpansionOption(const RuleExpansionContextPtr &ctx, const RuleExpansionState *previousState) {
	size_t expansionIndex = 0;
	size_t optionIndex = 0;
	RuleExpansionSuperStatePtr superState;

	if(previousState) {
		superState = previousState->superState;
		expansionIndex = superState->expansionIndex;
		optionIndex = previousState->optionIndex + 1;

		ASSERT(superState->context == ctx);
	}

	while(true) {
		// No possible expansion -> quitty
		if(expansionIndex >= ctx->possibleExpansions.size())
			return {};

		if(superState && optionIndex >= superState->possibleOptions.size()) {
			superState = {};
			expansionIndex++;
			optionIndex = 0;

			continue;
		}

		const WGA_Rule::CompiledExpansion &cex = ctx->possibleExpansions[expansionIndex];
		WGA_RuleExpansion *rex = cex.expansion;

		ASSERT(!optionIndex == !superState);

		using TT = WGA_RuleExpansion::TargetType;
		const TT tt = rex->targetType();

		if(!superState) {
			superState = RuleExpansionSuperStatePtr(new RuleExpansionSuperState{
				.context = ctx,
				.expansionIndex = expansionIndex,
				.expansionData = DataContext::create(&api_, ctx->ruleData, rex),
			});
			currentDataContext_ = superState->expansionData;
			SCOPE_EXIT(currentDataContext_ = {});
			DataContext &dcx = *superState->expansionData;

			// Check conditions
			if(!checkConditions(rex))
				continue;

			// Prepare output params
			dcx.setParams();

			// Generate node variants if the rule expands to a component
			if(tt == TT::expandsToComponent) {
				auto &opts = superState->possibleOptions;

				WGA_Component *comp = rex->component();
				const auto nodeList = comp->nodes(rex->node());

				if(nodeList.empty()) {
					std::cerr << std::format("There are no '{}' nodes in the '{}' component.\n", rex->node(), comp->description());
					continue;
				}

				for(WGA_ComponentNode *targetNode: nodeList) {
					BlockOrientation ori = targetNode->config().orientation;

					if(ori.isSpecified() && std::get<bool>(targetNode->pragma("allowRotation"))) {
						for(int i = 0; i < 4; i++, ori = ori.nextUpVariant())
							opts.push_back({targetNode, ori});
					}
					else
						opts.push_back({targetNode, ori});
				}

				// Randomize the order of the nodes using Fisher-Yates shuffle
				if(0) {
					const size_t sz = opts.size();
					const Seed seed = WorldGen_CPU_Utils::hash(16512, dcx.seed());
					for(size_t i = 0; i < sz; i++) {
						const size_t j = i + (WorldGen_CPU_Utils::hash(i, seed) % (sz - i));
						std::swap(opts[i], opts[j]);
					}
				}
			}
			else
				// Push one dummy option to trigger the expansion processing
				superState->possibleOptions.push_back(RuleExpansionSuperState::Option{});
		}

		return RuleExpansionStatePtr(new RuleExpansionState{
			.superState = superState,
			.optionIndex = optionIndex,
		});
	}
}

void WGA_StructureGenerator_CPU::addBranch() {
	// ZoneScoped;

	stateStack_.push(State{
		.areaCount = areas_.size(),
		.componentExpansionCount = componentExpansions_.size(),
		.ruleExpansionCount = ruleExpansions_.size(),
		.queuedRuleExpansions = queuedRuleExpansions_,
	});
}

void WGA_StructureGenerator_CPU::failBranch() {
	// ZoneScoped;

	ASSERT(!stateStack_.empty());

	const State s = stateStack_.top();
	stateStack_.pop();

	// Remove areas and component expansions added after the addBranch() was called
	ASSERT(s.areaCount <= areas_.size());
	areas_.resize(s.areaCount);

	ASSERT(s.componentExpansionCount <= componentExpansions_.size());
	componentExpansions_.resize(s.componentExpansionCount);

	ASSERT(s.ruleExpansionCount <= ruleExpansions_.size());
	ruleExpansions_.resize(s.ruleExpansionCount);

	queuedRuleExpansions_ = s.queuedRuleExpansions;
}

bool WGA_StructureGenerator_CPU::checkConditions(WGA_GrammarSymbol *sym) {
	// ZoneScoped;

	{
		std::unique_lock _ml(dbgFileMutex);
		const auto pos = currentDataContext_->constSamplePos();
		dbgFile << std::format("checkCondition pos={} start cnt={} ctx={}\n", pos.to<BlockWorldPos_T>(), sym->conditions().size(), currentDataContext_->seed());
	}

	const bool result = iterator(sym->conditions()).mapx(boolValue(x.value, currentDataContext_->constSamplePos())).all();

	{
		std::unique_lock _ml(dbgFileMutex);
		const auto pos = currentDataContext_->constSamplePos();
		dbgFile << std::format("checkCondition {} pos={} {} {}\n", result, pos.to<BlockWorldPos_T>(), currentDataContext_->seed(), sym->description());
	}

	return result;
}

BlockWorldPos WGA_StructureGenerator_CPU::blockPosValue(WGA_Value *val, const BlockWorldPos &samplePoint) {
	return WGA_ValueWrapper_CPU<WGA_Value::ValueType::Float3>(val).sampleAt(samplePoint).to<BlockWorldPos_T>();
}

bool WGA_StructureGenerator_CPU::boolValue(WGA_Value *val, const BlockWorldPos &samplePoint) {
	return WGA_ValueWrapper_CPU<WGA_Value::ValueType::Bool>(val).sampleAt(samplePoint);
}

BlockID WGA_StructureGenerator_CPU::blockValue(WGA_Value *val, const BlockWorldPos &samplePoint) {
	return WGA_ValueWrapper_CPU<WGA_Value::ValueType::Block>(val).sampleAt(samplePoint);
}

WGA_StructureGenerator_CPU::DataContext::~DataContext() {
	for(const auto e: temporarySymbols_)
		delete e;
}

WGA_StructureGenerator_CPU::DataContextPtr WGA_StructureGenerator_CPU::DataContext::create(WorldGenAPI_CPU *api, const WGA_StructureGenerator_CPU::DataContextPtr &parentContext, WGA_GrammarSymbol *sym, const BlockTransformMatrix &transform) {
	DataContextPtr r(new DataContext());
	r->load(api, parentContext, sym, transform);
	static size_t ix = 0;
	r->ix = ix++;
	return r;
}

void WGA_StructureGenerator_CPU::DataContext::load(WorldGenAPI_CPU *api, const DataContextPtr &parentContext, WGA_GrammarSymbol *sym, const BlockTransformMatrix &transform) {
	// ZoneScoped;

	ASSERT(!sym_);
	sym_ = sym;
	parentContext_ = parentContext;
	api_ = api;

	if(parentContext)
		localToWorldMatrix_ = parentContext->localToWorldMatrix_ * transform;
	else
		localToWorldMatrix_ = transform;

	updateMatrix();

	for(const WGA_GrammarSymbol::ParamDeclare &pd: sym->paramDeclares()) {
		const std::string key = paramKey(pd.paramName, pd.type);
		paramInputs_[key] = pd.defaultValue;
		paramKeyMapping_[pd.value] = key;
	}

	if(parentContext) {
		for(auto it = parentContext->paramOutputs_.begin(), end = parentContext->paramOutputs_.end(); it != end; it++) {
			WGA_Value_CPU *sourceVal = static_cast<WGA_Value_CPU *>(it->second);

			const auto dimFunc = [sourceVal, this] {
				auto &cdc = WorldGenAPI_CPU::structureGen->currentDataContext_;
				ASSERT(cdc.get() == this);

				ValueGuard _vg(cdc, parentContext_);
				return parentContext_->getValueDimensionality(sourceVal);
			};
			const auto ctorFunc = [sourceVal, this](const WGA_DataRecord_CPU::Key &key) {
				auto &cdc = WorldGenAPI_CPU::structureGen->currentDataContext_;
				ASSERT(cdc.get() == this);

				ValueGuard _vg(cdc, parentContext_);

				{
					std::unique_lock _ml(dbgFileMutex);
					dbgFile << std::format("parent six={}\n", cdc->ix);
				}
				return parentContext_->getDataRecord(key, sourceVal->ctor());
			};

			WGA_Value_CPU *localVal = new WGA_Value_CPU(sourceVal->api(), sourceVal->valueType(), true, dimFunc, ctorFunc);
			temporarySymbols_.push_back(localVal);
			paramInputs_[it->first] = localVal;

			{
				std::unique_lock _ml(dbgFileMutex);
				dbgFile << std::format("temps cix={} kix={}\n", ix, localVal->ix);
			}
		}
	}

	for(const WGA_GrammarSymbol::ParamDeclare &pd: sym->paramDeclares()) {
		const std::string key = paramKey(pd.paramName, pd.type);
		if(!paramInputs_[key])
			throw std::exception(std::format("Param value not defined for param {}", pd.paramName).c_str());
	}

	paramOutputs_ = paramInputs_;
}

void WGA_StructureGenerator_CPU::DataContext::setParams() {
	for(const WGA_GrammarSymbol::ParamSet &ps: sym_->paramSets()) {
		paramOutputs_[paramKey(ps.paramName, ps.value->valueType())] = ps.value;
		dbgFile << std::format("cspos={} seed={} param={} val0={}\n", constSamplePos_.to<BlockWorldPos_T>(), seed_, paramKey(ps.paramName, ps.value->valueType()), static_cast<WGA_Value_CPU *>(ps.value)->getDataRecord({}, 0)->debugInfo());
	}
}

void WGA_StructureGenerator_CPU::DataContext::updateMatrix() {
	constSamplePos_ = localToWorldMatrix_ * BlockWorldPos();
	seed_ = WorldGen_CPU_Utils::hash(constSamplePos_.to<uint32_t>(), parentContext_ ? parentContext_->seed_ : api_->structureGen->seed_);
}

WGA_DataRecord_CPU::Ptr WGA_StructureGenerator_CPU::DataContext::getDataRecord(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor) {
	{
		std::unique_lock _ml(dbgFileMutex);
		dbgFile << std::format("cache cix={} sz={}\n{}\n", ix, dataCache_.size(), iterator(dataCache_).mapx(std::format("kix={} pos={}", x.first.symbol->ix, x.first.origin.to<BlockWorldPos_T>())).join(" | "));
	}

	WGA_DataRecord_CPU::Ptr result = dataCache_[key];

	const auto ff = [&] {
		return std::format("{} kix={} cix={} cspos={} seed={} {}", key.symbol->description(), key.symbol->ix, ix, constSamplePos_.to<BlockWorldPos_T>(), seed_, result->debugInfo());
	};

	if(result) {
		{
			std::unique_lock _ml(dbgFileMutex);
			dbgFile << ff() << std::format("cached\n");
		}

		return result;
	}

	// Check if the symbol is param declare value, map it to actual param value
	bool isParam = true;
	if(const auto f = paramKeyMapping_.find(key.symbol); f != paramKeyMapping_.end())
		result = static_cast<WGA_Value_CPU *>(paramInputs_[f->second])->getDataRecord(key.origin, key.subKey);
	else {
		result = ctor(key);
		isParam = false;
	}

	dataCache_[key] = result;

	{
		std::unique_lock _ml(dbgFileMutex);
		dbgFile << ff() << std::format("isParam={}\n", isParam);
	}


	return result;
}

WGA_Value::Dimensionality WGA_StructureGenerator_CPU::DataContext::getValueDimensionality(const WGA_Value *val) {
	WGA_Value::Dimensionality &result = dimensionalityCache_[val];
	if(result == WGA_Value::Dimensionality::Unknown)
		result = static_cast<const WGA_Value_CPU *>(val)->dimFunc()();

	return result;
}

WGA_Value::Dimensionality WGA_StructureGenerator_CPU::DataContext::getInputParamDimensionality(WGA_Symbol *symbol) {
	WGA_Value::Dimensionality &result = inputParamDimensionalityCache_[symbol];
	if(result == WGA_Value::Dimensionality::Unknown) {
		ASSERT(paramKeyMapping_.contains(symbol));
		result = paramInputs_[paramKeyMapping_.at(symbol)]->dimensionality();
	}

	return result;
}

std::string WGA_StructureGenerator_CPU::DataContext::paramKey(const std::string &paramName, WGA_Value::ValueType type) {
	return std::format("{}#{}", paramName, WGA_Value::typeNames.at(type));
}
