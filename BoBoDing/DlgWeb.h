#pragma once

//#include "DlgProject.h"
//#include "DlgZiJinLiuShui.h"

#include "DlgWebsite.h"
#include "DlgNavigation.h"
// CDlgWeb �Ի���

class CDlgWeb : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWeb)

public:
	CDlgWeb(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWeb();

// �Ի�������
	enum { IDD = IDD_DIALOG_WEB };

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

		CDlgWebsite m_DlgWebsite;
		CDlgNavigation m_DlgNavigation;
//CDlgProject m_DlgProject;
//CDlgZiJinLiuShui m_DlgZiJinLiuShui;
		virtual BOOL PreTranslateMessage(MSG* pMsg);
};
