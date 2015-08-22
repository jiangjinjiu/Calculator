#ifndef __MSGMAP_H__
#define __MSGAMP_H__
#include "Frame.h"
#include "Control.h"

extern int g_nNumFir;//��һ����
extern int g_nNumSec ;//�ڶ�����
extern int g_nOperSign ; //1--"+",2--"-",3--"*",4--"/"
extern int g_nCount ;	//����λ��
extern int g_nCountNum ; //�ж��ǵڼ�����
extern int g_nOperCount ;//��������Ĵ���
extern int g_nXCount ;//�ж�1/x,sqrt���������
extern int g_nPercent ;
extern int g_nM ; 
extern int g_nMinusSign  ;

extern double g_dNum ;//sqrt�е���

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