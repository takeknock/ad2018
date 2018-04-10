#pragma once

#ifdef DS_EXPORT
#define DS_API __declspec(dllexport)
#else
#define DS_API __declspec(dllimport)
#endif