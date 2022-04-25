#pragma once

class WGLAPIContext;

using WGLDependencyList = std::unordered_set<WGLSymbol *>;

using WGLExpressionFunc = std::function<WGA_Value *(WGLAPIContext &ctx)>;

struct WGLExpressionResult {
	WGLExpressionFunc func;
	std::shared_ptr<std::string> signature;
	WGA_Value::ValueType type;
};