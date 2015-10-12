#pragma once

#include "UGProjectEdit.h"
#include "button\xskinbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
//#include "button\xskinbutton.h"
//#include "button\xskinbutton.h"

// CDlgProject 窗体视图

class CDlgProject : public CDialogEx 
{
	DECLARE_DYNCREATE(CDlgProject)

public:
	CDlgProject();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgProject();

public:
	enum { IDD = IDD_DIALOG_PROJECT };
//#ifdef _DEBUG
//	virtual void AssertValid() const;
//#ifndef _WIN32_WCE
//	virtual void Dump(CDumpContext& dc) const;
//#endif
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedButtonPrint2();
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//virtual void OnInitialUpdate();

	CUGProjectEdit m_ctrl;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int m_nSelect;
	afx_msg void OnBnClickedRadioAll();
	afx_msg void OnBnClickedRadioShouru();
	afx_msg void OnBnClickedRadioZhichu();
	afx_msg void OnBnClickedButtonNew();

//	afx_msg void OnBnClickedButtonChange();
	virtual BOOL OnInitDialog();
	//CxSkinButton m_Button_ctlNew;
	//CxSkinButton m_Button_ctlReturn;
	//CxSkinButton m_Button_ctlMin;
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnBnClickedButtonMin();
	//afx_msg void OnBnClickedButtonReturn();
	CGdipButton m_Button_ctlNew;
	CGdipButton m_Button_ctlChange;
	CGdipButton m_Button_ctlDel;
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDel();
};


