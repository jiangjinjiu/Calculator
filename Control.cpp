#include "StdAfx.h"
#include "Control.h"
#include "resource.h"
#include <STDLIB.H>

LRESULT BtnFun(int Num, HWND hCtrl)
{
	HWND hEdit = GetDlgItem(GetParent(hCtrl),IDC_EDIT_MAIN);
	
	NUmber(Num,g_nCount++,g_nCountNum);
	if(0 == g_nCountNum)
	{
		SetWindowText(hEdit,itoa(g_nNumFir , g_szNum, 10));
	}
	
	if (1 == g_nCountNum)
	{
		SetWindowText(hEdit,itoa(g_nNumSec , g_szNum, 10));
	}

	return TRUE;
}

LRESULT BtnOperation_Fun(int nOperSign, HWND hCtrl)
{
	HWND hEdit = GetDlgItem(GetParent(hCtrl),IDC_EDIT_MAIN);
	char szBuff[255] = ""; 
	
	if (g_nOperSign != 0)
	{
		Oper(g_nOperSign);
		SetWindowText(hEdit,itoa(g_nNumFir,szBuff,10));
	}
	
	g_nOperSign = nOperSign;
	g_nCountNum++;
	g_nOperCount++;
	g_nCount = 0;
	ArrayClear(g_szNum);
	
	if (g_nOperCount > 1)
	{
		g_nCountNum--;
	}
	
	return 1;

}


void NUmber(int nButtonNum,int nCount,int nNum)
{
	int *npTemp = NULL;
	if( 0 == nNum)
	{
		npTemp = &g_nNumFir; 	
	}
	if (1 == nNum)
	{
		npTemp = &g_nNumSec;
	}
	
	if (0 == nCount)
	{
		*npTemp = nButtonNum;
	}
	else if (nCount > 0)
	{
		*npTemp = *npTemp * 10 + nButtonNum; 
	}
}

void  Oper(int OperSign)
{
	//int nTemp = 0;
	if (1 == OperSign)
	{
		g_nNumFir = g_nNumFir + g_nNumSec;	
	}
	if (2 == OperSign)
	{
		g_nNumFir = g_nNumFir - g_nNumSec;
	}
	if (3 == OperSign)
	{
		g_nNumFir = g_nNumFir * g_nNumSec;
	}
	if (4 == OperSign)
	{
		g_nNumFir = g_nNumFir / g_nNumSec;
	}
	g_nNumSec = 0;
}

void NumberBack(int nCount,int nNum)
{
	int *npTemp = NULL;
	if( 0 == nNum)
	{
		npTemp = &g_nNumFir; 	
	}
	if (1 == nNum)
	{
		npTemp = &g_nNumSec;
	}
	
	if (nCount <= 0)
	{
		*npTemp = 0;
	}
	else if (1 == nCount)
	{
		*npTemp = 0;
	}
	else if(nCount > 1)
	{
		*npTemp = *npTemp / 10 ; 
	}
}

void ArrayClear(char *pArray)
{
	int i = 0;
	for (i=0; i<40; i++)
	{
		pArray[i] = NULL;
	}
}