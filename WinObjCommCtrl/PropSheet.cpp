// PropSheet.cpp: implementation of the CPropSheet class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include <tchar.h>
#include "PropSheet.h"

namespace WinObj
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPropSheet::CPropSheet()
{
}

CPropSheet::~CPropSheet()
{
}

UINT CALLBACK PropPageCallbackProc(HWND hwnd, UINT message, LPPROPSHEETPAGE page)
{
	switch (message)
	{
	case PSPCB_RELEASE:
		CPropSheet* propSheet = (CPropSheet*)page->lParam;
		delete propSheet;
		break;
	}
	return 1;
}

LRESULT OnInitDialog(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPPROPSHEETPAGE page = (LPPROPSHEETPAGE)lParam;
	CPropSheet* dialog   = (CPropSheet*)page->lParam;
#if _MSC_VER > 1200
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LPARAM)dialog);
#else
	SetWindowLong(hWnd, GWL_USERDATA, (LPARAM)dialog);
#endif
	dialog->SetHandle(hWnd);
	return dialog->OnMessage(message, wParam, lParam);
}

LRESULT CALLBACK InternalPropSheetBootstrapProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CPropSheet* dialog;
	switch (message)
	{
	case WM_INITDIALOG:
		return OnInitDialog(hWnd, message, wParam, lParam);
		break;
	default:
#if _MSC_VER > 1200
		dialog = (CPropSheet*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
#else
		dialog = (CPropSheet*)GetWindowLong(hWnd, GWL_USERDATA);
#endif
		if (dialog != NULL)
		{
			return dialog->OnMessage(message, wParam, lParam);
		}

		break;
	}

	return 0;
}

HPROPSHEETPAGE CPropSheet::CreatePropertyPage(const CInstance& instance, int dialogResource, int iconResource)
{
	PROPSHEETPAGE p;
	memset(&p, 0, sizeof(p));
	p.dwSize      = sizeof(p);
	p.dwFlags     = PSP_USEICONID | PSP_USECALLBACK;
	p.hInstance   = instance.GetHandle();
	p.pszTemplate = MAKEINTRESOURCE(dialogResource);
	p.pfnDlgProc  = (DLGPROC)(InternalPropSheetBootstrapProc);
	p.lParam      = (LPARAM)this;
	p.pszIcon     = MAKEINTRESOURCE(iconResource);
	p.pfnCallback = PropPageCallbackProc;
	return CreatePropertySheetPage(&p);
}

void CPropSheet::NotifyParentChanged()
{
	HWND hWnd = GetHandle();
	::SendMessage(GetParent(hWnd), PSM_CHANGED, (WPARAM)hWnd, 0);
}
} // namespace WinObj
