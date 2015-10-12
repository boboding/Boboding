#pragma once

#include "DlgProject.h"
#include "DlgZiJinLiuShui.h"
// CDlgJiZhang 对话框

class CDlgJiZhang : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgJiZhang)

public:
	CDlgJiZhang(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgJiZhang();

// 对话框数据
	enum { IDD = IDD_DIALOG_JIZHANG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SetTabsPosition();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	TabCtrlComplex m_TabCtrl;
	virtual BOOL OnInitDialog();
	public:
CDlgProject m_DlgProject;
CDlgZiJinLiuShui m_DlgZiJinLiuShui;
};
