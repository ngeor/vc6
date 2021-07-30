// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__2F4EC3E0_9FC7_4974_AC23_B73EEBFB947A__INCLUDED_)
#define AFX_STDAFX_H__2F4EC3E0_9FC7_4974_AC23_B73EEBFB947A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <atlbase.h>
// You may derive a class from CComModule and use it if you want to override
// something, but do not change the name of _Module
extern CComModule _Module;
#include <assert.h>
#include <atlcom.h>
#include <comdef.h>
#include <shellapi.h>
#include <shlobj.h>
#include <string>
#include <vector>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2F4EC3E0_9FC7_4974_AC23_B73EEBFB947A__INCLUDED)
