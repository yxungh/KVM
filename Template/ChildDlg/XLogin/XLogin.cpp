// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XLogin.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "XSendDataManage.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XDelegateLogin.h"

// XLogin 对话框

IMPLEMENT_DYNAMIC(XLogin,XBaseDialog)

	XLogin::XLogin(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XLogin::IDD, pParent)
{

}

XLogin::~XLogin()
{
}

void XLogin::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_USERNAME,m_TextName);
	DDX_Control(pDX,IDC_STATIC_PASSWD,m_TextPassWd);
	DDX_Control(pDX,IDC_STATIC_LOAD,m_TextLoad);
	DDX_Control(pDX,ID_OK,m_BtnOK);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XLogin,XBaseDialog)
	ON_COMMAND(ID_OK,OnBnClickedOk)
	ON_WM_TIMER()
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


// XLogin 消息处理程序

void XLogin::OnOk()
{
	XBaseDialog::OnOK();
}

BOOL XLogin::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XLogin::Init()
{
	InitData();
	SetDlgStatus(TRUE);
	ReloadInterface();
	m_BtnOK.SetFocus();
}

void XLogin::SetDlgStatus(BOOL b)
{
	GetDlgItem(IDC_STATIC_LOAD)->ShowWindow(!b);
	GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(b);
	GetDlgItem(IDC_STATIC_PASSWD)->ShowWindow(b);
	GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(b);
	GetDlgItem(IDC_EDIT_PASSWD)->ShowWindow(b);
	GetDlgItem(ID_OK)->ShowWindow(b);
	GetDlgItem(IDCANCEL)->ShowWindow(b);
}

void XLogin::InitData()
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	CString szUserName=HandleIni::GetString(_T("Info"), _T("UserName"),_T(""),szIniPath);
	GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(szUserName);
}

void XLogin::ReloadInterface()
{
	SetWindowText(_C(_T("24"),_T("登录")));

	m_TextName.SetText(_C(_T("25"),_T("用户名"))+_T(":"));
	m_TextPassWd.SetText(_C(_T("26"),_T("密码"))+_T(":"));

	m_BtnOK.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
}

void XLogin::OnBnClickedOk()
{

}

void XLogin::SaveUserName(CString szUserName)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	HandleIni::WriteData(_T("Info"),_T("UserName"),szUserName,szIniPath);
}

void XLogin::SetLoginLoad()
{
	m_dLoginTime=GetTickCount();

	SetDlgStatus(FALSE);
	m_szText=_C(_T("32"),_T("加载数据"));
	UpdateText();
	SetTimer(1,500,NULL);
}

void XLogin::StopTimer()
{
	KillTimer(1);
}

void XLogin::UpdateText()
{
	m_nIndex++;

	CString szText=m_szText;

	for(int i=0;i<6;i++)
	{
		if (i<m_nIndex)
		{
			szText+=_T("．");
		}
		else
		{
			szText+=_T("　");
		}
	}

	if (m_nIndex>=6)
	{
		m_nIndex=0;
	}

	//m_TextLoad.SetLeft(TRUE);
	m_TextLoad.SetText(szText,TRUE);

	CRect rectText;
	GetDlgItem(IDC_STATIC_LOAD)->GetWindowRect(&rectText);
	ScreenToClient(&rectText);
	InvalidateRect(&rectText);
}

void XLogin::OnTimer(UINT_PTR nIDEvent)
{
	DWORD dCurTime=GetTickCount();

	UpdateText();
	if(abs((long)(m_dLoginTime)-(long)(dCurTime))>=5000)
	{
		KillTimer(1);
		_M(_T("45"),_T("登录超时！"),MB_OK);
		SetDlgStatus(TRUE);

	}
	__super::OnTimer(nIDEvent);
}

void XLogin::ClickOk()
{
	CString szUserName=_T("");
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(szUserName);
	szUserName.Trim();
	if(_T("")==szUserName)
	{
		_M(_T("28"),_T("用户名不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
		return;
	}

	CString szPassWd=_T("");
	GetDlgItem(IDC_EDIT_PASSWD)->GetWindowText(szPassWd);
	szPassWd.Trim();
	if(_T("")==szPassWd)
	{
		_M(_T("29"),_T("密码不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
		return;
	}

	if(!XHandleVerification::VerificationString(szUserName))
	{
		_M(_T("30"),_T("用户名包含非法字符！"),MB_OK);
		return;
	}

	if(!XHandleVerification::VerificationString(szPassWd))
	{
		_M(_T("31"),_T("密码包含非法字符！"),MB_OK);
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	SaveUserName(szUserName);
	//发送数据
	XSendDataManage::GetInstance()->AddSendDataOfLogin(szUserName,szPassWd);

	//设置现在登陆用户
	m_pDelegate->SetLoginUser(szUserName,szPassWd);

	SetLoginLoad();
}

LRESULT XLogin::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	if(wParam==ID_OK)
	{
		ClickOk();
	}
	else if(wParam==IDCANCEL)
	{

	}

	return 0;
}


BOOL XLogin::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_RETURN://屏蔽回车  
				{
					ClickOk();
				}
				break;
			case VK_ESCAPE://屏蔽Esc  
				{
					if(!m_bEnableVK_ESCAPE)
					{
						return TRUE;
					}
				}
				break;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}