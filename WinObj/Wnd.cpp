// Wnd.cpp: implementation of the CWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wnd.h"

namespace WinObj
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWnd::CWnd(HWND hWnd) : CHandle<HWND>(hWnd)
{
}

CWnd::~CWnd()
{
}

void CWnd::Show()
{
	::ShowWindow(GetHandle(), SW_SHOWNORMAL);
}

bool CWnd::IsDialogMessage(LPMSG msg)
{
	return ::IsDialogMessage(GetHandle(), msg) != 0;
}

bool CWnd::MoveDlgItem(int dlgItem, int x, int y, int width, int height, bool repaint)
{
	HWND hChildWnd = ::GetDlgItem(GetHandle(), dlgItem);
	if (hChildWnd)
	{
		return ::MoveWindow(hChildWnd, x, y, width, height, repaint) != 0;
	}
	else
	{
		return false;
	}
}

bool CWnd::GetClientRect(LPRECT rect)
{
	return ::GetClientRect(GetHandle(), rect);
}

bool CWnd::InvalidateRect(LPRECT rect, bool repaint)
{
	return ::InvalidateRect(GetHandle(), rect, repaint);
}

bool CWnd::DestroyWindow()
{
	return ::DestroyWindow(GetHandle());
}

HDC CWnd::BeginPaint(LPPAINTSTRUCT ps)
{
	return ::BeginPaint(GetHandle(), ps);
}

bool CWnd::EndPaint(LPPAINTSTRUCT ps)
{
	return ::EndPaint(GetHandle(), ps);
}

UINT CWnd::GetDlgItemText(int id, LPTSTR buffer, int maxCharacters)
{
	return ::GetDlgItemText(GetHandle(), id, buffer, maxCharacters);
}

UINT CWnd::GetDlgItemInt(int id, bool *translated, bool bSigned)
{
	BOOL bTranslated;
	UINT result = ::GetDlgItemInt(GetHandle(), id, &bTranslated, bSigned);
	*translated = bTranslated != 0;
	return result;
}

int CWnd::GetDlgItemTextLength(int id)
{
	HWND hChild = ::GetDlgItem(GetHandle(), id);
	if (hChild != NULL)
	{
		return ::GetWindowTextLength(hChild);
	}
	else
	{
		return 0;
	}
}

LRESULT CWnd::SendDlgItemMessage(int id, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ::SendDlgItemMessage(GetHandle(), id, msg, wParam, lParam);
}

} // namespace WinObj
