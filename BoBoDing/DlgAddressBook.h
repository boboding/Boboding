#pragma once

#include "UGAddressBook.h"
#include "Edit\EditWithButton.h"
#include "button\xskinbutton.h"
#include "afxwin.h"
#include "gdipbutton\gdipbutton.h"
#include "list\listctrlcl.h"
#include "gdipbutton\gdipbutton.h"
// CDlgAddressBook �Ի���
#define WM_USER_EDITWITHBUTTON_CLICKED	(WM_USER + 3000)
class CDlgAddressBook : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddressBook)

public:
	CDlgAddressBook(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddressBook();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADDRESSBOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CUGAddressBook m_ctrl;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CEditWithButton m_Edit_ctlQuery;
	afx_msg void OnBnClickedButtonNew();
	afx_msg LRESULT OnQuery(WPARAM wParam, LPARAM lParam);
	CGdipButton m_Button_ctlNew;
	CComboBox m_Combo_ctlQuery;
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);


	//CGdipButton m_Button_ctlMin;
//	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnEnUpdateEditQuery();


	CListCtrlCl m_List_ctlTitle;
	CGdipButton m_Button_ctlChange;
	CGdipButton m_Button_ctlDel;
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonExport();
	CGdipButton m_Button_ctlExport;
	afx_msg void OnNMClickListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeleditListTitle(NMHDR *pNMHDR, LRESULT *pResult);

	CString GetDefaultCategory();//ɾ�����ʱ�����ڸ����ļ�¼ ����Ϊ �����
	bool IsSame(CString strCompare);
	void InitList();
	CString DealWithValue(CString strTemp);
};
