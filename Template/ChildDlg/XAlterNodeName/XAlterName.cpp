// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XAlterName.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "HandlePath.h"
#include "HandleIni.h"


// XAlterName 对话框

IMPLEMENT_DYNAMIC(XAlterName, XBaseDialog)

	XAlterName::XAlterName(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAlterName::IDD, pParent),
	m_szNodeName(_T(""))
{
}

XAlterName::~XAlterName()
{
}

void XAlterName::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_NODE,m_TextName);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XAlterName, XBaseDialog)
	ON_COMMAND(IDOK,OnBnClickedOk)
END_MESSAGE_MAP()


// XAlterName 消息处理程序

void XAlterName::OnOk()
{
	XBaseDialog::OnOK();
}

BOOL XAlterName::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XAlterName::Init()
{
	InitData();
	ReloadInterface();
}

void XAlterName::InitData()
{

}

void XAlterName::ReloadInterface()
{
	SetWindowText(_C(_T("71"),_T("更改名称")));
	m_TextName.SetText(_C(_T("72"), _T("名称")) + _T(":"));
	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
}

void XAlterName::OnBnClickedOk()
{
	CString szNodeName=_T("");
	GetDlgItem(IDC_EDIT_NODE)->GetWindowText(szNodeName);
	szNodeName.Trim();
	if (_T("")==szNodeName)
	{
		_M(_T("73"),_T("名称不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
		return;
	}

	if (!XHandleVerification::VerificationString(szNodeName))
	{
		_M(_T("74"),_T("名称包含非法字符！"),MB_OK);
		return;
	}

	m_szNodeName=szNodeName;

	XBaseDialog::OnOK();
}


