#include "stdAfx.h"
#include "resource.h"
#include "Frame.h"
#include "MsgMap.h"
#include <stdlib.h>
#include <tchar.h>

int g_nNumFir = 0;//第一个数
int g_nNumSec = 0;//第二个数
int g_nOperSign = 0; //1--"+",2--"-",3--"*",4--"/"
int g_nCount = 0;	//数的位数
int g_nCountNum = 0; //判断是第几个数
int g_nOperCount = 0;//连续运算的次数
int g_nXCount = 0;//判断1/x,sqrt的运算次数
int g_nPercent = 0;
int g_nM = 0; 
int g_nMinusSign  = 0;

double g_dNum = 0.0;//sqrt中的数

char g_szNum[40] = "";

IMPLEMENT_PROC(Main)

BEGIN_MAP(Main)
	 MESSAGE(WM_INITDIALOG,GET_PREFIX(InitDlg))
     MESSAGE(WM_CLOSE,GET_PREFIX(Close))
	 MESSAGE(WM_DESTROY,GET_PREFIX(Destroy))
	 MESSAGE(WM_DRAWITEM,GET_PREFIX(DrawItem))

	 COMCTRL(0)
	 COMCTRL(1)
	 COMCTRL(2)
	 COMCTRL(3)
	 COMCTRL(4)
	 COMCTRL(5)
	 COMCTRL(6)
	 COMCTRL(7)
	 COMCTRL(8)
	 COMCTRL(9)
	 COMCTRL(ADD)
	 COMCTRL(SUB)
	 COMCTRL(RIDE)
	 COMCTRL(DIV)

	 COMCTRL(DELETE)
	 COMCTRL(CE)
	 COMCTRL(EQUAL)
	 COMCTRL(BACKSPACE)
	
END_MAP()

FUN_PREFIX(Destroy)
 {
	 PostQuitMessage(0);
	 return 0;
 }

FUN_PREFIX(InitDlg)
 {
	 HWND hEdit = GetDlgItem(hWnd,IDC_EDIT_MAIN);
	 SetWindowText(hEdit,"0.");
	 return 0;
 }

FUN_PREFIX(Close)
 {
	DestroyWindow(hWnd);
	 return 0;
 }

FUN_PREFIX(DrawItem)
{
	LPDRAWITEMSTRUCT pDis = (LPDRAWITEMSTRUCT) lParam;
	
	if(ODT_BUTTON == pDis->CtlType)
	{
		UINT uState = DFCS_BUTTONPUSH;
		TCHAR szBuf[255] = TEXT("");
		RECT rt = pDis->rcItem; 
		RECT rFocus = pDis->rcItem;
		GetWindowText(pDis->hwndItem,szBuf,50);
		
		if(pDis->itemState & ODS_SELECTED)
		{
			uState |=  DFCS_PUSHED;
			rt.left +=2;
			rt.top +=2;
		}

		if(IDC_BUTTON_BACKSPACE == LOWORD(wParam)||IDC_BUTTON_CE == LOWORD(wParam)||IDC_BUTTON_DELETE == LOWORD(wParam)||IDC_BUTTON_M == LOWORD(wParam)||
			IDC_BUTTON_MC == LOWORD(wParam)||IDC_BUTTON_MR == LOWORD(wParam)||IDC_BUTTON_MS == LOWORD(wParam)||IDC_BUTTON_DIV == LOWORD(wParam)||
			IDC_BUTTON_ADD == LOWORD(wParam)||IDC_BUTTON_SUB == LOWORD(wParam)||IDC_BUTTON_RIDE == LOWORD(wParam)||IDC_BUTTON_EQUAL == LOWORD(wParam))
		{
			SetTextColor(pDis->hDC,RGB(255,0,0));
		}
		else
		{
			SetTextColor(pDis->hDC,RGB(0,0,204));
		}

		DrawFrameControl(pDis->hDC,&(pDis->rcItem),DFC_BUTTON,uState);

		if(pDis->itemState & ODS_FOCUS)
		{
			rFocus.bottom -= 3;
			rFocus.left += 3;
			rFocus.right -= 3;
			rFocus.top += 3;
			DrawFocusRect(pDis->hDC,&rFocus);
		}
		DrawText(pDis->hDC,szBuf,_tcslen(szBuf),&rt,DT_VCENTER |DT_CENTER |DT_SINGLELINE);
		
	}
	return 0;
}

IMPLEMENT_NUMFUN(0)
IMPLEMENT_NUMFUN(1)
IMPLEMENT_NUMFUN(2)
IMPLEMENT_NUMFUN(3)
IMPLEMENT_NUMFUN(4)
IMPLEMENT_NUMFUN(5)
IMPLEMENT_NUMFUN(6)
IMPLEMENT_NUMFUN(7)
IMPLEMENT_NUMFUN(8)
IMPLEMENT_NUMFUN(9)

IMPLEMENT_OPERFUN(ADD,1)
IMPLEMENT_OPERFUN(SUB,2)
IMPLEMENT_OPERFUN(RIDE,3)
IMPLEMENT_OPERFUN(DIV,4)

DECLARE_FUN(EQUAL)
{
	HWND hEdit = GetDlgItem(GetParent(hCtrl),IDC_EDIT_MAIN);
	char szBuff[255] = ""; 
	
	if ( 1 == g_nOperSign)
	{
		g_nNumFir = g_nNumFir + g_nNumSec;
	}
	
	if ( 2 == g_nOperSign)
	{
		g_nNumFir = g_nNumFir - g_nNumSec;
	}
	
	if ( 3 == g_nOperSign)
	{
		g_nNumFir = g_nNumFir * g_nNumSec;
	}
	
	if ( 4 == g_nOperSign)
	{
		if(g_nNumSec != 0)
		{
			g_nNumFir = g_nNumFir / g_nNumSec;
		}
		else
		{
			SetWindowText(hEdit,"除数不能为零");
		}
		
	}
	
	SetWindowText(hEdit,itoa(g_nNumFir,szBuff,10));
	g_nNumSec = 0;
	
	g_nOperSign = 0;
	g_nOperCount = 0;
	g_nCountNum = 0;
	g_nCount = 0;	
	
	return 1;
	
}

DECLARE_FUN(CE)
{
	HWND hEdit = GetDlgItem(GetParent(hCtrl),IDC_EDIT_MAIN);
	SetWindowText(hEdit,"0");
	g_nNumSec = 0;
	g_nCount = 0;
	g_nCountNum = 1;
	
	return 1;
}

DECLARE_FUN(DELETE)
{
	HWND hEdit = GetDlgItem(GetParent(hCtrl),IDC_EDIT_MAIN);
	SetWindowText(hEdit,"0.");
	
	g_nOperSign = 0;
	g_nCountNum = 0;
	g_nOperCount = 0;
	g_nXCount = 0;
	g_nCount = 0;
	g_nNumFir = 0;
	g_nNumSec = 0;
	return 1;
}

DECLARE_FUN(BACKSPACE)
{
	HWND hEdit = GetDlgItem(GetParent(hCtrl),IDC_EDIT_MAIN);
	NumberBack(g_nCount--,g_nCountNum);
	
	if (g_nCount < 0)
	{
		g_nCount = 0;
	}
	
	if(0 == g_nCountNum)
	{
		SetWindowText(hEdit,itoa(g_nNumFir , g_szNum, 10));
	}
	if (1 == g_nCountNum)
	{
		SetWindowText(hEdit,itoa(g_nNumSec , g_szNum, 10));
	}
	return 0;
}

