#pragma once

//#include "DlgProject.h"
//#include "DlgZiJinLiuShui.h"

#include "DlgDesktop.h"
#include "DlgKeyboard.h"
// CDlgTool �Ի���

class CDlgTool : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTool)

public:
	CDlgTool(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTool();

// �Ի�������
	enum { IDD = IDD_DIALOG_TOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
