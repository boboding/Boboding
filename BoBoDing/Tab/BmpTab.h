
//

/////////////////////////////////////////////////////////////////////////////
// CBmpTab window
#include <afxtempl.h>
#include <afxcoll.h>

class CBmpTab : public CStatic
{
// Construction
public:
	CBmpTab();
public:
typedef	struct  tabitem
	{
		int		nIndex;
		HICON	icon;
		void	*pVoid;
	}TABITEM,*PTABITEM;
// Attributes
public:

// Operations
public:
		CDC	m_memDC;
		CPtrArray	m_aryItem;
		//HICON	m_hIconHand;
		BOOL	m_bIsCDC;
		DWORD	m_dwState;
		CBitmap m_bmpNormal;
		CBitmap m_bmpHover;
		CBitmap m_bmpHdown;

		int		m_iCurrentSelect;
		int		m_iCurrentFouce;
		enum{
			HTNORMAL	=0x0001,
			HTHOVER		=0x0002,
			HTHDOWN		=0x0003
		};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpTab)
	public:
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetTabItemRect(int nIndex,CRect *rc);
	void AddTabItem(TABITEM &item);
	void SetBmp(UINT nBmpNormal, UINT nBmpHover, UINT nBmpHdown);
	void SetIcon(int nIndex,UINT nIcon,void *pVoid);
	void AddTabItem(UINT nBmpNormal, UINT nBmpHover, UINT nBmpHdown, UINT nIcon, void *pVoid);
	void TransparentBlt1(CDC *pDC, CBitmap &Image, CRect &rect, COLORREF rgbMask);
	virtual ~CBmpTab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBmpTab)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
