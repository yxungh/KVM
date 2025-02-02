#include "stdafx.h"
#include "XCopyUser.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XDelegateCopyUser.h"

// XCopyUser 对话框

IMPLEMENT_DYNAMIC(XCopyUser,XBaseDialog)

XCopyUser::XCopyUser(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XCopyUser::IDD,pParent)
{
}

XCopyUser::~XCopyUser()
{
}

void XCopyUser::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_USERNAME,m_TextName);
	DDX_Control(pDX,IDC_STATIC_PASSWD,m_TextPasswd);
	DDX_Control(pDX,IDC_STATIC_TIPS,m_TextTip);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XCopyUser,XBaseDialog)
	ON_COMMAND(IDOK,OnBnClickedOk)
	ON_EN_UPDATE(IDC_EDIT_USERNAME,&XCopyUser::OnUpdateEditUsername)
END_MESSAGE_MAP()


// XCopyUser 消息处理程序


void XCopyUser::CloseDlg()
{
	OnCancel();
}

BOOL XCopyUser::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XCopyUser::Init()
{
	InitData();
	ReloadInterface();
}

void XCopyUser::InitData()
{

}

void XCopyUser::ReloadInterface()
{
	SetWindowText(_C(_T("58"),_T("复制用户")));
	m_TextName.SetText(_C(_T("25"),_T("用户名"))+_T(":"));
	m_TextPasswd.SetText(_C(_T("26"),_T("密码"))+_T(":"));

	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));

	m_TextTip.SetText(_C(_T("50"),_T("提示:复制所选用户权限，仅用户名密码不同")));
}

void XCopyUser::OnBnClickedOk()
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


	//if(XHandleVerification::HasChinese(szPassWd))
	//{
	//	_M(_T("319"),_T("密码为字母和数组！"),MB_OK);
	//	return;
	//}

	//int nRet=XHandleVerification::VerificationPasswd(szPassWd);
	//if(nRet==1)
	//{
	//	_M(_T("320"),_T("密码为字密码至少位4位！"),MB_OK);
	//	return;
	//}
	//else if(nRet==2)
	//{
	//	_M(_T("319"),_T("密码为字母和数组！"),MB_OK);
	//	return;
	//}


	m_szUserName=szUserName;
	m_szPassWd=szPassWd;

	m_pDelegate->CopyUser();
	//XBaseDialog::OnOK();
}

void XCopyUser::OnUpdateEditUsername()
{
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	CString szContent;
	pEdit->GetWindowText(szContent);

	int nLen=XHandleVerification::GetWordLength(szContent);
	if(nLen>14)
	{
		pEdit->SetSel(0,-1);
		pEdit->ReplaceSel(szContent.Right(szContent.GetLength()-1));
	}
}



