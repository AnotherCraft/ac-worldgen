#include "wga_funcs_cpu.h"

#include "util/iterators.h"
#include "util/macroutils.h"

#include "../supp/wga_fillfunc_cpu.h"

#include "wga_biomefuncs_cpu.h"
#include "wga_utilityfuncs_cpu.h"
#include "wga_noisefuncs_cpu.h"
#include "wga_structurefuncs_cpu.h"
#include "wga_samplingfuncs_cpu.h"

#pragma optimize("gt", on)

std::unordered_map<WorldGenAPI::FunctionID, WGA_Funcs_CPU::Func> WGA_Funcs_CPU::functions() {
	static const auto result = [] {
		std::unordered_map<WorldGenAPI::FunctionID, Func> result;

#include "worldgen/util/wg_macro_def.h"

#define DIM_MAX_2(v1, v2) std::max(v1, v2)
#define DIM_MIN_2(v1, v2) std::min(v1, v2)
#define DIM_C(c) WGA_Value::Dimensionality::D ## c
#define DIM_ARG(i) args[i-1]->dimensionality()

#define ARG_DEF(i) Arg ## i argv ## i = Arg ## i(args[i-1]);
#define IMPL_EXT_ARG(i) , argv ## i
#define IMPL_INLINE_ARG(i) Arg ## i::DataHandle argh ## i = argv ## i.dataHandle(key.origin, key.subKey);
#define IMPL_INLINE_ARG2(ix) const Arg ## ix::T arg ## ix = argh ## ix[i];

#define IMPL_EXT(Module, funcName, argCount) return WGA_ ## Module ## Funcs_CPU::funcName(api, key, data IOTA_F_ ## argCount(IMPL_EXT_ARG));
#define IMPL_EXT_CONTEXTUAL(Module, funcName, argCount) IMPL_EXT(Module, funcName, argCount)
#define IMPL_INLINE(expr, funcName, argCount) \
  IOTA_F_ ## argCount(IMPL_INLINE_ARG) \
  /*ZoneTransientN(_tracyZone, #funcName ":loop", true);*/ \
  const int sz = data.size; \
  for(int i = 0; i < sz; i++) { \
  IOTA_F_ ## argCount(IMPL_INLINE_ARG2) \
  data[i] = (expr); \
  };

#define ARGS_END(returnType, dim, argCount, impl, funcName) { \
  DEFER2(CONCAT)(RET_, M_ARG_1 returnType)(PREVENT_EATING_COMMA(M_ARG_1_REST returnType)) \
  const WorldGenAPI::Function &f = WorldGenAPI::functions().list[i++]; \
  ASSERT(#funcName == f.name); \
  result[f.id] = [] (WorldGenAPI_CPU *api, const WorldGenAPI::FunctionArgs &args) { \
  const bool isContextual = DEFER2(CONCAT)(IS_CONTEXTUAL_, M_ARG_1 impl) || iterator(args).anyx(x->isContextual()); \
  if(isContextual) for(WGA_Value *v : args) static_cast<WGA_Value_CPU*>(v)->markAsCrossSampled(0); /* If the function call uses any contextual value, mark tall used arguments as cross sampled to keep them better in the cache */ \
  const auto dimFunc = [=] { auto result = dim; ASSERT(result != WGA_Value::Dimensionality::_count); return dim; }; \
  const auto fillFunc = [=] (const WGA_DataRecord_CPU::Key &key, const typename Result::DataHandle &data) { \
  IOTA_F_ ## argCount (ARG_DEF) \
  DEFER2(CONCAT)(IMPL_, M_ARG_1 impl)(PREVENT_EATING_COMMA(M_ARG_1_REST impl), funcName, argCount) \
  }; \
  return api->registerSymbol(new WGA_Value_CPU(*api, Result::valueType, isContextual, dimFunc, wga_fillCtor<Result::valueType>(dimFunc, fillFunc, #funcName))); \
  }; \
  }

#define ARG_ARG(name, ai, i, Rest) { \
  using Arg ## i = Arg ## ai; \
  Rest \
  }
#define ARG_T(name, T, i, Rest) { \
  using Arg ## i = WGA_ValueWrapper_CPU<WGA_Value::ValueType::T>; \
  Rest \
  }

#define RET_T(name, T) using Result = WGA_ValueWrapper_CPU<WGA_Value::ValueType::T>;
#define RET_ARG(name, i) using Result = Arg ## i;

#define ARG_APPLY(arg, i, Rest) DEFER2(CONCAT)(ARG_, M_ARG_1 arg)(PREVENT_EATING_COMMA(M_ARG_1_REST arg), i, DEFER8(Rest))
#define FUNC(funcName, argCount, args, returnType, dim, impl, desc, ...) DEFER(ARGS_ ## argCount)(DEFER(DEFER args), returnType, dim, argCount, impl, funcName)

		int i = 0;
		WORLDGEN_FUNCTIONS


#undef ARG_DEF
#undef IMPL_EXT_ARG
#undef IMPL_INLINE_ARG
#undef IMPL_INLINE_ARG2

#include "worldgen/util/wg_macro_undef.h"

		return result;
	}();

	return result;
}
