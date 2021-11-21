#pragma once

#if EU_DEBUG
#define EU_ENABLE_ASSERT
#endif

#ifdef EU_ENABLE_ASSERT
#define EU_ASSERT(x, ...) {if(!(x)){ EU_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#define EU_CORE_ASSERT(x, ...) {if(!(x)){ EU_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define EU_ASSERT(x, ...)
#define EU_CORE_ASSERT(x, ...)
#endif  


#define BIT(x) (1 << x)

#define EU_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
