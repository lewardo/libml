#pragma once

//  https://stackoverflow.com/a/11994395

#define FE_0(WHAT)
#define FE_1(WHAT, X) WHAT(X) FE_0(WHAT)
#define FE_2(WHAT, X, ...) WHAT(X) FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X) FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X) FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X) FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X) FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X) FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X) FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X) FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT(X) FE_9(WHAT, __VA_ARGS__)
#define FE_11(WHAT, X, ...) WHAT(X) FE_10(WHAT, __VA_ARGS__)
#define FE_12(WHAT, X, ...) WHAT(X) FE_11(WHAT, __VA_ARGS__)
#define FE_13(WHAT, X, ...) WHAT(X) FE_12(WHAT, __VA_ARGS__)
#define FE_14(WHAT, X, ...) WHAT(X) FE_13(WHAT, __VA_ARGS__)
#define FE_15(WHAT, X, ...) WHAT(X) FE_14(WHAT, __VA_ARGS__)
#define FE_16(WHAT, X, ...) WHAT(X) FE_15(WHAT, __VA_ARGS__)

#define GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, \
                  _14, _15, _16, NAME, ...)                                   \
  NAME
#define FOR_EACH(action, ...)                                                 \
  GET_MACRO(_0, __VA_ARGS__, FE_16, FE_15, FE_14, FE_13, FE_12, FE_11, FE_10, \
            FE_9, FE_8, FE_7, FE_6, FE_5, FE_4, FE_3, FE_2, FE_1, FE_0)       \
  (action, __VA_ARGS__)

#define STRINGIZE(s) __STRINGIZE1(s)
#define __STRINGIZE1(s) __STRINGIZE2(s)
#define __STRINGIZE2(s) #s

#define CONCATENATE(a, b) __CONCATENATE1(a, b)
#define __CONCATENATE1(a, b) __CONCATENATE2(a, b)
#define __CONCATENATE2(a, b) a##b

#define ML_USING_DECL(NS) using namespace ::ml::NS;
#define libml_using(...) \
  using namespace ::ml;  \
  FOR_EACH(ML_USING_DECL, __VA_ARGS__)