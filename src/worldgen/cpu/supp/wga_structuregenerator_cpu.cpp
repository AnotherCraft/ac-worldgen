#include "wga_structuregenerator_cpu.h"

#include <iostream>
#include <format>

#include "util/scopeexit.h"
#include "util/tracyutils.h"
#include "util/iterators.h"

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
	currentDataContext_ = nullptr;

	currentlyExpandedRuleIx_ = ruleExpansions_.begin();

	addBranch();
	expandRule(entryRule, origin, BlockOrientation(), nullptr);

	currentlyExpandedRuleIx_ = ruleExpansions_.begin();
}

bool WGA_StructureGenerator_CPU::process() {
	ZoneScoped;
	bind();
	SCOPE_EXIT(unbind());

	while(currentlyExpandedRuleIx_ != ruleExpansions_.end()) {
		expansionCount_++;
		if(expansionCount_ >= maxExpansionCount_) {
			std::cerr << "Failed to spawn structure: maximum expansion count exceeded (" << maxExpansionCount_ << ")";
			return false;
		}

		if(stateStack_.size() > maxStackDepth_) {
			std::cerr << "Failed to spawn structure: maximum stack depth exceeded (" << maxStackDepth_ << ")";
			return false;
		}

		if(processExpansion(**currentlyExpandedRuleIx_))
			currentlyExpandedRuleIx_++;

		/*TracyPlot("structureGenerator.stackSize", static_cast<float>(stateStack_.size()));
		TracyPlot("structureGenerator.componentExpansions", static_cast<float>(componentExpansions_.size()));
		TracyPlot("structureGenerator.ruleExpansions", static_cast<float>(ruleExpansions_.size()));
		TracyPlot("structureGenerator.expansionCount", static_cast<float>(expansionCount_));*/
	}

	if(ruleExpansions_.empty()) {
		std::cerr << "Failed to spawn structure: no solution found, tried all possible expansions. (" << expansionCount_ << ")";
		return false;
	}

	return true;
}

WGA_StructureOutputData_CPUPtr WGA_StructureGenerator_CPU::generateOutput() {
	ZoneScoped;
	bind();
	SCOPE_EXIT(unbind());

	WGA_StructureOutputData_CPUPtr result(new WGA_StructureOutputData_CPU());

	// Expand all components
	for(const ComponentExpansionStatePtr &cex: componentExpansions_) {
		currentDataContext_ = &cex->data;

		for(const WGA_Component::Blocks &bar: cex->component->blockAreas()) {
			ZoneScopedN("processArea");

			auto blockv = WGA_ValueWrapper_CPU<WGA_Value::ValueType::Block>(bar.block);

			if(bar.startPos) {
				const BlockWorldPos worldPos1 = cex->data.mapToWorld(blockPosValue(bar.startPos, cex->data.constSamplePos()));
				const BlockWorldPos worldPos2 = bar.endPos ? cex->data.mapToWorld(blockPosValue(bar.endPos, cex->data.constSamplePos())) : worldPos1;

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
								srr.associativeData.push_back({i, blockv});
						}
					}
				}
			}

			if(!bar.positions.empty()) {
				BlockWorldPos offset;
				if(bar.positionsOffset)
					offset = blockPosValue(bar.startPos, cex->data.constSamplePos());

				for(const BlockWorldPos &pos: bar.positions) {
					const BlockWorldPos worldPos = cex->data.mapToWorld(pos + offset);

					const BlockID block = blockv.sampleAt(worldPos);
					if(block == blockID_undefined)
						continue;

					const BlockWorldPos subChunkPos = worldPos & ~(chunkSize - 1);

					auto &srr = result->subChunkRecords[subChunkPos];
					const ChunkBlockIndex six = worldPos.subChunkBlockIndex(0);

					if(srr.shouldUseFlat(1))
						srr.flatData[six] = block;
					else
						srr.associativeData.push_back({six, block});
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

bool WGA_StructureGenerator_CPU::expandRule(WGA_Rule *rule, const BlockWorldPos &localOrigin, const BlockOrientation &orientation, WGA_StructureGenerator_CPU::DataContext *data) {
	// ZoneScoped;

	RuleExpansionStatePtr res(new RuleExpansionState());
	currentDataContext_ = &res->ruleData;

	res->ruleData.load(&api_, data, rule);
	res->ruleData.localToWorldMatrix() *= BlockTransformMatrix::translation(localOrigin);

	res->orientation = orientation;
	res->rule = rule;

	bool doDepthFirst = false;
	if(!ruleExpansions_.empty()) {
		const float prob = std::get<float>(rule->pragma("depthFirstProbability"));
		doDepthFirst = WorldGen_CPU_Utils::hash(136841, res->ruleData.seed()) % 1000 < prob * 1000;
	}

	if(doDepthFirst) {
		auto it = currentlyExpandedRuleIx_;
		it++;
		ruleExpansions_.insert(it, res);
	}
	else
		ruleExpansions_.push_back(res);

	// Check rule conditions
	if(!checkConditions(rule)) {
		//qDebug() << "Rule conditions failed";
		failBranch();
		return false;
	}

	Seed seed = WorldGen_CPU_Utils::hash((res->ruleData.localToWorldMatrix() * BlockWorldPos()).to<uint32_t>(), seed_ ^ 0xA9);

	// Create possible expansion list
	// Go from the lowest priority to the highest, add expansions
	const WGA_Rule::CompiledExpansionList &cel = rule->compiledExpansionList();
	for(const auto &ci: cel.subLists) {
		std::vector<const WGA_Rule::CompiledExpansion *> unprocessedExpansions;
		//QVector<WGA_Rule::CompiledExpansion const*> unprocessedExpansions;

		for(const WGA_Rule::CompiledExpansion &cex: ci.second.expansions)
			unprocessedExpansions.push_back(&cex);

		if(unprocessedExpansions.empty())
			std::cerr << "Rule has no possible expansions";

		// Randomly order the same priority expansions, follow probability Ratios
		float unprocessedProbabilityRatioSum = ci.second.probabilityRatioSum;

		while(!unprocessedExpansions.empty()) {
			seed = WorldGen_CPU_Utils::hash(seed);
			const float randomPos = (static_cast<float>(seed & 0xffff) / 0xffff) * unprocessedProbabilityRatioSum;

			float sum = 0;
			for(auto i = unprocessedExpansions.begin(), end = unprocessedExpansions.end(); i != end; i++) {
				const WGA_Rule::CompiledExpansion *cex = *i;

				sum += cex->probabilityRatio;
				if(randomPos <= sum) {
					unprocessedProbabilityRatioSum -= cex->probabilityRatio;
					res->possibleExpansions.push_back(*cex);
					unprocessedExpansions.erase(i);
					sum = -1;
					break;
				}
			}

			// Check that we hit break
			ASSERT(sum == -1);
		}
	}

	// Process param sets
	res->ruleData.setParams();

	return true;
}

bool WGA_StructureGenerator_CPU::processExpansion(WGA_StructureGenerator_CPU::RuleExpansionState &res) {
	// ZoneScoped;

	// Load next possible expansion if needed
	if(res.currentExpansionNodeIndex == -1 || res.currentExpansionNodeIndex >= res.possibleExpansionNodes.size()) {
		res.currentExpansionIndex++;

		// If we've run out of possible expansions, fail the branch
		if(res.currentExpansionIndex >= res.possibleExpansions.size()) {
			//qDebug() << QStringLiteral("Exhausted possible expansions (%1 attempts)").arg(expansionCount_);
			failBranch();
			return false;
		}

		WGA_Rule::CompiledExpansion crex = res.possibleExpansions[res.currentExpansionIndex];
		WGA_RuleExpansion *rex = crex.expansion;
		currentDataContext_ = &res.currentExpansionData;

		// Setup for the new rule
		res.possibleExpansionNodes.clear();
		res.currentExpansionNodeIndex = 0;

		res.currentExpansionData = DataContext();
		res.currentExpansionData.load(&api_, &res.ruleData, rex);

		// Check expansion conditions
		// Expansion condition failed -> we have to try different expansion in the next processExpansion call (possibleEpxansionNodes is empty so it should jump into it)
		if(!checkConditions(rex))
			return false;

		using TT = WGA_RuleExpansion::TargetType;

		// Expands to nothing -> instant success
		if(rex->targetType() == TT::expandsToVoid)
			return true;

			// Expands to rule -> we just expand it
		else if(rex->targetType() == TT::expandsToRule) {
			return expandRule(rex->targetRule(), BlockWorldPos(), res.orientation, &res.currentExpansionData);
		}

			// Expands to component -> we generate a list of possible component nodes it can join to and then iterate them
		else if(rex->targetType() == TT::expandsToComponent) {
			WGA_Component *comp = rex->component();

			const auto nodeList = comp->nodes(rex->node());
			if(nodeList.empty())
				std::cerr << std::format("There are no '{}' nodes in the '{}' component.\n", rex->node(), comp->description());

			for(WGA_ComponentNode *targetNode: nodeList) {
				BlockOrientation ori = targetNode->config().orientation;

				if(ori.isSpecified() && std::get<bool>(targetNode->pragma("allowRotation"))) {
					for(int i = 0; i < 4; i++) {
						res.possibleExpansionNodes.push_back({targetNode, ori});
						ori = ori.nextUpVariant();
					}
				}
				else
					res.possibleExpansionNodes.push_back({targetNode, ori});
			}

			// Randomize the order of the nodes using Fisher-Yates shuffle
			{
				const size_t sz = res.possibleExpansionNodes.size();
				const Seed seed = WorldGen_CPU_Utils::hash((res.ruleData.localToWorldMatrix() * BlockWorldPos()).to<uint32_t>(), seed_ ^ 0x12);
				for(size_t i = 0; i < sz; i++) {
					const size_t j = i + (WorldGen_CPU_Utils::hash(i, seed) % (sz - i));
					std::swap(res.possibleExpansionNodes[i], res.possibleExpansionNodes[j]);
				}
			}

			/*if(res.possibleExpansionNodes.isEmpty())
				qDebug() << "Component has no nodes named " << rex->node();*/

			// Process param sets
			res.currentExpansionData.setParams();

			// Return to check if the expansion has enough target nodes, or go to another expansion if it doesn't
			return false;
		}
		else
			throw;
	}

	WGA_Rule::CompiledExpansion crex = res.possibleExpansions[res.currentExpansionIndex];
	WGA_RuleExpansion *rex = crex.expansion;

	ASSERT(rex->targetType() == WGA_RuleExpansion::TargetType::expandsToComponent);

	const RuleExpansionNode &n = res.possibleExpansionNodes[res.currentExpansionNodeIndex];
	WGA_ComponentNode *node = n.node;

	res.currentExpansionNodeIndex++;
	addBranch();

	WGA_Component *comp = rex->component();
	ComponentExpansionStatePtr cex(new ComponentExpansionState{
		.component = comp,
		.entryNode = node,
	});
	currentDataContext_ = &cex->data;

	cex->data.load(&api_, &res.currentExpansionData, comp);

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

		cex->data.localToWorldMatrix() *= n.orientation.transformToMatch(res.orientation.adjacent(), transformFlags);
		cex->data.localToWorldMatrix() *= BlockTransformMatrix::translation(-blockPosValue(node->config().position, res.currentExpansionData.constSamplePos()));

		cex->placementHash = HashUtils::multiHash(cex->data.localToWorldMatrix(), comp);
	}

	// Check if there already isn't the same component with the same position (so we can create a loop)
	// This is basically useless, dropping
	/*for(const ComponentExpansionStatePtr &ocex: componentExpansions_) {
		// If there already is the same component with the same position, return true
		// This means that this expansion branch joined with a previously build structure
		if(ocex->placementHash == cex->placementHash && ocex->component == cex->component && ocex->data.localToWorldMatrix() == cex->data.localToWorldMatrix()) {
			return true;
		}
	}*/

	componentExpansions_.push_back(cex);

	// Generate and check areas
	for(const WGA_Component::Area &arc: comp->areas()) {
		int &nameID = areaNameMapping_[arc.name];
		if(!nameID)
			nameID = areaNameMapping_.size();

		const BlockWorldPos pos1 = cex->data.mapToWorld(blockPosValue(arc.startPos, cex->data.constSamplePos()));
		const BlockWorldPos pos2 = cex->data.mapToWorld(blockPosValue(arc.endPos, cex->data.constSamplePos()));

		Area area{
			.nameID = nameID,
			.startPos = pos1.min(pos2),
			.endPos = pos1.max(pos2),
		};

		// Check if the area is not overlapping other areas with the same name
		if(!arc.canOverlap || arc.mustOverlap) {
			bool overlaps = false;

			for(const Area &testArea: areas_) {
				if(testArea.nameID != area.nameID)
					continue;

				// Areas with the same name cannot intersect
				if((testArea.endPos >= area.startPos).all() && (testArea.startPos <= area.endPos).all()) {
					overlaps = true;
					break;
				}
			}

			if(overlaps != arc.mustOverlap) {
				failBranch();
				return false;
			}
		}

		// Overlap areas are just for checking
		if(!arc.isVirtual)
			areas_.push_back(area);
	}

	// Check component conditions
	if(!checkConditions(comp)) {
		//qDebug() << "Component conditions failed";
		failBranch();
		return false;
	}

	// Process param sets
	cex->data.setParams();

	auto nodes = comp->nodes();

	// Randomize the order of the nodes using Fisher-Yates shuffle
	{
		const size_t sz = nodes.size();
		const Seed seed = WorldGen_CPU_Utils::hash(cex->data.seed() ^ 1531, seed_);
		for(int i = 0; i < sz; i++) {
			const int j = i + (WorldGen_CPU_Utils::hash(i, seed) % (sz - i));
			std::swap(nodes[i], nodes[j]);
		}
	}

	// Expand the component node rules
	for(const WGA_ComponentNode *node: nodes) {
		if(!node->config().rule || node == cex->entryNode)
			continue;

		// If the expansion fails, expandRule calls failBranch, so we just return
		if(!expandRule(node->config().rule, blockPosValue(node->config().position, cex->data.constSamplePos()), node->config().orientation, &cex->data))
			return false;

		// expandRule changes the current data context, so we gotta change it back
		currentDataContext_ = &cex->data;
	}

	return true;
}

void WGA_StructureGenerator_CPU::addBranch() {
	// ZoneScoped;

	stateStack_.push(State{
		.areaCount = areas_.size(),
		.componentExpansionCount = componentExpansions_.size(),
		.ruleExpansionCount = ruleExpansions_.size(),
		.currentlyExpandedRuleIx = currentlyExpandedRuleIx_,
	});
}

void WGA_StructureGenerator_CPU::failBranch() {
	// ZoneScoped;

	ASSERT(!stateStack_.empty());

	const State s = stateStack_.top();
	stateStack_.pop();

	areas_.resize(s.areaCount);
	ruleExpansions_.resize(s.ruleExpansionCount);
	componentExpansions_.resize(s.componentExpansionCount);
	currentlyExpandedRuleIx_ = s.currentlyExpandedRuleIx;
}

bool WGA_StructureGenerator_CPU::checkConditions(WGA_GrammarSymbol *sym) {
	// ZoneScoped;

	for(const WGA_GrammarSymbol::Condition &cond: sym->conditions()) {
		if(!boolValue(cond.value, currentDataContext_->constSamplePos()))
			return false;
	}

	return true;
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

void WGA_StructureGenerator_CPU::DataContext::load(WorldGenAPI_CPU *api, DataContext *parentContext, WGA_GrammarSymbol *sym) {
	// ZoneScoped;

	ASSERT(!sym_);
	sym_ = sym;
	parentContext_ = parentContext;
	api_ = api;

	if(parentContext) {
		localToWorldMatrix_ = parentContext->localToWorldMatrix_;
		seed_ = HashUtils::multiHash(parentContext_->seed_, parentContext_->localToWorldMatrix_ * BlockWorldPos());
	}
	else {
		localToWorldMatrix_ = BlockTransformMatrix();
		seed_ = api->structureGen->seed_;
	}

	for(const WGA_GrammarSymbol::ParamDeclare &pd: sym->paramDeclares()) {
		const std::string key = paramKey(pd.paramName, pd.type);
		paramInputs_[key] = pd.defaultValue;
		paramKeyMapping_[pd.value] = key;
	}

	if(parentContext) {
		for(auto it = parentContext->paramOutputs_.begin(), end = parentContext->paramOutputs_.end(); it != end; it++) {
			WGA_Value_CPU *sourceVal = static_cast<WGA_Value_CPU *>(it->second);

			const auto dimFunc = [sourceVal, this] {
				WorldGenAPI_CPU::structureGen->currentDataContext_ = parentContext_;
				const WGA_Value::Dimensionality result = parentContext_->getValueDimensionality(sourceVal);
				WorldGenAPI_CPU::structureGen->currentDataContext_ = this;

				return result;
			};
			const auto ctorFunc = [sourceVal, this](const WGA_DataRecord_CPU::Key &key) {
				ASSERT(WorldGenAPI_CPU::structureGen);
				ASSERT(WorldGenAPI_CPU::structureGen->currentDataContext_ == this);

				WorldGenAPI_CPU::structureGen->currentDataContext_ = parentContext_;
				auto result = parentContext_->getDataRecord(key, sourceVal->ctor());
				WorldGenAPI_CPU::structureGen->currentDataContext_ = this;

				return result;
			};

			WGA_Value_CPU *localVal = new WGA_Value_CPU(sourceVal->api(), sourceVal->valueType(), true, dimFunc, ctorFunc);
			temporarySymbols_.push_back(localVal);
			paramInputs_[it->first] = localVal;
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
	for(const WGA_GrammarSymbol::ParamSet &ps: sym_->paramSets())
		paramOutputs_[paramKey(ps.paramName, ps.value->valueType())] = ps.value;
}

WGA_DataRecord_CPU::Ptr WGA_StructureGenerator_CPU::DataContext::getDataRecord(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor) {
	WGA_DataRecord_CPU::Ptr result = dataCache_[key];
	if(result)
		return result;

	// Check if the symbol is param declare value, map it to actual param value
	;
	if(const auto f = paramKeyMapping_.find(key.symbol); f != paramKeyMapping_.end())
		result = static_cast<WGA_Value_CPU *>(paramInputs_[f->second])->getDataRecord(key.origin, key.subKey);
	else
		result = ctor(key);

	dataCache_[key] = result;
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
