// ListCtrlCl.cpp : 实现文件
//

#include "stdafx.h"

#include "ListCtrlCl.h"

struct stColor
{
	int nRow;
	int nCol;
	COLORREF rgb;
};
// CListCtrlCl

IMPLEMENT_DYNAMIC(CListCtrlCl, CListCtrl)

CListCtrlCl::CListCtrlCl()
: m_nRowHeight(0)
, m_fontHeight(12)
, m_fontWith(0)

///***********************************************/
//,m_nDropIndex(-1),
//m_pDragImage(NULL),
//m_nPrevDropIndex(-1),
//m_uPrevDropState(NULL),
//m_uScrollTimer(0),
//m_ScrollDirection(scrollNull),
//m_dwStyle(NULL)
///***********************************************/
{
	m_color = RGB(0,0,0);

	
}

CListCtrlCl::~CListCtrlCl()
{/***********************************************/
	//delete m_pDragImage;
	//m_pDragImage = NULL;
	///***********************************************/
}


BEGIN_MESSAGE_MAP(CListCtrlCl, CListCtrl)
	ON_WM_MEASUREITEM()
	ON_WM_MEASUREITEM_REFLECT()

	///***********************************************/
	//ON_WM_MOUSEMOVE()
	//ON_WM_LBUTTONUP()
	//ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBeginDrag)
	///***********************************************/
END_MESSAGE_MAP()



// CListCtrlCl 消息处理程序



void CListCtrlCl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	CListCtrl::PreSubclassWindow();
	CHeaderCtrl *pHeader = GetHeaderCtrl();
	m_Header.SubclassWindow(pHeader->GetSafeHwnd());
}

void CListCtrlCl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	TCHAR lpBuffer[256];

	LV_ITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_PARAM ;
	lvi.iItem = lpDrawItemStruct->itemID ; 
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer ;
	lvi.cchTextMax = sizeof(lpBuffer);
	VERIFY(GetItem(&lvi));

	LV_COLUMN lvc, lvcprev ;
	::ZeroMemory(&lvc, sizeof(lvc));
	::ZeroMemory(&lvcprev, sizeof(lvcprev));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;
	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;

	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rtClient;
	GetClientRect(&rtClient);
	for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)
	{
		if ( nCol > 0 ) 
		{
			// Get Previous Column Width in order to move the next display item
			GetColumn(nCol-1, &lvcprev) ;
			lpDrawItemStruct->rcItem.left += lvcprev.cx ;
			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left; 
		}

		CRect rcItem;   
		if (!GetSubItemRect(lpDrawItemStruct->itemID,nCol,LVIR_LABEL,rcItem))   
			continue;   

		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpDrawItemStruct->itemID;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iSubItem = nCol;
		lvi.pszText = lpBuffer;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));
		CRect rcTemp;
		rcTemp = rcItem;

		if (nCol==0)
		{
			rcTemp.left -=4;//左边距
		}

		if ( lpDrawItemStruct->itemState & ODS_SELECTED )
		{
			//pDC->FillSolidRect(&rcTemp, 122(COLOR_HIGHLIGHT)) ;
			pDC->FillSolidRect(&rcTemp, RGB(111,118,122)) ;//选中列的背景颜色
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)) ;
		}
		else
		{
			COLORREF color;
			color = GetBkColor();
			pDC->FillSolidRect(rcTemp,color);

			if (FindColColor(nCol,color))
			{
				pDC->FillSolidRect(rcTemp,color);
			}
			if (FindItemColor(nCol,lpDrawItemStruct->itemID,color))
			{
				pDC->FillSolidRect(rcTemp,color);
			}
			
			//pDC->SetTextColor(m_color);
		}

		pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));

		UINT   uFormat    = DT_CENTER ;
		if (m_Header.m_Format[nCol]=='0')
		{
			uFormat = DT_LEFT;
		}
		else if (m_Header.m_Format[nCol]=='1')
		{
			uFormat = DT_CENTER;
		}
		else if (m_Header.m_Format[nCol]=='2')
		{
			uFormat = DT_RIGHT;
		}
		TEXTMETRIC metric;
		pDC->GetTextMetrics(&metric);
		int ofst;
		ofst = rcItem.Height() - metric.tmHeight;
		rcItem.OffsetRect(0,ofst/2);
		pDC->SetTextColor(m_color);
		COLORREF color;
		if (FindColTextColor(nCol,color))
		{
			pDC->SetTextColor(color);
		}
		if (FindItemTextColor(nCol,lpDrawItemStruct->itemID,color))
		{
			pDC->SetTextColor(color);
		}
		CFont nFont ,* nOldFont; 
		nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("宋体"));//创建字体 
		nOldFont = pDC->SelectObject(&nFont);
		DrawText(lpDrawItemStruct->hDC, lpBuffer, lstrlenW(lpBuffer), 
			&rcItem, uFormat) ;

		pDC->SelectStockObject(SYSTEM_FONT) ;
	}

}

void CListCtrlCl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
void CListCtrlCl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_nRowHeight>0)
	{
		lpMeasureItemStruct->itemHeight = m_nRowHeight;
	}
}
int CListCtrlCl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat /* = LVCFMT_LEFT */, int nWidth /* = -1 */, int nSubItem /* = -1 */)
{
	m_Header.m_HChar.Add(lpszColumnHeading);
	if (nFormat==LVCFMT_LEFT)
	{
		m_Header.m_Format = m_Header.m_Format + _T("0");
	}
	else if (nFormat==LVCFMT_CENTER)
	{
		m_Header.m_Format = m_Header.m_Format + L"1";
	}
	else if (nFormat==LVCFMT_RIGHT)
	{
		m_Header.m_Format = m_Header.m_Format + L"2";
	}
	else
	{
		m_Header.m_Format = m_Header.m_Format + L"1";
	}
	return CListCtrl::InsertColumn(nCol,lpszColumnHeading,nFormat,nWidth,nSubItem);
}
// Gradient - 渐变系数，立体背景用,不用渐变设为0
void CListCtrlCl::SetHeaderBKColor(int R, int G, int B, int Gradient) //设置表头背景色
{
	m_Header.m_R = R;
	m_Header.m_G = G;
	m_Header.m_B = B;
	m_Header.m_Gradient = Gradient;
}

// 设置表头高度
void CListCtrlCl::SetHeaderHeight(float Height) //设置表头高度
{
	m_Header.m_Height = Height;
}
bool CListCtrlCl::FindColColor(int col,COLORREF &color) //查找列颜色
{
	int flag = 0;
	for (POSITION pos = m_ptrListCol.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ptrListCol.GetNext(pos);
		if (pColor->nCol==col)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;
}
bool CListCtrlCl::FindItemColor(int col,int row,COLORREF &color) //查找颜色
{
	int flag = 0;
	for (POSITION pos = m_ptrListItem.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ptrListItem.GetNext(pos);
		if (pColor->nCol==col&&pColor->nRow==row)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;
}
void CListCtrlCl::SetColColor(int col,COLORREF color) //设置列颜色
{
	stColor *pColor  = new stColor;
	pColor->nCol = col;
	pColor->rgb = color;
	m_ptrListCol.AddTail(pColor);
}
void CListCtrlCl::SetItemColor(int col,int row,COLORREF color) //设置格子颜色
{
	stColor *pColor  = new stColor;
	pColor->nCol = col;
	pColor->nRow = row;
	pColor->rgb = color;
	m_ptrListItem.AddTail(pColor);
}
void CListCtrlCl::SetRowHeigt(int nHeight) //高置行高
{
	m_nRowHeight = nHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}
void CListCtrlCl::SetHeaderFontHW(int nHeight,int nWith) //设置头部字体宽和高
{
	m_Header.m_fontHeight = nHeight;
	m_Header.m_fontWith = nWith;
}
void CListCtrlCl::SetHeaderTextColor(COLORREF color) //设置头部字体颜色
{
	m_Header.m_color = color;
}
BOOL CListCtrlCl::SetTextColor(COLORREF cr)  //设置字体颜色
{
	m_color = cr;
	return TRUE;
}
void CListCtrlCl::SetFontHW(int nHeight,int nWith) //设置字体高和宽
{
	m_fontHeight = nHeight;
	m_fontWith = nWith;
}
void CListCtrlCl::SetColTextColor(int col,COLORREF color)
{
	stColor *pColor = new stColor;
	pColor->nCol = col;
	pColor->rgb = color;
	m_colTextColor.AddTail(pColor);
}
bool CListCtrlCl::FindColTextColor(int col,COLORREF &color)
{
	int flag = 0;
	for (POSITION pos = m_colTextColor.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_colTextColor.GetNext(pos);
		if (pColor->nCol==col)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;
}
bool CListCtrlCl::FindItemTextColor(int col,int row,COLORREF &color)
{
	int flag = 0;
	for (POSITION pos = m_ItemTextColor.GetHeadPosition();pos!=NULL;)
	{
		stColor *pColor = (stColor*)m_ItemTextColor.GetNext(pos);
		if (pColor->nCol==col&&pColor->nRow==row)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1==flag)
	{
		return true;
	}
	return false;
}
void CListCtrlCl::SetItemTextColor(int col,int row,COLORREF color)
{
	stColor *pColor = new stColor;
	pColor->nCol = col;
	pColor->nRow = row;
	pColor->rgb = color;
	m_ItemTextColor.AddTail(pColor);
}





//void CListCtrlCl::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult) 
//{
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//
//	if (pNMListView)
//	{
//		m_nPrevDropIndex	= -1;
//		m_uPrevDropState	= NULL;
//		
//		// Items being dragged - can be one or more.
//		m_anDragIndexes.RemoveAll();
//		POSITION pos = GetFirstSelectedItemPosition();
//		while (pos)
//		{
//			m_anDragIndexes.Add(GetNextSelectedItem(pos));
//		}
//
//		DWORD dwStyle = GetStyle();
//		if ((dwStyle & LVS_SINGLESEL) == LVS_SINGLESEL)
//		{
//			// List control is single select; we need it to be multi-select so
//			// we can show both the drag item and potential drag target as selected.
//			m_dwStyle = dwStyle;
//			ModifyStyle(LVS_SINGLESEL, NULL);
//		}
//
//		if (m_anDragIndexes.GetSize() > 0)
//		{
//			// Create a drag image from the centre point of the item image.
//			// Clean up any existing drag image first.
//			delete m_pDragImage;
//			CPoint ptDragItem;
//			m_pDragImage = CreateDragImageEx(&ptDragItem);
//			if (m_pDragImage)
//			{
//				m_pDragImage->BeginDrag(0, ptDragItem);
//				m_pDragImage->DragEnter(CWnd::GetDesktopWindow(), pNMListView->ptAction);
//			
//				// Capture all mouse messages in case the user drags outside the control.
//				SetCapture();
//			}
//		}
//	}
//	
//	*pResult = 0;
//}
//
//// Based on code by Frank Kobs.
//CImageList* CListCtrlCl::CreateDragImageEx(LPPOINT lpPoint)
//{
//	CRect rectSingle;	
//	CRect rectComplete(0, 0, 0, 0);
//	int	nIndex	= -1;
//	BOOL bFirst	= TRUE;
//
//	// Determine the size of the drag image.
//	POSITION pos = GetFirstSelectedItemPosition();
//	while (pos)
//	{
//		nIndex = GetNextSelectedItem(pos);
//		GetItemRect(nIndex, rectSingle, LVIR_BOUNDS);
//		if (bFirst)
//		{
//			// Initialize the CompleteRect
//			GetItemRect(nIndex, rectComplete, LVIR_BOUNDS);
//			bFirst = FALSE;
//		}
//		rectComplete.UnionRect(rectComplete, rectSingle);
//	}
//
//	// Create bitmap in memory DC
//	CClientDC dcClient(this);	
//	CDC dcMem;	
//	CBitmap Bitmap;
//
//	if (!dcMem.CreateCompatibleDC(&dcClient))
//	{
//		return NULL;
//	}
//
//	if (!Bitmap.CreateCompatibleBitmap(&dcClient, rectComplete.Width(), rectComplete.Height()))
//	{
//		return NULL;
//	}
//	
//	CBitmap* pOldMemDCBitmap = dcMem.SelectObject(&Bitmap);
//	// Here green is used as mask color.
//	dcMem.FillSolidRect(0, 0, rectComplete.Width(), rectComplete.Height(), RGB(0, 255, 0)); 
//
//	// Paint each DragImage in the DC.
//	CImageList* pSingleImageList = NULL;
//	CPoint pt;
//
//	pos = GetFirstSelectedItemPosition();
//	while (pos)
//	{
//		nIndex = GetNextSelectedItem(pos);
//		GetItemRect(nIndex, rectSingle, LVIR_BOUNDS);
//
//		pSingleImageList = CreateDragImage(nIndex, &pt);
//		if (pSingleImageList)
//		{
//			// Make sure width takes into account not using LVS_EX_FULLROWSELECT style.
//			IMAGEINFO ImageInfo;
//			pSingleImageList->GetImageInfo(0, &ImageInfo);
//			rectSingle.right = rectSingle.left + (ImageInfo.rcImage.right - ImageInfo.rcImage.left);
//
//			pSingleImageList->DrawIndirect(
//				&dcMem, 
//				0, 
//				CPoint(rectSingle.left - rectComplete.left, 
//				rectSingle.top - rectComplete.top),
//				rectSingle.Size(), 
//				CPoint(0,0));
//
//			delete pSingleImageList;
//		}
//	}
//
//	dcMem.SelectObject(pOldMemDCBitmap);
//
//	// Create the imagelist	with the merged drag images.
//	CImageList* pCompleteImageList = new CImageList;
//	
//	pCompleteImageList->Create(rectComplete.Width(), rectComplete.Height(), ILC_COLOR | ILC_MASK, 0, 1);
//	// Here green is used as mask color.
//	pCompleteImageList->Add(&Bitmap, RGB(0, 255, 0)); 
//
//	Bitmap.DeleteObject();
//
//	// As an optional service:
//	// Find the offset of the current mouse cursor to the imagelist
//	// this we can use in BeginDrag().
//	if (lpPoint)
//	{
//		CPoint ptCursor;
//		GetCursorPos(&ptCursor);
//		ScreenToClient(&ptCursor);
//		lpPoint->x = ptCursor.x - rectComplete.left;
//		lpPoint->y = ptCursor.y - rectComplete.top;
//	}
//
//	return pCompleteImageList;
//}
//
//void CListCtrlCl::OnMouseMove(UINT nFlags, CPoint point) 
//{
//	if (m_pDragImage)
//	{
//		// Must be dragging, as there is a drag image.
//
//		// Move the drag image.
//		CPoint ptDragImage(point);
//		ClientToScreen(&ptDragImage);
//		m_pDragImage->DragMove(ptDragImage);
//		
//		// Leave dragging so we can update potential drop target selection.
//		m_pDragImage->DragLeave(CWnd::GetDesktopWindow());
//
//		// Force x coordinate to always be in list control - only interested in y coordinate.
//		// In effect the list control has captured all horizontal mouse movement.
//		static const int nXOffset = 8;
//		CRect rect;
//		GetWindowRect(rect);
//		CWnd* pDropWnd = CWnd::WindowFromPoint(CPoint(rect.left + nXOffset, ptDragImage.y));
//
//		// Get the window under the drop point.
//		if (pDropWnd == this)
//		{
//			// Still in list control so select item under mouse as potential drop target.
//			point.x = nXOffset;	// Ensures x coordinate is always valid.
//			UpdateSelection(HitTest(point));
//		}
//
//		CRect rectClient;
//		GetClientRect(rectClient);
//		CPoint ptClientDragImage(ptDragImage);
//		ScreenToClient(&ptClientDragImage);
//
//		// Client rect includes header height, so ignore it, i.e.,
//		// moving the mouse over the header (and higher) will result in a scroll up.
//		CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
//		if (pHeader)
//		{
//			CRect rectHeader;
//			pHeader->GetClientRect(rectHeader);
//			rectClient.top += rectHeader.Height();
//		}
//
//		//if (ptClientDragImage.y < rectClient.top)
//		//{
//		//	// Mouse is above the list control - scroll up.
//		//	SetScrollTimer(scrollUp);
//		//}
//		//else if (ptClientDragImage.y > rectClient.bottom)
//		//{
//		//	// Mouse is below the list control - scroll down.
//		//	SetScrollTimer(scrollDown);
//		//}
//		/*else
//		{
//			KillScrollTimer();
//		}*/
//
//		// Resume dragging.
//		m_pDragImage->DragEnter(CWnd::GetDesktopWindow(), ptDragImage);
//	}
//	/*else
//	{
//		KillScrollTimer();
//	}*/
//
//	CListCtrl::OnMouseMove(nFlags, point);
//}
//
//void CListCtrlCl::UpdateSelection(int nDropIndex)
//{
//	if (nDropIndex > -1 && nDropIndex < GetItemCount())
//	{
//		// Drop index is valid and has changed since last mouse movement.
//
//		RestorePrevDropItemState();
//
//		// Save information about current potential drop target for restoring next time round.
//		m_nPrevDropIndex = nDropIndex;
//		m_uPrevDropState = GetItemState(nDropIndex, LVIS_SELECTED);
//
//		// Select current potential drop target.
//		//SetItemState(nDropIndex, LVIS_SELECTED, LVIS_SELECTED);
//		m_nDropIndex = nDropIndex;		// Used by DropItem().
//
//		UpdateWindow();
//	}
//}
//
//void CListCtrlCl::RestorePrevDropItemState()
//{
//	if (m_nPrevDropIndex > -1 && m_nPrevDropIndex < GetItemCount())
//	{
//		// Restore state of previous potential drop target.
//		SetItemState(m_nPrevDropIndex, m_uPrevDropState, LVIS_SELECTED);
//	}
//}
//
//
//
//
//
//void CListCtrlCl::OnLButtonUp(UINT nFlags, CPoint point) 
//{
//	if (m_pDragImage)
//	{
////		KillScrollTimer();
//
//		// Release the mouse capture and end the dragging.
//		::ReleaseCapture();
//		m_pDragImage->DragLeave(CWnd::GetDesktopWindow());
//		m_pDragImage->EndDrag();
//
//		delete m_pDragImage;
//		m_pDragImage = NULL;
//
//		// Drop the item on the list.
//		DropItem();
//	}
//	
//	CListCtrl::OnLButtonUp(nFlags, point);
//}
//
//void CListCtrlCl::DropItem()
//{
//	RestorePrevDropItemState();
//
//	// Drop after currently selected item.
//	m_nDropIndex++;
//	if (m_nDropIndex < 0 || m_nDropIndex > GetItemCount() - 1)
//	{
//		// Fail safe - invalid drop index, so drop at end of list.
//		m_nDropIndex = GetItemCount();
//	}
//
//	int nColumns = 1;
//	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
//	if (pHeader)
//	{
//		nColumns = pHeader->GetItemCount();
//	}
//
//	// Move all dragged items to their new positions.
//	for (int nDragItem = 0; nDragItem < m_anDragIndexes.GetSize(); nDragItem++)
//	{
//		int nDragIndex = m_anDragIndexes[nDragItem];
//
//		if (nDragIndex > -1 && nDragIndex < GetItemCount())
//		{
//			// Get information about this drag item.
//			TCHAR szText[256];
//			LV_ITEM lvItem;
//			ZeroMemory(&lvItem, sizeof(LV_ITEM));
//			lvItem.iItem		= nDragIndex;
//			lvItem.mask			= LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
//			lvItem.stateMask	= LVIS_DROPHILITED | LVIS_FOCUSED | LVIS_SELECTED | LVIS_STATEIMAGEMASK;
//			lvItem.pszText		= szText;
//			lvItem.cchTextMax	= sizeof(szText) - 1;
//			GetItem(&lvItem);
//			BOOL bChecked = GetCheck(nDragIndex);
//			
//			// Before moving drag item, make sure it is deselected in its original location,
//			// otherwise GetSelectedCount() will return 1 too many.
//			SetItemState(nDragIndex, static_cast<UINT>(~LVIS_SELECTED), LVIS_SELECTED);
//
//			// Insert the dragged item at drop index.
//			lvItem.iItem		= m_nDropIndex;
//			InsertItem(&lvItem);
//			if (bChecked)
//			{
//				SetCheck(m_nDropIndex);
//			}
//			
//			// Index of dragged item will change if item has been dropped above itself.
//			if (nDragIndex > m_nDropIndex)
//			{
//				nDragIndex++;
//			}
//
//			// Fill in all the columns for the dragged item.
//			lvItem.mask		= LVIF_TEXT;
//			lvItem.iItem	= m_nDropIndex;
//
//			for (int nColumn = 1; nColumn < nColumns; nColumn++)
//			{
//				_tcscpy(lvItem.pszText, (LPCTSTR)(GetItemText(nDragIndex, nColumn)));
//				lvItem.iSubItem = nColumn;
//				SetItem(&lvItem);
//			}
//			
//			// Delete the original item.
//			DeleteItem(nDragIndex);
//
//			// Need to adjust indexes of remaining drag items.
//			for (int nNewDragItem = nDragItem; nNewDragItem < m_anDragIndexes.GetSize(); nNewDragItem++)
//			{
//				int nNewDragIndex = m_anDragIndexes[nNewDragItem];
//
//				if (nDragIndex < nNewDragIndex && nNewDragIndex < m_nDropIndex)
//				{
//					// Item has been removed from above this item, and inserted after it,
//					// so this item moves up the list.
//					m_anDragIndexes[nNewDragItem] = max(nNewDragIndex - 1, 0);
//				}
//				else if (nDragIndex > nNewDragIndex && nNewDragIndex > m_nDropIndex)
//				{
//					// Item has been removed from below this item, and inserted before it,
//					// so this item moves down the list.
//					m_anDragIndexes[nNewDragItem] = nNewDragIndex + 1;
//				}
//			}
//			if (nDragIndex > m_nDropIndex)
//			{
//				// Item has been added before the drop target, so drop target moves down the list.
//				m_nDropIndex++;
//			}
//		}
//	}
//
//	if (m_dwStyle != NULL)
//	{
//		// Style was modified, so return it back to original style.
//		ModifyStyle(NULL, m_dwStyle);
//		m_dwStyle = NULL;
//	}
//}