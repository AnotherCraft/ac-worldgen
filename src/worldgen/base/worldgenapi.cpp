#include "worldgenapi.h"

#include <math.h>

#include "util/iterators.h"
#include "util/macroutils.h"

const WorldGenAPI::Functions &WorldGenAPI::functions() {
	static const Functions fs = [] {
		Functions fs;
		Function f;

		const auto finalize = [&]() {
			f.prototype = Function::composePrototype(f.name, iterator(f.arguments).mapx(x.type).toList());
			f.id = fs.list.size();
			fs.list += f;
			fs.prototypeMapping[f.prototype] = f.id;
			if(!fs.nameSet.contains(f.name))
				fs.nameList += f.name;
			fs.nameSet += f.name;
			fs.nameMapping[f.name] += f.id;
		};

#include "worldgen/util/wg_macro_def.h"

#undef SECTION
#define SECTION(name) f.section = name;

#define ARGS_END(returnType) \
  DEFER2(CONCAT)(RET_, M_ARG_1 returnType)(PREVENT_EATING_COMMA(M_ARG_1_REST returnType)) \
  finalize();

#define ARG_ARG(name, ai, i, Rest) \
  f.arguments[i-1] = FunctionArgument(f.arguments[ai-1].type, #name); \
  Rest
#define ARG_T(name, T, i, Rest) \
  f.arguments[i-1] = FunctionArgument(Type::T, #name); \
  Rest

#define RET_T(name, T) f.returnValue = FunctionArgument(Type::T, #name);
#define RET_ARG(name, i) f.returnValue = FunctionArgument(f.arguments[i-1].type, #name);

#define ARG_APPLY(arg, i, Rest) DEFER2(CONCAT)(ARG_, M_ARG_1 arg)(PREVENT_EATING_COMMA(M_ARG_1_REST arg), i, DEFER8(Rest))
#define FUNC(funcName, argCount, args, returnType, dim, impl, desc, ...) \
  f.name = #funcName; \
  f.arguments.resize(argCount); \
  f.description = desc; \
  DEFER(ARGS_ ## argCount)(DEFER(DEFER args), returnType)

		WORLDGEN_FUNCTIONS

#include "worldgen/util/wg_macro_undef.h"

		return fs;
	}();
	return fs;
}

WorldGenAPI::WorldGenAPI(WorldGenSeed seed) : seed_(seed) {

}

WorldGenAPI::~WorldGenAPI() {

}

QString WorldGenAPI::Function::composePrototype(const QString &functionName, const QVector <WGA_Value::ValueType> &argTypes) {
	return QStringLiteral("%1(%2)").arg(functionName, iterator(argTypes).mapx(WGA_Value::typeNames[x]).join(", "));
}

void WorldGenAPI::Functions::generateDocumentation(QTextStream &ts) const {
	const WorldGenAPI::Functions &functions = WorldGenAPI::functions();

	QString section;

	for(const QString &fn: functions.nameList) {
		const QString s = list[functions.nameMapping[fn].first()].section;
		if(section != s) {
			section = s;
			ts << QStringLiteral("# %1 \n\n").arg(s);
		}

		ts << QStringLiteral("## `%1` \n").arg(fn);

		QMap <QString, QString> prototypesByDescription;
		QSet < QString > mentionedPrototypes;

		for(const WorldGenAPI::FunctionID fid: functions.nameMapping[fn]) {
			const WorldGenAPI::Function &f = functions.list[fid];
			const QString prototype = QStringLiteral("%1 %2(%3)\n").arg(
				WGA_Value::typeNames[f.returnValue.type],
				f.name,
				iterator(f.arguments).mapx(QStringLiteral("%1 %2").arg(WGA_Value::typeNames[x.type], x.name)).join(", ")
			);

			if(mentionedPrototypes.contains(prototype))
				continue;

			mentionedPrototypes += prototype;
			prototypesByDescription[f.description] += prototype;
		}

		for(auto it = prototypesByDescription.begin(), end = prototypesByDescription.end(); it != end; it++) {
			ts << "```WOGLAC\n";
			ts << it.value(); // Prototypes
			ts << "```\n";

			ts << "\n";
			ts << it.key(); // Description
			ts << "\n";
		}
	}
}
