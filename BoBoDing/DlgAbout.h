#pragma once
//#include "stdafx.h"
#include "button\xskinbutton.h"
// CDlgAbout 对话框

class CDlgAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAbout();

// 对话框数据
	enum { IDD = IDD_DIALOG_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//CxSkinButton m_Button_ctlMin;
	
	//afx_msg void OnBnClickedButtonMin();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
