#pragma once
#include "explorer_shopping.h"


// CDlgNavigation 对话框

class CDlgNavigation : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNavigation)

public:
	CDlgNavigation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNavigation();

// 对话框数据
	enum { IDD = IDD_DIALOG_NAVIGATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExplorer_shopping m_Explorer;
	virtual BOOL OnInitDialog();

	//afx_msg void OnDocumentComplete(LPDISPATCH pDisp, VARIANT FAR* URL);
	
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT* URL);
	virtual void PreInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
};
