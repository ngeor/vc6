// ChangeFileTimePS.cpp : Implementation of DLL Exports.

// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL,
//      run nmake -f ChangeFileTimePSps.mk in the project directory.

#include "StdAfx.h"
#if _MSC_VER > 1200
#include "ChangeFileTimePS_h.h"
#else
#include "ChangeFileTimePS.h"
#endif
#include "ChangeFileTimePS_i.c"
#include "ChangeFileTimeHandler.h"
#include "GlobalWinObjInstance.h"
#include "Resource.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_ChangeFileTimeHandler, CChangeFileTimeHandler)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance, &LIBID_CHANGEFILETIMEPSLib);
		DisableThreadLibraryCalls(hInstance);
		_WinObjInstance.SetHandle(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
		_WinObjInstance.Detach();
	}
	return TRUE; // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount() == 0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	return _Module.UnregisterServer(TRUE);
}
