#include "stdafx.h"
#include "XSecurityDlg.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "HandlePath.h"
#include "XSetSecretDlg.h"
#include "XSetPassWord.h"
#include "XResetPassWord.h"

IMPLEMENT_DYNAMIC(XSecurityDlg,XBaseDialog)

XSecurityDlg::XSecurityDlg(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XSecurityDlg::IDD,pParent)
{

}

XSecurityDlg::~XSecurityDlg()
{
}

void XSecurityDlg::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_SECURT,m_TextSecret);
	DDX_Control(pDX,IDC_STATIC_PASSWD,m_TextPassWd);
	DDX_Control(pDX,IDC_STATIC_RESETPASSWD,m_TextResetPassWd);
	DDX_Control(pDX,IDC_BTN_SECRET,m_BtnSecret);
	DDX_Control(pDX,IDC_BTN_PASSWD,m_BtnPassWd);
	DDX_Control(pDX,IDC_BTN_RESETPASSWD,m_BtnResetPassWd);

	
}


BEGIN_MESSAGE_MAP(XSecurityDlg,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XSecurityDlg::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XSecurityDlg::Init()
{
	SetWindowText(_C(_T("354"),_T("安全中心")));
	ReloadInterface();
}

void XSecurityDlg::ReloadInterface()
{
	m_TextSecret.SetText(_C(_T("355"),_T("设置密保")),FALSE,TRUE);
	m_TextPassWd.SetText(_C(_T("356"),_T("修改密码")),FALSE,TRUE);
	m_TextResetPassWd.SetText(_C(_T("357"),_T("重置密码")),FALSE,TRUE);

	m_BtnSecret.SetImage(HandlePath::GetPhotoPath(_T("secret.png")));
	m_BtnPassWd.SetImage(HandlePath::GetPhotoPath(_T("resetpw.png")));
	m_BtnResetPassWd.SetImage(HandlePath::GetPhotoPath(_T("passwd.png")));
}

void XSecurityDlg::SetSecret()
{
	XSetSecretDlg dlg;
	dlg.DoModal();
}

void XSecurityDlg::AlterPassWd()
{
	//更改密码
	//1 是否有密保 2 验证密保


	XSetPassWord dlg;
	dlg.DoModal();


}

void XSecurityDlg::ResetPassWd()
{
	XResetPassWord dlg;
	dlg.DoModal();
}

LRESULT XSecurityDlg::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
		case IDC_BTN_SECRET:
			{
				SetSecret();
			}
			break;
		case IDC_BTN_PASSWD:
			{
				AlterPassWd();
			}
			break;
		case IDC_BTN_RESETPASSWD:
			{
				ResetPassWd();
			}
			break;
		default:
			break;
	}

	return 0;
}