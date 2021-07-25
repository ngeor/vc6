// Dialog.cpp: implementation of the CDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dialog.h"
namespace WinObj
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialog::CDialog(const CInstance& instance) : CWnd(NULL), _instance(instance)
{
}

CDialog::~CDialog()
{
}

const CInstance& CDialog::GetInstance() const
{
	return _instance;
}

LRESULT CALLBACK __InternalDialogBootstrapProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CDialog* dialog;
	switch (message)
	{
	case WM_INITDIALOG:
		if (lParam)
		{
#if _MSC_VER > 1200
			SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
#else
			SetWindowLong(hWnd, GWL_USERDATA, lParam);
#endif
			dialog = (CDialog*)lParam;
			dialog->SetHandle(hWnd);
			return dialog->OnMessage(message, wParam, lParam);
		}
		return 1;
	default:
#if _MSC_VER > 1200
		dialog = (CDialog*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
#else
		dialog = (CDialog*)GetWindowLong(hWnd, GWL_USERDATA);
#endif
		if (dialog)
		{
			return dialog->OnMessage(message, wParam, lParam);
		}

		return 0;
	}
}

bool CDialog::Create(int dialogResource)
{
	HWND hWnd = ::CreateDialogParam(GetInstance().GetHandle(), MAKEINTRESOURCE(dialogResource), 0,
	                                (DLGPROC)__InternalDialogBootstrapProc, (LPARAM)this);
	return hWnd != NULL;
}

INT_PTR CDialog::Modal(int dialogResource)
{
	return ::DialogBoxParam(GetInstance().GetHandle(), MAKEINTRESOURCE(dialogResource), 0,
	                        (DLGPROC)__InternalDialogBootstrapProc, (LPARAM)this);
}

LRESULT CDialog::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

bool CDialog::EndDialog(INT_PTR result)
{
	return ::EndDialog(GetHandle(), result) != 0;
}

} // namespace WinObj
