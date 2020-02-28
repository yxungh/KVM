// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XNodeLoginUser.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XSetListCtrl.h"
#include "XDelegateNodeLoginUser.h"
#include "XPower.h"



// XNodeLoginUser 对话框

IMPLEMENT_DYNAMIC(XNodeLoginUser,XBaseDialog)

XNodeLoginUser::XNodeLoginUser(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XNodeLoginUser::IDD,pParent),
	m_szUserName(_T("")),
	m_szPassWd(_T("")),
	m_nUserID(0),
	m_pDelegate(NULL)
{
}

XNodeLoginUser::~XNodeLoginUser()
{
}

void XNodeLoginUser::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_NODELOGINUSER,m_ListNodeLogin);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XNodeLoginUser,XBaseDialog)
	ON_COMMAND(IDOK,OnBnClickedOk)

END_MESSAGE_MAP()


// XNodeLoginUser 消息处理程序

void XNodeLoginUser::OnOk()
{
	XBaseDialog::OnOK();
}

void XNodeLoginUser::SetDelegate(XDelegateNodeLoginUser* p)
{
	m_pDelegate=p;
}

BOOL XNodeLoginUser::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XNodeLoginUser::Init()
{
	InitList();

	SetList();

	ReloadInterface();
}

void XNodeLoginUser::InitList()
{
	XSetListCtrl::InitList(&m_ListNodeLogin,2,FALSE);

	m_ListNodeLogin.EnableToolTips(TRUE);

	m_ListNodeLogin.SetColumnWidth(0,127);
	m_ListNodeLogin.SetColumnWidth(1,128);
}

void XNodeLoginUser::SetList()
{
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	//子用户列表（没有当前用户）
	MAP_SUBUSER& MapSubUser=m_pDelegate->GetMapSubUser();

	//应该牵扯到是否有权限登录问题（以后考虑）
	for(auto iter=MapPower.begin();iter!=MapPower.end();++iter)
	{
		XPower* pInfo=iter->second;

		int nUserID=pInfo->GetUserID();
		CString szUserName=pInfo->GetUserName();

		AddListInfo(nUserID,szUserName);
	}
}

void XNodeLoginUser::ReloadInterface()
{
	SetWindowText(_C(_T("66"),_T("登录用户")));

	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
	//////////////////////////////////////////////////////////////////////////

	CString szTemp=_T("");
	LVCOLUMN col;
	col.mask=LVCF_TEXT;

	szTemp=_C(_T("39"),_T("ID"));
	col.pszText=szTemp.GetBuffer();
	m_ListNodeLogin.SetColumn(0,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("25"),_T("用户名"));
	col.pszText=szTemp.GetBuffer();
	m_ListNodeLogin.SetColumn(1,&col);
	szTemp.ReleaseBuffer();
}

void XNodeLoginUser::OnBnClickedOk()
{
	int nItem=XSetListCtrl::GetListSelectItem(&m_ListNodeLogin);
	if(nItem==-1)
	{
		_M(_T("67"),_T("请选择用户！"),MB_OK);
		return;
	}

	CString szUserName=XSetListCtrl::GetColumnText(&m_ListNodeLogin,nItem,1);
	m_szUserName=szUserName;

	//MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	//MAP_POWER::iterator iter=MapPower.find(m_szUserName);
	//if(iter!=MapPower.end())
	//{
	//	XPower* pPower=iter->second;
	//	CString szPassWd=pPower->GetPassWd();
	//	m_szPassWd=szPassWd;
	//}

	XBaseDialog::OnOK();
}

int XNodeLoginUser::AddListInfo(int nUserID,CString szUserName)
{
	int nCount=m_ListNodeLogin.GetItemCount();
	if(nCount>18)
	{
		m_ListNodeLogin.SetColumnWidth(0,119);
		m_ListNodeLogin.SetColumnWidth(1,119);
	}
	else
	{
		m_ListNodeLogin.SetColumnWidth(0,127);
		m_ListNodeLogin.SetColumnWidth(1,128);
	}

	m_ListNodeLogin.InsertItem(nCount,_T(""));
	SetListInfo(nCount,nUserID,szUserName);

	return nCount;
}

void XNodeLoginUser::SetListInfo(int nCount,int nUserID,CString szUserName)
{
	CString szUserID;
	szUserID.Format(_T("%d"),nUserID);

	m_ListNodeLogin.SetItemText(nCount,0,szUserID);
	m_ListNodeLogin.SetItemText(nCount,1,szUserName);
}
