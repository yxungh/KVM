// XDeviceNet.cpp : 实现文件
//

#include "stdafx.h"
#include "XDeviceNet.h"
#include "afXDialogex.h"
#include "XDelegateDeviceNet.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "HandleCalculate.h"
#include "HandleIni.h"
#include "HandlePath.h"
#include "XSendDataManage.h"
#include "XConstant.h"
#include "XMessageBox.h"
#include "XThemeColor.h"

// XDeviceNet 对话框
#define TIMERID     1
#define TIMERSPACE  1000


IMPLEMENT_DYNAMIC(XDeviceNet,XBaseDialog)

XDeviceNet::XDeviceNet(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XDeviceNet::IDD,pParent)
{

}

XDeviceNet::~XDeviceNet()
{
	m_config.CLear();
}

void XDeviceNet::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Radio(pDX,IDC_RADIOSEL1,m_nRadioSel);
	//DDX_Control(pDX,IDC_STATIC_DEVICE1,m_TextDevice1);
	//DDX_Control(pDX,IDC_STATIC_DEVICE2,m_TextDevice2);
	DDX_Control(pDX,IDC_STATIC_IP1,m_TextIP1);
	DDX_Control(pDX,IDC_STATIC_IP2,m_TextIP2);
	DDX_Control(pDX,IDC_STATIC_MASK,m_TextMask1);
	DDX_Control(pDX,IDC_STATIC_GATEWAY,m_TextGetWay1);
	DDX_Control(pDX,IDC_STATIC_PORT1,m_TextPort1);
	DDX_Control(pDX,IDC_STATIC_PORT2,m_TextPort2);
	DDX_Control(pDX,IDC_STATIC_MASK2,m_TextMask2);
	DDX_Control(pDX,IDC_STATIC_GATEWAY2,m_TextGetWay2);

	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}

BEGIN_MESSAGE_MAP(XDeviceNet,XBaseDialog)
	ON_COMMAND(IDOK,OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIOSEL1,OnBnClickedRadiosel1)
	ON_BN_CLICKED(IDC_RADIOSEL2,OnBnClickedRadiosel1)

	ON_BN_CLICKED(IDC_CHECK_OPEN1,&XDeviceNet::OnBnClickedCheckOpen1)
	ON_BN_CLICKED(IDC_CHECK_OPEN2,&XDeviceNet::OnBnClickedCheckOpen2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// XDeviceNet 消息处理程序
BOOL XDeviceNet::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XDeviceNet::Init()
{
	InitShowData();
	ShowControl();
	InitRadio();
	InitCheckBox();
	GetNetConfig();
	ReloadInterface();
}

void XDeviceNet::GetNetConfig()
{
	XSendDataManage::GetInstance()->AddSendDataOfNetConfig();
}

void XDeviceNet::InitShowData()
{
	CString szIP1=m_pDelegate->GetDeviceIP();
	GetDlgItem(IDC_IP1)->SetWindowText(szIP1);

	int nPort1=m_pDelegate->GetDevicePort();
	CString szPort1;
	szPort1.Format(_T("%d"),nPort1);
	GetDlgItem(IDC_EDIT_PORT1)->SetWindowText(szPort1);

	GetDlgItem(IDC_MASK)->SetWindowText(m_pDelegate->GetDeviceMask());
	GetDlgItem(IDC_GATEWAY)->SetWindowText(m_pDelegate->GetDeviceGateway());
	//////////////////////////////////////////////////////////////////////////

	CString szIP2=m_pDelegate->GetDevice2IP();
	GetDlgItem(IDC_IP2)->SetWindowText(szIP2);

	int nPort2=m_pDelegate->GetDevice2Port();
	CString szPort2;
	szPort2.Format(_T("%d"),nPort2);
	GetDlgItem(IDC_EDIT_PORT2)->SetWindowText(szPort2);

	GetDlgItem(IDC_MASK2)->SetWindowText(m_pDelegate->GetDevice2Mask());
	GetDlgItem(IDC_GATEWAY2)->SetWindowText(m_pDelegate->GetDevice2Gateway());
}

void XDeviceNet::ResetShowData(VEC_NETCONFIG& vecConfig)
{
	if(vecConfig.size()!=0)
	{
		XNetConfig* pNetConfig=pNetConfig=vecConfig[0];
		if(m_nRadioSel==0)
		{
			GetDlgItem(IDC_IP1)->SetWindowText(pNetConfig->GetIP());
			CString szPort;
			szPort.Format(_T("%d"),pNetConfig->GetPort());
			GetDlgItem(IDC_EDIT_PORT1)->SetWindowText(szPort);
			GetDlgItem(IDC_MASK)->SetWindowText(pNetConfig->GetMask());
			GetDlgItem(IDC_GATEWAY)->SetWindowText(pNetConfig->GetGateway());
		}
		else if(m_nRadioSel==1)
		{
			GetDlgItem(IDC_IP2)->SetWindowText(pNetConfig->GetIP());
			CString szPort;
			szPort.Format(_T("%d"),pNetConfig->GetPort());
			GetDlgItem(IDC_EDIT_PORT2)->SetWindowText(szPort);
			GetDlgItem(IDC_MASK2)->SetWindowText(pNetConfig->GetMask());
			GetDlgItem(IDC_GATEWAY2)->SetWindowText(pNetConfig->GetGateway());
		}
	}
}

void XDeviceNet::InitRadio()
{
	if(m_nRadioSel==0)
	{
		((CButton*)GetDlgItem(IDC_RADIOSEL1))->SetCheck(BST_CHECKED);
	}
	else if(m_nRadioSel==1)
	{
		((CButton*)GetDlgItem(IDC_RADIOSEL2))->SetCheck(BST_CHECKED);
	}
	SetStstusByRadio();
}

void XDeviceNet::InitCheckBox()
{
	if(m_pDelegate->GetNetStatus())
	{
		((CButton*)GetDlgItem(IDC_CHECK_OPEN1))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_OPEN2))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_OPEN1))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_OPEN2))->SetCheck(FALSE);
	}
}

void XDeviceNet::SetRadioSelect(int nSelect)
{
	m_nRadioSel=nSelect;
}

void XDeviceNet::ReloadInterface()
{
	SetWindowText(_C(_T("138"),_T("设备网络")));
	//GetDlgItem(IDC_STATIC_NETINFO)->SetWindowText(_C(_T("138"),_T("设备网络")));
	//GetDlgItem(IDC_STATIC_DEVICE1)->SetWindowText(_C(_T("114"),_T("设备1")));
	//GetDlgItem(IDC_STATIC_DEVICE2)->SetWindowText(_C(_T("115"),_T("设备2")));
	//GetDlgItem(IDC_STATIC_IP1)->SetWindowText(_C(_T("139"),_T("IP地址"))+_T(":"));
	//GetDlgItem(IDC_STATIC_PORT1)->SetWindowText(_C(_T("140"),_T("端口号"))+_T(":"));

	//GetDlgItem(IDC_STATIC_IP2)->SetWindowText(_C(_T("139"),_T("IP地址"))+_T(":"));
	//GetDlgItem(IDC_STATIC_PORT2)->SetWindowText(_C(_T("140"),_T("端口号"))+_T(":"));

	//m_TextDevice1.SetText(_C(_T("114"),_T("设备1")));
	//m_TextDevice2.SetText(_C(_T("115"),_T("设备2")));
	m_TextIP1.SetText(_C(_T("139"),_T("IP地址"))+_T(":"));
	m_TextPort1.SetText(_C(_T("140"),_T("端口号"))+_T(":"));
	m_TextMask1.SetText(_C(_T("311"),_T("掩码"))+_T(":"));
	m_TextGetWay1.SetText(_C(_T("312"),_T("网关"))+_T(":"));

	m_TextIP2.SetText(_C(_T("139"),_T("IP地址"))+_T(":"));
	m_TextPort2.SetText(_C(_T("140"),_T("端口号"))+_T(":"));
	m_TextMask2.SetText(_C(_T("311"),_T("掩码"))+_T(":"));
	m_TextGetWay2.SetText(_C(_T("312"),_T("网关"))+_T(":"));

	GetDlgItem(IDC_RADIOSEL1)->SetWindowText(_C(_T("288"),_T("选择")));
	GetDlgItem(IDC_RADIOSEL2)->SetWindowText(_C(_T("288"),_T("选择")));
	GetDlgItem(IDC_CHECK_OPEN1)->SetWindowText(_C(_T("19"),_T("打开")));
	GetDlgItem(IDC_CHECK_OPEN2)->SetWindowText(_C(_T("19"),_T("打开")));
	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
}

void XDeviceNet::ShowControl()
{
	if(!m_pDelegate->GetLogin())
	{
		GetDlgItem(IDC_STATIC_MASK)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_GATEWAY)->ShowWindow(FALSE);
		GetDlgItem(IDC_MASK)->ShowWindow(FALSE);
		GetDlgItem(IDC_GATEWAY)->ShowWindow(FALSE);

		GetDlgItem(IDC_STATIC_MASK2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_GATEWAY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_MASK2)->ShowWindow(FALSE);
		GetDlgItem(IDC_GATEWAY2)->ShowWindow(FALSE);

		SetControlRect(IDC_STATIC_DEVICE1,0,90);
		SetControlRect(IDC_STATIC_DEVICE2,70,90);
		SetControlRect(IDC_STATIC_IP2,70,20);
		SetControlRect(IDC_STATIC_PORT2,70,20);
		SetControlRect(IDC_IP2,70,21);
		SetControlRect(IDC_EDIT_PORT2,70,21);
		SetControlRect(IDC_RADIOSEL2,70,18);
		SetControlRect(IDOK,130,25);
		SetControlRect(IDCANCEL,130,25);
		SetControlRect(IDC_CHECK_OPEN2,75,25);

		CRect rect;
		GetWindowRect(&rect);
		rect.bottom=rect.top+280;
		MoveWindow(rect);
	}
}

void XDeviceNet::SetControlRect(int nID,int nTop,int nHeight/*,XThemeText* pText*/)
{
	//if(NULL!=pText)
	//{
	//	CRect rect;

	//	pText->GetWindowRect(&rect);
	//	//ScreenToClient(&rect);
	//	rect.top-=nTop;
	//	rect.bottom=rect.top+nHeight;
	//	pText->MoveWindow(rect);
	//}
	//else
	{
		CRect rect;
		CWnd *pWnd;
		pWnd=GetDlgItem(nID);
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.top-=nTop;
		rect.bottom=rect.top+nHeight;
		pWnd->MoveWindow(rect);
	}

}

void XDeviceNet::OnBnClickedOk()
{
	CString szIP1;
	GetDlgItem(IDC_IP1)->GetWindowText(szIP1);
	szIP1.Trim();
	if(!HandleCalculate::DecideIP(szIP1))
	{
		_M(_T("16"),_T("设备IP地址输入错误，请重新输入!"),MB_OK);
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	CString szPort1;
	GetDlgItem(IDC_EDIT_PORT1)->GetWindowText(szPort1);
	int nPort1=_ttoi(szPort1);
	//////////////////////////////////////////////////////////////////////////
	CString szMask1;
	GetDlgItem(IDC_MASK)->GetWindowText(szMask1);
	szMask1.Trim();
	if(!HandleCalculate::DecideIP(szMask1))
	{
		_M(_T("233"),_T("设备掩码输入错误，请重新输入!"),MB_OK);
		return;
	}

	CString szGateway1;
	GetDlgItem(IDC_GATEWAY)->GetWindowText(szGateway1);
	szGateway1.Trim();
	if(!HandleCalculate::DecideIP(szGateway1))
	{
		_M(_T("234"),_T("设备网关输入错误，请重新输入!"),MB_OK);
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	CString szIP2;
	GetDlgItem(IDC_IP2)->GetWindowText(szIP2);
	szIP2.Trim();
	if(!HandleCalculate::DecideIP(szIP2))
	{
		_M(_T("16"),_T("设备IP地址输入错误，请重新输入!"),MB_OK);
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	CString szPort2;
	GetDlgItem(IDC_EDIT_PORT2)->GetWindowText(szPort2);
	int nPort2=_ttoi(szPort2);

	CString szMask2;
	GetDlgItem(IDC_MASK2)->GetWindowText(szMask2);
	szMask2.Trim();
	if(!HandleCalculate::DecideIP(szMask2))
	{
		_M(_T("233"),_T("设备掩码输入错误，请重新输入!"),MB_OK);
		return;
	}

	CString szGateway2;
	GetDlgItem(IDC_GATEWAY2)->GetWindowText(szGateway2);
	szGateway2.Trim();
	if(!HandleCalculate::DecideIP(szGateway2))
	{
		_M(_T("234"),_T("设备网关输入错误，请重新输入!"),MB_OK);
		return;
	}

	//如果没登陆 只是设置IP和端口
	if(!m_pDelegate->GetLogin())
	{
		m_pDelegate->SetIPAddr1(szIP1);
		SaveIP1(szIP1);

		m_pDelegate->SetPort1(nPort1);
		SavePort1(nPort1);

		m_pDelegate->SetIPAddr2(szIP2);
		SaveIP2(szIP2);

		m_pDelegate->SetPort2(nPort2);
		SavePort2(nPort2);
		//选择通信网络
		m_pDelegate->ConnectNetSelect();

		XBaseDialog::OnOK();
	}
	else
	{
		//选择通信网络
		m_pDelegate->ConnectNetSelect();
		//根据单选按钮 判断设置那个设备
		if(m_nRadioSel==0)
		{
			m_config.CLear();
			m_config.SetIP(szIP1);
			m_config.SetPort(nPort1);
			m_config.SetMask(szMask1);
			m_config.SetGateway(szGateway1);
		}
		else if(m_nRadioSel==1)
		{
			m_config.CLear();
			m_config.SetIP(szIP2);
			m_config.SetPort(nPort2);
			m_config.SetMask(szMask2);
			m_config.SetGateway(szGateway2);
		}

		m_config.SetApply(TRUE);
		m_config.SetSave(FALSE);

		XSendDataManage::GetInstance()->AddSendDataOfApplyNetConfig(m_config);
		//开始定时器
		SetTimer(TIMERID,TIMERSPACE,NULL);
		m_dwTimer=GetTickCount();
		m_pDelegate->SetSendApplyTime(m_dwTimer);
	}
}

void XDeviceNet::StopTimer()
{
	KillTimer(TIMERID);
}

void XDeviceNet::SaveNetConfig()
{
	XSendDataManage::GetInstance()->AddSendDataOfSaveNetConfig(m_config);
}

void XDeviceNet::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
		case TIMERID:
			{
				DWORD dwTimer=GetTickCount();
				if((long)dwTimer-(long)m_dwTimer>3000)
				{
					KillTimer(TIMERID);
					_M(_T("235"),_T("设置设备网络失败，重启设备！"),MB_OK);
				}
			}
			break;
		default:
			break;
	}
}

void XDeviceNet::CloseDialog()
{
	XBaseDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////
void XDeviceNet::SaveIP1(CString szIP)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	HandleIni::WriteData(_T("Info"),_T("IP1"),szIP,szIniPath);
}

void XDeviceNet::SaveIP2(CString szIP)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	HandleIni::WriteData(_T("Info"),_T("IP2"),szIP,szIniPath);
}

void XDeviceNet::SavePort1(int nPort)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szPort1;
	szPort1.Format(_T("%d"),nPort);

	HandleIni::WriteData(_T("Info"),_T("Port1"),szPort1,szIniPath);
}

void XDeviceNet::SavePort2(int nPort)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szPort2;
	szPort2.Format(_T("%d"),nPort);

	HandleIni::WriteData(_T("Info"),_T("Port2"),szPort2,szIniPath);
}

void XDeviceNet::OnBnClickedRadiosel1()
{
	UpdateData(TRUE);
	m_pDelegate->SetDeviceSelect(m_nRadioSel);
	//TRACE(_T("Sel=%d\n"),m_nRadioSel);
	SetStstusByRadio();
}

void XDeviceNet::SetStstusByRadio()
{
	if(m_nRadioSel==0)
	{
		GetDlgItem(IDC_CHECK_OPEN1)->ShowWindow(TRUE);
		GetDlgItem(IDC_CHECK_OPEN2)->ShowWindow(FALSE);
	}
	else if(m_nRadioSel==1)
	{
		GetDlgItem(IDC_CHECK_OPEN1)->ShowWindow(FALSE);
		GetDlgItem(IDC_CHECK_OPEN2)->ShowWindow(TRUE);
	}
}

void XDeviceNet::OnBnClickedCheckOpen1()
{
	if(((CButton*)GetDlgItem(IDC_CHECK_OPEN1))->GetCheck())
	{
		Open();
	}
	else
	{
		Close();
	}
	InitCheckBox();
}

void XDeviceNet::OnBnClickedCheckOpen2()
{
	if(((CButton*)GetDlgItem(IDC_CHECK_OPEN2))->GetCheck())
	{
		Open();
	}
	else
	{
		Close();
	}
	InitCheckBox();
}

void XDeviceNet::Open()
{
	m_pDelegate->Operate(OPERATETYPE_OPENNET,NULL);
}

void XDeviceNet::Close()
{
	m_pDelegate->Operate(OPERATETYPE_CLOSENET,NULL);
}

HBRUSH XDeviceNet::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hbr=CDialogEx::OnCtlColor(pDC,pWnd,nCtlColor);
	//switch(nCtlColor)
	//{
	//	case CTLCOLOR_STATIC:
	//		{
	//			pDC->SetBkMode(TRANSPARENT);
	//			return (HBRUSH)::GetStockObject(NULL_BRUSH);
	//		}
	//		break;
	//	case CTLCOLOR_EDIT:
	//		{
	//			if(pWnd->IsWindowEnabled())
	//			{
	//				pDC->SetBkMode(TRANSPARENT);
	//				HBRUSH b=CreateSolidBrush(RGB(255,255,255));
	//				return b;
	//			}
	//		}
	//		break;
	//	default:
	//		break;
	//}


	TCHAR szClassName[MAX_PATH]={0};
	::GetClassName(pWnd->m_hWnd,szClassName,sizeof(szClassName)/sizeof(TCHAR)-2);
	if(lstrcmpi(szClassName,_T("Button"))==0)
	{
		UINT uStyle=((CButton*)pWnd)->GetButtonStyle();
		switch(uStyle)
		{
			case BS_AUTORADIOBUTTON:
			case BS_AUTOCHECKBOX:
				{
					int nIndex=XThemeColor::GetInstance()->GetThemeIndex();
					Color color=m_BgColor[nIndex];
					HBRUSH hbrSatic=::CreateSolidBrush(RGB(color.GetR(),color.GetG(),color.GetB()));
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(RGB(255,255,255));
					return hbrSatic;
				}
				break;
			default:
				break;
		}
	}


	return hbr;
}