import std.file;
import std.string;
import std.algorithm;
import std.array;
import std.format;
import std.range;
import std.regex;
import std.conv;
import std.stdio;
import std.exception;

import dyaml;

const baseTypes = [
	"Float", "Float2", "Float3",
	"Bool",
	"Block",
	"Rule", "ComponentNode"
	];

const baseDims = [
	"2D", "3D", "Const", "PerChunk"
	];

void main() {
	string apiCode;
	string implCode;

	size_t fid = 0;

	Node rootn = Loader.fromFile("functions.yaml").load();
	foreach(Node sectionn; rootn) {
		apiCode ~= "f.section = \"%s\";\n".format(sectionn["section"].as!string);

		foreach(Node funcn; sectionn["functions"]) {
			string functionName = funcn["function"].as!string;
			apiCode ~= "f.name = \"%s\";\n".format(functionName);

			auto resultd = funcn["result"].as!string.split(' ').array;
			string resultName = resultd[1];
			string resultType;
			apiCode ~= "f.returnValue.name = \"%s\";\n".format(resultName);

			string[][] argd;
			if("args" in funcn)
				argd = funcn["args"].as!(Node[]).map!(x => x.as!string.split(' ')).array;

			string[] argNames = argd.map!(x => x[1]).array;
			string[] argt = argd.map!(x => x[0]).array;
			apiCode ~= "f.arguments.resize(%s);\n".format(argt.length);
			foreach(size_t i, string argn; argNames)
				apiCode ~= "f.arguments[%s].name = \"%s\";\n".format(i, argn);

			bool isContextual;
			if("contextual" in funcn)
				isContextual = funcn["contextual"].as!bool;

			string[] argTypes;
			argTypes.length = argd.length;
			void procf(string t, int i, void delegate(string pt, int i) callback) {
				if(baseTypes.canFind(t))
					callback(t, i);
				else if(t == "Any") {
					foreach(string bt; baseTypes[])
						callback(bt, i);
				}
				else if(t == "Num") {
					callback("Float", i);	
					callback("Float2", i);	
					callback("Float3", i);	
				}
				else if(t == "Float2+") {
					callback("Float2", i);	
					callback("Float3", i);	
				}
				else if(auto m = t.matchFirst(ctRegex!"^Arg([0-9]+)$"))
					callback(argTypes[m[1].to!int-1], i);
				else if(auto m = t.matchFirst(ctRegex!"^Arg([0-9]+)Or([a-zA-Z]+)$")) {
					enforce(baseTypes.canFind(m[2]));
					callback(argTypes[m[1].to!int-1], i);
					callback(m[2], i);
				}
				else
					throw new Exception("Unknown template %s.".format(t));
			}

			void procEnd() {
				procf(resultd[0], 0, (string pt, int i) {
						resultType = pt;

						apiCode ~= "f.returnValue.type = WGA_Value::ValueType::%s;\n".format(resultType);
						apiCode ~= "f.id = %s;\n".format(fid);
						apiCode ~= "finalize();\n\n";

						string dimCode;
						string dim = "dim" in funcn ? funcn["dim"].as!string : null;
						if(baseDims.canFind(dim))
							dimCode = "WGA_Value::Dimensionality::D%s".format(dim);
						else if(auto m = dim.matchFirst(ctRegex!"^arg([0-9]+)$"))
							dimCode = "args[%s]->dimensionality()".format(m[1].to!int - 1);
						else if(dim == "max" || dim == null)
							dimCode = "std::max({%s})".format(iota(argt.length).map!(i => "args[%s]->dimensionality()".format(i)).join(", "));
						else if(dim == "min")
							dimCode = "std::min({%s})".format(iota(argt.length).map!(i => "args[%s]->dimensionality()".format(i)).join(", "));
						else if(dim.startsWith(":"))
							dimCode =
								dim[1..$]
									.replaceAll!(m => "args[%s]->dimensionality()".format(m[1].to!int - 1))(ctRegex!r"\barg([0-9]+)\b")
									;
						else
							throw new Exception("Unknown dimensionality: %s".format(dim));

						string fillCode = iota(argt.length).map!(i => "Arg%s argv%s = Arg%s(args[%s]);\n".format(i+1, i+1, i+1, i)).join;

						string impl = funcn["impl"].as!string;
						if(impl.startsWith(":"))
							fillCode ~= `return WGA_%sFuncs_CPU::%s(api, key, data %s);`.format(impl[1..$], functionName, iota(argt.length).map!(i => ", argv%s".format(i+1)).join);
						else
							fillCode ~=
`
%s
const int sz = data.size;
for(int i = 0; i < sz; i++) {
  %s
  data[i] = (%s);
 }
 return data;`.format(
 	iota(argt.length).map!(i => "Arg%s::DataHandle argh%s = argv%s.dataHandle(key.origin, key.subKey);\n".format(i+1, i+1, i+1)).join,
 	iota(argt.length).map!(i => "const Arg%s::T arg%s = argh%s[i];\n".format(i+1, i+1, i+1)).join,
 	impl
 	);

 						string argDecls = iota(argt.length).map!(i => "using Arg%s = WGA_ValueWrapper_CPU<WGA_Value::ValueType::%s>;\n".format(i+1, argTypes[i])).join;
						implCode ~=
`result[%s] = [] (WorldGenAPI_CPU *api, const WorldGenAPI::FunctionArgs &args) {
	const bool isContextual = %s || iterator(args).anyx(x->isContextual());

	// If the function call uses any contextual value, mark tall used arguments as cross sampled to keep them better in the cache
	if(isContextual) for(WGA_Value *v : args) static_cast<WGA_Value_CPU*>(v)->markAsCrossSampled(0);

	using Result = WGA_ValueWrapper_CPU<WGA_Value::ValueType::%s>;
	%s

	const auto dimFunc = [=] {
		auto result = %s;
		ASSERT(result != WGA_Value::Dimensionality::_count);
		return result;
	};
  const auto fillFunc = [=] (const WGA_DataRecord_CPU::Key &key, const typename Result::DataHandle &data) {
  	%s
  };
  return api->registerSymbol(new WGA_Value_CPU(*api, Result::valueType, isContextual, dimFunc, wga_fillCtor<Result::valueType>(dimFunc, fillFunc, "%s")));
};

`.format(fid, isContextual, resultType, argDecls, dimCode, fillCode, functionName);

						fid ++;
				});
			}

			if(argt.length) {
				void delegate(string pt, int i) callback;
				callback = (string pt, int i) {
					apiCode ~= "f.arguments[%s].type = WGA_Value::ValueType::%s;\n".format(i, pt);
					argTypes[i] = pt;
					i++;

					if(i < argt.length)
						procf(argt[i], i, callback);

					else
						procEnd();
				};
				procf(argt[0], 0, callback);
			}
			else
				procEnd();
		}
	}

	// Write to the files
	string apiTemplate =
`// This file was automatically generated by /supp/autogen.

#include "../worldgenapi.h"

const WorldGenAPI::Functions &WorldGenAPI::functions() {
	static const Functions fs = [] {
		Functions fs;
		Function f;

		const auto finalize = [&]() {
			f.prototype = Function::composePrototype(f.name, iterator(f.arguments).mapx(x.type).toList());
			fs.list.push_back(f);
			fs.prototypeMapping[f.prototype] = f.id;
			if(!fs.nameSet.contains(f.name))
				fs.nameList.push_back(f.name);
			fs.nameSet.insert(f.name);
			fs.nameMapping[f.name].push_back(f.id);
		};

		$IMPL$
		return fs;
	} ();
	return fs;
}
`;
	std.file.write("../../src/worldgen/base/autogen/wga_funcs.cpp", apiTemplate.replace("$IMPL$", apiCode));

	string implTemplate =
`
// This file was automatically generated by /supp/autogen.

#include "../funcs/wga_funcs_cpu.h"

#include "util/iterators.h"

#include "../supp/wga_fillfunc_cpu.h"

#include "../funcs/wga_biomefuncs_cpu.h"
#include "../funcs/wga_utilityfuncs_cpu.h"
#include "../funcs/wga_noisefuncs_cpu.h"
#include "../funcs/wga_structurefuncs_cpu.h"
#include "../funcs/wga_samplingfuncs_cpu.h"

std::unordered_map<WorldGenAPI::FunctionID, WGA_Funcs_CPU::Func> WGA_Funcs_CPU::functions() {
	static const auto result = [] {
		std::unordered_map<WorldGenAPI::FunctionID, Func> result;

		$IMPL$

		return result;
	}();
	return result;
}
`;
	std.file.write("../../src/worldgen/cpu/autogen/wga_funcs_cpu.cpp", implTemplate.replace("$IMPL$", implCode));
}