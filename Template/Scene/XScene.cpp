#include "stdafx.h"
#include "XScene.h"
#include "XConstant.h"
#include "XDelegateScene.h"
#include "..\MainFrm.h"
#include "..\resource.h"
#include "XTranslationManage.h"
#include "XScenePaneData.h"
#include "XSceneInfo.h"
#include "XMessageBox.h"
#include "XConstantData.h"
#include "HandlePath.h"
#include "XSceneGroupInfo.h"
#include "XSplitScene.h"
#include "XSendDataManage.h"




XScene* XScene::m_pInstance=NULL;
IMPLEMENT_DYNAMIC(XScene,CDockablePane)
XScene::XScene()
{
}

XScene::~XScene()
{
	ClearMapScene();
	ClearMapItem();
	ClearMapSceneGroup();
}

BEGIN_MESSAGE_MAP(XScene,CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK,ID_SCENETREE,OnNMRClickTree)
	ON_NOTIFY(NM_DBLCLK,ID_SCENETREE,OnDblclkTree)
	ON_NOTIFY(TVN_ENDLABELEDIT,ID_SCENETREE,OnTvnEndlabeledit)
	ON_COMMAND(ID_ALTERSCENE,AlterScene)
	ON_COMMAND(ID_DELSCENE,DelScene)
	ON_COMMAND(ID_REMOVE,Remove)

	ON_COMMAND(ID_ALTERSPLITSCENE,AlterSplitScene)
	ON_COMMAND(ID_DELSPLITSCENE,DelSplitScene)
	ON_COMMAND(ID_REMOVEFROMSGROUP,RemoveFromSplitGroup)
	ON_COMMAND(ID_ALTERSPLITGROUP,AlterSplitGroup)
	ON_COMMAND(ID_DELSPLITGROUP,DelSplitGroup)

END_MESSAGE_MAP()

void XScene::ClearMapScene()
{
	for(auto& map:m_MapScene)
	{
		delete map.second;
	}
	m_MapScene.clear();
}

void XScene::ClearMapItem()
{
	m_MapItem.clear();
}

void XScene::ClearMapSceneGroup()
{
	for(auto& map:m_MapSceneGroup)
	{
		delete map.second;
	}
	m_MapSceneGroup.clear();
}

XScene* XScene::GetInstance()
{
	if(NULL==m_pInstance)
	{
		m_pInstance=new XScene;
	}

	return m_pInstance;
}

void XScene::Release()
{
	RELEASE(m_pInstance);
}

int XScene::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CDockablePane::OnCreate(lpCreateStruct)==-1)
		return -1;

	if(!InitImageList())
		return -1;

	if(!InitTreeCtrl())
		return -1;

	return 0;
}

void XScene::OnSize(UINT nType,int cx,int cy)
{
	CDockablePane::OnSize(nType,cx,cy);
	AdjustLayout();
}

void XScene::OnPaint()
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

void XScene::AdjustLayout()
{
	if(NULL==GetSafeHwnd())
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	m_TreeCtrl.SetWindowPos(NULL,rectClient.left,rectClient.top,rectClient.Width(),rectClient.Height(),SWP_NOACTIVATE|SWP_NOZORDER);
}

void XScene::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_TreeCtrl.SetFocus();
}

void XScene::OnContextMenu(CWnd* /* pWnd */,CPoint point)
{
	return;
}

void XScene::SetUpPane(XLeftWnd* p)
{
	m_pLeftWnd=p;
}

void XScene::Init()
{
	CreatePane();
	//InitScene();
}

void XScene::CreatePane()
{
	CWnd* pWnd=m_pDelegate->GetCWND();
	CMainFrame* pMainFrame=(CMainFrame*)pWnd;

	CString szTitle=_C(_T("238"),_T("接管预案"));

	if(!Create(szTitle,pMainFrame,CRect(0,0,200,100),TRUE,
	   ID_SCENEPANE,WS_CHILD|WS_VISIBLE|CBRS_LEFT|CBRS_FLOAT_MULTI,
	   AFX_CBRS_REGULAR_TABS,AFX_CBRS_RESIZE))
	{
		return;
	}

	EnableDocking(CBRS_ALIGN_LEFT);
	pMainFrame->DockPane(this);

	//ShowPane(TRUE,TRUE,TRUE);

	DockToWindow((CDockablePane*)m_pLeftWnd,CBRS_BOTTOM);
}

BOOL XScene::InitTreeCtrl()
{
	if(m_TreeCtrl.Create(WS_CHILD|WS_VISIBLE|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS|TVS_EDITLABELS,CRect(0,0,0,0),this,ID_SCENETREE))
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

BOOL XScene::InitImageList()
{
	if(!m_ImageList.Create(20,20,ILC_COLOR32|ILC_MASK,0,1))
		return FALSE;

	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SCENE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUP));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_TemplateTYPE));

	return TRUE;
}

void XScene::SaveData(CArchive& arch)
{
	XScenePaneData::SaveData(this,arch);
}
void XScene::GetData(CArchive& arch)
{
	XScenePaneData::GetData(this,arch);
}

void XScene::ReloadInterface()
{
	CString szTemp;

	if(m_szTitle==_T("接管预案"))
	{
		szTemp=_C(_T("238"),_T("接管预案"));
		SetWindowText(szTemp);
	}
	else if(m_szTitle==_T("拼接场景"))
	{
		szTemp=_C(_T("349"),_T("拼接场景"));
		SetWindowText(szTemp);
	}
}

void XScene::OnNMRClickTree(NMHDR *pNMHDR,LRESULT *pResult)
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

	m_TempItem=hItem;

	m_TreeCtrl.SelectItem(hItem);
	DWORD dwData=m_TreeCtrl.GetItemData(hItem);

	if(dwData==SCENETYPE_GROUP)
	{
		ShowGroupMenu();
	}
	else if(dwData==SCENETYPE_SCENE)
	{
		ShowSceneMenu();
	}
	else if(dwData==SCENETYPE_SPLIT)
	{
		ShowSplitMenu();
	}
	else if(dwData==SCENETYPE_SPLITGROUP)
	{
		ShowSplitGroup();
	}


}

void XScene::ShowSplitGroup()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,ID_ALTERSPLITGROUP,_C(_T("55"),_T("修改")));
	menu.AppendMenu(MF_STRING,ID_DELSPLITGROUP,_C(_T("57"),_T("删除")));
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	menu.DestroyMenu();
}

void XScene::ShowSplitMenu()
{
	CPoint point;
	GetCursorPos(&point);

	if(NULL==m_TempItem)
		return;

	CString szSceneName=m_TreeCtrl.GetItemText(m_TempItem);
	BOOL bFlag=FALSE;
	auto& MapScene=m_pDelegate->GetMapSplitScene();
	if(MapScene.find(szSceneName)!=MapScene.end())
	{
		XSplitScene* pInfo=MapScene[szSceneName];
		if(pInfo->m_szSceneGroup!=_T(""))
		{
			bFlag=TRUE;
		}
	}

	CMenu menu;
	menu.CreatePopupMenu();
	if(bFlag)
	{
		menu.AppendMenu(MF_STRING,ID_REMOVEFROMSGROUP,_C(_T("250"),_T("移出")));
	}
	
	menu.AppendMenu(MF_STRING,ID_DELSPLITSCENE,_C(_T("57"),_T("删除")));
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	menu.DestroyMenu();
}

void XScene::ShowGroupMenu()
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,ID_ALTERSCENE,_C(_T("55"),_T("修改")));
	menu.AppendMenu(MF_STRING,ID_DELSCENE,_C(_T("57"),_T("删除")));

	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	menu.DestroyMenu();
}

void XScene::ShowSceneMenu()
{
	CPoint point;
	GetCursorPos(&point);

	if(NULL==m_TempItem)
		return;

	CString szSceneName=m_TreeCtrl.GetItemText(m_TempItem);
	BOOL bFlag=FALSE;
	if(m_MapScene.find(szSceneName)!=m_MapScene.end())
	{
		XSceneInfo* pInfo=m_MapScene[szSceneName];
		if(pInfo->GetSceneGroupName()!=_T(""))
		{
			bFlag=TRUE;
		}
	}


	CMenu menu;
	menu.CreatePopupMenu();

	if(bFlag)
	{
		menu.AppendMenu(MF_STRING,ID_REMOVE,_C(_T("250"),_T("移出"))+_T("(&R)"));
	}

	menu.AppendMenu(MF_STRING,ID_ALTERSCENE,_C(_T("55"),_T("修改"))+_T("(&A)"));
	menu.AppendMenu(MF_STRING,ID_DELSCENE,_C(_T("57"),_T("删除"))+_T("(&D)"));

	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	menu.DestroyMenu();
}

void XScene::Remove()
{
	//移出组
	if(NULL==m_TempItem)
		return;


	HTREEITEM hParent=m_TreeCtrl.GetParentItem(m_TempItem);
	if(NULL==hParent)
		return;
	CString szGroupName=m_TreeCtrl.GetItemText(hParent);

	CString szSceneName=m_TreeCtrl.GetItemText(m_TempItem);
	//删除节点
	m_TreeCtrl.DeleteItem(m_TempItem);
	//插入树
	HTREEITEM hItem=AddRootItem(szSceneName,(DWORD_PTR)SCENETYPE_SCENE);
	SaveItem(szSceneName,hItem);
	//设置组名称为空
	if(m_MapScene.find(szSceneName)!=m_MapScene.end())
	{
		XSceneInfo* pInfo=m_MapScene[szSceneName];
		pInfo->SetSceneGroupName(_T(""));
	}
	//判断还有没用组员
	BOOL bFlag=FALSE;
	for(auto& map:m_MapScene)
	{
		XSceneInfo* pInfo=map.second;
		if(pInfo->GetSceneGroupName()==szGroupName)
		{
			bFlag=TRUE;
			break;
		}
	}
	if(!bFlag)
	{
		//删除组
		m_TreeCtrl.DeleteItem(hParent);
		auto iter=m_MapItem.find(szGroupName);
		if(iter!=m_MapItem.end())
		{
			m_MapItem.erase(iter);
		}
		//从组集合中删除
		auto iterGroup=m_MapSceneGroup.find(szGroupName);
		if(iterGroup!=m_MapSceneGroup.end())
		{
			XSceneGroupInfo* pInfo=iterGroup->second;
			m_MapSceneGroup.erase(iterGroup);
			delete pInfo;
		}
	}
}

void XScene::AlterSplitScene()
{
	if(NULL==m_TempItem)
		return;

	//更改名称(现在无法更改场景名称)

}

void XScene::RemoveFromSplitGroup()
{
	if(NULL==m_TempItem)
		return;

	HTREEITEM hParent=m_TreeCtrl.GetParentItem(m_TempItem);
	if(NULL!=hParent)
	{
		//移出完时 删除组
		CString szGroupName=m_TreeCtrl.GetItemText(hParent);
		XConstantData::GetInstance()->SetSplitGroup(szGroupName);
	}

	//从组中移出
	CString szItem=m_TreeCtrl.GetItemText(m_TempItem);
	XSendDataManage::GetInstance()->AddSendDataOfSetSceneGroup(szItem,_T(""),TRUE);
}

void XScene::AlterSplitGroup()
{
	if(NULL==m_TempItem)
		return;


	DWORD dwData=m_TreeCtrl.GetItemData(m_TempItem);
	XConstantData::GetInstance()->SetSceneType(dwData);

	//修改组名称
	CString szGroupName=m_TreeCtrl.GetItemText(m_TempItem);
	XConstantData::GetInstance()->SetSplitGroup(szGroupName);


	CEdit* pEdit=m_TreeCtrl.EditLabel(m_TempItem);
}

void XScene::DelSplitGroup()
{
	if(NULL==m_TempItem)
		return;

	CString szItem=m_TreeCtrl.GetItemText(m_TempItem);
	XConstantData::GetInstance()->SetSplitGroup(szItem);

	auto& MapScene=m_pDelegate->GetMapSplitScene();
	for(auto& scene:MapScene)
	{
		XSplitScene* pScene=scene.second;
		if(pScene->m_szSceneGroup==szItem)
		{
			XSendDataManage::GetInstance()->AddSendDataOfSetSceneGroup(pScene->GetSceneName(),_T(""),TRUE);
		}
	}

	//如果组里没有


}

void XScene::DelSplitScene()
{
	if(NULL==m_TempItem)
		return;

	//删除场景
	DWORD dwData=m_TreeCtrl.GetItemData(m_TempItem);
	if(dwData==SCENETYPE_SPLIT)
	{
		CString szItem=m_TreeCtrl.GetItemText(m_TempItem);
		XSendDataManage::GetInstance()->AddSendDataOfDeleteSplitScene(szItem);
	}
}

void XScene::DeleteSplitScene(HTREEITEM hItem)
{
	if(NULL==hItem)
		return;

	m_TreeCtrl.DeleteItem(hItem);
}

void XScene::AlterScene()
{
	if(NULL==m_TempItem)
		return;

	DWORD dwData=m_TreeCtrl.GetItemData(m_TempItem);
	XConstantData::GetInstance()->SetSceneType(dwData);
	if(dwData==SCENETYPE_GROUP)
	{
		//修改组名称
		CString szGroupName=m_TreeCtrl.GetItemText(m_TempItem);
		XConstantData::GetInstance()->SetOldSceneName(szGroupName);
	}
	else if(dwData==SCENETYPE_SCENE)
	{
		CString szSceneName=m_TreeCtrl.GetItemText(m_TempItem);

		//先检查文件是否存在
		CString szFilePath=HandlePath::GetPlanPath(szSceneName);
		if(!PathFileExists(szFilePath))
		{
			_M(_T("249"),_T("预案文件不存在！"),MB_OK);
			return;
		}
		XConstantData::GetInstance()->SetOldSceneName(szSceneName);
	}
	CEdit* pEdit=m_TreeCtrl.EditLabel(m_TempItem);
}

void XScene::DelScene()
{
	if(NULL==m_TempItem)
		return;

	DWORD dwData=m_TreeCtrl.GetItemData(m_TempItem);
	if(dwData==SCENETYPE_GROUP)
	{
		//直接删除组(组员插入到后面)
		CString szGroupName=m_TreeCtrl.GetItemText(m_TempItem);
		
		XSceneGroupInfo* pInfo=NULL;
		auto iter=m_MapSceneGroup.find(szGroupName);
		if(iter!=m_MapSceneGroup.end())
		{
			pInfo=iter->second;
			if(m_MapItem.find(pInfo->GetGroupName())!=m_MapItem.end())
			{
				HTREEITEM hItem=m_MapItem[pInfo->GetGroupName()];
				m_TreeCtrl.DeleteItem(hItem);
			}

			m_MapSceneGroup.erase(iter);
			delete pInfo;
		}
		
		if(NULL==pInfo)
			return;

		//删除组员节点
		for(auto& map:m_MapScene)
		{
			XSceneInfo* pInfo=map.second;
			CString szSceneName=pInfo->GetSceneName();
			if(pInfo->GetSceneGroupName()==szGroupName)
			{
				pInfo->SetSceneGroupName(_T(""));
				if(m_MapItem.find(szSceneName)!=m_MapItem.end())
				{
					HTREEITEM hItem=m_MapItem[szSceneName];
					m_TreeCtrl.DeleteItem(hItem);

					HTREEITEM hNewItem=AddRootItem(szSceneName,(DWORD_PTR)SCENETYPE_SCENE);
					SaveItem(szSceneName,hNewItem);
				}
			}
		}
	}
	else if(dwData==SCENETYPE_SCENE)
	{
		CString szSceneName=m_TreeCtrl.GetItemText(m_TempItem);
		HTREEITEM hItem=NULL;
		if(m_MapItem.find(szSceneName)!=m_MapItem.end())
		{
			hItem=m_MapItem[szSceneName];
		}

		if(NULL!=hItem)
		{
			//从集合中删除
			auto iter=m_MapScene.find(szSceneName);
			if(iter!=m_MapScene.end())
			{
				m_MapScene.erase(iter);
			}
			//从树中删除
			m_TreeCtrl.DeleteItem(hItem);

			//检查文件是否存在
			CString szFilePath=HandlePath::GetPlanPath(szSceneName);
			if(PathFileExists(szFilePath))
			{
				::DeleteFile(szFilePath);
			}
		}
	}
}

void XScene::OnTvnEndlabeledit(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo=reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);

	CString szNewText=pTVDispInfo->item.pszText;
	szNewText.Trim();
	if(szNewText.IsEmpty())
	{
		*pResult=0;
		return;
	}

	int nData=XConstantData::GetInstance()->GetSceneType();
	if(nData==0)
	{
		*pResult=0;
		return;
	}


	switch(nData)
	{
		case SCENETYPE_SCENE:
			{
				CString szOldName=XConstantData::GetInstance()->GetOldSceneName();
				if(_T("")==szOldName)
					return;

				//先判断重名
				if(!DecidedNameExist(szNewText,SCENETYPE_SCENE))
				{
					*pResult=0;
					_M(_T("161"),_T("名称已存在！"),MB_OK);
					return;
				}
				//先更改文件名称
				CString szOldFilePath=HandlePath::GetPlanPath(szOldName);
				CString szNewFilePath=HandlePath::GetPlanPath(szNewText);

				CFile::Rename(szOldFilePath,szNewFilePath);
				//处理集合
				XSceneInfo* pInfo=NULL;
				auto iter=m_MapScene.find(szOldName);
				if(iter!=m_MapScene.end())
				{
					pInfo=m_MapScene[szOldName];
					//从集合中删除
					m_MapScene.erase(szOldName);
				}
				//更改名称
				pInfo->SetSceneName(szNewText);
				//再添加到集合
				if(m_MapScene.find(szNewText)==m_MapScene.end())
				{
					m_MapScene.insert(std::pair<CString,XSceneInfo*>(szNewText,pInfo));
				}
				else
				{
					m_MapScene[szNewText]=pInfo;
				}

				//更改节点集合
				HTREEITEM hItem=NULL;
				auto iterItem=m_MapItem.find(szOldName);
				if(iterItem!=m_MapItem.end())
				{
					hItem=m_MapItem[szOldName];
					m_MapItem.erase(szOldName);
				}

				SaveItem(szNewText,hItem);
			}
			break;
		case SCENETYPE_GROUP:
			{
				CString szOldName=XConstantData::GetInstance()->GetOldSceneName();
				if(_T("")==szOldName)
					return;

				//更改组名称
			    //先判断重名
				if(!DecidedNameExist(szNewText,SCENETYPE_GROUP))
				{
					*pResult=0;
					_M(_T("161"),_T("名称已存在！"),MB_OK);
					return;
				}
				//查找
				XSceneGroupInfo* pInfo=NULL;
				auto iter=m_MapSceneGroup.find(szOldName);
				if(iter!=m_MapSceneGroup.end())
				{
					pInfo=iter->second;
					m_MapSceneGroup.erase(iter);
				}
				if(NULL==pInfo)
				{
					*pResult=0;
					return;
				}
				pInfo->SetGroupName(szNewText);
				//在插入到集合
				if(m_MapSceneGroup.find(szNewText)==m_MapSceneGroup.end())
				{
					m_MapSceneGroup.insert(std::pair<CString,XSceneGroupInfo*>(szNewText,pInfo));
				}
				else
				{
					m_MapSceneGroup[szNewText]=pInfo;
				}

				//更改组员的组名称
				for(auto& map:m_MapScene)
				{
					XSceneInfo* pInfo=map.second;
					if(pInfo->GetSceneGroupName()==szOldName)
						pInfo->SetSceneGroupName(szNewText);
				}

				//更改节点集合
				HTREEITEM hItem=NULL;
				auto iterItem=m_MapItem.find(szOldName);
				if(iterItem!=m_MapItem.end())
				{
					hItem=m_MapItem[szOldName];
					m_MapItem.erase(szOldName);
				}

				SaveItem(szNewText,hItem);
			}
			break;
		case SCENETYPE_SPLITGROUP:
			{
				CString szSplitGroup=XConstantData::GetInstance()->GetSplitGroup();

				//TRACE(_T("AlterSplitGroup\n"));
				//判断重名
				if(DecidedNameExist(szNewText,SCENETYPE_SPLITGROUP))
				{
					*pResult=0;
					_M(_T("161"),_T("名称已存在！"),MB_OK);
					return;
				}

				//先更改组中场景
				auto& mapSplitScene=m_pDelegate->GetMapSplitScene();
				for(auto& scene:mapSplitScene)
				{
					XSplitScene* pScene=scene.second;
					if(pScene->m_szSceneGroup==szSplitGroup)
					{
						XSendDataManage::GetInstance()->AddSendDataOfSetSceneGroup(pScene->GetSceneName(),szNewText,TRUE);
					}
				}
				//往后就改了 

			}
			break;
		default:
			break;
	}


	//返回1 会直接更改名称
	*pResult=1;	
}

void XScene::OnDblclkTree(NMHDR *pNMHDR,LRESULT *pResult)
{
	HTREEITEM hItem=m_TreeCtrl.GetSelectedItem();

	//if(hItem==NULL)
	//	return;

	//DWORD dwData=m_TreeCtrl.GetItemData(hItem);
	//if(dwData==SCENETYPE_GROUP)
	//{
	//	*pResult=0;
	//	return;
	//}
	//	
	//CString szSceneName=m_TreeCtrl.GetItemText(hItem);
	//XConstantData::GetInstance()->SetOpenSceneName(szSceneName);
	//m_pDelegate->OpenScene(dwData);

	*pResult=0;
}

void XScene::AddSplitScene(CString szName,CString szGroup)
{
	//TRACE(_T("AddSplitScene=%s,Group=%s\n"),szName,szGroup);


	auto& MapSplitScene=m_pDelegate->GetMapSplitScene();
	auto& MapSceneGroup=m_pDelegate->GetMapSplitSceneGroup();
	if(MapSceneGroup.find(szGroup)==MapSceneGroup.end())
	{
		if(MapSplitScene.find(szName)!=MapSplitScene.end())
		{
			XSplitScene* pScene=MapSplitScene[szName];

			HTREEITEM hItem=AddRootItem(pScene->GetSceneName(),(DWORD_PTR)(SCENETYPE_SPLIT));
			SetItemRoot(hItem);
			pScene->m_hItem=hItem;

			//插入拼接墙
			auto& VecWallList=pScene->GetVecWallList();
			for(auto& szWall:VecWallList)
			{
				AddChildItem(szWall,(DWORD_PTR)(SCENETYPE_SPLITWALL));
			}
		}
	}
	else
	{
		HTREEITEM hItem=MapSceneGroup[szGroup];

		SetItemRoot(hItem);
		//auto& MapScene=m_pDelegate->GetMapSplitScene();
		if(MapSplitScene.find(szName)!=MapSplitScene.end())
		{
			XSplitScene* pScene=MapSplitScene[szName];
			HTREEITEM hSceneItem=AddChildItem(szName,SCENETYPE_SPLIT);
			pScene->m_hItem=hSceneItem;

			SetItemRoot(hSceneItem);
			auto& VecWall=pScene->GetVecWallList();
			for(auto& szWall:VecWall)
			{
				AddChildItem(szWall,SCENETYPE_SPLITWALL);
			}
		}
	}
}

void XScene::InitSceneOfSplit()
{
	//TRACE(_T("Split\n"));
	m_szTitle=_C(_T("349"),_T("拼接场景"));
	SetWindowText(m_szTitle);
	m_TreeCtrl.DeleteAllItems();

	auto& MapSceneGroup=m_pDelegate->GetMapSplitSceneGroup();
	auto& MapSplitScene=m_pDelegate->GetMapSplitScene();
	for(auto& group:MapSceneGroup)
	{
		CString szGroup=group.first;
		HTREEITEM hItemGroup=AddRootItem(szGroup,SCENETYPE_SPLITGROUP);
		MapSceneGroup[szGroup]=hItemGroup;
		SetItemRoot(hItemGroup);

		for(auto& map:MapSplitScene)
		{
			XSplitScene* pScene=map.second;
			if(pScene->m_szSceneGroup==szGroup)
			{
				SetItemRoot(hItemGroup);
				HTREEITEM hItemScene=AddChildItem(pScene->GetSceneName(),SCENETYPE_SPLIT);
				pScene->m_hItem=hItemScene;

				//插入拼接墙
				SetItemRoot(hItemScene);
				auto& VecWallList=pScene->GetVecWallList();
				for(auto& szWall:VecWallList)
				{
					HTREEITEM hItem=AddChildItem(szWall,SCENETYPE_SPLITWALL);
				}
			}
		}
		m_TreeCtrl.Expand(hItemGroup,TVE_EXPAND);
	}

	//插入没有组的
	for(auto& map:MapSplitScene)
	{
		XSplitScene* pScene=map.second;
		if(pScene->m_szSceneGroup==_T(""))
		{
			HTREEITEM hItemScene=AddRootItem(pScene->GetSceneName(),SCENETYPE_SPLIT);
			pScene->m_hItem=hItemScene;

			//插入拼接墙
			SetItemRoot(hItemScene);
			auto& VecWallList=pScene->GetVecWallList();
			for(auto& szWall:VecWallList)
			{
				HTREEITEM hItem=AddChildItem(szWall,SCENETYPE_SPLITWALL);
			}
		}
	}
}

void XScene::InitSceneOfTakeOver()
{
	m_szTitle=_C(_T("238"),_T("接管预案"));
	SetWindowText(m_szTitle);
	m_TreeCtrl.DeleteAllItems();

	//初始化场景树
	for(auto& map:m_MapSceneGroup)
	{
		XSceneGroupInfo* pInfo=map.second;
		CString szGroupName=pInfo->GetGroupName();

		HTREEITEM hFrontItem=GetItemWhere();
		HTREEITEM hGroupItem=AddRootItem(szGroupName,(DWORD_PTR)(SCENETYPE_GROUP),hFrontItem);
		SetItemRoot(hGroupItem);
		SaveItem(szGroupName,hGroupItem);

		for(auto& map:m_MapScene)
		{
			XSceneInfo* pSceneInfo=map.second;
			if(pSceneInfo->GetSceneGroupName()==szGroupName)
			{
				CString szSceneName=pSceneInfo->GetSceneName();
				HTREEITEM hSceneItem=AddChildItem(szSceneName,(DWORD_PTR)SCENETYPE_SCENE);
				SaveItem(szSceneName,hSceneItem);
			}
		}
		m_TreeCtrl.Expand(hGroupItem,TVE_EXPAND);
	}
	//不在组里的
	for(auto& map:m_MapScene)
	{
		XSceneInfo* pInfo=map.second;
		CString szGroupName=pInfo->GetSceneGroupName();
		if(_T("")==szGroupName)
		{
			HTREEITEM hItem=AddRootItem(pInfo->GetSceneName(),(DWORD_PTR)SCENETYPE_SCENE);

			SaveItem(pInfo->GetSceneName(),hItem);
		}
	}
}



//void XScene::InitScene()
//{
//	m_TreeCtrl.DeleteAllItems();
//
//	//初始化场景树
//	for(auto& map:m_MapSceneGroup)
//	{
//		XSceneGroupInfo* pInfo=map.second;
//		CString szGroupName=pInfo->GetGroupName();
//
//		HTREEITEM hFrontItem=GetItemWhere();
//		HTREEITEM hGroupItem=AddRootItem(szGroupName,(DWORD_PTR)(SCENETYPE_GROUP),hFrontItem);
//		SetItemRoot(hGroupItem);
//		SaveItem(szGroupName,hGroupItem);
//		
//		for(auto& map:m_MapScene)
//		{
//			XSceneInfo* pSceneInfo=map.second;
//			if(pSceneInfo->GetSceneGroupName()==szGroupName)
//			{
//				CString szSceneName=pSceneInfo->GetSceneName();
//				HTREEITEM hSceneItem=AddChildItem(szSceneName,(DWORD_PTR)SCENETYPE_SCENE);
//				SaveItem(szSceneName,hSceneItem);
//			}
//		}
//		m_TreeCtrl.Expand(hGroupItem,TVE_EXPAND);
//	}
//	//不在组里的
//	for(auto& map:m_MapScene)
//	{
//		XSceneInfo* pInfo=map.second;
//		CString szGroupName=pInfo->GetSceneGroupName();
//		if(_T("")==szGroupName)
//		{
//			HTREEITEM hItem=AddRootItem(pInfo->GetSceneName(),(DWORD_PTR)SCENETYPE_SCENE);
//
//			SaveItem(pInfo->GetSceneName(),hItem);
//		}
//	}
//
//}

void XScene::ClearSceneTree()
{
	//在清理
	m_TreeCtrl.DeleteAllItems();
	ClearMapItem();
}

void XScene::AddSceneToTree(CString szName)
{
	//新建 添加到集合
	XSceneInfo* pInfo=new XSceneInfo;
	pInfo->SetSceneName(szName);

	if(m_MapScene.find(szName)==m_MapScene.end())
	{
		m_MapScene.insert(std::pair<CString,XSceneInfo*>(szName,pInfo));
	}
	else
	{
		m_MapScene[szName]=pInfo;
	}

	HTREEITEM hItem=AddRootItem(szName,SCENETYPE_SCENE);
	//保存树节点
	SaveItem(szName,hItem);
}

void XScene::AddSplitGroup(CString szGroupName,HTREEITEM hItem)
{
	if(_T("")==szGroupName)
		return;

	auto& MapSplitGroup=m_pDelegate->GetMapSplitSceneGroup();	
	HTREEITEM hNewItem=AddRootItem(szGroupName,SCENETYPE_SPLITGROUP,hItem);
	if(MapSplitGroup.find(szGroupName)!=MapSplitGroup.end())
	{
		MapSplitGroup[szGroupName]=hNewItem;
		//MapSplitGroup.insert(std::pair<CString,HTREEITEM>(szGroupName,hNewItem));
	}
}

void XScene::AddSplitSceneAtLast(CString szSceneName)
{
	if(_T("")==szSceneName)
		return;

	auto& MapScene=m_pDelegate->GetMapSplitScene();
	if(MapScene.find(szSceneName)!=MapScene.end())
	{
		XSplitScene* pScene=MapScene[szSceneName];
		
		HTREEITEM hItem=AddRootItem(szSceneName,SCENETYPE_SPLIT);
		pScene->m_hItem=hItem;

		//添加墙
		SetItemRoot(hItem);
		auto& VecWall=pScene->GetVecWallList();
		for(auto& szWall:VecWall)
		{
			AddChildItem(szWall,SCENETYPE_SPLITWALL);
		}
	}
}

void XScene::DelSplitSceneByItem(CString szSceneName)
{
	if(_T("")==szSceneName)
		return;

	auto& MapScene=m_pDelegate->GetMapSplitScene();
	if(MapScene.find(szSceneName)!=MapScene.end())
	{
		XSplitScene* pScene=MapScene[szSceneName];
		HTREEITEM hItem=pScene->m_hItem;
		if(NULL!=hItem)
			m_TreeCtrl.DeleteItem(hItem);
	}
}

void XScene::DelSplitGroupByItem(HTREEITEM hItem)
{
	if(NULL==hItem)
		return;
	m_TreeCtrl.DeleteItem(hItem);
}

void XScene::AddSplitSceneToGroup(CString szGroupName,CString szSceneName)
{
	//TRACE(_T("AddSplitSceneToGroup=%s,G=%s\n"),szSceneName,szGroupName);

	if(_T("")==szGroupName||_T("")==szSceneName)
		return;

	HTREEITEM hItem=NULL;
	auto& MapSplitGroup=m_pDelegate->GetMapSplitSceneGroup();
	if(MapSplitGroup.find(szGroupName)!=MapSplitGroup.end())
	{
		hItem=MapSplitGroup[szGroupName];
	}

	if(NULL==hItem)
		return;

	SetItemRoot(hItem);
	auto& MapScene=m_pDelegate->GetMapSplitScene();
	if(MapScene.find(szSceneName)!=MapScene.end())
	{
		XSplitScene* pScene=MapScene[szSceneName];
		HTREEITEM hSceneItem=AddChildItem(szSceneName,SCENETYPE_SPLIT);
		pScene->m_hItem=hSceneItem;

		SetItemRoot(hSceneItem);
		auto& VecWall=pScene->GetVecWallList();
		for(auto& szWall:VecWall)
		{
			AddChildItem(szWall,SCENETYPE_SPLITWALL);
		}
	}
	m_TreeCtrl.Expand(hItem,TVE_EXPAND);
}

void XScene::AddSplitGroup(HTREEITEM hItemFirst,HTREEITEM hItemSecond)
{
	//TRACE(_T("SplitGroup\n"));
	//添加组
	if(NULL==hItemSecond||NULL==hItemSecond)
		return;

	if(hItemFirst==hItemSecond)
		return;

	DWORD dwFirstData=m_TreeCtrl.GetItemData(hItemFirst);
	CString szFirstName=m_TreeCtrl.GetItemText(hItemFirst);

	HTREEITEM hFirstParent=m_TreeCtrl.GetParentItem(hItemFirst);
	if(NULL==hFirstParent)
	{
		//第一个不在组中
		if(dwFirstData==SCENETYPE_SPLITGROUP)
			return;

		//拖拽不在组里
		DWORD dwSecondData=m_TreeCtrl.GetItemData(hItemSecond);
		HTREEITEM hSecondParent=m_TreeCtrl.GetParentItem(hItemSecond);
		if(NULL==hSecondParent)
		{
			//被托也不在组中 添加组
			CString szSecondName=m_TreeCtrl.GetItemText(hItemSecond);
			if(dwSecondData==SCENETYPE_SPLIT)
			{
				CString szFrontName=_C(_T("105"),_T("分组"));
				CString szGroupName=GetSplitGroupNameByFrontName(szFrontName);

				XSendDataManage::GetInstance()->AddSendDataOfSetSceneGroup(szFirstName,szGroupName);
				XSendDataManage::GetInstance()->AddSendDataOfSetSceneGroup(szSecondName,szGroupName);
			}
			else if(dwSecondData==SCENETYPE_SPLITGROUP)
			{
				//拖拽到组节点
				CString szSecondName=m_TreeCtrl.GetItemText(hItemSecond);
				XSendDataManage::GetInstance()->AddSendDataOfSetSceneGroup(szFirstName,szSecondName);
			}
		}
	}
	else
	{

	}

	//拖拽出组、从组拖拽到另一个组 暂时没添加



}

void XScene::AddGroup(HTREEITEM hItemFirst,HTREEITEM hItemSecond)
{
	//添加组
	if(NULL==hItemSecond||NULL==hItemSecond)
		return;

	if(hItemFirst==hItemSecond)
		return;

	DWORD dwFirstData=m_TreeCtrl.GetItemData(hItemFirst);
	CString szFirstName=m_TreeCtrl.GetItemText(hItemFirst);

	HTREEITEM hFirstParent=m_TreeCtrl.GetParentItem(hItemFirst);
	if(NULL==hFirstParent)
	{
		if(dwFirstData==SCENETYPE_GROUP)
			return;

		//拖拽不在组里
		DWORD dwSecondData=m_TreeCtrl.GetItemData(hItemSecond);
		HTREEITEM hSecondParent=m_TreeCtrl.GetParentItem(hItemSecond);
		if(NULL==hSecondParent)
		{
			//被拖拽不在组里
			CString szSecondName=m_TreeCtrl.GetItemText(hItemSecond);
			if(dwSecondData==SCENETYPE_SCENE)
			{
				//TRACE(_T("SCENE1\n"));
				//两者添加组
				CString szFrontName=_C(_T("105"),_T("分组"));
				CString szGroupName=GetGroupNameByFrontName(szFrontName);
				//插入树(先计算插在哪里)
				HTREEITEM hNewItem=GetItemWhere();
				HTREEITEM hGroupItem=AddRootItem(szGroupName,(DWORD_PTR)SCENETYPE_GROUP,hNewItem);
				SetItemRoot(hGroupItem);
				//保存组节点
				SaveItem(szGroupName,hGroupItem);
				//删除两个
				m_TreeCtrl.DeleteItem(hItemFirst);
				m_TreeCtrl.DeleteItem(hItemSecond);
				//插在组里
				HTREEITEM hItem1=AddChildItem(szFirstName,(DWORD_PTR)SCENETYPE_SCENE);
				SaveItem(szFirstName,hItem1);
				SetSceneGroupName(szFirstName,szGroupName);
				HTREEITEM hItem2=AddChildItem(szSecondName,(DWORD_PTR)SCENETYPE_SCENE);
				SaveItem(szSecondName,hItem2);
				SetSceneGroupName(szSecondName,szGroupName);

				//插在组集合
				XSceneGroupInfo* pInfo=new XSceneGroupInfo;
				pInfo->SetGroupName(szGroupName);
				if(m_MapSceneGroup.find(szGroupName)==m_MapSceneGroup.end())
				{
					m_MapSceneGroup.insert(std::pair<CString,XSceneGroupInfo*>(szGroupName,pInfo));
				}
				else
				{
					m_MapSceneGroup[szGroupName]=pInfo;
				}
			}
			else if(dwSecondData==SCENETYPE_GROUP)
			{
				//拖拽到组节点,添加到组
				//TRACE(_T("GROUP1\n"));
				HTREEITEM hGroupItem=NULL;
				if(m_MapItem.find(szSecondName)!=m_MapItem.end())
				{
					hGroupItem=m_MapItem[szSecondName];
				}

				if(NULL==hGroupItem)
					return;
				SetItemRoot(hGroupItem);

				m_TreeCtrl.DeleteItem(hItemFirst);
				HTREEITEM hSceneItem=AddChildItem(szFirstName,(DWORD_PTR)SCENETYPE_SCENE);
				SaveItem(szFirstName,hSceneItem);

				if(m_MapScene.find(szFirstName)!=m_MapScene.end())
				{
					XSceneInfo* pInfo=m_MapScene[szFirstName];
					pInfo->SetSceneGroupName(szSecondName);
				}
			}
		}
		else
		{
			//被拖拽在组里(拖到组里)
			if(dwSecondData==SCENETYPE_SCENE)
			{
				//TRACE(_T("SCENE2\n"));
				CString szGroup=m_TreeCtrl.GetItemText(hSecondParent);
				SetItemRoot(hSecondParent);
				m_TreeCtrl.DeleteItem(hItemFirst);
				HTREEITEM hSceneItem=AddChildItem(szFirstName,(DWORD_PTR)SCENETYPE_SCENE);
				SaveItem(szFirstName,hSceneItem);

				if(m_MapScene.find(szFirstName)!=m_MapScene.end())
				{
					XSceneInfo* pInfo=m_MapScene[szFirstName];
					pInfo->SetSceneGroupName(szGroup);
				}
			}
			else if(dwSecondData==SCENETYPE_GROUP)
			{
				//TRACE(_T("GROUP2\n"));
			}
		}
	}
	else
	{
		//在组里
		//TRACE(_T("In Group\n"));
		DWORD dwSecondData=m_TreeCtrl.GetItemData(hItemSecond);
		HTREEITEM hSecondParent=m_TreeCtrl.GetParentItem(hItemSecond);
		if(NULL==hSecondParent)
		{
			//被拖拽为外面(从组里移除)
			//TRACE(_T("out Group\n"));
			//先把组名称置空
			if(m_MapScene.find(szFirstName)!=m_MapScene.end())
			{
				XSceneInfo* pInfo=m_MapScene[szFirstName];
				pInfo->SetSceneGroupName(_T(""));
			}
			//删除
			m_TreeCtrl.DeleteItem(hItemFirst);
			//插入到后面
			HTREEITEM hItem=AddRootItem(szFirstName,(DWORD_PTR)SCENETYPE_SCENE,NULL);
			SaveItem(szFirstName,hItem);
		}
		else
		{
			//TRACE(_T("In Group2\n"));
			//添加到其他组

		}
	}
}

HTREEITEM XScene::GetItemWhere()
{
	//
	int nSize=m_MapSceneGroup.size();
	if(nSize==0)
	{
		return NULL;
	}
	else
	{
		auto iter=m_MapSceneGroup.end();
		iter--;

		CString szName=iter->first;
		return m_MapItem[szName];
	}
}

void XScene::SaveItem(CString szName,HTREEITEM hItem)
{
	if(NULL==hItem)
		return;

	if(m_MapSceneGroup.find(szName)==m_MapSceneGroup.end())
	{
		m_MapItem.insert(std::pair<CString,HTREEITEM>(szName,hItem));
	}
	else
	{
		m_MapItem[szName]=hItem;
	}
}

void XScene::SetSceneGroupName(CString szName,CString szGroupName)
{
	if(m_MapScene.find(szName)!=m_MapScene.end())
	{
		XSceneInfo* pInfo=m_MapScene[szName];
		pInfo->SetSceneGroupName(szGroupName);
	}
}

CString XScene::GetSplitGroupNameByFrontName(CString szName)
{
	CString szTemp;

	int n=1;
	while(1)
	{
		szTemp.Format(_T("%d"),n);
		szTemp=szName+szTemp;

		auto& MapSplitGroup=m_pDelegate->GetMapSplitSceneGroup();
		if(MapSplitGroup.find(szTemp)==MapSplitGroup.end())
			break;
		n++;
	}
	return szTemp;
}

CString XScene::GetGroupNameByFrontName(CString szName)
{
	CString szTemp;

	int n=1;
	while(1)
	{
		szTemp.Format(_T("%d"),n);
		szTemp=szName+szTemp;

		MAP_SCENEGROUP::iterator iter=m_MapSceneGroup.find(szTemp);
		if(iter==m_MapSceneGroup.end())
			break;
		n++;
	}
	return szTemp;
}

void XScene::OpenScene(int nData)
{
	m_pDelegate->OpenScene(nData);
}

//////////////////////////////////////////////////////////////////////////
HTREEITEM XScene::AddRootItem(CString szRoot,int nType/*=0*/,HTREEITEM hItem/*=NULL*/)
{
	CString szCategories=szRoot;

	HTREEITEM item=NULL;
	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent=TVI_ROOT;
	//添加在哪里
	switch(nType)
	{
		case SCENETYPE_SCENE:
		case SCENETYPE_SPLIT:
			{
				tvinsert.hInsertAfter=TVI_LAST;
			}
			break;
		case SCENETYPE_GROUP:
		case SCENETYPE_SPLITGROUP:
			{
				if(NULL==hItem)
				{
					tvinsert.hInsertAfter=TVI_FIRST;
				}
				else
				{
					tvinsert.hInsertAfter=hItem;
				}
			}
			break;
		default:
			break;
	}

	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE;
	tvinsert.item.cChildren=1;
	tvinsert.item.pszText=szCategories.GetBuffer();
	tvinsert.item.iImage=0;
	tvinsert.item.iSelectedImage=0;
	item=m_TreeCtrl.InsertItem(&tvinsert);
	szCategories.ReleaseBuffer();

	m_TreeCtrl.SetItemData(item,(DWORD_PTR)nType);
	switch(nType)
	{
		case SCENETYPE_SCENE:
		case SCENETYPE_SPLIT:
			m_TreeCtrl.SetItemImage(item,0,0);
			break;
		case SCENETYPE_GROUP:
		case SCENETYPE_SPLITGROUP:
			m_TreeCtrl.SetItemImage(item,1,1);
			break;
		default:
			break;
	}

	return item;
}

void XScene::SetItemRoot(HTREEITEM h)
{
	m_hRootItem=h;
}

HTREEITEM XScene::GetItemRoot()
{
	return m_hRootItem;
}

HTREEITEM XScene::AddChildItem(CString szChild,int nType/*=0*/)
{
	CString szCategories=szChild;
	HTREEITEM item=NULL;
	TVINSERTSTRUCTW tvinsert;
	tvinsert.hParent=GetItemRoot();
	tvinsert.hInsertAfter=TVI_LAST;
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.cChildren=1;
	tvinsert.item.pszText=szCategories.GetBuffer();
	tvinsert.item.iImage=0;
	tvinsert.item.iSelectedImage=0;
	item=m_TreeCtrl.InsertItem(&tvinsert);
	szCategories.ReleaseBuffer();

	switch(nType)
	{
		case SCENETYPE_SPLITWALL:
			m_TreeCtrl.SetItemImage(item,2,2);
			break;
		case SCENETYPE_SCENE:
		case SCENETYPE_SPLIT:
			m_TreeCtrl.SetItemImage(item,0,0);
			break;
		default:
			break;
	}

	m_TreeCtrl.SetItemData(item,(DWORD_PTR)nType);
	return item;
}

BOOL XScene::DecidedNameExist(CString szName,int nType)
{
	switch(nType)
	{
		case SCENETYPE_SCENE:
			{
				for(auto& map:m_MapScene)
				{
					XSceneInfo* pInfo=map.second;
					if(szName==pInfo->GetSceneName())
						return FALSE;
				}
			}
			break;
		case SCENETYPE_GROUP:
			{
				for(auto& map:m_MapSceneGroup)
				{
					XSceneGroupInfo* pInfo=map.second;
					if(szName==pInfo->GetGroupName())
						return FALSE;
				}
			}
			break;
		case SCENETYPE_SPLITGROUP:
			{
				auto& MapSplitGroup=m_pDelegate->GetMapSplitSceneGroup();
				if(MapSplitGroup.find(szName)==MapSplitGroup.end())
					return FALSE;
			}
			break;
		default:
			break;
	}

	return TRUE;
}
