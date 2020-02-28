// XFolder.cpp : 实现文件
//

#include "stdafx.h"
#include "XFolder.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XUserManage.h"
#include "XFolderInfo.h"
#include "XNode.h"
#include "XSendDataManage.h"
#include "XSetListCtrl.h"
#include "XPower.h"
#include "XAddFolder.h"



// XFolder 对话框

IMPLEMENT_DYNAMIC(XFolder,XBaseDialog)

XFolder::XFolder(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XFolder::IDD,pParent)
{

}

XFolder::~XFolder()
{
}

void XFolder::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TREE_FOLDER,m_Tree);
	DDX_Control(pDX,IDC_LIST_VISIBLEUSER,m_ListVisible);
	DDX_Control(pDX,IDC_STATIC_FLIST,m_TextTree);
	DDX_Control(pDX,IDC_STATIC_ULIST,m_TextUser);
	DDX_Control(pDX,IDC_BTN_ADD,m_BtnAddFolder);
	DDX_Control(pDX,IDC_BTN_DEL,m_BtnDelFolder);
}


BEGIN_MESSAGE_MAP(XFolder,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
	ON_NOTIFY(NM_DBLCLK,IDC_TREE_FOLDER,OnDblclkTree)
	ON_NOTIFY(NM_CLICK,IDC_TREE_FOLDER,OnClkTree)
END_MESSAGE_MAP()


BOOL XFolder::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XFolder::Init()
{
	SetWindowText(_C(_T("316"),_T("文件夹")));
	if(InitImageList())
	{
		m_Tree.SetImageList(&m_ImageList,TVSIL_NORMAL);
	}
	
	InitList();
	InsertUserList();

	InsertFloder();

	ReloadInterface();
}

BOOL XFolder::InitImageList()
{
	if(!m_ImageList.Create(20,20,ILC_COLOR32|ILC_MASK,0,1))
		return FALSE;

	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_INPUT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_OUTPUT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUP));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NODE));
	return TRUE;
}

void XFolder::InitList()
{
	XSetListCtrl::InitList(&m_ListVisible,3,TRUE);

	m_ListVisible.EnableToolTips(TRUE);

	//m_ListVisible.SetColumnWidth(0,118);
	//m_ListVisible.SetColumnWidth(0,118);
}

void XFolder::ReloadInterface()
{
	m_TextTree.SetText(_C(_T("321"),_T("文件夹列表")),TRUE);
	m_TextUser.SetText(_C(_T("322"),_T("可见用户列表")),TRUE);

	m_BtnAddFolder.SetCaption(_C(_T("323"),_T("添加目录")));
	m_BtnDelFolder.SetCaption(_C(_T("163"),_T("删除")));

	ReloadListInterface();
}

void XFolder::ReloadListInterface()
{
	CString szTemp=_T("");

	LVCOLUMN col;
	col.mask=LVCF_TEXT;

	szTemp=_C(_T("39"),_T("ID"));
	col.pszText=szTemp.GetBuffer();
	m_ListVisible.SetColumn(0,&col);
	szTemp.ReleaseBuffer();
	//////////////////////////////////////////////////////////////////////////
	szTemp=_C(_T("25"),_T("用户名"));
	col.pszText=szTemp.GetBuffer();
	m_ListVisible.SetColumn(1,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("42"),_T("用户组"));
	col.pszText=szTemp.GetBuffer();
	m_ListVisible.SetColumn(2,&col);
	szTemp.ReleaseBuffer();
}

void XFolder::InsertUserList()
{
	//显示用户
	auto& MapPower=m_pManage->GetMapPower();
	for(auto& user:MapPower)
	{
		XPower* pPower=user.second;

		CString szID;
		szID.Format(_T("%d"),pPower->GetUserID());

		CString szUserName=pPower->GetUserName();
		CString szUserGroup=pPower->GetUserGroup();

		AddListInfo(szID,szUserName,szUserGroup);
	}
}

int XFolder::AddListInfo(CString szID,CString szUserName,CString szUserGroup)
{
	//权限列表
	int nCount=0;
	nCount=m_ListVisible.GetItemCount();

	//if(nCount>17)
	//	m_PowerList.SetColumnWidth(0,217);
	//else
	//	m_PowerList.SetColumnWidth(0,235);

	m_ListVisible.InsertItem(nCount,_T(""));
	SetListInfo(nCount,szID,szUserName,szUserGroup);
	return nCount;
}

void XFolder::SetListInfo(int nCount,CString szID,CString szUserName,CString szUserGroup)
{
	m_ListVisible.SetItemText(nCount,0,szID);
	m_ListVisible.SetItemText(nCount,1,szUserName);
	m_ListVisible.SetItemText(nCount,2,szUserGroup);
}

void XFolder::InsertFloder()
{
	//插入根目录和根目录的子目录

	//获取集合
	auto& MapRootFolder=m_pManage->GetMapRootFolder();
	
	//先根目录
	for(auto& root:MapRootFolder)
	{
		XFolderInfo* pInfo=root.second;

		//1为输入
		if(NULL==m_hInputItem)
			m_hInputItem=AddRootItem(_C(_T("62"),_T("输入")),FOLDERTYPE_IN);

		//2为输出
		if(NULL==m_hOutputItem)
			m_hOutputItem=AddRootItem(_C(_T("63"),_T("输出")),FOLDERTYPE_OUT);

		CString szName=pInfo->GetName();
		int nType=pInfo->GetType();
		if(nType==1)
		{
			HTREEITEM hItem=AddChildItem(szName,m_hInputItem,FOLDERTYPE_ROOT);
			pInfo->SetTreeItem(hItem);
			//////////////////////////////////////////////////////////////////////////
			//子目录
			//先文件夹
			//int nID=pInfo->GetID();
			//InsertFloderInfo(nID,hItem);
		}
		else if(nType==2)
		{
			HTREEITEM hItem=AddChildItem(szName,m_hOutputItem,FOLDERTYPE_ROOT);
			pInfo->SetTreeItem(hItem);
			//先文件夹
			//int nID=pInfo->GetID();
			//InsertFloderInfo(nID,hItem);
		}
	}
	m_Tree.Expand(m_hInputItem,TVE_EXPAND);
	m_Tree.Expand(m_hOutputItem,TVE_EXPAND);
}

CString XFolder::GetNodeNameByID(int nID)
{
	MAP_NODE& MapNode=m_pManage->GetMapNode();

	for(auto& map:MapNode)
	{
		XNode* pNode=map.second;
		if(pNode->GetNodeID()==nID)
			return pNode->GetNodeName();
	}
	return _T("");
}


void XFolder::OnClkTree(NMHDR* pNMHDR,LRESULT* pResult)
{
	CPoint point;
	GetCursorPos(&point);//获得鼠标点击的位置
	m_Tree.ScreenToClient(&point);//转化为客户坐标
	UINT uFlags;

	HTREEITEM hItem;
	hItem=m_Tree.HitTest(point,&uFlags);//获得当前点击节点的ITEM
	if(NULL==hItem)
		return;
	m_hSelItem=hItem;
	//单击时显示用户
	CString szItem=m_Tree.GetItemText(hItem);

	//文件夹才改变
	int nData=m_Tree.GetItemData(hItem);
	if(nData==FOLDERTYPE_CHILD||
	   nData==FOLDERTYPE_ROOT)
	{
		//选中可视用户
		SetVisibleUserSelect(szItem);
	}


	*pResult=0;
}

void XFolder::OnDblclkTree(NMHDR *pNMHDR,LRESULT *pResult)
{
	CPoint point;
	GetCursorPos(&point);//获得鼠标点击的位置
	m_Tree.ScreenToClient(&point);//转化为客户坐标
	UINT uFlags;

	HTREEITEM hItem;
	hItem=m_Tree.HitTest(point,&uFlags);//获得当前点击节点的ITEM
	if(NULL==hItem)
		return;
	m_hSelItem=hItem;
	if(hItem!=m_hInputItem&&
	   hItem!=m_hOutputItem)
	{
		DelAllSubItemByItem(hItem);
	}
	
	CString szItem=m_Tree.GetItemText(hItem);
	InsertFloderInfo(szItem,hItem);

	//文件夹才改变
	int nData=m_Tree.GetItemData(hItem);
	if(nData==FOLDERTYPE_CHILD||
	   nData==FOLDERTYPE_ROOT)
	{
		//选中可视用户
		SetVisibleUserSelect(szItem);
	}

	*pResult=0;
}

void XFolder::SetVisibleUserSelect(CString szParentName)
{
	int nCount=m_ListVisible.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		XSetListCtrl::SetListCheckItemFalse(&m_ListVisible,i);
	}

	auto& MapSubFolder=m_pManage->GetMapSubFolder();
	for(auto& sub:MapSubFolder)
	{
		XSubFolder* pSub=sub.second;

		CString szName=pSub->GetName();
		if(szParentName==szName)
		{
			auto& MapUserList=pSub->GetMapUserList();
			for(auto& userList:MapUserList)
			{
				int nUserID=userList.first;
				
				int nItem=GetItemIndexByUserID(nUserID);
				if(nItem!=-1)
				{
					XSetListCtrl::SetListCheckItem(&m_ListVisible,nItem);
				}
			}
		}
	}
}

int XFolder::GetItemIndexByUserID(int nID)
{
	int nCount=m_ListVisible.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		CString szID=XSetListCtrl::GetColumnText(&m_ListVisible,i,0);
		int nCurID=_ttoi(szID);
		if(nCurID==nID)
		{
			return i;
		}
	}
	return -1;
}

void XFolder::InsertFloderInfo(CString szParent,HTREEITEM hItem)
{
	//点击插入子目录
	auto& MapSubFolder=m_pManage->GetMapSubFolder();
	for(auto& sub:MapSubFolder)
	{
		XSubFolder* pSub=sub.second;

		CString szName=pSub->GetName();
		if(szName==szParent)
		{
			auto& MapSubFolderList=pSub->GetMapSubFolderList();
			for(auto& subList:MapSubFolderList)
			{
				XSubFolder* pSubInfo=subList.second;
				CString szSubName=pSubInfo->GetName();

				HTREEITEM hSubItem=AddChildItem(szSubName,hItem,FOLDERTYPE_CHILD);
				pSubInfo->SetTreeItem(hSubItem);
			}
		}
	}
	//再节点
	for(auto& sub:MapSubFolder)
	{
		XSubFolder* pSub=sub.second;
		CString szName=pSub->GetName();
		if(szName==szParent)
		{
			auto& MapTermList=pSub->GetMapTermList();
			for(auto& term:MapTermList)
			{
				int nNodeID=term.first;
				CString szNodeName=GetNodeNameByID(nNodeID);

				HTREEITEM hSubItem=AddChildItem(szNodeName,hItem,FOLDERTYPE_NODE);
				term.second=hSubItem;
			}
		}
	}
}


void XFolder::DelAllSubItemByItem(HTREEITEM hItem)
{
	if(m_Tree.ItemHasChildren(hItem))
	{
		HTREEITEM hNextItem=NULL;
		HTREEITEM hChildItem=m_Tree.GetChildItem(hItem);
		while(hChildItem!=NULL)
		{
			hNextItem=m_Tree.GetNextItem(hChildItem,TVGN_NEXT);

			CString szItem=m_Tree.GetItemText(hNextItem);
			TRACE(_T("Item=%s\n"),szItem);

			m_Tree.DeleteItem(hChildItem);
			hChildItem=hNextItem;
		}
	}
}

void XFolder::AddFolder()
{
	//if(NULL==m_hSelItem)	
		//return;

	HTREEITEM hSelItem=m_Tree.GetSelectedItem();
	if(NULL==hSelItem)
		return;

	m_hSelItem=hSelItem;

	int nType=0;
	int nID=0;
	if(hSelItem==m_hInputItem)
	{
		nType=1;
	}
	else if(hSelItem==m_hOutputItem)
	{
		nType=2;
	}
	else
	{
		CString szItemText=m_Tree.GetItemText(hSelItem);
		XSubFolder* pSub=GetSubFolderByName(szItemText);
		if(NULL!=pSub)
		{
			nType=pSub->GetType();
			nID=pSub->GetID();
		}
	}

	//先添加空目录
	XAddFolder dlg;
	if(IDOK==dlg.DoModal())
	{
		CString szName=dlg.GetName();

		XSubFolder sub;
		sub.SetName(szName);
		sub.SetParentID(nID);
		sub.SetType(nType);

		XSendDataManage::GetInstance()->AddSendDataOfAddFolder(sub);


	}
}

void XFolder::AddFolderToTree(CString szName)
{
	if(NULL==m_hSelItem)
		return;

	//auto& MapSubFolder=m_pManage->GetMapSubFolder();
	//if(MapSubFolder.find(nID)!=MapSubFolder.end())
	//{
	//	XSubFolder* pSub=MapSubFolder[nID];
	//	HTREEITEM hSubItem=AddChildItem(pSub->GetParent(),m_hSelItem,FOLDERTYPE_CHILD);
	//	pSub->SetTreeItem(hSubItem);
	//}

	HTREEITEM hSubItem=AddChildItem(szName,m_hSelItem,FOLDERTYPE_CHILD);
	//pSub->SetTreeItem(hSubItem);



	m_Tree.Expand(m_hSelItem,TVE_EXPAND);
}

XSubFolder* XFolder::GetSubFolderByName(CString szName)
{
	auto& MapSubFolder=m_pManage->GetMapSubFolder();
	for(auto& sub:MapSubFolder)
	{
		XSubFolder* pSub=sub.second;
		if(pSub->GetName()==szName)
			return pSub;
	}
	return NULL;
}

void XFolder::DeleteFolder()
{
	if(NULL==m_hSelItem)
	{
		_M(_T("337"),_T("选择要删除目录！"),MB_OK);
		return;
	}
		
	CString szItemText=m_Tree.GetItemText(m_hSelItem);
	if(szItemText==_C(_T("62"),_T("输入"))||szItemText==_C(_T("63"),_T("输出")))
		return;

	auto& MapSubFolder=m_pManage->GetMapSubFolder();
	for(auto& sub:MapSubFolder)
	{
		XSubFolder* pSub=sub.second;

		CString szName=pSub->GetName();
		if(szName==szItemText)
		{
			XSendDataManage::GetInstance()->AddSendDataOfDeleteFolder(pSub->GetID());
		}
	}
}

void XFolder::DeleteFolderFromTree(int nID)
{
	//从集合删除
	auto& MapRootFolder=m_pManage->GetMapRootFolder();
	for(auto& iter=MapRootFolder.begin();iter!=MapRootFolder.end();)
	{
		XFolderInfo* pInfo=iter->second;
		if(pInfo->GetID()==nID)
		{
			iter=MapRootFolder.erase(iter);
			delete pInfo;
		}
		else
		{
			++iter;
		}
	}

	if(NULL==m_hSelItem)
		return;

	HTREEITEM hParent=m_Tree.GetParentItem(m_hSelItem);
	CString szItemText=m_Tree.GetItemText(hParent);

	auto& MapSubFolder=m_pManage->GetMapSubFolder();
	for(auto& sub:MapSubFolder)
	{
		XSubFolder* pSub=sub.second;

		CString szName=pSub->GetName();
		if(szName==szItemText)
		{
			auto& MapSubFolderList=pSub->GetMapSubFolderList();
			for(auto iter1=MapSubFolderList.begin();iter1!=MapSubFolderList.end();)
			{
				XSubFolder* pSubInfo=iter1->second;
				if(pSubInfo->GetID()==nID)
				{
					iter1=MapSubFolderList.erase(iter1);
					delete pSubInfo;
				}
				else
				{
					++iter1;
				}
			}
		}
	}

	for(auto& iter=MapSubFolder.begin();iter!=MapSubFolder.end();)
	{
		XSubFolder* pInfo=iter->second;
		if(pInfo->GetID()==nID)
		{
			iter=MapSubFolder.erase(iter);
			delete pInfo;
		}
		else
		{
			++iter;
		}
	}

	//从树上删除
	m_Tree.DeleteItem(m_hSelItem);

	m_hSelItem=NULL;

}

LRESULT XFolder::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
		case IDC_BTN_ADD:
			{
				AddFolder();
			}
			break;
		case IDC_BTN_DEL:
			{
				DeleteFolder();
			}
			break;
		default:
			break;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//双击之后插入子目录
//void XFolder::InsetSubFolder()
//{
//	auto& MapSubFolder=m_pManage->GetMapSubFolder();
//	for(auto& sub:MapSubFolder)
//	{
//		XSubFolder* pSub=sub.second;
//		int nParentID=pSub->GetParentID();
//		//if(nParentID==nID)
//		{
//			auto& MapSubFolderList=pSub->GetMapSubFolderList();
//			for(auto& subList:MapSubFolderList)
//			{
//				XFolderInfo* pSubInfo=subList.second;
//				CString szSubName=pSubInfo->GetName();
//
//				HTREEITEM hSubItem=AddChildItem(szSubName,m_hTempItem,FOLDERTYPE_CHILD);
//				pSubInfo->SetTreeItem(hSubItem);
//			}
//		}
//	}
//	//再节点
//	for(auto& sub:MapSubFolder)
//	{
//		XSubFolder* pSub=sub.second;
//		int nParentID=pSub->GetParentID();
//		//if(nParentID==nID)
//		{
//			auto& MapTermList=pSub->GetMapTermList();
//			for(auto& term:MapTermList)
//			{
//				int nNodeID=term.first;
//				CString szNodeName=GetNodeNameByID(nNodeID);
//
//				HTREEITEM hSubItem=AddChildItem(szNodeName,m_hTempItem,FOLDERTYPE_NODE);
//				term.second=hSubItem;
//			}
//		}
//	}
//
//	m_Tree.Expand(m_hTempItem,TVE_EXPAND);
//}

HTREEITEM XFolder::AddRootItem(CString szRoot,int nType)
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
	item=m_Tree.InsertItem(&tvinsert);
	m_Tree.SetItemData(item,nType);
	szCategories.ReleaseBuffer();


	if(nType==FOLDERTYPE_IN)
	{
		m_Tree.SetItemImage(item,0,0);
	}
	else if(nType==FOLDERTYPE_OUT)
	{
		m_Tree.SetItemImage(item,1,1);
	}

	//SetRootItem(item);
	return item;
}

HTREEITEM XFolder::AddChildItem(CString szChild,HTREEITEM hItem,int nType)
{
	CString szCategories=szChild;
	HTREEITEM item=NULL;
	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent=hItem;
	tvinsert.hInsertAfter=TVI_LAST;
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren=1;
	tvinsert.item.pszText=szCategories.GetBuffer();
	tvinsert.item.iImage=3;
	tvinsert.item.iSelectedImage=3;
	item=m_Tree.InsertItem(&tvinsert);

	m_Tree.SetItemData(item,nType);
	szCategories.ReleaseBuffer();

	if(nType==FOLDERTYPE_ROOT)
	{
		m_Tree.SetItemImage(item,2,2);
	}
	else if(nType==FOLDERTYPE_CHILD)
	{
		m_Tree.SetItemImage(item,2,2);
	}
	else if(nType==FOLDERTYPE_NODE)
	{
		m_Tree.SetItemImage(item,3,3);
	}
	return item;
}