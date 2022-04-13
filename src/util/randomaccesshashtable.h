#pragma once

#include <QRandomGenerator>

/// Hash table that allows random access (via indexes)
/// Index for an item can change if other item is deleted
template<typename Key, typename Value>
class RandomAccessHashTable {

public:
	inline int size() const {
		return records_.size();
	}

	inline bool isEmpty() const {
		return records_.isEmpty();
	}

public:
	inline void insert(const Key &key, const Value &value) {
		(*this)[key] = value;
	}

	inline void remove(const Key &key) {
		if(const int ix = indexes_.value(key, -1); ix != -1)
			removeIndex(ix);
	}

	inline Value take(const Key &key) {
		if(const int ix = indexes_.value(key, -1); ix != -1)
			return takeIndex(ix);

		return Value();
	}

public:
	void removeIndex(int ix) {
		ASSERT(ix >= 0 && ix < size());

		Record &r = records_[ix];
		indexes_.remove(r.key);

		// Item is on the back - just remove it
		if(ix == records_.size() - 1)
			records_.removeLast();

		else {
			// Item is not on the back - swap
			r = records_.takeLast();
			ASSERT(indexes_.value(r.key) == records_.size());
			indexes_[r.key] = ix;
		}
	}

	Value takeIndex(int ix) {
		ASSERT(ix >= 0 && ix < size());

		const Value rv = records_[ix].value;
		removeIndex(ix);
		return rv;
	}

	/// Takes sampleCount random samples and returns index of the one with best scoreFunc(value)
	template<typename ScoreFunc>
	inline int probabilisticSelect(const ScoreFunc &scoreFunc, int sampleCount = 16) const {
		using Score = decltype(scoreFunc(Value()));

		if(isEmpty())
			return -1;

		QRandomGenerator &rg = *QRandomGenerator::global();
		const int sz = size();

		int bestIx = rg.bounded(sz);
		Score bestScore = scoreFunc(records_[bestIx].value);
		for(int i = 1; i < sampleCount; i++) {
			const int ix = rg.bounded(sz);
			const Score score = scoreFunc(records_[ix].value);

			if(score > bestScore) {
				bestScore = score;
				bestIx = ix;
			}
		}

		return bestIx;
	}

public:
	Value value(const Key &key, const Value &defaultValue = Value()) const {
		const int i = indexes_.value(key, -1);
		return (i == -1) ? defaultValue : records_[i].value;
	}

	inline Value &defaultValue() {
		return defaultValue_;
	}

	/// Reutrns reference to value if key exists or reference to defaultValue()
	Value &valueRef(const Key &key) {
		const int i = indexes_.value(key, -1);
		return (i == -1) ? defaultValue_ : records_[i].value;
	}

	Value &operator [](const Key &key) {
		const auto cnt = records_.size();
		const int i = indexes_.value(key, cnt);

		// Key exists - return the value
		if(i != cnt)
			return records_[i].value;

		indexes_.insert(key, cnt);
		Record &rec = records_.emplaceBack(key);
		return rec.value;
	}

private:
	struct Record {

	public:
		inline Record() = default;
		inline Record(const Record &o) = default;

		inline Record(const Key &k) : key(k) {}

	public:
		Key key;
		Value value;

	};
	QHash<Key, int> indexes_;
	QVector<Record> records_;
	Value defaultValue_;

};