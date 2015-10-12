#pragma once
#include "explorer_shopping.h"


// CDlgExpressage 对话框

class CDlgExpressage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgExpressage)

public:
	CDlgExpressage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgExpressage();

// 对话框数据
	enum { IDD = IDD_DIALOG_EXPRESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExplorer_shopping m_Explorer_ctlExpressage;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
