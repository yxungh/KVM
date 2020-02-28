
#include "stdafx.h"
#include "XPropertiesWnd.h"
#include "XTranslationManage.h"
#include "XDelegatePropertiesWnd.h"
#include "..\MainFrm.h"
#include "XConstant.h"
#include "XNode.h"
#include "XNodeGroupInfo.h"
#include "XSeat.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

XPropertiesWnd* XPropertiesWnd::m_pPropertiesWnd=NULL;
/////////////////////////////////////////////////////////////////////////////
XPropertiesWnd::XPropertiesWnd()
{
}

XPropertiesWnd::~XPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(XPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

XPropertiesWnd* XPropertiesWnd::GetInstance()
{
	if(NULL==m_pPropertiesWnd)
	{
		m_pPropertiesWnd=new XPropertiesWnd;
	}
	
	return m_pPropertiesWnd;
}

void XPropertiesWnd::Release()
{
	if(NULL!=m_pPropertiesWnd)
	{
		delete m_pPropertiesWnd;
	}
	m_pPropertiesWnd=NULL;
}

void XPropertiesWnd::Init()
{
	CreatePropertiesWnd();
	AdjustLayout();
}

void XPropertiesWnd::ReloadInterface()
{
	SetWindowText(_C(_T("65"),_T("属性")));

	//属性栏翻译
	m_wndPropList.RemoveAll();
	m_wndPropList.RedrawWindow();

	if(NULL!=m_pNode)
		m_pNode->SetPropertiesWnd();

	if(NULL!=m_pNodeGroup)
		m_pNodeGroup->SetProprityWnd();

	if(NULL!=m_pSeat)
		m_pSeat->SetPropertiesWnd();
}

void XPropertiesWnd::CreatePropertiesWnd()
{
	CWnd* pWnd=m_pDelegate->GetCWND();
	CMainFrame* pMainFrame=(CMainFrame*)pWnd;
	CString szTitle=_C(_T("65"),_T("属性"));

	if(!Create(szTitle,pMainFrame,CRect(0,0,200,200),TRUE,ID_PROPERTIESWND,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_RIGHT|CBRS_FLOAT_MULTI))
	{
		//TRACE0("Create Faile\n");
		return;
	}

	EnableDocking(CBRS_ALIGN_RIGHT);
	pMainFrame->DockPane(this);
}

void XPropertiesWnd::AdjustLayout()
{
	if(GetSafeHwnd()==NULL)
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	m_wndPropList.SetWindowPos(NULL,rectClient.left,rectClient.top,rectClient.Width(),rectClient.Height(),SWP_NOACTIVATE|SWP_NOZORDER);
}

int XPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct)==-1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wndPropList.Create(WS_VISIBLE|WS_CHILD,rectDummy,this,2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();
	AdjustLayout();
	return 0;
}

void XPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void XPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
}
 
LRESULT XPropertiesWnd::OnPropertyChanged(WPARAM,LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp=(CMFCPropertyGridProperty*)lParam;

	if(NULL!=m_pNode)
		m_pNode->OnPropertyChanged(pProp);

	if(NULL!=m_pNodeGroup)
		m_pNodeGroup->OnPropertyChanged(pProp);

	if(NULL!=m_pSeat)
		m_pSeat->OnPropertyChanged(pProp);

	return 0;
}

void XPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void XPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void XPropertiesWnd::OnContextMenu(CWnd* /* pWnd */,CPoint point)
{
	return;
}

void XPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
}
