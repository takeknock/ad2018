#pragma once

#ifdef AD_EXPORT
    #define AD_API __declspec(dllexport)
#else
    #define AD_API __declspec(dllimport)
#endif

#ifdef MATH_EXPORT
    #define MATH_API __declspec(dllexport)
#else
    #define MATH_API __declspec(dllimport)
#endif

#ifdef DS_EXPORT
    #define DS_API __declspec(dllexport)
#else
    #define DS_API __declspec(dllimport)
#endif

