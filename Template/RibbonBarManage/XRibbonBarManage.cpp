#include "StdAfx.h"
#include "XRibbonBarManage.h"
#include "XDelegateRibbonBarManage.h"
#include "../resource.h"
#include "XTranslationManage.h"
//#include "XStatusBar.h"



CMFCRibbonBar* XRibbonBarManage::m_pTempBar=NULL;
XRibbonBarManage::XRibbonBarManage(void)
{

}

XRibbonBarManage::~XRibbonBarManage(void)
{

}

void XRibbonBarManage::Init()
{
	InitRibbonBar();
	//InitStatusBar();
}

void XRibbonBarManage::InitRibbonBar()
{
	m_wndRibbonBar.Create(GetCWND());
	m_wndRibbonBar.SetDelegate(this);
	InitRibbonBar(&m_wndRibbonBar);
}

//void XRibbonBarManage::InitStatusBar()
//{
//	//状态栏
//	XStatusBar::GetInstance()->Create(GetCWND());
//	XStatusBar::GetInstance()->Init();
//}

void XRibbonBarManage::ResetRibbonBar()
{
	int nPageIndex=m_pDelegate->GetPageIndex();
	if(nPageIndex==1)
	{
		if(NULL==m_pCategorySeatArrage)
			return;
		//隐藏行列面板
		if(NULL!=m_pPanelSeatRange&&NULL!=m_pBtnArray)
		{
			m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelSeatRange));
			m_pPanelSeatRange=NULL;
			m_pBtnArray=NULL;
		}
		//隐藏操作面板
		if(NULL!=m_pPanelOperate&&NULL!=m_pBtnSaveSeat/*&&NULL!=m_pBtnSendSeat*/&&NULL!=m_pBtnClearSeat)
		{
			m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelOperate));
			m_pPanelOperate=NULL;
			m_pBtnSaveSeat=NULL;
			//m_pBtnSendSeat=NULL;
			m_pBtnClearSeat=NULL;
		}
		//////////////////////////////////////////////////////////////////////////
		if(NULL==m_pPanelSeat&&NULL==m_pBtnSeat&&NULL==m_pBtnAlign)
		{
			//坐席
			m_pPanelSeat=m_pCategorySeatArrage->AddPanel(_C(_T("97"),_T("坐席")));
			m_pPanelSeat->SetJustifyColumns(TRUE);
			m_pPanelSeat->SetCenterColumnVert(TRUE);

			m_pBtnSeat=new CMFCRibbonButton(ID_BTN_SEAT,_C(_T("97"),_T("坐席")),AfxGetApp()->LoadIcon(IDI_ICON_SEAT));
			m_pPanelSeat->Add(m_pBtnSeat);

			m_pBtnAlign=new CMFCRibbonButton(ID_BTN_ALIGN,_C(_T("125"),_T("对齐")),AfxGetApp()->LoadIcon(IDI_ICON_ALIGN));
			m_pPanelSeat->Add(m_pBtnAlign);
			m_pBtnAlign->SetMenu(IDR_MENU4);
		}
	}
	else if(nPageIndex==2)
	{
		if(NULL==m_pCategorySeatArrage)
			return;
		//隐藏行列面板
		if(NULL==m_pPanelSeatRange&&NULL==m_pBtnArray)
		{
			//范围
			m_pPanelSeatRange=m_pCategorySeatArrage->AddPanel(_C(_T("92"),_T("屏幕排列")));
			m_pPanelSeatRange->SetJustifyColumns(TRUE);
			m_pPanelSeatRange->SetCenterColumnVert(TRUE);

			//行列
			m_pBtnArray=new CMFCRibbonButton(ID_BTN_ARRAY,_C(_T("177"),_T("行列")),AfxGetApp()->LoadIcon(IDI_ICON_SCREENARRAY));
			m_pPanelSeatRange->Add(m_pBtnArray);
		}
		//隐藏操作面板
		if(NULL==m_pPanelOperate&&NULL==m_pBtnSaveSeat/*&&NULL==m_pBtnSendSeat*/&&NULL==m_pBtnClearSeat)
		{
			//操作
			m_pPanelOperate=m_pCategorySeatArrage->AddPanel(_C(_T("98"),_T("操作")));
			m_pPanelOperate->SetJustifyColumns(TRUE);
			m_pPanelOperate->SetCenterColumnVert(TRUE);

			//保存
			m_pBtnSaveSeat=new CMFCRibbonButton(ID_BTN_SAVESEAT,_C(_T("99"),_T("保存")),AfxGetApp()->LoadIcon(IDI_ICON_SAVESEAT));
			m_pPanelOperate->Add(m_pBtnSaveSeat);

			//发送
			//m_pBtnSendSeat=new CMFCRibbonButton(ID_BTN_SENDSEAT,_C(_T("100"),_T("发送")),AfxGetApp()->LoadIcon(IDI_ICON_SENDSEAT));
			//m_pPanelOperate->Add(m_pBtnSendSeat);

			//清除
			m_pBtnClearSeat=new CMFCRibbonButton(ID_BTN_CLEARSEAT,_C(_T("107"),_T("清空")),AfxGetApp()->LoadIcon(IDI_ICON_CLEAR));
			m_pPanelOperate->Add(m_pBtnClearSeat);
		}
		//////////////////////////////////////////////////////////////////////////
		if(NULL!=m_pPanelSeat&&NULL!=m_pBtnSeat&&NULL!=m_pBtnAlign)
		{
			m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelSeat));
			m_pPanelSeat=NULL;
			m_pBtnSeat=NULL;
			m_pBtnAlign=NULL;
		}
	}
	m_pTempBar->ForceRecalcLayout();
}

void XRibbonBarManage::InitRibbonBar(CMFCRibbonBar* pRibbonBar)
{
	m_pTempBar=pRibbonBar;

	//移除所有控件
	pRibbonBar->RemoveAllCategories();
	pRibbonBar->RemoveAllFromTabs();

	m_pAboutButton=new CMFCRibbonButton(ID_BTN_ABOUT,_T(""),AfxGetApp()->LoadIcon(IDI_ICON_ABOUT));
	pRibbonBar->AddToTabs(m_pAboutButton);

	//第一页显示 页面和坐席，第二页显示屏幕排列和操作
	//第一页-----------------------------------------------------------------
	//工具栏标签
	m_pCategoryMain=pRibbonBar->AddCategory(_C(_T("6"),_T("主页")),0,0);
	m_pCategoryMain->SetData(DWORD_PTR(_T("主页")));

	//界面
	m_pPanelMainSet=m_pCategoryMain->AddPanel(_C(_T("7"),_T("界面")));
	m_pPanelMainSet->SetJustifyColumns(TRUE);
	m_pPanelMainSet->SetCenterColumnVert(TRUE);

	m_pBtnTheme=new CMFCRibbonButton(ID_BTN_THEME,_C(_T("108"),_T("主题")),AfxGetApp()->LoadIcon(IDI_ICON_THEME));
	m_pPanelMainSet->Add(m_pBtnTheme);
	m_pBtnTheme->SetMenu(IDR_MENU3);

	m_pBtnLanguage=new CMFCRibbonButton(ID_BTN_LANGUAGE,_C(_T("8"),_T("语言")),AfxGetApp()->LoadIcon(IDI_ICON_LANGUE));
	m_pPanelMainSet->Add(m_pBtnLanguage);
	m_pBtnLanguage->SetMenu(IDR_MENU1);

	m_pBtnScale=new CMFCRibbonButton(ID_BTN_SCALE,_C(_T("9"),_T("比例")),AfxGetApp()->LoadIcon(IDI_ICON_ZOOM));
	m_pPanelMainSet->Add(m_pBtnScale);
	m_pBtnScale->SetMenu(IDR_MENU2);

	//////////////////////////////////////////////////////////////////////////
	//用户管理
	m_pPanelUser=m_pCategoryMain->AddPanel(_C(_T("23"),_T("用户管理")));
	m_pPanelUser->SetJustifyColumns(TRUE);
	m_pPanelUser->SetCenterColumnVert(TRUE);

	m_pLogin=new CMFCRibbonButton(IDC_BTN_LOGIN,_C(_T("21"),_T("登录")),AfxGetApp()->LoadIcon(IDI_ICON_LOGIN));
	m_pPanelUser->Add(m_pLogin);

	m_pPowerManage=new CMFCRibbonButton(IDC_BTN_POWER,_C(_T("34"),_T("权限")),AfxGetApp()->LoadIcon(IDI_ICON_POWER_1));
	m_pPanelUser->Add(m_pPowerManage);

	m_pFloder=new CMFCRibbonButton(ID_BTN_FOLDER,_C(_T("316"),_T("文件夹")),AfxGetApp()->LoadIcon(IDI_ICON_FOLDER));
	m_pPanelUser->Add(m_pFloder);

	m_pLoginOut=new CMFCRibbonButton(IDC_BTN_LOGINOUT,_C(_T("22"),_T("注销")),AfxGetApp()->LoadIcon(IDI_ICON_OUT));
	m_pPanelUser->Add(m_pLoginOut);

	m_pPanelImage=m_pCategoryMain->AddPanel(_C(_T("77"),_T("底图")));
	m_pPanelImage->SetJustifyColumns(TRUE);
	m_pPanelImage->SetCenterColumnVert(TRUE);

	//osd底图
	m_pBtnOSDImage=new CMFCRibbonButton(ID_BTN_OSDIMAGE,_C(_T("78"),_T("OSD底图")),AfxGetApp()->LoadIcon(IDI_ICON_IMAGE));
	m_pPanelImage->Add(m_pBtnOSDImage);

	//中控
	//m_pPanelControl=m_pCategoryMain->AddPanel(_C(_T("236"),_T("中控")));
	//m_pPanelControl->SetJustifyColumns(TRUE);
	//m_pPanelControl->SetCenterColumnVert(TRUE);
	//m_pBtnControl=new CMFCRibbonButton(ID_BTN_CONTROL,_C(_T("237"),_T("控制")),AfxGetApp()->LoadIcon(IDI_ICON_CONTROL));
	//m_pPanelControl->Add(m_pBtnControl);
	//////////////////////////////////////////////////////////////////////////
	//预案
	m_pPanelScene=m_pCategoryMain->AddPanel(_C(_T("239"),_T("预案")));
	m_pPanelScene->SetJustifyColumns(TRUE);
	m_pPanelScene->SetCenterColumnVert(TRUE);
	m_pBtnScene=new CMFCRibbonButton(ID_BTN_SAVESCENE,_C(_T("240"),_T("保存预案")),AfxGetApp()->LoadIcon(IDI_ICON_SAVESCENE));
	m_pPanelScene->Add(m_pBtnScene);
	//////////////////////////////////////////////////////////////////////////
	//日志
	m_pPanelLog=m_pCategoryMain->AddPanel(_C(_T("251"),_T("日志")));
	m_pPanelLog->SetJustifyColumns(TRUE);
	m_pPanelLog->SetCenterColumnVert(TRUE);
	m_pBtnLog=new CMFCRibbonButton(ID_BTN_LOG,_C(_T("251"),_T("日志")),AfxGetApp()->LoadIcon(IDI_ICON_LOG));
	m_pPanelLog->Add(m_pBtnLog);
	//////////////////////////////////////////////////////////////////////////
	//设备网络对话框
	m_pPanelDevice=m_pCategoryMain->AddPanel(_C(_T("13"),_T("设备")));
	m_pPanelDevice->SetJustifyColumns(TRUE);
	m_pPanelDevice->SetCenterColumnVert(TRUE);

	//升级服务器
	m_pBtnUpdate=new CMFCRibbonButton(ID_BTN_UPDATE,_C(_T("269"),_T("升级")),AfxGetApp()->LoadIcon(IDI_ICON_UPDATE));
	m_pPanelDevice->Add(m_pBtnUpdate);

	//网络
	m_pBtnNet=new CMFCRibbonButton(IDC_BTN_DEVICENET,_C(_T("18"),_T("网络")),AfxGetApp()->LoadIcon(IDI_ICON_NET));
	m_pPanelDevice->Add(m_pBtnNet);

	//打开网络
	//m_pBtnOpenNet=new CMFCRibbonButton(IDC_BTN_OPENNET,_C(_T("19"),_T("打开")),AfxGetApp()->LoadIcon(IDI_ICON_OPEN));
	//m_pPanelDevice->Add(m_pBtnOpenNet);

	//关闭网络
	//m_pBtnCloseNet=new CMFCRibbonButton(IDC_BTN_CLOSENET,_C(_T("20"),_T("关闭")),AfxGetApp()->LoadIcon(IDI_ICON_CLOSE));
	//m_pPanelDevice->Add(m_pBtnCloseNet);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//坐席工具栏根据页面单独显示
	//第二页------------------------------------------------------------------
	//坐席编排
	m_pCategorySeatArrage=pRibbonBar->AddCategory(_C(_T("76"),_T("坐席编排")),0,0);
	m_pCategorySeatArrage->SetData(DWORD_PTR(_T("坐席编排")));

	//界面
	m_pPanelMainSeat=m_pCategorySeatArrage->AddPanel(_C(_T("7"),_T("界面")));
	m_pPanelMainSeat->SetJustifyColumns(TRUE);
	m_pPanelMainSeat->SetCenterColumnVert(TRUE);

	//背景
	m_pBtnBg=new CMFCRibbonButton(ID_BTN_BG,_C(_T("120"),_T("背景")),AfxGetApp()->LoadIcon(IDI_ICON_BG));
	m_pPanelMainSeat->Add(m_pBtnBg);
	//m_pBtnSeatScale->SetMenu(IDR_MENU2);

	//比例
	m_pBtnSeatScale=new CMFCRibbonButton(IDC_BTN_SEATSCALE,_C(_T("9"),_T("比例")),AfxGetApp()->LoadIcon(IDI_ICON_ZOOM));
	m_pPanelMainSeat->Add(m_pBtnSeatScale);
	m_pBtnSeatScale->SetMenu(IDR_MENU2);

	//坐席
	m_pPanelSeat=m_pCategorySeatArrage->AddPanel(_C(_T("97"),_T("坐席")));
	m_pPanelSeat->SetJustifyColumns(TRUE);
	m_pPanelSeat->SetCenterColumnVert(TRUE);

	m_pBtnSeat=new CMFCRibbonButton(ID_BTN_SEAT,_C(_T("97"),_T("坐席")),AfxGetApp()->LoadIcon(IDI_ICON_SEAT));
	m_pPanelSeat->Add(m_pBtnSeat);

	m_pBtnAlign=new CMFCRibbonButton(ID_BTN_ALIGN,_C(_T("125"),_T("对齐")),AfxGetApp()->LoadIcon(IDI_ICON_ALIGN));
	m_pPanelSeat->Add(m_pBtnAlign);
	m_pBtnAlign->SetMenu(IDR_MENU4);

	//范围
	m_pPanelSeatRange=m_pCategorySeatArrage->AddPanel(_C(_T("92"),_T("屏幕排列")));
	m_pPanelSeatRange->SetJustifyColumns(TRUE);
	m_pPanelSeatRange->SetCenterColumnVert(TRUE);

	//行列
	m_pBtnArray=new CMFCRibbonButton(ID_BTN_ARRAY,_C(_T("177"),_T("行列")),AfxGetApp()->LoadIcon(IDI_ICON_SCREENARRAY));
	m_pPanelSeatRange->Add(m_pBtnArray);

	//////////////////////////////////////////////////////////////////////////
	//操作
	m_pPanelOperate=m_pCategorySeatArrage->AddPanel(_C(_T("98"),_T("操作")));
	m_pPanelOperate->SetJustifyColumns(TRUE);
	m_pPanelOperate->SetCenterColumnVert(TRUE);

	//保存
	m_pBtnSaveSeat=new CMFCRibbonButton(ID_BTN_SAVESEAT,_C(_T("99"),_T("保存")),AfxGetApp()->LoadIcon(IDI_ICON_SAVESEAT));
	m_pPanelOperate->Add(m_pBtnSaveSeat);

	//发送
	//m_pBtnSendSeat=new CMFCRibbonButton(ID_BTN_SENDSEAT,_C(_T("100"),_T("发送")),AfxGetApp()->LoadIcon(IDI_ICON_SENDSEAT));
	//m_pPanelOperate->Add(m_pBtnSendSeat);

	//清除
	m_pBtnClearSeat=new CMFCRibbonButton(ID_BTN_CLEARSEAT,_C(_T("107"),_T("清空")),AfxGetApp()->LoadIcon(IDI_ICON_CLEAR));
	m_pPanelOperate->Add(m_pBtnClearSeat);

	//////////////////////////////////////////////////////////////////////////
	//初始隐藏 第二页按钮
	//隐藏行列面板
	if(NULL!=m_pPanelSeatRange&&NULL!=m_pBtnArray)
	{
		m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelSeatRange));
		m_pPanelSeatRange=NULL;
		m_pBtnArray=NULL;
	}
	//隐藏操作面板
	if(NULL!=m_pPanelOperate&&NULL!=m_pBtnSaveSeat/*&&NULL!=m_pBtnSendSeat*/&&NULL!=m_pBtnClearSeat)
	{
		m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelOperate));
		m_pPanelOperate=NULL;
		m_pBtnSaveSeat=NULL;
		//m_pBtnSendSeat=NULL;
		m_pBtnClearSeat=NULL;
	}

	//第三页矩阵切换--------------------------------------------------------------
	m_pCategoryMatrix=pRibbonBar->AddCategory(_C(_T("252"),_T("矩阵切换")),0,0);
	m_pCategoryMatrix->SetData(DWORD_PTR(_T("矩阵切换")));

	//节点排列
	m_pPanelMatrixArray=m_pCategoryMatrix->AddPanel(_C(_T("253"),_T("排列")));
	m_pPanelMatrixArray->SetJustifyColumns(TRUE);
	m_pPanelMatrixArray->SetCenterColumnVert(TRUE);
	//排列
	m_pBtnMatrixArray=new CMFCRibbonButton(ID_BTN_MATRIXARRAY,_C(_T("253"),_T("排列")),AfxGetApp()->LoadIcon(IDI_ICON_SCREENARRAY));
	m_pPanelMatrixArray->Add(m_pBtnMatrixArray);
	//矩阵界面
	m_pPanelMatrixScale=m_pCategoryMatrix->AddPanel(_C(_T("7"),_T("界面")));
	m_pPanelMatrixScale->SetJustifyColumns(TRUE);
	m_pPanelMatrixScale->SetCenterColumnVert(TRUE);
	//缩放
	m_pBtnMatrixScale=new CMFCRibbonButton(ID_BTN_MATRIXSCALE,_C(_T("9"),_T("比例")),AfxGetApp()->LoadIcon(IDI_ICON_ZOOM));
	m_pPanelMatrixScale->Add(m_pBtnMatrixScale);
	m_pBtnMatrixScale->SetMenu(IDR_MENU2);


	//拼接页面--------------------------------------------------------------
	m_pCategorySplit=pRibbonBar->AddCategory(_C(_T("325"),_T("拼接")),0,0);
	m_pCategorySplit->SetData(DWORD_PTR(_T("拼接")));
	//添加拼接屏
	m_pPanelOne=m_pCategorySplit->AddPanel(_C(_T("326"),_T("新建")));
	m_pPanelOne->SetJustifyColumns(TRUE);
	m_pPanelOne->SetCenterColumnVert(TRUE);
	//新建
	m_pBtnAdd=new CMFCRibbonButton(ID_BTN_ADDSPLIT,_C(_T("327"),_T("新建拼接")),AfxGetApp()->LoadIcon(IDI_ICON_ADDSPLIT));
	m_pPanelOne->Add(m_pBtnAdd);
	//界面
	m_pPanelTwo=m_pCategorySplit->AddPanel(_C(_T("7"),_T("界面")));
	m_pPanelTwo->SetJustifyColumns(TRUE);
	m_pPanelTwo->SetCenterColumnVert(TRUE);
	//比例
	m_pBtnSplitScale=new CMFCRibbonButton(ID_BTN_SPLITSCALE,_C(_T("9"),_T("比例")),AfxGetApp()->LoadIcon(IDI_ICON_ZOOM));
	m_pPanelTwo->Add(m_pBtnSplitScale);
	m_pBtnSplitScale->SetMenu(IDR_MENU2);
	//操作
	m_pPanelThree=m_pCategorySplit->AddPanel(_C(_T("527"),_T("操作")));
	m_pPanelThree->SetJustifyColumns(TRUE);
	m_pPanelThree->SetCenterColumnVert(TRUE);

	//开窗模式
	//m_pBtnAddModel=new CMFCRibbonButton(ID_BTN_ADDMODEL,_C(_T("335"),_T("开窗模式")),AfxGetApp()->LoadIcon(IDI_ICON_SIGNALMODEL));
	//m_pPanelThree->Add(m_pBtnAddModel);
	//m_pBtnAddModel->SetMenu(IDR_MENU6);
	//限制模式
	m_pBtnLimitModel=new CMFCRibbonButton(ID_BTN_LIMITMODEL,_C(_T("338"),_T("限制模式")),AfxGetApp()->LoadIcon(IDI_ICON_LEVEL));
	m_pPanelThree->Add(m_pBtnLimitModel);
	m_pBtnLimitModel->SetMenu(IDR_MENU5);

	m_pBtnQuickTop=new CMFCRibbonButton(ID_MENU_QUICKTOP,_C(_T("343"),_T("快速置顶")),AfxGetApp()->LoadIcon(IDI_ICON_QUICKTOP));
	m_pPanelThree->Add(m_pBtnQuickTop);
	//清空信号
	m_pBtnClearSignal=new CMFCRibbonButton(ID_BTN_CLEARSIGNAL,_C(_T("107"),_T("清空")),AfxGetApp()->LoadIcon(IDI_ICON_CLEAR));
	m_pPanelThree->Add(m_pBtnClearSignal);
	//场景保存
	m_pBtnSplitScene=new CMFCRibbonButton(ID_MENU_SAVESCENE,_C(_T("350"),_T("场景保存")),AfxGetApp()->LoadIcon(IDI_ICON_SAVESCENE));
	m_pPanelThree->Add(m_pBtnSplitScene);

	//调整布局
	pRibbonBar->ForceRecalcLayout();
}

CWnd* XRibbonBarManage::GetCWND()
{
	return m_pDelegate->GetCWND();
}

void XRibbonBarManage::UpdateControlDataShowOfAll()
{

}

void XRibbonBarManage::ReloadInterface()
{
	InitRibbonBar(&m_wndRibbonBar);
	UpdateControlDataShowOfAll();
}

void XRibbonBarManage::RibbonBarShowCategory(DWORD_PTR dwData)
{
	m_pDelegate->RibbonBarShowCategory(dwData);
}

//void XRibbonBarManage::SetCurUserName(CString szUserName)
//{
//	m_szUserName=szUserName;
//}

//void XRibbonBarManage::SetStatusInfo()
//{
	//CString szTemp=XTranslationManage::GetInstance()->_C(_T("33"));

	//CString szInformation;
	//szInformation.Format(_T("%s %s"),m_szUserName,szTemp);

	//m_wndStatusBar.SetInformation(szInformation);

	//CMFCRibbonBaseElement* pUser=m_wndStatusBar.FindElement(ID_STATUSBAR_USER);
	//if(NULL!=pUser)
	//{
	//	pUser->SetText(m_szUserName);
	//}
//}

void XRibbonBarManage::SetActiveCategory(int nBaseIndex)
{
	if(nBaseIndex==0)
	{
		if(NULL!=m_pCategoryMain)
			m_wndRibbonBar.SetActiveCategory(m_pCategoryMain);
	}
	else if(nBaseIndex==1)
	{
		if(NULL!=m_pCategorySeatArrage)
			m_wndRibbonBar.SetActiveCategory(m_pCategorySeatArrage);
	}
	else if(nBaseIndex==2)
	{
		if(NULL!=m_pCategoryMatrix)
			m_wndRibbonBar.SetActiveCategory(m_pCategoryMatrix);
	}
	else
	{
		//都是拼接屏
		if(NULL!=m_pCategorySplit)
			m_wndRibbonBar.SetActiveCategory(m_pCategorySplit);
	}
}

//////////////////////////////////////////////////////////////////////////
void XRibbonBarManage::ControlDataChange(XDATATYPE type)
{

}

void XRibbonBarManage::UpdateControlDataShow(XDATATYPE type)
{
	switch(type)
	{
		case XDATATYPE_ALL:
			{
				UpdateControlDataShowOfAll();
			}
			break;
		case XDATATYPE_LOGIN:
			{
				m_pDelegate->UpdateControlDataShow(type,m_pLogin);
			}
			break;
		case XDATATYPE_LOGINOUT:
			{
				m_pDelegate->UpdateControlDataShow(type,m_pLoginOut);
			}
			break;

		default:
			break;
	}
}
