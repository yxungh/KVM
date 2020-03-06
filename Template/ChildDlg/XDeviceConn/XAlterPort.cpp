#include "stdafx.h"
#include "XAlterPort.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XSendDataManage.h"


// XAlterPort 对话框

IMPLEMENT_DYNAMIC(XAlterPort,XBaseDialog)

XAlterPort::XAlterPort(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAlterPort::IDD,pParent)
{

}

XAlterPort::~XAlterPort()
{
}

void XAlterPort::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_TIP,m_TextTip);
	DDX_Control(pDX,IDC_STATIC_PORT,m_TextPort);
	DDX_Control(pDX,ID_OK,m_BtnOk);
	DDX_Control(pDX,ID_CANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XAlterPort,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XAlterPort::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XAlterPort::Init()
{
	SetWindowText(_C(_T("364"),_T("更改端口")));

	ReloadInterface();
}

void XAlterPort::ReloadInterface()
{
	m_TextPort.SetText(_C(_T("140"),_T("端口号"))+_T(":"));
	m_TextTip.SetText(_C(_T("365"),_T("提示:端口号应大于12380")),TRUE);

	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
}

void XAlterPort::CloseDlg()
{
	OnCancel();
}

void XAlterPort::OnBtnOk()
{
	CString szPort;
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(szPort);
	szPort.Trim();
	if(szPort==_T(""))
	{
		_M(_T("366"),_T("端口号不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_PORT)->SetFocus();
		return;
	}

	int nPort=_ttoi(szPort);
	if(nPort<12380)
	{
		_M(_T("367"),_T("端口号小于12380"),MB_OK);
		GetDlgItem(IDC_EDIT_PORT)->SetFocus();
		return;
	}

	XSendDataManage::GetInstance()->AddSendDataOfAlterPort(nPort);

}

LRESULT XAlterPort::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
		case ID_OK:
			{
				OnBtnOk();
			}
			break;
		case ID_CANCEL:
			{
				OnCancel();
			}
			break;
		default:
			break;
	}

	return 0;
}