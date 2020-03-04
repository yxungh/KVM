
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Template.h"
#include "MainFrm.h"
#include "XInternalManage.h"
#include "XConstant.h"
#include "TemplateView.h"
#include "HandleIni.h"
#include "HandlePath.h"
#include "XThemeColor.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame,CMDIFrameWndEx)

const int  iMaxUserToolbars=10;
const UINT uiFirstUserToolBarId=AFX_IDW_CONTROLBAR_FIRST+40;
const UINT uiLastUserToolBarId=uiFirstUserToolBarId+iMaxUserToolbars-1;

BEGIN_MESSAGE_MAP(CMainFrame,CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_WINDOW_MANAGER,OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE,OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR,OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000,ID_VIEW_APPLOOK_WINDOWS_7,OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000,ID_VIEW_APPLOOK_WINDOWS_7,OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_MESSAGE(MSG_UDP,OnUDP)
	ON_MESSAGE(MSG_ADDDOCUMENT,OnAddDocument)
	//////////////////////////////////////////////////////////////////////////
	ON_WM_CLOSE()
	ON_COMMAND(ID_BTN_ABOUT,OnAbout)

	ON_COMMAND(IDC_EDIT_DEVICEIP,OnEditDeviceIP)
	ON_COMMAND(IDC_EDIT_DEVICEPORT,OnEditDevicePort)
	ON_COMMAND(IDC_EDIT_SECONDDEVICEIP,OnEditSecondDeviceIP)
	ON_COMMAND(IDC_EDIT_SECONDDEVICEPORT,OnEditSecondDevicePort)

	ON_COMMAND(ID_BTN_UPDATE,OnBtnUpdate)
	ON_COMMAND(ID_BTN_FOLDER,OnBtnFolder)
	//ON_COMMAND(IDC_BTN_OPENNET,OnBtnOpenNet)
	//ON_COMMAND(IDC_BTN_CLOSENET,OnBtnCloseNet)

	ON_COMMAND(IDC_BTN_LOGIN,OnBtnLogin)
	ON_COMMAND(IDC_BTN_LOGINOUT,OnBtnLoginOut)
	ON_COMMAND(IDC_BTN_POWER,OnBtnPowerManage)
	ON_COMMAND(ID_BTN_OSDIMAGE,OnBtnOsdImage)

	//ON_COMMAND(ID_BTN_CONTROL,OnBtnControl)
	ON_COMMAND(ID_BTN_SAVESCENE,OnBtnSaveScene)
	ON_COMMAND(ID_BTN_LOG,OnBtnLog)

	ON_COMMAND(ID_BTN_ARRAY,OnBtnArray)

	ON_COMMAND(IDC_EDIT_SEATROW,OnEditSeatRow)
	ON_COMMAND(IDC_EDIT_SEATCOLUMN,OnEditSeatColumn)
	ON_COMMAND(ID_BTN_SAVESEAT,OnBtnSaveSeat)
	ON_COMMAND(ID_BTN_SENDSEAT,OnBtnSendSeat)
	ON_COMMAND(ID_BTN_CLEARSEAT,OnBtnClearSeat)
	ON_COMMAND(ID_BTN_BG,OnBtnBg)
	ON_COMMAND(ID_BTN_SEAT,OnBtnSeat)
	ON_UPDATE_COMMAND_UI(ID_BTN_SEAT,OnUpdateBtnSeat)

	ON_COMMAND(ID_BTN_MATRIXARRAY,OnBtnMatrixArray)
	ON_UPDATE_COMMAND_UI(ID_BTN_MATRIXARRAY,OnUpdataBtnMatrixArray)

	//*************************************
	ON_COMMAND(ID_BTN_THEME,OnBtnTheme)
	ON_COMMAND(ID_THEME_WIN7,OnThemeWin7)
	ON_COMMAND(ID_THEME_BLUE,OnThemeBlue)
	ON_COMMAND(ID_THEME_BLACK,OnThemeBlack)
	ON_COMMAND(ID_THEME_SILVER,OnThemeSliver)
	ON_COMMAND(ID_THEME_AQUA,OnThemeAque)

	ON_COMMAND(ID_BTN_LANGUAGE,OnBtnLanguage)
	ON_COMMAND(ID_LANGUAGE_ZN,OnLanguageZN)
	ON_COMMAND(ID_LANGUAGE_TW,OnLanguageTW)
	ON_COMMAND(ID_LANGUAGE_EN,OnLanguageEN)

	ON_COMMAND(ID_BTN_SCALE,OnBtnScale)
	ON_COMMAND(IDC_BTN_SEATSCALE,OnBtnSeatScale)
	ON_COMMAND(ID_BTN_MATRIXSCALE,OnBtnMatrixScale)
	ON_COMMAND(ID_SCALE200,OnScale200)
	ON_COMMAND(ID_SCALE175,OnScale175)
	ON_COMMAND(ID_SCALE150,OnScale150)
	ON_COMMAND(ID_SCALE125,OnScale125)
	ON_COMMAND(ID_SCALE100,OnScale100)
	ON_COMMAND(ID_SCALE75,OnScale75)
	ON_COMMAND(ID_SCALE50,OnScale50)

	ON_UPDATE_COMMAND_UI(ID_THEME_WIN7,OnUpdateThemeWin7)
	ON_UPDATE_COMMAND_UI(ID_THEME_BLUE,OnUpdateThemeBlue)
	ON_UPDATE_COMMAND_UI(ID_THEME_BLACK,OnUpdateThemeBlack)
	ON_UPDATE_COMMAND_UI(ID_THEME_SILVER,OnUpdateThemeSliver)
	ON_UPDATE_COMMAND_UI(ID_THEME_AQUA,OnUpdateThemeAque)

	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_ZN,OnUpdateLanguageZN)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_TW,OnUpdateLanguageTW)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_EN,OnUpdateLanguageEN)

	ON_UPDATE_COMMAND_UI(ID_SCALE200,OnUpdateScale200)
	ON_UPDATE_COMMAND_UI(ID_SCALE175,OnUpdateScale175)
	ON_UPDATE_COMMAND_UI(ID_SCALE150,OnUpdateScale150)
	ON_UPDATE_COMMAND_UI(ID_SCALE125,OnUpdateScale125)
	ON_UPDATE_COMMAND_UI(ID_SCALE100,OnUpdateScale100)
	ON_UPDATE_COMMAND_UI(ID_SCALE75,OnUpdateScale75)
	ON_UPDATE_COMMAND_UI(ID_SCALE50,OnUpdateScale50)
	//*************************************
	//ON_UPDATE_COMMAND_UI(IDC_BTN_OPENNET,OnUpdataBtnOpenNet)
	//ON_UPDATE_COMMAND_UI(IDC_BTN_CLOSENET,OnUpdataBtnCloseNet)
	ON_UPDATE_COMMAND_UI(IDC_BTN_LOGIN,OnUpdataBtnLogin)
	ON_UPDATE_COMMAND_UI(IDC_BTN_LOGINOUT,OnUpdataBtnLoginOut)
	ON_UPDATE_COMMAND_UI(ID_BTN_FOLDER,OnUpdateBtnFolder)
	ON_UPDATE_COMMAND_UI(IDC_BTN_POWER,OnUpdataBtnPowerManage)
	ON_UPDATE_COMMAND_UI(ID_BTN_OSDIMAGE,OnUpdataBtnOsdImage)
	//ON_UPDATE_COMMAND_UI(ID_BTN_CONTROL,OnUpdataBtnControl)
	ON_UPDATE_COMMAND_UI(ID_BTN_UPDATE,OnUpdataBtnUpdate)
	ON_UPDATE_COMMAND_UI(ID_BTN_SAVESCENE,OnUpdataBtnSaveScene)
	ON_UPDATE_COMMAND_UI(ID_BTN_LOG,OnUpdataBtnLog)
	ON_UPDATE_COMMAND_UI(ID_BTN_SAVESEAT,OnUpdataBtnSaveSeat)
	ON_UPDATE_COMMAND_UI(ID_BTN_SENDSEAT,OnUpdataBtnSendSeat)
	ON_UPDATE_COMMAND_UI(ID_BTN_CLEARSEAT,OnUpdataBtnClearSeat)
	//************************************
	ON_COMMAND(ID_BTN_ALIGN,OnBtnAlign)
	ON_UPDATE_COMMAND_UI(ID_BTN_ALIGN,OnUpdataBtnALign)


	ON_COMMAND(ID_ALIGNLEFT,OnBtnAlignLeft)
	ON_COMMAND(ID_ALIGNHORIZON,OnBtnAlignHorizon)
	ON_COMMAND(ID_ALIGNRIGHT,OnBtnALignRight)
	ON_COMMAND(ID_ALIGNUP,OnBtnALignUp)
	ON_COMMAND(ID_ALIGNVERTICAL,OnBtnALignVertical)
	ON_COMMAND(ID_ALIGNDOWN,OnBtnAlignDown)
	ON_COMMAND(ID_ALIGNSAME,OnBtnAlignSame)

	ON_COMMAND(ID_ALIGNHSAME,OnBtnAlignHSame)
	ON_UPDATE_COMMAND_UI(ID_ALIGNHSAME,OnUpdateAlignHSame)
	ON_COMMAND(ID_ALIGNVSAME,OnBtnAlignVSame)
	ON_UPDATE_COMMAND_UI(ID_ALIGNVSAME,OnUpdateAlignVSame)
	ON_COMMAND(ID_ALIGNWIDTH,OnBtnAlignWidth)
	ON_UPDATE_COMMAND_UI(ID_ALIGNWIDTH,OnUpdateAlignWidth)
	ON_COMMAND(ID_ALIGNHEIGHT,OnBtnAlignHeight)
	ON_UPDATE_COMMAND_UI(ID_ALIGNHEIGHT,OnUpdateAlignHeight)
	ON_UPDATE_COMMAND_UI(ID_ALIGNLEFT,OnUpdateAlignleft)
	ON_UPDATE_COMMAND_UI(ID_ALIGNHORIZON,OnUpdateAlignhorizon)
	ON_UPDATE_COMMAND_UI(ID_ALIGNRIGHT,OnUpdateAlignright)
	ON_UPDATE_COMMAND_UI(ID_ALIGNUP,OnUpdateAlignup)
	ON_UPDATE_COMMAND_UI(ID_ALIGNVERTICAL,OnUpdateAlignvertical)
	ON_UPDATE_COMMAND_UI(ID_ALIGNDOWN,OnUpdateAligndown)
	ON_UPDATE_COMMAND_UI(ID_ALIGNSAME,OnUpdateAlignsame)

	ON_UPDATE_COMMAND_UI(ID_INDICATOR_EXT,OnUpdateStatusNet)

	ON_COMMAND(IDC_BTN_DEVICENET,OnBtnDeviceNet)
	//////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_MENUOUTOFLOGOUT,OnMeunOut)
	//////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_BTN_ADDSPLIT,OnBtnAddSplit)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADDSPLIT,OnUpdateAddSplit)
	ON_COMMAND(ID_BTN_SPLITSCALE,OnBtnSplitScale)
	ON_UPDATE_COMMAND_UI(ID_BTN_SPLITSCALE,OnBtnUpdateSplitScale)
	ON_COMMAND(ID_BTN_CLEARSIGNAL,OnBtnClearSignal)
	ON_UPDATE_COMMAND_UI(ID_BTN_CLEARSIGNAL,OnBtnUpdateClearSignal)

	ON_COMMAND(ID_MENU_UP,OnMenuUp)
	ON_COMMAND(ID_MENU_DOWN,OnMenuDown)
	ON_COMMAND(ID_MENU_TOP,OnMenuTop)
	ON_COMMAND(ID_MENU_BOTTOM,OnMenuBottom)
	ON_COMMAND(ID_MENU_FULLSCREEN,OnMenuFullSceeen)
	ON_COMMAND(ID_MENU_RESTORE,OnMenuRestore)
	ON_COMMAND(ID_MENU_EXTEND,OnMenuExtend)
	ON_COMMAND(ID_MENU_CLOSESIGNAL,OnMenuCloseSignal)


	//ON_COMMAND(ID_BTN_ADDMODEL,OnAddModel)
	//ON_UPDATE_COMMAND_UI(ID_BTN_ADDMODEL,OnUpdateAddModel)
	//ON_COMMAND(ID_DEFUALT,OnAddDefault)
	//ON_UPDATE_COMMAND_UI(ID_DEFUALT,OnUpdateAddDefault)
	//ON_COMMAND(ID_FULLSCREEN,OnFullScreen)
	//ON_UPDATE_COMMAND_UI(ID_FULLSCREEN,OnUpdateFullScreen)

	ON_COMMAND(ID_BTN_LIMITMODEL,OnLimit)
	ON_UPDATE_COMMAND_UI(ID_BTN_LIMITMODEL,OnUpdateLimit)
	ON_COMMAND(ID_LIMITMODEL,OnLimitModel)
	ON_UPDATE_COMMAND_UI(ID_LIMITMODEL,OnUpdateLimitModel)
	ON_COMMAND(ID_DELTOP,OnDelTop)
	ON_UPDATE_COMMAND_UI(ID_DELTOP,OnUpdateDelTop)
	ON_COMMAND(ID_DELBOTTOM,OnDelBottom)
	ON_UPDATE_COMMAND_UI(ID_DELBOTTOM,OnUpdateDelBottom)

	ON_COMMAND(ID_MENU_QUICKTOP,OnBtnQuickTop)
	ON_UPDATE_COMMAND_UI(ID_MENU_QUICKTOP,OnUpdateQuickTop)

	ON_COMMAND(ID_MENU_SAVESCENE,OnBtnSplitScene)
	ON_UPDATE_COMMAND_UI(ID_MENU_SAVESCENE,OnUpdateSplitScene)






END_MESSAGE_MAP()


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	m_pBaseInternalManage=NULL;
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook=theApp.GetInt(_T("ApplicationLook"),ID_VIEW_APPLOOK_WINDOWS_7);
}

CMainFrame::~CMainFrame()
{
	Clear();
}

void CMainFrame::Clear()
{
	if(NULL!=m_pBaseInternalManage)
	{
		delete m_pBaseInternalManage;
		m_pBaseInternalManage=NULL;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CMDIFrameWndEx::OnCreate(lpCreateStruct)==-1)
		return -1;

	//BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style=CMFCTabCtrl::STYLE_3D_ONENOTE; // 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton=TRUE;      // 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons=TRUE;    // 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor=FALSE;    // 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu=TRUE; // 在选项卡区域的右边缘启用文档菜单
	mdiTabParams.m_bTabCloseButton=TRUE;
	mdiTabParams.m_bTabCustomTooltips=FALSE;
	mdiTabParams.m_bEnableTabSwap=FALSE;
	mdiTabParams.m_bFlatFrame=TRUE;
	mdiTabParams.m_nTabBorderSize=0;

	EnableMDITabbedGroups(TRUE,mdiTabParams);
	//////////////////////////////////////////////////////////////////////////
	srand((unsigned)time(NULL));
	InitManage();
	SetViewColor(theApp.m_nAppLook);
	//////////////////////////////////////////////////////////////////////////
	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	InitPane();
	//定时器
	BeginTimer();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CMDIFrameWndEx::PreCreateWindow(cs))
		return FALSE;

	m_strTitle=_T("KVM Manage");
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG

// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust=new CMFCToolBarsCustomizeDialog(this,TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres=CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if(lres==0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar=(CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid=strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE,ID_VIEW_CUSTOMIZE,strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;
	theApp.m_nAppLook=id;
	switch(theApp.m_nAppLook)
	{
		case ID_VIEW_APPLOOK_WIN_2000:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
			break;

		case ID_VIEW_APPLOOK_OFF_XP:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
			break;

		case ID_VIEW_APPLOOK_WIN_XP:
			CMFCVisualManagerWindows::m_b3DTabsXPTheme=TRUE;
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
			break;

		case ID_VIEW_APPLOOK_OFF_2003:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
			CDockingManager::SetDockingMode(DT_SMART);
			break;

		case ID_VIEW_APPLOOK_VS_2005:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
			CDockingManager::SetDockingMode(DT_SMART);
			break;

		case ID_VIEW_APPLOOK_VS_2008:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
			CDockingManager::SetDockingMode(DT_SMART);
			break;

		case ID_VIEW_APPLOOK_WINDOWS_7:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
			CDockingManager::SetDockingMode(DT_SMART);
			break;

		default:
			switch(theApp.m_nAppLook)
			{
				case ID_VIEW_APPLOOK_OFF_2007_BLUE:
					CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
					break;

				case ID_VIEW_APPLOOK_OFF_2007_BLACK:
					CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
					break;

				case ID_VIEW_APPLOOK_OFF_2007_SILVER:
					CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
					break;

				case ID_VIEW_APPLOOK_OFF_2007_AQUA:
					CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
					break;
			}

			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
			CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL,NULL,RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_UPDATENOW|RDW_FRAME|RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"),theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook==pCmdUI->m_nID);
}

void CMainFrame::ChangeTheme(int nIndex)
{
	UINT id=0;
	switch(nIndex)
	{
		case OPERATETYPE_THEMEWIN7:
			{
				id=ID_VIEW_APPLOOK_WINDOWS_7;
				m_pBaseInternalManage->SetViewColor(Color(255,230,240,250));
				XThemeColor::GetInstance()->SetThemeIndex(0);
			}
			break;
		case OPERATETYPE_THEMEBLUE:
			{
				id=ID_VIEW_APPLOOK_OFF_2007_BLUE;
				m_pBaseInternalManage->SetViewColor(Color(255,200,216,237));
				XThemeColor::GetInstance()->SetThemeIndex(1);
			}
			break;
		case OPERATETYPE_THEMEBLACK:
			{
				id=ID_VIEW_APPLOOK_OFF_2007_BLACK;
				m_pBaseInternalManage->SetViewColor(Color(255,187,192,201));
				XThemeColor::GetInstance()->SetThemeIndex(2);
			}
			break;
		case OPERATETYPE_THEMESLIVER:
			{
				id=ID_VIEW_APPLOOK_OFF_2007_SILVER;
				m_pBaseInternalManage->SetViewColor(Color(255,216,221,231));
				XThemeColor::GetInstance()->SetThemeIndex(3);
			}
			break;
		case OPERATETYPE_THEMEAQUE:
			{
				id=ID_VIEW_APPLOOK_OFF_2007_AQUA;
				m_pBaseInternalManage->SetViewColor(Color(255,195,202,217));
				XThemeColor::GetInstance()->SetThemeIndex(4);
			}
			break;
		default:
			break;
	}
	OnApplicationLook(id);
	//SetViewColor(theApp.m_nAppLook);
}

void CMainFrame::SetViewColor(int nID)
{
	switch(nID)
	{
		case ID_VIEW_APPLOOK_WINDOWS_7:
			{
				m_pBaseInternalManage->SetViewColor(Color(255,230,240,250));
				XThemeColor::GetInstance()->SetThemeIndex(0);
			}
			break;
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			{
				m_pBaseInternalManage->SetViewColor(Color(255,200,216,237));
				XThemeColor::GetInstance()->SetThemeIndex(1);
			}
			break;
		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			{
				m_pBaseInternalManage->SetViewColor(Color(255,187,192,201));
				XThemeColor::GetInstance()->SetThemeIndex(2);
			}
			break;
		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			{
				m_pBaseInternalManage->SetViewColor(Color(255,216,221,231));
				XThemeColor::GetInstance()->SetThemeIndex(3);
			}
			break;
		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			{
				m_pBaseInternalManage->SetViewColor(Color(255,195,202,217));
				XThemeColor::GetInstance()->SetThemeIndex(4);
			}
			break;
		default:
			break;
	}
}


BOOL CMainFrame::LoadFrame(UINT nIDResource,DWORD dwDefaultStyle,CWnd* pParentWnd,CCreateContext* pContext)
{
	// 基类将执行真正的工作
	if(!CMDIFrameWndEx::LoadFrame(nIDResource,dwDefaultStyle,pParentWnd,pContext))
	{
		return FALSE;
	}

	// 为所有用户工具栏启用自定义按钮
	//BOOL bNameValid;
	//CString strCustomize;
	//bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	//ASSERT(bNameValid);

	//for (int i = 0; i < iMaxUserToolbars; i ++)
	//{
	//	CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
	//	if (pUserToolbar != NULL)
	//	{
	//		pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	//	}
	//}

	return TRUE;
}

//
//void CMainFrame::OnSettingChange(UINT uFlags,LPCTSTR lpszSection)
//{
//	CMDIFrameWndEx::OnSettingChange(uFlags,lpszSection);
//	//m_wndOutput.UpdateFonts();
//}

void CMainFrame::OnClose()
{
	if((nullptr==m_pBaseInternalManage)||m_pBaseInternalManage->AppClose())
		__super::OnClose();
}

void CMainFrame::InitManage()
{
	m_pBaseInternalManage=new XInternalManage;
	m_pBaseInternalManage->SetDelegate(this);
	m_pBaseInternalManage->Init();
}

void CMainFrame::InitPane()
{
	m_pBaseInternalManage->InitPane();
}

CWnd* CMainFrame::GetCWND()
{
	return this;
}

HWND CMainFrame::GetHWND()
{
	return GetSafeHwnd();
}

int CMainFrame::MessageBox(CString szText,CString szCaption,UINT uType)
{
	return ::MessageBox(this->GetSafeHwnd(),szText,szCaption,uType);
}

LRESULT CMainFrame::OnUDP(WPARAM wParam,LPARAM lParam)
{
	m_pBaseInternalManage->HandleUDPMsg(wParam,lParam);
	return 0;
}

LRESULT CMainFrame::OnAddDocument(WPARAM wParam,LPARAM lParam)
{
	m_pBaseInternalManage->AddDocument();
	return 0;
}

//////////////////////////////////////////////////////////////////////////
void CMainFrame::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY)
{
	m_pBaseInternalManage->ViewDraw(pDC,rect,noffsetX,noffsetY);
}

CSize CMainFrame::ViewGetSize()
{
	return m_pBaseInternalManage->ViewGetSize();
}

void CMainFrame::ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseInternalManage->ViewLButtonDown(nFlags,point,rect,noffsetX,noffsetY);
}

void CMainFrame::ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseInternalManage->ViewLButtonDblClk(nFlags,point,rect,noffsetX,noffsetY);
}

void CMainFrame::ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseInternalManage->ViewLButtonUp(nFlags,point,rect,noffsetX,noffsetY);
}

void CMainFrame::ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseInternalManage->ViewMouseMove(nFlags,point,rect,noffsetX,noffsetY);
}

void CMainFrame::ViewMouseLeave()
{
	m_pBaseInternalManage->ViewMouseLeave();
}

BOOL CMainFrame::ViewMouseWheel(short zDelta)
{
	return m_pBaseInternalManage->ViewMouseWheel(zDelta);
}

void CMainFrame::ViewKeyUp(UINT nChar)
{
	m_pBaseInternalManage->ViewKeyUp(nChar);
}

void CMainFrame::ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseInternalManage->ViewRButtonUp(pWnd,nFlags,point,rect,noffsetX,noffsetY);
}

void CMainFrame::AdjustMultiVideoWindowSize()
{
	m_pBaseInternalManage->AdjustMultiVideoWindowSize();
}

void CMainFrame::HideMenuWnd()
{
	m_pBaseInternalManage->HideMenuWnd();
}

//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnAbout()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ABOUT,NULL);
}

void CMainFrame::OnEditDeviceIP()
{
	m_pBaseInternalManage->ControlDataChange(XDATATYPE_DEVICEIP);
}

void CMainFrame::OnEditDevicePort()
{
	m_pBaseInternalManage->ControlDataChange(XDATATYPE_DEVICEPORT);
}

void CMainFrame::OnEditSecondDeviceIP()
{
	m_pBaseInternalManage->ControlDataChange(XDATATYPE_SECONDDEVICEIP);
}

void CMainFrame::OnEditSecondDevicePort()
{
	m_pBaseInternalManage->ControlDataChange(XDATATYPE_SECONDDEVICEPORT);
}

void CMainFrame::OnBtnArray()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SCREENARRAY,NULL);
}

void CMainFrame::OnEditSeatRow()
{
	m_pBaseInternalManage->ControlDataChange(XDATATYPE_SEATROW);
}

void CMainFrame::OnEditSeatColumn()
{
	m_pBaseInternalManage->ControlDataChange(XDATATYPE_SEATCOLUMN);
}

//void CMainFrame::OnBtnOpenNet()
//{
//	m_pBaseInternalManage->Operate(OPERATETYPE_OPENNET,NULL);
//}

void CMainFrame::OnBtnUpdate()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_UPDATE,NULL);
}


void CMainFrame::OnUpdataBtnUpdate(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_UPDATE,pCmdUI);
}

void CMainFrame::OnBtnFolder()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_FOLDER,NULL);
}

void CMainFrame::OnUpdateBtnFolder(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_FOLDER,pCmdUI);
}


//void CMainFrame::OnUpdataBtnOpenNet(CCmdUI *pCmdUI)
//{
//	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_OPENNET,pCmdUI);
//}

//void CMainFrame::OnBtnCloseNet()
//{
//	m_pBaseInternalManage->Operate(OPERATETYPE_CLOSENET,NULL);
//}
//
//void CMainFrame::OnUpdataBtnCloseNet(CCmdUI *pCmdUI)
//{
//	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_CLOSENET,pCmdUI);
//}

void CMainFrame::OnBtnLogin()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_LOGIN,NULL);
}

void CMainFrame::OnUpdataBtnLogin(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_LOGIN,pCmdUI);
}

void CMainFrame::OnBtnLoginOut()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_LOGINOUT,NULL);
}

void CMainFrame::OnUpdataBtnLoginOut(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_LOGINOUT,pCmdUI);
}

void CMainFrame::OnBtnPowerManage()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_POWER,NULL);
}

void CMainFrame::OnUpdataBtnPowerManage(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_POWER,pCmdUI);
}

void CMainFrame::OnMeunOut()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENUOUTOFLOGOUT,NULL);
}

void CMainFrame::OnBtnOsdImage()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_OSDIMAGE,NULL);
}

void CMainFrame::OnUpdataBtnOsdImage(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_OSDIMAGE,pCmdUI);
}

//void CMainFrame::OnBtnControl()
//{
//	m_pBaseInternalManage->Operate(OPERATETYPE_CONTROL,NULL);
//}

//void CMainFrame::OnUpdataBtnControl(CCmdUI* pCmdUI)
//{
//	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_CONTROL,pCmdUI);
//}

void CMainFrame::OnBtnSaveScene()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SAVESCENE,NULL);
}

void CMainFrame::OnBtnLog()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_LOG,NULL);
}

void CMainFrame::OnUpdataBtnSaveScene(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SAVESCENE,pCmdUI);
}

void CMainFrame::OnBtnSaveSeat()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SAVESEAT,NULL);
}

void CMainFrame::OnUpdataBtnSaveSeat(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SAVESEAT,pCmdUI);
}

void CMainFrame::OnBtnSendSeat()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SENDSEAT,NULL);
}

void CMainFrame::OnUpdataBtnSendSeat(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SENDSEAT,pCmdUI);
}

void CMainFrame::OnBtnClearSeat()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_CLEARSEAT,NULL);
}

void CMainFrame::OnUpdataBtnClearSeat(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_CLEARSEAT,pCmdUI);
}

void CMainFrame::OnUpdataBtnLog(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_LOG,pCmdUI);
}

//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnBtnTheme()
{
	//主题
}

void CMainFrame::OnThemeWin7()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_THEMEWIN7,NULL);
}
void CMainFrame::OnThemeBlue()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_THEMEBLUE,NULL);
}
void CMainFrame::OnThemeBlack()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_THEMEBLACK,NULL);
}
void CMainFrame::OnThemeSliver()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_THEMESLIVER,NULL);
}
void CMainFrame::OnThemeAque()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_THEMEAQUE,NULL);
}

void CMainFrame::OnBtnLanguage()
{
	//语言
	//TRACE0("Languahe");
}

void CMainFrame::OnLanguageZN()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_LANGUAGEZN,NULL);
}
void CMainFrame::OnLanguageTW()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_LANGUAGETW,NULL);
}
void CMainFrame::OnLanguageEN()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_LANGUAGEEN,NULL);
}

void CMainFrame::OnBtnScale()
{
	//放缩
}

void CMainFrame::OnBtnSeatScale()
{
	//放缩
}

void CMainFrame::OnBtnMatrixScale()
{
	//放缩
}

void CMainFrame::OnScale200()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SCALE200,NULL);
}

void CMainFrame::OnScale175()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SCALE175,NULL);
}

void CMainFrame::OnScale150()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SCALE150,NULL);
}
void CMainFrame::OnScale125()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SCALE125,NULL);
}
void CMainFrame::OnScale100()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SCALE100,NULL);
}
void CMainFrame::OnScale75()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SCALE75,NULL);
}
void CMainFrame::OnScale50()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SCALE50,NULL);
}

void CMainFrame::OnBtnBg()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_BG,NULL);
}

void CMainFrame::OnBtnSeat()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SEAT,NULL);
}

void CMainFrame::OnUpdateBtnSeat(CCmdUI *pCmdUI)
{
	//pCmdUI->SetCheck(m_bFlag);
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SEAT,pCmdUI);
}

void CMainFrame::OnUpdateThemeWin7(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_THEMEWIN7,pCmdUI);
}
void CMainFrame::OnUpdateThemeBlue(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_THEMEBLUE,pCmdUI);
}
void CMainFrame::OnUpdateThemeBlack(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_THEMEBLACK,pCmdUI);
}
void CMainFrame::OnUpdateThemeSliver(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_THEMESLIVER,pCmdUI);
}
void CMainFrame::OnUpdateThemeAque(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_THEMEAQUE,pCmdUI);
}
void CMainFrame::OnUpdateLanguageZN(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_LANGUAGEZN,pCmdUI);
}
void CMainFrame::OnUpdateLanguageTW(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_LANGUAGETW,pCmdUI);
}
void CMainFrame::OnUpdateLanguageEN(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_LANGUAGEEN,pCmdUI);
}
void CMainFrame::OnUpdateScale200(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SCALE200,pCmdUI);
}
void CMainFrame::OnUpdateScale175(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SCALE175,pCmdUI);
}
void CMainFrame::OnUpdateScale150(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SCALE150,pCmdUI);
}
void CMainFrame::OnUpdateScale125(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SCALE125,pCmdUI);
}
void CMainFrame::OnUpdateScale100(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SCALE100,pCmdUI);
}
void CMainFrame::OnUpdateScale75(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SCALE75,pCmdUI);
}
void CMainFrame::OnUpdateScale50(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SCALE50,pCmdUI);
}

void CMainFrame::OnBtnAlign()
{
	//对齐
}

void CMainFrame::OnUpdataBtnALign(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIEN,pCmdUI);
}

void CMainFrame::OnBtnAlignLeft()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNLEFT,NULL);
}

void CMainFrame::OnBtnAlignHorizon()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNHORIZON,NULL);
}

void CMainFrame::OnBtnALignRight()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNRIGHT,NULL);
}

void CMainFrame::OnBtnALignUp()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNUP,NULL);
}

void CMainFrame::OnBtnALignVertical()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNVERTICAL,NULL);
}

void CMainFrame::OnBtnAlignDown()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNDOWN,NULL);
}

void CMainFrame::OnBtnAlignSame()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNSAME,NULL);
}

void CMainFrame::OnUpdateAlignleft(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNLEFT,pCmdUI);
}

void CMainFrame::OnUpdateAlignhorizon(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNHORIZON,pCmdUI);
}

void CMainFrame::OnUpdateAlignright(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNRIGHT,pCmdUI);
}

void CMainFrame::OnUpdateAlignup(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNUP,pCmdUI);
}

void CMainFrame::OnUpdateAlignvertical(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNVERTICAL,pCmdUI);
}

void CMainFrame::OnUpdateAligndown(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNDOWN,pCmdUI);
}

void CMainFrame::OnUpdateAlignsame(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNSAME,pCmdUI);
}

void CMainFrame::OnBtnAlignHSame()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNHSAME,NULL);
}

void CMainFrame::OnBtnAlignVSame()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNVSAME,NULL);
}

void CMainFrame::OnBtnAlignWidth()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNWIDTH,NULL);
}

void CMainFrame::OnBtnAlignHeight()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ALIGNHEIGHT,NULL);
}

void CMainFrame::OnUpdateAlignHSame(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNHSAME,pCmdUI);
}

void CMainFrame::OnUpdateAlignWidth(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNWIDTH,pCmdUI);
}

void CMainFrame::OnUpdateAlignVSame(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNVSAME,pCmdUI);
}

void CMainFrame::OnUpdateAlignHeight(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ALIGNHEIGHT,pCmdUI);
}

void CMainFrame::OnBtnDeviceNet()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_DEVICENET,NULL);
}

void CMainFrame::OnBtnMatrixArray()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MATRIXARRAY,NULL);
}

void CMainFrame::OnUpdataBtnMatrixArray(CCmdUI* pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_MATRIXARRAY,pCmdUI);
}

void CMainFrame::OnUpdateStatusNet(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_STATUSNET,pCmdUI);
}

void CMainFrame::OnBtnAddSplit()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_ADDSPLIT,NULL);
}

void CMainFrame::OnUpdateAddSplit(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ADDSPLIT,pCmdUI);
}

void CMainFrame::OnBtnSplitScale()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SPLITSCALE,NULL);
}

void CMainFrame::OnBtnUpdateSplitScale(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SPLITSCALE,pCmdUI);
}

void CMainFrame::OnBtnClearSignal()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_CLEARSIGNAL,NULL);
}

void CMainFrame::OnBtnUpdateClearSignal(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_CLEARSIGNAL,pCmdUI);
}

void CMainFrame::OnMenuUp()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENUUP,NULL);
}

void CMainFrame::OnMenuDown()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENUDOWN,NULL);
}

void CMainFrame::OnMenuTop()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENUTOP,NULL);
}

void CMainFrame::OnMenuBottom()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENUBOTTOM,NULL);
}

void CMainFrame::OnMenuFullSceeen()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENUFULLSCREEN,NULL);
}
void CMainFrame::OnMenuRestore()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENURESTORE,NULL);
}
void CMainFrame::OnMenuExtend()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENUEXTEND,NULL);
}
void CMainFrame::OnMenuCloseSignal()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_MENUCLOSESIGNAL,NULL);
}

//void CMainFrame::OnAddModel()
//{
//	//添加模式 不用响应
//}
//
//void CMainFrame::OnUpdateAddModel(CCmdUI *pCmdUI)
//{
//	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ADDMODEL,pCmdUI);
//}
//
//void CMainFrame::OnAddDefault()
//{
//	m_pBaseInternalManage->Operate(OPERATETYPE_ADDDEFAULT,NULL);
//}
//
//void CMainFrame::OnUpdateAddDefault(CCmdUI *pCmdUI)
//{
//	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_ADDDEFAULT,pCmdUI);
//}
//
//void CMainFrame::OnFullScreen()
//{
//	m_pBaseInternalManage->Operate(OPERATETYPE_FULLSCREEN,NULL);
//}
//
//void CMainFrame::OnUpdateFullScreen(CCmdUI *pCmdUI)
//{
//	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_FULLSCREEN,pCmdUI);
//}

void CMainFrame::OnLimit()
{
	//限制
}

void CMainFrame::OnUpdateLimit(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_LIMITNMODEL,pCmdUI);
}

void CMainFrame::OnLimitModel()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_LIMIT,NULL);
}

void CMainFrame::OnUpdateLimitModel(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_LIMIT,pCmdUI);
}

void CMainFrame::OnDelTop()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_DELTOP,NULL);
}

void CMainFrame::OnUpdateDelTop(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_DELTOP,pCmdUI);
}

void CMainFrame::OnDelBottom()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_DELBOTTOM,NULL);
}

void CMainFrame::OnUpdateDelBottom(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_DELBOTTOM,pCmdUI);
}

void CMainFrame::OnBtnQuickTop()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_QUICKTOP,NULL);
}

void CMainFrame::OnUpdateQuickTop(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_QUICKTOP,pCmdUI);
}

void CMainFrame::OnBtnSplitScene()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SAVESPLITSCENE,NULL);
}

void CMainFrame::OnUpdateSplitScene(CCmdUI *pCmdUI)
{
	m_pBaseInternalManage->UpdateControlUI(CMDUITYPE_SAVESPLITSCENE,pCmdUI);
}

//////////////////////////////////////////////////////////////////////////
void CMainFrame::BeginTimer()
{
	m_pBaseInternalManage->Operate(OPERATETYPE_SYSTEMSTATUS,NULL);
	SetTimer(TIMERID_SYSTEM,TIMERSPACE_SYSTEM,NULL);

	m_pBaseInternalManage->Operate(OPERATETYPE_STATUSTIME,NULL);
	SetTimer(TIMERID_CLICK,TIMERSPACE_CLICK,NULL);
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
		case TIMERID_SYSTEM:
			{
				m_pBaseInternalManage->Operate(OPERATETYPE_SYSTEMSTATUS,NULL);
			}
			break;
		case TIMERID_CLICK:
			{
				m_pBaseInternalManage->Operate(OPERATETYPE_STATUSTIME,NULL);
			}
			break;
		default:
			break;
	}
	__super::OnTimer(nIDEvent);
}







