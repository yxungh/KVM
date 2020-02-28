
#include "stdafx.h"
#include "XPowerManage.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "XSendDataManage.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XDelegatePowerManage.h"
#include "XPower.h"
#include "XSetListCtrl.h"
#include "HandlePower.h"
#include "XPowerListInfo.h"
#include "XSubUserInfo.h"
#include "XCopyUser.h"
#include "XPowerSelectInfo.h"
#include "HandleCalculate.h"
#include "XStoreListInfo.h"
#include "XAddUser.h"
#include "XAlterUser.h"
#include "XAddStore.h"
#include "XNodeAll.h"
#include "XPrivilege.h"
#include "XThemeColor.h"

// XPowerManage 对话框
IMPLEMENT_DYNAMIC(XPowerManage,XBaseDialog)

XPowerManage::XPowerManage(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XPowerManage::IDD,pParent)
{
}

XPowerManage::~XPowerManage()
{
	ClearMapUserPower();
	ClearMapSubUserPower();
	ClearMapSelect();
	ClearMapPrivilege();
}

void XPowerManage::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_POWER,m_PowerList);
	DDX_Control(pDX,IDC_LIST_USERINFO,m_UserInfo);
	DDX_Control(pDX,IDC_LIST_USER,m_UserList);
	DDX_Control(pDX,IDC_LIST_STORE,m_StoreList);
	DDX_Control(pDX,IDC_LIST_SUBCTRL,m_SubPowerList);
	//DDX_Control(pDX,IDC_STATIC_USERINFO,m_TextUserInfo);
	DDX_Radio(pDX,IDC_RADIO_CTRL,m_nRadioSelect);

	DDX_Control(pDX,IDC_STATIC_GROUP1,m_TextGroup1);
	DDX_Control(pDX,IDC_STATIC_GROUP2,m_TextGroup2);
	DDX_Control(pDX,IDC_STATIC_GROUP3,m_TextGroup3);
	DDX_Control(pDX,IDC_STATIC_GROUP4,m_TextGroup4);
	DDX_Control(pDX,IDC_STATIC_TIP,m_TextTip);

	DDX_Control(pDX,IDC_ALL,m_BtnAll);
	DDX_Control(pDX,IDC_OTHER,m_BtnOther);
	DDX_Control(pDX,IDC_ALLNOT,m_BtnAllNot);
	DDX_Control(pDX,IDC_SUBALL,m_BtnSubAll);
	DDX_Control(pDX,IDC_SUBOTHER,m_BtnSubOther);
	DDX_Control(pDX,IDC_SUBALLNOT,m_BtnSubAllNot);
	DDX_Control(pDX,IDC_ADDUSER,m_BtnAddUser);
	DDX_Control(pDX,IDC_ALTERUSER,m_BtnAlterUser);
	DDX_Control(pDX,IDC_COPYUSER,m_BtnCopyUser);
	DDX_Control(pDX,IDC_DELUSER,m_BtnDelUser);
	DDX_Control(pDX,IDC_QUERYSTORE,m_BtnQueryStore);
	DDX_Control(pDX,IDC_ADDSTORE,m_BtnAddStore);
	DDX_Control(pDX,IDC_DELSTORE,m_BtnDelStore);
	//DDX_Control(pDX,IDC_TREE_STROE,m_StoreTree);
}

BEGIN_MESSAGE_MAP(XPowerManage,XBaseDialog)
	ON_COMMAND(IDC_ALL,OnBtnClickedAll)
	ON_COMMAND(IDC_ALLNOT,OnBtnClickedAllNot)
	ON_COMMAND(IDC_OTHER,OnBtnClickedOther)

	ON_COMMAND(IDC_ADDUSER,OnBtnClickedAdd)
	ON_COMMAND(IDC_ALTERUSER,OnBtnClickedAlter)
	ON_COMMAND(IDC_COPYUSER,OnBtnClickedCopy)
	ON_COMMAND(IDC_DELUSER,OnBtnClickedDel)

	ON_COMMAND(IDC_QUERYSTORE,OnBtnClickedQueryStore)
	ON_COMMAND(IDC_ADDSTORE,OnBtnClickedAddStore)
	ON_COMMAND(IDC_DELSTORE,OnBtnClickedDelStore)

	ON_NOTIFY(NM_CLICK,IDC_LIST_POWER,OnNMClickPowerList)
	ON_NOTIFY(NM_CLICK,IDC_LIST_USER,OnNMClickUserList)
	ON_NOTIFY(NM_CLICK,IDC_LIST_SUBCTRL,OnNMClickSubPowerList)

	ON_BN_CLICKED(IDC_SUBALL,OnBnClickedSuball)
	ON_BN_CLICKED(IDC_SUBOTHER,OnBnClickedSubother)
	ON_BN_CLICKED(IDC_SUBALLNOT,OnBnClickedSuballnot)

	ON_BN_CLICKED(IDC_RADIO_CTRL,OnBnClickedRadiosel)
	ON_BN_CLICKED(IDC_RADIO_VIEW,OnBnClickedRadiosel)
	ON_BN_CLICKED(IDC_RADIO_LOGIN,OnBnClickedRadiosel)
	ON_BN_CLICKED(IDC_RADIO_MONCTRL,OnBnClickedRadiosel)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()


// XPowerManage 消息处理程序

void XPowerManage::OnOk()
{
	XBaseDialog::OnOK();
}

void XPowerManage::ClearMapUserPower()
{
	for(auto iter=m_MapUserPower.begin();iter!=m_MapUserPower.end();++iter)
	{
		delete iter->second;
	}

	m_MapUserPower.clear();
}

void XPowerManage::ClearMapSubUserPower()
{
	for(auto iter=m_MapSubUserPower.begin();iter!=m_MapSubUserPower.end();++iter)
	{
		delete iter->second;
	}
	m_MapSubUserPower.clear();
}

void XPowerManage::ClearMapSelect()
{
	for(auto iter=m_MapSelect.begin();iter!=m_MapSelect.end();++iter)
	{
		delete iter->second;
	}
	m_MapSelect.clear();
}

void XPowerManage::ClearMapPrivilege()
{
	for(auto iter=m_MapPrivilege.begin();iter!=m_MapPrivilege.end();++iter)
	{
		delete iter->second;
	}
	m_MapPrivilege.clear();
}

BOOL XPowerManage::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XPowerManage::Init()
{
	InitData();
	InitList();
	//InitTree();
	ReloadInterface();
}

void XPowerManage::InitList()
{
	InitUserInfoList();
	InitUserInfo();
	///////////////////
	InitPowerList();
	InitUserPower();
	AddPowerInfo();
	//////////////////
	InitUserList();
	InitUser();
	//////////////////
	InitQueryUserID();
	InitStoreList();
	InitStore();
	///////////////
	InitRadio();
	InitSubPowerList();
	InitSubPower(0);
}

//void XPowerManage::InitTree()
//{
//	InitImageList();
//	m_StoreTree.SetImageList(&m_ImageList,TVSIL_NORMAL);
//
//	HTREEITEM hInItem=AddRootItem(_C(_T("62"),_T("输入")),STORE_IN);
//	m_hInItem=hInItem;
//	HTREEITEM hOutItem=AddRootItem(_C(_T("63"),_T("输出")),STORE_OUT);
//	m_hOutItem=hOutItem;
//
//	InitTreeInfo();
//}
//
//void XPowerManage::InitImageList()
//{
//	if(!m_ImageList.Create(20,20,ILC_COLOR32|ILC_MASK,0,1))
//		return;
//
//	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_INPUT));
//	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_OUTPUT));
//	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUP));
//	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NODE));
//}

MAP_POWER& XPowerManage::GetMapPower()
{
	return m_pDelegate->GetMapPower();
}

MAP_NODE& XPowerManage::GetMapNode()
{
	return m_pDelegate->GetMapNode();
}

MAP_STORE& XPowerManage::GetMapStore()
{
	return m_pDelegate->GetMapStore();
}

CString XPowerManage::GetUserName()
{
	return m_pDelegate->GetUserName();
}

void XPowerManage::InitData()
{
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	CString szUserName=m_pDelegate->GetUserName();

	MAP_POWER::iterator iter=MapPower.find(szUserName);
	if(iter!=MapPower.end())
	{
		m_pPower=iter->second;
	}
}

void XPowerManage::InitPowerList()
{
	XSetListCtrl::InitList(&m_PowerList,1,TRUE);
	m_PowerList.EnableToolTips(TRUE);
	m_PowerList.SetColumnWidth(0,235);
}

void XPowerManage::InitUserInfoList()
{
	XSetListCtrl::InitList(&m_UserInfo,2,FALSE);
	m_UserInfo.EnableToolTips(TRUE);

	m_UserInfo.SetColumnWidth(0,118);
	m_UserInfo.SetColumnWidth(0,118);
}

void XPowerManage::InitUserList()
{
	XSetListCtrl::InitList(&m_UserList,4,FALSE);

	//m_UserList.InitImageList();
	m_UserList.EnableToolTips(TRUE);

	m_UserList.SetColumnWidth(0,50);
	m_UserList.SetColumnWidth(1,80);
	m_UserList.SetColumnWidth(2,75);
	m_UserList.SetColumnWidth(3,116);
}

void XPowerManage::InitStoreList()
{
	//初始化收藏列表
	XSetListCtrl::InitList(&m_StoreList,3,FALSE);

	m_StoreList.EnableToolTips(TRUE);

	//m_StoreList.SetColumnWidth(0,50);
	m_StoreList.SetColumnWidth(0,55);
	m_StoreList.SetColumnWidth(1,123);
	m_StoreList.SetColumnWidth(2,60);
}

void XPowerManage::InitUserPower()
{
	if(nullptr==m_pPower)
		return;

	unsigned int nPermission=m_pPower->GetManagePermission();

	XPowerListInfo* pListInfo=nullptr;
	for(int i=0;i<32;i++)
	{
		BOOL bHas=FALSE;
		if((nPermission&(1<<i))!=0)
			bHas=TRUE;
		else
			bHas=FALSE;

		MAP_USERPOWER::iterator iter=m_MapUserPower.find(i);
		if(iter!=m_MapUserPower.end())
		{
			pListInfo=iter->second;
		}
		else
		{
			pListInfo=new XPowerListInfo;
			m_MapUserPower.insert(std::pair<int,XPowerListInfo*>(i,pListInfo));
		}
		pListInfo->SetPowerIndex(i);
		pListInfo->SetHas(bHas);

		CString szPower=HandlePower::GetPowerByByte(i,bHas);
		pListInfo->SetPowerName(szPower);
	}
}

void XPowerManage::InitSubPowerByUser(CString szUserName)
{
	//m_VecViewNodeID.clear();
	//m_VecLoginNodeID.clear();

	XPower* pPower=nullptr;
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	MAP_POWER::iterator iter=MapPower.find(szUserName);
	if(iter!=MapPower.end())
	{
		pPower=iter->second;
	}

	if(!pPower)
		return;

	//admin 权限不能改	
	CString szCurName=m_pDelegate->GetUserName();
	if(szUserName==_T("admin")||szUserName==szCurName)
		m_SubPowerList.EnableWindow(FALSE);
	else
		m_SubPowerList.EnableWindow(TRUE);

	//接管权限
	////////////////////////////////////////////////////////////////////////
	auto VecCtrlPriv=pPower->GetPrivilegeCtrl().GetVecPrivilege();
	ParsePrivilege(VecCtrlPriv,m_MapPrivilege,szUserName);
	////////////////////////////////////////////////////////////////////////
	//预览权限
	//auto VecViewPriv=pPower->GetPrivilegeView().GetVecPrivilege();
	//ParsePrivilege(VecViewPriv,m_VecViewNodeID);
	////////////////////////////////////////////////////////////////////////
	//登录权限
	auto VecLoginPriv=pPower->GetPrivilegeLogin().GetVecPrivilege();
	ParsePrivilege(VecLoginPriv,m_VecLoginNodeID,szUserName);
}

void XPowerManage::ParsePrivilege(VEC_PRIVILEGE& VecPrivilige,MAP_CTRLPRIVILEGE& MapPrivilege,CString szUserName)
{
	ClearMapPrivilege();
	int nIndex=0;
	for(auto& nValue:VecPrivilige)
	{
		int nIndex2=0;
		for(int i=0;i<8;i++)
		{
			int nNodeID=i+(nIndex*8);

			int nPrivilige=nValue&(0x03<<nIndex2);
			nPrivilige=nPrivilige>>nIndex2;

			XPrivilege* pPrivilige=new XPrivilege;
			//admin权限为3
			if(szUserName==_T("admin"))
				nPrivilige=3;

			pPrivilige->m_nNodeID=nNodeID;
			pPrivilige->m_nPrivilege=nPrivilige;

			MapPrivilege.insert(std::pair<int,XPrivilege*>(nNodeID,pPrivilige));
			nIndex2+=2;
		}
		nIndex++;
	}
}

void XPowerManage::ParsePrivilege(VEC_PRIVILEGE& VecPrivilige,VEC_NODEID& VecNodeID,CString szUSerName)
{
	VecNodeID.clear();
	int nIndex=0;
	for(auto& nValue:VecPrivilige)
	{
		for(int i=0;i<16;i++)
		{
			if(szUSerName==_T("admin"))
			{
				int nNodeID=i+(nIndex*16);
				VecNodeID.push_back(nNodeID);
			}
			else
			{
				if((nValue&(1<<i))!=0)
				{
					int nNodeID=i+(nIndex*16);
					VecNodeID.push_back(nNodeID);
				}
			}
		}
		nIndex++;
	}
}

void XPowerManage::InitSubUserPower(CString szSubUser)
{
	ClearMapSubUserPower();

	XPower* pPower=nullptr;
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	MAP_POWER::iterator iter=MapPower.find(szSubUser);
	if(iter!=MapPower.end())
	{
		pPower=iter->second;
	}

	if(!pPower)
		return;

	unsigned int nPermission=pPower->GetManagePermission();
	XPowerListInfo* pListInfo=nullptr;
	for(int i=0;i<32;i++)
	{
		BOOL bHas=FALSE;
		if((nPermission&(1<<i))!=0)
			bHas=TRUE;
		else
			bHas=FALSE;

		MAP_USERPOWER::iterator iter=m_MapSubUserPower.find(i);
		if(iter!=m_MapSubUserPower.end())
		{
			pListInfo=iter->second;
		}
		else
		{
			pListInfo=new XPowerListInfo;
			m_MapSubUserPower.insert(std::pair<int,XPowerListInfo*>(i,pListInfo));
		}
		pListInfo->SetPowerIndex(i);
		pListInfo->SetHas(bHas);

		CString szPower=HandlePower::GetPowerByByte(i,bHas);
		pListInfo->SetPowerName(szPower);
	}
}

void XPowerManage::InitUserInfo()
{
	if(nullptr==m_pPower)
		return;

	CString szID;
	szID.Format(_T("%d"),m_pPower->GetUserID());
	AddListInfo(GetTranslationString(_T("39"),_T("ID")),szID);

	AddListInfo(GetTranslationString(_T("25"),_T("用户名")),m_pPower->GetUserName());
	AddListInfo(GetTranslationString(_T("26"),_T("密码")),m_pPower->GetPassWd());

	CString szCreateID;
	szCreateID.Format(_T("%d"),m_pPower->GetCreateID());
	AddListInfo(GetTranslationString(_T("40"),_T("创建者")),szCreateID);

	//CString szCreateTime;
	//szCreateTime.Format(_T("%d"),m_pPower->GetCreateTime());
	CString szCreateTime=HandleCalculate::GetTimeBySecond(m_pPower->GetCreateTime());
	AddListInfo(GetTranslationString(_T("41"),_T("创建时间")),szCreateTime);

	AddListInfo(GetTranslationString(_T("42"),_T("用户组")),m_pPower->GetUserGroup());

	CString szLevel;
	szLevel.Format(_T("%d"),m_pPower->GetLevel());
	AddListInfo(GetTranslationString(_T("43"),_T("级别")),szLevel);
}

void XPowerManage::AddPowerInfo()
{
	for(auto iter=m_MapUserPower.begin();iter!=m_MapUserPower.end();++iter)
	{
		XPowerListInfo* pListInfo=iter->second;
		//CString szPower=HandlePower::GetPowerByByte(iter->first,pListInfo->GetHas());
		//pListInfo->SetPowerName(szPower);
		CString szPower=pListInfo->GetPowerName();
		if(szPower!=_T(""))
			AddListInfo(szPower);
	}
}

void XPowerManage::InitUser()
{
	MAP_SUBUSER& MapSubUser=m_pDelegate->GetMapSubUser();
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	//插入当前用户
	//CString szCurName=m_pDelegate->GetUserName();
	//MAP_POWER::iterator iterPower=MapPower.find(szCurName);
	//if(iterPower!=MapPower.end())
	//{
	//	XPower* pPower=iterPower->second;

	//	int nID=pPower->GetUserID();
	//	CString szGroup=pPower->GetUserGroup();
	//	time_t nCreateTime=pPower->GetCreateTime();

	//	CString szCreateTime=HandleCalculate::GetTimeBySecond(nCreateTime);

	//	AddUserListInfo(nID,szCurName,szCreateTime,szGroup);
	//}

	//登录用户没有插入进去
	for(auto iter=MapSubUser.begin();iter!=MapSubUser.end();++iter)
	{
		XSubUserInfo* pSubUserInfo=iter->second;

		int nID=pSubUserInfo->GetID();
		CString szUserName=pSubUserInfo->GetUserName();
		//////////////////////////////////////////////////////////////////////////
		MAP_POWER::iterator iterPower=MapPower.find(szUserName);
		if(iterPower!=MapPower.end())
		{
			XPower* pPower=iterPower->second;

			CString szGroup=pPower->GetUserGroup();
			time_t nCreateTime=pPower->GetCreateTime();
			CString szCreateTime=HandleCalculate::GetTimeBySecond(nCreateTime);

			AddUserListInfo(nID,szUserName,szCreateTime,szGroup);
		}
	}
}

void XPowerManage::InitStore()
{
	//设置收藏列表
	MAP_STORE& MapStore=m_pDelegate->GetMapStore();
	for(auto iter=MapStore.begin();iter!=MapStore.end();++iter)
	{
		XStoreListInfo* pListInfo=iter->second;

		if(pListInfo->GetUserID()==m_nQueryStoreUserID)
		{
			CString szNodeName=pListInfo->GetNodeName();
			int nNodeID=pListInfo->GetNodeID();
			int nType=pListInfo->GetNodeType();

			AddStoreListInfo(nNodeID,szNodeName,nType,pListInfo->GetNumber());
		}
	}
}

void XPowerManage::UpdateStoreList()
{
	m_StoreList.DeleteAllItems();
	//按照名字添加
	MAP_STORE& MapStore=m_pDelegate->GetMapStore();
	for(auto iter=MapStore.begin();iter!=MapStore.end();++iter)
	{
		int nNodeID=iter->first;
		XStoreListInfo* pListInfo=iter->second;

		//if(pListInfo->GetUserName()==m_szQueryStoreUser)
		if(pListInfo->GetUserID()==m_nQueryStoreUserID)
		{
			CString szNodeName=pListInfo->GetNodeName();
			int nNodeID=pListInfo->GetNodeID();
			int nType=pListInfo->GetNodeType();
			int nNumber=pListInfo->GetNumber();

			AddStoreListInfo(nNodeID,szNodeName,nType,nNumber);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void XPowerManage::InitRadio()
{
	((CButton*)GetDlgItem(IDC_RADIO_CTRL))->SetCheck(BST_CHECKED);
	//((CButton*)GetDlgItem(IDC_RADIO_VALID))->SetCheck(BST_CHECKED);
}

int XPowerManage::GetColumnCount()
{
	return m_SubPowerList.GetHeaderCtrl()->GetItemCount();
}

int XPowerManage::GetItemCount()
{
	return m_SubPowerList.GetItemCount();
}

void XPowerManage::OnBnClickedRadiosel()
{
	UpdateData(TRUE);
	//TRACE(_T("Radio=%d\n"),m_nRadioSelect);

	int nIndex=m_nRadioSelect;
	if(nIndex==0)
	{
		SetSubPowerTitle(_C(_T("293"),_T("接管输入节点")),nIndex);
		InitSubPower(nIndex);
	}
	else if(nIndex==1)
	{
		SetSubPowerTitle(_C(_T("294"),_T("预览输入节点")),nIndex);
		InitSubPower(nIndex);
	}
	else if(nIndex==2)
	{
		SetSubPowerTitle(_C(_T("295"),_T("登录输出节点")),nIndex);
		InitSubPower(nIndex);
	}
	else if(nIndex==3)
	{
		SetSubPowerTitle(_C(_T("303"),_T("独占输入节点")),nIndex);
		InitSubPower(nIndex);
	}
}

void XPowerManage::SetSubPowerTitle(CString szTitle,int nIndex)
{
	CString szTemp=szTitle;
	LVCOLUMN col;
	col.mask=LVCF_TEXT;

	int nColumnCount=m_SubPowerList.GetHeaderCtrl()->GetItemCount();
	int nCount=m_SubPowerList.GetItemCount();
	if(nIndex==0||nIndex==1||nIndex==3)
	{
		//3列
		if(nColumnCount==2)
		{
			m_SubPowerList.InsertColumn(2,_T(""),LVCFMT_LEFT,50,0);
		}

		CString szID=_T("ID");
		col.pszText=szID.GetBuffer();
		m_SubPowerList.SetColumn(0,&col);
		szID.ReleaseBuffer();

		col.pszText=szTemp.GetBuffer();
		m_SubPowerList.SetColumn(1,&col);
		szTemp.ReleaseBuffer();

		CString szCur=_C(_T("304"),_T("权限"));
		col.pszText=szCur.GetBuffer();
		m_SubPowerList.SetColumn(2,&col);
		szCur.ReleaseBuffer();

		if(nCount>22)
		{
			m_SubPowerList.SetColumnWidth(0,50);
			m_SubPowerList.SetColumnWidth(1,137);
			m_SubPowerList.SetColumnWidth(2,50);
		}
		else
		{
			m_SubPowerList.SetColumnWidth(0,50);
			m_SubPowerList.SetColumnWidth(1,135);
			m_SubPowerList.SetColumnWidth(2,50);
		}
	}
	else
	{
		//2列
		if(nColumnCount==3)
		{
			m_SubPowerList.DeleteColumn(2);
		}

		CString szID=_T("ID");
		col.pszText=szID.GetBuffer();
		m_SubPowerList.SetColumn(0,&col);
		szID.ReleaseBuffer();

		col.pszText=szTemp.GetBuffer();
		m_SubPowerList.SetColumn(1,&col);
		szTemp.ReleaseBuffer();

		//设置列宽度
		if(nCount>22)
		{
			m_SubPowerList.SetColumnWidth(0,80);
			m_SubPowerList.SetColumnWidth(1,137);
		}
		else
		{
			m_SubPowerList.SetColumnWidth(0,80);
			m_SubPowerList.SetColumnWidth(1,155);
		}
	}
}

void XPowerManage::InitSubPowerList()
{
	XSetListCtrl::InitList(&m_SubPowerList,3,TRUE);
	m_SubPowerList.EnableToolTips(TRUE);
	m_SubPowerList.SetColumnWidth(0,50);
	m_SubPowerList.SetColumnWidth(1,135);
	m_SubPowerList.SetColumnWidth(2,50);
}

void XPowerManage::InitSubPower(int nIndex)
{
	m_SubPowerList.DeleteAllItems();
	MAP_NODEALL& MapNodeAll=m_pDelegate->GetMapNodeAll();
	for(auto& node:MapNodeAll)
	{
		XNodeAll* pNode=node.second;
		if(nIndex==0)
		{
			if(pNode->GetNodeType()==TERM_IN)
			{
				int nListIndex=AddSubPowerInfo(pNode->GetNodeID(),pNode->GetNodeName());
				//根据保存初始化
				SubSelectByNodeID(m_VecCtrlSel,pNode->GetNodeID(),nListIndex);
				//判断其他里面有没有
				CString szNodeID;
				szNodeID.Format(_T("%d"),pNode->GetNodeID());
				if(GetNodeInVecSelect(m_VecCtrlSel,szNodeID))
				{
					//在
					InsertSubPowerList(nListIndex,0);
				}
				else
				{
					//不在
					if(GetNodeInVecSelect(m_VecViewSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,1);
					}
					else if(GetNodeInVecSelect(m_VecMonCtrlSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,3);
					}
					else if(!GetNodeInVecSelect(m_VecMonCtrlSel,szNodeID)&&!GetNodeInVecSelect(m_VecViewSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,-1);
					}
				}
			}
		}
		else if(nIndex==1)
		{
			if(pNode->GetNodeType()==TERM_IN)
			{
				int nListIndex=AddSubPowerInfo(pNode->GetNodeID(),pNode->GetNodeName());
				SubSelectByNodeID(m_VecViewSel,pNode->GetNodeID(),nListIndex);

				//判断其他里面有没有
				CString szNodeID;
				szNodeID.Format(_T("%d"),pNode->GetNodeID());
				if(GetNodeInVecSelect(m_VecViewSel,szNodeID))
				{
					//在
					InsertSubPowerList(nListIndex,1);
				}
				else
				{
					//不在
					if(GetNodeInVecSelect(m_VecCtrlSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,0);
					}
					else if(GetNodeInVecSelect(m_VecMonCtrlSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,3);
					}
					else if(!GetNodeInVecSelect(m_VecMonCtrlSel,szNodeID)&&!GetNodeInVecSelect(m_VecCtrlSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,-1);
					}
				}
			}
		}
		else if(nIndex==2)
		{
			if(pNode->GetNodeType()==TERM_OUT)
			{
				int nListIndex=AddSubPowerInfo(pNode->GetNodeID(),pNode->GetNodeName());
				SubSelectByNodeID(m_VecLoginSel,pNode->GetNodeID(),nListIndex);
			}
		}
		else if(nIndex==3)
		{
			if(pNode->GetNodeType()==TERM_IN)
			{
				int nListIndex=AddSubPowerInfo(pNode->GetNodeID(),pNode->GetNodeName());
				//打勾
				SubSelectByNodeID(m_VecMonCtrlSel,pNode->GetNodeID(),nListIndex);
				//判断其他里面有没有
				CString szNodeID;
				szNodeID.Format(_T("%d"),pNode->GetNodeID());
				if(GetNodeInVecSelect(m_VecMonCtrlSel,szNodeID))
				{
					//在
					InsertSubPowerList(nListIndex,3);
				}
				else
				{
					//不在
					if(GetNodeInVecSelect(m_VecCtrlSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,0);
					}
					else if(GetNodeInVecSelect(m_VecViewSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,1);
					}
					else if(!GetNodeInVecSelect(m_VecViewSel,szNodeID)&&!GetNodeInVecSelect(m_VecCtrlSel,szNodeID))
					{
						InsertSubPowerList(nListIndex,-1);
					}
				}
			}
		}
	}
}

void XPowerManage::SubSelectByNodeID(VEC_SUBSELECT& VecSelect,int nNodeID,int nIndex)
{
	CString szNodeID;
	szNodeID.Format(_T("%d"),nNodeID);

	for(auto& nodeName:VecSelect)
	{
		if(szNodeID==nodeName)
		{
			XSetListCtrl::SetListCheckItem(&m_SubPowerList,nIndex);
		}
	}
}

void XPowerManage::InsertSubPowerList(int nItem,int nRadio)
{
	//插入第三列
	if(nRadio==0)
	{
		m_SubPowerList.SetItemText(nItem,2,_C(_T("69"),_T("接管")));
	}
	else if(nRadio==1)
	{
		m_SubPowerList.SetItemText(nItem,2,_C(_T("86"),_T("预览")));
	}
	else if(nRadio==3)
	{
		m_SubPowerList.SetItemText(nItem,2,_C(_T("305"),_T("独占")));
	}
	else if(nRadio==-1)
	{
		m_SubPowerList.SetItemText(nItem,2,_C(_T("306"),_T("无权限")));
	}
}

int XPowerManage::AddSubPowerInfo(int nNodeID,CString szNodeName)
{
	int nCount=GetItemCount();
	int nColumnCount=GetColumnCount();
	int nIndex=m_nRadioSelect;

	if(nIndex==0||nIndex==1||nIndex==3)
	{
		if(nCount>22)
		{
			m_SubPowerList.SetColumnWidth(0,50);
			m_SubPowerList.SetColumnWidth(1,118);
			m_SubPowerList.SetColumnWidth(2,50);
		}
		else
		{
			m_SubPowerList.SetColumnWidth(0,50);
			m_SubPowerList.SetColumnWidth(1,135);
			m_SubPowerList.SetColumnWidth(2,50);
		}

		m_SubPowerList.InsertItem(nCount,_T(""));

		CString szNodeID;
		szNodeID.Format(_T("%d"),nNodeID);
		m_SubPowerList.SetItemText(nCount,0,szNodeID);
		m_SubPowerList.SetItemText(nCount,1,szNodeName);
		m_SubPowerList.SetItemText(nCount,2,_T("无权限"));
	}
	else if(nIndex==2)
	{
		if(nCount>22)
		{
			m_SubPowerList.SetColumnWidth(0,80);
			m_SubPowerList.SetColumnWidth(1,138);
		}
		else
		{
			m_SubPowerList.SetColumnWidth(0,80);
			m_SubPowerList.SetColumnWidth(1,154);
		}

		m_SubPowerList.InsertItem(nCount,_T(""));

		CString szNodeID;
		szNodeID.Format(_T("%d"),nNodeID);
		m_SubPowerList.SetItemText(nCount,0,szNodeID);
		m_SubPowerList.SetItemText(nCount,1,szNodeName);
	}

	return nCount;
}

void XPowerManage::SetSubPowerList(int nCount,int nNodeID,CString szName,CString szItem)
{
	//CString szNodeID;
	//szNodeID.Format(_T("%d"),nNodeID);
	//m_SubPowerList.SetItemText(nCount,0,szNodeID);
	//m_SubPowerList.SetItemText(nCount,1,szName);
	//m_SubPowerList.SetItemText(nCount,2,_T("无权限"));
}

void XPowerManage::ReloadInterface()
{
	SetWindowText(_C(_T("35"),_T("权限管理")));

	//////////////////////////////////////////////////////////////////////////
	//m_TextGroup1.SetLeft(TRUE);
	//m_TextGroup2.SetLeft(TRUE);
	//m_TextGroup3.SetLeft(TRUE);
	//m_TextGroup4.SetLeft(TRUE);
	//m_TextTip.SetLeft(TRUE);
	m_TextGroup1.SetText(_C(_T("230"),_T("当前用户信息")),TRUE);
	m_TextGroup2.SetText(_C(_T("296"),_T("子权限")),TRUE);
	m_TextGroup3.SetText(_C(_T("231"),_T("用户列表")),TRUE);
	m_TextGroup4.SetText(_C(_T("232"),_T("收藏列表")),TRUE);

	m_TextTip.SetText(_C(_T("302"),_T("提示:添加用户时，先选择权限，修改用户时，先修改权限")),TRUE);
	//////////////////////////////////////////////////////////////////////////
	m_BtnAll.SetCaption(_C(_T("51"),_T("全选")));
	m_BtnOther.SetCaption(_C(_T("52"),_T("反选")));
	m_BtnAllNot.SetCaption(_C(_T("53"),_T("全不选")));
	m_BtnSubAll.SetCaption(_C(_T("51"),_T("全选")));
	m_BtnSubOther.SetCaption(_C(_T("52"),_T("反选")));
	m_BtnSubAllNot.SetCaption(_C(_T("53"),_T("全不选")));

	m_BtnAddUser.SetCaption(_C(_T("54"),_T("添加")));
	m_BtnAlterUser.SetCaption(_C(_T("55"),_T("修改")));
	m_BtnCopyUser.SetCaption(_C(_T("56"),_T("复制")));
	m_BtnDelUser.SetCaption(_C(_T("57"),_T("删除")));
	m_BtnQueryStore.SetCaption(_C(_T("119"),_T("查询")));
	m_BtnAddStore.SetCaption(_C(_T("54"),_T("添加")));
	m_BtnDelStore.SetCaption(_C(_T("57"),_T("删除")));

	GetDlgItem(IDC_RADIO_CTRL)->SetWindowText(_C(_T("69"),_T("接管")));
	GetDlgItem(IDC_RADIO_VIEW)->SetWindowText(_C(_T("86"),_T("预览")));
	GetDlgItem(IDC_RADIO_LOGIN)->SetWindowText(_C(_T("24"),_T("登录")));
	GetDlgItem(IDC_RADIO_MONCTRL)->SetWindowText(_C(_T("305"),_T("独占")));

	ReloadListInterface();
}

void XPowerManage::ReloadListInterface()
{
	CString szTemp=_T("");

	LVCOLUMN col;
	col.mask=LVCF_TEXT;

	szTemp=GetTranslationString(_T("38"),_T("用户权限"));
	col.pszText=szTemp.GetBuffer();
	m_PowerList.SetColumn(0,&col);
	szTemp.ReleaseBuffer();
	//////////////////////////////////////////////////////////////////////////
	szTemp=GetTranslationString(_T("39"),_T("ID"));
	col.pszText=szTemp.GetBuffer();
	m_UserList.SetColumn(0,&col);
	szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("25"),_T("用户名"));
	col.pszText=szTemp.GetBuffer();
	m_UserList.SetColumn(1,&col);
	szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("42"),_T("用户组"));
	col.pszText=szTemp.GetBuffer();
	m_UserList.SetColumn(2,&col);
	szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("41"),_T("创建时间"));
	col.pszText=szTemp.GetBuffer();
	m_UserList.SetColumn(3,&col);
	szTemp.ReleaseBuffer();
	//////////////////////////////////////////////////////////////////////////
	//szTemp=_T("NO.");
	//col.pszText=szTemp.GetBuffer();
	//m_StoreList.SetColumn(0,&col);
	//szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("59"),_T("节点ID"));
	col.pszText=szTemp.GetBuffer();
	m_StoreList.SetColumn(0,&col);
	szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("60"),_T("节点名称"));
	col.pszText=szTemp.GetBuffer();
	m_StoreList.SetColumn(1,&col);
	szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("61"),_T("类型"));
	col.pszText=szTemp.GetBuffer();
	m_StoreList.SetColumn(2,&col);
	szTemp.ReleaseBuffer();

	/////////////////////////////////////////////////////////////////////////
	szTemp=_T("ID");
	col.pszText=szTemp.GetBuffer();
	m_SubPowerList.SetColumn(0,&col);
	szTemp.ReleaseBuffer();

	szTemp=GetTranslationString(_T("293"),_T("接管输入节点"));
	col.pszText=szTemp.GetBuffer();
	m_SubPowerList.SetColumn(1,&col);
	szTemp.ReleaseBuffer();

	if(GetColumnCount()==3)
	{
		szTemp=GetTranslationString(_T("304"),_T("权限"));
		col.pszText=szTemp.GetBuffer();
		m_SubPowerList.SetColumn(2,&col);
		szTemp.ReleaseBuffer();
	}
}

void XPowerManage::OnNMClickPowerList(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate=reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos=GetMessagePos();
	CPoint pt(dwPos);
	m_PowerList.ScreenToClient(&pt);

	UINT nFlag;
	int nItem=m_PowerList.HitTest(pt,&nFlag);

	BOOL bCheckState=m_PowerList.GetCheck(nItem);
	if(nFlag==LVHT_ONITEMSTATEICON)
	{
		//注意，bCheckState为TRUE，checkbox从勾选状态变为未勾选状态
		if(bCheckState)
		{
			MAP_SELECT::iterator iter=m_MapSelect.find(nItem);
			if(iter!=m_MapSelect.end())
			{
				XPowerSelectInfo* pInfo=iter->second;
				m_MapSelect.erase(iter);
				delete pInfo;
			}
		}
		else
		{
			CString szItemText=XSetListCtrl::GetColumnText(&m_PowerList,nItem,0);
			int nPowerIndex=GetPowerIndexByName(szItemText);

			XPowerSelectInfo* pInfo=new XPowerSelectInfo;
			pInfo->SetPowerName(szItemText);
			pInfo->SetPowerIndex(nPowerIndex);

			m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(nItem,pInfo));
		}
	}
	else if(nFlag==LVHT_ONITEMLABEL||nFlag==LVHT_ONITEM)
	{
		//单击选项
		if(bCheckState)
		{
			XSetListCtrl::SetListCheckItemFalse(&m_PowerList,nItem);

			MAP_SELECT::iterator iter=m_MapSelect.find(nItem);
			if(iter!=m_MapSelect.end())
			{
				XPowerSelectInfo* pInfo=iter->second;
				m_MapSelect.erase(iter);
				delete pInfo;
			}
		}
		else
		{
			XSetListCtrl::SetListCheckItem(&m_PowerList,nItem);

			CString szItemText=XSetListCtrl::GetColumnText(&m_PowerList,nItem,0);
			int nPowerIndex=GetPowerIndexByName(szItemText);

			XPowerSelectInfo* pInfo=new XPowerSelectInfo;
			pInfo->SetPowerName(szItemText);
			pInfo->SetPowerIndex(nPowerIndex);

			m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(nItem,pInfo));
		}
	}

	*pResult=0;
}

int XPowerManage::GetPowerIndexByName(CString szPowerName)
{
	for(auto iter=m_MapUserPower.begin();iter!=m_MapUserPower.end();++iter)
	{
		XPowerListInfo* pInfo=iter->second;

		if(szPowerName==pInfo->GetPowerName())
		{
			return pInfo->GetPowerIndex();
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//权限列表选择按钮
void XPowerManage::OnBtnClickedAll()
{
	//全选
	ClearMapSelect();

	int nCount=m_PowerList.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		XSetListCtrl::SetListCheckItem(&m_PowerList,i);

		CString szItem=XSetListCtrl::GetColumnText(&m_PowerList,i,0);
		int nPowerIndex=GetPowerIndexByName(szItem);

		XPowerSelectInfo* pInfo=new XPowerSelectInfo;
		pInfo->SetPowerName(szItem);
		pInfo->SetPowerIndex(nPowerIndex);

		m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(i,pInfo));
	}
}

void XPowerManage::OnBtnClickedOther()
{
	//反选
	int nCount=m_PowerList.GetItemCount();

	for(int i=0;i<nCount;i++)
	{
		MAP_SELECT::iterator iter=m_MapSelect.find(i);
		if(iter==m_MapSelect.end())
		{
			XSetListCtrl::SetListCheckItem(&m_PowerList,i);

			CString szItem=XSetListCtrl::GetColumnText(&m_PowerList,i,0);
			int nPowerIndex=GetPowerIndexByName(szItem);

			XPowerSelectInfo* pInfo=new XPowerSelectInfo;
			pInfo->SetPowerName(szItem);
			pInfo->SetPowerIndex(nPowerIndex);

			m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(i,pInfo));
		}
		else
		{
			XSetListCtrl::SetListCheckItemFalse(&m_PowerList,i);

			XPowerSelectInfo* pInfo=iter->second;
			m_MapSelect.erase(iter);
			delete pInfo;
		}
	}
}

void XPowerManage::OnBtnClickedAllNot()
{
	//全不选
	ClearMapSelect();

	int nCount=m_PowerList.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		XSetListCtrl::SetListCheckItemFalse(&m_PowerList,i);
	}
}
//////////////////////////////////////////////////////////////////////////
void XPowerManage::OnBnClickedSuball()
{
	int nIndex=m_nRadioSelect;
	if(nIndex==0)
	{
		SubPowerListSelectAll(m_VecCtrlSel);
	}
	else if(nIndex==1)
	{
		SubPowerListSelectAll(m_VecViewSel);
	}
	else if(nIndex==2)
	{
		SubPowerListSelectAll(m_VecLoginSel);
	}
	else if(nIndex==3)
	{
		SubPowerListSelectAll(m_VecMonCtrlSel);
	}
}

void XPowerManage::SubPowerListSelectAll(VEC_SUBSELECT& VecSel)
{
	VecSel.clear();
	int nCount=m_SubPowerList.GetItemCount();

	for(int i=0;i<nCount;i++)
	{
		XSetListCtrl::SetListCheckItem(&m_SubPowerList,i);
		InsertSubPowerList(i,m_nRadioSelect);
		CString szItem=XSetListCtrl::GetColumnText(&m_SubPowerList,i,0);
		VecSel.push_back(szItem);
	}
	//////////////////////////////////////////////////////////////////////////
	if(m_nRadioSelect==0)
	{
		m_VecViewSel.clear();
		m_VecMonCtrlSel.clear();
	}
	else if(m_nRadioSelect==1)
	{
		m_VecCtrlSel.clear();
		m_VecMonCtrlSel.clear();
	}
	else if(m_nRadioSelect==3)
	{
		m_VecCtrlSel.clear();
		m_VecViewSel.clear();
	}
}

void XPowerManage::OnBnClickedSubother()
{
	//反选
	int nIndex=m_nRadioSelect;
	if(nIndex==0)
	{
		SubPowerListSelectOther(m_VecCtrlSel);
	}
	else if(nIndex==1)
	{
		SubPowerListSelectOther(m_VecViewSel);
	}
	else if(nIndex==2)
	{
		SubPowerListSelectOther(m_VecLoginSel);
	}
	else if(nIndex==3)
	{
		SubPowerListSelectOther(m_VecMonCtrlSel);
	}
}

void XPowerManage::SubPowerListSelectOther(VEC_SUBSELECT& VecSel)
{
	int nCount=m_SubPowerList.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		CString szItem=XSetListCtrl::GetColumnText(&m_SubPowerList,i,0);
		if(GetNodeInVecSelect(VecSel,szItem))
		{
			//如果找到就删除
			XSetListCtrl::SetListCheckItemFalse(&m_SubPowerList,i);
			DeleteNodeByName(VecSel,szItem);

			//判断在不在三个里面
			if(m_nRadioSelect==0)
			{
				if(!GetNodeInVecSelect(m_VecViewSel,szItem)&&!GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					InsertSubPowerList(i,-1);
				}
			}
			else if(m_nRadioSelect==1)
			{
				if(!GetNodeInVecSelect(m_VecCtrlSel,szItem)&&!GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					InsertSubPowerList(i,-1);
				}
			}
			else if(m_nRadioSelect==3)
			{
				if(!GetNodeInVecSelect(m_VecCtrlSel,szItem)&&!GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					InsertSubPowerList(i,-1);
				}
			}
		}
		else
		{
			//不在插入
			XSetListCtrl::SetListCheckItem(&m_SubPowerList,i);
			VecSel.push_back(szItem);
			InsertSubPowerList(i,m_nRadioSelect);

			//取消其他两个
			if(m_nRadioSelect==0)
			{
				if(GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					DeleteNodeByName(m_VecViewSel,szItem);
				}

				if(GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecMonCtrlSel,szItem);
				}
			}
			else if(m_nRadioSelect==1)
			{
				if(GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecCtrlSel,szItem);
				}

				if(GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecMonCtrlSel,szItem);
				}
			}
			else if(m_nRadioSelect==3)
			{
				if(GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecCtrlSel,szItem);
				}

				if(GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					DeleteNodeByName(m_VecViewSel,szItem);
				}
			}
		}
	}
}

BOOL XPowerManage::GetNodeInVecSelect(VEC_SUBSELECT& VecSel,CString szName)
{
	for(auto& nodeName:VecSel)
	{
		if(nodeName==szName)
			return TRUE;
	}
	return FALSE;
}

BOOL XPowerManage::GetNodeInVecSelect(VEC_NODEID& VecNodeID,CString szName)
{
	int nNode=_ttoi(szName);
	for(auto& nodeID:VecNodeID)
	{
		if(nodeID==nNode)
			return TRUE;
	}
	return FALSE;
}

void XPowerManage::DeleteNodeByName(VEC_SUBSELECT& VecSel,CString szName)
{
	for(auto iter=VecSel.begin();iter!=VecSel.end();)
	{
		CString szNodeName=*iter;
		if(szName==szNodeName)
		{
			iter=VecSel.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void XPowerManage::OnBnClickedSuballnot()
{
	if(m_nRadioSelect==0)
	{
		m_VecCtrlSel.clear();
	}
	else if(m_nRadioSelect==1)
	{
		m_VecViewSel.clear();
	}
	else if(m_nRadioSelect==3)
	{
		m_VecLoginSel.clear();
	}

	int nCount=m_SubPowerList.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		CString szItem=XSetListCtrl::GetColumnText(&m_SubPowerList,i,0);
		XSetListCtrl::SetListCheckItemFalse(&m_SubPowerList,i);

		if(m_nRadioSelect==0)
		{
			if(!GetNodeInVecSelect(m_VecViewSel,szItem)&&!GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
			{
				InsertSubPowerList(i,-1);
			}
		}
		else if(m_nRadioSelect==1)
		{
			if(!GetNodeInVecSelect(m_VecCtrlSel,szItem)&&!GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
			{
				InsertSubPowerList(i,-1);
			}
		}
		else if(m_nRadioSelect==3)
		{
			if(!GetNodeInVecSelect(m_VecCtrlSel,szItem)&&!GetNodeInVecSelect(m_VecViewSel,szItem))
			{
				InsertSubPowerList(i,-1);
			}
		}
	}
}

void XPowerManage::OnNMClickSubPowerList(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate=reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos=GetMessagePos();
	CPoint pt(dwPos);
	m_SubPowerList.ScreenToClient(&pt);

	UINT nFlag;
	int nItem=m_SubPowerList.HitTest(pt,&nFlag);
	CString szItem=XSetListCtrl::GetColumnText(&m_SubPowerList,nItem,0);

	int nComIndex=m_nRadioSelect;
	//TRACE(_T("Comindex=%d\n"),nComIndex);
	//////////////////////////////////////////////////////////////////////////
	BOOL bCheckState=m_SubPowerList.GetCheck(nItem);
	if(nFlag==LVHT_ONITEMSTATEICON)
	{
		//注意，bCheckState为TRUE，checkbox从勾选状态变为未勾选状态
		if(bCheckState)
		{
			//TRACE(_T("Check=%d\n"),bCheckState);
			//如果找到就删除
			if(nComIndex==0)
			{
				if(GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecCtrlSel,szItem);
					//更新状态
					InsertSubPowerList(nItem,-1);
				}
			}
			else if(nComIndex==1)
			{
				if(GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					DeleteNodeByName(m_VecViewSel,szItem);
					InsertSubPowerList(nItem,-1);
				}
			}
			else if(nComIndex==2)
			{
				if(GetNodeInVecSelect(m_VecLoginSel,szItem))
				{
					DeleteNodeByName(m_VecLoginSel,szItem);
				}
			}
			else if(nComIndex==3)
			{
				if(GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecMonCtrlSel,szItem);
					InsertSubPowerList(nItem,-1);
				}
			}
		}
		else
		{
			//TRACE(_T("Check=%d\n"),bCheckState);
			//不在
			if(nComIndex==0)
			{
				if(!GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					m_VecCtrlSel.push_back(szItem);
					InsertSubPowerList(nItem,nComIndex);
				}
				//把其他删除掉
				if(GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					DeleteNodeByName(m_VecViewSel,szItem);
				}
				if(GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecMonCtrlSel,szItem);
				}

			}
			else if(nComIndex==1)
			{
				if(!GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					m_VecViewSel.push_back(szItem);
					InsertSubPowerList(nItem,nComIndex);
				}
				//////////////////////////////////////////////////////////////////////////
				if(GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecCtrlSel,szItem);
				}
				if(GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecMonCtrlSel,szItem);
				}

			}
			else if(nComIndex==2)
			{
				if(!GetNodeInVecSelect(m_VecLoginSel,szItem))
				{
					m_VecLoginSel.push_back(szItem);
				}
			}
			else if(nComIndex==3)
			{
				if(!GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					m_VecMonCtrlSel.push_back(szItem);
					InsertSubPowerList(nItem,nComIndex);
				}
				//////////////////////////////////////////////////////////////////////////
				if(GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecCtrlSel,szItem);
				}
				if(GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					DeleteNodeByName(m_VecViewSel,szItem);
				}
			}
		}
	}
	else if(nFlag==LVHT_ONITEMLABEL||nFlag==LVHT_ONITEM)
	{
		//单击选项
		if(bCheckState)
		{
			//TRACE(_T("Check=%d\n"),bCheckState);
			//TRACE(_T("item=%s\n"),szItem);

			XSetListCtrl::SetListCheckItemFalse(&m_SubPowerList,nItem);

			if(nComIndex==0)
			{
				if(GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					//如果找到就删除
					DeleteNodeByName(m_VecCtrlSel,szItem);
					InsertSubPowerList(nItem,-1);
				}
			}
			else if(nComIndex==1)
			{
				if(GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					//如果找到就删除
					DeleteNodeByName(m_VecViewSel,szItem);
					InsertSubPowerList(nItem,-1);
				}
			}
			else if(nComIndex==2)
			{
				if(GetNodeInVecSelect(m_VecLoginSel,szItem))
				{
					//如果找到就删除
					DeleteNodeByName(m_VecLoginSel,szItem);
				}
			}
			else if(nComIndex==3)
			{
				if(GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					//如果找到就删除
					DeleteNodeByName(m_VecMonCtrlSel,szItem);
					InsertSubPowerList(nItem,-1);
				}
			}
		}
		else
		{
			//TRACE(_T("Check=%d\n"),bCheckState);
			XSetListCtrl::SetListCheckItem(&m_SubPowerList,nItem);

			//不在
			if(nComIndex==0)
			{
				if(!GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					m_VecCtrlSel.push_back(szItem);
					InsertSubPowerList(nItem,nComIndex);
				}
				//把其他删除掉
				if(GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					DeleteNodeByName(m_VecViewSel,szItem);
				}
				if(GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecMonCtrlSel,szItem);
				}

			}
			else if(nComIndex==1)
			{
				if(!GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					m_VecViewSel.push_back(szItem);
					InsertSubPowerList(nItem,nComIndex);
				}
				//////////////////////////////////////////////////////////////////////////
				if(GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecCtrlSel,szItem);
				}
				if(GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecMonCtrlSel,szItem);
				}

			}
			else if(nComIndex==2)
			{
				if(!GetNodeInVecSelect(m_VecLoginSel,szItem))
				{
					m_VecLoginSel.push_back(szItem);
				}
			}
			else if(nComIndex==3)
			{
				if(!GetNodeInVecSelect(m_VecMonCtrlSel,szItem))
				{
					m_VecMonCtrlSel.push_back(szItem);
					InsertSubPowerList(nItem,nComIndex);
				}
				//////////////////////////////////////////////////////////////////////////
				if(GetNodeInVecSelect(m_VecCtrlSel,szItem))
				{
					DeleteNodeByName(m_VecCtrlSel,szItem);
				}
				if(GetNodeInVecSelect(m_VecViewSel,szItem))
				{
					DeleteNodeByName(m_VecViewSel,szItem);
				}
			}
		}
	}

	*pResult=0;
}

//////////////////////////////////////////////////////////////////////////
void XPowerManage::SetUserInfo(CString szUserName,CString szPassWd)
{
	m_szUserName=szUserName;
	m_szPassWd=szPassWd;
}

//创建用户列表控制按钮
void XPowerManage::OnBtnClickedAdd()
{
	//添加用户(组信息，权限暂时没添加)
	if(m_MapSelect.size()==0)
	{
		_M(_T("48"),_T("请先选择权限！"),MB_OK);
		return;
	}

	XAddUser dlg;
	m_pAddUser=&dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();
	m_pAddUser=nullptr;
}

void XPowerManage::CloseAddUserDlg()
{
	if(nullptr!=m_pAddUser)
		m_pAddUser->OnOk();
}

void XPowerManage::AddUser()
{
	DWORD dwTime=GetTickCount();
	if((long)dwTime-(long)m_dwTime<3000)
	{
		m_dwTime=GetTickCount();
		//TRACE(_T("\nReturn\n"));
		return;
	}

	//根据选择计算权限
	int nPermission=0;
	for(auto iter=m_MapSelect.begin();iter!=m_MapSelect.end();++iter)
	{
		XPowerSelectInfo* pInfo=iter->second;
		int nIndex=pInfo->GetPowerIndex();
		nPermission|=(1<<nIndex);
	}
	//计算子权限
	VEC_PRIVILEGE VecCtrl;
	MAP_CTRLPRIVILEGE MapPrivilege;
	SetPrivilegeBySelect(m_VecCtrlSel,MapPrivilege,2);
	SetPrivilegeBySelect(m_VecViewSel,MapPrivilege,1);
	SetPrivilegeBySelect(m_VecMonCtrlSel,MapPrivilege,3);


	//for(auto iter=m_VecCtrlSel.begin();iter!=m_VecCtrlSel.end();++iter)
	//{
	//	CString szNodeID=*iter;
	//	int nNodeID=_ttoi(szNodeID);

	//	XPrivilege* p=new XPrivilege;
	//	p->m_nNodeID=nNodeID;
	//	p->m_nPrivilege=2;

	//	MapPrivilege.insert(std::pair<int,XPrivilege*>(nNodeID,p));
	//}

	//for(auto iter=m_VecViewSel.begin();iter!=m_VecViewSel.end();++iter)
	//{
	//	CString szNodeID=*iter;
	//	int nNodeID=_ttoi(szNodeID);

	//	XPrivilege* p=new XPrivilege;
	//	p->m_nNodeID=nNodeID;
	//	p->m_nPrivilege=1;

	//	MapPrivilege.insert(std::pair<int,XPrivilege*>(nNodeID,p));
	//}

	//for(auto iter=m_VecMonCtrlSel.begin();iter!=m_VecMonCtrlSel.end();++iter)
	//{
	//	CString szNodeID=*iter;
	//	int nNodeID=_ttoi(szNodeID);

	//	XPrivilege* p=new XPrivilege;
	//	p->m_nNodeID=nNodeID;
	//	p->m_nPrivilege=3;

	//	MapPrivilege.insert(std::pair<int,XPrivilege*>(nNodeID,p));
	//}

	WritePrivilege(VecCtrl,MapPrivilege);

	VEC_PRIVILEGE VecLogin;
	WritePrivilege(VecLogin,m_VecLoginSel);

	CString szCurUser=m_pDelegate->GetUserName();

	XPower pPower;
	pPower.SetUserName(m_szUserName);
	pPower.SetPassWd(m_szPassWd);
	pPower.SetManagePermission(nPermission);
	pPower.SetUserGroup(szCurUser);
	pPower.GetPrivilegeCtrl().SetType(86);
	pPower.GetPrivilegeLogin().SetType(86);
	pPower.GetPrivilegeView().SetType(86);
	pPower.GetPrivilegeCtrl().SetVecPrivilege(VecCtrl);
	pPower.GetPrivilegeLogin().SetVecPrivilege(VecLogin);
	//pPower.GetPrivilegeView().SetVecPrivilege(VecView);

	XSendDataManage::GetInstance()->AddSendDataOfAddUser(&pPower);
}

void XPowerManage::SetPrivilegeBySelect(VEC_SUBSELECT& VecSelect,MAP_CTRLPRIVILEGE& MapPrivilege,int nType)
{
	for(auto iter=VecSelect.begin();iter!=VecSelect.end();++iter)
	{
		CString szNodeID=*iter;
		int nNodeID=_ttoi(szNodeID);

		XPrivilege* p=new XPrivilege;
		p->m_nNodeID=nNodeID;
		p->m_nPrivilege=nType;

		MapPrivilege.insert(std::pair<int,XPrivilege*>(nNodeID,p));
	}
}

void XPowerManage::WritePrivilege(VEC_PRIVILEGE& VecPrivilige,MAP_CTRLPRIVILEGE& MapPrivilege)
{
	for(int i=0;i<128;i++)
	{
		int nPrilivage=0;
		int nIndex=0;
		for(int j=0;j<8;j++)
		{
			int nNodeID=j+i*8;
			if(MapPrivilege.find(nNodeID)!=MapPrivilege.end())
			{
				XPrivilege* p=MapPrivilege[nNodeID];
				int nPri=p->m_nPrivilege;


				nPrilivage|=(nPri<<nIndex);
			}
			nIndex+=2;
		}
		VecPrivilige.push_back(nPrilivage);
	}
}

void XPowerManage::WritePrivilege(VEC_PRIVILEGE& VecPriviege,VEC_SUBSELECT& VecNodeID)
{
	for(int i=0;i<32;i++)
	{
		int nPrilivage=0;
		for(int j=0;j<16;j++)
		{
			CString szNodeID;
			szNodeID.Format(_T("%d"),j+i*16);
			if(GetNodeInVecSelect(VecNodeID,szNodeID))
			{
				nPrilivage|=(1<<j);
			}
		}
		VecPriviege.push_back(nPrilivage);
	}
}

void XPowerManage::UpdateUserList(int nID,CString szUserName)
{
	//只是更新用户列表
	MAP_SUBUSER& MapSubUser=m_pDelegate->GetMapSubUser();
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	//////////////////////////////////////////////////////////////////////////
	MAP_POWER::iterator iterPower=MapPower.find(szUserName);
	if(iterPower!=MapPower.end())
	{
		XPower* pPower=iterPower->second;

		CString szGroup=pPower->GetUserGroup();
		time_t nCreateTime=pPower->GetCreateTime();

		CString szCreateTime=HandleCalculate::GetTimeBySecond(nCreateTime);
		AddUserListInfo(nID,szUserName,szCreateTime,szGroup);
	}
}

void XPowerManage::OnBtnClickedAlter()
{
	//更改用户，包括更改密码、权限，当前登录用户不能修改权限
	int nItem=XSetListCtrl::GetListSelectItem(&m_UserList);
	if(nItem==-1)
	{
		_M(_T("211"),_T("请选择要更改的用户！"),MB_OK);
		return;
	}

	CString szUserName=XSetListCtrl::GetColumnText(&m_UserList,nItem,1);

	XAlterUser dlg;
	m_pAlterUser=&dlg;
	dlg.SetDelegate(this);
	dlg.SetUserName(szUserName);
	dlg.DoModal();
	m_pAlterUser=nullptr;
}

void XPowerManage::CloseAlterUserDlg()
{
	if(nullptr!=m_pAlterUser)
		m_pAlterUser->OnOK();
}

void XPowerManage::AlterUser()
{
	//CString szUserName=m_pAlterUser->GetUserName();
	//CString szPassWd=m_pAlterUser->GetPassWd();
	//MAP_SELECT& MapSelect=m_pAlterUser->GetMapSelect();
	////根据选择计算权限
	//int nPermission=0;
	//for(auto iter=MapSelect.begin();iter!=MapSelect.end();++iter)
	//{
	//	XPowerSelectInfo* pInfo=iter->second;
	//	int nIndex=pInfo->GetPowerIndex();
	//	nPermission|=(1<<nIndex);
	//}

	//MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	//XPower* pPower=NULL;
	//MAP_POWER::iterator iter=MapPower.find(szUserName);
	//if(iter!=MapPower.end())
	//{
	//	pPower=iter->second;
	//}

	//pPower->SetPassWd(szPassWd);
	//pPower->SetManagePermission(nPermission);


	DWORD dwTime=GetTickCount();
	if((long)dwTime-(long)m_dwTime<3000)
	{
		m_dwTime=GetTickCount();
		return;
	}

	CString szUserName=m_pAlterUser->GetUserName();
	CString szPassWd=m_pAlterUser->GetPassWd();

	//根据选择计算权限
	int nPermission=0;
	for(auto iter=m_MapSelect.begin();iter!=m_MapSelect.end();++iter)
	{
		XPowerSelectInfo* pInfo=iter->second;
		int nIndex=pInfo->GetPowerIndex();
		nPermission|=(1<<nIndex);
	}
	//计算子权限
	VEC_PRIVILEGE VecCtrl;
	MAP_CTRLPRIVILEGE MapPrivilege;

	SetPrivilegeBySelect(m_VecCtrlSel,MapPrivilege,2);
	SetPrivilegeBySelect(m_VecViewSel,MapPrivilege,1);
	SetPrivilegeBySelect(m_VecMonCtrlSel,MapPrivilege,3);

	WritePrivilege(VecCtrl,MapPrivilege);

	//取消预览权限
	//VEC_PRIVILEGE VecView;
	//WritePrivilege(VecView,m_VecViewSel);

	VEC_PRIVILEGE VecLogin;
	WritePrivilege(VecLogin,m_VecLoginSel);

	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	XPower* pPower=NULL;
	MAP_POWER::iterator iter=MapPower.find(szUserName);
	if(iter!=MapPower.end())
	{
		pPower=iter->second;
	}

	if(NULL==pPower)
		return;

	XPower *pPowerNew=new XPower;
	pPowerNew->SetUserName(szUserName);
	pPowerNew->SetPassWd(szPassWd);
	pPowerNew->SetManagePermission(nPermission);
	pPowerNew->GetPrivilegeCtrl().SetType(86);
	pPowerNew->GetPrivilegeLogin().SetType(86);
	pPowerNew->GetPrivilegeView().SetType(86);
	pPowerNew->GetPrivilegeCtrl().SetVecPrivilege(VecCtrl);
	pPowerNew->GetPrivilegeLogin().SetVecPrivilege(VecLogin);
	//pPower->GetPrivilegeView().SetVecPrivilege(VecView);
	XSendDataManage::GetInstance()->AddSendDataOfAlterUser(pPowerNew,szPassWd);

	delete pPowerNew;
}

void XPowerManage::UpdatePowerList(CString szName)
{
	//用户自己权限
	InitSubUserPower(szName);

	//清空选中集合
	ClearMapSelect();

	//先全部不选中
	int nCount=m_PowerList.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		XSetListCtrl::SetListCheckItemFalse(&m_PowerList,i);
	}
	//根据用户权限集合，check选中用户权限
	for(auto iter=m_MapSubUserPower.begin();iter!=m_MapSubUserPower.end();++iter)
	{
		int nItem=iter->first;
		XPowerListInfo* pListInfo=iter->second;

		CString szPower=HandlePower::GetPowerByByte(nItem,pListInfo->GetHas());

		//每次只要有相同的都选中
		int nCount=m_PowerList.GetItemCount();
		for(int i=0;i<nCount;i++)
		{
			CString szItemText=XSetListCtrl::GetColumnText(&m_PowerList,i,0);
			if(szItemText==szPower)
			{
				//添加选中集合
				MAP_SELECT::iterator iterSel=m_MapSelect.find(i);
				if(iterSel==m_MapSelect.end())
				{
					int nPowerIndex=GetPowerIndexByName(szItemText);

					XPowerSelectInfo* pInfo=new XPowerSelectInfo;
					pInfo->SetPowerName(szItemText);
					pInfo->SetPowerIndex(nPowerIndex);

					m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(i,pInfo));
				}

				XSetListCtrl::SetListCheckItem(&m_PowerList,i);
				break;
			}
		}
	}
}

void XPowerManage::OnBtnClickedCopy()
{
	//复制用户（复制权限，用户名，密码不同）
	int nItem=XSetListCtrl::GetListSelectItem(&m_UserList);

	if(nItem==-1)
	{
		_M(_T("49"),_T("请选择要复制的用户！"),MB_OK);
		return;
	}

	m_szCopyUserName=XSetListCtrl::GetColumnText(&m_UserList,nItem,1);

	XCopyUser dlg;
	dlg.SetDelegate(this);
	m_pCopyUser=&dlg;
	dlg.DoModal();
	m_pCopyUser=nullptr;
}

void XPowerManage::CloseCopyUserDlg()
{
	if(nullptr!=m_pCopyUser)
		m_pCopyUser->OnOk();
}

void XPowerManage::CopyUser()
{
	CString szUserName=m_pCopyUser->GetUserName();
	CString szPassWd=m_pCopyUser->GetPassWd();
	///////////////////////////////////
	//查找所复制用户权限
	XPower* pPower=NULL;
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	MAP_POWER::iterator iter=MapPower.find(m_szCopyUserName);
	if(iter!=MapPower.end())
	{
		pPower=iter->second;
	}

	pPower->SetUserName(szUserName);
	pPower->SetPassWd(szPassWd);

	//发送添加用户
	XSendDataManage::GetInstance()->AddSendDataOfAddUser(pPower);
}

void XPowerManage::OnBtnClickedDel()
{
	int nItem=XSetListCtrl::GetListSelectItem(&m_UserList);
	if(nItem==-1)
	{
		_M(_T("47"),_T("请选择要删除的用户！"),MB_OK);
	}
	else
	{
		CString szUserID=XSetListCtrl::GetColumnText(&m_UserList,nItem,0);
		CString szUserName=XSetListCtrl::GetColumnText(&m_UserList,nItem,1);

		//发送删除用户
		XSendDataManage::GetInstance()->AddSendDataOfDelUser(szUserName);
	}
}

void XPowerManage::DelUserFromMapAndList(CString szDelUserName)
{
	//从子用户删除
	MAP_SUBUSER& MapSubUser=m_pDelegate->GetMapSubUser();
	MAP_SUBUSER::iterator iterSubUser=MapSubUser.find(szDelUserName);
	if(iterSubUser!=MapSubUser.end())
	{
		XSubUserInfo* pInfo=iterSubUser->second;
		MapSubUser.erase(iterSubUser);
		delete pInfo;
	}
	//////////////////////////////////////////////////////////////////////////
	//从权限删除
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	MAP_POWER::iterator iterPower=MapPower.find(szDelUserName);
	if(iterPower!=MapPower.end())
	{
		XPower* pPower=iterPower->second;
		MapPower.erase(iterPower);
		delete pPower;
	}
	//////////////////////////////////////////////////////////////////////////
	//清空权限列表
	int nCount=m_PowerList.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		XSetListCtrl::SetListCheckItemFalse(&m_PowerList,i);
	}
	//清空选中集合
	ClearMapSelect();
	//////////////////////////////////////////////////////////////////////////
	//从用户表删除
	int nItem=XSetListCtrl::GetListSelectItem(&m_UserList);
	m_UserList.DeleteItem(nItem);

	//更新列表滚动条区域
	int nCount1=m_UserList.GetItemCount();
	//TRACE(_T("Count=%d\n"),nCount1);
	if(nCount1>24)
	{
		m_UserList.SetColumnWidth(0,45);
		m_UserList.SetColumnWidth(1,80);
		m_UserList.SetColumnWidth(2,64);
		m_UserList.SetColumnWidth(3,120);
	}
	else
	{
		m_UserList.SetColumnWidth(0,50);
		m_UserList.SetColumnWidth(1,90);
		m_UserList.SetColumnWidth(2,70);
		m_UserList.SetColumnWidth(3,115);
	}
}

void XPowerManage::OnNMClickUserList(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate=reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos=GetMessagePos();
	CPoint pt(dwPos);
	m_UserList.ScreenToClient(&pt);

	UINT nFlag;
	int nItem=m_UserList.HitTest(pt,&nFlag);

	CString szUserName=XSetListCtrl::GetColumnText(&m_UserList,nItem,1);
	InitSubUserPower(szUserName);
	//解析权限
	InitSubPowerByUser(szUserName);

	SetPowerListSelectByUser();
	SetSubPowerListSelectByUser();

	*pResult=0;
}

void XPowerManage::SetSubPowerListSelectByUser()
{
	m_VecCtrlSel.clear();
	m_VecViewSel.clear();
	m_VecLoginSel.clear();
	m_VecMonCtrlSel.clear();

	//根据权限选中
	//接管权限
	MAP_NODEALL& MapNodeAll=m_pDelegate->GetMapNodeAll();
	for(auto& node:MapNodeAll)
	{
		XNodeAll* pNode=node.second;
		int nNodeID=pNode->GetNodeID();
		if(pNode->GetNodeType()==TERM_IN)
		{
			if(m_MapPrivilege.find(nNodeID)!=m_MapPrivilege.end())
			{
				//找到了
				//0为没有，1预览，2接管，3独占
				XPrivilege* pPrivilege=m_MapPrivilege[nNodeID];

				CString szNodeID;
				szNodeID.Format(_T("%d"),nNodeID);
				if(pPrivilege->m_nPrivilege==1)
				{
					m_VecViewSel.push_back(szNodeID);
				}
				else if(pPrivilege->m_nPrivilege==2)
				{
					m_VecCtrlSel.push_back(szNodeID);
				}
				else if(pPrivilege->m_nPrivilege==3)
				{
					m_VecMonCtrlSel.push_back(szNodeID);
				}
				else
				{
					//0的话 不插进去
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//登录权限
	for(auto& node:MapNodeAll)
	{
		XNodeAll* pNode=node.second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			CString szItem;
			szItem.Format(_T("%d"),pNode->GetNodeID());
			if(GetNodeInVecSelect(m_VecLoginNodeID,szItem))
			{
				m_VecLoginSel.push_back(szItem);
			}
		}
	}

	InitSubPower(m_nRadioSelect);
}

void XPowerManage::SetPowerListSelectByUser()
{
	ClearMapSelect();
	int nCount=m_PowerList.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		XSetListCtrl::SetListCheckItemFalse(&m_PowerList,i);
	}

	//根据用户权限集合，check选中用户权限
	for(auto iter=m_MapSubUserPower.begin();iter!=m_MapSubUserPower.end();++iter)
	{
		int nItem=iter->first;
		XPowerListInfo* pListInfo=iter->second;
		CString szPower=HandlePower::GetPowerByByte(nItem,pListInfo->GetHas());
		//////////////////////////////////////////////////////////////////////////
		//每次只要有相同的都选中
		int nCount=m_PowerList.GetItemCount();
		for(int i=0;i<nCount;i++)
		{
			CString szItemText=XSetListCtrl::GetColumnText(&m_PowerList,i,0);
			if(szItemText==szPower)
			{
				//添加选中集合
				MAP_SELECT::iterator iterSel=m_MapSelect.find(i);
				if(iterSel==m_MapSelect.end())
				{
					int nPowerIndex=GetPowerIndexByName(szItemText);

					XPowerSelectInfo* pInfo=new XPowerSelectInfo;
					pInfo->SetPowerName(szItemText);
					pInfo->SetPowerIndex(nPowerIndex);

					m_MapSelect.insert(std::pair<int,XPowerSelectInfo*>(i,pInfo));
				}

				XSetListCtrl::SetListCheckItem(&m_PowerList,i);
				break;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//收藏列表
void XPowerManage::OnBtnClickedQueryStore()
{
	int nItem=XSetListCtrl::GetListSelectItem(&m_UserList);
	if(nItem==-1)
	{
		_M(_T("64"),_T("请选择查询的用户！"),MB_OK);
		return;
	}
	else
	{
		//m_szQueryStoreUser=XSetListCtrl::GetColumnText(&m_UserList,nItem,1);
		//XSendDataManage::GetInstance()->AddSendDataOfObtainStoreList(m_szQueryStoreUser);
		CString szUserID=XSetListCtrl::GetColumnText(&m_UserList,nItem,0);
		m_nQueryStoreUserID=_ttoi(szUserID);
		XSendDataManage::GetInstance()->AddSendDataOfObtainStoreList(m_nQueryStoreUserID);
	}
}

void XPowerManage::OnBtnClickedAddStore()
{
	//添加收藏
	if(m_nQueryStoreUserID==0)
		return;

	XAddStore dlg;
	dlg.SetDelegate(this);
	dlg.SetCurUser(m_nQueryStoreUserID);
	dlg.DoModal();
}

void XPowerManage::InitQueryUserID()
{
	m_nQueryStoreUserID=m_pDelegate->GetUserID();
	//TRACE(_T("m_nQueryStoreUserID=%d\n"),m_nQueryStoreUserID);
}

void XPowerManage::OnBtnClickedDelStore()
{
	//删除收藏
	if(m_nQueryStoreUserID==0)
		return;
	int nItem=XSetListCtrl::GetListSelectItem(&m_StoreList);
	CString szNodeID=XSetListCtrl::GetColumnText(&m_StoreList,nItem,0);
	if(_T("")==szNodeID.Trim())
		return;
	int nNodeID=_ttoi(szNodeID);
	MAP_STORE& MapStore=m_pDelegate->GetMapStore();
	if(MapStore.find(nNodeID)!=MapStore.end())
	{
		XStoreListInfo* pInfo=MapStore[nNodeID];
		if(NULL!=pInfo)
		{
			XSendDataManage::GetInstance()->AddSendDataOfDelStoreList(pInfo);
		}
	}
}

void XPowerManage::DelStoreList(int nNodeID)
{
	int nItem=XSetListCtrl::GetListSelectItem(&m_StoreList);
	m_StoreList.DeleteItem(nItem);
}
//////////////////////////////////////////////////////////////////////////
void XPowerManage::GetCurUserSubUserList(int nIndex,int nSize)
{
	//添加按钮实现分页（暂时没用）
	//用户太多的话需要分页获取(暂时不分页)
	XSendDataManage::GetInstance()->AddSendDataOfObtainUserList(nIndex,nSize);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CString XPowerManage::GetTranslationString(CString szKey,CString szDefault)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

int XPowerManage::AddListInfo(CString szInfo,CString szUserInfo)
{
	if(szUserInfo==_T(""))
	{
		//权限列表
		int nCount=0;
		nCount=m_PowerList.GetItemCount();

		if(nCount>17)
			m_PowerList.SetColumnWidth(0,217);
		else
			m_PowerList.SetColumnWidth(0,235);

		m_PowerList.InsertItem(nCount,_T(""));
		SetListInfo(nCount,szInfo);
		return nCount;
	}
	else
	{
		//登录用户信息列表
		int nCount=0;
		nCount=m_UserInfo.GetItemCount();
		m_UserInfo.InsertItem(nCount,_T(""));
		SetListInfo(nCount,szInfo,szUserInfo);
		return nCount;
	}
}

void XPowerManage::SetListInfo(int nCount,CString szInfo,CString szUserInfo)
{
	if(_T("")==szUserInfo)
	{
		m_PowerList.SetItemText(nCount,0,szInfo);
	}
	else
	{
		m_UserInfo.SetItemText(nCount,0,szInfo);
		m_UserInfo.SetItemText(nCount,1,szUserInfo);
	}
}

int XPowerManage::AddUserListInfo(int nID,CString szUserName,CString szCreateTime,CString szGroup)
{
	int nCount=m_UserList.GetItemCount();
	//去除滚动条宽度
	if(nCount>23)
	{
		m_UserList.SetColumnWidth(0,45);
		m_UserList.SetColumnWidth(1,80);
		m_UserList.SetColumnWidth(2,60);
		m_UserList.SetColumnWidth(3,120);
	}
	else
	{
		m_UserList.SetColumnWidth(0,50);
		m_UserList.SetColumnWidth(1,80);
		m_UserList.SetColumnWidth(2,75);
		m_UserList.SetColumnWidth(3,116);
	}

	m_UserList.InsertItem(nCount,_T(""));

	CString szID;
	szID.Format(_T("%d"),nID);
	SetUserListInfo(nCount,szID,szUserName,szCreateTime,szGroup);

	return nCount;
}

void XPowerManage::SetUserListInfo(int nCount,CString szID,CString szUserName,CString szCreateTime,CString szGroup)
{
	m_UserList.SetItemText(nCount,0,szID);
	m_UserList.SetItemText(nCount,1,szUserName);
	m_UserList.SetItemText(nCount,2,szGroup);
	m_UserList.SetItemText(nCount,3,szCreateTime);
}

int XPowerManage::AddStoreListInfo(int nNodeID,CString szNodeName,int nNodeType,int nNumber)
{
	int nCount=m_StoreList.GetItemCount();

	//设置去除滚动条宽度
	if(nCount>23)
	{
		//m_StoreList.SetColumnWidth(0,45);
		m_StoreList.SetColumnWidth(0,60);
		m_StoreList.SetColumnWidth(1,106);
		m_StoreList.SetColumnWidth(2,60);
	}
	else
	{
		//m_StoreList.SetColumnWidth(0,50);
		m_StoreList.SetColumnWidth(0,55);
		m_StoreList.SetColumnWidth(1,123);
		m_StoreList.SetColumnWidth(2,60);
	}

	m_StoreList.InsertItem(nCount,_T(""));

	CString szNodeID;
	szNodeID.Format(_T("%d"),nNodeID);
	SetStoreListInfo(nCount,szNodeID,szNodeName,nNodeType,nNumber);

	return nCount;
}

void XPowerManage::SetStoreListInfo(int nCount,CString szNodeID,CString szNodeName,int nNodeType,int nNumber)
{
	CString szNumber;
	szNumber.Format(_T("%d"),nNumber);

	//m_StoreList.SetItemText(nCount,0,szNumber);
	m_StoreList.SetItemText(nCount,0,szNodeID);
	m_StoreList.SetItemText(nCount,1,szNodeName);
	if(nNodeType==NODETYPE_IN)
	{
		CString szTemp=GetTranslationString(_T("62"),_T("输入"));
		m_StoreList.SetItemText(nCount,2,szTemp);
	}
	else if(nNodeType==NODETYPE_OUT)
	{
		CString szTemp=GetTranslationString(_T("63"),_T("输出"));
		m_StoreList.SetItemText(nCount,2,szTemp);
	}
}

HBRUSH XPowerManage::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hbr=CDialogEx::OnCtlColor(pDC,pWnd,nCtlColor);
	TCHAR szClassName[MAX_PATH]={0};
	::GetClassName(pWnd->m_hWnd,szClassName,sizeof(szClassName)/sizeof(TCHAR)-2);
	if(lstrcmpi(szClassName,_T("Button"))==0)
	{
		UINT uStyle=((CButton*)pWnd)->GetButtonStyle();        
		switch(uStyle)
		{
			case BS_AUTORADIOBUTTON:
				{
					int nIndex=XThemeColor::GetInstance()->GetThemeIndex();
					Color color=m_BgColor[nIndex];
					HBRUSH hbrSatic=::CreateSolidBrush(RGB(color.GetR(),color.GetG(),color.GetB()));       
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(RGB(255,255,255));             
					return hbrSatic;
				}
				break;
			default:
				break;
		}
	}  

	return hbr;
}
