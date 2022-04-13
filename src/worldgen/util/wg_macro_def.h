#define ARG_NUM(name, ...) DEFER(ARG_T_3)(name, Float, Float2, Float3, __VA_ARGS__)
#define ARG_NUM_VEC(name, ...) DEFER(ARG_T_2)(name, Float2, Float3, __VA_ARGS__)

#define ARG_ANY(name, ...) DEFER(ARG_T_7)(name, Float, Float2, Float3, Bool, Block, Rule, ComponentNode, __VA_ARGS__)

#define ARGS_0(x, ...) DEFER(ARGS_END)(__VA_ARGS__)
#define ARGS_1(arg1, ...) ARG_APPLY(arg1, 1, DEFER(ARGS_END)(__VA_ARGS__))
#define ARGS_2(arg1, arg2, ...) ARG_APPLY(arg1, 1, ARG_APPLY(arg2, 2, DEFER(ARGS_END)(__VA_ARGS__)))
#define ARGS_3(arg1, arg2, arg3, ...) ARG_APPLY(arg1, 1, ARG_APPLY(arg2, 2, ARG_APPLY(arg3, 3, DEFER(ARGS_END)(__VA_ARGS__))))
#define ARGS_4(arg1, arg2, arg3, arg4, ...) ARG_APPLY(arg1, 1, ARG_APPLY(arg2, 2, ARG_APPLY(arg3, 3, ARG_APPLY(arg4, 4, DEFER(ARGS_END)(__VA_ARGS__)))))
#define ARGS_5(arg1, arg2, arg3, arg4, arg5, ...) ARG_APPLY(arg1, 1, ARG_APPLY(arg2, 2, ARG_APPLY(arg3, 3, ARG_APPLY(arg4, 4, ARG_APPLY(arg5, 5, DEFER(ARGS_END)(__VA_ARGS__))))))

#define ARG_T_2(name, T1, T2, i, Rest) ARG_T(name, T1, i, Rest) ARG_T(name, T2, i, Rest)
#define ARG_T_3(name, T1, T2, T3, i, Rest) ARG_T_2(name, T1, T2, i, Rest) ARG_T(name, T3, i, Rest)
#define ARG_T_4(name, T1, T2, T3, T4, i, Rest) ARG_T_2(name, T1, T2, i, Rest) ARG_T_2(name, T3, T4, i, Rest)
#define ARG_T_5(name, T1, T2, T3, T4, T5, i, Rest) ARG_T_4(name, T1, T2, T3, T4, i, Rest) ARG_T(name, T5, i, Rest)
#define ARG_T_6(name, T1, T2, T3, T4, T5, T6, i, Rest) ARG_T_5(name, T1, T2, T3, T4, T5, i, Rest) ARG_T(name, T6, i, Rest)
#define ARG_T_7(name, T1, T2, T3, T4, T5, T6, T7, i, Rest) ARG_T_6(name, T1, T2, T3, T4, T5, T6, i, Rest) ARG_T(name, T7, i, Rest)

#define ARG_ARG_OR_T(name, arg, T1, i, Rest) ARG_ARG(name, arg, i, Rest) ARG_T(name, T1, i, Rest)

#define DIM_MAX_3(v1, v2, v3) DIM_MAX_2(v1, DIM_MAX_2(v2, v3))

#define DIM_MAX_ARGS_1 DIM_ARG(1)
#define DIM_MAX_ARGS_2 DIM_MAX_2(DIM_ARG(1), DIM_ARG(2))
#define DIM_MAX_ARGS_3 DIM_MAX_3(DIM_ARG(1), DIM_ARG(2), DIM_ARG(3))

#define DIM_MIN_3(v1, v2, v3) DIM_MIN_2(v1, DIM_MIN_2(v2, v3))

#define DIM_MIN_ARGS_1 DIM_ARG(1)
#define DIM_MIN_ARGS_2 DIM_MIN_2(DIM_ARG(1), DIM_ARG(2))
#define DIM_MIN_ARGS_3 DIM_MIN_3(DIM_ARG(1), DIM_ARG(2), DIM_ARG(3))

#define IS_CONTEXTUAL_EXT false
#define IS_CONTEXTUAL_EXT_CONTEXTUAL true
#define IS_CONTEXTUAL_INLINE false

#define SECTION(...)
