#pragma once

#include <string>

#ifdef QT_DEBUG
#define ASSERT(cond, ...) ((cond) ? static_cast<void>(0) : assertError(#cond, __FILE__, __LINE__, __VA_ARGS__))
#else
#define ASSERT(cond, ...) static_cast<void>(false && (cond))
#endif

#define ENFORCE(cond, ...) ((cond) ? static_cast<void>(0) : assertError(#cond, __FILE__, __LINE__, __VA_ARGS__))

struct AssertFailureException {

};

void assertError(const char *assert, const char *file, int line, const std::string &msg = {});
