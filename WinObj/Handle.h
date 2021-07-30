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
	CHandle() : _handle(NULL)
	{
	}

	CHandle(T handle) : _handle(handle)
	{
	}

	virtual ~CHandle()
	{
	}

	T GetHandle() const
	{
		return _handle;
	}

	void SetHandle(T handle)
	{
		assert(_handle == NULL);
		assert(handle);
		_handle = handle;
	}

	T Detach()
	{
		T currentValue = _handle;
		_handle        = NULL;
		return currentValue;
	}
};
} // namespace WinObj

#endif // !defined(AFX_HANDLE_H__E5B67A2B_FDCC_42AA_BA64_EA9D2CB8A5A5__INCLUDED_)
