// DialogMessageLoop.h: interface for the CDialogMessageLoop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGMESSAGELOOP_H__A83B5322_4C48_4889_ADD2_E1E73028E3D3__INCLUDED_)
#define AFX_DIALOGMESSAGELOOP_H__A83B5322_4C48_4889_ADD2_E1E73028E3D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dialog.h"
#include "MessageLoop.h"

namespace WinObj
{
/// A message loop for an app that has a dialog as its main window.
class CDialogMessageLoop : public CMessageLoop
{
	CDialog& _dialog;

public:
	CDialogMessageLoop(CDialog& dialog);
	virtual ~CDialogMessageLoop();

protected:
	virtual bool IsMessageProcessed(LPMSG msg);
};
} // namespace WinObj

#endif // !defined(AFX_DIALOGMESSAGELOOP_H__A83B5322_4C48_4889_ADD2_E1E73028E3D3__INCLUDED_)
