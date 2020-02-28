#include "stdafx.h"
#include "XStatusBar.h"
#include "XTranslationManage.h"
#include "XDelegateStatusBar.h"


static UINT indicators[]=
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_EXT,
	ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

XStatusBar::XStatusBar()
{
}

XStatusBar::~XStatusBar()
{
}

XStatusBar* XStatusBar::GetInstance()
{
	static XStatusBar statusBar;
	return &statusBar;
}

void XStatusBar::Init()
{
	m_StatusBar.CreateEx(m_pDelegate->GetCWND());
	m_StatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));

	m_StatusBar.SetPaneInfo(0,m_StatusBar.GetDlgCtrlID(),SBPS_STRETCH,150);
	m_StatusBar.SetPaneInfo(1,m_StatusBar.GetDlgCtrlID(),SBPS_NORMAL,150);
	m_StatusBar.SetPaneInfo(2,m_StatusBar.GetDlgCtrlID(),SBPS_NORMAL,150);

	m_StatusBar.SetPaneText(0,_C(_T("68"),_T("�û�")));
	m_StatusBar.SetPaneText(1,_T(""));
	m_StatusBar.SetPaneText(2,_T(""));

	//m_StatusBar.OnUpdateCmdUI();
}

void XStatusBar::ReloadInterface()
{
	//���ؽ���
	SetUserElement();
}

void XStatusBar::SetCurUserName(CString szName)
{
	m_szUserName=szName;
	SetUserElement();
}

void XStatusBar::SetDevideNet(CString szIPAddr,int nPort)
{
	m_szIP=szIPAddr;
	m_nPort=nPort;
	SetDeviceElement();
}

void XStatusBar::SetUserElement()
{
	CString szElement;
	if(m_szUserName==_T(""))
		szElement.Format(_T("%s"),_C(_T("68"),_T("�û�")));
	else
		szElement.Format(_T("%s:%s"),_C(_T("68"),_T("�û�")),m_szUserName);

	
	m_StatusBar.SetPaneText(0,szElement);
}

void XStatusBar::SetDeviceElement()
{
	CString szNet;
	szNet.Format(_T("%s:%s:%d"),_T("Net"),m_szIP,m_nPort);
	m_StatusBar.SetPaneText(1,szNet);
}

void XStatusBar::UpdateTime()
{
	CString szTime; 
	CTime curTime=CTime::GetCurrentTime();
 
	szTime=curTime.Format(_T("%Y-%m-%d %A %H:%M:%S "));  
	m_StatusBar.SetPaneText(2,szTime);
}

void XStatusBar::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}