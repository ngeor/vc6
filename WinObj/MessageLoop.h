// MessageLoop.h: interface for the CMessageLoop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGELOOP_H__529FD7E7_4F66_43BD_9DA8_257660996E24__INCLUDED_)
#define AFX_MESSAGELOOP_H__529FD7E7_4F66_43BD_9DA8_257660996E24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace WinObj
{
/// Provides the message loop for an application.
class CMessageLoop
{
public:
	CMessageLoop();
	virtual ~CMessageLoop();
	WPARAM Run();

protected:
	/// Checks if the given message is already processed.
	/// If this method returns true, the message will not be dispatched.
	virtual bool IsMessageProcessed(LPMSG msg);
};
} // namespace WinObj

#endif // !defined(AFX_MESSAGELOOP_H__529FD7E7_4F66_43BD_9DA8_257660996E24__INCLUDED_)
