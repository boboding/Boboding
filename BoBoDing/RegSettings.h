// RegSettings.h: interface for the CRegSettings class.
//
//////////////////////////////////////////////////////////////////////




#pragma once




class CRegSettings  
{
public:
	//static CString m_strSubKey;
	CRegSettings();

	virtual ~CRegSettings();

	BOOL SetProfileString(LPCTSTR, LPCTSTR, LPCTSTR);
	BOOL SetProfileInt(LPCTSTR, LPCTSTR, int);

	CString ReadProfileString(LPCTSTR, LPCTSTR, LPCTSTR);

	UINT ReadProfileInt(LPCTSTR, LPCTSTR, int);
};


