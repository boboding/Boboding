#pragma once

#include "UGWebsite.h"
#include "Edit\EditWithButton.h"
#include "button\xskinbutton.h"
#include "afxwin.h"
#include "groupbox\ultimategroupbox.h"
#include "colorstatic\xcolorstatic.h"
#include "button\xskinbutton.h"
#include "list\listctrlcl.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
// CDlgWebsite 对话框
#define WM_USER_EDITWITHBUTTON_CLICKED	(WM_USER + 3000)
class CDlgWebsite : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWebsite)

public:
	CDlgWebsite(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWebsite();

// 对话框数据
	enum { IDD = IDD_DIALOG_WEBSITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CUGWebsite m_ctrl;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CEditWithButton m_Edit_ctlQuery;
	afx_msg void OnBnClickedButtonNew();
	afx_msg LRESULT OnQuery(WPARAM wParam, LPARAM lParam);
	//CxSkinButton m_Button_ctlNew;
	CComboBox m_Combo_ctlQuery;
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);


	//CxSkinButton m_Button_ctlMin;
	//afx_msg void OnBnClickedButtonMin();
	afx_msg void OnEnUpdateEditQuery();
	//CUltimateGroupBox m_GroupBox_ctlGroup;
	//CXColorStatic m_Static_ctlSeparation;
	//CStatic m_Static_ctlSeparation;
	//CxSkinButton m_Button_ctlFavorite;

	/********************************************************************************/
	BOOL m_Check_bGoogle;
	BOOL m_Check_bBaiDu;
	BOOL m_Check_bSouGou;
	BOOL m_Check_bYouDao;
	CString GetIniPath();
	afx_msg void OnStnClickedStaticSearch();
	CString m_Edit_strSearch;

	afx_msg void OnBnClickedCheckGoogle();
	afx_msg void OnBnClickedCheckBaidu();
	afx_msg void OnBnClickedCheckSougou();
	afx_msg void OnBnClickedCheckYoudao();

	afx_msg void OnBnClickedCheckStart();
	afx_msg void OnBnClickedButtonFavorite();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrlCl m_List_ctlTitle;
	CGdipButton m_Button_ctlNew;
	CGdipButton m_Button_ctlFavorites;
	CGdipButton m_Button_ctlChange;
	CGdipButton m_Button_ctlDel;

	
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnNMClickListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeleditListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	public:
	CString GetDefaultCategory();//删除类别时，属于该类别的记录 更新为 此类别
	bool IsSame(CString strCompare);
	void InitList();
	CString DealWithValue(CString strTemp);
};
