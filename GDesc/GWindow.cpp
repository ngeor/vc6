// GWindow.cpp: implementation of the GWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "GWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GWindow::GWindow()
{
	FCaption = NULL;
	FState   = 0;
}

GWindow::~GWindow()
{
	if (FCaption != NULL)
	{
		free(FCaption);
	}
}

void GWindow::GetWindowRect(LPRECT lpRect) const
{
	lpRect->left   = FLeft;
	lpRect->top    = FTop;
	lpRect->right  = FLeft + FWidth;
	lpRect->bottom = FTop + FHeight;
}

void GWindow::Paint(GAbstractCanvas* canvas)
{
	int cx;
	int cy;
	canvas->Rectangle(FLeft, FTop, FLeft + FWidth, FTop + FHeight);
	canvas->SetTextColor(0x00FFFFFF);
	canvas->SetBgColor((FState & WS_ACTIVE) != 0 ? 0x00C00000 : 0x00808080);
	canvas->GetTextExtent(_T("Mg"), 2, &cx, &cy);
	canvas->Rectangle(FLeft, FTop, FLeft + FWidth, FTop + cy + 2);
	canvas->SetBgColor(0x00C0C0C0);
	canvas->Rectangle(FLeft + FWidth - cy, FTop + 1, FLeft + FWidth - 1, FTop + cy - 1);
	canvas->SetTextTransparent(TRUE);
	if (FCaption != NULL)
	{
		canvas->TextOut(FCaption, -1, FLeft + 2, FTop + 2);
	}
}

LPTSTR GWindow::GetCaption()
{
	return FCaption;
}

void GWindow::SetCaption(LPCTSTR szText)
{
	if (FCaption != NULL)
	{
		free(FCaption);
	}

	int len = szText != NULL ? _tcslen(szText) : 0;
	if (len > 0)
	{
		FCaption = (LPTSTR)malloc((len + 1) * sizeof(TCHAR));
#if _MSC_VER > 1200
		_tcscpy_s(FCaption, len + 1, szText);
#else
		_tcscpy(FCaption, szText);
#endif
	}
	else
	{
		FCaption = NULL;
	}
}

void GWindow::SetBounds(int left, int top, int width, int height)
{
	FLeft   = left;
	FTop    = top;
	FWidth  = width;
	FHeight = height;
}

long GWindow::GetWindowState() const
{
	return FState;
}

void GWindow::SetWindowState(long newState)
{
	if (newState != FState)
	{
		FState = newState;
	}
}

LONG GWindow::HitTest(int x, int y) const
{
	return static_cast<LONG>((x >= FLeft) && (x <= FLeft + FWidth) && (y >= FTop) && (y <= FTop + FHeight));
}
