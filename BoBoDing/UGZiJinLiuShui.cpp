/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived CUGCtrl class

#include "stdafx.h"
#include "resource.h"
#include "UGZiJinLiuShui.h"
#include "BoBoDing.h"
#include "DlgZiJinLiuShui.h"
#include "DlgZiJinLiuShuiShouRuChange.h"
#include "Excel\BasicExcel.h"
using namespace YExcel;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CUGZiJinLiuShui,CUGCtrl)
	//{{AFX_MSG_MAP(CUGZiJinLiuShui)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard CUGZiJinLiuShui construction/destruction
CUGZiJinLiuShui::CUGZiJinLiuShui()
{
}

CUGZiJinLiuShui::~CUGZiJinLiuShui()
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void CUGZiJinLiuShui::OnSetup()
{
	/*int rows = 12;
	int cols = 8;*/

	m_nButtonIndex = AddCellType(&m_button);

	COleDateTime timeCurrentTime=COleDateTime::GetCurrentTime();
	int nYear=timeCurrentTime.GetYear();
	int nMonth=timeCurrentTime.GetMonth();
	CString strTime=_T("");
	strTime.Format(_T("%d-%d-1"),nYear,nMonth);
	COleDateTime	oleDateTime_timeFrom;
	oleDateTime_timeFrom.ParseDateTime(strTime);
	COleDateTime oleDateTime_timeTo=timeCurrentTime;

	m_font.CreateFont(13,0,0,0,500,0,0,0,0,0,0,0,0,_T("宋体"));
	SetDefFont(&m_font);


	 m_oleDateTime_timeFrom=oleDateTime_timeFrom;
	 m_oleDateTime_timeTo=oleDateTime_timeTo;

	SetNumberRows(GetRowCount( oleDateTime_timeFrom, oleDateTime_timeTo));
	InitGrid();
	InitData( oleDateTime_timeFrom, oleDateTime_timeTo);
	LockRows(1);
	
}

/////////////////////////////////////////////////////////////////////////////
//	OnSheetSetup	
//		This notification is called for each additional sheet that the grid
//		might contain, here you can customize each sheet in the grid.
//	Params:
//		sheetNumber - index of current sheet
//	Return:
//		<none>
void CUGZiJinLiuShui::OnSheetSetup(int sheetNumber)
{
	UNREFERENCED_PARAMETER(sheetNumber);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanMove
//		is sent when a cell change action was instigated
//		( user clicked on another cell, used keyboard arrows,
//		or Goto[...] function was called ).
//	Params:
//		oldcol, oldrow - 
//		newcol, newrow - cell that is gaining focus
//	Return:
//		TRUE - to allow the move
//		FALSE - to prevent new cell from gaining focus
int CUGZiJinLiuShui::OnCanMove(int oldcol,long oldrow,int newcol,long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanViewMove
//		is called when current grid's view is about to be scrolled.
//	Params:
//		oldcol, oldrow - coordinates of original top-left cell
//		newcol, newrow - coordinates of top-left cell that is gaining the focus
//	Return:
//		TRUE - to allow for the scroll
//		FALSE - to prevent the view from scrolling
int CUGZiJinLiuShui::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitBottom
//		This notification allows for dynamic row loading, it will be called
//		when the grid's drawing function has hit the last row.  It allows the grid
//		to ask the datasource/developer if there are additional rows to be displayed.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//		rowsfound	- number of rows actually found, usually equal to rowspast or zero.
//	Return:
//		<none>
void CUGZiJinLiuShui::OnHitBottom(long numrows,long rowspast,long rowsfound)
{
	UNREFERENCED_PARAMETER(numrows);
	UNREFERENCED_PARAMETER(rowspast);
	UNREFERENCED_PARAMETER(rowsfound);
	// used by the datasources
	/*if ( rowsfound > 0 )
	{
	SetNumberRows( numrows + rowsfound, FALSE );
	}*/
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitTop
//		Is called when the user has scrolled all the way to the top of the grid.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//	Return:
//		<none>
void CUGZiJinLiuShui::OnHitTop(long numrows,long rowspast)
{
	UNREFERENCED_PARAMETER(numrows);
	UNREFERENCED_PARAMETER(rowspast);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeCol
//		is sent when the mouse was moved in the area between
//		columns on the top heading, indicating that the user
//		might want to resize a column.
//	Params:
//		col - identifies column number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int CUGZiJinLiuShui::OnCanSizeCol(int col)
{
	UNREFERENCED_PARAMETER(col);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSizing
//		is sent continuously when user is sizing a column.
//		This notification is ideal to provide min/max width checks.
//	Params:
//		col - column currently sizing
//		width - current new column width
//	Return:
//		<none>
void CUGZiJinLiuShui::OnColSizing(int col,int *width)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(*width);
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSized
//		This is sent when the user finished sizing the 
//		given column.(see above for more information)
//	Params:
//		col - column sized
//		width - new column width
//	Return:
//		<none>
void CUGZiJinLiuShui::OnColSized(int col,int *width)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(*width);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeRow
//		is sent when the mouse was moved in the area between
//		rows on the side heading, indicating that the user
//		might want to resize a row.
//	Params:
//		row - identifies row number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int CUGZiJinLiuShui::OnCanSizeRow(long row)
{
	UNREFERENCED_PARAMETER(row);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowSizing
//		Sent during user sizing of a row, can provide
//		feed back on current height
//	Params:
//		row - row sizing
//		height - pointer to current new row height
//	Return:
//		<none>
void CUGZiJinLiuShui::OnRowSizing(long row,int *height)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*height);
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowSized
//		This is sent when the user is finished sizing the
//		given row.
//	Params:
//		row - row sized
//		height - pointer to current new row height
//	Return:
//		<none>
void CUGZiJinLiuShui::OnRowSized(long row,int *height)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*height);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeSideHdg
//		Sent when the user is about to start sizing of the side heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int CUGZiJinLiuShui::OnCanSizeSideHdg()
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSideHdgSizing
//		Sent while the heading is being sized
//	Params:
//		width - pointer to current new width of the side heading
//	Return:
//		TRUE - to accept current new size
//		FALSE - to stop sizing, the size is either too large or too small
int CUGZiJinLiuShui::OnSideHdgSizing(int *width)
{
	UNREFERENCED_PARAMETER(*width);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSideHdgSized
//		Sent when the user has completed the sizing of the side heading
//	Params:
//		width - pointer to new width
//	Return:
//		TRUE - to accept new size
//		FALSE - to revert to old size
int CUGZiJinLiuShui::OnSideHdgSized(int *width)
{
	UNREFERENCED_PARAMETER(*width);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeTopHdg
//		Sent when the user is about to start sizing of the top heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int CUGZiJinLiuShui::OnCanSizeTopHdg()
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopHdgSizing
//		Sent while the top heading is being sized
//	Params:
//		height - pointer to current new height of the top heading
//	Return:
//		TRUE - to accept current new size
//		FALSE - to stop sizing, the size is either too large or too small
int CUGZiJinLiuShui::OnTopHdgSizing(int *height)
{
	UNREFERENCED_PARAMETER(*height);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopHdgSized
//		Sent when the user has completed the sizing of the top heading
//	Params:
//		height - pointer to new height
//	Return:
//		TRUE - to accept new size
//		FALSE - to revert to old size
int CUGZiJinLiuShui::OnTopHdgSized(int *height)
{
	UNREFERENCED_PARAMETER(*height);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColChange
//		Sent whenever the current column changes
//	Params:
//		oldcol - column that is loosing the focus
//		newcol - column that the user move into
//	Return:
//		<none>
void CUGZiJinLiuShui::OnColChange(int oldcol,int newcol)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(newcol);
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowChange
//		Sent whenever the current row changes
//	Params:
//		oldrow - row that is loosing the locus
//		newrow - row that user moved into
//	Return:
//		<none>
void CUGZiJinLiuShui::OnRowChange(long oldrow,long newrow)
{
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellChange
//		Sent whenever the current cell changes
//	Params:
//		oldcol, oldrow - coordinates of cell that is loosing the focus
//		newcol, newrow - coordinates of cell that is gaining the focus
//	Return:
//		<none>
void CUGZiJinLiuShui::OnCellChange(int oldcol,int newcol,long oldrow,long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
}

/////////////////////////////////////////////////////////////////////////////
//	OnLeftColChange
//		Sent whenever the left visible column in the grid changes, indicating
//		that the view was scrolled horizontally
//	Params:
//		oldcol - column that used to be on the left
//		newcol - new column that is going to be the first visible column from the left
//	Return:
//		<none>
void CUGZiJinLiuShui::OnLeftColChange(int oldcol,int newcol)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(newcol);
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopRowChange
//		Sent whenever the top visible row in the grid changes, indicating
//		that the view was scrolled vertically
//	Params:
//		oldrow - row that used to be on the top
//		newrow - new row that is going to be the first visible row from the top
//	Return:
//		<none>
void CUGZiJinLiuShui::OnTopRowChange(long oldrow,long newrow)
{
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
}

/////////////////////////////////////////////////////////////////////////////
//	OnViewMoved
//		This notification is fired after the current viewing area
//		was scrolled.
//	Params:
//		nScrolDir - UG_VSCROLL, UG_HSCROLL
//
//		if the nScrolDir == UG_VSCROLL
//			oldPos - row that used to be on the top
//			newPos - row that is now the first visible row from the top
//
//		if the nScrolDir == UG_VSCROLL
//			oldPos - column that used to be on the left
//			newPos - column that is now the first visible column from the left
//	Return:
//		<none>
void CUGZiJinLiuShui::OnViewMoved( int nScrolDir, long oldPos, long newPos )
{
	UNREFERENCED_PARAMETER(nScrolDir);
	UNREFERENCED_PARAMETER(oldPos);
	UNREFERENCED_PARAMETER(newPos);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSelectionChanged
//		The OnSelectionChanged notification is called by the multiselect
//		class when a change occurred in current selection (i.e. user clicks
//		on a new cell, drags a mouse selecting range of cells, or uses
//		CTRL/SHIFT - left click key combination to select cells.)
//	Params:
//		startCol, startRow	- coordinates of the cell starting the selection block
//		endCol, endRow		- coordinates of the cell ending the selection block
//		blockNum			- block number representing this range, this will
//							always represent total number of selection blocks.
//	Return:
//		<none>
void CUGZiJinLiuShui::OnSelectionChanged(int startCol,long startRow,int endCol,long endRow,int blockNum)
{
	UNREFERENCED_PARAMETER(startCol);
	UNREFERENCED_PARAMETER(startRow);
	UNREFERENCED_PARAMETER(endCol);
	UNREFERENCED_PARAMETER(endRow);
	UNREFERENCED_PARAMETER(blockNum);
}

/////////////////////////////////////////////////////////////////////////////
//	OnLClicked
//		Sent whenever the user clicks the left mouse button within the grid
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)

{


	if(m_nLightRow==row) return;
	if (row==0)
	{return;
	}
	//if( !updn )
	//{


		QuickSetBackColor(0,m_nLightRow,RGB(240,240,240));
		QuickSetBackColor(0,row,RGB(115,153,188));
		for(int i=1;i<m_nCols-2;i++)
		{
			QuickSetBackColor(i,row,GridSelectRowColor);
			QuickSetBackColor(i,m_nLightRow,RGB(255,255,255));
		}
		m_nLightRow=row;
		GetYeWuBianHao(2,m_nLightRow);

		/*CString strTruncate;
		strTruncate=m_strYeWuBianHao.Left(2);
		if(strTruncate.Compare(_T("SZ"))!=0)
		{	CDlgZiJinLiuShui *pDlg = (CDlgZiJinLiuShui *)GetParent();
		pDlg->m_Button_ctlChange.EnableWindow(FALSE);
		pDlg->m_Button_ctlDel.EnableWindow(FALSE);
		}
		else
		{	CDlgZiJinLiuShui *pDlg = (CDlgZiJinLiuShui *)GetParent();
		pDlg->m_Button_ctlChange.EnableWindow(TRUE);
		pDlg->m_Button_ctlDel.EnableWindow(TRUE);
		}*/
	//}

	Invalidate(TRUE);


}

/////////////////////////////////////////////////////////////////////////////
//	OnRClicked
//		Sent whenever the user clicks the right mouse button within the grid
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnDClicked
//		Sent whenever the user double clicks the left mouse button within the grid
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
	Change();
}	

/////////////////////////////////////////////////////////////////////////////
//	OnMouseMove
//		is sent when the user moves mouse over the grid area.
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		point		- represents the screen point where the mouse event was detected
//		nFlags		- 
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void CUGZiJinLiuShui::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_LClicked
//		Sent whenever the user clicks the left mouse button within the top heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_RClicked
//		Sent whenever the user clicks the right mouse button within the top heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_DClicked
//		Sent whenever the user double clicks the left mouse
//		button within the top heading
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_LClicked
//		Sent whenever the user clicks the left mouse button within the side heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_RClicked
//		Sent whenever the user clicks the right mouse button within the side heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_DClicked
//		Sent whenever the user double clicks the left mouse button within the side heading
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_LClicked
//		Sent whenever the user clicks the left mouse button within the top corner button
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_RClicked
//		Sent whenever the user clicks the right mouse button within the top corner button
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_DClicked
//		Sent whenever the user double clicks the left mouse
//		button within the top corner button
//	Params:
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
}

/////////////////////////////////////////////////////////////////////////////
//	OnKeyDown
//		Sent when grid received a WM_KEYDOWN message, usually as a result
//		of a user pressing any key on the keyboard.
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void CUGZiJinLiuShui::OnKeyDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(*vcKey);
	UNREFERENCED_PARAMETER(processed);
	//	GetScrollBarCtrl(SB_HORZ)->EnableScrollBar(ESB_DISABLE_BOTH);
}

/////////////////////////////////////////////////////////////////////////////
//	OnKeyUp
//		Sent when grid received a WM_KEYUP message, usually as a result
//		of a user releasing a key.
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void CUGZiJinLiuShui::OnKeyUp(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(*vcKey);
	UNREFERENCED_PARAMETER(processed);
	//	GetScrollBarCtrl(SB_HORZ)->EnableScrollBar(ESB_DISABLE_BOTH);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCharDown
//		Sent when grid received a WM_CHAR message, usually as a result
//		of a user pressing any key that represents a printable character.
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void CUGZiJinLiuShui::OnCharDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(*vcKey);
	UNREFERENCED_PARAMETER(processed);
	//	GetScrollBarCtrl(SB_HORZ)->EnableScrollBar(ESB_DISABLE_BOTH);
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetCell
//		This message is sent every time the grid needs to
//		draw a cell in the grid. At this point the cell
//		object has been populated with all of the information
//		that will be used to draw the cell. This information
//		can now be changed before it is used for drawing.
//	Warning:
//		This notification is called for each cell that needs to be painted
//		Placing complicated calculations here will slowdown the refresh speed.
//	Params:
//		col, row	- coordinates of cell currently drawing
//		cell		- pointer to the cell object that is being drawn
//	Return:
//		<none>
void CUGZiJinLiuShui::OnGetCell(int col,long row,CUGCell *cell)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*cell);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetCell
//		This notification is sent every time a cell is set,
//		here you have a chance to make final modification
//		to the cell's content before it is saved to the data source.
//	Params:
//		col, row	- coordinates of cell currently saving
//		cell		- pointer to the cell object that is being saved
//	Return:
//		<none>
void CUGZiJinLiuShui::OnSetCell(int col,long row,CUGCell *cell)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*cell);
}

/////////////////////////////////////////////////////////////////////////////
//	OnDataSourceNotify
//		This message is sent from a data source and this message
//		depends on the data source - check the information
//		on the data source(s) being used
//		- The ID of the Data source is also returned
//	Params:
//		ID		- datasource ID
//		msg		- message ID to identify current process
//		param	- additional information or object that might be needed
//	Return:
//		<none>
void CUGZiJinLiuShui::OnDataSourceNotify(int ID,long msg,long param)
{
	UNREFERENCED_PARAMETER(ID);
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(param);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellTypeNotify
//		This notification is sent by the celltype and it is different from cell-type
//		to celltype and even from notification to notification.  It is usually used to
//		provide the developer with some feed back on the cell events and sometimes to
//		ask the developer if given event is to be accepted or not
//	Params:
//		ID			- celltype ID
//		col, row	- co-ordinates cell that is processing the message
//		msg			- message ID to identify current process
//		param		- additional information or object that might be needed
//	Return:
//		TRUE - to allow celltype event
//		FALSE - to disallow the celltype event
int CUGZiJinLiuShui::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	UNREFERENCED_PARAMETER(ID);
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(param);
	if(ID == m_nButtonIndex){
		return OnPushButton( ID, col, row, msg, param);
	}
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditStart
//		This message is sent whenever the grid is ready to start editing a cell
//	Params:
//		col, row - location of the cell that edit was requested over
//		edit -	pointer to a pointer to the edit control, allows for swap of edit control
//				if edit control is swapped permanently (for the whole grid) is it better
//				to use 'SetNewEditClass' function.
//	Return:
//		TRUE - to allow the edit to start
//		FALSE - to prevent the edit from starting
int CUGZiJinLiuShui::OnEditStart(int col, long row,CWnd **edit)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(**edit);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditVerify
//		This notification is sent every time the user hits a key while in edit mode.
//		It is mostly used to create custom behavior of the edit control, because it is
//		so easy to allow or disallow keys hit.
//	Params:
//		col, row	- location of the edit cell
//		edit		-	pointer to the edit control
//		vcKey		- virtual key code of the pressed key
//	Return:
//		TRUE - to accept pressed key
//		FALSE - to do not accept the key
int CUGZiJinLiuShui::OnEditVerify(int col, long row,CWnd *edit,UINT *vcKey)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*edit);
	UNREFERENCED_PARAMETER(*vcKey);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditFinish
//		This notification is sent when the edit is being finished
//	Params:
//		col, row	- coordinates of the edit cell
//		edit		- pointer to the edit control
//		string		- actual string that user typed in
//		cancelFlag	- indicates if the edit is being canceled
//	Return:
//		TRUE - to allow the edit to proceed
//		FALSE - to force the user back to editing of that same cell
int CUGZiJinLiuShui::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*edit);
	UNREFERENCED_PARAMETER(string);
	UNREFERENCED_PARAMETER(cancelFlag);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditContinue
//		This notification is called when the user pressed 'tab' or 'enter' keys
//		Here you have a chance to modify the destination cell
//	Params:
//		oldcol, oldrow - edit cell that is loosing edit focus
//		newcol, newrow - cell that the edit is going into, by changing their
//							values you are able to change where to edit next
//	Return:
//		TRUE - allow the edit to continue
//		FALSE - to prevent the move, the edit will be stopped
int CUGZiJinLiuShui::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(*newcol);
	UNREFERENCED_PARAMETER(*newrow);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuCommand
//		This notification is called when the user has selected a menu item
//		in the pop-up menu.
//	Params:
//		col, row - the cell coordinates of where the menu originated from
//		section - identify for which portion of the gird the menu is for.
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//		item - ID of the menu item selected
//	Return:
//		<none>
void CUGZiJinLiuShui::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	UNREFERENCED_PARAMETER(item);
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuStart
//		Is called when the pop up menu is about to be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		setcion		- identify for which portion of the gird the menu is for.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		TRUE - to allow menu to show
//		FALSE - to prevent the menu from poping up
int CUGZiJinLiuShui::OnMenuStart(int col,long row,int section)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetContextHelpID 
//		this notification is called as result of context help bing activated
//		over the UG area and should return context help ID to be displayed
//	Params:
//		col, row	- coordinates of cell which received the message
//		section		- grid section which received this message
//	Return:
//		Context help ID to be shown in the help.
DWORD CUGZiJinLiuShui::OnGetContextHelpID( int col, long row, int section )
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHint
//		Is called whent the hint is about to be displayed on the main grid area,
//		here you have a chance to set the text that will be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		string		- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int CUGZiJinLiuShui::OnHint(int col,long row,int section,CString *string)
{
	UNREFERENCED_PARAMETER(section);
	string->Format( _T("Col:%d Row:%ld") ,col,row);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnVScrollHint
//		Is called when the hint is about to be displayed on the vertical scroll bar,
//		here you have a chance to set the text that will be shown
//	Params:
//		row		- current top row
//		string	- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int CUGZiJinLiuShui::OnVScrollHint(long row,CString *string)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*string);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHScrollHint
//		Is called whent the hint is about to be displayed on the horizontal scroll bar,
//		here you have a chance to set the text that will be shown
//	Params:
//		col		- current left col
//		string	- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int CUGZiJinLiuShui::OnHScrollHint(int col,CString *string)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(*string);
	return TRUE;
}

#ifdef __AFXOLE_H__
/////////////////////////////////////////////////////////////////////////////
//	OLE
//		following 3 functions are to be used with drag and drop functionality
/////////////////////////////////////////////////////////////////////////////
//	OnDragEnter
//	Params:
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT CUGZiJinLiuShui::OnDragEnter(COleDataObject* pDataObject)
{
	UNREFERENCED_PARAMETER(*pDataObject);
	return DROPEFFECT_NONE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnDragOver
//	Params:
//		col, row	-
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT CUGZiJinLiuShui::OnDragOver(COleDataObject* pDataObject,int col,long row)
{
	UNREFERENCED_PARAMETER(*pDataObject);
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	return DROPEFFECT_NONE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnDragDrop
//	Params:
//		col, row	-
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT CUGZiJinLiuShui::OnDragDrop(COleDataObject* pDataObject,int col,long row)
{
	UNREFERENCED_PARAMETER(*pDataObject);
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	return DROPEFFECT_NONE;
}
#endif

/////////////////////////////////////////////////////////////////////////////
//	OnScreenDCSetup
//		Is called when each of the components are painted.
//	Params:
//		dc		- pointer to the current CDC object
//		section	- section of the grid painted.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		<none>
void CUGZiJinLiuShui::OnScreenDCSetup(CDC *dc,int section)
{
	UNREFERENCED_PARAMETER(*dc);
	UNREFERENCED_PARAMETER(section);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSortEvaluate
//		Sent as a result of the 'SortBy' call, this is called for each cell
//		comparison and allows for customization of the sorting routines.
//		We provide following code as example of what could be done here,
//		you might have to modify it to give your application customized sorting.
//	Params:
//		cell1, cell2	- pointers to cells that are compared
//		flags			- identifies sort direction
//	Return:
//		value less than zero to identify that the cell1 comes before cell2
//		value equal to zero to identify that the cell1 and cell2 are equal
//		value greater than zero to identify that the cell1 comes after cell2
int CUGZiJinLiuShui::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
	// if one of the cells is NULL, do not compare its text
	if ( cell1 == NULL && cell2 == NULL )
		return 0;
	else if ( cell1 == NULL )
		return 1;
	else if ( cell2 == NULL )
		return -1;

	if(flags&UG_SORT_DESCENDING)
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}

	// initialize variables for numeric check
	double num1, num2;
	// compare the cells, with respect to the cell's datatype
	switch(cell1->GetDataType())
	{
	case UGCELLDATA_STRING:
		if(NULL == cell1->GetText() && NULL == cell2->GetText())
			return 0;
		if(NULL == cell1->GetText())
			return 1;
		if(NULL == cell2->GetText())
			return -1;
		return _tcscmp(cell1->GetText(),cell2->GetText());	
	case UGCELLDATA_NUMBER:
	case UGCELLDATA_BOOL:
	case UGCELLDATA_CURRENCY:
		num1 = cell1->GetNumber();
		num2 = cell2->GetNumber();
		if(num1 < num2)
			return -1;
		if(num1 > num2)
			return 1;
		return 0;
	default:
		// if datatype is not recognized, compare cell's text
		if(NULL == cell1->GetText())
			return 1;
		if(NULL == cell2->GetText())
			return -1;
		return _tcscmp(cell1->GetText(),cell2->GetText());	
	}
}

/////////////////////////////////////////////////////////////////////////////
//	OnTabSelected
//		Called when the user selects one of the tabs on the bottom of the screen
//	Params:
//		ID	- id of selected tab
//	Return:
//		<none>
void CUGZiJinLiuShui::OnTabSelected(int ID)
{
	UNREFERENCED_PARAMETER(ID);
}

/////////////////////////////////////////////////////////////////////////////
//	OnAdjustComponentSizes
//		Called when the grid components are being created,
//		sized, and arranged.  This notification provides
//		us with ability to further customize the way
//		the grid will be presented to the user.
//	Params:
//		grid, topHdg, sideHdg, cnrBtn, vScroll, hScroll, 
//		tabs	- sizes and location of each of the grid components
//	Return:
//		<none>
void CUGZiJinLiuShui::OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,
	RECT *cnrBtn,RECT *vScroll,RECT *hScroll,RECT *tabs)
{
	UNREFERENCED_PARAMETER(*grid);
	UNREFERENCED_PARAMETER(*topHdg);
	UNREFERENCED_PARAMETER(*sideHdg);
	UNREFERENCED_PARAMETER(*cnrBtn);
	UNREFERENCED_PARAMETER(*vScroll);
	UNREFERENCED_PARAMETER(*hScroll);
	UNREFERENCED_PARAMETER(*tabs);
} 

/////////////////////////////////////////////////////////////////////////////
//	OnDrawFocusRect
//		Called when the focus rect needs to be painted.
//	Params:
//		dc		- pointer to the current CDC object
//		rect	- rect of the cell that requires the focus rect
//	Return:
//		<none>
void CUGZiJinLiuShui::OnDrawFocusRect(CDC *dc,RECT *rect)
{
	//DrawExcelFocusRect(dc,rect);

	//rect->bottom --;
	//rect->right --;	
	//dc->DrawFocusRect(rect);
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetDefBackColor
//		Sent when the area behind the grid needs to be painted.
//	Params:
//		section - Id of the grid section that requested this color
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		RGB value representing the color of choice
COLORREF CUGZiJinLiuShui::OnGetDefBackColor(int section)
{
	UNREFERENCED_PARAMETER(section);
	return RGB(255,255,255);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetFocus
//		Sent when the grid is gaining focus.
//	Note:
//		The grid will loose focus when the edit is started, or drop list shown
//	Params:
//		section - Id of the grid section gaining focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		<none>
//
void CUGZiJinLiuShui::OnSetFocus(int section)
{
	UNREFERENCED_PARAMETER(section);
}

/////////////////////////////////////////////////////////////////////////////
//	OnKillFocus
//		Sent when the grid is loosing focus.
//	Params:
//		section - Id of the grid section loosing focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//		pNewWnd	- pointer to the window that is gaining focus
//	Return:
//		<none>
void CUGZiJinLiuShui::OnKillFocus(int section, CWnd *pNewWnd)
{
	UNREFERENCED_PARAMETER(section);
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSwapStart
//		Called to inform the grid that the col swap was started on given col.
//	Params:
//		col - identifies the column
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL CUGZiJinLiuShui::OnColSwapStart(int col)
{
	UNREFERENCED_PARAMETER(col);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanColSwap
//		Called when col swap is about to take place, here you can 'lock' certain
//		cols in place so that are not swappable.
//	Params:
//		fromCol - where the col originated from
//		toCol	- where the col will be located if the swap is allowed
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL CUGZiJinLiuShui::OnCanColSwap(int fromCol,int toCol)
{
	UNREFERENCED_PARAMETER(fromCol);
	UNREFERENCED_PARAMETER(toCol);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSwapped
//		Called just after column-swap operation was completed.
//	Params:
//		fromCol - where the col originated from
//		toCol	- where the col will be located if the swap is allowed
//	Return:
//		<none>
void CUGZiJinLiuShui::OnColSwapped(int fromCol,int toCol)
{
	UNREFERENCED_PARAMETER(fromCol);
	UNREFERENCED_PARAMETER(toCol);
}

/////////////////////////////////////////////////////////////////////////////
//	OnTrackingWindowMoved
//		Called to notify the grid that the tracking window was moved
//	Params:
//		origRect	- from
//		newRect		- to location and size of the track window
//	Return:
//		<none>
void CUGZiJinLiuShui::OnTrackingWindowMoved(RECT *origRect,RECT *newRect)
{
	UNREFERENCED_PARAMETER(*origRect);
	UNREFERENCED_PARAMETER(*newRect);
}

void CUGZiJinLiuShui::InitGrid(void)
{

	m_nCols=10 ;
	m_nLightRow=1;

	CUGCell		cell;

	SetNumberCols(m_nCols);
	SetUserSizingMode( 2 );
	//SetNumberRows(m_nRows);
	SetSH_Width( 0 );
	SetTH_Height( 0 );
	//设置标题行的内容
	QuickSetText(0,0, _T("行号"));  
	QuickSetText(1,0, _T("日期"));//单据日期
	QuickSetText(2,0, _T("业务编号")); 
	QuickSetText(3,0, _T("往来单位")); 
	QuickSetText(4,0, _T("收支项目")); //销售金额
	QuickSetText(5,0, _T("收入金额")); 
	QuickSetText(6,0, _T("支出金额"));
	QuickSetText(7,0, _T("备注"));
	JoinCells(8,0,9,0);
	QuickSetText(8,0, _T("操作")); 
	QuickSetText(9,0, _T("ID"));
	//38的两个按钮 40+100+150+100*4+130+38*2= 820+76=896
	SetColWidth(0, 40); 
	

	SetColWidth(1, 100);
	SetColWidth(2, 0);//150
	SetColWidth(3, 150);
	SetColWidth(4, 150);
	SetColWidth(5, 150);
	SetColWidth(6, 150);
	SetColWidth(7, 160);

	SetColWidth(8, 0);
	SetColWidth(9, 0);
	//编译器是543，程序里是820
	//   594  593.3        现在程序896
	                       // 838
	//设置标题列的列内容，背景色，文本颜色
	CString strHangHao;
	for(int i=1;i<m_nRows;i++)
	{
		strHangHao.Format(_T("%d"),i);
		QuickSetText(0,i, strHangHao);

		QuickSetBackColor(0,i, RGB(240,240,240) ); 
		QuickSetTextColor(0, i, RGB(40,55,100) );
		QuickSetAlignment(0, i, UG_ALIGNCENTER|UG_ALIGNVCENTER);
	}

	//设置标题行的背景色和文本颜色
	for (int i=0;i<m_nCols;i++)
	{
		QuickSetBackColor(i,0, RGB(240,240,240) ); 
		QuickSetTextColor(i, 0, RGB(40,55,100) );
		QuickSetAlignment(i, 0, UG_ALIGNCENTER|UG_ALIGNVCENTER); 
	}

	//设置行高
	for(int i=0;i<m_nRows;i++)
	{
		SetRowHeight(i,25);
	}

	for (int i=1;i<m_nCols;i++)
	{
		QuickSetBackColor(i,1, RGB(225,235,255) ); 

	}


	m_nLightRow=1;

	QuickSetBackColor(0,m_nLightRow,RGB(115,153,188));
	for(int i=1;i<m_nCols;i++)
	{
		QuickSetBackColor(i,m_nLightRow,GridSelectRowColor);
	}


}

void CUGZiJinLiuShui::OnSize(UINT nType, int cx, int cy)
{
	CUGCtrl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
void CUGZiJinLiuShui::InitData(COleDateTime oleDateTimeFrom,COleDateTime oleDateTimeTo)
{
	CString strOleDateTimeFrom =oleDateTimeFrom.Format(_T("%Y-%m-%d"));

	CString strOleDateTimeTo =oleDateTimeTo.Format(_T("%Y-%m-%d"));
	try{
		CString strSQL=_T("");

		strSQL.Format(_T("select Account.AccountDate as RiQi,\
						 Account.AccountCode as BianHao,\
						 Account.CompanyName as MingCheng,\
						 Account.InAmount as ShouRu,\
						 Account.OutAmount as ZhiChu,\
						 Account.ProjectName as ProjectName,\
						 Account.remark as remark from   Account  where RiQi>='%s' and  RiQi<='%s' union  all select JinhuoDanLiShi.XiaoShouRiQi as RiQi,\
						 JinhuoDanLiShi.DanJuBianHao as BianHao,\
						 JinhuoDanLiShi.KeHuMingCheng as MingCheng,\
						 JinhuoDanLiShi.Sync as ShouRu,\
						 JinhuoDanLiShi.ShouKuanJinE as ZhiChu,\
						 JinhuoDanLiShi.ProjectName as ProjectName,\
						 JinhuoDanLiShi.ShuoMing as remark  from JinhuoDanLiShi  where RiQi>='%s' and  RiQi<='%s' union all select  XiaoShouDanLiShi.XiaoShouRiQi as RiQi,\
						 XiaoShouDanLiShi.DanJuBianHao as BianHao,\
						 XiaoShouDanLiShi.KeHuMingCheng as MingCheng,\
						 XiaoShouDanLiShi.ShouKuanJinE as ShouRu, \
						 XiaoShouDanLiShi.Sync as ZhiCHu,\
						 XiaoShouDanLiShi.ProjectName as ProjectName,\
						 XiaoShouDanLiShi.ShuoMing as remark from   XiaoShouDanLiShi  where RiQi>='%s' and  RiQi<='%s' order by RiQi  asc;"),strOleDateTimeFrom,strOleDateTimeTo,strOleDateTimeFrom,strOleDateTimeTo,strOleDateTimeFrom,strOleDateTimeTo);
		//strSQL.Format(_T("select * from XiaoShouDanLiShi where RiQi>='%s' and  RiQi<='%s';"),strOleDateTimeFrom,strOleDateTimeTo);
		CUGCell cell;
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CppSQLite3Query q = db.execQuery(strSQL);//销售单历史表

		
		int i=1;
		CString strBillCode;;
		while (!q.eof())
		{
			strBillCode=q.fieldValue(_T("RiQi"));//销售日期
			QuickSetText(1,i,strBillCode);
			strBillCode=q.fieldValue(_T("BianHao"));//单据编号
			QuickSetText(2,i,strBillCode);
			strBillCode=q.fieldValue(_T("MingCheng"));//往来单位
			QuickSetText(3,i,strBillCode);

			strBillCode=q.fieldValue(_T("ProjectName"));//收支项目
			QuickSetText(4,i,strBillCode);
			strBillCode=q.fieldValue(_T("ShouRu"));//收入

			QuickSetText(5,i,strBillCode);
			strBillCode=q.fieldValue(_T("ZhiChu"));//支出
			QuickSetText(6,i,strBillCode);


			strBillCode=q.fieldValue(_T("remark"));//说明
			QuickSetText(7,i,strBillCode);



			
				QuickSetCellTypeEx(3,i,UGCT_NORMALELLIPSIS);
			QuickSetCellTypeEx(4,i,UGCT_NORMALELLIPSIS);
			QuickSetCellTypeEx(7,i,UGCT_NORMALELLIPSIS);

		GetCell(8,i,&cell);
			cell.SetText(_T("删除"));
			cell.SetCellType(m_nButtonIndex);
			cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS);
			cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
			cell.SetTextColor(RGB(0,0,128));
			cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
			cell.SetParam(BUTTON_CLICK_DEL);
			SetCell(8,i,&cell);

			GetCell(9,i,&cell);
			cell.SetText(_T("修改"));
			cell.SetCellType(m_nButtonIndex);
			cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS);
			cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
			cell.SetTextColor(RGB(0,0,128));
			cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
			cell.SetParam(BUTTON_CLICK_CHANGE);
			SetCell(9,i,&cell);



			//strBillCode=q.fieldValue(_T("ID"));//说明
			//QuickSetText(10,i,strBillCode);
			q.nextRow();
			i++;
		}
	}

	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	GetYeWuBianHao(2,1);//默认选择一个业务编号
}



long CUGZiJinLiuShui::GetRowCount(COleDateTime oleDateTimeFrom,COleDateTime oleDateTimeTo)
{
	long nRows=0;

	CString strOleDateTimeFrom =oleDateTimeFrom.Format(_T("%Y-%m-%d"));

	CString strOleDateTimeTo =oleDateTimeTo.Format(_T("%Y-%m-%d"));


	CString strSQL=_T("");

	/*strSQL.Format(_T("select Account.AccountDate as RiQi,\
					 Account.AccountCode as BianHao,\
					 Account.CompanyName as MingCheng,\
					 Account.InAmount as ShouRu,\
					 Account.OutAmount as ZhiChu,\
					 Account.remark as remark from   Account where RiQi>='%s' and  RiQi<='%s' union  all select JinhuoDanLiShi.XiaoShouRiQi as RiQi,\
					 JinhuoDanLiShi.DanJuBianHao as BianHao,\
					 JinhuoDanLiShi.KeHuMingCheng as MingCheng,\
					 JinhuoDanLiShi.Sync as ShouRu,\
					 JinhuoDanLiShi.ShouKuanJinE as ZhiChu,\
					 JinhuoDanLiShi.ShuoMing as remark  from JinhuoDanLiShi where RiQi>='%s' and  RiQi<='%s' union all select  XiaoShouDanLiShi.XiaoShouRiQi as RiQi,\
					 XiaoShouDanLiShi.DanJuBianHao as BianHao,\
					 XiaoShouDanLiShi.KeHuMingCheng as MingCheng,\
					 XiaoShouDanLiShi.ShouKuanJinE as ShouRu, \
					 XiaoShouDanLiShi.Sync as ZhiCHu,\
					 XiaoShouDanLiShi.ShuoMing as remark from   XiaoShouDanLiShi  where RiQi>='%s' and  RiQi<='%s' order by RiQi  asc;"),strOleDateTimeFrom,strOleDateTimeTo,strOleDateTimeFrom,strOleDateTimeTo,strOleDateTimeFrom,strOleDateTimeTo);;*/
	strSQL.Format(_T("select Account.AccountDate as RiQi,\
					 Account.AccountCode as BianHao,\
					 Account.CompanyName as MingCheng,\
					 Account.InAmount as ShouRu,\
					 Account.OutAmount as ZhiChu,\
					 Account.ProjectName as ProjectName,\
					 Account.remark as remark from   Account  where RiQi>='%s' and  RiQi<='%s' union  all select JinhuoDanLiShi.XiaoShouRiQi as RiQi,\
					 JinhuoDanLiShi.DanJuBianHao as BianHao,\
					 JinhuoDanLiShi.KeHuMingCheng as MingCheng,\
					 JinhuoDanLiShi.Sync as ShouRu,\
					 JinhuoDanLiShi.ShouKuanJinE as ZhiChu,\
					 JinhuoDanLiShi.ProjectName as ProjectName,\
					 JinhuoDanLiShi.ShuoMing as remark  from JinhuoDanLiShi  where RiQi>='%s' and  RiQi<='%s' union all select  XiaoShouDanLiShi.XiaoShouRiQi as RiQi,\
					 XiaoShouDanLiShi.DanJuBianHao as BianHao,\
					 XiaoShouDanLiShi.KeHuMingCheng as MingCheng,\
					 XiaoShouDanLiShi.ShouKuanJinE as ShouRu, \
					 XiaoShouDanLiShi.Sync as ZhiCHu,\
					 XiaoShouDanLiShi.ProjectName as ProjectName,\
					 XiaoShouDanLiShi.ShuoMing as remark from   XiaoShouDanLiShi  where RiQi>='%s' and  RiQi<='%s' order by RiQi  asc;"),strOleDateTimeFrom,strOleDateTimeTo,strOleDateTimeFrom,strOleDateTimeTo,strOleDateTimeFrom,strOleDateTimeTo);

	try{
		CppSQLite3DB db;
		db.open(CBoBoDingApp::g_strDatabasePath);
		CppSQLite3Query q = db.execQuery(strSQL);
		while (!q.eof())
		{
			nRows++;q.nextRow();
		}


	}


	catch (CppSQLite3Exception& e)
	{

		AfxMessageBox(e.errorMessage());
	}
	m_nRows=nRows+1;
	if (nRows<18)
	{nRows=18;
	m_nRows=nRows+1;

	}

	return m_nRows;
}



void CUGZiJinLiuShui::SQLQuery(COleDateTime oleDateTimeFrom,COleDateTime oleDateTimeTo)
{
	m_oleDateTime_timeFrom =oleDateTimeFrom;
		m_oleDateTime_timeTo=oleDateTimeTo;
GetDataSource(0)->Empty();

SetNumberRows(GetRowCount( oleDateTimeFrom, oleDateTimeTo));
InitGrid();
InitData( oleDateTimeFrom, oleDateTimeTo);
Invalidate(TRUE);
}

CString CUGZiJinLiuShui::GetYeWuBianHao(int nCol,long nRow)
{

	m_strYeWuBianHao=QuickGetText(nCol,nRow);

	return m_strYeWuBianHao;
}
double CUGZiJinLiuShui:: GetTotalIn()
{
	double nSum=0;


	CString strSum=_T("");
	CUGCell		cell;
	cell.GetNumber();
	for (int i=1;i<m_nRows-1;i++)
	{
		GetCell(5, i, &cell );
		nSum=nSum+cell.GetNumber();	
	}

	return nSum;
}
double CUGZiJinLiuShui::GetTotalOut()
{
	double nSum=0;


	CString strSum=_T("");
	CUGCell		cell;
	cell.GetNumber();
	for (int i=1;i<m_nRows-1;i++)
	{
		GetCell(6, i, &cell );
		nSum=nSum+cell.GetNumber();	
	}

	return nSum;
}
int CUGZiJinLiuShui::OnPushButton(long ID,int col,long row,long msg,long param){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(msg == UGCT_BUTTONCLICK){
		if(nParam == BUTTON_CLICK_CHANGE){
			//WinExec("calc.exe",SW_SHOW);
		/*	CString strYeWuBianHao;
			strYeWuBianHao=m_ctrl.m_strYeWuBianHao;*/
			CString strTruncate;
			strTruncate=m_strYeWuBianHao.Left(2);
			if(strTruncate.Compare(_T("SZ"))!=0)return TRUE;
			ReleaseCapture();
			CDlgZiJinLiuShuiShouRuChange DlgZiJinLiuShuiShouRuChange;

			DlgZiJinLiuShuiShouRuChange.m_strYeWuBianHao=m_strYeWuBianHao;

			DlgZiJinLiuShuiShouRuChange.DoModal();
			if (DlgZiJinLiuShuiShouRuChange.m_bIsSave==true)
			{
				//SetButtonStatus();
				//UpdateData(TRUE);
				SQLQuery(m_oleDateTime_timeFrom , m_oleDateTime_timeTo);
			}
		}
		else if(nParam == BUTTON_CLICK_DEL){
		ReleaseCapture();
			CString strPrompt;
			strPrompt.Format(_T("您确定要删除编号是 %s 的记录吗？"),m_strYeWuBianHao);

			if ((MessageBox(strPrompt,_T("提示"),MB_OKCANCEL)==IDOK))
			{
				//AfxMessageBox(_T("1"));
				try{
					CString strSQL;
					CppSQLite3DB db;
					db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
					db.execDML(_T("BEGIN TRANSACTION;"));
					strSQL.Format(_T("DELETE FROM Account WHERE AccountCode='%s'"),(m_strYeWuBianHao));
				
					db.execDML(strSQL);
					db.execDML(_T("COMMIT TRANSACTION;"));



				}
				catch (CppSQLite3Exception& e)
				{

					AfxMessageBox(e.errorMessage());
				}
				SQLQuery(m_oleDateTime_timeFrom , m_oleDateTime_timeTo);
			}
		}

		//	else{
		//		MessageBox("The button was clicked","Cell Type Notification");
		//	}
		//}
		//if(msg == UGCT_BUTTONDOWN){
		//	if(nParam == BUTTON_CLICK3){
		//		MessageBox("The button pressed","Cell Type Notification");
		//	}
	}

	return TRUE;
}


CString CUGZiJinLiuShui::GetID()
{
	return _T("");
}
void CUGZiJinLiuShui::Change()
{

	
	if (m_strYeWuBianHao.IsEmpty())return;

	CDlgZiJinLiuShuiShouRuChange DlgZiJinLiuShuiShouRuChange;

	DlgZiJinLiuShuiShouRuChange.m_strYeWuBianHao=m_strYeWuBianHao;

	DlgZiJinLiuShuiShouRuChange.DoModal();
	if (DlgZiJinLiuShuiShouRuChange.m_bIsSave==true)
	{
		//SetButtonStatus();
		//UpdateData(TRUE);
		SQLQuery(m_oleDateTime_timeFrom , m_oleDateTime_timeTo);
	}
}
void CUGZiJinLiuShui::Del()
{
	
	if (m_strYeWuBianHao.IsEmpty())return;

	CString strPrompt;
	strPrompt.Format(_T("您确定要删除行号是 %s 的记录吗？"),QuickGetText(0,m_nLightRow));

	if ((MessageBox(strPrompt,_T("提示"),MB_OKCANCEL)==IDOK))
	{
		//AfxMessageBox(_T("1"));
		try{
			CString strSQL;
			CppSQLite3DB db;
			db.open(CBoBoDingApp::g_strDatabasePath);//打开数据库
			db.execDML(_T("BEGIN TRANSACTION;"));
			strSQL.Format(_T("DELETE FROM Account WHERE AccountCode='%s'"),(m_strYeWuBianHao));

			db.execDML(strSQL);
			db.execDML(_T("COMMIT TRANSACTION;"));



		}
		catch (CppSQLite3Exception& e)
		{

			AfxMessageBox(e.errorMessage());
		}
		SQLQuery(m_oleDateTime_timeFrom , m_oleDateTime_timeTo);
	}
}

void CUGZiJinLiuShui::Export()
{
	CString strFilePathName;
	CFileDialog dlg(FALSE,_T("xls"),_T("记账"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("表格文件(*.xls)|*.xls|所有文件(*.*)|*.*||"));///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if(dlg.DoModal()==IDOK)
	{
		strFilePathName=dlg.GetPathName();
		if (!strFilePathName.IsEmpty())
		{

			BasicExcel e;
			e.New(1);
			BasicExcelWorksheet* sheet = e.GetWorksheet("Sheet1");
			if (sheet)
			{
				int k=0;
				CString strTemp=_T("");
				for (int i=0;i<m_nRows;i++)
				{
					for (int j=1;j<m_nCols-2;j++)//删除 修改 ID
					{
						if(j==2)continue;

						if (j>2)
							k=j-2;
						else
						k=j-1;

						strTemp=QuickGetText(j,i);
						if (!strTemp.IsEmpty())
						{
							sheet->Cell(i,k)->SetWString(strTemp);
						}
					}
				}
			}
			e.SaveAs(StringToChar(strFilePathName));
		}
	}
}


char* CUGZiJinLiuShui::StringToChar(CString strOriginal)
{
	strOriginal.ReleaseBuffer();
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,strOriginal,-1,NULL,0,NULL,FALSE);
	char *psText = new char[dwNum];
	WideCharToMultiByte (CP_OEMCP,NULL,strOriginal,-1,psText,dwNum,NULL,FALSE);
	return  psText;
}