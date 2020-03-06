#include "stdafx.h"
#include "XDeviceConn.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "HandlePath.h"
#include "XDeviceServer.h"
#include "XDeviceClient.h"
#include "XSendDataManage.h"
#include "XDelegateDeviceConn.h"


// XDeviceConn 对话框

IMPLEMENT_DYNAMIC(XDeviceConn,XBaseDialog)

XDeviceConn::XDeviceConn(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XDeviceConn::IDD,pParent)
{

}

XDeviceConn::~XDeviceConn()
{
}

void XDeviceConn::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_SERVER,m_TextSetver);
	DDX_Control(pDX,IDC_STATIC_CLIENT,m_TextClient);
	DDX_Control(pDX,IDC_STATIC_TIP,m_TextTip);
	DDX_Control(pDX,IDC_BTN_CLIENT,m_BtnClient);
	DDX_Control(pDX,IDC_BTN_SERVER,m_BtnServer);

}


BEGIN_MESSAGE_MAP(XDeviceConn,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XDeviceConn::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XDeviceConn::Init()
{
	SetWindowText(_C(_T("358"),_T("设备互联")));

	//获取服务端信息
	XSendDataManage::GetInstance()->AddSendDataOfObtainAsServer();
	//获取客户端信息
	XSendDataManage::GetInstance()->AddSendDataOfObtainAsClient();

	ReloadInterface();
}

void XDeviceConn::ReloadInterface()
{
	m_TextTip.SetText(_C(_T("361"),_T("提示:当前连接设备当作客户端或者服务端")),TRUE);
	m_TextSetver.SetText(_C(_T("359"),_T("服务端")),FALSE,TRUE);
	m_TextClient.SetText(_C(_T("360"),_T("客户端")),FALSE,TRUE);


	m_BtnServer.SetImage(HandlePath::GetPhotoPath(_T("dserver.png")));
	m_BtnClient.SetImage(HandlePath::GetPhotoPath(_T("dclient.png")));
}

VEC_CLIENT& XDeviceConn::GetVecClient()
{
	return m_pDelegate->GetVecClient();
}

MAP_POWER& XDeviceConn::GetMapPower()
{
	return m_pDelegate->GetMapPower();
}

void XDeviceConn::SetServer()
{
	TRACE(_T("Server\n"));

	XDeviceServer dlg;
	m_pDeviceServer=&dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();

	m_pDeviceServer=NULL;

}

void XDeviceConn::CloseAlterPortDlg()
{
	if(NULL!=m_pDeviceServer)
	{
		m_pDeviceServer->CloseAlterPortDlg();
	}
}

void XDeviceConn::SetClient()
{
	TRACE(_T("Client\n"));

	XDeviceClient dlg;
	dlg.DoModal();

}

LRESULT XDeviceConn::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
		case IDC_BTN_SERVER:
			{
				SetServer();
			}
			break;
		case IDC_BTN_CLIENT:
			{
				SetClient();
			}
			break;
		default:
			break;
	}

	return 0;
}
