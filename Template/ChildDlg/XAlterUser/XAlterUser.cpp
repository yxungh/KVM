// XAlterUser.cpp : 实现文件
//

#include "stdafx.h"
#include "XAlterUser.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "XDelegateAlterUser.h"
#include "XSetListCtrl.h"
#include "XTranslationManage.h"
#include "XPowerListInfo.h"
#include "XPower.h"
#include "HandlePower.h"
#include "XPowerSelectInfo.h"


// XAlterUser 对话框

IMPLEMENT_DYNAMIC(XAlterUser, XBaseDialog)

XAlterUser::XAlterUser(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAlterUser::IDD, pParent)
{

}

XAlterUser::~XAlterUser()
{
	//ClearMapUserPower();
	//ClearMapSelect();
}

//void XAlterUser::ClearMapUserPower()
//{
//	for(auto iter=m_MapUserPower.begin();iter!=m_MapUserPower.end();++iter)
//	{
//		delete iter->second;
//	}
//	m_MapUserPower.clear();
//}
//
//void XAlterUser::ClearMapSelect()
//{
//	for(auto iter=m_MapSelect.begin();iter!=m_MapSelect.end();++iter)
//	{
//		delete iter->second;
//	}
//	m_MapSelect.clear();
//}

void XAlterUser::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_USERNAME,m_TextName);
	DDX_Control(pDX,IDC_STATIC_PW,m_TextPassWd);
	DDX_Control(pDX,IDC_STATIC_TIP,m_TextTip);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}

BEGIN_MESSAGE_MAP(XAlterUser, XBaseDialog)
	ON_COMMAND(IDOK,OnButtonClick)
	//ON_NOTIFY(NM_CLICK,IDC_LIST_POWER1,OnNMClickPowerList)
END_MESSAGE_MAP()


//XAlterUser 消息处理程序
BOOL XAlterUser::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XAlterUser::OnOK()
{
	XBaseDialog::OnOK();
}

void XAlterUser::Init()
{
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(m_szUserName);
	
	//CString szCurUserName=m_pDelegate->GetUserName();
	//if(szCurUserName==m_szUserName)
	//{
	//	m_PowerList.EnableWindow(FALSE);
	//}

	//InitPowerList();
	//AddPowerInfo();
	//SetPowerSelect();
	ReloadInterface();
}

//void XAlterUser::InitPowerList()
//{
//	//XSetListCtrl::InitList(&m_PowerList,1,TRUE);
//	//m_PowerList.SetColumnWidth(0,217);
//}

CString XAlterUser::GetTranslationString(CString szKey,CString szDefault/*=_T("")*/)
{
	return _C(szKey,szDefault);
}

void XAlterUser::ReloadInterface()
{
	SetWindowText(_C(_T("118"),_T("修改用户")));

	m_TextName.SetText(_C(_T("25"),_T("用户名"))+_T(":"));
	m_TextPassWd.SetText(_C(_T("26"),_T("密码"))+_T(":"));
	//m_TextTip.SetLeft(TRUE);
	m_TextTip.SetText(_C(_T("298"),_T("提示:密码为空时，不修改密码")),TRUE);

	m_BtnOk.SetCaption(_C(_T("1"), _T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"), _T("取消")));

	//CString szTemp=_T("");
	//LVCOLUMN col;
	//col.mask=LVCF_TEXT;
	//szTemp=GetTranslationString(_T("38"),_T("用户权限"));
	//col.pszText=szTemp.GetBuffer();
	//m_PowerList.SetColumn(0,&col);
	//szTemp.ReleaseBuffer();
}

//void XAlterUser::AddPowerInfo()
//{
//	//按照登录用户权限添加列表
//	CString szCurUserName=m_pDelegate->GetUserName();
//
//	XPower* pPower=NULL;
//	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
//	MAP_POWER::iterator iter=MapPower.find(szCurUserName);
//	if(iter!=MapPower.end())
//	{
//		pPower=iter->second;
//	}
//
//	if(!pPower)
//		return;
//
//	ClearMapUserPower();
//	unsigned int nPermission=pPower->GetManagePermission();
//	XPowerListInfo* pListInfo=NULL;
//	for(int i=0;i<32;i++)
//	{
//		BOOL bHas=FALSE;
//		if((nPermission&(1<<i))!=0)
//			bHas=TRUE;
//		else
//			bHas=FALSE;
//
//		MAP_USERPOWER::iterator iter=m_MapUserPower.find(i);
//		if(iter!=m_MapUserPower.end())
//		{
//			pListInfo=iter->second;
//		}
//		else
//		{
//			pListInfo=new XPowerListInfo;
//			m_MapUserPower.insert(std::pair<int,XPowerListInfo*>(i,pListInfo));
//		}
//		pListInfo->SetPowerIndex(i);
//		pListInfo->SetHas(bHas);
//	}
//
//	for(auto iter=m_MapUserPower.begin();iter!=m_MapUserPower.end();++iter)
//	{
//		XPowerListInfo* pListInfo=iter->second;
//		CString szPower=HandlePower::GetPowerByByte(iter->first,pListInfo->GetHas());
//		pListInfo->SetPowerName(szPower);
//		if(szPower!=_T(""))
//			AddListInfo(szPower);
//	}
//}
//
//void XAlterUser::SetPowerSelect()
//{
//	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
//	CString szUserName=m_szUserName;
//	//////////////////////////////////////////////////////////////////////////
//	//用户自己权限
//	XPower* pPower=NULL;
//	MAP_POWER::iterator iter=MapPower.find(szUserName);
//	if(iter!=MapPower.end())
//	{
//		pPower=iter->second;
//	}
//
//	if(!pPower)
//		return;
//
//	ClearMapUserPower();
//	unsigned int nPermission=pPower->GetManagePermission();
//	XPowerListInfo* pListInfo=NULL;
//	for(int i=0;i<32;i++)
//	{
//		BOOL bHas=FALSE;
//		if((nPermission&(1<<i))!=0)
//			bHas=TRUE;
//		else
//			bHas=FALSE;
//
//		MAP_USERPOWER::iterator iter=m_MapUserPower.find(i);
//		if(iter!=m_MapUserPower.end())
//		{
//			pListInfo=iter->second;
//		}
//		else
//		{
//			pListInfo=new XPowerListInfo;
//			m_MapUserPower.insert(std::pair<int,XPowerListInfo*>(i,pListInfo));
//		}
//		pListInfo->SetPowerIndex(i);
//		pListInfo->SetHas(bHas);
//
//		CString szPower=HandlePower::GetPowerByByte(i,bHas);
//		if(_T("")!=szPower)
//			pListInfo->SetPowerName(szPower);
//	}
//
//	//清空选中集合
//	ClearMapSelect();
//
//	//先全部不选中
//	int nCount=m_PowerList.GetItemCount();
//	for(int i=0;i<nCount;i++)
//	{
//		XSetListCtrl::SetListCheckItemFalse(&m_PowerList,i);
//	}
//	//根据用户权限集合，check选中用户权限
//	for(auto iter=m_MapUserPower.begin();iter!=m_MapUserPower.end();++iter)
//	{
//		int nItem=iter->first;
//		XPowerListInfo* pListInfo=iter->second;
//
//		CString szPower=HandlePower::GetPowerByByte(nItem,pListInfo->GetHas());
//
//		//每次只要有相同的都选中
//		int nCount=m_PowerList.GetItemCount();
//		for(int i=0;i<nCount;i++)
//		{
//			CString szItemText=XSetListCtrl::GetColumnText(&m_PowerList,i,0);
//			if(szItemText==szPower)
//			{
//				//添加选中集合
//				MAP_SELECT::iterator iterSel=m_MapSelect.find(i);
//				if(iterSel==m_MapSelect.end())
//				{
//					int nPowerIndex=m_pDelegate->GetPowerIndexByName(szItemText);
//
//					XPowerSelectInfo* pInfo=new XPowerSelectInfo;
//					pInfo->SetPowerName(szItemText);
//					pInfo->SetPowerIndex(nPowerIndex);
//
//					m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(i,pInfo));
//				}
//
//
//				XSetListCtrl::SetListCheckItem(&m_PowerList,i);
//				break;
//			}	
//		}
//	}
//}

void XAlterUser::OnButtonClick()
{
	CString szPassWd=_T("");
	GetDlgItem(IDC_EDIT_PW)->GetWindowText(szPassWd);
	szPassWd.Trim();
	//if(_T("")==szPassWd)
	//{
	//	_M(_T("29"),_T("密码不能为空！"),MB_OK);
	//	GetDlgItem(IDC_EDIT_PW)->SetFocus();
	//	return;
	//}

	//if (!XHandleVerification::VerificationString(szPassWd))
	//{
	//	_M(_T("31"),_T("密码包含非法字符！"),MB_OK);
	//	return;
	//}

	if(_T("")!=szPassWd)
	{
		if(!XHandleVerification::VerificationString(szPassWd))
		{
			_M(_T("31"),_T("密码包含非法字符！"),MB_OK);
			return;
		}

		if(XHandleVerification::HasChinese(szPassWd))
		{
			_M(_T("319"),_T("密码为字母和数组！"),MB_OK);
			return;
		}

		int nRet=XHandleVerification::VerificationPasswd(szPassWd);
		if(nRet==1)
		{
			_M(_T("320"),_T("密码为字密码至少位4位！"),MB_OK);
			return;
		}
		else if(nRet==2)
		{
			_M(_T("319"),_T("密码为字母和数组！"),MB_OK);
			return;
		}
	}
	
	m_szPassWd=szPassWd;
	m_pDelegate->AlterUser();

	//XBaseDialog::OnOK();
}

//int XAlterUser::AddListInfo(CString szInfo)
//{	
//	int nCount=0;
//
//	//权限列表
//	nCount=m_PowerList.GetItemCount();	
//
//	if(nCount>13)
//		m_PowerList.SetColumnWidth(0,201);
//	else
//		m_PowerList.SetColumnWidth(0,217);
//
//	m_PowerList.InsertItem(nCount,_T(""));
//	SetListInfo(nCount,szInfo);
//
//	return nCount;
//}
//
//void XAlterUser::SetListInfo(int nCount,CString szInfo)
//{
//	m_PowerList.SetItemText(nCount,0,szInfo);
//}
//
//void XAlterUser::OnNMClickPowerList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate=reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	DWORD dwPos=GetMessagePos();
//	CPoint pt(dwPos);
//	m_PowerList.ScreenToClient(&pt);
//
//	UINT nFlag;
//	int nItem=m_PowerList.HitTest(pt,&nFlag);
//
//	BOOL bCheckState=m_PowerList.GetCheck(nItem);
//	if(nFlag==LVHT_ONITEMSTATEICON)
//	{
//		//注意，bCheckState为TRUE，checkbox从勾选状态变为未勾选状态
//		if(bCheckState)
//		{
//			MAP_SELECT::iterator iter=m_MapSelect.find(nItem);
//			if(iter!=m_MapSelect.end())
//			{
//				XPowerSelectInfo* pInfo=iter->second;
//				m_MapSelect.erase(iter);
//				delete pInfo;
//			}
//		}
//		else
//		{
//			CString szItemText=XSetListCtrl::GetColumnText(&m_PowerList,nItem,0);
//			int nPowerIndex=m_pDelegate->GetPowerIndexByName(szItemText);
//
//			XPowerSelectInfo* pInfo=new XPowerSelectInfo;
//			pInfo->SetPowerName(szItemText);
//			pInfo->SetPowerIndex(nPowerIndex);
//
//			m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(nItem,pInfo));
//		}
//	}
//	else if(nFlag==LVHT_ONITEMLABEL)
//	{
//		//单击选项
//		if(bCheckState)
//		{
//			XSetListCtrl::SetListCheckItemFalse(&m_PowerList,nItem);
//
//			MAP_SELECT::iterator iter=m_MapSelect.find(nItem);
//			if(iter!=m_MapSelect.end())
//			{
//				XPowerSelectInfo* pInfo=iter->second;
//				m_MapSelect.erase(iter);
//				delete pInfo;
//			}
//		}
//		else
//		{
//			XSetListCtrl::SetListCheckItem(&m_PowerList,nItem);
//
//			CString szItemText=XSetListCtrl::GetColumnText(&m_PowerList,nItem,0);
//			int nPowerIndex=m_pDelegate->GetPowerIndexByName(szItemText);
//
//			XPowerSelectInfo* pInfo=new XPowerSelectInfo;
//			pInfo->SetPowerName(szItemText);
//			pInfo->SetPowerIndex(nPowerIndex);
//
//			m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(nItem,pInfo));
//		}
//	}
//
//	*pResult = 0;
//}
