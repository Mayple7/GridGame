/*!****************************************************************************
File:       MacroUtilities.h

******************************************************************************/
/*=================================
*         include guard
*/
#pragma once

/*=================================
*           Macros
*/
// Taken From http://stackoverflow.com/questions/9183993/msvc-variadic-macro-expansion/9338429#9338429
#define GLUE(x, y) x y

#define RETURN_ARG_COUNT(_1_, _2_, _3_, _4_, _5_, count, ...) count
#define EXPAND_ARGS(args) RETURN_ARG_COUNT args
#define COUNT_ARGS_MAX5(...) EXPAND_ARGS((__VA_ARGS__, 5, 4, 3, 2, 1, 0))

#define OVERLOAD_MACRO2(name, count) name##count
#define OVERLOAD_MACRO1(name, count) OVERLOAD_MACRO2(name, count)
#define OVERLOAD_MACRO(name, count) OVERLOAD_MACRO1(name, count)

// Can only overload for a max of 5 args
#define CALL_OVERLOAD(name, ...) GLUE(OVERLOAD_MACRO(name, COUNT_ARGS_MAX5(__VA_ARGS__)), (__VA_ARGS__))

// Concatenate macros
#define CONCATENATE2(A,B) A ## B
#define CONCATENATE3(A, B, C) A ## B ## C
#define CONCATENATE4(A, B, C, D) A ## B ## C ## D
#define CONCATENATE5(A, B, C, D, E) A ## B ## C ## D ## E

#define CONCATENATE(...) CALL_OVERLOAD(CONCATENATE, __VA_ARGS__)

#define ALLOCA(TYPE, COUNT) \
  reinterpret_cast<TYPE *>(sizeof(TYPE) * COUNT)
