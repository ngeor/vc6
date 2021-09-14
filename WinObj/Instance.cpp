// Instance.cpp: implementation of the CInstance class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Instance.h"

namespace WinObj
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInstance::CInstance()
{
}

CInstance::CInstance(HINSTANCE instance) : CHandle<HINSTANCE>(instance)
{
}

CInstance::~CInstance()
{
}

str CInstance::LoadStr(int id) const
{
	HINSTANCE hInstance = GetHandle();
#if _MSC_VER > 1200
	LPTSTR readOnlyBuffer;
	// get a read-only buffer into the string resource
	int len = ::LoadString(hInstance, id, (LPTSTR)&readOnlyBuffer, 0);
	return str(readOnlyBuffer, len);
#else
	TCHAR buffer[256];
	int len = ::LoadString(hInstance, id, buffer, 256);
	return str(buffer, len);
#endif
}

} // namespace WinObj
