// DialogCmd.cpp : Defines the entry point for the application.
//

#include "StdAfx.h"
#include "MsgMap.h"
#include "resource.h"

#include <TCHAR.H>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	CreateDlg(modeless, MAKEINTRESOURCE(IDD_CALCULATOR),NULL,(DLGPROC)GET_PROC(Main));
	return MsgLoop();
}



