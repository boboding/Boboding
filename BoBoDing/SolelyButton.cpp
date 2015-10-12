#include "StdAfx.h"
#include "SolelyButton.h"

CSolelyButton::CSolelyButton(HWND hWnd, UINT uControlID, CRect rc, UINT resourceID, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
						   BOOL bIsDisable/* = FALSE*/ ,BOOL bIsPressDown/* = FALSE*/)
						   : CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable, 40, 90, bIsPressDown)
{
	m_pImage = NULL;
	m_bIsDraw = FALSE;
	//if (strImage)
	//{
	//	USES_CONVERSION; 
	//	m_pImage = Image::FromFile((strImage), TRUE);
	//}

	ImageFromIDResource( resourceID, _T("PNG"), m_pImage);

}


//CSolelyButton::CSolelyButton(HWND hWnd, UINT uControlID, CRect rc, CString strImage, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
//	BOOL bIsDisable/* = FALSE*/ ,BOOL bIsPressDown/* = FALSE*/)
//	: CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable, 40, 90, bIsPressDown)
//{
//	m_pImage = NULL;
//	m_bIsDraw = FALSE;
//	if (strImage)
//	{
//		USES_CONVERSION; 
//		m_pImage = Image::FromFile((strImage), TRUE);
//	}
//
//	ImageFromIDResource(UINT resourceID, LPCTSTR resourceType, Image*& image)
//
//}
CSolelyButton::~CSolelyButton(void)
{

}
void CSolelyButton::OnTimer()
{
	//TRACE("控件 %d 执行定时器 %d RECT(%d, %d, %d, %d)\n", m_uID, m_TimerID, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	::InvalidateRect(m_hWnd, &m_rc, FALSE);
	if (m_bIsDraw)
	{
		KillTimer();
		m_bIsDraw = FALSE;
		return;

	}
	
	m_bIsDraw = TRUE;
	
}
void CSolelyButton::Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown)
{
	CRect rc = m_rc;
	int n = 0;
	if (m_bIsDraw)
	{
		n = 3;

	}
  	if (m_bIsDisable)
  	{
  		
  	}
  	else
  	{
  		if (m_rc.PtInRect(point) || m_bIsDraw)
  		{			
  			if (bIsPressDown)
  			{
				rc.OffsetRect(0, n);
  				DrawTransitionSpace(dc, m_rc, m_nEndTransparent, m_nBeginTransparent);
  			}
  			else
  			{
				rc.OffsetRect(0, -n);
  				DrawTransitionSpace(dc, m_rc, m_nBeginTransparent + n * 3, m_nEndTransparent);
  			}
  		}
  	}

	Graphics graphics(dc);	
	graphics.DrawImage(m_pImage, rc.left, rc.top,  m_pImage->GetWidth(), m_pImage->GetHeight());

}



inline BOOL CSolelyButton::ImageFromIDResource(UINT resourceID, LPCTSTR resourceType, Image*& image)
{
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource(hInst,MAKEINTRESOURCE(resourceID),resourceType);
	if (hRsrc == NULL)
		return FALSE;

	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (lpRsrc == NULL)
		return FALSE;

	// Allocate global memory on which to create stream
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
	memcpy(pmem,lpRsrc,len);
	IStream* pstm;
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);

	// load from stream
	image = Gdiplus::Image::FromStream(pstm);

	// free/release stuff
	GlobalUnlock(m_hMem);
	GlobalFree(m_hMem);
	pstm->Release();
	FreeResource(lpRsrc);

	return TRUE;
}