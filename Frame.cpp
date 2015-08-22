#include "StdAfx.h"
#include "Frame.h"
#include <TCHAR.H>

WNDCLASS *InitWndClass(WNDPROC WndProc, TCHAR *pClassName)
{
	
	static WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW; 
    wc.lpfnWndProc = WndProc; 
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hInstance = GetModuleHandle(NULL); 
    wc.hIcon = NULL; 
    wc.hCursor = LoadCursor(NULL,IDC_ARROW); 
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); 
    wc.lpszMenuName = NULL; 
    wc.lpszClassName = pClassName;

	return &wc;
}

BOOL InitWnd(WNDCLASS *pClass, TCHAR *pWndName)
{
	if(NULL != pClass)
	{
		if(!RegisterClass(pClass))
		{
			return FALSE;
		}

		HWND hMain=CreateWindow(pClass->lpszClassName, 
							pWndName != NULL ?pWndName:TEXT("Frame"),
							WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
							CW_USEDEFAULT,NULL,NULL,pClass->hInstance,NULL);
		if(!hMain)
		{
			return FALSE;
		}
	
		ShowWindow(hMain,SW_SHOW);
		return TRUE;
	}
	return FALSE;
}

LONG CreateDlg(DLG_MODE mode, LPCTSTR lpTemplate, HWND hWndParent,DLGPROC DlgProc)
{
	switch(mode)
	{
		case modeless:
			{
				HWND hWnd = CreateDialog(GetModuleHandle(NULL), lpTemplate, hWndParent, DlgProc);
				ShowWindow(hWnd, SW_SHOW);
				return (LONG)hWnd;
			}
		case modal:
			{
				return DialogBox(GetModuleHandle(NULL), lpTemplate, hWndParent, DlgProc);
			}
		default:
			break;
	}
	return -1;
}

int MsgLoop()
{
	MSG msg;

	while(GetMessage(&msg,NULL,0,0))
	{ 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
