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

