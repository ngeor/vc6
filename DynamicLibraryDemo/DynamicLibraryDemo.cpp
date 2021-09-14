// DynamicLibraryDemo.cpp : Defines the entry point for the DLL application.
//

#include "StdAfx.h"
#define DLL_EXPORTING
#include "DynamicLibraryDemo.h"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

extern "C" DECLSPEC int __stdcall Add(int a, int b)
{
	return a + b;
}
