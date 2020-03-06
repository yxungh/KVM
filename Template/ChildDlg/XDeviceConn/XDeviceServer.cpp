#include "stdafx.h"
#include "XDeviceServer.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XSetListCtrl.h"
#include "XDelegateDeviceServer.h"
#include "XClient.h"
#include "XPower.h"
#include "XAlterPort.h"


// XDeviceServer �Ի���

IMPLEMENT_DYNAMIC(XDeviceServer,XBaseDialog)

XDeviceServer::XDeviceServer(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XDeviceServer::IDD,pParent)
{

}

XDeviceServer::~XDeviceServer()
{
}

void XDeviceServer::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_SERVERINFO,m_TextServerInfo);
	DDX_Control(pDX,IDC_STATIC_CONNCLIENT,m_TextConnCLient);
	DDX_Control(pDX,IDC_LIST_SERVERINFO,m_ServerInfoList);
	DDX_Control(pDX,IDC_LIST_CLIENTLIST,m_ClientList);

	DDX_Control(pDX,IDC_BTN_ALTER,m_BtnAlter);
	DDX_Control(pDX,IDC_BTN_ADD,m_BtnAddClient);
	DDX_Control(pDX,IDC_BTN_UPDATE,m_BtnUpdateClient);
	DDX_Control(pDX,IDC_BTN_DEL,m_BtnDelClient);
}


BEGIN_MESSAGE_MAP(XDeviceServer,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XDeviceServer::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XDeviceServer::Init()
{
	SetWindowText(_C(_T("359"),_T("�����")));

	InitListServer();
	InitListConnClient();

	InitListData();

	ReloadInterface();
}

void XDeviceServer::InitListServer()
{
	XSetListCtrl::InitList(&m_ServerInfoList,2,FALSE);
}

void XDeviceServer::InitListConnClient()
{	
	XSetListCtrl::InitList(&m_ClientList,3,FALSE);
}

void XDeviceServer::ReloadInterface()
{
	m_TextServerInfo.SetText(_C(_T("362"),_T("�������Ϣ")),TRUE);
	m_TextConnCLient.SetText(_C(_T("363"),_T("�ͻ����б�")),TRUE);

	m_BtnAlter.SetCaption(_C(_T("364"),_T("���Ķ˿�")));
	m_BtnAddClient.SetCaption(_C(_T("54"),_T("���")));
	m_BtnUpdateClient.SetCaption(_C(_T("55"),_T("�޸�")));
	m_BtnDelClient.SetCaption(_C(_T("57"),_T("ɾ��")));

	//////////////////////////////////////////////////////////////////////////
	CString szTemp=_T("");

	LVCOLUMN col;
	col.mask=LVCF_TEXT;

	szTemp=_C(_T("139"),_T("IP��ַ"));
	col.pszText=szTemp.GetBuffer();
	m_ServerInfoList.SetColumn(0,&col);
	szTemp.ReleaseBuffer();


	szTemp=_C(_T("140"),_T("�˿ں�"));
	col.pszText=szTemp.GetBuffer();
	m_ServerInfoList.SetColumn(1,&col);
	szTemp.ReleaseBuffer();

	//////////////////////////////////////////////////////////////////////////
	szTemp=_C(_T("72"),_T("����"));
	col.pszText=szTemp.GetBuffer();
	m_ClientList.SetColumn(0,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("139"),_T("IP��ַ"));
	col.pszText=szTemp.GetBuffer();
	m_ClientList.SetColumn(1,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("68"),_T("�û�"));
	col.pszText=szTemp.GetBuffer();
	m_ClientList.SetColumn(2,&col);
	szTemp.ReleaseBuffer();
}

void XDeviceServer::InitListData()
{
	auto& VecClient=m_pDelegate->GetVecClient();
	//�����������Ϣ
	if(VecClient.size()!=0)
	{
		XClient* pClient=VecClient[0];
		AddServerListInfo(pClient->m_szServerIP,pClient->m_nServerPort);
	}
	//////////////////////////////////////////////////////////////////////////
	//�ͻ����б�
	for(auto& pClient:VecClient)
	{
		AddClientListInfo(pClient->m_szClientName,pClient->m_szClientIP,pClient->m_nUserID);
	}
}

void XDeviceServer::AddServerListInfo(CString szIP,int nPort)
{
	m_ServerInfoList.DeleteAllItems();
	m_ServerInfoList.InsertItem(0,_T(""));


	m_ServerInfoList.SetItemText(0,0,szIP);
	CString szPort;
	szPort.Format(_T("%d"),nPort);
	m_ServerInfoList.SetItemText(0,1,szPort);
}

int XDeviceServer::AddClientListInfo(CString szName,CString szIP,int nUserID)
{
	//Ȩ���б�
	int nCount=0;
	nCount=m_ClientList.GetItemCount();

	//if(nCount>17)
	//	m_ClientList.SetColumnWidth(0,217);
	//else
	//	m_ClientList.SetColumnWidth(0,235);

	m_ClientList.InsertItem(nCount,_T(""));

	//��ȡ����
	CString szUserName=GetUserNameByID(nUserID);
	SetClientListInfo(nCount,szName,szIP,szUserName);
	return nCount;
}

CString XDeviceServer::GetUserNameByID(int nID)
{
	auto& MapPower=m_pDelegate->GetMapPower();
	for(auto& map:MapPower)
	{
		XPower* pPower=map.second;

		if(pPower->GetUserID()==nID)
			return pPower->GetUserName();
	}
	return _T("");
}

void XDeviceServer::SetClientListInfo(int nCount,CString szName,CString szIP,CString szUser)
{
	m_ClientList.SetItemText(nCount,0,szName);
	m_ClientList.SetItemText(nCount,1,szIP);
	m_ClientList.SetItemText(nCount,2,szUser);
}

void XDeviceServer::AlterPort()
{
	XAlterPort dlg;
	m_pAlterPort=&dlg;
	dlg.DoModal();

	m_pAlterPort=NULL;
}

void XDeviceServer::CloseAlterPortDlg()
{
	if(NULL!=m_pAlterPort)
	{
		m_pAlterPort->CloseDlg();
	}

	//����list
	InitListData();
}

void XDeviceServer::AddClient()
{
	lllllllllllll
}

void XDeviceServer::UpdateClient()
{

}

void XDeviceServer::DelClient()
{

}

LRESULT XDeviceServer::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
		case IDC_BTN_ALTER:
			{
				AlterPort();
			}
			break;
		case IDC_BTN_ADD:
			{
				AddClient();
			}
			break;
		case IDC_BTN_UPDATE:
			{
				UpdateClient();
			}
			break;
		case IDC_BTN_DEL:
			{
				DelClient();
			}
			break;
		default:
			break;
	}
	return 0;
}