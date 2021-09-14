// WindowClass.cpp: implementation of the CWindowClass class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "WindowClass.h"

namespace WinObj
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWindowClass::CWindowClass()
{
	_wcex.cbSize     = sizeof(WNDCLASSEX);
	_wcex.cbClsExtra = 0;
	_wcex.style      = CS_HREDRAW | CS_VREDRAW;
}

CWindowClass::CWindowClass(const CWindowClass& other)
{
}

CWindowClass::~CWindowClass()
{
}

CWindowClass& CWindowClass::Dialog()
{
	_wcex.lpfnWndProc = (WNDPROC)DefDlgProc;
	_wcex.cbWndExtra  = DLGWINDOWEXTRA;
	return *this;
}

CWindowClass& CWindowClass::WithIcon(int icon)
{
	_icon = icon;
	return *this;
}

CWindowClass& CWindowClass::WithSmallIcon(int smallIcon)
{
	_smallIcon = smallIcon;
	return *this;
}

CWindowClass& CWindowClass::WithMenu(int menu)
{
	_menu = menu;
	return *this;
}

CWindowClass& CWindowClass::WithClassName(LPCTSTR className)
{
	_className = className;
	return *this;
}

void CWindowClass::Register(const CInstance& instance)
{
	HINSTANCE hInstance = instance.GetHandle();
	_wcex.hInstance     = hInstance;
	_wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(_icon));
	_wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	_wcex.lpszMenuName  = MAKEINTRESOURCE(_menu);
	_wcex.lpszClassName = _className;
	_wcex.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(_smallIcon));
	RegisterClassEx(&_wcex);
}

} // namespace WinObj
