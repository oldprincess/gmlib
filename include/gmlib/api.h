#ifndef GMLIB_API_H
#define GMLIB_API_H

#ifdef GMLIB_BUILD_DLL

#if defined(_WIN32) || defined(_WIN64)
#define GMLIB_API __declspec(dllexport)
#elif defined(__GNUC__)
// use -fvisibility=hidden to change the "default" behavior
#define GMLIB_API __attribute__((visibility("default")))
#else
#define GMLIB_API
#endif

#else

#define GMLIB_API

#endif

#endif
