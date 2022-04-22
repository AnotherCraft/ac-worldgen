#pragma once

template<typename T>
class ValueGuard {

public:
	inline ValueGuard(T &ref) : ref_(ref), origValue_(ref) {}

	template<typename T2>
	inline ValueGuard(T &ref, const T2 &set)    : ref_(ref), origValue_(ref) { ref = set; }

	inline ~ValueGuard() { ref_ = origValue_; }

private:
	T &ref_;
	const T origValue_;

};
