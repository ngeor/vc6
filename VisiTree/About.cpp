#include "StdAfx.h"
#include "About.h"

AboutDialog::AboutDialog() {}

AboutDialog::~AboutDialog() {}

// Mesage handler for about box.
LRESULT AboutDialog::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(LOWORD(wParam));
				return TRUE;
			}
			break;
	}
	return CDialog::OnMessage(message, wParam, lParam);
}
