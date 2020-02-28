// AboutDlg.cpp : ʵ���ļ�
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

// XLogin �Ի���

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


// XLogin ��Ϣ�������

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
	SetWindowText(_C(_T("24"),_T("��¼")));

	m_TextName.SetText(_C(_T("25"),_T("�û���"))+_T(":"));
	m_TextPassWd.SetText(_C(_T("26"),_T("����"))+_T(":"));

	m_BtnOK.SetCaption(_C(_T("1"),_T("ȷ��")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("ȡ��")));
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
	m_szText=_C(_T("32"),_T("��������"));
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
			szText+=_T("��");
		}
		else
		{
			szText+=_T("��");
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
		_M(_T("45"),_T("��¼��ʱ��"),MB_OK);
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
		_M(_T("28"),_T("�û�������Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
		return;
	}

	CString szPassWd=_T("");
	GetDlgItem(IDC_EDIT_PASSWD)->GetWindowText(szPassWd);
	szPassWd.Trim();
	if(_T("")==szPassWd)
	{
		_M(_T("29"),_T("���벻��Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
		return;
	}

	if(!XHandleVerification::VerificationString(szUserName))
	{
		_M(_T("30"),_T("�û��������Ƿ��ַ���"),MB_OK);
		return;
	}

	if(!XHandleVerification::VerificationString(szPassWd))
	{
		_M(_T("31"),_T("��������Ƿ��ַ���"),MB_OK);
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	SaveUserName(szUserName);
	//��������
	XSendDataManage::GetInstance()->AddSendDataOfLogin(szUserName,szPassWd);

	//�������ڵ�½�û�
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
			case VK_RETURN://���λس�  
				{
					ClickOk();
				}
				break;
			case VK_ESCAPE://����Esc  
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