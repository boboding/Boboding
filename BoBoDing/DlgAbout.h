#pragma once
//#include "stdafx.h"
#include "button\xskinbutton.h"
// CDlgAbout �Ի���

class CDlgAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAbout();

// �Ի�������
	enum { IDD = IDD_DIALOG_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//CxSkinButton m_Button_ctlMin;
	
	//afx_msg void OnBnClickedButtonMin();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
