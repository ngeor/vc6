#if !defined(_STRING_LIST_H_INCLUDED_)
#define _STRING_LIST_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

#ifdef UNICODE
typedef std::vector<std::wstring> string_list;
#else
typedef std::vector<std::string> string_list;
#endif

#endif
