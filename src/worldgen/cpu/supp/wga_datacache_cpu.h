#pragma once

#include <QVector>
#include <QCache>
#include <QMutex>
#include <QReadWriteLock>
#include <QSharedPointer>

#include "util/enumutils.h"
#include "worldgen/base/supp/wga_value.h"

#include "wga_datarecord_cpu.h"
#include "wga_datacacheinstance_cpu.h"

class WGA_DataCache_CPU {

public:
	using DataRecordPtr = QSharedPointer<WGA_DataRecord_CPU>;
	using Dimensionality = WGA_Value::Dimensionality;
	using Key = WGA_DataRecord_CPU::Key;
	using Ctor = WGA_DataRecord_CPU::Ctor;

public:
	WGA_DataCache_CPU();
	~WGA_DataCache_CPU();

public:
	/// Subkey - can be used if you need multiple data records per one symbol (used in structurefuncs)
	DataRecordPtr get(const Key &key, const Ctor &ctor);

	void reportHitRate();

private:
	enum class CacheType {
		Const,
		PerChunk,
		NonLocal2D,
		Local2D,
		NonLocal3D,
		Local3D,
		_count
	};
	static const size_t cacheSizes[+CacheType::_count];
	/// The cache is split into multiple separate bins to reduce mutex collisions (each record's bin is determined by the hash)
	static constexpr int cacheDivisions = 8;

private:
	static CacheType getCacheType(WGA_Symbol *symbol, int subKey);

private:
	struct CacheData {
		WGA_DataCacheInstance_CPU cache;
		QSet<Key> generatedKeys; /// Set of all already genreated keys, even those that aren't in the cache anymore

		//TracyLockable(QMutex, mutex);
		QMutex mutex;
	};
	CacheData cacheData_[+CacheType::_count][cacheDivisions];

private:
	QAtomicInt hitCount_[+CacheType::_count], missCount_[+CacheType::_count];

private:
	struct RecordStats {
		int hitCount = 0;
		int missCount = 0;
		int genCount = 0;
	};
	QHash<Key, RecordStats> recordStats_; ///< Key.origin is set to 0
	QReadWriteLock recordStatsMutex_;

};

