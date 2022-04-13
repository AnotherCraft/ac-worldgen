#pragma once

/// Very fast cache that keeps a fixed number of results
template<typename Key>
class QuickCache {

public:
	/// Sets the cached key to @key. Returns true if the key was already @key.
	inline bool isAndSet(const Key &key) {
		const bool result = hasLastVal_ && lastKey_ == key;
		if(!result) {
			hasLastVal_ = true;
			lastKey_ = key;
		}
		return result;
	}

private:
	bool hasLastVal_ = false;
	Key lastKey_;

};
