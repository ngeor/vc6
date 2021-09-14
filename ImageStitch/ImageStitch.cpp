// ImageStitch.cpp : Defines the entry point for the application.
//

#include "StdAfx.h"
#include "..\WinObjCommDlg\OpenFileName.h"
#include "..\WinObj\WinObj.h"
#include "Resource.h"

#define ID_TOOLBAR       500
#define ID_CMD_NEW_FILE  501
#define ID_CMD_OPEN_FILE 502
#define ID_CMD_SAVE_FILE 503

#define DEFAULT_EXTENSION _T("isf")

typedef struct ListEntry
{
	TCHAR szPath[MAX_PATH];
	HBITMAP hBitmap;
} ListEntry;

class MainDialog : public WinObj::CDialog
{
	void OnClose();
	void OnCommand(WPARAM wParam, LPARAM lParam);
	static void OnDeleteItem(WPARAM wParam, LPARAM lParam);
	static void OnDrawItem(LPARAM lParam);
	void OnMeasureItem(LPARAM lParam);
	void OnPaint();
	void DoAddFile(LPCTSTR szFileName, LPCTSTR szPathName = NULL);
	void OnCmdAdd();
	void OnCmdRemove();
	void OnCmdMoveLeft(int pos);
	void OnCmdNewFile();
	void DoOpenFile(LPCTSTR szFileName);
	void OnCmdOpenFile();
	void DoSaveFile(LPCTSTR szFileName);
	void OnCmdSaveFile();

public:
	MainDialog();
	virtual ~MainDialog();
	virtual LRESULT OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	virtual LRESULT OnInitDialog(LPARAM lParam);
};

LRESULT MainDialog::OnInitDialog(LPARAM lParam)
{
	TBBUTTON tbb[3];
	SendDlgItemMessage(ID_LST_ICONS, LB_SETCOLUMNWIDTH, 32, 0);
	SetDlgItemInt(ID_TXT_IMG_WIDTH, 16, false);
	SetDlgItemInt(ID_TXT_IMG_HEIGHT, 16, false);

	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap   = 0;
	tbb[0].idCommand = ID_CMD_NEW_FILE;
	tbb[0].fsState   = TBSTATE_ENABLED;
	tbb[0].fsStyle   = TBSTYLE_BUTTON;

	tbb[1].iBitmap   = 1;
	tbb[1].idCommand = ID_CMD_OPEN_FILE;
	tbb[1].fsState   = TBSTATE_ENABLED;
	tbb[1].fsStyle   = TBSTYLE_BUTTON;

	tbb[2].iBitmap   = 2;
	tbb[2].idCommand = ID_CMD_SAVE_FILE;
	tbb[2].fsState   = TBSTATE_ENABLED;
	tbb[2].fsStyle   = TBSTYLE_BUTTON;

	// TODO: find a better way for GetInstance()->GetHandle()
	CreateToolbarEx(GetHandle(), WS_CHILD | WS_VISIBLE, ID_TOOLBAR, 3 /* number of bitmaps */,
	                GetInstance()->GetHandle(), IDB_TOOLBAR, tbb, 3 /* number of buttons */, 1, 0, 16, 16,
	                sizeof(TBBUTTON));
	return 1;
}

void MainDialog::OnClose()
{
	EndDialog();
}

void MainDialog::DoAddFile(LPCTSTR szFileName, LPCTSTR szPathName)
{
	// TODO do not use lstr* functions
	ListEntry* le;
	le = new ListEntry;
	if (szPathName != NULL)
	{
		lstrcpy(le->szPath, szPathName);
		if (szPathName[lstrlen(szPathName) - 1] != '\\')
		{
			lstrcat(le->szPath, _T("\\"));
		}
		lstrcat(le->szPath, szFileName);
	}
	else
	{
		lstrcpy(le->szPath, szFileName);
	}
	le->hBitmap = (HBITMAP)LoadImage(0, le->szPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	SendDlgItemMessage(ID_LST_ICONS, LB_ADDSTRING, 0, (LPARAM)le);
}

void MainDialog::OnCmdAdd()
{
	// TODO: find a better way for this constructor
	WinObj::COpenFileName of(*GetInstance(), *this);
	of.WithFilter(IDS_OPEN_IMAGE_FILTER)
		.WithFilterIndex(1)
		.WithFlags(OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY);
	if (of.GetOpenFileName())
	{
		LPCTSTR file = of.GetFile();
		if (of.GetFileOffset() > _tcslen(file))
		{
			// multiple files, separated by null, first element in path, last element terminated with double null
			LPCTSTR nextFile = file + of.GetFileOffset();
			while (*nextFile != '\0')
			{
				DoAddFile(nextFile, file);
				nextFile = nextFile + _tcslen(nextFile) + 1;
			}
		}
		else
		{
			// single file
			DoAddFile(file);
		}
		InvalidateRect();
	}
}

void MainDialog::OnCmdRemove()
{
	int nSel = SendDlgItemMessage(ID_LST_ICONS, LB_GETCURSEL, 0, 0);
	if (nSel >= 0)
	{
		SendDlgItemMessage(ID_LST_ICONS, LB_DELETESTRING, nSel, 0);
		InvalidateRect();
	}
}

void MainDialog::OnCmdMoveLeft(int pos)
{
	int nSel = SendDlgItemMessage(ID_LST_ICONS, LB_GETCURSEL, 0, 0);
	if (nSel >= 0)
	{
		DWORD a;
		DWORD b;
		int newSel;
		int count = SendDlgItemMessage(ID_LST_ICONS, LB_GETCOUNT, 0, 0);
		newSel    = (nSel + count + pos) % count;

		a = SendDlgItemMessage(ID_LST_ICONS, LB_GETITEMDATA, nSel, 0);
		b = SendDlgItemMessage(ID_LST_ICONS, LB_GETITEMDATA, newSel, 0);

		SendDlgItemMessage(ID_LST_ICONS, LB_SETITEMDATA, nSel, b);
		SendDlgItemMessage(ID_LST_ICONS, LB_SETITEMDATA, newSel, a);

		SendDlgItemMessage(ID_LST_ICONS, LB_SETCURSEL, newSel, 0);

		InvalidateRect();
	}
}

void MainDialog::OnCmdNewFile()
{
	SendDlgItemMessage(ID_LST_ICONS, LB_RESETCONTENT, 0, 0);
	InvalidateRect();
}

void MainDialog::DoOpenFile(LPCTSTR szFileName)
{
	FILE* fp;
	TCHAR buf[MAX_PATH];
	LPTSTR p;

	buf[0] = '\0';
	lstrcpy(buf, szFileName);
	if (buf[0] == '"' && buf[lstrlen(buf) - 1] == '"')
	{
		buf[lstrlen(buf) - 1] = '\0';
		p                     = buf + 1;
	}
	else
	{
		p = buf;
	}

#if _MSC_VER > 1200
	_tfopen_s(&fp, p, _T("rt"));
#else
	fp = _tfopen(p, _T("rt"));
#endif
	SendDlgItemMessage(ID_LST_ICONS, LB_RESETCONTENT, 0, 0);
	while (_fgetts(buf, MAX_PATH, fp) != NULL)
	{
		if ((p = _tcsrchr(buf, '\n')) != NULL)
		{
			*p = '\0';
		}

		DoAddFile(buf);
	}
	fclose(fp);
	InvalidateRect();
}

void MainDialog::OnCmdOpenFile()
{
	WinObj::COpenFileName of(*GetInstance(), *this);
	of.WithFilter(IDS_OPEN_FILTER)
		.WithDefaultExtension(DEFAULT_EXTENSION)
		.WithFilterIndex(1)
		.WithFlags(OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY);
	if (of.GetOpenFileName())
	{
		DoOpenFile(of.GetFile());
	}
}

void MainDialog::DoSaveFile(LPCTSTR szFileName)
{
	FILE* fp;
#if _MSC_VER > 1200
	_tfopen_s(&fp, szFileName, _T("wt"));
#else
	fp = _tfopen(szFileName, _T("tw"));
#endif
	int i;
	int count = SendDlgItemMessage(ID_LST_ICONS, LB_GETCOUNT, 0, 0);
	for (i = 0; i < count; i++)
	{
		ListEntry* le = (ListEntry*)SendDlgItemMessage(ID_LST_ICONS, LB_GETITEMDATA, i, 0);
#if _MSC_VER > 1200
		_ftprintf_s(fp, _T("%s\n"), le->szPath);
#else
		_ftprintf(fp, _T("%s\n"), le->szPath);
#endif
	}
	fclose(fp);
}

void MainDialog::OnCmdSaveFile()
{
	WinObj::COpenFileName of(*GetInstance(), *this);
	of.WithFilter(IDS_OPEN_FILTER)
		.WithDefaultExtension(DEFAULT_EXTENSION)
		.WithFilterIndex(1)
		.WithFlags(OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY);
	if (of.GetSaveFileName())
	{
		DoSaveFile(of.GetFile());
	}
}

void MainDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam); // notification code
	WORD wID         = LOWORD(wParam); // item, control, or accelerator identifier
	HWND hwndCtl     = (HWND)lParam;   // handle of control

	switch (wID)
	{
	case ID_CMD_ADD:
		OnCmdAdd();
		break;
	case ID_CMD_REMOVE:
		OnCmdRemove();
		break;
	case ID_CMD_MOVE_LEFT:
		OnCmdMoveLeft(-1);
		break;
	case ID_CMD_MOVE_RIGHT:
		OnCmdMoveLeft(1);
		break;
	case ID_CMD_NEW_FILE:
		OnCmdNewFile();
		break;
	case ID_CMD_OPEN_FILE:
		OnCmdOpenFile();
		break;
	case ID_CMD_SAVE_FILE:
		OnCmdSaveFile();
		break;
	}
}

void MainDialog::OnDeleteItem(WPARAM wParam, LPARAM lParam)
{
	LPDELETEITEMSTRUCT lpdis = (LPDELETEITEMSTRUCT)lParam; // structure with item information
	if (lpdis->CtlID == ID_LST_ICONS)
	{
		ListEntry* le = (ListEntry*)lpdis->itemData;
		if (le != NULL)
		{
			if (le->hBitmap != NULL)
			{
				DeleteObject(le->hBitmap);
			}
			delete le;
		}
	}
}

void MainDialog::OnDrawItem(LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
	ListEntry* le          = (ListEntry*)lpdis->itemData;

	FillRect(lpdis->hDC, &lpdis->rcItem,
	         (HBRUSH)(1 + ((lpdis->itemState & ODS_SELECTED) != 0u ? COLOR_HIGHLIGHT : COLOR_WINDOW)));

	if ((signed int)lpdis->itemID >= 0 && lpdis->itemData != NULL)
	{

		HDC hMemDC      = CreateCompatibleDC(0);
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, le->hBitmap);
		BITMAP bmp;
		GetObject(le->hBitmap, sizeof(BITMAP), &bmp);

		SIZE vp;
		RECT rt;
		vp.cx   = lpdis->rcItem.right - lpdis->rcItem.left;
		vp.cy   = lpdis->rcItem.bottom - lpdis->rcItem.top;
		rt.left = rt.top = 0;
		if (bmp.bmWidth > bmp.bmHeight)
		{
			if (bmp.bmWidth > vp.cx)
			{
				rt.right  = vp.cx;
				rt.bottom = (bmp.bmHeight * vp.cx) / bmp.bmWidth;
			}
			else
			{
				rt.right  = bmp.bmWidth; // set to vp.cx for left justify
				rt.bottom = bmp.bmHeight;
			}
		}
		else
		{
			if (bmp.bmHeight > vp.cy)
			{
				rt.bottom = vp.cy;
				rt.right  = (bmp.bmWidth * vp.cy) / bmp.bmHeight;
			}
			else
			{
				rt.right  = bmp.bmWidth;
				rt.bottom = bmp.bmHeight;
			}
		}

		OffsetRect(&rt, (lpdis->rcItem.left + lpdis->rcItem.right - rt.right) / 2,
		           (lpdis->rcItem.top + lpdis->rcItem.bottom - rt.bottom) / 2);

		StretchBlt(lpdis->hDC, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, hMemDC, 0, 0, bmp.bmWidth,
		           bmp.bmHeight, SRCCOPY);

		DeleteDC(hMemDC);
	}
}

void MainDialog::OnMeasureItem(LPARAM lParam)
{
	LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT)lParam;
	RECT rt;
	GetDlgItemClientRect(ID_LST_ICONS, &rt);
	lpmis->itemHeight = rt.bottom;
}

void MainDialog::OnPaint()
{
	PAINTSTRUCT ps;
	RECT clientRt;
	SIZE imgSz;
	int x;
	int y;
	int i;
	int count;
	bool success;

	BeginPaint(&ps);

	imgSz.cx = GetDlgItemInt(ID_TXT_IMG_WIDTH, &success, FALSE);
	if (success)
	{
		imgSz.cy = GetDlgItemInt(ID_TXT_IMG_HEIGHT, &success, FALSE);
		if (success)
		{
			if ((count = SendDlgItemMessage(ID_LST_ICONS, LB_GETCOUNT, 0, 0)) > 0)
			{
				GetClientRect(&clientRt);
				y          = clientRt.bottom - 2 - imgSz.cy;
				x          = 2;
				HDC hMemDC = CreateCompatibleDC(0);
				BITMAP bmp;
				ListEntry* le;

				for (i = 0; i < count; i++, x += imgSz.cx)
				{
					le = (ListEntry*)SendDlgItemMessage(ID_LST_ICONS, LB_GETITEMDATA, i, 0);
					if (le != NULL && le->hBitmap != NULL)
					{
						SelectObject(hMemDC, le->hBitmap);
						GetObject(le->hBitmap, sizeof(BITMAP), &bmp);
						RECT rt;
						rt.left = rt.top = 0;
						if (bmp.bmWidth > bmp.bmHeight)
						{
							if (bmp.bmWidth > imgSz.cx)
							{
								rt.right  = imgSz.cx;
								rt.bottom = (bmp.bmHeight * imgSz.cx) / bmp.bmWidth;
							}
							else
							{
								rt.right  = bmp.bmWidth; // set to imgSz.cx for left justify
								rt.bottom = bmp.bmHeight;
							}
						}
						else
						{
							if (bmp.bmHeight > imgSz.cy)
							{
								rt.bottom = imgSz.cy;
								rt.right  = (bmp.bmWidth * imgSz.cy) / bmp.bmHeight;
							}
							else
							{
								rt.right  = bmp.bmWidth;
								rt.bottom = bmp.bmHeight;
							}
						}

						OffsetRect(&rt, x + (imgSz.cx - rt.right) / 2, y + (imgSz.cy - rt.bottom) / 2);
						StretchBlt(ps.hdc, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, hMemDC, 0, 0,
						           bmp.bmWidth, bmp.bmHeight, SRCCOPY);
					}
				} /* end of for loop */
				DeleteDC(hMemDC);
			}
		}
	}

	EndPaint(&ps);
}

MainDialog::MainDialog()
{
}

MainDialog::~MainDialog()
{
}

LRESULT MainDialog::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		OnClose();
		break;
	case WM_COMMAND:
		OnCommand(wParam, lParam);
		break;
	case WM_DELETEITEM:
		OnDeleteItem(wParam, lParam);
		break;
	case WM_DRAWITEM:
		OnDrawItem(lParam);
		break;
	case WM_MEASUREITEM:
		OnMeasureItem(lParam);
		break;
	case WM_PAINT:
		OnPaint();
		break;
	default:
		return CDialog::OnMessage(message, wParam, lParam);
		break;
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WinObj::CInstance app(hInstance);
	MainDialog dialog;
	dialog.Modal(app, IDD_MAIN);
	return 0;
}
