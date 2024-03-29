#pragma once
#include "afxwin.h"
#include "atlcomtime.h"
#include "orangeedit.h"
#include "resource.h"
#include "gdipbutton\gdipbutton.h"
//#include "gdipbutton\gdipbutton.h"
//#include "BuGu.h"
// CDlgZiJinLiuShuiZhiChu 对话框

class CDlgZiJinLiuShuiZhiChu : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgZiJinLiuShuiZhiChu)

public:
	CDlgZiJinLiuShuiZhiChu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgZiJinLiuShuiZhiChu();

// 对话框数据
	enum { IDD = IDD_DIALOG_ZIJINLIUSHUI_ZHICHU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combo_ctlXiangMu;
	COleDateTime m_oleDateTime_timeRiQi;
	CString m_Edit_strJinE;
	CString m_Edit_strBeiZhu;
	//afx_msg void OnBnClickedButtonSave();
	//afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
	CString m_Combo_strXiangMu;
	COrangeEdit m_Edit_ctlJinE;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CString m_Edit_strDanWei;
	bool m_bIsSave;

	CString DealWithValue(CString strTemp);
	//afx_msg void OnStnClickedStaticSave();
	//afx_msg void OnStnClickedStaticCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGdipButton m_Button_ctlSave;
	CGdipButton m_Button_ctlCancel;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnClose();
};
