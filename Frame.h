#ifndef __FRAME_H__
#define __FRAME_H__

typedef LRESULT (*PMSGFUN)(HWND, WPARAM, LPARAM);
typedef LRESULT (*PCTRL)(HWND hCtrl);

struct MSGMAP
{
	UINT uMsg;
	UINT uID;
	int uNotify;

	PMSGFUN MsgFun;
};

enum DLG_MODE{modeless, modal};

LONG CreateDlg(DLG_MODE mode, LPCTSTR lpTemplate, HWND hWndParent,DLGPROC DlgProc);

WNDCLASS *InitWndClass(WNDPROC WndProc, TCHAR *pClassName);
BOOL InitWnd(WNDCLASS *pClass, TCHAR *pWndName);
int MsgLoop();

#define DECLARE_MSGSTRUCT(name) extern MSGMAP g_##name##Map[];
#define GET_MSGSTRUCT(name) g_##name##Map

#define BEGIN_MAP(name) MSGMAP g_##name##Map[] = {
#define MESSAGE(id, MsgFun) {id, 0, 0, MsgFun},
#define COMCTRL(id) {WM_COMMAND, IDC_BUTTON_##id, BN_CLICKED, (PMSGFUN)Btn##id##_Fun},
#define END_MAP() {WM_NULL,0,0,NULL}};

////////////////////////////////////////////////
#define DECLARE_FUN(id) LRESULT Btn##id##_Fun(HWND hCtrl)

#define IMPLEMENT_NUMFUN(id)\
	LRESULT Btn##id##_Fun(HWND hCtrl)\
	{\
		return BtnFun(id,hCtrl);\
	}\

#define IMPLEMENT_OPERFUN(id,sign)\
	LRESULT Btn##id##_Fun(HWND hCtrl)\
	{\
		return BtnOperation_Fun(sign, hCtrl);\
	}\


/////////////////////////////////////////
#define  FUN_PREFIX(msg) LRESULT OnMain##msg(HWND hWnd, WPARAM wParam, LPARAM lParam)
#define  GET_PREFIX(msg) OnMain##msg

#define DECLARE_PROC(name) LRESULT CALLBACK name##Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#define GET_PROC(name) name##Proc

#define IMPLEMENT_PROC(name)\
	LRESULT CALLBACK name##Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)\
	{\
		MSGMAP *pMsg = GET_MSGSTRUCT(name);\
		if (NULL != pMsg->MsgFun)\
		{\
			while (WM_NULL != pMsg->uMsg)\
			{\
				if(uMsg == pMsg->uMsg)\
				{\
					if(WM_COMMAND == uMsg)\
					{\
						if (HIWORD(wParam) == pMsg->uNotify)\
						{\
							if(LOWORD(wParam) == pMsg->uID)\
							{\
								return ((PCTRL)(pMsg->MsgFun))(((HWND)lParam) ? ((HWND)lParam) : hWnd);\
							}\
						}\
						pMsg++;\
						continue;\
					}\
					return pMsg->MsgFun(hWnd, wParam, lParam);\
				}\
				pMsg++;\
			}\
		}\
		TCHAR szClassName[255] = TEXT("");\
		GetClassName(hWnd, szClassName , 255);\
		return _tcscmp(szClassName, TEXT("#32770")) ? DefWindowProc(hWnd, uMsg, wParam, lParam) : FALSE;\
	}


#endif