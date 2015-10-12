#pragma once
#include "afxwin.h"
#include "list\listctrlcl.h"
#include "gdipbutton\gdipbutton.h"
#include "resource.h"



// CDlgNote 对话框

class CDlgNote : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNote)

public:
	CDlgNote(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNote();

// 对话框数据
	enum { IDD = IDD_DIALOG_NOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrlCl m_List_ctlTitle;
	//CImageButton *mp_Button_ctlNew;
	CGdipButton m_Button_ctlNew;
	CEdit m_Edit_ctlTitle;
	CEdit m_Edit_ctlContent;
	CGdipButton m_Button_ctlSave;
	CGdipButton m_Button_ctlCancel;
	afx_msg void OnNMClickListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_Edit_strContent;

	CFont   m_Font;
	CString m_Edit_strTitle;
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnEnChangeEditTitle();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
