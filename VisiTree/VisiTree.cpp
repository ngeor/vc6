// VisiTree.cpp : Defines the entry point for the application.

#include "StdAfx.h"
#include "MainWindow.h"
#include "..\WinObj\WinObj.h"
#include "resource.h"

#define MYCLASSNAME _T("VISITREECLASS")

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow)
{
	// app wraps the current `hInstance`
	WinObj::CInstance app(hInstance);

	// register window class
	WinObj::CWindowClass()
		.Dialog()
		.WithClassName(MYCLASSNAME)
		.WithIcon(IDI_VISITREE)
		.WithSmallIcon(IDI_SMALL)
		.WithMenu(IDC_VISITREE)
		.Register(app);

	// create the main window
	MainWindow mainWindow;
	mainWindow.Create(app, IDD_MAIN);
	mainWindow.Show();

	// message loop
	WinObj::CDialogMessageLoop messageLoop(mainWindow);
	WPARAM result = messageLoop.Run();

	return result;
}
