// DlgSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BoBoDing.h"
#include "DlgSetting.h"
#include "afxdialogex.h"


// CDlgSetting �Ի���

IMPLEMENT_DYNAMIC(CDlgSetting, CDialogEx)

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetting::IDD, pParent)
{

}

CDlgSetting::~CDlgSetting()
{
}

void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSetting, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_START, &CDlgSetting::OnBnClickedCheckStart)
END_MESSAGE_MAP()


// CDlgSetting ��Ϣ�������


void CDlgSetting::OnBnClickedCheckStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CString strGetStringValue;
	//TCHAR s[_MAX_PATH];
	//DWORD len=_MAX_PATH;
	//CRegKey key;
	//if (key.Open(HKEY_LOCAL_MACHINE,_T("SOFTWARE//Microsoft//Windows//CurrentVersion//Run"))==ERROR_SUCCESS)
	//{
	//	if(key.QueryStringValue(_T("name"),s,&len)==ERROR_SUCCESS)
	//	{
	//		strGetStringValue=s;
	//	}
	//	key.Close();

	//}



}
