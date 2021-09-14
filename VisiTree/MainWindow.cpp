#include "StdAfx.h"
#include "MainWindow.h"
#include "About.h"
#include "Render.h"
#include "resource.h"
#include "..\WinObjCommDlg\OpenFileName.h"

#define DEFAULT_EXTENSION _T("emf")

MainWindow::MainWindow()
{
	myTree = treeFactory.Create(TreeTypeSearch, KeyTypeInteger);
}

MainWindow::~MainWindow()
{
	delete myTree;
}

void MainWindow::SizeControls()
{
	RECT rt;
	int i;
	GetClientRect(&rt);
	MoveDlgItem(ID_INPUT, 0, rt.bottom - 40, rt.right - 300, 20);
	MoveDlgItem(ID_ADD, rt.right - 300, rt.bottom - 40, 100, 20);
	MoveDlgItem(ID_FREE, rt.right - 200, rt.bottom - 40, 100, 20);
	MoveDlgItem(ID_KEYTYPE, rt.right - 100, rt.bottom - 40, 100, 20);

	i = rt.right / 4;
	MoveDlgItem(ID_OPENFILE, 0, rt.bottom - 20, i, 20);
	MoveDlgItem(ID_SAVEMETAFILE, i, rt.bottom - 20, i, 20);
	MoveDlgItem(ID_ABOUT, 2 * i, rt.bottom - 20, i, 20);
	MoveDlgItem(ID_EXIT, 3 * i, rt.bottom - 20, rt.right - 3 * i, 20);
}

void MainWindow::OpenTreeFile(LPCTSTR szFile)
{
	FILE *fp;
	key data;
	int success;

	myTree->Clear();

#if _MSC_VER > 1200
	_tfopen_s(&fp, szFile, _T("r"));
#else
	fp = _tfopen(szFile, _T("r"));
#endif
	while (feof(fp) == 0)
	{
		switch (myTree->GetKeyType())
		{
			case KeyTypeChar:
				success = _ftscanf_s(fp, _T("%c"), &data.c) != EOF;
				break;
			case KeyTypeInteger:
				success = _ftscanf_s(fp, _T("%d"), &data.i);
				break;
			case KeyTypeFloat:
				success = _ftscanf_s(fp, _T("%f"), &data.f) != EOF;
				break;
			case KeyTypeString:
				data.s  = (LPTSTR)malloc(sizeof(TCHAR) * MAX_PATH);
				success = _ftscanf_s(fp, _T("%s"), data.s) != EOF;
				break;
			default:
				// throw an error
				break;
		}

		if (success != 0)
		{
			myTree->Add(data);
		}
	}

	fclose(fp);
	InvalidateRect();
}

void MainWindow::OnOpenTreeFile()
{
	WinObj::COpenFileName of(*GetInstance(), *this);
	of.WithFilter(IDS_OPEN_FILTER)
		.WithDefaultExtension(DEFAULT_EXTENSION)
		.WithFlags(OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST);
	if (of.GetOpenFileName())
	{
		OpenTreeFile(of.GetFile());
	}
}

void MainWindow::OnSaveMetafile()
{
	if (myTree->GetRoot() == NULL)
	{
		return;
	}

	WinObj::COpenFileName of(*GetInstance(), *this);
	of.WithFilter(IDS_OPEN_FILTER)
		.WithDefaultExtension(DEFAULT_EXTENSION)
		.WithFlags(OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT);

	if (of.GetSaveFileName())
	{
		renderMetafile(myTree, GetHandle(), of.GetFile());
	}
}

void MainWindow::OnAdd()
{
	bool success;
	key data;
	success = false;
	int len;

	switch (myTree->GetKeyType())
	{
		case KeyTypeChar:
			TCHAR buf[2];
			if ((success = (GetDlgItemText(ID_INPUT, buf, 2) != 0)))
			{
				data.c = buf[0];
			}
			break;

		case KeyTypeInteger:
			data.i = (int)GetDlgItemInt(ID_INPUT, &success, true);
			break;

		case KeyTypeFloat:
			LPTSTR s;
			len = GetDlgItemTextLength(ID_INPUT) + 1;
			if (len > 0)
			{
				s       = (LPTSTR)malloc(sizeof(TCHAR) * len);
				success = GetDlgItemText(ID_INPUT, s, len) != 0;
				_stscanf_s(s, _T("%f"), &data.f);
				free(s);
			}

			break;

		case KeyTypeString:
			len = GetDlgItemTextLength(ID_INPUT) + 1;
			if (len > 0)
			{
				data.s  = (LPTSTR)malloc(sizeof(TCHAR) * len);
				success = GetDlgItemText(ID_INPUT, data.s, len) != 0;
			}
			break;
	}

	if (success)
	{
		myTree->Add(data);
		InvalidateRect();
	}

	SendDlgItemMessage(ID_INPUT, EM_SETSEL, 0, -1); // select everything
}

void MainWindow::KeyTypeChanged(KeyType keyType)
{
	int i;
	int j;

	/* Refresh combo box */
	j = SendDlgItemMessage(ID_KEYTYPE, CB_GETCOUNT, 0, 0);
	i = 0;
	while ((i < j) && (keyType != (char)SendDlgItemMessage(
									  ID_KEYTYPE, CB_GETITEMDATA, i, 0)))
	{
		i++;
	}
	if (i < j)
	{
		SendDlgItemMessage(ID_KEYTYPE, CB_SETCURSEL, i, 0);
	}

	/* Refresh Menu Items */
	/* Remember that the order is char, int, float, string */

	switch (keyType)
	{
		case KeyTypeChar:
			i = ID_TREE_CHAR;
			break;
		case KeyTypeInteger:
			i = ID_TREE_INT;
			break;
		case KeyTypeFloat:
			i = ID_TREE_FLOAT;
			break;
		case KeyTypeString:
			i = ID_TREE_STRING;
			break;
		default:
			i = 0;
	}
	CheckMenuRadioItem(GetSubMenu(GetMenu(GetHandle()), 1),
					   ID_TREE_CHAR,
					   ID_TREE_STRING,
					   i,
					   MF_BYCOMMAND);
}

void MainWindow::SetKeyType(KeyType keyType)
{
	AbstractTree *oldTree = myTree;
	myTree                = treeFactory.Create(oldTree->GetTreeType(), keyType);
	delete oldTree;
	KeyTypeChanged(keyType);
	InvalidateRect();
}

void MainWindow::TreeTypeChanged(TreeType treeType)
{
	int i;
	switch (treeType)
	{
		case TreeTypeSimple:
			i = ID_TREE_SIMPLE;
			break;
		case TreeTypeSearch:
			i = ID_TREE_SEARCH;
			break;
		case TreeTypeAVL:
			i = ID_TREE_AVL;
			break;
		default:
			i = 0;
	}

	CheckMenuRadioItem(GetSubMenu(GetMenu(GetHandle()), 1),
					   ID_TREE_SIMPLE,
					   ID_TREE_AVL,
					   i,
					   MF_BYCOMMAND);
}

void MainWindow::SetTreeType(TreeType treeType)
{
	AbstractTree *oldTree = myTree;
	myTree                = treeFactory.Create(treeType, oldTree->GetKeyType());
	delete oldTree;
	TreeTypeChanged(treeType);
	InvalidateRect();
}

int MainWindow::CbAddString(int id, LPCTSTR string)
{
	return SendDlgItemMessage(id, CB_ADDSTRING, 0, (LPARAM)string);
}

int MainWindow::CbSetItemData(int id, int index, LPARAM data)
{
	return SendDlgItemMessage(id, CB_SETITEMDATA, index, data);
}

void MainWindow::CbAddKeyType(int keyType)
{
	const int STRING_OFFSET = 100;
	str buffer              = GetInstance()->LoadStr(STRING_OFFSET + keyType);
	LPCTSTR msg =
		buffer.length() > 0 ? buffer.c_str() : _T("Failed to load string");
	CbSetItemData(ID_KEYTYPE, CbAddString(ID_KEYTYPE, msg), keyType);
}

LRESULT MainWindow::OnCommand(UINT message, WPARAM wParam, LPARAM lParam)
{
	int id    = LOWORD(wParam);
	int event = HIWORD(wParam);
	// Parse the menu selections:
	switch (id)
	{
		case ID_ABOUT:
		{
			AboutDialog aboutDialog;
			aboutDialog.Modal(*GetInstance(), *this, IDD_ABOUTBOX);
		}
		break;
		case ID_EXIT:
			DestroyWindow();
			break;
		case ID_ADD:
			OnAdd();
			break;
		case ID_FREE:
			myTree->Clear();
			InvalidateRect();
			break;
		case ID_OPENFILE:
			OnOpenTreeFile();
			break;
		case ID_SAVEMETAFILE:
			OnSaveMetafile();
			break;
		case ID_TREE_CHAR:
			SetKeyType(KeyTypeChar);
			break;
		case ID_TREE_INT:
			SetKeyType(KeyTypeInteger);
			break;
		case ID_TREE_FLOAT:
			SetKeyType(KeyTypeFloat);
			break;
		case ID_TREE_STRING:
			SetKeyType(KeyTypeString);
			break;
		case ID_TREE_SIMPLE:
			SetTreeType(TreeTypeSimple);
			break;
		case ID_TREE_SEARCH:
			SetTreeType(TreeTypeSearch);
			break;
		case ID_TREE_AVL:
			SetTreeType(TreeTypeAVL);
			break;
		case ID_KEYTYPE:
			if (event == CBN_SELCHANGE)
			{
				int i;
				i = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				if (i >= 0)
				{
					SetKeyType((KeyType)SendMessage(
						(HWND)lParam, CB_GETITEMDATA, i, 0));
				}
			}
		default:
			return DefWindowProc(GetHandle(), message, wParam, lParam);
	}

	return 0;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT MainWindow::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_SIZE:
			SizeControls();
			break;
		case WM_ERASEBKGND:
			return 1;
		case WM_COMMAND:
			return OnCommand(message, wParam, lParam);
		case WM_CLOSE:
			DestroyWindow();
			break;
		case WM_PAINT:
			PAINTSTRUCT ps;
			RECT rt;

			BeginPaint(&ps);
			GetClientRect(&rt);
			rt.bottom -= 39;
			rt.right++;
			render(myTree, &rt, ps.hdc);
			EndPaint(&ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return CDialog::OnMessage(message, wParam, lParam);
	}
	return 0;
}

LRESULT MainWindow::OnInitDialog(LPARAM lParam)
{
	CbAddKeyType(KeyTypeInteger);
	CbAddKeyType(KeyTypeFloat);
	CbAddKeyType(KeyTypeChar);
	CbAddKeyType(KeyTypeString);

	KeyTypeChanged(myTree->GetKeyType());
	TreeTypeChanged(myTree->GetTreeType());
	return 1;
}
