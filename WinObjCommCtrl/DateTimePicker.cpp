// DateTimePicker.cpp: implementation of the CDateTimePicker class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "DateTimePicker.h"

namespace WinObj
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDateTimePicker::CDateTimePicker(const CWnd& parent, int id) : CWnd(::GetDlgItem(parent.GetHandle(), id))
{
}

CDateTimePicker::~CDateTimePicker()
{
}

UINT CDateTimePicker::GetSystemTime(LPSYSTEMTIME systemTime)
{
	return DateTime_GetSystemtime(GetHandle(), systemTime);
}

bool CDateTimePicker::SetSystemTime(int flags, LPSYSTEMTIME systemTime)
{
	return DateTime_SetSystemtime(GetHandle(), flags, systemTime) != 0;
}
} // namespace WinObj