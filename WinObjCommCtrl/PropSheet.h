// PropSheet.h: interface for the CPropSheet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPSHEET_H__B2BA2B5B_5C47_4CD5_B26A_C60D42954223__INCLUDED_)
#define AFX_PROPSHEET_H__B2BA2B5B_5C47_4CD5_B26A_C60D42954223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\WinObj\Dialog.h"
#include "..\WinObj\Instance.h"

namespace WinObj
{
class CPropSheet : public CDialog
{
public:
	CPropSheet();
	virtual ~CPropSheet();
	void NotifyParentChanged();
	HPROPSHEETPAGE CreatePropertyPage(const CInstance& instance, int dialogResource, int iconResource);
};

} // namespace WinObj

#endif // !defined(AFX_PROPSHEET_H__B2BA2B5B_5C47_4CD5_B26A_C60D42954223__INCLUDED_)
