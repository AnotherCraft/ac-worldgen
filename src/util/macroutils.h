#pragma once

#define DO_NOTHING(...) (void) nullptr
#define BREAKABLE_SCOPE for(bool CONCAT(breakable_, __LINE__) = true; CONCAT(breakable_, __LINE__); CONCAT(breakable_, __LINE__) = false)

#define NOTHING

#define WRAP(x) x

#define STRINGIFY_DELAYED(x) STRINGIFY(x)
#define STRINGIFY(x) #x

#define PRIMITIVE_CONCAT(a, b) a ## b
#define PRIMITIVE_CONCAT3(a, b, c) a ## b ## c

#define CONCAT(a, b) PRIMITIVE_CONCAT(a, b)
#define CONCAT3(a, b, c) PRIMITIVE_CONCAT3(a, b, c)

#define M_ARG_1(a, ...) a
#define M_ARG_1_REST(a, ...) __VA_ARGS__

#define REMOVE_PARENT(...) REMOVE_PARENT_IMPL __VA_ARGS__
#define REMOVE_PARENT_IMPL(...) __VA_ARGS__

#define DEFER(...) __VA_ARGS__ NOTHING
#define DEFER2(...) DEFER(__VA_ARGS__)
#define DEFER4(...) DEFER2(DEFER2(__VA_ARGS__))
#define DEFER8(...) DEFER4(DEFER4(__VA_ARGS__))
#define DEFER16(...) DEFER8(DEFER8(__VA_ARGS__))
#define DEFER32(...) DEFER16(DEFER16(__VA_ARGS__))

#define IOTA_F_0(F, ...)
#define IOTA_F_1(F, ...) DEFER(F)(1, __VA_ARGS__)
#define IOTA_F_2(F, ...) DEFER(F)(1, __VA_ARGS__) DEFER(F)(2, __VA_ARGS__)
#define IOTA_F_3(F, ...) DEFER(F)(1, __VA_ARGS__) DEFER(F)(2, __VA_ARGS__) DEFER(F)(3, __VA_ARGS__)
#define IOTA_F_4(F, ...) DEFER(F)(1, __VA_ARGS__) DEFER(F)(2, __VA_ARGS__) DEFER(F)(3, __VA_ARGS__) DEFER(F)(4, __VA_ARGS__)
#define IOTA_F_5(F, ...) DEFER(F)(1, __VA_ARGS__) DEFER(F)(2, __VA_ARGS__) DEFER(F)(3, __VA_ARGS__) DEFER(F)(4, __VA_ARGS__) DEFER(F)(5, __VA_ARGS__)

#define ARG_COUNT_IMPL(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, ...) a16
#define ARG_COUNT(...) ARG_COUNT_IMPL(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, ERR ERR, ERR ERR, ERR ERR, ERR ERR)

#define PWRAP_0(x)
#define PWRAP_1(x, a0) a0
#define PWRAP_2(x, a0, a1) a0, a1
#define PWRAP_3(x, a0, a1, a2) a0, a1, a2
#define PWRAP_4(x, a0, a1, a2, a3) a0, a1, a2, a3
#define PWRAP_5(x, a0, a1, a2, a3, a4) a0, a1, a2, a3, a4
#define PWRAP_6(x, a0, a1, a2, a3, a4, a5) a0, a1, a2, a3, a4, a5
#define PWRAP_7(x, a0, a1, a2, a3, a4, a5, a6) a0, a1, a2, a3, a4, a5, a6
#define PWRAP_8(x, a0, a1, a2, a3, a4, a5, a6, a7) a0, a1, a2, a3, a4, a5, a6, a7
#define PWRAP_9(x, a0, a1, a2, a3, a4, a5, a6, a7, a8) a0, a1, a2, a3, a4, a5, a6, a7, a8
#define PWRAP_10(x, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) a0, a1, a2, a3, a4, a5, a6, a7, a8, a9

#define PREVENT_EATING_COMMA(...) CONCAT(PWRAP_, ARG_COUNT(__VA_ARGS__))(x, __VA_ARGS__)
