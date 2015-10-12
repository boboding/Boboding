

#include "stdafx.h"


#include "BmpTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpTab

CBmpTab::CBmpTab()
{
	m_bIsCDC=FALSE;
	m_dwState=HTNORMAL;
	//m_hIconHand=AfxGetApp()->LoadCursor(IDC_HANDLE);
	m_iCurrentSelect=1;
	m_iCurrentFouce=-1;
}

CBmpTab::~CBmpTab()
{
}


BEGIN_MESSAGE_MAP(CBmpTab, CStatic)
	//{{AFX_MSG_MAP(CBmpTab)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpTab message handlers

void CBmpTab::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;GetClientRect(&rc);

	CDC memDC;memDC.CreateCompatibleDC(&dc);
	CBitmap bmpBack;bmpBack.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
	CBitmap *bmpOld=memDC.SelectObject(&bmpBack);

	memDC.BitBlt(0,0,rc.Width(),rc.Height(),&m_memDC,0,0,SRCCOPY);


	CRect rcItem;
	TABITEM* tabItem;
	for(int i=0;i<m_aryItem.GetSize();i++)
	{
		CDC tmpDC;tmpDC.CreateCompatibleDC(&dc);
		
		tabItem=(TABITEM*)m_aryItem.GetAt(i);
// 		if(tabItem->pVoid)
// 			((CWnd*)(tabItem->pVoid))->ShowWindow(SW_HIDE);

		GetTabItemRect(i,&rcItem);

			bmpOld=tmpDC.SelectObject(&m_bmpNormal);

		if(m_iCurrentFouce==i)
		{
			bmpOld=tmpDC.SelectObject(&m_bmpHover);
		}
		if(m_iCurrentSelect==i)
		{
			bmpOld=tmpDC.SelectObject(&m_bmpHdown);
// 			if(tabItem->pVoid)
// 			((CWnd*)(tabItem->pVoid))->ShowWindow(SW_NORMAL);
		}

		memDC.BitBlt(rcItem.left+1,rcItem.top,rcItem.Width(),rcItem.Height(),&tmpDC,0,0,SRCCOPY);

		tmpDC.SelectObject(bmpOld);
		ReleaseDC(&tmpDC);
		tmpDC.DeleteDC();

		::DrawIconEx(memDC,rcItem.left+5,rcItem.top+5,tabItem->icon,24,24,0,NULL,DI_NORMAL);
	}

	dc.BitBlt(0,0,rc.Width(),rc.Height(),&memDC,0,0,SRCCOPY);

//	CStatic::OnPaint();
}

void CBmpTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	AfxMessageBox("dd");
	//m_dwState=HTHDOWN;
	CRect rcItem;
	for(int i=0;i<m_aryItem.GetSize();i++)
	{
		CWnd *tabItemView;
		tabItemView=(CWnd*)((TABITEM*)m_aryItem.GetAt(i))->pVoid;
		if(tabItemView)
			tabItemView->ShowWindow(SW_HIDE);

		GetTabItemRect(i,&rcItem);
		if(rcItem.PtInRect(point))
		{
			m_iCurrentSelect=i;
			if((m_aryItem.GetAt(i))!=NULL)
			{
				if(tabItemView)
					tabItemView->ShowWindow(SW_NORMAL);
			}
		}
		
	}
	Invalidate();
	CStatic::OnLButtonDown(nFlags, point);
}

BOOL CBmpTab::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bIsCDC)
	{
		m_memDC.CreateCompatibleDC(pDC);
		CRect rc;GetClientRect(&rc);
		CBitmap bmpBack;bmpBack.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
		m_memDC.SelectObject(&bmpBack);
		
		m_memDC.BitBlt(0,0,rc.Width(),rc.Height(),pDC,0,0,SRCCOPY);
		//	m_memDC.SelectObject(bmpOld);
		//	bmpOld->DeleteObject();
		m_bIsCDC=TRUE;
	
	}
	return TRUE;
	//return CStatic::OnEraseBkgnd(pDC);
}

void CBmpTab::TransparentBlt1(CDC *pDC, CBitmap &Image, CRect &rect, COLORREF rgbMask)
{
	CDC ImageDC,MaskDC;
	
	CBitmap *pOldImage;
	CBitmap maskBitmap,*pOldMaskDCBitmap ;
	
	//	Image.LoadBitmap(nBmp);
	ImageDC.CreateCompatibleDC(pDC);
	pOldImage=ImageDC.SelectObject(&Image);
	
	MaskDC.CreateCompatibleDC(pDC);
	maskBitmap.CreateBitmap( rect.Width(), rect.Height(), 1, 1, NULL );
	pOldMaskDCBitmap = MaskDC.SelectObject( &maskBitmap );
	
	ImageDC.SetBkColor(rgbMask);
	MaskDC.BitBlt( 0, 0, rect.Width(), rect.Height(), &ImageDC, 0, 0, SRCCOPY );
	
	ImageDC.SetBkColor(RGB(0,0,0));
	ImageDC.SetTextColor(RGB(255,255,255));
	ImageDC.BitBlt(0, 0, rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);
	
	pDC->BitBlt(rect.left,rect.top,rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);
	pDC->BitBlt(rect.left,rect.top,rect.Width(), rect.Height(), &ImageDC, 0, 0,SRCPAINT);
	
	MaskDC.SelectObject(pOldMaskDCBitmap);
	ImageDC.SelectObject(pOldImage);
}

void CBmpTab::SetIcon(int nIndex,UINT nIcon,void *pVoid)
{
	TABITEM* tabItem=new TABITEM;
	tabItem->nIndex=nIndex;
	tabItem->icon=AfxGetApp()->LoadIcon(nIcon);
	tabItem->pVoid=pVoid;

	m_aryItem.Add(tabItem);
}

void CBmpTab::SetBmp(UINT nBmpNormal, UINT nBmpHover, UINT nBmpHdown)
{
	m_bmpNormal.LoadBitmap(nBmpNormal);
	m_bmpHover.LoadBitmap(nBmpHover);
	m_bmpHdown.LoadBitmap(nBmpHdown);
}

void CBmpTab::AddTabItem(TABITEM &item)
{
	//m_aryItem.Add(&item);
}

void CBmpTab::AddTabItem(UINT nBmpNormal, UINT nBmpHover, UINT nBmpHdown, UINT nIcon, void *pVoid)
{
	//if(m_aryItem.GetSize()==0)
// 	CBitmap bmpNormal,bmpHover,bmpHdown;
// 	HICON icon;
// // 	bmpNormal.LoadBitmap(nBmpNormal);
// // 	bmpHover.LoadBitmap(nBmpHover);
// // 	bmpHdown.LoadBitmap(nBmpHdown);
// 	icon=AfxGetApp()->LoadIcon(nIcon);
// 
// 	TABITEM* tabitm=new TABITEM;
// //	tabitm.rcItem=rc;
// 	tabitm->bmpNormal.LoadBitmap(nBmpNormal);
// 	tabitm->bmpHover.LoadBitmap(nBmpHover);
// 	tabitm->bmpHdown.LoadBitmap(nBmpHdown);
// 	tabitm->icon=icon;
// 	tabitm->pVoid=NULL;
// 	
// 	m_aryItem.Add((void*)tabitm);
}

void CBmpTab::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("dd");
//	m_dwState=HTHOVER;
// 	CRect rc;
// 	BOOL IsTrue=FALSE;
// 	for(int i=0;i<m_aryItem.GetSize();i++)
// 	{
// 		GetTabItemRect(i,&rc);
// 		if(rc.PtInRect(point))
// 		{
// 			m_iCurrentFouce=i;
// 			IsTrue=TRUE;
// 		}
// 	}
// 	if(!IsTrue)
// 		m_iCurrentFouce=-1;
	
	SetTimer(1,10,NULL);
	Invalidate();
	CStatic::OnMouseMove(nFlags, point);
}

void CBmpTab::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,SS_NOTIFY);
	CStatic::PreSubclassWindow();
}

void CBmpTab::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	CRect rc;
	
	BOOL bIsOK=FALSE;

	for (int i=0;i<m_aryItem.GetSize();i++)
	{
		GetTabItemRect(i,&rc);
		if(rc.PtInRect(pt))
		{
			m_iCurrentFouce=i;
			bIsOK=TRUE;
		}

	}
	
	if (!bIsOK)
	{
		m_iCurrentFouce=-1;
			KillTimer(1);
	}

	Invalidate();
// 	if(rc.PtInRect(pt))
// 	{
// 		m_dwState=HTHOVER;
// 	}
// 	else
// 	{
// 		m_dwState=HTNORMAL;
// 	
// 		
// 	}
// 	
	CStatic::OnTimer(nIDEvent);
}

BOOL CBmpTab::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
// 	CPoint pt(GetMessagePos());
// 	CRect rc;GetClientRect(&rc);
// 	//ScreenToClient(&pt);
// 	if(rc.PtInRect(pt))
// 	{
		//::SetCursor(m_hIconHand);
//	}
		return TRUE;
//	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CBmpTab::GetTabItemRect(int nIndex, CRect *rc)
{
// 	if(m_bmpNormal.GetSafeHandle())
// 	{
		BITMAP bm;
		m_bmpNormal.GetBitmap(&bm);
		
		rc->SetRect(0,nIndex*bm.bmHeight,bm.bmWidth,nIndex*bm.bmHeight+bm.bmHeight);
// 	}
// 	else
// 	{
// 		rc->SetRect(0,0,0,0);
// 	}
}
