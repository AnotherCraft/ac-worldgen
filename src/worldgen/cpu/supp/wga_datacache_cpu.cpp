#include "wga_datacache_cpu.h"

#include "util/tracyutils.h"
#include "util/bytesizeliterals.h"
#include "util/forit.h"
#include "util/iterators.h"

#include "wga_value_cpu.h"

const size_t WGA_DataCache_CPU::cacheSizes[+CacheType::_count] = {
	32_MB, // Const,
	128_MB, // PerChunk,
	1024_MB, // NonLocal2D,
	256_MB, // Local2D,
	1024_MB, // NonLocal3D,
	256_MB, // Local3D,
};

WGA_DataCache_CPU::WGA_DataCache_CPU() {
	for(int i = 0; i < +CacheType::_count; i++) {
		for(int j = 0; j < cacheDivisions; j++)
			cacheData_[i][j].cache.setMemoryCapacity(qMax<size_t>(1, cacheSizes[i] / cacheDivisions));

		TracyPlotConfig(TracyUtils::mapName(QStringLiteral("dataCacheHitRate[%1]").arg(i)), tracy::PlotFormatType::Percentage);
	}
}

WGA_DataCache_CPU::~WGA_DataCache_CPU() {

}

WGA_DataCache_CPU::DataRecordPtr WGA_DataCache_CPU::get(const WGA_DataRecord_CPU::Key &key, const WGA_DataRecord_CPU::Ctor &ctor) {
	ASSERT(key.origin.xy() % chunkSize.xy() == 0);

	DataRecordPtr result;

	const CacheType cacheType = getCacheType(key.symbol, key.subKey);
	const int divisionIx = qHash(key.symbol, qHash(key.origin.x() / 16, qHash(key.origin.y() / 16))) % cacheDivisions;
	ASSERT(divisionIx >= 0 && divisionIx < cacheDivisions);
	CacheData &cd = cacheData_[+cacheType][divisionIx];

	bool isHit = false;
	bool isMiss = false;

	// Try getting the data
	{
		//ZoneScopedN("dcCheck");
		QMutexLocker _ml(&cd.mutex);

		if(auto p = cd.cache.get(key)) {
			result = p;
			isHit = true;
		}
		else if(cd.generatedKeys.contains(key))
			isMiss = true;
	}

	// Not in the cache - we must create it and put it there
	if(!result) {
		{
			//ZoneScopedN("dcGen");

			missCount_[+cacheType]++;
			result = ctor(key);
		}

		{
			//ZoneScopedN("dcWrite");

			QMutexLocker _ml(&cd.mutex);
			cd.cache.insert(key, result, result->dataSize());
			cd.generatedKeys.insert(key);
		}
	}
	else
		hitCount_[+cacheType]++;

	// Report statistics
	{
		Key statsKey = key;
		statsKey.origin = BlockWorldPos();

		QWriteLocker _ml(&recordStatsMutex_);
		RecordStats *stats = &recordStats_[statsKey];

		if(isHit)
			stats->hitCount++;
		else if(isMiss)
			stats->missCount++;
		else
			stats->genCount++;
	}

	return result;
}

void WGA_DataCache_CPU::reportHitRate() {
	if(0) {
		struct S {
			Key key;
			RecordStats value;
		};

		QMap<int, S> m;
		{
			QReadLocker _ml(&recordStatsMutex_);
			forit(recordStats_) m.insert(-it.value().missCount, S{it.key(), it.value()});
		}

		for(const S &s: m) {
			const bool isValue = dynamic_cast<WGA_Value_CPU *>(s.key.symbol);
			const bool isCrossSampled = isValue ? static_cast<WGA_Value_CPU *>(s.key.symbol)->isCrossSampled(0) : false;
			qDebug()
				<< " | MISS " << QString::number(s.value.missCount).rightJustified(6)
				<< " | HIT " << QString::number(s.value.hitCount).rightJustified(6)
				<< " | MIR " <<
				QString::number(static_cast<double>(s.value.missCount) / (s.value.missCount + s.value.hitCount) * 100, 'f',
				                2).rightJustified(6) + " %"
				<< " | GEN " << QString::number(s.value.genCount).rightJustified(6)
				<< " | " << QString(QMetaEnum::fromType<WGA_Value::Dimensionality>().valueToKey(
				+(isValue ? static_cast<WGA_Value_CPU *>(s.key.symbol)->dimensionality()
				          : WGA_Value::Dimensionality::Unknown))).leftJustified(6)
				<< " | " << (s.key.symbol->isContextual() ? "CTX" : "   ")
				<< " | " << (isCrossSampled ? "CS" : "  ")
				<< " | " << s.key.symbol->description() << s.key.subKey;
		}

		qDebug() << "\n\n\n\n";
	}

	for(int i = 0; i < +CacheType::_count; i++) {
		const int missCount = missCount_[i], hitCount = hitCount_[i];

		/*if(missCount + hitCount > 0)
			TracyPlot(TracyUtils::mapName(QStringLiteral("dataCacheHitRate[%1]").arg(i)), hitCount / (static_cast<float>(missCount) + hitCount) * 100.0f);*/
	}
}

WGA_DataCache_CPU::CacheType WGA_DataCache_CPU::getCacheType(WGA_Symbol *symbol, int subKey) {
	if(symbol->symbolType() != WGA_Symbol::SymbolType::Value)
		return CacheType::PerChunk;

	WGA_Value_CPU *val = static_cast<WGA_Value_CPU *>(symbol);
	const Dimensionality dim = val->dimensionality();
	const bool isNonLocal = val->isCrossSampled(subKey);

	if(dim == Dimensionality::DConst)
		return CacheType::Const;

	else if(dim == Dimensionality::DPerChunk)
		return CacheType::PerChunk;

	else if(dim == Dimensionality::D2D && isNonLocal)
		return CacheType::NonLocal2D;
	else if(dim == Dimensionality::D2D && !isNonLocal)
		return CacheType::Local2D;

	else if(dim == Dimensionality::D3D && isNonLocal)
		return CacheType::NonLocal3D;
	else if(dim == Dimensionality::D3D && !isNonLocal)
		return CacheType::Local3D;

	else
		throw;
}
