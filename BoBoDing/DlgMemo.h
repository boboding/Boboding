#pragma once

#include "UGMemo.h"
#include "Edit\EditWithButton.h"
#include "button\xskinbutton.h"
#include "afxwin.h"
#include "resource.h"
#include "list\listctrlcl.h"
#include "gdipbutton\gdipbutton.h"
#include "gdipbutton\gdipbutton.h"
// CDlgMemo 对话框

typedef struct {
	LVITEM* plvi;
	CString sCol2;
} lvItem, *plvItem;


#define WM_USER_EDITWITHBUTTON_CLICKED	(WM_USER + 3000)
class CDlgMemo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMemo)

public:
	CDlgMemo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMemo();

// 对话框数据
	enum { IDD = IDD_DIALOG_MEMO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CUGMemo m_ctrl;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CEditWithButton m_Edit_ctlQuery;
	afx_msg void OnBnClickedButtonNew();
	afx_msg LRESULT OnQuery(WPARAM wParam, LPARAM lParam);
	CGdipButton m_Button_ctlNew;
	CComboBox m_Combo_ctlQuery;
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);


	//CxSkinButton m_Button_ctlMin;
//	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnEnUpdateEditQuery();
	CListCtrlCl m_List_ctlTitle;
	CGdipButton m_Button_ctlChange;
	CGdipButton m_Button_ctlDel;
	afx_msg void OnNMClickListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeleditListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDel();

	void InitList();
	afx_msg void OnLvnBegindragListTitle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);



	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);





	//CImageList* m_pDragImage;	//For creating and managing the drag-image
	//BOOL		m_bDragging;	//T during a drag operation
	//int			m_nDragIndex;	//Index of selected item in the List we are dragging FROM
	//int			m_nDropIndex;	//Index at which to drop item in the List we are dropping ON
	//CWnd*		m_pDropWnd;

	//CListCtrlCl* m_pDragList;		//Which ListCtrl we are dragging FROM
	//CListCtrlCl* m_pDropList;		//Which ListCtrl we are dropping ON

	//void DropItemOnList(CListCtrlCl* pDragList, CListCtrlCl* pDropList);

	//CString m_strCategoryOldName;//
	CString DealWithValue(CString strTemp);

	
	CString GetDefaultCategory();//删除类别时，属于该类别的记录 更新为 此类别
	afx_msg void OnLvnBeginlabeleditListTitle(NMHDR *pNMHDR, LRESULT *pResult);

	bool IsSame(CString strCompare);
	//CEdit* pEdit;
};
