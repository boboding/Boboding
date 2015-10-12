#pragma once
#include "ControlBase.h"

class CImageButton : public CControlBase
{
public:
	CImageButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle = L"", BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE, BOOL bIsPressDown = FALSE);
	void SetBitmap(CString strNormal, CString strHover = L"", CString strDown = L"", CString strDisable = L"");
	~CImageButton(void);
protected:
	void Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown);
	void OnTimer();
	CString m_strFileImage;
public:
	Image *m_pImageNormal;
	Image *m_pImageHover;
	Image *m_pImageDown;
	Image *m_pImageDisable;

	inline BOOL ImageFromIDResource(UINT resourceID, LPCTSTR resourceType, Image*& image);
	void SetBitmap(UINT nNormal, UINT nHover, UINT nDown);
};