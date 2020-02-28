// XAddGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "XAddGroup.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XLeftWnd.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "XNodeGroupInfo.h"



// XAddGroup 对话框

IMPLEMENT_DYNAMIC(XAddGroup, XBaseDialog)

XAddGroup::XAddGroup(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAddGroup::IDD, pParent)
{

}

XAddGroup::~XAddGroup()
{
}

void XAddGroup::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_GNAME,m_TextName);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XAddGroup, XBaseDialog)
	ON_COMMAND(IDOK,OnBtnClick)
END_MESSAGE_MAP()


// XAddGroup 消息处理程序
BOOL XAddGroup::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}
void XAddGroup::Init()
{
	ReloadInterface();
}
void XAddGroup::ReloadInterface()
{
	//SetWindowText(_C(_T("165"),_T("创建组")));
	SetWindowText(m_szTitle);
	m_TextName.SetText(_C(_T("72"),_T("名称")));
	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
}

void XAddGroup::OnBtnClick()
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

BOOL XAddGroup::DecidedExist(CString szName)
{
	if(m_bMainSec)
	{
		MAP_GROUPMAINSEC& MapNodeGroup=XLeftWnd::GetInstance()->GetMapNodeGroupMainSec();
		for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
		{
			XNodeGroupInfo* pInfo=iter->second;
			if(pInfo->GetGroupName()==szName)
				return TRUE;
		}
	}
	else
	{
		MAP_NODEGROUP& MapNodeGroup=XLeftWnd::GetInstance()->GetMapNodeGroup();
		for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
		{
			XNodeGroupInfo* pInfo=iter->second;
			if(pInfo->GetGroupName()==szName)
				return TRUE;
		}
	}
	return FALSE;
}