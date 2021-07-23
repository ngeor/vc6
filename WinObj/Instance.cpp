// Instance.cpp: implementation of the CInstance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Instance.h"

namespace WinObj
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInstance::CInstance(HINSTANCE instance) : CHandle<HINSTANCE>(instance)
{
}

CInstance::~CInstance()
{
}

LPTSTR CInstance::LoadString(int id) const
{
	HINSTANCE hInstance = GetHandle();
#if _MSC_VER > 1200
	LPTSTR readOnlyBuffer;
	int len = ::LoadString(hInstance, id, (LPTSTR)&readOnlyBuffer, 0);
	// because readOnlyBuffer isn't guaranteed to be null terminated
	LPTSTR result = (LPTSTR)calloc(sizeof(TCHAR), len + 1);
	_tcsncpy_s(result, len + 1, readOnlyBuffer, len);
#else
	TCHAR buffer[256];
	int len       = ::LoadString(hInstance, id, buffer, 256);
	LPTSTR result = (LPTSTR)calloc(sizeof(TCHAR), len + 1);
	_tcsncpy(result, buffer, len);
#endif
	return result;
}

} // namespace WinObj
