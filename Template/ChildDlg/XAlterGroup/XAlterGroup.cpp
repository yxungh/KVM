// XAlterGroup.cpp : 实现文件
//
#include "stdafx.h"
#include "XAlterGroup.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XHandleVerification.h"
#include "XMessageBox.h"
#include "XLeftWnd.h"
#include "XNodeGroupInfo.h"


// XAlterGroup 对话框

IMPLEMENT_DYNAMIC(XAlterGroup, XBaseDialog)

XAlterGroup::XAlterGroup(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAlterGroup::IDD, pParent),
	m_szGroupName(_T(""))
{

}

XAlterGroup::~XAlterGroup()
{
}

void XAlterGroup::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_GNAME,m_TextName);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XAlterGroup, XBaseDialog)
	ON_COMMAND(IDOK,OnBnClickedOk)
END_MESSAGE_MAP()


// XAlterGroup 消息处理程序
BOOL XAlterGroup::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XAlterGroup::Init()
{
	ReloadInterface();
}

void XAlterGroup::ReloadInterface()
{
	SetWindowText(GetTranslationString(_T("71"),_T("更改名称")));
	m_TextName.SetText(GetTranslationString(_T("72"),_T("名称"))+_T(":"));
	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
}

CString XAlterGroup::GetTranslationString(CString szKey,CString szDefault/*=_T("")*/)
{
	return _C(szKey,szDefault);
}

void XAlterGroup::OnBnClickedOk()
{
	CString szGroupName=_T("");
	GetDlgItem(IDC_EDIT_GNAME)->GetWindowText(szGroupName);
	szGroupName.Trim();
	if (_T("")==szGroupName)
	{
		_M(_T("73"),_T("名称不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_GNAME)->SetFocus();
		return;
	}

	if (!XHandleVerification::VerificationString(szGroupName))
	{
		_M(_T("74"),_T("名称包含非法字符！"),MB_OK);
		return;
	}

	//判断是否重复
	if(DecidedExist(szGroupName))
	{
		_M(_T("161"),_T("名称已存在！"),MB_OK);
		return;
	}
	
	m_szGroupName=szGroupName;

	XBaseDialog::OnOK();
}

BOOL XAlterGroup::DecidedExist(CString szName)
{
	MAP_NODEGROUP& MapNodeGroup=XLeftWnd::GetInstance()->GetMapNodeGroup();
	for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
	{
		XNodeGroupInfo* pInfo=iter->second;
		if(pInfo->GetGroupName()==szName)
			return TRUE;
	}
	return FALSE;
}
