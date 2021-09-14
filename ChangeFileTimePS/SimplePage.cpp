// SimplePage.cpp: implementation of the SimplePage class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SimplePage.h"
#if _MSC_VER > 1200
#include "ChangeFileTimePS_h.h"
#else
#include "ChangeFileTimePS.h"
#endif
#include "ChangeFileTimeHandler.h"
#include "RecurseModeDialog.h"

str IncludeTrailingBackSlash(const str& buf)
{
	int len = buf.size();
	if (len > 0 && buf[len - 1] != '\\')
	{
		return buf + _T("\\");
	}
	return buf;
}

CSimplePage::CSimplePage(string_list fileList, bool hasFolders) : mylist(fileList), hasfolders(hasFolders)
{
}

void CSimplePage::initTempList()
{
	templist.clear();
	for (int it = 0; it < mylist.size(); it++)
	{
		templist.push_back(mylist[it]);
	}
}

CSimplePage::~CSimplePage()
{
}

void CSimplePage::OnAttributesClick()
{
	bool f = IsDlgButtonChecked(IDC_ATTRIBUTES) == BST_CHECKED;
	EnableDlgItem(IDC_ARCHIVE, f);
	EnableDlgItem(IDC_READONLY, f);
	EnableDlgItem(IDC_HIDDEN, f);
	EnableDlgItem(IDC_SYSTEM, f);
}

void CSimplePage::OnTimesClick()
{
	bool f = IsDlgButtonChecked(IDC_TIMES) == BST_CHECKED;
	EnableDlgItem(IDC_ONE_TIME, f);
	EnableDlgItem(IDC_CREATE, f);
	EnableDlgItem(IDC_LAST_ACCESS, f);
	EnableDlgItem(IDC_LAST_WRITE, f);
	EnableDlgItem(IDC_DATEPICKER1, f);
	EnableDlgItem(IDC_DATEPICKER2, f);
	EnableDlgItem(IDC_DATEPICKER3, f);
	EnableDlgItem(IDC_TIMEPICKER1, f);
	EnableDlgItem(IDC_TIMEPICKER2, f);
	EnableDlgItem(IDC_TIMEPICKER3, f);
	EnableDlgItem(IDC_NOW1, f);
	EnableDlgItem(IDC_NOW2, f);
	EnableDlgItem(IDC_NOW3, f);
	EnableDlgItem(IDC_READONLY_TOO, f);
}

void CSimplePage::OnOneTimeClick()
{
	int flag = (IsDlgButtonChecked(IDC_ONE_TIME) == BST_CHECKED) ? SW_HIDE : SW_SHOW;
	ShowDlgItem(IDC_DATEPICKER2, flag);
	ShowDlgItem(IDC_DATEPICKER3, flag);
	ShowDlgItem(IDC_TIMEPICKER2, flag);
	ShowDlgItem(IDC_TIMEPICKER3, flag);
	ShowDlgItem(IDC_NOW2, flag);
	ShowDlgItem(IDC_NOW3, flag);
}

void CSimplePage::applyAttribute(LPDWORD attrs, UINT checkboxState, DWORD fileAttribute)
{
	if (checkboxState == BST_CHECKED)
	{
		*attrs |= fileAttribute;
	}
	else if (checkboxState == BST_UNCHECKED)
	{
		*attrs &= ~fileAttribute;
	}
}

void CSimplePage::prepareAttribute(LPDWORD orMask, LPDWORD andMask, UINT bFlag, UINT bInitFlag, DWORD fileAttribute)
{
	if (bFlag != bInitFlag)
	{
		if (bFlag == BST_CHECKED)
		{
			*orMask |= fileAttribute;
		}
		else if (bFlag == BST_UNCHECKED)
		{
			*andMask &= ~fileAttribute;
		}
	}
}

void CSimplePage::prepareMasks(LPDWORD orMask, LPDWORD andMask, UINT bArchive, UINT bReadOnly, UINT bHidden,
                               UINT bSystem)
{
	*andMask = 0xFFFFFFFF;
	*orMask  = 0;
	prepareAttribute(orMask, andMask, bArchive, bInitArchive, FILE_ATTRIBUTE_ARCHIVE);
	prepareAttribute(orMask, andMask, bReadOnly, bInitReadOnly, FILE_ATTRIBUTE_READONLY);
	prepareAttribute(orMask, andMask, bHidden, bInitHidden, FILE_ATTRIBUTE_HIDDEN);
	prepareAttribute(orMask, andMask, bSystem, bInitSystem, FILE_ATTRIBUTE_SYSTEM);
}

void CSimplePage::MySetFileAttrs(const str& lpFileName, DWORD orMask, DWORD andMask)
{
	DWORD attrs = GetFileAttributes(lpFileName.c_str());
	if (attrs == 0xFFFFFFFF)
	{
		// add a failure message to the log
	}
	else
	{
		attrs |= orMask;
		attrs &= andMask;

		if (!SetFileAttributes(lpFileName.c_str(), attrs))
		{
			// add a failure message to the log
		}
	}
}

BOOL CSimplePage::GetSomeFileTime(int ctlIndex, LPFILETIME ft)
{
	WinObj::CDateTimePicker dateCtl(*this, IDC_DATEPICKER1 + ctlIndex);
	WinObj::CDateTimePicker timeCtl(*this, IDC_TIMEPICKER1 + ctlIndex);
	SYSTEMTIME p1;
	SYSTEMTIME p2;
	bool validDate = dateCtl.GetSystemTime(&p1) == GDT_VALID;
	bool validTime = timeCtl.GetSystemTime(&p2) == GDT_VALID;
	FILETIME f1;
	if (validDate && validTime)
	{
		p1.wHour         = p2.wHour;
		p1.wMilliseconds = p2.wMilliseconds;
		p1.wMinute       = p2.wMinute;
		p1.wSecond       = p2.wSecond;
		if (SystemTimeToFileTime(&p1, &f1) == 0)
		{
			return FALSE;
		}
		return LocalFileTimeToFileTime(&f1, ft);
	}

	return FALSE;
}

void CSimplePage::MySetFileTime(const str& lpFileName, LPFILETIME f1, LPFILETIME f2, LPFILETIME f3)
{
	HANDLE hFile = CreateFile(lpFileName.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING,
	                          FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		// add something to the log
	}
	else
	{
		if (SetFileTime(hFile, f1, f2, f3) == 0)
		{
			// add something to the log
		}
		CloseHandle(hFile);
	}
}

void CSimplePage::MyGetFileTime(const str& lpFileName, SYSTEMTIME(s)[3])
{
	HANDLE hFile = CreateFile(lpFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
	                          FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		// add something to the log
	}
	else
	{
		FILETIME f[3];
		FILETIME lf[3];
		if (GetFileTime(hFile, &f[0], &f[1], &f[2]) == 0)
		{
			// add something to the log
		}
		for (int i = 0; i < 3; i++)
		{
			FileTimeToLocalFileTime(&f[i], &lf[i]);
			FileTimeToSystemTime(&lf[i], &s[i]);
		}
		CloseHandle(hFile);
	}
}

void CSimplePage::SetSystemTime(int index, LPSYSTEMTIME systemTime)
{
	WinObj::CDateTimePicker dateCtl(*this, IDC_DATEPICKER1 + index);
	dateCtl.SetSystemTime(GDT_VALID, systemTime);
	WinObj::CDateTimePicker timeCtl(*this, IDC_TIMEPICKER1 + index);
	timeCtl.SetSystemTime(GDT_VALID, systemTime);
}

void CSimplePage::InitDateTimeCtls(const str& lpFileName)
{
	SYSTEMTIME s[3];
	MyGetFileTime(lpFileName, s);
	for (int i = 0; i < 3; i++)
	{
		SetSystemTime(i, &s[i]);
	}
}

void CSimplePage::OnNowClick(UINT id)
{
	SYSTEMTIME s;
	GetLocalTime(&s);
	SetSystemTime(id - IDC_NOW1, &s);
	Changed();
}

bool CSimplePage::OnOK()
{

	LPCTSTR lpFileName = NULL;
	int it;

	if (IsDlgButtonChecked(IDC_ATTRIBUTES) != BST_CHECKED && IsDlgButtonChecked(IDC_TIMES) != BST_CHECKED)
	{
		return true;
	}

	if (hasfolders)
	{
		recurseMode = RecurseMode();
		if (recurseMode == 0)
		{
			return false;
		}
	}

	SetCursor(LoadCursor(0, IDC_WAIT));

	if ((recurseMode & RECURSE_SKIP_ROOT) != 0)
	{
		templist.clear();
		for (it = 0; it < mylist.size(); it++)
		{
			if ((GetFileAttributes(mylist[it].c_str()) & FILE_ATTRIBUTE_DIRECTORY) == 0u)
			{
				templist.push_back(mylist[it]);
			}
		}
	}
	else
	{
		initTempList();
	}

	if (recurseMode != RECURSE_SIMPLE)
	{
		for (it = 0; it < mylist.size(); it++)
		{
			if (GetFileAttributes(mylist[it].c_str()) & FILE_ATTRIBUTE_DIRECTORY)
			{
				recurseThat(mylist[it]);
			}
		}
	}

	if (IsDlgButtonChecked(IDC_ATTRIBUTES) == BST_CHECKED)
	{
		// set file attributes

		UINT bArchive  = IsDlgButtonChecked(IDC_ARCHIVE);
		UINT bReadOnly = IsDlgButtonChecked(IDC_READONLY);
		UINT bHidden   = IsDlgButtonChecked(IDC_HIDDEN);
		UINT bSystem   = IsDlgButtonChecked(IDC_SYSTEM);

		DWORD orMask;
		DWORD andMask;
		prepareMasks(&orMask, &andMask, bArchive, bReadOnly, bHidden, bSystem);

		// for each file:
		for (it = 0; it < templist.size(); it++)
		{
			MySetFileAttrs(templist[it], orMask, andMask);
		}

		bInitArchive  = IsDlgButtonChecked(IDC_ARCHIVE);
		bInitReadOnly = IsDlgButtonChecked(IDC_READONLY);
		bInitHidden   = IsDlgButtonChecked(IDC_HIDDEN);
		bInitSystem   = IsDlgButtonChecked(IDC_SYSTEM);
	}

	if (IsDlgButtonChecked(IDC_TIMES) == BST_CHECKED)
	{
		bool failure = false;
		FILETIME ftCreate;
		FILETIME ftLastAccess;
		FILETIME ftLastWrite;
		LPFILETIME lpftCreate     = NULL;
		LPFILETIME lpftLastAccess = NULL;
		LPFILETIME lpftLastWrite  = NULL;

		if (IsDlgButtonChecked(IDC_ONE_TIME) == BST_CHECKED)
		{
			if (GetSomeFileTime(0, &ftCreate) == 0)
			{
				// generic failure
				failure = true;
			}
			else
			{
				lpftCreate = lpftLastAccess = lpftLastWrite = &ftCreate;
			}
		}
		else
		{
			if (IsDlgButtonChecked(IDC_CREATE) == BST_CHECKED)
			{
				if (GetSomeFileTime(0, &ftCreate) == 0)
				{
					failure = true;
				}
				else
				{
					lpftCreate = &ftCreate;
				}
			}

			if (!failure && IsDlgButtonChecked(IDC_LAST_ACCESS) == BST_CHECKED)
			{
				if (GetSomeFileTime(1, &ftLastAccess) == 0)
				{
					failure = true;
				}
				else
				{
					lpftLastAccess = &ftLastAccess;
				}
			}

			if (!failure && IsDlgButtonChecked(IDC_LAST_WRITE) == BST_CHECKED)
			{
				if (GetSomeFileTime(2, &ftLastWrite) == 0)
				{
					failure = true;
				}
				else
				{
					lpftLastWrite = &ftLastWrite;
				}
			}
		}

		if (!failure)
		{
			bool includeReadOnly = IsDlgButtonChecked(IDC_READONLY_TOO) == BST_CHECKED;
			for (it = 0; it < templist.size(); it++)
			{
				bool restoreReadOnly = false;
				DWORD attrs;

				if (includeReadOnly)
				{
					attrs = GetFileAttributes(templist[it].c_str());
					if ((restoreReadOnly = ((attrs & FILE_ATTRIBUTE_READONLY)) != 0u))
					{
						SetFileAttributes(templist[it].c_str(), attrs & ~FILE_ATTRIBUTE_READONLY);
					}
				}

				MySetFileTime(templist[it], lpftCreate, lpftLastAccess, lpftLastWrite);

				if (restoreReadOnly)
				{
					SetFileAttributes(templist[it].c_str(), attrs);
				}
			}
		}
	}

	templist.clear();
	SetCursor(LoadCursor(0, IDC_ARROW));

	return true;
}

void CSimplePage::Changed()
{
	NotifyParentChanged();
}

void CSimplePage::Nag()
{
	DWORD test = GetTickCount();
	do
	{
		MsgBox(_T("ChangeFileTimePS is shareware. Visit http://nikosgeorgiou.tripod.com to find out how to ")
		       _T("become a registered user and get rid of this message."),
		       _T("Shareware reminder"), MB_ICONINFORMATION);
		test = GetTickCount() - test;
	} while (test < 2000);
}

void CSimplePage::checkFileAttribute(DWORD attrs, DWORD attrBit, UINT* value, bool firstTime)
{
	UINT test;

	test = (attrs & attrBit) != 0u ? BST_CHECKED : BST_UNCHECKED;
	if (firstTime)
	{
		*value = test;
	}
	else if (*value != test)
	{
		*value = BST_INDETERMINATE;
	}
}

void CSimplePage::initCheckBox(UINT ctlID, UINT value)
{
	if (value == BST_INDETERMINATE)
	{
		SendDlgItemMessage(ctlID, BM_SETSTYLE, BS_AUTO3STATE, 0);
	}

	CheckDlgButton(ctlID, value);
}

LRESULT CSimplePage::OnInitDialog(LPARAM lParam)
{
	int it;

	UINT bArchive;
	UINT bReadOnly;
	UINT bHidden;
	UINT bSystem;
	for (it = 0; it < mylist.size(); it++)
	{

		SendDlgItemMessage(IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)mylist[it].c_str());
		DWORD attrs = GetFileAttributes(mylist[it].c_str());

		checkFileAttribute(attrs, FILE_ATTRIBUTE_ARCHIVE, &bArchive, it == 0);
		checkFileAttribute(attrs, FILE_ATTRIBUTE_READONLY, &bReadOnly, it == 0);
		checkFileAttribute(attrs, FILE_ATTRIBUTE_HIDDEN, &bHidden, it == 0);
		checkFileAttribute(attrs, FILE_ATTRIBUTE_SYSTEM, &bSystem, it == 0);
	}

	initCheckBox(IDC_ARCHIVE, bInitArchive = bArchive);
	initCheckBox(IDC_READONLY, bInitReadOnly = bReadOnly);
	initCheckBox(IDC_HIDDEN, bInitHidden = bHidden);
	initCheckBox(IDC_SYSTEM, bInitSystem = bSystem);

	initCheckBox(IDC_ATTRIBUTES, BST_CHECKED);
	initCheckBox(IDC_TIMES, BST_CHECKED);
	initCheckBox(IDC_CREATE, BST_CHECKED);
	initCheckBox(IDC_LAST_ACCESS, BST_CHECKED);
	initCheckBox(IDC_LAST_WRITE, BST_CHECKED);
	initCheckBox(IDC_ONE_TIME, BST_CHECKED);
	OnOneTimeClick();

	if (!mylist.empty())
	{
		InitDateTimeCtls(mylist[0]);
	}
	return 1;
}

LRESULT CSimplePage::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		BUTTON_HANDLER(IDC_ATTRIBUTES, OnAttributesClick);
		BUTTON_HANDLER(IDC_TIMES, OnTimesClick);
		BUTTON_HANDLER(IDC_ONE_TIME, OnOneTimeClick);
		BUTTON_HANDLER(IDC_ARCHIVE, Changed);
		BUTTON_HANDLER(IDC_READONLY, Changed);
		BUTTON_HANDLER(IDC_HIDDEN, Changed);
		BUTTON_HANDLER(IDC_SYSTEM, Changed);
		BUTTON_HANDLER_RANGE(IDC_NOW1, IDC_NOW3, OnNowClick);
		break;
	case WM_NOTIFY: {
		NMHDR* phdr = (NMHDR*)lParam;

		switch (phdr->code)
		{
		case PSN_APPLY:
			bool result;
			result = OnOK();
			if (result)
			{
				Nag();
			}
			SetDialogMessageResult(result ? PSNRET_NOERROR : PSNRET_INVALID);
			return 1;
			break;

		case DTN_DATETIMECHANGE:
			// If the user changes any of the DTP controls, enable
			// the Apply button.

			Changed();
			break;
		}
	}
	default:
		return CPropSheet::OnMessage(msg, wParam, lParam);
	}
	return 0;
}

int CSimplePage::RecurseMode()
{
	RecurseModeDialog dlg;
	int ret = dlg.Modal(*GetInstance(), *this, IDD_RECURSE);
	lstrcpy(recurseFilter, dlg.filter);
	if (lstrlen(recurseFilter) == 0)
	{
		lstrcpy(recurseFilter, _T("*.*"));
	}

	return ret;
}

void CSimplePage::recurseThat(const str& szDir)
{
	HANDLE fh;
	WIN32_FIND_DATA fd;
	str buf = IncludeTrailingBackSlash(szDir) + _T("*.*");

	if ((fh = FindFirstFile(buf.c_str(), &fd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (lstrcmp(fd.cFileName, _T(".")) && lstrcmp(fd.cFileName, _T("..")))
			{
				buf = IncludeTrailingBackSlash(szDir) + fd.cFileName;
				if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0u)
				{
					recurseThat(buf);
				}
			}
		} while (FindNextFile(fh, &fd));
		FindClose(fh);
	}

	buf = IncludeTrailingBackSlash(szDir) + recurseFilter;

	if ((fh = FindFirstFile(buf.c_str(), &fd)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (lstrcmp(fd.cFileName, _T(".")) && lstrcmp(fd.cFileName, _T("..")))
			{
				buf = IncludeTrailingBackSlash(szDir) + fd.cFileName;
				if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0u)
				{
					if ((recurseMode & RECURSE_FOLDERS) != 0)
					{
						templist.push_back(buf);
					}
				}
				else
				{
					if ((recurseMode & RECURSE_FILES) != 0)
					{
						templist.push_back(buf);
					}
				}
			}
		} while (FindNextFile(fh, &fd));
		FindClose(fh);
	}
}
