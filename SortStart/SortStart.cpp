// SortStart
// Based on:
// {
// NGSortStart
// Version 0.0.1 (16/6/1999)
// Author: Nick Georgiou
// }

#include "StdAfx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    LPCTSTR sConfirmSort = _T("Do you want to sort the Start Menu?");
    LPCTSTR sQuestion = _T("Question");
    LPCTSTR sError = _T("Error");
    LPCTSTR sErrRegistryRead   = _T("Couldn't read a system registry key");
    LPCTSTR sErrRegistryDelete = _T("Couldn't delete a system registry key");
    LPCTSTR sReboot = _T("SortStart has successfully sorted the Start Menu! For this change to take efffect you must restart your computer. Do you want to restart your computer now?");

    // get the user's OK
    if (MessageBox(NULL, sConfirmSort, sQuestion, MB_ICONQUESTION | MB_YESNO) == IDYES) {
        HKEY h;
        // open the proper registry key
        bool success = RegOpenKeyEx(HKEY_CURRENT_USER,
            _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer"),
            0, KEY_ALL_ACCESS, &h) == ERROR_SUCCESS;
        // did that work?
        if (!success) {
            MessageBox(NULL, sErrRegistryRead, sError, MB_ICONERROR);
        }
        else {
            // delete the subkey MenuOrder and there you go!!!
            success = RegDeleteKey(h, _T("MenuOrder")) == ERROR_SUCCESS;
            // God, I hope that worked...
            if (!success) {
                MessageBox(NULL, sErrRegistryDelete, sError, MB_ICONERROR);
                // key probably open so we just close it here
                RegCloseKey(h);
            }
            else {
                // Great, close the registry key!
                RegCloseKey(h);
                // Tell him that he MUST reboot
                if (MessageBox(NULL, sReboot, sQuestion, MB_ICONQUESTION or MB_YESNO) == IDYES) {
                    ExitWindowsEx(EWX_REBOOT, 0);
                }
            }
        }
    }
	return 0;
}
