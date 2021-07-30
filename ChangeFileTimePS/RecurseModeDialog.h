// RecurseModeDialog.h: interface for the CRecurseModeDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECURSEMODEDIALOG_H__F95AB691_F21E_4E8E_BB70_9FE3268C4383__INCLUDED_)
#define AFX_RECURSEMODEDIALOG_H__F95AB691_F21E_4E8E_BB70_9FE3268C4383__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\WinObj\WinObj.h"

#define RECURSE_SIMPLE    1
#define RECURSE_FILES     2
#define RECURSE_FOLDERS   4
#define RECURSE_SKIP_ROOT 8

class RecurseModeDialog : public WinObj::CDialog
{
public:
	TCHAR filter[MAX_PATH];

	RecurseModeDialog();
	virtual LRESULT OnMessage(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	virtual LRESULT OnInitDialog(LPARAM lParam);
};

#endif // !defined(AFX_RECURSEMODEDIALOG_H__F95AB691_F21E_4E8E_BB70_9FE3268C4383__INCLUDED_)
