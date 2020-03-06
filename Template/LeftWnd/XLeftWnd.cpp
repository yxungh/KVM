#include "stdafx.h"
#include <algorithm>
#include "XLeftWnd.h"
#include "XConstant.h"
#include "..\MainFrm.h"
#include "..\resource.h"
#include "XDelegateLeftWnd.h"
#include "XTranslationManage.h"
#include "XDragWnd.h"
#include "XNode.h"
#include "XNodeGroupInfo.h"
#include "XSendDataManage.h"
#include "XAlterGroup.h"
#include "XConstantData.h"
#include "XMessageBox.h"
#include "XAlterName.h"
#include "XAddGroup.h"
#include "XSplitInput.h"
#include "XSplitInputResult.h"
#include "XJsonManage.h"



XLeftWnd* XLeftWnd::m_pLeftWnd=NULL;
IMPLEMENT_DYNAMIC(XLeftWnd,CDockablePane)

XLeftWnd::XLeftWnd():
	m_pDelegate(NULL),
	m_pDragWnd(NULL),
	m_szTitle(_T("")),
	m_hRootItem(NULL),
	m_hChildItem(NULL),
	m_hItemInput(NULL),
	m_hItemOutput(NULL)
{

}

XLeftWnd::~XLeftWnd()
{
	RELEASE(m_pDragWnd);
	ClearVecDrag();
	ClearVecDel();
	ClearSplitInput();
}

BEGIN_MESSAGE_MAP(XLeftWnd,CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK,ID_LEFTTREE,OnNMRClickTree)
	ON_NOTIFY(NM_DBLCLK,ID_LEFTTREE,OnDblclkTree)
	ON_NOTIFY(TVN_ENDLABELEDIT,ID_LEFTTREE,OnTvnEndlabeledit)

	ON_COMMAND(ID_MENU_ALTERGROUP,OnAlterGroup)
	ON_COMMAND(ID_MENU_DELGROUP,OnDelGroup)
	ON_COMMAND(ID_MENU_ALTERNODE,OnAlterNode)
	ON_COMMAND(ID_MENU_REMOVENODE,OnRemoveNodeInGroup)
	ON_COMMAND(ID_MENU_ADDGROUP,OnAddGroup)
	ON_COMMAND(ID_MENU_MAINSECOND,OnAddMainAndSecond)
	

END_MESSAGE_MAP()


XLeftWnd* XLeftWnd::GetInstance()
{
	if(NULL==m_pLeftWnd)
		m_pLeftWnd=new XLeftWnd;

	return m_pLeftWnd;
}

void XLeftWnd::Release()
{
	if(NULL!=m_pLeftWnd)
	{
		delete m_pLeftWnd;
		m_pLeftWnd=NULL;
	}
}

void XLeftWnd::ClearVecDrag()
{
	m_VecDrag.clear();
}

void XLeftWnd::ClearVecDel()
{
	m_VecDel.clear();
}

void XLeftWnd::ClearSplitInput()
{
	for(auto& pInput:m_VecSplitInput)
	{
		delete pInput;
	}
	m_VecSplitInput.clear();
}

int XLeftWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CDockablePane::OnCreate(lpCreateStruct)==-1)
		return -1;

	if(!InitImageList())
		return -1;

	if(!InitTreeCtrl())
		return -1;

	return 0;
}

void XLeftWnd::OnSize(UINT nType,int cx,int cy)
{
	CDockablePane::OnSize(nType,cx,cy);
	AdjustLayout();
}

void XLeftWnd::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(rect);

	CBrush bruDB;
	bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	dc.FillRect(&rect,&bruDB);

	CRect rectTreeCtrl;
	m_TreeCtrl.GetWindowRect(rectTreeCtrl);
	ScreenToClient(rectTreeCtrl);
	rectTreeCtrl.InflateRect(1,1);
	dc.Draw3dRect(rectTreeCtrl,::GetSysColor(COLOR_3DFACE),::GetSysColor(COLOR_3DFACE));
}

void XLeftWnd::AdjustLayout()
{
	if(NULL==GetSafeHwnd())
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	m_TreeCtrl.SetWindowPos(NULL,rectClient.left,rectClient.top,rectClient.Width(),rectClient.Height(),SWP_NOACTIVATE|SWP_NOZORDER);
}

void XLeftWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_TreeCtrl.SetFocus();
}

void XLeftWnd::OnContextMenu(CWnd* /* pWnd */,CPoint point)
{
	return;
}

void XLeftWnd::Init()
{
	CreatePane();
}

void XLeftWnd::CreatePane()
{
	CWnd* pWnd=m_pDelegate->GetCWND();
	CMainFrame* pMainFrame=(CMainFrame*)pWnd;

	CString szTitle=_C(_T("68"),_T("用户"));

	if(!Create(szTitle,pMainFrame,CRect(0,0,200,100),TRUE,
	   ID_LEFTPANE,WS_CHILD|WS_VISIBLE|CBRS_LEFT|CBRS_FLOAT_MULTI,
	   AFX_CBRS_REGULAR_TABS,AFX_CBRS_RESIZE))
	{
		return;
	}

	EnableDocking(CBRS_ALIGN_LEFT);
	pMainFrame->DockPane(this);

	ShowPane(TRUE,TRUE,TRUE);
}

BOOL XLeftWnd::InitTreeCtrl()
{
	m_TreeCtrl.SetLeftWnd(this);

	if(m_TreeCtrl.Create(WS_CHILD|WS_VISIBLE|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS|TVS_EDITLABELS,CRect(0,0,0,0),this,ID_LEFTTREE))
	{
		m_TreeCtrl.SetImageList(&m_ImageList,TVSIL_NORMAL);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL XLeftWnd::InitImageList()
{
	if(!m_ImageList.Create(20,20,ILC_COLOR32|ILC_MASK,0,1))
		return FALSE;

	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_USER));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_INPUT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_OUTPUT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUP));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NODE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_ANNODE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_MGROUP));

	return TRUE;
}

void XLeftWnd::ReloadInterface()
{
	CString szTemp;

	if(m_szTitle==_T("用户")||m_szTitle==_T("User")||m_szTitle==_T("用戶"))
	{
		szTemp=_C(_T("68"),_T("用户"));
		SetWindowText(szTemp);
	}
	else if(m_szTitle==_T("节点")||m_szTitle==_T("Node")||m_szTitle==_T("節點"))
	{
		szTemp=_C(_T("95"),_T("节点"));
		SetWindowText(szTemp);
	}
}

void XLeftWnd::OnTvnEndlabeledit(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo=reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);

	CString szNewText=pTVDispInfo->item.pszText;
	szNewText.Trim();
	if(szNewText.IsEmpty())
	{
		*pResult=0;
		return;
	}

	CString szGroupName=XConstantData::GetInstance()->GetGroupName();
	BOOL bMainSecond=FALSE;

	MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapNodeGroupMainSec=m_pDelegate->GetMapNodeGroupMainSec();

	if(MapNodeGroup.find(szGroupName)!=MapNodeGroup.end())
	{
		XNodeGroupInfo* pInfo=MapNodeGroup[szGroupName];
		bMainSecond=pInfo->GetMainSecond();
	}

	if(MapNodeGroupMainSec.find(szGroupName)!=MapNodeGroupMainSec.end())
	{
		XNodeGroupInfo* pInfo=MapNodeGroupMainSec[szGroupName];
		bMainSecond=pInfo->GetMainSecond();
	}

	int nData=XConstantData::GetInstance()->GetType();
	
	switch(nData)
	{
		case ITEMDATA_NODEGROUPIN:
		case ITEMDATA_NODEGROUPOUT:
			{
				//先判断重名
				if(DecidedGroupNameExist(szNewText))
				{
					*pResult=0;
					_M(_T("161"),_T("名称已存在！"),MB_OK);
					return;
				}

				int nGroupID=XConstantData::GetInstance()->GetGroupID();
				//更改名称
				XNodeGroupInfo nodeGroupInfo;
				nodeGroupInfo.SetGroupID(nGroupID);
				nodeGroupInfo.SetGroupName(szNewText);

				if(bMainSecond)
				{
					//更改主副屏组名称
					XSendDataManage::GetInstance()->AddSendDataOfUpdataMasterNodeGroupName(nodeGroupInfo);
				}
				else
				{
					//普通组名称
					XSendDataManage::GetInstance()->AddSendDataOfUpdataNodeGroupName(nodeGroupInfo);
				}	
			}
			break;
		case ITEMDATA_NODE:
			{
				if(DecidedNodeNameExist(szNewText))
				{
					*pResult=0;
					_M(_T("161"),_T("名称已存在！"),MB_OK);
					return;
				}

				int nNodeID=XConstantData::GetInstance()->GetNodeID();
				XSendDataManage::GetInstance()->AddSendDataOfAlterNodeName(nNodeID,szNewText);
			}
			break;
		default:
			break;
	}

	//返回1 会自动更改名称，这里要按返回值手动更改
	//*pResult=1;	
}

BOOL XLeftWnd::DecidedGroupNameExist(CString szName)
{
	MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
	for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
	{
		XNodeGroupInfo* pInfo=iter->second;
		if(pInfo->GetGroupName()==szName)
			return TRUE;
	}
	return FALSE;
}

BOOL XLeftWnd::DecidedNodeNameExist(CString szName)
{
	MAP_NODE& MapNode=GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeName()==szName)
			return TRUE;
	}
	return FALSE;
}

void XLeftWnd::OnNMRClickTree(NMHDR *pNMHDR,LRESULT *pResult)
{
	//右键
	CPoint point;
	GetCursorPos(&point);

	CPoint tempPoint=point;
	m_TreeCtrl.ScreenToClient(&tempPoint);

	UINT flags;
	HTREEITEM  hItem=m_TreeCtrl.HitTest(tempPoint,&flags);
	if(hItem==NULL)
		return;

	m_TreeCtrl.SelectItem(hItem);
	DWORD dwData=m_TreeCtrl.GetItemData(hItem);

	XConstantData::GetInstance()->SetType(dwData);
	switch(dwData)
	{
		case ITEMDATA_NODEGROUPIN:
		case ITEMDATA_NODEGROUPOUT:
			{
				//保存组ID
				CString szGroupName=m_TreeCtrl.GetItemText(hItem);
				int nGroupID=GetGroupIDByName(szGroupName);
				XConstantData::GetInstance()->SetGroupID(nGroupID);
				XConstantData::GetInstance()->SetGroupName(szGroupName);

				ShowGroupMenu();
			}
			break;
		case ITEMDATA_NODE:
			{
				CString szNodeName=m_TreeCtrl.GetItemText(hItem);
				XNode* pNode=GetNodeByName(szNodeName);
				if(NULL==pNode)
					return;

				XConstantData::GetInstance()->SetNodeID(pNode->GetNodeID());
				if(pNode->GetGroup()!=0||pNode->GetMaster()!=0)
				{
					HTREEITEM hParent=m_TreeCtrl.GetParentItem(hItem);
					if(NULL==hParent)
						return;

					CString szItemText=m_TreeCtrl.GetItemText(hParent);
					XConstantData::GetInstance()->SetGroupName(szItemText);

					ShowNodeMenuInGroup();
				}
				else if(pNode->GetGroup()==0&&pNode->GetMaster()==0)
				{
					ShowNodeMenuNotInGroup();
				}
			}
			break;
		case ITEMDATA_NODEIN:
		case ITEMDATA_NODEOUT:
			{
				//显示菜单，手动创建空组
				ShowMenuOfAddGroup(dwData);
			}
			break;
		default:
			break;
	}
}

void XLeftWnd::ShowGroupMenu()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,ID_MENU_ALTERGROUP,_C(_T("162"),_T("修改")));
	menu.AppendMenu(MF_STRING,ID_MENU_DELGROUP,_C(_T("163"),_T("删除")));
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	menu.DestroyMenu();
}

void XLeftWnd::ShowNodeMenuInGroup()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,ID_MENU_ALTERNODE,_C(_T("162"),_T("修改")));
	menu.AppendMenu(MF_STRING,ID_MENU_REMOVENODE,_C(_T("164"),_T("移除")));
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	menu.DestroyMenu();
}

void XLeftWnd::ShowNodeMenuNotInGroup()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,ID_MENU_ALTERNODE,_C(_T("162"),_T("修改")));
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	menu.DestroyMenu();
}

void XLeftWnd::ShowMenuOfAddGroup(DWORD& dData)
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.CreatePopupMenu();

	switch(dData)
	{
		case ITEMDATA_NODEIN:
			{
				menu.AppendMenu(MF_STRING,ID_MENU_ADDGROUP,_C(_T("165"),_T("创建组")));
				menu.AppendMenu(MF_STRING,ID_MENU_MAINSECOND,_C(_T("219"),_T("主副屏")));
			}
			break;
		case ITEMDATA_NODEOUT:
			{
				menu.AppendMenu(MF_STRING,ID_MENU_ADDGROUP,_C(_T("165"),_T("创建组")));
			}
			break;
		default:
			break;
	}

	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	menu.DestroyMenu();
}

void XLeftWnd::OnAlterGroup()
{
	//弹出对话框更改
	//XAlterGroup dlg;
	//if(IDOK==dlg.DoModal())
	//{
	//	CString szGroupName=dlg.GetGroupName();
	//	int nGroupID=XConstantData::GetInstance()->GetGroupID();
	//	//更改名称
	//	XNodeGroupInfo nodeGroupInfo;

	//	nodeGroupInfo.SetGroupID(nGroupID);
	//	nodeGroupInfo.SetGroupName(szGroupName);
	//	XSendDataManage::GetInstance()->AddSendDataOfUpdataNodeGroupName(nodeGroupInfo);
	//}
	//在树中直接更改
	XNodeGroupInfo* pInfo=NULL;
	CString szGroupName=XConstantData::GetInstance()->GetGroupName();
	MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapNodeGroupMainSec=m_pDelegate->GetMapNodeGroupMainSec();

	MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szGroupName);
	if(iter!=MapNodeGroup.end())
	{
		pInfo=iter->second;
	}

	if(MapNodeGroupMainSec.find(szGroupName)!=MapNodeGroupMainSec.end())
	{
		pInfo=MapNodeGroupMainSec[szGroupName];
	}

	if(NULL==pInfo)
		return;

	HTREEITEM hItem=pInfo->GetGroupItem();
	if(NULL!=hItem)
		CEdit* pEdit=m_TreeCtrl.EditLabel(hItem);
}

void XLeftWnd::OnDelGroup()
{
	if(IDYES==_M(_T("109"),_T("是否删除组？"),MB_YESNO))
	{
		DragDelGroup(XConstantData::GetInstance()->GetGroupName());
	}
}

void XLeftWnd::DragDelGroup(CString szGroupName)
{
	MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapNodeGroupMainSec=GetMapNodeGroupMainSec();

	XNodeGroupInfo* pInfo=NULL;
	if(MapNodeGroup.find(szGroupName)!=MapNodeGroup.end())
	{
		pInfo=MapNodeGroup[szGroupName];
	}

	if(MapNodeGroupMainSec.find(szGroupName)!=MapNodeGroupMainSec.end())
	{
		pInfo=MapNodeGroupMainSec[szGroupName];
	}

	if(NULL==pInfo)
		return;

	XNodeGroupInfo nodeGroupInfo;
	nodeGroupInfo.SetGroupName(pInfo->GetGroupName());
	nodeGroupInfo.SetGroupID(pInfo->GetGroupID());
	if(pInfo->GetMainSecond())
	{
		XSendDataManage::GetInstance()->AddSendDataOfDelNodeGroupMainSecond(nodeGroupInfo);
	}
	else
	{
		XSendDataManage::GetInstance()->AddSendDataOfDelNodeGroup(nodeGroupInfo);
	}
}

void XLeftWnd::OnAlterNode()
{
	//更改节点名称
	//XAlterName dlg;
	//if(IDOK==dlg.DoModal())
	//{
	//	CString szName=dlg.GetNodeName();
	//	int nNodeID=XConstantData::GetInstance()->GetNodeID();

	//	XSendDataManage::GetInstance()->AddSendDataOfAlterNodeName(nNodeID,szName);
	//}
	XNode* pNode=NULL;
	int nNodeID=XConstantData::GetInstance()->GetNodeID();
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	auto iter=MapNode.find(nNodeID);
	if(iter!=MapNode.end())
	{
		pNode=iter->second;
	}
	if(!pNode)
		return;

	HTREEITEM hItem=pNode->GetTreeItem();
	if(NULL!=hItem)
		CEdit* pEdit=m_TreeCtrl.EditLabel(hItem);
}

void XLeftWnd::OnRemoveNodeInGroup()
{
	//从组里移除
	//思路：先更新组排列，成功后 将删除的节点的组更改成0，执行成功后从树中删除
	CString szGroupName=XConstantData::GetInstance()->GetGroupName();
	int nNodeID=XConstantData::GetInstance()->GetNodeID();

	XNodeGroupInfo* pInfo=NULL;
	MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapNodeGroupMainSec=m_pDelegate->GetMapNodeGroupMainSec();

	auto iter=MapNodeGroup.find(szGroupName);
	if(iter!=MapNodeGroup.end())
	{
		pInfo=iter->second;
	}

	if(MapNodeGroupMainSec.find(szGroupName)!=MapNodeGroupMainSec.end())
	{
		pInfo=MapNodeGroupMainSec[szGroupName];
	}

	if(NULL==pInfo)
		return;

	VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
	//判断在不在集合中
	if(DecidedNodeInGroup(VecArrage,nNodeID))
	{
		//在组中
		//保存要移除的节点
		ClearVecDel();
		m_VecDel.push_back(nNodeID);

		//先更新组信息
		m_pDelegate->UpdateGroupArrageByRemoveNode(szGroupName,nNodeID);
	}
	else
	{
		//直接移除
		if(pInfo->GetMainSecond())
		{
			int nMark=UPDATAMAKE_MASTER;
			XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(nNodeID,0,nMark);
		}
		else
		{
			int nMark=UPDATAMAKE_GROUP;
			XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(nNodeID,0,nMark);
		}
	}
}

void XLeftWnd::OnAddGroup()
{
	XAddGroup dlg;
	dlg.SetMainSec(FALSE);
	dlg.SetTitle(_C(_T("165"),_T("创建组")));
	if(IDOK==dlg.DoModal())
	{
		CString szGroupName=dlg.GetGroupName();

		//利用拖拽方式创建组 先清除拖拽
		ClearVecDrag();

		int nGroupType=0;
		if(XConstantData::GetInstance()->GetType()==ITEMDATA_NODEIN)
			nGroupType=1;
		else if(XConstantData::GetInstance()->GetType()==ITEMDATA_NODEOUT)
			nGroupType=3;

		int nCreatorID=m_pDelegate->GetCurUserID();

		XNodeGroupInfo nodeGroupInfo;
		nodeGroupInfo.SetGroupName(szGroupName);
		nodeGroupInfo.SetType(nGroupType);
		nodeGroupInfo.SetCreatorID(nCreatorID);
		nodeGroupInfo.SetCreateMode(CREATEMODE_DRAG);//利用拖拽添加组方式

		XSendDataManage::GetInstance()->AddSendDataOfAddSeatArrage(nodeGroupInfo);
	}
}

void XLeftWnd::OnAddMainAndSecond()
{
	XAddGroup dlg;
	dlg.SetMainSec(TRUE);
	dlg.SetTitle(_C(_T("219"),_T("主副屏")));
	if(IDOK==dlg.DoModal())
	{
		CString szGroupName=dlg.GetGroupName();

		//int nCreatorID=m_pDelegate->GetCurUserID();

		XNodeGroupInfo nodeGroupInfo;
		nodeGroupInfo.SetGroupName(szGroupName);
		//nodeGroupInfo.SetCreatorID(nCreatorID);

		XSendDataManage::GetInstance()->AddSendDataOfMainAndSecond(nodeGroupInfo);
	}
}

BOOL XLeftWnd::DecidedNodeInGroup(VEC_ARRAGE& VecArrage,int nNodeID)
{
	for(auto iter=VecArrage.begin();iter!=VecArrage.end();++iter)
	{
		std::vector<int> VecNode=*iter;
		for(auto iter=VecNode.begin();iter!=VecNode.end();++iter)
		{
			int nTempNodeID=*iter;
			if(nTempNodeID==nNodeID)
				return TRUE;
		}
	}
	return FALSE;
}

int XLeftWnd::GetGroupIDByName(CString szGroupName)
{
	MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapNodeGroupMainSec=GetMapNodeGroupMainSec();

	if(MapNodeGroup.find(szGroupName)!=MapNodeGroup.end())
	{
		XNodeGroupInfo* pInfo=MapNodeGroup[szGroupName];
		return pInfo->GetGroupID();
	}

	if(MapNodeGroupMainSec.find(szGroupName)!=MapNodeGroupMainSec.end())
	{
		XNodeGroupInfo* pInfo=MapNodeGroupMainSec[szGroupName];
		return pInfo->GetGroupID();
	}

	return 0;
}

void XLeftWnd::OnDblclkTree(NMHDR *pNMHDR,LRESULT *pResult)
{
	*pResult=0;

}

void XLeftWnd::ShowGroupSeatArrage(CString szGroup)
{
	m_pDelegate->ShowGroupSeatArrage(szGroup);
}

void XLeftWnd::InitTreeListItemOfSplit()
{
	//切换左侧树 拼接
	m_szTitle=_C(_T("95"),_T("节点"));
	SetWindowText(m_szTitle);
	m_TreeCtrl.DeleteAllItems();
	//////////////////////////////////////////////////////////////////////////
	//只有输入
	AddRootItem(_T("Text1"),(DWORD_PTR)ITEMDATA_SPLITNODE);
	AddRootItem(_T("Text2"),(DWORD_PTR)ITEMDATA_SPLITNODE);


	//输入
	//m_hItemInput=AddRootItem(_C(_T("62"),_T("输入")),(DWORD_PTR)ITEMDATA_SPLITNODEIN);
	//SetItemRoot(m_hItemInput);

	//HTREEITEM hItem=NULL;
	//hItem=AddChildItem(_T("Text"),ITEMDATA_SPLITNODE);

	//////////////////////////////////////////////////////////////////////////
	////先没有组
	//MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	//if(MapNode.size()!=0)
	//{
	//	//输入
	//	m_hItemInput=AddRootItem(_C(_T("62"),_T("输入")),(DWORD_PTR)ITEMDATA_SPLITNODEIN);
	//	SetItemRoot(m_hItemInput);

	//	for(auto& map:MapNode)
	//	{
	//		XNode* pNode=map.second;
	//		if(pNode->GetNodeType()==TERM_IN)
	//		{
	//			CString szNodeName=pNode->GetNodeName();

	//			HTREEITEM hItem=NULL;
	//			hItem=AddChildItem(szNodeName,ITEMDATA_SPLITNODE);
	//		}
	//	}
	//	m_TreeCtrl.Expand(m_hItemInput,TVE_EXPAND);
	//}
}

void XLeftWnd::InitTreeListItemOfMatrix()
{
	m_szTitle=_C(_T("95"),_T("节点"));
	SetWindowText(m_szTitle);
	m_TreeCtrl.DeleteAllItems();

	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	if(MapNode.size()!=0)
	{
		//输入
		m_hItemInput=AddRootItem(_C(_T("62"),_T("输入")),(DWORD_PTR)ITEMDATA_MATRIXNODEIN);
		SetItemRoot(m_hItemInput);

		for(auto& map:MapNode)
		{
			XNode* pNode=map.second;
			if(pNode->GetNodeType()==TERM_IN)
			{
				CString szNodeName=pNode->GetNodeName();

				HTREEITEM hItem=NULL;
				hItem=AddChildItem(szNodeName,ITEMDATA_MATRIXNODE);
			}
		}
		m_TreeCtrl.Expand(m_hItemInput,TVE_EXPAND);
	}
}

void XLeftWnd::InitTreeListItemOfUser()
{
	m_szTitle=_C(_T("68"),_T("用户"));
	SetWindowText(m_szTitle);

	m_TreeCtrl.DeleteAllItems();
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	for(auto iter=MapPower.begin();iter!=MapPower.end();++iter)
	{
		CString szUserName=iter->first;

		HTREEITEM item;
		item=m_TreeCtrl.InsertItem(szUserName);
		m_TreeCtrl.SetItemData(item,(DWORD_PTR)ITEMDATA_USER);
		m_TreeCtrl.SetItemImage(item,0,0);
	}
}

void XLeftWnd::InitTreeListItemOfNode()
{
	m_szTitle=_C(_T("95"),_T("节点"));
	SetWindowText(m_szTitle);
	m_TreeCtrl.DeleteAllItems();

	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	MAP_NODEMAINSEC& MapNodeMainSec=m_pDelegate->GetMapNodeMainSec();
	MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapNodeGroupMainSec=m_pDelegate->GetMapNodeGroupMainSec();

	if(MapNode.size()!=0)
	{
		//输入
		m_hItemInput=AddRootItem(_C(_T("62"),_T("输入")),(DWORD_PTR)ITEMDATA_NODEIN);
		SetItemRoot(m_hItemInput);

		//主副屏
		for(auto map:MapNodeGroupMainSec)
		{
			XNodeGroupInfo* pInfo=map.second;
			int nGroupID=pInfo->GetGroupID();
			CString szGroupName=pInfo->GetGroupName();
			HTREEITEM hItem=NULL;
			hItem=AddChildItem(szGroupName,ITEMDATA_NODEGROUPIN,ITEMDATA_NODEGROUPIN_M);
			pInfo->SetGroupItem(hItem);
			//如果主副屏不为0，则找到主副屏集合中的节点名称插入组中，组为0的继续插入到结尾
			for(auto& map:MapNode)
			{
				XNode* pNode=map.second;
				//找到主副屏不为0，插到主副屏中
				if(pNode->GetMaster()==nGroupID)
				{
					if(MapNodeMainSec.find(pNode->GetNodeID())!=MapNodeMainSec.end())
					{
						HTREEITEM hItemNode=AddSubItem(pNode->GetNodeName());
						MapNodeMainSec[pNode->GetNodeID()]=hItemNode;

						//if(!pNode->GetDrag())
						//	m_TreeCtrl.SetItemImage(hItemNode,5,5);
					}
				}
			}
			m_TreeCtrl.Expand(hItem,TVE_EXPAND);
		}
		//////////////////////////////////////////////////////////////////////////
		//普通组
		for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
		{
			XNodeGroupInfo* pInfo=iter->second;
			//if(pInfo->GetOnLine())
			{
				int nGroupID=pInfo->GetGroupID();
				int nType=pInfo->GetType();
				if(nType==1)
				{
					CString szGroupName=pInfo->GetGroupName();
					HTREEITEM hItem=NULL;

					hItem=AddChildItem(szGroupName,ITEMDATA_NODEGROUPIN,ITEMDATA_NODEGROUPIN_G);
					pInfo->SetGroupItem(hItem);

					for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
					{
						XNode* pNode=iter->second;
						if(pNode->GetGroup()==nGroupID)
						{
							CString szNode=pNode->GetNodeName();
							HTREEITEM hItemNode=AddSubItem(szNode);
							pNode->SetTreeItem(hItemNode);

							if(!pNode->GetDrag())
								m_TreeCtrl.SetItemImage(hItemNode,5,5);
						}
					}
					m_TreeCtrl.Expand(hItem,TVE_EXPAND);
				}
			}
		}
		//不在组里的节点
		//节点全部显示在下面（不管在不在组里）
		for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
		{
			XNode* pNode=iter->second;
			if(pNode->GetNodeType()==TERM_IN)
			{
				if(pNode->GetGroup()==0)
				{
					CString szNodeName=pNode->GetNodeName();

					SetItemRoot(m_hItemInput);
					HTREEITEM hItem=AddChildItem(szNodeName,ITEMDATA_NODE);
					pNode->SetTreeItem(hItem);
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//输出
		m_hItemOutput=AddRootItem(_C(_T("63"),_T("输出")),(DWORD_PTR)ITEMDATA_NODEOUT);
		SetItemRoot(m_hItemOutput);

		for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
		{
			XNodeGroupInfo* pInfo=iter->second;
			//if(pInfo->GetOnLine())
			{
				int nGroupID=pInfo->GetGroupID();
				int nType=pInfo->GetType();
				if(nType==3)
				{
					CString szGroupName=pInfo->GetGroupName();
					HTREEITEM hItem=AddChildItem(szGroupName,ITEMDATA_NODEGROUPOUT);
					pInfo->SetGroupItem(hItem);

					for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
					{
						XNode* pNode=iter->second;
						if(pNode->GetGroup()==nGroupID)
						{
							CString szNode=pNode->GetNodeName();
							HTREEITEM hItemNode=AddSubItem(szNode);
							pNode->SetTreeItem(hItemNode);

							if(!pNode->GetDrag())
								m_TreeCtrl.SetItemImage(hItemNode,5,5);
						}
					}
					m_TreeCtrl.Expand(hItem,TVE_EXPAND);
				}
			}
		}

		//不在组里的节点
		for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
		{
			XNode* pNode=iter->second;
			if(pNode->GetNodeType()==TERM_OUT)
			{
				if(pNode->GetGroup()==0)
				{
					CString szNodeName=pNode->GetNodeName();

					SetItemRoot(m_hItemOutput);
					HTREEITEM hItem=AddChildItem(szNodeName,ITEMDATA_NODE);
					pNode->SetTreeItem(hItem);
				}
			}
		}
	}

	if(m_hItemInput!=NULL&&m_hItemOutput!=NULL)
	{
		m_TreeCtrl.Expand(m_hItemInput,TVE_EXPAND);
		m_TreeCtrl.Expand(m_hItemOutput,TVE_EXPAND);
	}
}

void XLeftWnd::InsertItemToTree(CString szUserName)
{
	HTREEITEM item;
	item=m_TreeCtrl.InsertItem(szUserName);
	m_TreeCtrl.SetItemData(item,(DWORD_PTR)ITEMDATA_USER);
}

void XLeftWnd::DeleteItemFromTree(CString szUserName)
{
	HTREEITEM item=m_TreeCtrl.GetRootItem();

	HTREEITEM itemDel=FindItem(item,szUserName);
	if(itemDel!=NULL)
		m_TreeCtrl.DeleteItem(itemDel);
}

void XLeftWnd::DeleteNodeGroupFromTree(HTREEITEM item)
{
	if(NULL!=item)
		m_TreeCtrl.DeleteItem(item);
}

void XLeftWnd::ClearTree()
{
	m_TreeCtrl.DeleteAllItems();
}

void XLeftWnd::SetPropertyValue(CString szUserName)
{
	m_pDelegate->SetPropertyValue(szUserName);
}

void XLeftWnd::SetNodeSelected(CString szNodeName)
{
	m_pDelegate->SetNodeSelected(szNodeName);
}

HTREEITEM XLeftWnd::FindItem(HTREEITEM item,CString szItemText)
{
	HTREEITEM hfind;

	if(item==NULL)
		return NULL;

	while(item!=NULL)
	{
		if(m_TreeCtrl.GetItemText(item)==szItemText)
			return item;

		if(m_TreeCtrl.ItemHasChildren(item))
		{
			item=m_TreeCtrl.GetChildItem(item);

			hfind=FindItem(item,szItemText);
			if(hfind)
				return hfind;
			else
				item=m_TreeCtrl.GetNextSiblingItem(m_TreeCtrl.GetParentItem(item));
		}
		else
		{
			item=m_TreeCtrl.GetNextSiblingItem(item);
		}
	}

	return item;
}

MAP_POWER& XLeftWnd::GetMapPower()
{
	return m_pDelegate->GetMapPower();
}

MAP_NODE& XLeftWnd::GetMapNode()
{
	return m_pDelegate->GetMapNode();
}

MAP_NODEGROUP& XLeftWnd::GetMapNodeGroup()
{
	return m_pDelegate->GetMapNodeGroup();
}

MAP_GROUPMAINSEC& XLeftWnd::GetMapNodeGroupMainSec()
{
	return m_pDelegate->GetMapNodeGroupMainSec();
}

VEC_DRAG& XLeftWnd::GetVecDrag()
{
	return m_VecDrag;
}

MAP_DRAG& XLeftWnd::GetMapDrag()
{
	return m_MapDrag;
}

VEC_DEL& XLeftWnd::GetVecDel()
{
	return m_VecDel;
}

XDragWnd* XLeftWnd::CreateDragWnd()
{
	if(m_pDragWnd==NULL)
	{
		CreateWnd();
	}

	m_pDragWnd->Show();

	return m_pDragWnd;
}

void XLeftWnd::CreateWnd()
{
	int nWidth=80;
	int nHeight=30;

	CRect rect(CPoint(0,0),CSize(nWidth,nHeight));

	m_pDragWnd=new XDragWnd;
	m_pDragWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pDelegate->GetCWND()->GetDesktopWindow(),0);
	m_pDragWnd->SetLeftWnd(this);
	m_pDragWnd->ShowWindow(SW_HIDE);
	m_pDragWnd->UpdateWindow();
}

void XLeftWnd::DragEnd(CPoint& point,CRect& rect)
{
	m_pDelegate->DragEnd(point,rect);
}

void XLeftWnd::SetNodeDrag(int nNodeID,BOOL b)
{
	XNode* pNode=GetNodeByID(nNodeID);
	if(NULL!=pNode)
		pNode->SetDrag(b);
}

void XLeftWnd::SetNodeColor(int nNodeID,BOOL b)
{
	XNode* pNode=GetNodeByID(nNodeID);
	if(NULL!=pNode)
	{
		HTREEITEM item=pNode->GetTreeItem();
		if(NULL!=item)
		{
			if(!b)
				m_TreeCtrl.SetItemImage(item,5,5);
			else
				m_TreeCtrl.SetItemImage(item,4,4);
		}
	}
}

XNode* XLeftWnd::GetNodeByID(int nNodeID)
{
	MAP_NODE& MapNode=GetMapNode();
	MAP_NODE::iterator iter=MapNode.find(nNodeID);
	if(iter!=MapNode.end())
	{
		return iter->second;
	}

	return NULL;
}

XNode* XLeftWnd::GetNodeByName(CString szName)
{
	MAP_NODE& MapNode=GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(szName==pNode->GetNodeName())
			return pNode;
	}
	return NULL;
}

XNodeGroupInfo* XLeftWnd::GetNodeGroupByName(CString szName)
{
	MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapNodeGroupMainSec=GetMapNodeGroupMainSec();
	XNodeGroupInfo* pInfo=NULL;

	MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szName);
	if(iter!=MapNodeGroup.end())
	{
		pInfo=iter->second;
	}
		
	if(MapNodeGroupMainSec.find(szName)!=MapNodeGroupMainSec.end())
	{
		pInfo=MapNodeGroupMainSec[szName];
	}

	return pInfo;
}

void XLeftWnd::UpdateGroupNameAfterChange(HTREEITEM item,CString szName)
{
	if(item!=NULL)
	{
		CString szGroupName=m_TreeCtrl.GetItemText(item);
		m_pDelegate->UpdateGroupNameAfterChange(szGroupName,szName);
	}
}

void XLeftWnd::ChangeGroupItemText(HTREEITEM item,CString szName)
{
	if(item!=NULL)
	{
		m_TreeCtrl.SetItemText(item,szName);
	}
}

void XLeftWnd::ChangeNodeItemText(HTREEITEM item,CString szNodeName)
{
	if(item!=NULL)
	{
		m_TreeCtrl.SetItemText(item,szNodeName);
	}
}

/***********************************************************
** 功能描述: 新建组，添加到树中
** 输入参数: CString szGroupName	组名称
			int nType           类型：输入输出
			BOOL bMainSec       是否为主副屏添加 TRUE是
** 输出结果: 
************************************************************/
void XLeftWnd::AddNodeGroup(CString szGroupName,int nType,BOOL bMainSec)
{
	//父节点
	HTREEITEM hParent=NULL;
	int nData=0;
	if(nType==1)
	{
		hParent=m_hItemInput;
		nData=ITEMDATA_NODEGROUPIN;
	}
	else if(nType==3)
	{
		hParent=m_hItemOutput;
		nData=ITEMDATA_NODEGROUPOUT;
	}

	HTREEITEM itemNew=NULL;
	XNodeGroupInfo* pInfo=NULL;
	MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapNodeGroupMainSec=m_pDelegate->GetMapNodeGroupMainSec();
	//先计算出该组所在树顺序
	std::vector<CString> VecStr;
	if(bMainSec)
	{
		for(auto iter=MapNodeGroupMainSec.begin();iter!=MapNodeGroupMainSec.end();++iter)
		{
			pInfo=iter->second;
			if(nType==pInfo->GetType())
				VecStr.push_back(pInfo->GetGroupName());
		}
	}
	else
	{
		for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
		{
			pInfo=iter->second;
			if(nType==pInfo->GetType())
				VecStr.push_back(pInfo->GetGroupName());
		}
	}

	int nIndex=GetGroupIndexInTree(VecStr,szGroupName);
	if(nIndex==0)
	{
		//插在第一个
		CString szTempName=VecStr[nIndex];

		if(bMainSec)
		{
			itemNew=m_TreeCtrl.InsertItem(szGroupName,6,6,hParent,TVI_FIRST);
		}
		else
		{
			//插在主副屏后面，如果没有主副屏，插在第一个
			if(MapNodeGroupMainSec.size()==0)
			{
				itemNew=m_TreeCtrl.InsertItem(szGroupName,3,3,hParent,TVI_FIRST);
			}
			else
			{
				auto iter=MapNodeGroupMainSec.end();
				iter--;
				XNodeGroupInfo* pInfo=iter->second;
				HTREEITEM item=NULL;
				if(NULL!=pInfo)
					item=pInfo->GetGroupItem();

				itemNew=m_TreeCtrl.InsertItem(szGroupName,3,3,hParent,item);
			}
		}
		m_TreeCtrl.SetItemData(itemNew,nData);
	}
	else
	{
		CString szTempName=VecStr[nIndex-1];
		MAP_NODEGROUP::iterator iterGroup=MapNodeGroup.find(szTempName);
		if(iterGroup!=MapNodeGroup.end())
			pInfo=iterGroup->second;

		HTREEITEM item=NULL;
		if(NULL!=pInfo)
			item=pInfo->GetGroupItem();//组项（插在这个后面）

		if(pInfo->GetMainSecond())
		{
			itemNew=m_TreeCtrl.InsertItem(szGroupName,6,6,hParent,item);
		}
		else
		{
			itemNew=m_TreeCtrl.InsertItem(szGroupName,3,3,hParent,item);
		}
		
		m_TreeCtrl.SetItemData(itemNew,nData);
	}

	if(bMainSec)
	{
		auto iter=MapNodeGroupMainSec.find(szGroupName);
		if(iter!=MapNodeGroupMainSec.end())
		{
			pInfo=iter->second;
			pInfo->SetGroupItem(itemNew);
		}
	}
	else
	{
		MAP_NODEGROUP::iterator iterNew=MapNodeGroup.find(szGroupName);
		if(iterNew!=MapNodeGroup.end())
		{
			pInfo=iterNew->second;
			pInfo->SetGroupItem(itemNew);
		}
	}
}

int XLeftWnd::GetGroupIndexInTree(std::vector<CString>& VecStr,CString szGroupName)
{
	//0,1,2 从0开始
	int nIndex=0;
	std::vector<CString>::iterator iter=find(VecStr.begin(),VecStr.end(),szGroupName);
	nIndex=iter-VecStr.begin();
	return nIndex;
}

void XLeftWnd::AddNodeInGroup(XNode* pNode,int nGroupID)
{
	//插在组里
	HTREEITEM hItemGroup=NULL;
	MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
	{
		XNodeGroupInfo* pInfo=iter->second;
		if(!pInfo->GetMainSecond())
		{
			if(pInfo->GetGroupID()==nGroupID)
			{
				hItemGroup=pInfo->GetGroupItem();
				SetItemChild(hItemGroup);
				HTREEITEM itemNode=AddSubItem(pNode->GetNodeName());
				pNode->SetTreeItem(itemNode);

				if(!pNode->GetDrag())
					m_TreeCtrl.SetItemImage(itemNode,5,5);
			}
		}
	}
	m_TreeCtrl.Expand(hItemGroup,TVE_EXPAND);
}

void XLeftWnd::AddNodeInGroupMaster(int nNodeID,int nMasterID)
{
	//插在组里
	HTREEITEM hItemMaster=NULL;
	MAP_GROUPMAINSEC& MapNodeGroup=m_pDelegate->GetMapNodeGroupMainSec();
	MAP_NODEMAINSEC& MapNodeMainSec=m_pDelegate->GetMapNodeMainSec();
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();

	for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
	{
		XNodeGroupInfo* pInfo=iter->second;
		if(pInfo->GetMainSecond())
		{
			if(pInfo->GetGroupID()==nMasterID)
			{
				hItemMaster=pInfo->GetGroupItem();
				SetItemChild(hItemMaster);

				XNode* pNode=NULL;
				if(MapNode.find(nNodeID)!=MapNode.end())
				{
					pNode=MapNode[nNodeID];
				}

				HTREEITEM itemNode=AddSubItem(pNode->GetNodeName());
				if(MapNodeMainSec.find(nNodeID)!=MapNodeMainSec.end())
				{
					MapNodeMainSec[nNodeID]=itemNode;
				}

				if(!pNode->GetDrag())
					m_TreeCtrl.SetItemImage(itemNode,5,5);
			}
		}
	}
	m_TreeCtrl.Expand(hItemMaster,TVE_EXPAND);
}

HTREEITEM XLeftWnd::GetParentItem(HTREEITEM item)
{
	return m_TreeCtrl.GetParentItem(item);
}

void XLeftWnd::AddNodeInTreeLast(XNode* pNode,int nType)
{
	if(nType==TERM_IN)
		SetItemRoot(m_hItemInput);
	else if(nType==TERM_OUT)
		SetItemRoot(m_hItemOutput);

	HTREEITEM hItem=AddChildItem(pNode->GetNodeName(),ITEMDATA_NODE);
	pNode->SetTreeItem(hItem);

	SetNodeDrag(pNode->GetNodeID(),TRUE);
	SetNodeColor(pNode->GetNodeID(),TRUE);
}

BOOL XLeftWnd::JudgeNodeInGroup(XNode* pNode)
{
	BOOL bInGroup=FALSE;
	if(pNode->GetGroup()==0&&pNode->GetMaster()==0)
	{
		bInGroup=FALSE;
	}
	else if(pNode->GetGroup()!=0||pNode->GetMaster()!=0)
	{
		bInGroup=TRUE;
	}
	return bInGroup;
}

void XLeftWnd::AddGroup(HTREEITEM hItemFirst,HTREEITEM hItemSecond)
{
	//hItemFirst为主动拖拽，hItemSecond为被动
	CString szFirstText=m_TreeCtrl.GetItemText(hItemFirst);
	int nFirstData=m_TreeCtrl.GetItemData(hItemFirst);

	XNode* pFirstNode=GetNodeByName(szFirstText);
	if(NULL==pFirstNode)
		return;

	if(nFirstData==ITEMDATA_NODEGROUPIN||
	   nFirstData==ITEMDATA_NODEGROUPOUT)
		return;

	HTREEITEM hFirstParent=m_TreeCtrl.GetParentItem(hItemFirst);
	if(NULL==hFirstParent)
		return;
	CString szFirstItem=m_TreeCtrl.GetItemText(hFirstParent);
	XNodeGroupInfo* pFirstParentInfo=GetNodeGroupByName(szFirstItem);

	if(pFirstNode->GetGroup()==0&&NULL==pFirstParentInfo)
	{
		//不在组内,只要组为0 就是不在组内
		CString szSecondText=m_TreeCtrl.GetItemText(hItemSecond);
		int nSecondData=m_TreeCtrl.GetItemData(hItemSecond);

		if(nSecondData==ITEMDATA_NODE)
		{
			//被动为节点，通过判断组类型 确定是哪种组
			XNode* pSecondNode=GetNodeByName(szSecondText);
			if(NULL==pSecondNode)
				return;

			HTREEITEM hSecondParent=m_TreeCtrl.GetParentItem(hItemSecond);
			if(NULL==hSecondParent)
				return;

			CString szParent=m_TreeCtrl.GetItemText(hSecondParent);
			XNodeGroupInfo* pSecondParentInfo=GetNodeGroupByName(szParent);

			if(pSecondNode->GetGroup()==0&&NULL==pSecondParentInfo)
			{
				//被拖拽不在组内
				if(pFirstNode->GetNodeType()!=pSecondNode->GetNodeType())
					return;

				//保存拖拽
				ClearVecDrag();
				m_VecDrag.push_back(pFirstNode->GetNodeID());
				m_VecDrag.push_back(pSecondNode->GetNodeID());

				//先添加组
				CString szFrontName=_C(_T("105"),_T("分组"));
				CString szGroupName=GetGroupNameByFrontName(szFrontName);

				int nGroupType=0;
				if(pFirstNode->GetNodeType()==TERM_IN)
					nGroupType=1;
				else if(pFirstNode->GetNodeType()==TERM_OUT)
					nGroupType=3;

				int nCreatorID=m_pDelegate->GetCurUserID();

				XNodeGroupInfo nodeGroupInfo;
				nodeGroupInfo.SetGroupName(szGroupName);
				nodeGroupInfo.SetType(nGroupType);
				nodeGroupInfo.SetCreatorID(nCreatorID);
				nodeGroupInfo.SetCreateMode(CREATEMODE_DRAG);

				XSendDataManage::GetInstance()->AddSendDataOfAddSeatArrage(nodeGroupInfo);
			}
			else if(pSecondNode->GetGroup()==0&&NULL!=pSecondParentInfo)
			{
				if(pSecondParentInfo->GetMainSecond())
				{
					//在主副屏组内
					//HTREEITEM hSecondParent=m_TreeCtrl.GetParentItem(hItemSecond);
					//if(NULL==hSecondParent)
					//	return;

					//CString szGroupName=m_TreeCtrl.GetItemText(hSecondParent);
					//XNodeGroupInfo* pInfo=GetNodeGroupByName(szGroupName);
					//if(NULL==pInfo)
					//	return;

					int nGroupID=pSecondParentInfo->GetGroupID();

					//判断是不是重复了
					if(pFirstNode->GetMaster()==nGroupID)
						return;

					int nMark=UPDATAMAKE_MASTER;
					XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(pFirstNode->GetNodeID(),nGroupID,nMark);
				}
			}
			else if(pSecondNode->GetGroup()!=0&&NULL!=pSecondParentInfo)
			{
				if(!pSecondParentInfo->GetMainSecond())
				{
					//在普通组内
					//HTREEITEM hSecondParent=m_TreeCtrl.GetParentItem(hItemSecond);
					//if(NULL==hSecondParent)
					//	return;

					//CString szGroupName=m_TreeCtrl.GetItemText(hSecondParent);
					//XNodeGroupInfo* pInfo=GetNodeGroupByName(szGroupName);
					//if(NULL==pInfo)
					//	return;

					int nGroupID=pSecondParentInfo->GetGroupID();

					int nMark=UPDATAMAKE_GROUP;
					XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(pFirstNode->GetNodeID(),nGroupID,nMark);
				}
			}
		}
		else if(nSecondData==ITEMDATA_NODEGROUPIN||nSecondData==ITEMDATA_NODEGROUPOUT)
		{
			//被动为组
			//先判断是否为同类型
			int nNodeType=pFirstNode->GetNodeType();
			if(nNodeType==TERM_IN&&nSecondData==ITEMDATA_NODEGROUPOUT)
				return;
			else if(nNodeType==TERM_OUT&&nSecondData==ITEMDATA_NODEGROUPIN)
				return;

			XNodeGroupInfo* pInfo=GetNodeGroupByName(szSecondText);
			if(NULL==pInfo)
				return;

			int nGroupID=pInfo->GetGroupID();
			if(pInfo->GetMainSecond())
			{
				if(pFirstNode->GetMaster()==nGroupID)
					return;

				int nMark=UPDATAMAKE_MASTER;
				XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(pFirstNode->GetNodeID(),nGroupID,nMark);
			}
			else
			{
				int nMark=UPDATAMAKE_GROUP;
				XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(pFirstNode->GetNodeID(),nGroupID,nMark);
			}
		}
		else
		{
			return;
		}
	}
	else if(NULL!=pFirstParentInfo)
	{
		//拖拽在组内
		//////////////////////////////////////////////////////////////////////////
		CString szSecondText=m_TreeCtrl.GetItemText(hItemSecond);
		int nSecondData=m_TreeCtrl.GetItemData(hItemSecond);

		if(nSecondData==ITEMDATA_NODE)
		{
			//被动为节点
			//判断节点在那个组里，还是在外面
			XNode* pSecondNode=GetNodeByName(szSecondText);
			if(NULL==pSecondNode)
				return;
			HTREEITEM hSecondParent=m_TreeCtrl.GetParentItem(hItemSecond);
			if(NULL==hSecondParent)
				return;
			CString szGroupName=m_TreeCtrl.GetItemText(hSecondParent);
			XNodeGroupInfo* pInfo=GetNodeGroupByName(szGroupName);
			if(pSecondNode->GetGroup()==0&&NULL==pInfo)
			{
				//被动在组外（从组中删除）
				HTREEITEM hFirstParent=m_TreeCtrl.GetParentItem(hItemFirst);
				if(NULL==hFirstParent)
					return;
				CString szFirstGroup=m_TreeCtrl.GetItemText(hFirstParent);
				XNodeGroupInfo* pFirstInfo=GetNodeGroupByName(szFirstGroup);	
				if(NULL==pFirstInfo)
					return;

				VEC_ARRAGE& VecArrage=pFirstInfo->GetVecArrage();
				//判断在不在集合中
				if(DecidedNodeInGroup(VecArrage,pFirstNode->GetNodeID()))
				{
					//在组中
					//保存要移除的节点
					ClearVecDel();
					m_VecDel.push_back(pFirstNode->GetNodeID());
					//先更新组信息
					m_pDelegate->UpdateGroupArrageByRemoveNode(szFirstGroup,pFirstNode->GetNodeID());
				}
				else
				{
					//直接移除
					if(pFirstInfo->GetMainSecond())
					{
						int nMark=UPDATAMAKE_MASTER;
						XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(pFirstNode->GetNodeID(),0,nMark);
					}
					else
					{
						int nMark=UPDATAMAKE_GROUP;
						XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(pFirstNode->GetNodeID(),0,nMark);
					}
				}
			}
			else if(pSecondNode->GetGroup()!=0&&NULL!=pInfo)
			{
				//pInfo 为secondInfo
				//在组内（添加到组内）
				//HTREEITEM hFirstParent=m_TreeCtrl.GetParentItem(hItemFirst);
				//if(NULL==hFirstParent)
				//	return;
				//HTREEITEM hSecondParent=m_TreeCtrl.GetParentItem(hItemSecond);
				//if(NULL==hSecondParent)
				//	return;
				//if(hFirstParent==hSecondParent)
				//	return;

				//CString szFirstParentText=m_TreeCtrl.GetItemText(hFirstParent);
				//XNodeGroupInfo* pFirstInfo=GetNodeGroupByName(szFirstParentText);
				//if(NULL==pFirstInfo)
				//	return;
				////CString szSecondParentText=m_TreeCtrl.GetItemText(hSecondParent);
				////XNodeGroupInfo* pSecondInfo=GetNodeGroupByName(szSecondParentText);
				////if(NULL==pSecondInfo)
				////	return;
				////类型不同 输入输出
				//if(pFirstInfo->GetType()!=pInfo->GetType())
				//	return;

				////主副屏组中 不能拖到其他组
				//if(pFirstInfo->GetMainSecond())
				//	return;

				//if(!pFirstInfo->GetMainSecond()&&!pInfo->GetMainSecond())
				//{
				//	//从组拖到组
				//}
				//else if(!pFirstInfo->GetMainSecond()&&pInfo->GetMainSecond())
				//{
				//	//从组中拖到主副屏中

				//}





				//if(pFirstInfo->GetMainSecond()!=pSecondInfo->GetMainSecond())
				//	return;

				////保存拖拽节点
				////m_MapDrag.clear();
				////m_MapDrag.insert(std::pair<int,int>(pFirstNode->GetNodeID(),pSecondInfo->GetGroupID()));

				////先更新组信息
				//m_pDelegate->UpdateGroupArrageByRemoveNode(szFirstParentText,pFirstNode->GetNodeID());

				//int nGroupID=pSecondInfo->GetGroupID();
				//if(pSecondInfo->GetMainSecond())
				//{
				//	int nMark=UPDATAMAKE_MASTER;
				//	XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(pFirstNode->GetNodeID(),nGroupID,nMark);
				//}
				//else
				//{
				//	int nMark=UPDATAMAKE_GROUP;
				//	XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(pFirstNode->GetNodeID(),nGroupID,nMark);
				//}

				////更新坐席排列
				////首先要判断坐席中能不能删除(现在没判断)
				//if(m_pDelegate->JudgetDelNodeFromGroup(szFirstParentText,pFirstNode->GetNodeID()))
				//{
				//	//执行删除
				//	m_pDelegate->DelNodeFromGroup(szFirstParentText,pFirstNode->GetNodeID());
				//}
			}
		}
		else if(nSecondData==ITEMDATA_NODEGROUPIN||nSecondData==ITEMDATA_NODEGROUPOUT)
		{
			//被动为组
			//移到其他组中
			//int nNodeType=pFirstNode->GetNodeType();
			//if(nNodeType==TERM_IN&&nSecondData==ITEMDATA_NODEGROUPOUT)
			//	return;
			//else if(nNodeType==TERM_OUT&&nSecondData==ITEMDATA_NODEGROUPIN)
			//	return;

			//HTREEITEM hFirstParentItem=m_TreeCtrl.GetParentItem(hItemFirst);
			//if(NULL==hFirstParentItem)
			//	return;
			//if(hFirstParentItem==hItemSecond)
			//	return;

			//CString szFirstParentText=m_TreeCtrl.GetItemText(hFirstParentItem);

			//XNodeGroupInfo* pInfo=NULL;
			//CString szSecondText=m_TreeCtrl.GetItemText(hItemSecond);
			//MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
			//MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szSecondText);
			//if(iter!=MapNodeGroup.end())
			//{
			//	pInfo=iter->second;
			//}

			////TRACE0("XXXXXX\n");
			////TRACE(_T("GroupID=%d\n"),pInfo->GetGroupID());

			////保存拖拽节点
			//m_MapDrag.clear();
			//m_MapDrag.insert(std::pair<int,int>(pFirstNode->GetNodeID(),pInfo->GetGroupID()));

			////首先从组中删除
			////更新坐席排列
			////首先要判断坐席中能不能删除(现在没判断)
			//if(m_pDelegate->JudgetDelNodeFromGroup(szFirstParentText,pFirstNode->GetNodeID()))
			//{
			//	//执行删除
			//	m_pDelegate->DelNodeFromGroup(szFirstParentText,pFirstNode->GetNodeID());
			//}
		}
		else
		{
			return;
		}
	}
}

CString XLeftWnd::GetGroupNameByFrontName(CString szName)
{
	MAP_NODEGROUP& MapGroup=GetMapNodeGroup();
	CString szTemp;

	int n=1;
	while(1)
	{
		szTemp.Format(_T("%d"),n);
		szTemp=szName+szTemp;

		MAP_NODEGROUP::iterator iter=MapGroup.find(szTemp);
		if(iter==MapGroup.end())
			break;
		n++;
	}
	return szTemp;
}

//////////////////////////////////////////////////////////////////////////
void XLeftWnd::DragGroupToSeat(CString szGroupName,CPoint& point)
{
	m_pDelegate->DragGroupToSeat(szGroupName,point);
}

void XLeftWnd::SwitchPage(int nPage)
{
	m_pDelegate->SwitchPage(nPage);
}

void XLeftWnd::DrawGroupInScreen(CString szGroupName)
{
	m_pDelegate->DrawGroupInScreen(szGroupName);
}

void XLeftWnd::SetSeatSelected(CString szGroupName)
{
	m_pDelegate->SetSeatSelected(szGroupName);
}

void XLeftWnd::HidePopMenuBtn()
{
	m_pDelegate->HidePopMenuBtn();
}

void XLeftWnd::ShowPopMenuBtn()
{
	m_pDelegate->ShowPopMenuBtn();
}

void XLeftWnd::ResetRibbonBar()
{
	m_pDelegate->ResetRibbonBar();
}

float XLeftWnd::GetCurScale()
{
	return m_pDelegate->GetCurScale();
}

void XLeftWnd::ReciveDataOfSplitInput(char* pData)
{
	XSplitInputResult result;
	XJsonManage::GetInstance()->ParseJsonToSplitInput(pData,result);




}

/////////////////////////////////////////////////////////////////////////
HTREEITEM XLeftWnd::AddRootItem(CString szRoot,int nType)
{
	CString szCategories=szRoot;

	HTREEITEM item=NULL;
	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent=TVI_ROOT;
	tvinsert.hInsertAfter=TVI_LAST;
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE;
	tvinsert.item.cChildren=1;
	tvinsert.item.pszText=szCategories.GetBuffer();
	tvinsert.item.iImage=0;
	tvinsert.item.iSelectedImage=0;
	item=m_TreeCtrl.InsertItem(&tvinsert);
	m_TreeCtrl.SetItemData(item,nType);
	szCategories.ReleaseBuffer();

	switch(nType)
	{
		case ITEMDATA_NODEIN:
		case ITEMDATA_MATRIXNODEIN:
			m_TreeCtrl.SetItemImage(item,1,1);
			break;
		case ITEMDATA_NODEOUT:
			m_TreeCtrl.SetItemImage(item,2,2);
			break;
		case ITEMDATA_SPLITNODE:
			m_TreeCtrl.SetItemImage(item,4,4);
			break;
		default:
			break;
	}

	SetItemRoot(item);
	return item;
}

void XLeftWnd::SetItemRoot(HTREEITEM h)
{
	m_hRootItem=h;
}

HTREEITEM XLeftWnd::GetItemRoot()
{
	return m_hRootItem;
}

HTREEITEM XLeftWnd::AddChildItem(CString szChild,int nType,int nGroupType)
{
	CString szCategories=szChild;
	HTREEITEM item=NULL;
	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent=GetItemRoot();
	tvinsert.hInsertAfter=TVI_LAST;
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren=1;
	tvinsert.item.pszText=szCategories.GetBuffer();
	tvinsert.item.iImage=3;
	tvinsert.item.iSelectedImage=3;
	item=m_TreeCtrl.InsertItem(&tvinsert);

	m_TreeCtrl.SetItemData(item,nType);
	szCategories.ReleaseBuffer();

	if(nType==ITEMDATA_NODE)
	{
		m_TreeCtrl.SetItemImage(item,4,4);
	}
	else if(nType==ITEMDATA_MATRIXNODE)
	{
		m_TreeCtrl.SetItemImage(item,4,4);
	}
	else
	{
		if(nGroupType==ITEMDATA_NODEGROUPIN_M)
		{
			m_TreeCtrl.SetItemImage(item,6,6);
		}
	}
	SetItemChild(item);
	return item;
}

void XLeftWnd::SetItemChild(HTREEITEM h)
{
	m_hChildItem=h;
}

HTREEITEM XLeftWnd::GetItemChild()
{
	return m_hChildItem;
}

HTREEITEM XLeftWnd::AddSubItem(CString szSub)
{
	CString szCategories=szSub;
	HTREEITEM item=NULL;
	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent=GetItemChild();
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren=1;
	tvinsert.item.pszText=szCategories.GetBuffer();
	tvinsert.item.iImage=4;
	tvinsert.item.iSelectedImage=4;
	item=m_TreeCtrl.InsertItem(&tvinsert);

	m_TreeCtrl.SetItemData(item,(DWORD_PTR)ITEMDATA_NODE);
	szCategories.ReleaseBuffer();

	//SetItemChild(item);
	return item;
}

