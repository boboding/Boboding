
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


//#define DialogBackgroundColor RGB(225,235,255) //���屳��ɫ
//#define DialogBackgroundColor RGB(105,161,191)

//#define DialogSubBackgroundColor RGB(76,85,89)
//#define BoBoDingWindowWidth 896
#define BoBoDingWindowWidth 915
#define BoBoDingWindowHeight 567

#define VerticalWidth 58
//#define VerticalHeight 720
#define VerticalHeight 580

//#define HorizontalWidth 536
#define HorizontalHeight 70
#define HorizontalWidth 432


#define TITLETEXT _T("�������Ƹ��� 2.2")
#define TOOLINTERVAL 5
#define MINSIZEX 920
#define MINSIZEY 680
//#define MINSIZEX 1024
//#define MINSIZEY 728
//#define MINSIZEY 600
#define TOOLHEIGHT 71
#define TOOLWIDTH 71
#define CAPTIONHEIGHT 24
//#define BACKGROUNDCOLOR   RGB(105,161,191)
#define LISTCONTROLBACKGROUNDCOLOR RGB(76,85,89)

//#define TABBACKGROUNDCOLOR RGB(76,85,89)
#define TABBACKGROUNDCOLOR RGB(16,60,93)
#define DialogBackgroundColor RGB(16,60,93)
//#define DialogBackgroundColor RGB(71,91,126)

#define GridCaptionColor RGB(240,240,240) //������ⵥԪ�����ɫ
#define GridSelectRowColor RGB(218,225,230) //����ѡ���е���ɫ
#define StaticCaptionColor    RGB(41,57,85) //������ı���ɫ
#define DialogSubBackgroundColor  RGB(218,225,230)


#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include "SQLite\CppSQLite3U.h"


#pragma warning(disable:4244)


#pragma warning(disable : 4786)	// too long identifiers.
#include "TabCtrl\TabCtrl.h"
struct TabCtrlComplex : public TabCtrl
{	TabCtrlStyle_base styleBase;
// 
TabCtrlStyle_VS2003_client styleVS2003_client;
TabCtrlStyle_VS2003_client_custom1 styleVS2003_client_custom1;
TabCtrlStyle_VS2003_bars styleVS2003_bars;
TabCtrlStyle_VS2003_bars_custom1 styleVS2003_bars_custom1;
// 
TabCtrlStyle_VS2008_client_classic styleVS2008_client_classic;
TabCtrlStyle_VS2008_client_blue styleVS2008_client_blue;
TabCtrlStyle_VS2008_client_silver styleVS2008_client_silver;
TabCtrlStyle_VS2008_client_olive styleVS2008_client_olive;
TabCtrlStyle_VS2008_bars_classic styleVS2008_bars_classic;
TabCtrlStyle_VS2008_bars_classic_custom1 styleVS2008_bars_classic_custom1;
TabCtrlStyle_VS2008_bars_blue styleVS2008_bars_blue;
TabCtrlStyle_VS2008_bars_blue_custom1 styleVS2008_bars_blue_custom1;
TabCtrlStyle_VS2008_bars_silver styleVS2008_bars_silver;
TabCtrlStyle_VS2008_bars_silver_custom1 styleVS2008_bars_silver_custom1;
TabCtrlStyle_VS2008_bars_olive styleVS2008_bars_olive;
TabCtrlStyle_VS2008_bars_olive_custom1 styleVS2008_bars_olive_custom1;
// 
TabCtrlStyle_VS2010_client styleVS2010_client;
TabCtrlStyle_VS2010_client_custom1 styleVS2010_client_custom1;
TabCtrlStyle_VS2010_client_custom2 styleVS2010_client_custom2;
TabCtrlStyle_VS2010_bars styleVS2010_bars;
};
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


