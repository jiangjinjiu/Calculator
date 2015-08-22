#ifndef __CONTROL_H__
#define __CONTROL_H__
#include "Frame.h"
#include "MsgMap.h"

LRESULT BtnFun(int Num, HWND hCtrl);
LRESULT BtnOperation_Fun(int nOperSign, HWND hCtrl);
void NUmber(int nButtonNum,int nCount,int nNum);
void NumberBack(int nCount,int nNum);
void  Oper(int OperSign);
void ArrayClear(char *pArray);

#endif