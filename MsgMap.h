#ifndef __MSGMAP_H__
#define __MSGAMP_H__
#include "Frame.h"
#include "Control.h"

extern int g_nNumFir;//第一个数
extern int g_nNumSec ;//第二个数
extern int g_nOperSign ; //1--"+",2--"-",3--"*",4--"/"
extern int g_nCount ;	//数的位数
extern int g_nCountNum ; //判断是第几个数
extern int g_nOperCount ;//连续运算的次数
extern int g_nXCount ;//判断1/x,sqrt的运算次数
extern int g_nPercent ;
extern int g_nM ; 
extern int g_nMinusSign  ;

extern double g_dNum ;//sqrt中的数

extern char g_szNum[40];

DECLARE_MSGSTRUCT(Main)
DECLARE_PROC(Main)

FUN_PREFIX(Destroy);
FUN_PREFIX(InitDlg);
FUN_PREFIX(Close);
FUN_PREFIX(DrawItem);

DECLARE_FUN(0);
DECLARE_FUN(1);
DECLARE_FUN(2);
DECLARE_FUN(3);
DECLARE_FUN(4);
DECLARE_FUN(5);
DECLARE_FUN(6);
DECLARE_FUN(7);
DECLARE_FUN(8);
DECLARE_FUN(9);

DECLARE_FUN(ADD);
DECLARE_FUN(SUB);
DECLARE_FUN(RIDE);
DECLARE_FUN(DIV);

DECLARE_FUN(DELETE);
DECLARE_FUN(CE);
DECLARE_FUN(EQUAL);
DECLARE_FUN(BACKSPACE);



#endif