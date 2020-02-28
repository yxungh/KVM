#include "stdafx.h"
#include "XAddStore.h"
#include "XSetListCtrl.h"
#include "XTranslationManage.h"
#include "XDelegateAddStore.h"
#include "XNode.h"
#include "XMessageBox.h"
#include "XSendDataManage.h"


IMPLEMENT_DYNAMIC(XAddStore,XBaseDialog)

XAddStore::XAddStore(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAddStore::IDD,pParent)
{

}

XAddStore::~XAddStore()
{
}

void XAddStore::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_NODESTORE,m_NodeList);
	DDX_Control(pDX,IDC_STATIC_TITLE,m_TextTitle);
	DDX_Control(pDX,IDOK,m_BtnOK);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XAddStore,XBaseDialog)
	ON_BN_CLICKED(IDOK,&XAddStore::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK,IDC_LIST_NODESTORE,OnNMClickPowerList)
END_MESSAGE_MAP()


BOOL XAddStore::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XAddStore::Init()
{
	InitList();
	AddStoreList();
	ReloadInterface();
}

void XAddStore::ReloadInterface()
{
	SetWindowText(_C(_T("225"),_T("收藏")));
	m_BtnOK.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
	//m_TextTitle.SetLeft(TRUE);
	m_TextTitle.SetText(_C(_T("226"),_T("节点列表")),TRUE);

	CString szTemp=_T("");
	LVCOLUMN col;
	col.mask=LVCF_TEXT;
	szTemp=_C(_T("59"),_T("节点ID"));
	col.pszText=szTemp.GetBuffer();
	m_NodeList.SetColumn(0,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("60"),_T("节点名称"));
	col.pszText=szTemp.GetBuffer();
	m_NodeList.SetColumn(1,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("61"),_T("类型"));
	col.pszText=szTemp.GetBuffer();
	m_NodeList.SetColumn(2,&col);
	szTemp.ReleaseBuffer();
}

void XAddStore::InitList()
{
	XSetListCtrl::InitList(&m_NodeList,3,TRUE);

	m_NodeList.EnableToolTips(TRUE);
	m_NodeList.SetColumnWidth(0,70);
	m_NodeList.SetColumnWidth(1,142);
	m_NodeList.SetColumnWidth(2,70);
}

void XAddStore::AddStoreList()
{
	//去除已经存在的
	MAP_STORE& MapStore=m_pDelegate->GetMapStore();
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	for(auto& map:MapNode)
	{
		XNode* pNode=map.second;
		int nNodeID=pNode->GetNodeID();
		CString szNodeName=pNode->GetNodeName();
		int nNodeType=pNode->GetNodeType();

		if(MapStore.find(nNodeID)==MapStore.end())
		{
			AddStoreList(nNodeID,szNodeName,nNodeType);
		}
	}
}

void XAddStore::AddStoreList(int nNodeID,CString szNodeName,int nNodeType)
{
	int nCount=0;
	nCount=m_NodeList.GetItemCount();

	//if(nCount>17)
	//	m_PowerList.SetColumnWidth(0,219);
	//else
	//	m_PowerList.SetColumnWidth(0,235);

	m_NodeList.InsertItem(nCount,_T(""));

	SetListInfo(nCount,nNodeID,szNodeName,nNodeType);
}

void XAddStore::SetListInfo(int nCount,int nNodeID,CString szNodeName,int nNodeType)
{
	CString szNodeID;
	szNodeID.Format(_T("%d"),nNodeID);

	m_NodeList.SetItemText(nCount,0,szNodeID);
	m_NodeList.SetItemText(nCount,1,szNodeName);

	if(nNodeType==TERM_IN)
	{
		CString szTemp=_C(_T("62"),_T("输入"));
		m_NodeList.SetItemText(nCount,2,szTemp);
	}
	else if(nNodeType==TERM_OUT)
	{
		CString szTemp=_C(_T("63"),_T("输出"));
		m_NodeList.SetItemText(nCount,2,szTemp);
	}
}

void XAddStore::OnNMClickPowerList(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate=reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos=GetMessagePos();
	CPoint pt(dwPos);
	m_NodeList.ScreenToClient(&pt);

	UINT nFlag;
	int nItem=m_NodeList.HitTest(pt,&nFlag);

	BOOL bCheckState=m_NodeList.GetCheck(nItem);
	if(nFlag==LVHT_ONITEMSTATEICON)
	{
		//注意，bCheckState为TRUE，checkbox从勾选状态变为未勾选状态
		if(bCheckState)
		{
			auto iter=m_MapSelect.find(nItem);
			if(iter!=m_MapSelect.end())
			{
				m_MapSelect.erase(iter);
			}
		}
		else
		{
			CString szNodeID=XSetListCtrl::GetColumnText(&m_NodeList,nItem,0);
			int nNodeID=_ttoi(szNodeID);
			m_MapSelect.insert(std::pair<int,int>(nItem,nNodeID));
		}
	}
	else if(nFlag==LVHT_ONITEMLABEL||nFlag==LVHT_ONITEM)
	{
		//单击选项
		if(bCheckState)
		{
			XSetListCtrl::SetListCheckItemFalse(&m_NodeList,nItem);
			auto iter=m_MapSelect.find(nItem);
			if(iter!=m_MapSelect.end())
			{
				m_MapSelect.erase(iter);
			}
		}
		else
		{
			XSetListCtrl::SetListCheckItem(&m_NodeList,nItem);

			CString szNodeID=XSetListCtrl::GetColumnText(&m_NodeList,nItem,0);
			int nNodeID=_ttoi(szNodeID);
			m_MapSelect.insert(std::pair<int,int>(nItem,nNodeID));
		}
	}
	*pResult=0;
}

void XAddStore::OnBnClickedOk()
{
	if(m_MapSelect.size()==0)
	{
		_M(_T("227"),_T("选择要收藏节点！"),MB_OK);
		return;
	}

	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	for(auto& map:m_MapSelect)
	{
		int nNodeID=map.second;
		if(MapNode.find(nNodeID)!=MapNode.end())
		{
			XNode* pNode=MapNode[nNodeID];
			XSendDataManage::GetInstance()->AddSendDataOfAddStoreList(pNode,m_nUserID);
		}
	}
	XBaseDialog::OnOK();
}
