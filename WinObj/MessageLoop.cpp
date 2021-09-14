// MessageLoop.cpp: implementation of the CMessageLoop class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "MessageLoop.h"

namespace WinObj
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageLoop::CMessageLoop()
{
}

CMessageLoop::~CMessageLoop()
{
}

WPARAM CMessageLoop::Run()
{
	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else if (!IsMessageProcessed(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// Return the exit code to the system.

	return msg.wParam;
}

bool CMessageLoop::IsMessageProcessed(LPMSG msg)
{
	return false;
}

} // namespace WinObj
