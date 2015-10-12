#pragma once

//#include "button\xskinbutton.h"
#include "gdipbutton\gdipbutton.h"
//#include "gdipbutton\gdipbutton.h"
// CDlgDesktop 对话框

class CDlgDesktop : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDesktop)

public:
	CDlgDesktop(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDesktop();

// 对话框数据
	enum { IDD = IDD_DIALOG_DESKTOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	/*afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedStaticDesktop1();
	afx_msg void OnStnClickedStaticDesktop2();*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//void LoadDesktop1Move();
	//void LoadDesktop2Move();
	//void LoadDesktop1();
	//void LoadDesktop2();
	/*void CreateBobodingDesktop();
	void InitDesktop();
	void SwitchDesktopTo(TCHAR * szDesktopName);
	afx_msg void OnDestroy()*/;
	//CxSkinButton m_Button_ctlMin;
	//afx_msg void OnBnClickedButtonMin();

	//void RegisterApplicationHotKeys();

	/*LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);*/
	CGdipButton m_Button_ctlDesktop1;
	CGdipButton m_Button_ctlDesktop2;
	afx_msg void OnBnClickedButtonDesktop1();
	afx_msg void OnBnClickedButtonDesktop2();

	void ImageFromIDResource(CImage& image, UINT nID, LPCTSTR lpType);
};
