// DateTimePicker.h: interface for the CDateTimePicker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATETIMEPICKER_H__601048B3_3BDB_4EA1_9A82_8C5A4E03479B__INCLUDED_)
#define AFX_DATETIMEPICKER_H__601048B3_3BDB_4EA1_9A82_8C5A4E03479B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\WinObj\Wnd.h"

namespace WinObj
{
class CDateTimePicker : public CWnd
{
public:
	CDateTimePicker(const CWnd& parent, int id);
	virtual ~CDateTimePicker();
	UINT GetSystemTime(LPSYSTEMTIME systemTime);
	bool SetSystemTime(int flags, LPSYSTEMTIME systemTime);
};
} // namespace WinObj

#endif // !defined(AFX_DATETIMEPICKER_H__601048B3_3BDB_4EA1_9A82_8C5A4E03479B__INCLUDED_)
