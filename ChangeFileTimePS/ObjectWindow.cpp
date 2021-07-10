// ObjectWindow.cpp: implementation of the CObjectWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ObjectWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObjectWindow::CObjectWindow()
{
}

CObjectWindow::~CObjectWindow()
{
}

void CObjectWindow::attatchToDialog(HWND hWnd)
{
	setUserLong(hWnd, (LONG)this);
}

void CObjectWindow::detachFromDialog(HWND hWnd)
{
	setUserLong(hWnd, 0);
}

void CObjectWindow::setUserLong(HWND hWnd, LONG userData)
{
#if _MSC_VER > 1200
	SetWindowLongPtr(hWnd, DWLP_USER, userData);
#else
	SetWindowLong(hWnd, DWL_USER, userData);
#endif
}

CObjectWindow *CObjectWindow::objectFromDialog(HWND hWnd)
{
#if _MSC_VER > 1200
	return (CObjectWindow *)GetWindowLongPtr(hWnd, DWLP_USER);
#else
	return (CObjectWindow *)GetWindowLong(hWnd, DWL_USER);
#endif
}

LRESULT CObjectWindow::dialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CObjectWindow *obj = objectFromDialog(hWnd);
	if (msg == WM_CREATE)
	{
		obj = (CObjectWindow *)lParam;
		obj->attatchToDialog(hWnd);
		obj->hWnd = hWnd;
	}
	if (obj != NULL)
		return obj->Handler(msg, wParam, lParam);
	return 0;
}

LRESULT CObjectWindow::Handler(UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
