// OrangeEdit.cpp : ʵ���ļ�
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



// COrangeEdit ��Ϣ�������




void COrangeEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	  
		 // �������������ֺ͵�������ַ�   
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
	// ��ȡedit���ı� nPos = str.Find('.'); 
	// ����.��λ�� if(nPos>=0)
	//{ return TRUE; // �������. ���أ�����������.���� } } 

}
