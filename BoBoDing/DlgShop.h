#pragma once

//#include "DlgProject.h"
//#include "DlgZiJinLiuShui.h"

#include "DlgShopMall.h"
//#include "DlgNavigation.h"
// CDlgShop 对话框

class CDlgShop : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShop)

public:
	CDlgShop(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShop();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOP };

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

		//CDlgShopsite m_DlgShopsite;
		CDlgShopMall m_DlgShopMall;
//CDlgProject m_DlgProject;
//CDlgZiJinLiuShui m_DlgZiJinLiuShui;
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
};
