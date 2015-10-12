#include "StdAfx.h"
#include "Area.h"

CArea::CArea(HWND hWnd, UINT uControlID, CRect rc, int nBeginTransparent/* = 50*/,int nEndTransparent/* = 50*/, 
			 COLORREF clr/* = RGB(255, 255, 255)*/, BOOL bIsVisible/* = TRUE*/)
			: CControlBase(hWnd, uControlID, rc, L"", bIsVisible, FALSE, nBeginTransparent, nEndTransparent, FALSE)
{
	m_clr = clr;
}

CArea::~CArea(void)
{
}

void CArea::OnTimer()
{

}

void CArea::Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown)
{
	CDC TempDC;
	TempDC.CreateCompatibleDC(&dc);

	CBitmap memBmp;
	memBmp.CreateCompatibleBitmap(&dc, m_rc.right, m_rc.bottom);
	CBitmap *pOldmap =  TempDC.SelectObject(&memBmp);
	TempDC.FillSolidRect(&m_rc, m_clr);

	DrawVerticalTransition(dc, TempDC, m_rc, m_nBeginTransparent, m_nEndTransparent);

	TempDC.SelectObject(pOldmap);
	memBmp.DeleteObject();
	TempDC.DeleteDC();
}