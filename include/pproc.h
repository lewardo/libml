#pragma once

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