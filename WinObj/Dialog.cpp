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

CDialog::CDialog(const CInstance& instance, HWND hWnd) : CWnd(hWnd), _instance(instance)
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

LRESULT CDialog::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

} // namespace WinObj
