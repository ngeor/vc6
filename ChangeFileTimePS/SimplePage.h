// SimplePage.h: interface for the SimplePage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEPAGE_H__DDC5DD14_F203_440C_8BF0_3B6998093395__INCLUDED_)
#define AFX_SIMPLEPAGE_H__DDC5DD14_F203_440C_8BF0_3B6998093395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\WinObjCommCtrl\DateTimePicker.h"
#include "..\WinObjCommCtrl\PropSheet.h"
#include "..\WinObj\Dialog.h"
#include "..\WinObj\Instance.h"
#include "..\WinObj\str.h"
#include "StringList.h"
#include "resource.h"

//#define MULTIPLE_FILES list.getFileCount() > 1

#define BUTTON_HANDLER(id, proc)                                                                                       \
	if (LOWORD(wParam) == id && HIWORD(wParam) == BN_CLICKED)                                                          \
	{                                                                                                                  \
		proc();                                                                                                        \
		return 0;                                                                                                      \
	}
#define BUTTON_HANDLER_RANGE(id_min, id_max, proc)                                                                     \
	if (LOWORD(wParam) >= id_min && LOWORD(wParam) <= id_max && HIWORD(wParam) == BN_CLICKED)                          \
	{                                                                                                                  \
		proc(LOWORD(wParam));                                                                                          \
		return 0;                                                                                                      \
	}

class CSimplePage : public WinObj::CPropSheet
{
private:
	void recurseThat(const str& szDir);
	int RecurseMode();
	string_list mylist;
	string_list templist;
	bool hasfolders;
	int recurseMode;
	TCHAR recurseFilter[MAX_PATH];
	UINT bInitArchive, bInitReadOnly, bInitHidden, bInitSystem;
	void initTempList();
	void OnAttributesClick();
	void OnTimesClick();
	void OnOneTimeClick();
	static void applyAttribute(LPDWORD attrs, UINT checkboxState, DWORD fileAttribute);
	static void prepareAttribute(LPDWORD orMask, LPDWORD andMask, UINT bFlag, UINT bInitFlag, DWORD fileAttribute);
	void prepareMasks(LPDWORD orMask, LPDWORD andMask, UINT bArchive, UINT bReadOnly, UINT bHidden, UINT bSystem);
	static void MySetFileAttrs(const str& lpFileName, DWORD orMask, DWORD andMask);
	BOOL GetSomeFileTime(int ctlIndex, LPFILETIME ft);
	static void MySetFileTime(const str& lpFileName, LPFILETIME f1, LPFILETIME f2, LPFILETIME f3);
	static void MyGetFileTime(const str& lpFileName, SYSTEMTIME(s)[3]);
	void SetSystemTime(int index, LPSYSTEMTIME systemTime);
	void InitDateTimeCtls(const str& lpFileName);
	void OnNowClick(UINT id);
	bool OnOK();
	void Changed();
	void Nag();
	static void checkFileAttribute(DWORD attrs, DWORD attrBit, UINT* value, bool firstTime);
	void initCheckBox(UINT ctlID, UINT value);

public:
	CSimplePage(string_list fileList, bool hasFolders);
	virtual ~CSimplePage();

	virtual LRESULT OnMessage(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	virtual LRESULT OnInitDialog(LPARAM lParam);
};

#endif // !defined(AFX_SIMPLEPAGE_H__DDC5DD14_F203_440C_8BF0_3B6998093395__INCLUDED_)
