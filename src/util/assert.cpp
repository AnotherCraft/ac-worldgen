#include "assert.h"

#include <iostream>
#include <format>

void assertError(const char *assert, const char *file, int line, const std::string &msg) {
	std::cout << std::format("\n\n\n!!! assert FAILURE ({}:{}): {}", file, line, !msg.empty() ? msg : assert);
	throw AssertFailureException();
}
