// Dialog.h: interface for the CDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOG_H__A4E773BE_896D_4FA3_AA36_C1EB26575BCA__INCLUDED_)
#define AFX_DIALOG_H__A4E773BE_896D_4FA3_AA36_C1EB26575BCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Instance.h"
#include "Wnd.h"

namespace WinObj
{
/// Encapsulates a dialog window.
class CDialog : public CWnd
{
	const CInstance& _instance;

public:
	CDialog(const CInstance& instance);
	virtual ~CDialog();
	bool Create(int dialogResource);
	INT_PTR Modal(int dialogResource);

	/// Message handler for the dialog.
	virtual LRESULT OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

	/// Gets the application instance.
	const CInstance& GetInstance() const;

	bool EndDialog(INT_PTR result = 0);
};

} // namespace WinObj
#endif // !defined(AFX_DIALOG_H__A4E773BE_896D_4FA3_AA36_C1EB26575BCA__INCLUDED_)
