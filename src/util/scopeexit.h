#pragma once

#include <functional>

struct ScopeExit {
	std::function<void()> f;

	inline ScopeExit(const std::function<void()> &f) : f(f) {}

	inline ~ScopeExit() { f(); }
};

#define STRING_JOIN2(arg1, arg2) DO_STRING_JOIN2(arg1, arg2)
#define DO_STRING_JOIN2(arg1, arg2) arg1 ## arg2
#define SCOPE_EXIT(code) \
    ScopeExit STRING_JOIN2(scope_exit_, __LINE__)([&](){code;})
