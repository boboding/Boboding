// OrangeEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "OrangeEdit.h"


// COrangeEdit

IMPLEMENT_DYNAMIC(COrangeEdit, CEdit)

COrangeEdit::COrangeEdit()
{

}

COrangeEdit::~COrangeEdit()
{
}


BEGIN_MESSAGE_MAP(COrangeEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// COrangeEdit 消息处理程序




void COrangeEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	  
		 // 不允许输入数字和点以外的字符   
	if((nChar>=_T('0')&&nChar<=_T('9'))||nChar==VK_BACK ) 
	CEdit::OnChar(nChar, nRepCnt, nFlags);

	if((LOWORD(GetSel())==0) && (nChar == '.'))
	{ return;
	}
	if(nChar=='.')
	{ CString strTemp;
	int nPos = 0;
	GetWindowText(strTemp);
	nPos = strTemp.Find(nChar);
	if (nPos>=0)
	{return;
	} 
	else
	{
	}
	 return CEdit::OnChar(nChar, nRepCnt, nFlags);
	}

	
	//GetDlgItemText(IDC_EDIT1, str); 
	// 获取edit中文本 nPos = str.Find('.'); 
	// 查找.的位置 if(nPos>=0)
	//{ return TRUE; // 如果存在. 返回，即不再允许.输入 } } 

}
