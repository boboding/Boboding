#include "StdAfx.h"
#include "NormalButton.h"

CNormalButton::CNormalButton(HWND hWnd, UINT uControlID, CRect rc, CString strFileImage, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
							 int nBeginTransparent/* = 100*/,int nEndTransparent/* = 100*/ ,BOOL bIsPressDown/* = FALSE*/)
							 : CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, FALSE, nBeginTransparent, nEndTransparent, bIsPressDown)
{
	m_strFileImage = strFileImage;
	if (!m_strFileImage.IsEmpty())
	{
		HBITMAP hBmp = (HBITMAP)LoadImage(NULL, m_strFileImage, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (hBmp)
		{
			m_bitmap.Attach(hBmp);
			BITMAP bmInfo;
			::GetObject( m_bitmap.m_hObject, sizeof(BITMAP), &bmInfo );
			m_sizeBitmap.cx = bmInfo.bmWidth;
			m_sizeBitmap.cy = bmInfo.bmHeight;				
		}
	}
}

CNormalButton::~CNormalButton(void)
{
	if(m_bitmap.m_hObject != NULL)
	{
		m_bitmap.DeleteObject();
	}
}

void CNormalButton::OnTimer()
{

}

void CNormalButton::Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown)
{
	CDC TempDC;
	TempDC.CreateCompatibleDC(&dc);
	
// 	CBitmap memBmp;
// 	memBmp.CreateCompatibleBitmap(&dc, m_rc.right, m_rc.Height());
	CBitmap *pOldmap =  TempDC.SelectObject(&m_bitmap);

	
	int nStart = 0;
	CRect rc = m_rc;
	if (m_rc.PtInRect(point))
	{
		nStart += m_sizeBitmap.cx / 4;
		if (bIsPressDown)
		{
			nStart += m_sizeBitmap.cx / 4;
			rc.OffsetRect(1, 1);
		}
	}
	dc.SetBkMode(TRANSPARENT);
	dc.StretchBlt(m_rc.left, m_rc.top, m_rc.Width(), m_rc.Height(), &TempDC, nStart, 0, m_sizeBitmap.cx / 4, m_sizeBitmap.cy, SRCCOPY);
	dc.DrawText(m_strTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	TempDC.SelectObject(pOldmap);
	//memBmp.DeleteObject();
	TempDC.DeleteDC();
}