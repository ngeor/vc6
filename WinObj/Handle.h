// Handle.h: interface for the CHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANDLE_H__E5B67A2B_FDCC_42AA_BA64_EA9D2CB8A5A5__INCLUDED_)
#define AFX_HANDLE_H__E5B67A2B_FDCC_42AA_BA64_EA9D2CB8A5A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace WinObj
{
template <typename T> class CHandle
{
	T _handle;

public:
	CHandle(T handle) : _handle(handle)
	{
	}

	virtual ~CHandle()
	{
	}

	// TODO remove or at least reduce visibility
	T GetHandle() const
	{
		return _handle;
	}
};
} // namespace WinObj

#endif // !defined(AFX_HANDLE_H__E5B67A2B_FDCC_42AA_BA64_EA9D2CB8A5A5__INCLUDED_)
