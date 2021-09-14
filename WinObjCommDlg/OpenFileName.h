// OpenFileName.h: interface for the COpenFileName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENFILENAME_H__7C28D4FE_8876_4720_90B2_3308DF99D5F8__INCLUDED_)
#define AFX_OPENFILENAME_H__7C28D4FE_8876_4720_90B2_3308DF99D5F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\WinObj\Instance.h"
#include "..\WinObj\Wnd.h"
#include "..\WinObj\str.h"

namespace WinObj
{
class COpenFileName
{
	const CInstance& _app;
	OPENFILENAME _of;
	str _filter;
	void BeforeDialog();
	bool AfterDialog(bool result);
	COpenFileName(const COpenFileName& other);

public:
	COpenFileName(const CInstance& app, const CWnd& owner);
	virtual ~COpenFileName();
	bool GetOpenFileName();
	bool GetSaveFileName();

	COpenFileName& WithFilter(int stringResource);
	COpenFileName& WithFlags(DWORD flags);
	COpenFileName& WithDefaultExtension(LPCTSTR defaultExtension);
	COpenFileName& WithFilterIndex(int index);

	LPCTSTR GetFile() const;
	int GetFileOffset() const;
};
} // namespace WinObj
#endif // !defined(AFX_OPENFILENAME_H__7C28D4FE_8876_4720_90B2_3308DF99D5F8__INCLUDED_)
