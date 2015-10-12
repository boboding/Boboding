#pragma once
#include "afxeditbrowsectrl.h"
#include "button\xskinbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
// CDlgSet 对话框

class CDlgSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSet)

public:
	CDlgSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CMFCEditBrowseCtrl m_Edit_ctlBackup;
		CMFCEditBrowseCtrl m_Edit_ctlResume;


	CString m_Edit_strBackup;

	CString m_Edit_strResume;

	afx_msg void OnBnClickedButtonBackup();
	afx_msg void OnBnClickedButtonResume();
		HICON m_hIconFile ;
		HICON m_hIconFolder ;
	bool DirExist(const TCHAR  *pszDirName);

	//afx_msg void OnBnClickedButtonMin();
		//CxSkinButton m_Button_ctlMin;
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnBnClickedCheckStart();
		BOOL m_Check_bStart;
		int m_nRadio_nShow;
	/*	afx_msg void OnBnClickedRadio3();
		afx_msg void OnBnClickedRadio4();
		afx_msg void OnBnClickedRadio5();
		afx_msg void OnBnClickedRadio6();*/

		CString GetIniPath();
		CGdipButton m_Button_ctlBackup;
		CGdipButton m_Button_ctlResume;
};
