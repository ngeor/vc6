#if !defined(WINOBJ_STR_H_INCLUDED_)
#define WINOBJ_STR_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if UNICODE
typedef std::wstring str;
#else
typedef std::string str;
#endif

#endif // !defined(WINOBJ_STR_H_INCLUDED_)
