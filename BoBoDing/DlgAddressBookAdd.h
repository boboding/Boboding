#pragma once

#include "gdipbutton\gdipbutton.h"
#include "afxwin.h"


// CDlgAddressBookAdd �Ի���

class CDlgAddressBookAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddressBookAdd)

public:
	CDlgAddressBookAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddressBookAdd();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADDRESSBOOK_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Edit_strName;
	CString m_Edit_strTel;
	CString m_Edit_strAddress;
	CString m_Edit_strRemark;
	bool m_bIsSave;
//	afx_msg void OnBnClickedButtonSave();

	CString DealWithValue(CString strTemp);
	virtual BOOL OnInitDialog();
	//CxSkinButton m_Button_ctlSave;
	//CxSkinButton m_Button_ctlCancel;
//	afx_msg void OnBnClickedButtonCancel();
	//afx_msg void OnStnClickedStaticSave();
	//afx_msg void OnStnClickedStaticCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGdipButton m_Button_ctlSave;
	CGdipButton m_Button_ctlCancel;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnClose();
	CComboBox m_Combo_ctlCategory;
	CString m_Combo_strCategory;
};
