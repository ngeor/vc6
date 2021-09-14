// RecurseModeDialog.cpp: implementation of the CRecurseModeDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "RecurseModeDialog.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RecurseModeDialog::RecurseModeDialog()
{
}

LRESULT RecurseModeDialog::OnInitDialog(LPARAM lParam)
{
	CheckRadioButton(IDC_APPLY_SIMPLE, IDC_APPLY_RECURSE, IDC_APPLY_SIMPLE);
	CheckDlgButton(IDC_FILES, BST_CHECKED);
	CheckDlgButton(IDC_FOLDERS, BST_CHECKED);
	return 1;
}

LRESULT RecurseModeDialog::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		EndDialog(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			if (IsDlgButtonChecked(IDC_APPLY_SIMPLE) == BST_CHECKED)
			{
				EndDialog(RECURSE_SIMPLE);
			}
			else
			{
				int ret = 0;
				if (IsDlgButtonChecked(IDC_FILES) == BST_CHECKED)
				{
					ret |= RECURSE_FILES;
				}
				if (IsDlgButtonChecked(IDC_FOLDERS) == BST_CHECKED)
				{
					ret |= RECURSE_FOLDERS;
				}
				if (IsDlgButtonChecked(IDC_NOT_FOLDER) == BST_CHECKED)
				{
					ret |= RECURSE_SKIP_ROOT;
				}
				GetDlgItemText(IDC_FILTER, filter, MAX_PATH);
				EndDialog(ret);
			}
			break;
		case IDCANCEL:
			EndDialog(0);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return CDialog::OnMessage(msg, wParam, lParam);
}
