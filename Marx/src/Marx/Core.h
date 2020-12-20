#pragma once

#ifdef MX_PLATFORM_WINDOWS
  #ifdef MX_BUILD_DLL
    #define MARX_API __declspec(dllexport)
  #else
    #define MARX_API __declspec(dllimport)
  #endif
#else
  #error Marx only supports Windows!
#endif

#define DISABLE_DLL_INTERFACE_WARN  __pragma(warning(push)) \
                                      __pragma(warning(disable:4251))
#define REENABLE_DLL_INTERFACE_WARN __pragma(warning(pop))

#ifdef MX_ENABLE_ASSERTS
#define MX_ASSERT(x, ...)      { if (!(x)) { MX_ERROR     ("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
#define MX_CORE_ASSERT(x, ...) { if (!(x)) { MX_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define MX_ASSERT(x, ...)
#define MX_CORE_ASSERT(x, ...)
#endif

// Bitwise Flag operations
#define FLAG(f) (1 << f)
#define SET_FLAG(x, f) (x |= BIT(f))
#define CLEAR_FLAG(x, f) (x &= ~BIT(f))
#define HAS_FLAG(x, f) (x & FLAG(f))