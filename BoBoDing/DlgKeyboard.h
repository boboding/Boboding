#pragma once
#include "ledscreen\ledscreen.h"
#include "ledscreen\ledscreen.h"
#include "ledscreen\ledscreen.h"


// CDlgKeyboard 对话框

class CDlgKeyboard : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgKeyboard)

public:
	CDlgKeyboard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgKeyboard();

// 对话框数据
	enum { IDD = IDD_DIALOG_KEYBOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CLEDScreen m_Static_ctlKeyboard;
	CLEDScreen m_Static_ctlLeft;
	CLEDScreen m_Static_ctlRight;
	virtual BOOL OnInitDialog();

	typedef BOOL (* STARTHOOKPROC)(HWND hWnd);
	typedef BOOL (* STOPHOOKPROC)();
	typedef long (* GETLBUTTONCOUNTPROC)();
	typedef long (* GETRBUTTONCOUNTPROC)();
	typedef long (* GETKEYBOARDCOUNTPROC)();
	typedef BOOL (* RESETMOUSECOUNTPROC)();
	typedef BOOL (* RESETKEYBOARDCOUNTPROC)();

	STARTHOOKPROC			pStartHook;
	STOPHOOKPROC			pStopHook;
	GETLBUTTONCOUNTPROC		pGetLButtonCount;
	GETRBUTTONCOUNTPROC		pGetRButtonCount;
	GETKEYBOARDCOUNTPROC	pGetKeyBoardCount;
	RESETMOUSECOUNTPROC     pResetMouseCount;
	RESETKEYBOARDCOUNTPROC  pResetKeyBoardCount;

public:
	afx_msg LRESULT OnMyNotify(WPARAM wParam,LPARAM lParam);
	afx_msg void OnStartHook();

	afx_msg void OnExit();
private:
	long nLButtonDown;
	long nRButtonDown;
	long nKeyDown;
	HMODULE hMod;
	
public:
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
