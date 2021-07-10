// ObjectWindow.h: interface for the CObjectWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTWINDOW_H__66D201E0_A3FC_4F3C_A0A5_8ED2973D98A6__INCLUDED_)
#define AFX_OBJECTWINDOW_H__66D201E0_A3FC_4F3C_A0A5_8ED2973D98A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObjectWindow
{
public:
	HWND hWnd;

	CObjectWindow();
	virtual ~CObjectWindow();

	static LRESULT CALLBACK dialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static CObjectWindow *objectFromDialog(HWND hWnd);
	static void detachFromDialog(HWND hWnd);

	virtual LRESULT Handler(UINT msg, WPARAM wParam, LPARAM lParam);

	void attatchToDialog(HWND hWnd);

private:
	static void setUserLong(HWND hWnd, LONG userData);
};

#endif // !defined(AFX_OBJECTWINDOW_H__66D201E0_A3FC_4F3C_A0A5_8ED2973D98A6__INCLUDED_)
