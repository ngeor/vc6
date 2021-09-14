#if !defined(ABOUT_H_INCLUDED)
#define ABOUT_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\WinObj\Dialog.h"

class AboutDialog : public WinObj::CDialog
{
public:
	AboutDialog();
	virtual ~AboutDialog();
	virtual LRESULT OnMessage(UINT message, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(ABOUT_H_INCLUDED)
