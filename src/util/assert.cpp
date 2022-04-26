#include "assert.h"

#include <iostream>
#include <format>

void assertError(const char *assert, const char *file, int line, const std::string &msg) {
	std::cerr << std::format("\n!!! assert FAILURE ({}:{}): {}\n", file, line, !msg.empty() ? msg : assert);
	throw AssertFailureException();
}
