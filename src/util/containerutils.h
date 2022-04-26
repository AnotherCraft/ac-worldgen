#pragma once

#include <cstdlib>

class ContainerUtils {

public:
	/// Takes sampleCount random samples and returns index of the one with best scoreFunc(value)
	template<typename C, typename ScoreFunc>
	static size_t probabilisticSelect(const C &c, const ScoreFunc &scoreFunc, size_t sampleCount = 32) {
		using Score = decltype(scoreFunc(std::declval<decltype(c[0])>()));

		if(c.isEmpty())
			return -1;

		const size_t sz = c.size();
		sampleCount = std::min(sz, sampleCount);

		int bestIx = std::rand() % sz;
		Score bestScore = scoreFunc(c[bestIx]);
		for(size_t i = 1; i < sampleCount; i++) {
			const size_t ix = std::rand() % sz;
			const Score score = scoreFunc(c[ix]);

			if(score > bestScore) {
				bestScore = score;
				bestIx = ix;
			}
		}

		return bestIx;
	}

};