#include "StdAfx.h"
#include "ImageButton.h"

CImageButton::CImageButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
						   BOOL bIsDisable/* = FALSE*/ ,BOOL bIsPressDown/* = FALSE*/)
: CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable, 0, 0, bIsPressDown)
{
	m_pImageNormal = NULL;
	m_pImageHover = NULL;
	m_pImageDown = NULL;
	m_pImageDisable = NULL;
}

CImageButton::~CImageButton(void)
{

}
void CImageButton::SetBitmap(CString strNormal, CString strHover/* = ""*/, CString strDown/* = ""*/, CString strDisable/* = ""*/)
{
	if (strNormal.IsEmpty())
	{
		return;
	}
	USES_CONVERSION; 
	m_pImageDisable = m_pImageDown = m_pImageHover = m_pImageNormal = Image::FromFile((strNormal), TRUE);
	
 	if (!strHover.IsEmpty())
 	{
		m_pImageHover = Image::FromFile((strHover), TRUE);
		
		
 	}
 
 	if (!strDown.IsEmpty())
 	{
		m_pImageDown = Image::FromFile((strDown), TRUE);

 	}
 
 	if (!strDisable.IsEmpty())
 	{
		m_pImageDisable = Image::FromFile((strDisable), TRUE);

 	}
}

void CImageButton::OnTimer()
{

}
void CImageButton::Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown)
{
 	Graphics graphics(dc);
	CRect rc = m_rc;
 	Image *pImage = m_pImageNormal;
	if (m_bIsDisable)
	{
		pImage = m_pImageDisable;
	}
	else
	{
 		
 		if (m_rc.PtInRect(point))
 		{
 			pImage = m_pImageHover;
 			if (bIsPressDown)
 			{
 				rc.left += 2;
 				rc.top += 2;
 				pImage = m_pImageDown;
 			}
 		}
	}

 	graphics.DrawImage(pImage, m_rc.left, m_rc.top,  m_rc.Width(), m_rc.Height());

	dc.SetBkMode(TRANSPARENT);
	CFont *pOldFont = dc.SelectObject(&m_font);
	dc.DrawText(m_strTitle, &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
	dc.SelectObject(pOldFont);

}

void CImageButton::SetBitmap(UINT nNormal, UINT nHover, UINT nDown)
{
	ImageFromIDResource(nNormal,_T("PNG"),m_pImageNormal);
	ImageFromIDResource(nHover,_T("PNG"),m_pImageHover);
	ImageFromIDResource(nDown,_T("PNG"),m_pImageDown);
	
}
inline BOOL CImageButton::ImageFromIDResource(UINT resourceID, LPCTSTR resourceType, Image*& image)

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

