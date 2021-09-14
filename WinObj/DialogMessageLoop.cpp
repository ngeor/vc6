// DialogMessageLoop.cpp: implementation of the CDialogMessageLoop class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "DialogMessageLoop.h"

namespace WinObj
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialogMessageLoop::CDialogMessageLoop(CDialog& dialog) : _dialog(dialog)
{
}

CDialogMessageLoop::~CDialogMessageLoop()
{
}

bool CDialogMessageLoop::IsMessageProcessed(LPMSG msg)
{
	return _dialog.IsDialogMessage(msg);
}

} // namespace WinObj