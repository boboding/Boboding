#pragma once

//#include "DlgProject.h"
//#include "DlgZiJinLiuShui.h"

#include "DlgDesktop.h"
#include "DlgKeyboard.h"
// CDlgTool 对话框

class CDlgTool : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTool)

public:
	CDlgTool(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTool();

// 对话框数据
	enum { IDD = IDD_DIALOG_TOOL };

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
//CDlgProject m_DlgProject;
//CDlgZiJinLiuShui m_DlgZiJinLiuShui;

		CDlgDesktop m_DlgDesktop;
		CDlgKeyboard m_DlgKeyboard;
};
