#include "stdafx.h"
#include "XSignalProperty.h"
#include "XConstant.h"
#include "XTranslationManage.h"



IMPLEMENT_DYNAMIC(XSignalProperty,XBaseDialog)

XSignalProperty::XSignalProperty(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XSignalProperty::IDD,pParent)
{

}

XSignalProperty::~XSignalProperty()
{
}

void XSignalProperty::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	//DDX_Control(pDX,IDC_STATIC_INFO,m_TextInfo);
	//DDX_Control(pDX,IDC_STATIC_COPYRIGHT,m_TextCopyRight);
	//DDX_Control(pDX,IDC_STATIC_FPGA,m_TextFPGA);
	//DDX_Control(pDX,IDC_STATIC_VER,m_TextVer);
	//DDX_Control(pDX,IDC_STATIC_UPDATELOG,m_TextUpdate);
	//DDX_Control(pDX,IDC_STATIC_VER2,m_TextVer2);
	//DDX_Control(pDX,IDC_STATIC_UPDATELOG2,m_TextUpdate2);
	//DDX_Control(pDX,IDC_STATIC_VER3,m_TextVer3);
	//DDX_Control(pDX,IDC_STATIC_UPDATELOG3,m_TextUpdate3);
	//DDX_Control(pDX,IDC_BTN_UPDATE,m_BtnUpdate);
	DDX_Control(pDX,ID_OK,m_BtnOk);

}


BEGIN_MESSAGE_MAP(XSignalProperty,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XSignalProperty::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XSignalProperty::Init()
{
	SetWindowText(_C(_T("65"),_T("����")));

	ReloadInterface();
}

void XSignalProperty::ReloadInterface()
{

}

void XSignalProperty::OnBtnOk()
{
	TRACE(_T("property\n"));

	//CString md5(XMD5("abc").toString().c_str());
	//TRACE(_T("abc=%s\n"),md5);

	//CString md52(XMD5("abcd").toString().c_str());
	//TRACE(_T("abcd=%s\n"),md52);

}

LRESULT XSignalProperty::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
		case ID_OK:
			{
				OnBtnOk();
			}
			break;
		default:
			break;
	}

	return 0;
}