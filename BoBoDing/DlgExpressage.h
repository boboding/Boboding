#pragma once
#include "explorer_shopping.h"


// CDlgExpressage �Ի���

class CDlgExpressage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgExpressage)

public:
	CDlgExpressage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgExpressage();

// �Ի�������
	enum { IDD = IDD_DIALOG_EXPRESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExplorer_shopping m_Explorer_ctlExpressage;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
