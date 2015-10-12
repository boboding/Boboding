// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。


#include "stdafx.h"
#include "explorer_shopping.h"

/////////////////////////////////////////////////////////////////////////////
// CExplorer_shopping

IMPLEMENT_DYNCREATE(CExplorer_shopping, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CExplorer_shopping 属性

/////////////////////////////////////////////////////////////////////////////
// CExplorer_shopping 操作


BOOL CExplorer_shopping::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(WM_RBUTTONDOWN == pMsg->message)//禁止浏览器的右键
	{

		return TRUE;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}
