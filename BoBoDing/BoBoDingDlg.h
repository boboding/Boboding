
// BoBoDingDlg.h : ͷ�ļ�
//

#pragma once

#include "DlgBase.h"
//#include "DlgSearch.h"
#include "trayicon\trayicon.h"


//#include "DlgDesktopSearch.h"

//#include "DlgTabShopping.h"
// CBoBoDingDlg �Ի���
class CBoBoDingDlg : public CDlgBase
{
// ����
public:
	CBoBoDingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BOBODING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	//ԭ��Ϊ6
	afx_msg void OnSize(UINT nType, int cx, int cy);








//protected:
//	//�����ƶ�ʱ���ڵĴ�С
//	void FixMoving(UINT fwSide, LPRECT pRect);
//	//�����ĸı䴰�ڴ�Сʱ���ڵĴ�С
//	void FixSizing(UINT fwSide, LPRECT pRect);
//	//������״̬��ʾ����
//	void DoShow();
//	//����ʾ״̬��������
//	void DoHide();
//	//���غ���,ֻ��Ϊ�˷������
//	BOOL SetWindowPos(const CWnd* pWndInsertAfter,
//		LPCRECT pCRect, UINT nFlags = SWP_SHOWWINDOW);
public:
	//afx_msg LRESULT OnNcHitTest(CPoint point);
	//afx_msg void OnTimer(UINT nIDEvent);
	//afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	////afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
//private:
//	BOOL m_isSizeChanged;   //���ڴ�С�Ƿ�ı��� 
//	BOOL m_isSetTimer;      //�Ƿ������˼������Timer
//
//	INT  m_oldWndHeight;    //�ɵĴ��ڿ��
//	INT  m_taskBarHeight;   //�������߶�
//	INT  m_edgeHeight;      //��Ե�߶�
//	INT  m_edgeWidth;       //��Ե���
//
//	INT  m_hideMode;        //����ģʽ
//	BOOL m_hsFinished;      //���ػ���ʾ�����Ƿ����
//	BOOL m_hiding;          //�ò���ֻ����!m_hsFinished����Ч
	//��:��������,��:������ʾ

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


	//CDlgDesktopSearch * m_pDlgDesktopSearch;//��������
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
	//int m_nTaskBarHeight;//�������ĸ߶� 
	//int m_nPosition;//0 ��ʾ�ϣ�1��ʾ�£�2��ʾ��3��ʾ��

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
