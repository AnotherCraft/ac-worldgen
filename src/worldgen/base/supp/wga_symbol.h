#pragma once

#include <variant>
#include <string>
#include <unordered_map>

class WGA_Symbol {

public:
	using PragmaValue = std::variant<std::string, float, bool>;
	using PragmaList = std::unordered_map<std::string, PragmaValue>;
	enum class SymbolType {
		Abstract,
		Value,
		Biome,
		Component,
		Rule,
		RuleExpansion,
		StructureNode,
	};

public:
	WGA_Symbol();
	virtual ~WGA_Symbol();

	size_t ix;

public:
	virtual SymbolType symbolType() const;

	/// If true, the value is local to a structure/grammar symbol instance
	virtual bool isContextual() const;

public:
	PragmaValue pragma(const std::string &name) const;

	inline const auto &pragmas() const {
		return pragmas_;
	}

	void setPragma(const std::string &name, const PragmaValue &value = true);
	void setPragmas(const PragmaList &pragmas);

public:
	inline const std::string &description() const {
		return desc_;
	}

	inline void setDescription(const std::string &set) {
		desc_ = set;
	}

protected:
	PragmaList pragmas_;

private:
	std::string desc_, name_;

};

