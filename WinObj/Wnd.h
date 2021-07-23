// Wnd.h: interface for the CWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WND_H__93530528_8038_459B_9C73_D156D73F67BA__INCLUDED_)
#define AFX_WND_H__93530528_8038_459B_9C73_D156D73F67BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Handle.h"

namespace WinObj
{
/// Encapsulates a HWND handle.
class CWnd : public CHandle<HWND>
{
public:
	CWnd(HWND hWnd);
	virtual ~CWnd();

	void Show();

	bool IsDialogMessage(LPMSG msg);

	bool MoveDlgItem(int dlgItem, int x, int y, int width, int height, bool repaint = true);

	/// Gets the client bounds of the window.
	bool GetClientRect(LPRECT rect);

	/// Marks the given rect of the window for repaint.
	bool InvalidateRect(LPRECT rect = NULL, bool repaint = true);

	bool DestroyWindow();

	HDC BeginPaint(LPPAINTSTRUCT ps);

	bool EndPaint(LPPAINTSTRUCT ps);

	UINT GetDlgItemText(int id, LPTSTR buffer, int maxCharacters);

	UINT GetDlgItemInt(int id, bool *translated, bool bSigned);

	int GetDlgItemTextLength(int id);

	LRESULT SendDlgItemMessage(int id, UINT msg, WPARAM wParam, LPARAM lParam);
};
} // namespace WinObj
#endif // !defined(AFX_WND_H__93530528_8038_459B_9C73_D156D73F67BA__INCLUDED_)
