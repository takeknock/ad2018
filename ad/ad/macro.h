#pragma once

#ifdef AD_EXPORT
    #define AD_API __declspec(dllexport)
#else
    #define AD_API __declspec(dllimport)
#endif
