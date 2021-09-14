#pragma once

#ifdef DLL_EXPORTING
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

extern "C" DECLSPEC int __stdcall Add(int a, int b);
