
// BoBoDingDlg.h : 头文件
//

#pragma once

#include "DlgBase.h"
//#include "DlgSearch.h"
#include "trayicon\trayicon.h"


//#include "DlgDesktopSearch.h"

//#include "DlgTabShopping.h"
// CBoBoDingDlg 对话框
class CBoBoDingDlg : public CDlgBase
{
// 构造
public:
	CBoBoDingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BOBODING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:


	CString GetAppPath();

#define FUNCTIONCOUNT 9
	//原来为6
	afx_msg void OnSize(UINT nType, int cx, int cy);








//protected:
//	//修正移动时窗口的大小
//	void FixMoving(UINT fwSide, LPRECT pRect);
//	//修正改改变窗口大小时窗口的大小
//	void FixSizing(UINT fwSide, LPRECT pRect);
//	//从收缩状态显示窗口
//	void DoShow();
//	//从显示状态收缩窗口
//	void DoHide();
//	//重载函数,只是为了方便调用
//	BOOL SetWindowPos(const CWnd* pWndInsertAfter,
//		LPCRECT pCRect, UINT nFlags = SWP_SHOWWINDOW);
public:
	//afx_msg LRESULT OnNcHitTest(CPoint point);
	//afx_msg void OnTimer(UINT nIDEvent);
	//afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	////afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
//private:
//	BOOL m_isSizeChanged;   //窗口大小是否改变了 
//	BOOL m_isSetTimer;      //是否设置了检测鼠标的Timer
//
//	INT  m_oldWndHeight;    //旧的窗口宽度
//	INT  m_taskBarHeight;   //任务栏高度
//	INT  m_edgeHeight;      //边缘高度
//	INT  m_edgeWidth;       //边缘宽度
//
//	INT  m_hideMode;        //隐藏模式
//	BOOL m_hsFinished;      //隐藏或显示过程是否完成
//	BOOL m_hiding;          //该参数只有在!m_hsFinished才有效
	//真:正在隐藏,假:正在显示

	LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	void RegisterApplicationHotKeys();
public:
	CTrayIcon m_TrayIcon;
	LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);

	//void ShowDialog(int i);
	//afx_msg void OnMainMemo();
	//virtual BOOL DestroyWindow();
	//afx_msg void OnMainAddressbook();
	//afx_msg void OnMainAccount();
	//afx_msg void OnMainShop();
	//afx_msg void OnBobodingdesktop();
	//afx_msg void OnMaindesktop();
	//afx_msg void OnMainWeb();
	//afx_msg void OnMainSet();
	//afx_msg void OnMainAbout();
	afx_msg void OnMainQuit();

	int m_scrWidth,m_scrHeight;  
	RECT m_rect;
	//virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	/*afx_msg void OnStnClickedStatic1();
	afx_msg void OnStnClickedStatic2();
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnStnClickedStatic4();
	afx_msg void OnStnClickedStatic5();
	afx_msg void OnStnClickedStatic6();
	afx_msg void OnStnClickedStatic7();
	afx_msg void OnStnClickedStatic8();*/
	//afx_msg void OnStnClickedStatic9();
	//afx_msg void OnStnClickedStatic10();


	//CDlgDesktopSearch * m_pDlgDesktopSearch;//桌面搜索
	//afx_msg void OnTimer(UINT_PTR nIDEvent);

	//void SetPositionLeft();
	//void SetPositionRight();
	//void SetPositionTop();
	//void SetPositionBottom();

	//void SetVertical();
	//void SetHorizontal();

	//void InitPosition();
	CString GetIniPath();
	//int m_nScreenWidth;
	//int m_nScreenHeight;
	//int m_nTaskBarHeight;//任务栏的高度 
	//int m_nPosition;//0 表示上，1表示下，2表示左，3表示右

	CImage m_Image[9];  
	afx_msg void OnMainShow();
	//afx_msg void OnMainSearch();

	void CreateBobodingDesktop();
	void InitDesktop();
	void SwitchDesktopTo(TCHAR * szDesktopName);
	afx_msg void OnDestroy();
	afx_msg void OnMainMaindesktop();
	afx_msg void OnMainBobodingdesktop();
	afx_msg void OnMainUpdate();
	afx_msg LRESULT OnNcHitTest(CPoint point);

	//void UpdateDatabase();
	void GetUrl(CString sURL);
};
