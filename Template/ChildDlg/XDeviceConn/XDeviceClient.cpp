#include "stdafx.h"
#include "XDeviceClient.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"


// XDeviceClient 对话框

IMPLEMENT_DYNAMIC(XDeviceClient,XBaseDialog)

XDeviceClient::XDeviceClient(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XDeviceClient::IDD,pParent)
{

}

XDeviceClient::~XDeviceClient()
{
}

void XDeviceClient::DoDataExchange(CDataExchange* pDX)
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
	//DDX_Control(pDX,ID_BTN_OK,m_BtnOk);

}


BEGIN_MESSAGE_MAP(XDeviceClient,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XDeviceClient::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XDeviceClient::Init()
{
	SetWindowText(_C(_T("360"),_T("客户端")));

	ReloadInterface();
}

void XDeviceClient::ReloadInterface()
{

}

LRESULT XDeviceClient::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{

	return 0;
}