// ChangeFileTimeHandler.cpp : Implementation of CChangeFileTimeHandler
#include "StdAfx.h"
#if _MSC_VER > 1200
#include "ChangeFileTimePS_h.h"
#else
#include "ChangeFileTimePS.h"
#endif
#include "ChangeFileTimeHandler.h"
#include "GlobalWinObjInstance.h"
#include "SimplePage.h"

bool IsDirectory(LPCTSTR filename)
{
	return (GetFileAttributes(filename) & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;
}

HRESULT CChangeFileTimeHandler::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT lpdobj, HKEY hkeyProgID)
{
	FORMATETC etc;
	STGMEDIUM stg;
	TCHAR filename[MAX_PATH];

	etc.cfFormat = CF_HDROP;
	etc.ptd      = NULL;
	etc.dwAspect = DVASPECT_CONTENT;
	etc.lindex   = -1;            // all of the data
	etc.tymed    = TYMED_HGLOBAL; // HGLOBAL

	if (SUCCEEDED(lpdobj->GetData(&etc, &stg)))
	{
		HDROP hDrop   = (HDROP)stg.hGlobal;
		int fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
		for (int i = 0; i < fileCount; i++)
		{
			DragQueryFile(hDrop, i, filename, MAX_PATH);
			hasFolders = hasFolders || IsDirectory(filename);
			fileList.push_back(filename);
		}
		ReleaseStgMedium(&stg);
		return S_OK;
	}

	return E_FAIL;
}

HRESULT CChangeFileTimeHandler::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
	// init common controls
	InitCommonControls();
	// init extended common controls
	INITCOMMONCONTROLSEX ic;
	ic.dwICC  = ICC_DATE_CLASSES;
	ic.dwSize = sizeof(ic);
	InitCommonControlsEx(&ic);
	// create simple page instance, will be de-allocated by the CPropSheet callback
	CSimplePage* simplePage = new CSimplePage(fileList, hasFolders);
	// create the HPROPSHEETPAGE handle
	HPROPSHEETPAGE hPropSheetPage = simplePage->CreatePropertyPage(_WinObjInstance, IDD_SIMPLE_PAGE, IDI_ICON1);
	// register it with the Windows properties window
	lpfnAddPage(hPropSheetPage, lParam);
	return NOERROR;
}
