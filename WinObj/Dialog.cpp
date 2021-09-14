// Dialog.cpp: implementation of the CDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Dialog.h"
namespace WinObj
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialog::CDialog() : CWnd(NULL), _instance(NULL)
{
}

CDialog::~CDialog()
{

	delete _instance;
}

const CInstance* CDialog::GetInstance()
{
	if (_instance == NULL)
	{
		HINSTANCE hInstance;
#if _MSC_VER > 1200
		hInstance = (HINSTANCE)GetWindowLongPtr(GetHandle(), GWLP_HINSTANCE);
#else
		hInstance = (HINSTANCE)GetWindowLong(GetHandle(), GWL_HINSTANCE);
#endif
		_instance = new CInstance(hInstance);
	}

	return _instance;
}

LRESULT CALLBACK InternalDialogBootstrapProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CDialog* dialog;
	switch (message)
	{
	case WM_INITDIALOG:
		if (lParam != 0)
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
		if (dialog != NULL)
		{
			return dialog->OnMessage(message, wParam, lParam);
		}

		return 0;
	}
}

bool CDialog::Create(const CInstance& instance, int dialogResource)
{
	HWND hWnd = ::CreateDialogParam(instance.GetHandle(), MAKEINTRESOURCE(dialogResource), 0,
	                                (DLGPROC)InternalDialogBootstrapProc, (LPARAM)this);
	return hWnd != NULL;
}

INT_PTR CDialog::Modal(const CInstance& instance, const CWnd& parent, int dialogResource)
{
	return ::DialogBoxParam(instance.GetHandle(), MAKEINTRESOURCE(dialogResource), parent.GetHandle(),
	                        (DLGPROC)InternalDialogBootstrapProc, (LPARAM)this);
}

INT_PTR CDialog::Modal(const CInstance& instance, int dialogResource)
{
	return ::DialogBoxParam(instance.GetHandle(), MAKEINTRESOURCE(dialogResource), 0,
	                        (DLGPROC)InternalDialogBootstrapProc, (LPARAM)this);
}

LRESULT CDialog::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return OnInitDialog(lParam);
	default:
		return 0;
	}
}

LRESULT CDialog::OnInitDialog(LPARAM lParam)
{
	return 1;
}

bool CDialog::EndDialog(INT_PTR result)
{
	return ::EndDialog(GetHandle(), result) != 0;
}

void CDialog::SetDialogMessageResult(LPARAM result)
{
#if _MSC_VER > 1200
	SetWindowLongPtr(GetHandle(), DWLP_MSGRESULT, result);
#else
	SetWindowLong(GetHandle(), DWL_MSGRESULT, result);
#endif
}

} // namespace WinObj
