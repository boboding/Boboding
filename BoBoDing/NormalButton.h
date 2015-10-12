#pragma once
#include "ControlBase.h"

class CNormalButton : public CControlBase
{
public:
	CNormalButton(HWND hWnd, UINT uControlID, CRect rc, CString strFileImage, CString strTitle = L"", BOOL bIsVisible = TRUE, 
		int nBeginTransparent = 100,int nEndTransparent = 100 ,BOOL bIsPressDown = FALSE);
	~CNormalButton(void);
protected:
	void Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown);
	void OnTimer();
	CString m_strFileImage;
	CBitmap m_bitmap;
	CSize	m_sizeBitmap;
};
