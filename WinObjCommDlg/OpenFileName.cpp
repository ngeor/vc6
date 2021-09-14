// OpenFileName.cpp: implementation of the COpenFileName class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "OpenFileName.h"

namespace WinObj
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenFileName::COpenFileName(const CInstance& app, const CWnd& owner) : _app(app)
{
	memset(&_of, 0, sizeof(OPENFILENAME));
	_of.lStructSize = sizeof(OPENFILENAME);
	_of.hwndOwner   = owner.GetHandle();
	_of.hInstance   = app.GetHandle();
	_of.lpstrFile   = (LPTSTR)calloc(MAX_PATH, sizeof(TCHAR));
	_of.nMaxFile    = MAX_PATH;
}

COpenFileName::COpenFileName(const COpenFileName& other) : _app(other._app), _of(other._of)
{
}

COpenFileName::~COpenFileName()
{
	free(_of.lpstrFile);
}

// filter needs to be terminated with double null
LPTSTR ReplaceFilter(const str& filter)
{
	int len          = filter.length();
	LPTSTR newBuffer = (LPTSTR)calloc(len + 2, sizeof(TCHAR));
#if _MSC_VER > 1200
	_tcsncpy_s(newBuffer, len + 1, filter.c_str(), len);
#else
	_tcsncpy(newBuffer, filter.c_str(), len);
#endif

	LPTSTR p = newBuffer;
	while (*p != 0)
	{
		if (*p == '|')
		{
			*p = '\0';
		}
		p++;
	}
	return newBuffer;
}

void COpenFileName::BeforeDialog()
{
	if (_filter.length() > 0)
	{
		_of.lpstrFilter = ReplaceFilter(_filter);
	}
}

bool COpenFileName::AfterDialog(bool result)
{
	if (_filter.length() > 0)
	{
		free((void*)_of.lpstrFilter);
		_of.lpstrFilter = NULL;
	}
	return result;
}

bool COpenFileName::GetOpenFileName()
{
	BeforeDialog();
	return AfterDialog(::GetOpenFileName(&_of) != 0);
}

bool COpenFileName::GetSaveFileName()
{
	BeforeDialog();
	return AfterDialog(::GetSaveFileName(&_of) != 0);
}

COpenFileName& COpenFileName::WithFilter(int stringResource)
{
	_filter = _app.LoadStr(stringResource);
	return *this;
}

COpenFileName& COpenFileName::WithFilterIndex(int filterIndex)
{
	_of.nFilterIndex = filterIndex;
	return *this;
}

COpenFileName& COpenFileName::WithFlags(DWORD flags)
{
	_of.Flags = flags;
	return *this;
}

COpenFileName& COpenFileName::WithDefaultExtension(LPCTSTR defaultExtension)
{
	_of.lpstrDefExt = defaultExtension;
	return *this;
}

LPCTSTR COpenFileName::GetFile() const
{
	return _of.lpstrFile;
}

int COpenFileName::GetFileOffset() const
{
	return _of.nFileOffset;
}

} // namespace WinObj
