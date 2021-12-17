// SortStart
// Based on:
// {
// NGSortStart
// Version 0.0.1 (16/6/1999)
// Author: Nick Georgiou
// }

#include "StdAfx.h"

bool Confirm(LPCTSTR question)
{
	return MessageBox(NULL, question, _T("Question"), MB_ICONQUESTION | MB_YESNO) == IDYES;
}

void Error(LPCTSTR message)
{
	MessageBox(NULL, message, _T("Error"), MB_ICONERROR);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPCTSTR sConfirmSort       = _T("Do you want to sort the Start Menu?");
	LPCTSTR sErrRegistryRead   = _T("Couldn't read a system registry key");
	LPCTSTR sErrRegistryDelete = _T("Couldn't delete a system registry key");
	LPCTSTR sReboot = _T("SortStart has successfully sorted the Start Menu! For this change to take efffect you must ")
					  _T("restart your computer. Do you want to restart your computer now?");

	// get the user's OK
	if (Confirm(sConfirmSort))
	{
		HKEY h;
		// open the proper registry key
		bool success = RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer"), 0,
		                            KEY_ALL_ACCESS, &h) == ERROR_SUCCESS;
		// did that work?
		if (!success)
		{
			Error(sErrRegistryRead);
		}
		else
		{
			// delete the subkey MenuOrder and there you go!!!
			success = RegDeleteKey(h, _T("MenuOrder")) == ERROR_SUCCESS;
			// close the key
			RegCloseKey(h);
			// God, I hope that worked...
			if (!success)
			{
				Error(sErrRegistryDelete);
			}
			else
			{
				// Tell him that he MUST reboot
				if (Confirm(sReboot))
				{
					ExitWindowsEx(EWX_REBOOT, 0);
				}
			}
		}
	}
	return 0;
}
