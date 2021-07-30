// ChangeFileTimeHandler.h : Declaration of the CChangeFileTimeHandler

#ifndef __CHANGEFILETIMEHANDLER_H_
#define __CHANGEFILETIMEHANDLER_H_

#include "StringList.h"
#include "resource.h" // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChangeFileTimeHandler
class ATL_NO_VTABLE CChangeFileTimeHandler
	: public CComObjectRootEx<CComSingleThreadModel>,
	  public CComCoClass<CChangeFileTimeHandler, &CLSID_ChangeFileTimeHandler>,
	  public IDispatchImpl<IChangeFileTimeHandler, &IID_IChangeFileTimeHandler, &LIBID_CHANGEFILETIMEPSLib>,
	  public IShellExtInit,
	  public IShellPropSheetExt
{
public:
	CChangeFileTimeHandler()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CHANGEFILETIMEHANDLER)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CChangeFileTimeHandler)
	COM_INTERFACE_ENTRY(IChangeFileTimeHandler)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IShellPropSheetExt)
	END_COM_MAP()

private:
	string_list fileList;
	bool hasFolders;

	// IChangeFileTimeHandler
public:
	// IShellExtInit

	/// Initialize is called first. The files/folders the user has selected are accessible
	/// through the lpdobj parameter.
	///
	/// See https://docs.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ishellextinit-initialize
	STDMETHOD(Initialize)(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

	// IShellPropSheetExt

	/// Called after Initialize in order to add property sheet pages to the properties dialog.
	/// Note that the method exits without waiting for the properties dialog to exit
	/// and it is destroyed.
	///
	/// See
	/// https://docs.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ishellpropsheetext-addpages
	STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE, LPARAM);
	STDMETHOD(ReplacePage)(UINT, LPFNADDPROPSHEETPAGE, LPARAM)
	{
		return E_NOTIMPL;
	}
};

#endif //__CHANGEFILETIMEHANDLER_H_
