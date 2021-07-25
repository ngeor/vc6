// WindowClass.h: interface for the CWindowClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWCLASS_H__7AD31414_B49C_4DD4_A32D_CE2DBA43D334__INCLUDED_)
#define AFX_WINDOWCLASS_H__7AD31414_B49C_4DD4_A32D_CE2DBA43D334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Instance.h"

namespace WinObj
{
/// Builder object for a window class (WNDCLASSEX).
class CWindowClass
{
	WNDCLASSEX _wcex;
	int _icon;
	int _smallIcon;
	int _menu;
	LPCTSTR _className;
	CWindowClass(const CWindowClass& other);

public:
	CWindowClass();
	virtual ~CWindowClass();
	void Register(const CInstance& instance);
	CWindowClass& Dialog();
	CWindowClass& WithIcon(int icon);
	CWindowClass& WithSmallIcon(int smallIcon);
	CWindowClass& WithMenu(int menu);
	CWindowClass& WithClassName(LPCTSTR className);
};
} // namespace WinObj
#endif // !defined(AFX_WINDOWCLASS_H__7AD31414_B49C_4DD4_A32D_CE2DBA43D334__INCLUDED_)
