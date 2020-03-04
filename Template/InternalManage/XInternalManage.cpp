#include "Stdafx.h"
#include "XInternalManage.h"
#include "XDelegateInternalManage.h"
#include "XRibbonBarManage.h"
#include "XTranslationManage.h"
#include "XIniManage.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XMessageBox.h"
#include "XNetManage.h"
#include "XSendDataManage.h"
#include "XMessageBox.h"
#include "XJsonManage.h"
#include "XReciveDataManage.h"
#include "XUserManage.h"
#include "XNodeManage.h"
#include "XBaseViewManage.h"
#include "XMatrixManage.h"
#include "..\TemplateView.h"
#include "..\ChildFrm.h"
#include "XData.h"
#include "XPropertiesWnd.h"
#include "XLeftWnd.h"
#include "XScene.h"
#include "XConstantData.h"
#include "XSeatArrageManage.h"
#include "XTabCtrl.h"
#include "XSeatArrageData.h"
#include "XMultiVideoWindow.h"
#include "XMultiVideoWindowFrames.h"
#include "XPage.h"
#include "XSeat.h"
#include "XDeviceNet.h"
#include "XNetConfig.h"
#include "XResult.h"
#include "XCenterControl.h"
#include "XUpdate.h"
#include "About.h"
#include "XStatusBar.h"
#include "XSplitManage.h"
#include "XAddSplit.h"
#include "XSplitResult.h"
#include "XSplitWindow.h"
#include "XSignal.h"
#include "XSplitSceneResult.h"
#include "XSplitScene.h"
#include "XSaveSplitScene.h"






XInternalManage::XInternalManage()
{

}

XInternalManage::~XInternalManage()
{
	//m_bRunning=FALSE;
	StopHeartThread();
	Clear();
}

void XInternalManage::Clear()
{
	RELEASE(m_pRibbonBarManage);
	RELEASE(m_pIniManage);
	RELEASE(m_pBaseNetManage);
	RELEASE(m_pReciveDataManage);
	RELEASE(m_pUserManage);

	m_VideoPlayer.ClearData();

	XMessageBox::GetInstance()->Release();
	XSendDataManage::GetInstance()->Release();
	XJsonManage::GetInstance()->Relase();
	XPropertiesWnd::GetInstance()->Release();
	XLeftWnd::GetInstance()->Release();
	XScene::GetInstance()->Release();
	XConstantData::GetInstance()->Release();
	XSeatArrageData::GetInstance()->Release();

	ClearMapData();
	ClearMapBaseView();
	ClearNetConfig();
	ClearSplitScene();

}


void XInternalManage::ClearSplitScene()
{
	for(auto iter=m_MapSplitScene.begin();iter!=m_MapSplitScene.end();++iter)
	{
		delete iter->second;
	}
	m_MapSplitScene.clear();
}

void XInternalManage::ClearMapBaseView()
{
	for(auto iter=m_MapBaseView.begin();iter!=m_MapBaseView.end();++iter)
	{
		delete iter->second;
	}
	m_MapBaseView.clear();
}

void XInternalManage::ClearMapData()
{
	for(auto iter=m_MapData.begin();iter!=m_MapData.end();++iter)
	{
		delete iter->second;
	}
	m_MapData.clear();
}

void XInternalManage::ClearNetConfig()
{
	for(auto& vec:m_VecNetConfig)
	{
		delete vec;
	}
	m_VecNetConfig.clear();
}

void XInternalManage::SetHardWareChannel(int n)
{
	m_nHardWareChannel=n;
}

void XInternalManage::SetMatrixModel(CString szModel)
{
	m_szMatrixModel=szModel;
}

void XInternalManage::SetFPGAVersion(CString szVer)
{
	m_szFPGAVersion=szVer;
}

void XInternalManage::OperateOfAbout()
{
	XAbout about;
	about.SetFPGAVer(m_szFPGAVersion);
	about.SetLogin(m_bLogin);
	about.DoModal();
}

void XInternalManage::Init()
{
	InitManage();
	InitDocument();
	InitAppData();
	InitIPAddr();

	m_pBaseViewManage=m_MapBaseView[0];
	UpdateControlDataShow(XDATATYPE_ALL);

	//开启心跳线程
	if(BeginHeartThread())
	{
		return;
	}
}

void XInternalManage::InitManage()
{
	XTranslationManage::GetInstance()->SetDelegate(this);
	XTranslationManage::GetInstance()->Init();

	m_VideoPlayer.InitFFMPEG();
	m_VideoPlayer.Init();

	//工具栏管理
	m_pRibbonBarManage=new XRibbonBarManage;
	m_pRibbonBarManage->SetDelegate(this);
	m_pRibbonBarManage->Init();

	//状态栏
	XStatusBar::GetInstance()->SetDelegate(this);
	XStatusBar::GetInstance()->Init();

	//Ini管理
	m_pIniManage=new XIniManage;
	m_pIniManage->SetDelegate(this);
	m_pIniManage->Init();

	//网络管理
	m_pBaseNetManage=new XNetManage;
	m_pBaseNetManage->SetDelegate(this);
	m_pBaseNetManage->Init();

	//接受数据
	m_pReciveDataManage=new XReciveDataManage;
	m_pReciveDataManage->SetDelegate(this);

	//用户管理
	m_pUserManage=new XUserManage;
	m_pUserManage->SetDelegate(this);

	//单例先实例化（防止线程出问题） 
	XSendDataManage::GetInstance()->SetDelegate(this);
	XConstantData::GetInstance()->SetDelegate(this);
	XMessageBox::GetInstance();
	XJsonManage::GetInstance();
	XPropertiesWnd::GetInstance();
	XLeftWnd::GetInstance();
	XScene::GetInstance();
	XSeatArrageData::GetInstance();
}

void XInternalManage::InitDocument()
{
	//节点管理
	m_pNodeManage=new XNodeManage;
	m_pNodeManage->SetDelegate(this);

	CString szTitle=GetDocTitle(_T("设备运维状态"));
	m_pNodeManage->SetTitle(szTitle);
	m_pNodeManage->Init();
	m_pNodeManage->SetBaseIndex(0);

	m_MapBaseView.insert(std::pair<int,XBaseViewManage*>(0,m_pNodeManage));
	//////////////////////////////////////////////////////////////////////////
	//坐席编排
	m_pSeatArrageManage=new XSeatArrageManage;
	m_pSeatArrageManage->SetDelegate(this);

	szTitle=GetDocTitle(_T("坐席编排"));
	m_pSeatArrageManage->SetTitle(szTitle);
	m_pSeatArrageManage->Init();
	m_pSeatArrageManage->SetBaseIndex(1);

	m_MapBaseView.insert(std::pair<int,XBaseViewManage*>(1,m_pSeatArrageManage));
	//////////////////////////////////////////////////////////////////////////
	//矩阵切换
	m_pMatrixManage=new XMatrixManage;
	m_pMatrixManage->SetDelegate(this);

	szTitle=GetDocTitle(_T("矩阵切换"));
	m_pMatrixManage->SetTitle(szTitle);
	m_pMatrixManage->Init();
	m_pMatrixManage->SetBaseIndex(2);

	m_MapBaseView.insert(std::pair<int,XBaseViewManage*>(2,m_pMatrixManage));
	//////////////////////////////////////////////////////////////////////////
	//拼接
	//XSplitManage* pSplitManage=new XSplitManage;
	//pSplitManage->SetDelegate(this);
	//szTitle=GetDocTitle(_T("拼接屏"));
	//pSplitManage->SetTitle(szTitle);
	//pSplitManage->Init();
	//pSplitManage->SetBaseIndex(3);
	////pSplitManage->SetTest(TRUE);
	////m_pSplitManage=pSplitManage;
	//m_MapBaseView.insert(std::pair<int,XBaseViewManage*>(3,pSplitManage));
}

CString XInternalManage::GetDocTitle(CString szTitle)
{
	int nLen=szTitle.GetLength();

	if(nLen<25)
	{
		int nTitleLen=25-nLen;
		for(int i=0;i<nTitleLen;i++)
		{
			szTitle+=" ";
		}
	}

	return szTitle;
}

void XInternalManage::InitPane()
{
	XPropertiesWnd::GetInstance()->SetDelegate(this);
	XPropertiesWnd::GetInstance()->Init();

	XLeftWnd::GetInstance()->SetDelagate(this);
	XLeftWnd::GetInstance()->Init();
	//////////////////////////////////////////////////////////////////////////
	XScene::GetInstance()->SetDelegate(this);
	XScene::GetInstance()->SetUpPane(XLeftWnd::GetInstance());
	XScene::GetInstance()->Init();
}

void XInternalManage::SetCurUserName(CString szName)
{
	m_szUserName=szName;
	//设置状态栏显示
	XStatusBar::GetInstance()->SetCurUserName(szName);
}

CString XInternalManage::GetCurUserName()
{
	return m_szUserName;
}

void XInternalManage::SetCurUserID(int n)
{
	m_nUserID=n;
}

int XInternalManage::GetCurUserID()
{
	return m_nUserID;
}

////void XInternalManage::SetStatusBarInfo()
////{
////	m_pRibbonBarManage->SetCurUserName(m_szUserName);
//	m_pRibbonBarManage->SetStatusInfo();
////}

void XInternalManage::SetLogin(BOOL b)
{
	m_bLogin=b;
}

BOOL XInternalManage::GetLogin()
{
	return m_bLogin;
}

CTemplateView* XInternalManage::GetView()
{
	if(m_pBaseViewManage!=NULL)
		return m_pBaseViewManage->GetView();
	else
		return NULL;
}

void XInternalManage::SetViewManage(XBaseViewManage* p)
{
	if(NULL==p)
		return;

	//CString szStr=p->GetTitle();
	//TRACE(_T("Title=%s\n"),szStr);

	//激活对应工具栏
	if(NULL!=m_pBaseViewManage)
	{
		m_pBaseViewManage=p;

		int nBaseIndex=m_pBaseViewManage->GetBaseIndex();

		//根据页面切换左面板树
		m_pBaseViewManage->ResetLeftWnd();
		//切换场景树
		if(m_bLogin)
			m_pBaseViewManage->ResetSceneWnd();
		//清理属性面板
		m_pBaseViewManage->ClearProperityWnd();

		if(nBaseIndex==0)
		{
			if(NULL!=m_pSeatArrageManage)
				m_pSeatArrageManage->HideSeatDrawWnd();
		}
		else if(nBaseIndex==1)
		{
			if(NULL!=m_pSeatArrageManage)
			{
				m_pSeatArrageManage->ShowSeatDrawWnd();
				if(m_bLogin)
					m_pSeatArrageManage->EnableSeatDrawWnd(TRUE);
				else
					m_pSeatArrageManage->EnableSeatDrawWnd(FALSE);
			}
		}
		else if(nBaseIndex==2)
		{
			if(NULL!=m_pSeatArrageManage)
				m_pSeatArrageManage->HideSeatDrawWnd();
		}
		else
		{
			//都是拼接界面
			//保存当前界面序号，用于跳转
			m_nSplitIndex=nBaseIndex;

		}
		//由于拼接，要先保存界面序号，再设置工具栏
		m_pRibbonBarManage->SetActiveCategory(nBaseIndex);
	}
	//UpdateControlDataShow(XDATATYPE_ALL);
}

void XInternalManage::AddDocument()
{
	for(auto& map:m_MapBaseView)
	{
		XBaseViewManage* pBase=map.second;
		AddDocument(pBase);
	}

	//显示第一个
	m_pViewTabCtrl->SetActiveTab(0);

	ReloadDocTitle();
}

void XInternalManage::AddDocument(XBaseViewManage* pBase)
{
	CWinApp* pApp=AfxGetApp();
	POSITION curTemplatePos=pApp->GetFirstDocTemplatePosition();
	CDocTemplate* curTemplate=pApp->GetNextDocTemplate(curTemplatePos);
	CDocument* pDoc=curTemplate->OpenDocumentFile(NULL);

	CString szTitle=pBase->GetTitle();
	pDoc->SetTitle(szTitle);

	CTemplateView* pView=(CTemplateView*)GetDocumentFrontView(pDoc);
	pView->SetBaseViewManage(pBase);
	pView->Init();
	pBase->SetView(pView);

	CChildFrame* pFrame=(CChildFrame*)pView->GetParentFrame();
	pFrame->SetBaseViewManage(pBase);
	pFrame->SetInternalManage(this);

	//获取顶部TabCtrl
	if(NULL==m_pViewTabCtrl)
		m_pViewTabCtrl=(XTabCtrl*)pFrame->GetRelatedTabGroup();

	//坐席页面添加预览墙
	if(pBase->GetBaseIndex()==1)
	{
		Color color=pBase->GetViewColor();
		m_pMultiVideoWindow=m_VideoPlayer.AddMultiVideoWindow(pView->GetSafeHwnd(),color.GetR(),color.GetG(),color.GetB());
		m_pMultiVideoWindow->SetText(_C(_T("97"),_T("坐席")));

		pBase->SetMultiVideoWindow(m_pMultiVideoWindow);

		float fScale=((XSeatArrageManage*)pBase)->GetScale();
		m_pMultiVideoWindow->SetMultiVideoWindowScale(fScale);

		MAP_PAGE& MapPage=((XSeatArrageManage*)pBase)->GetMapPage();
		for(auto iter=MapPage.begin();iter!=MapPage.end();++iter)
		{
			int nIndex=iter->first;
			XPage* pPage=iter->second;

			int nWidth=pPage->GetPageWidth();
			int nHeight=pPage->GetPageHeight();

			CString szPhotoName=pPage->GetPhotoName();
			CString szPhotoPath=HandlePath::GetPhotoPath(szPhotoName);

			XMultiVideoWindowFrames* pFrames=AddPageToMultiVideoWindow(nIndex,nWidth,nHeight);

			m_pMultiVideoWindow->SetFramesShowModel(nIndex,pPage->GetModel());
			m_pMultiVideoWindow->SetFramesBgPic(nIndex,szPhotoPath);
			m_pMultiVideoWindow->SetFramesBgColor(nIndex,pPage->GetColorR(),pPage->GetColorG(),pPage->GetColorB());
		}
	}
}

void XInternalManage::OperateOfAddSeat()
{
	//添加坐席(登录时)
	RECTF rectImage(0,0,1920,1088);

	MAP_PAGE& MapPage=m_pSeatArrageManage->GetMapPage();
	XPage* pPage=MapPage[1];
	int nIndex=pPage->GetIndex();

	VEC_SEAT& VecSeat=pPage->GetVecSeat();
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pSeat=*iter;

		XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(nIndex,_T(""),pSeat->GetRect(),rectImage);
		m_pMultiVideoWindow->SetFrame(nIndex,pFrame,pSeat->GetSelected());
		m_pMultiVideoWindow->SetFrameModel(nIndex,pFrame,pSeat->GetModel());
		m_pMultiVideoWindow->SetFrame(nIndex,pFrame,pSeat->GetColorR(),pSeat->GetColorG(),pSeat->GetColorB(),pSeat->GetColorA());
		m_pMultiVideoWindow->SetFramePic(nIndex,pFrame,pSeat->GetPhotoPath());

		MAP_TEMPFRAME& MapTempFrame=m_pSeatArrageManage->GetMapTempFrame();
		MapTempFrame.insert(std::pair<int,XMultiVideoWindowFrame*>(pSeat->GetIndex(),pFrame));
	}
}

void XInternalManage::SetMultiVideoFramesBg()
{
	MAP_PAGE& MapPage=m_pSeatArrageManage->GetMapPage();
	for(auto iter=MapPage.begin();iter!=MapPage.end();++iter)
	{
		int nIndex=iter->first;
		XPage* pPage=iter->second;

		CString szPhotoName=pPage->GetPhotoName();
		CString szPhotoPath=HandlePath::GetPhotoPath(szPhotoName);

		m_pMultiVideoWindow->SetFramesShowModel(nIndex,pPage->GetModel());
		m_pMultiVideoWindow->SetFramesBgPic(nIndex,szPhotoPath);
		m_pMultiVideoWindow->SetFramesBgColor(nIndex,pPage->GetColorR(),pPage->GetColorG(),pPage->GetColorB());
	}
}

XMultiVideoWindowFrames* XInternalManage::AddPageToMultiVideoWindow(int nIndex,int nWidth,int nHeight)
{
	return m_pMultiVideoWindow->AddPage(nIndex,nWidth,nHeight);
}

void XInternalManage::SetMultiVideoWindowBkColor(Uint8 r,Uint8 g,Uint8 b)
{
	if(NULL!=m_pMultiVideoWindow)
		m_pMultiVideoWindow->SetBGColor(r,g,b);
}

void XInternalManage::SetMultiVideoWindowScale(float fScale)
{
	if(NULL!=m_pMultiVideoWindow)
		m_pMultiVideoWindow->SetMultiVideoWindowScale(fScale);
}

void XInternalManage::AdjustMultiVideoWindowSize()
{
	if(NULL!=m_pSeatArrageManage)
		m_pSeatArrageManage->AdjustMultiVideoWindowSize();
}

void XInternalManage::AdjustMultiVideoWindowSize(int nWidth,int nHeight)
{
	if(NULL!=m_pMultiVideoWindow)
		m_VideoPlayer.AdjustMultiVideoWindowSize(m_pMultiVideoWindow,nWidth,nHeight);
}

CView* XInternalManage::GetDocumentFrontView(CDocument* p)
{
	CView* pView=NULL;
	POSITION pos=p->GetFirstViewPosition();
	pView=p->GetNextView(pos);

	return pView;
}

void XInternalManage::InitAppData()
{
	BOOL bResult=FALSE;

	try
	{
		bResult=GetAppData();
	}
	catch(CException* e)
	{
		e->Delete();
	}

	if(!bResult)
	{
		ResetAppData();
	}
}

BOOL XInternalManage::GetAppData()
{
	CFile mFile;

	CString szDataPath=HandlePath::GetDataFilePath(APP_DATAFILENAME);

	if(mFile.Open(szDataPath,CFile::modeRead))
	{
		CArchive arch(&mFile,CArchive::load);

		GetAppData(arch);
		arch.Close();
		mFile.Close();

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void XInternalManage::GetAppData(CArchive& arch)
{
	m_pSeatArrageManage->GetData(arch);
	//XSeatArrageWnd::GetInstance()->GetData(arch);
	XScene::GetInstance()->GetData(arch);
}

void XInternalManage::ResetAppData()
{
	m_pSeatArrageManage->ResetData();
}

BOOL XInternalManage::AppClose()
{
	BOOL bResult=FALSE;

	if(SaveAppData())
	{
		bResult=TRUE;
	}
	else
	{
		if(IDYES==_M(_T("224"),_T("保存程序数据失败，请确认是否继续退出程序？"),MB_YESNO))
		{
			bResult=TRUE;
		}
	}

	return bResult;
}

void XInternalManage::SaveData()
{
	SaveAppData();
}

BOOL XInternalManage::SaveAppData()
{
	CFile mFile;

	CString szDataPath=HandlePath::GetDataFilePath(APP_DATAFILENAME);

	if(mFile.Open(szDataPath,CFile::modeCreate|CFile::modeWrite))
	{
		CArchive arch(&mFile,CArchive::store);

		SaveAppData(arch);
		arch.Close();
		mFile.Close();

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void XInternalManage::SaveAppData(CArchive& arch)
{
	m_pSeatArrageManage->SaveData(arch);
	//XSeatArrageWnd::GetInstance()->SaveData(arch);
	XScene::GetInstance()->SaveData(arch);
}

CWnd* XInternalManage::GetCWND()
{
	return m_pDelagate->GetCWND();
}

HWND XInternalManage::GetHWND()
{
	return m_pDelagate->GetHWND();
}

void XInternalManage::RibbonBarShowCategory(DWORD_PTR dwData)
{
	//菜单栏切换
	int nIndex=0;
	XBaseViewManage* pBaseView=GetBaseViewManageByData(dwData,nIndex);
	if(NULL==pBaseView)
		return;

	//if(m_pBaseViewManage!=pBaseView)
	{
		if(NULL!=m_pBaseViewManage)
		{
			m_pBaseViewManage=pBaseView;

			if(NULL!=m_pViewTabCtrl)
			{
				m_pViewTabCtrl->SetActiveTab(nIndex);
			}
				
			//重置左侧面板
			m_pBaseViewManage->ResetLeftWnd();
			//切换场景树
			if(m_bLogin)
				m_pBaseViewManage->ResetSceneWnd();
			//重置视图
			m_pBaseViewManage->ResetView();
		}
	}
}

XBaseViewManage* XInternalManage::GetBaseViewManageByData(DWORD_PTR dwData,int& nIndex)
{
	DWORD_PTR dwDataMain=DWORD_PTR(_T("主页"));
	DWORD_PTR dwDataSeatArray=DWORD_PTR(_T("坐席编排"));
	DWORD_PTR dwDataMatrixArray=DWORD_PTR(_T("矩阵切换"));
	DWORD_PTR dwDataSplit=DWORD_PTR(_T("拼接"));

	XBaseViewManage* pBaseView=NULL;

	if(dwData==dwDataMain)
	{
		nIndex=0;
		pBaseView=m_MapBaseView[nIndex];
	}
	else if(dwData==dwDataSeatArray)
	{
		nIndex=1;
		pBaseView=m_MapBaseView[nIndex];
	}
	else if(dwData==dwDataMatrixArray)
	{
		nIndex=2;
		pBaseView=m_MapBaseView[nIndex];
	}
	else if(dwData==dwDataSplit)
	{
		if(m_MapBaseView.find(m_nSplitIndex)!=m_MapBaseView.end())
		{
			nIndex=m_nSplitIndex;
			pBaseView=m_MapBaseView[nIndex];
		}
		else
		{
			nIndex=3;
			pBaseView=m_MapBaseView[0];
		}
	}
	return pBaseView;
}

void XInternalManage::ControlDataChange(XDATATYPE type)
{
	m_pRibbonBarManage->ControlDataChange(type);
}

void XInternalManage::UpdateControlDataShow(XDATATYPE type)
{
	m_pRibbonBarManage->UpdateControlDataShow(type);
}

void XInternalManage::ReloadInterface()
{
	ReloadDocTitle();

	m_pRibbonBarManage->ReloadInterface();
	m_pBaseViewManage->ReloadInterface();
	XLeftWnd::GetInstance()->ReloadInterface();
	XPropertiesWnd::GetInstance()->ReloadInterface();
	XStatusBar::GetInstance()->ReloadInterface();
	XScene::GetInstance()->ReloadInterface();
}

void XInternalManage::ReloadDocTitle()
{
	//翻译页面标题，用户自定义无法翻译
	CWinApp* pApp=AfxGetApp();
	POSITION pos=pApp->GetFirstDocTemplatePosition();
	while(pos!=NULL)
	{
		CDocTemplate *pTemplate=pApp->GetNextDocTemplate(pos);
		POSITION posDoc=pTemplate->GetFirstDocPosition();
		while(posDoc!=NULL)
		{
			CDocument* pDoc=pTemplate->GetNextDoc(posDoc);
			if(pDoc!=NULL)
			{
				POSITION posView=pDoc->GetFirstViewPosition();
				if(posView!=NULL)
				{
					CTemplateView* pView=(CTemplateView*)pDoc->GetNextView(posView);
					XBaseViewManage* pBase=pView->GetBaseViewManage();
					if(NULL!=pBase)
					{
						CString szTitle=pBase->GetTitle();
						szTitle.Trim();

						if(szTitle==_T("设备运维状态"))
						{
							CString szTempTitle=_C(_T("75"),_T("设备运维状态"));
							CString szDocTitle=GetDocTitle(szTempTitle);
							pDoc->SetTitle(szDocTitle);
						}
						else if(szTitle==_T("坐席编排"))
						{
							CString szTempTitle=_C(_T("76"),_T("坐席编排"));
							CString szDocTitle=GetDocTitle(szTempTitle);
							pDoc->SetTitle(szDocTitle);
						}
						else if(szTitle==_T("矩阵切换"))
						{
							CString szTempTitle=_C(_T("252"),_T("矩阵切换"));
							CString szDocTitle=GetDocTitle(szTempTitle);
							pDoc->SetTitle(szDocTitle);
						}
					}
				}
			}
		}
	}
}

void XInternalManage::HandleUDPData(unsigned char* pData,int nDataLen,SOCKADDR_IN addr)
{
	if(pData[0]==0xFF&&pData[1]==0x00)
	{
		//检验校验和
		//////////////////////////////////////////////////////////////////////////
		if(m_pReciveDataManage->HandleUDPData(pData,nDataLen,addr))
			return;
	}
	else if(pData[0]==0xFF&&pData[1]==0x01)
	{
		//检验校验和
		//////////////////////////////////////////////////////////////////////////
		//总包数
		int nPacket=0;
		memcpy(&nPacket,pData+2,2);

		//包序号
		int nPacketIndex=0;
		memcpy(&nPacketIndex,pData+4,2);

		//协议号
		int nProtocol;
		memcpy(&nProtocol,pData+8,2);

		if(nPacketIndex==1)
		{
			//有一个包记录包信息
			m_nProtocol=nProtocol;
			m_nPacket=nPacket;
			m_nPacketIndex=nPacketIndex;

			//每次进第一个包时，清空集合
			if(nProtocol!=m_nProtocol)
			{
				ClearMapData();
			}
			//////////////////////////////////////////////////////////////////////////
			int nTempLen=nDataLen-2;

			MAP_DATA::iterator iter=m_MapData.find(nPacketIndex);
			if(iter!=m_MapData.end())
			{
				XData* pTempData=iter->second;
				pTempData->SetPacket(nPacket);
				pTempData->SetPacketIndex(nPacketIndex);
				pTempData->SetDataLen(nTempLen);

				pTempData->DeleteData();
				pTempData->SetData(pData);
			}
			else
			{
				XData* pTempData=new XData;
				pTempData->SetPacket(nPacket);
				pTempData->SetPacketIndex(nPacketIndex);
				pTempData->SetDataLen(nTempLen);

				pTempData->DeleteData();
				pTempData->SetData(pData);

				m_MapData.insert(std::pair<int,XData*>(nPacketIndex,pTempData));
			}
		}
		else
		{
			int nTempLen=nDataLen-10;
			pData+=8;

			MAP_DATA::iterator iter=m_MapData.find(nPacketIndex);
			if(iter!=m_MapData.end())
			{
				XData* pTempData=iter->second;
				pTempData->SetPacket(nPacket);
				pTempData->SetPacketIndex(nPacketIndex);
				pTempData->SetDataLen(nTempLen);

				pTempData->DeleteData();
				pTempData->SetData(pData);
			}
			else
			{
				XData* pTempData=new XData;
				pTempData->SetPacket(nPacket);
				pTempData->SetPacketIndex(nPacketIndex);
				pTempData->SetDataLen(nTempLen);

				pTempData->DeleteData();
				pTempData->SetData(pData);

				m_MapData.insert(std::pair<int,XData*>(nPacketIndex,pTempData));
			}
		}
		//////////////////////////////////////////////////////////////////////////
		if(m_MapData.size()==nPacket)
		{
			//发送
			int nSendDataLen=0;
			for(auto iter=m_MapData.begin();iter!=m_MapData.end();++iter)
			{
				XData* pTemp=iter->second;
				nSendDataLen+=pTemp->GetDataLen();
			}

			unsigned char* pSendData=new unsigned char[nSendDataLen];
			memset(pSendData,0,nSendDataLen);

			int nPos=0;
			for(auto iter=m_MapData.begin();iter!=m_MapData.end();++iter)
			{
				XData* pTempData=iter->second;

				memcpy(pSendData+nPos,pTempData->GetData(),pTempData->GetDataLen());
				nPos+=pTempData->GetDataLen();
			}

			if(m_pReciveDataManage->HandleUDPData(pSendData,nSendDataLen,addr))
			{
				delete[]pSendData;
				ClearMapData();
				return;
			}

			delete[]pSendData;
			ClearMapData();
		}
	}
}

//BOOL XInternalManage::CheckDataSum(char* pData,int& nLen)
//{
//	char* data=new char[nLen];
//	char* pTempData=pData;
//	memcpy(data,pTempData,nLen);
//	unsigned short nSum=CheckSum(data,nLen);
//	delete []data;
//
//	char* pTemp=pData;
//	unsigned short nTempSum=0;
//	memcpy(&nTempSum,pTemp+nLen,2);
//	unsigned short nReSum=nTempSum&0xFF;
//	if(nSum!=nReSum)
//	{
//		return FALSE;
//	}
//	else
//	{
//		return TRUE;
//	}
//}
//
//unsigned short XInternalManage::CheckSum(unsigned char* pData,int nLen)
//{
//	unsigned short nSum=0;
//	for(int i=0;i<nLen;i++)
//	{
//		nSum+=pData[i];
//	}
//	return nSum;
//}

BOOL XInternalManage::GetNetStatus()
{
	return m_pBaseNetManage->GetState();
}

void XInternalManage::HandleUDPMsg(WPARAM wParam,LPARAM lParam)
{
	m_pBaseNetManage->HandleUDPMsg(wParam,lParam);
}

CString XInternalManage::GetCurIP()
{
	return m_szCurDeviceIP;
}

int XInternalManage::GetCurPort()
{
	return m_nCurDevicePort;
}

CString XInternalManage::GetDeviceIP()
{
	return m_szIPAddr1;
}

int XInternalManage::GetDevicePort()
{
	return m_nPort1;
}

CString XInternalManage::GetDevice2IP()
{
	return m_szIPAddr2;
}

int XInternalManage::GetDevice2Port()
{
	return m_nPort2;
}

CString XInternalManage::GetDeviceMask()
{
	return m_szMask1;
}
CString XInternalManage::GetDevice2Mask()
{
	return m_szMask2;
}
CString XInternalManage::GetDeviceGateway()
{
	return m_szGateway1;
}
CString XInternalManage::GetDevice2Gateway()
{
	return m_szGateway2;
}

void XInternalManage::SetSendApplyTime(DWORD dwTime)
{
	m_dwApplyTime=dwTime;
}

void XInternalManage::SetDeviceSelect(int nSelect)
{
	m_nDeviceSelect=nSelect;
}

void XInternalManage::ConnectNetSelect()
{
	if(m_nDeviceSelect==0)
	{
		m_szCurDeviceIP=m_szIPAddr1;
		m_nCurDevicePort=m_nPort1;
	}
	else if(m_nDeviceSelect==1)
	{
		m_szCurDeviceIP=m_szIPAddr2;
		m_nCurDevicePort=m_nPort2;
	}

	XStatusBar::GetInstance()->SetDevideNet(m_szCurDeviceIP,m_nCurDevicePort);
	//保存选择
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	CString szDeviceSel;
	szDeviceSel.Format(_T("%d"),m_nDeviceSelect);
	HandleIni::WriteData(_T("Info"),_T("DeviceSelect"),szDeviceSel,szIniPath);
}

void XInternalManage::OperateOfReNetConfig(char* pData)
{
	ClearNetConfig();
	XResult result;
	XJsonManage::GetInstance()->ParseJsonToReNetConfig(pData,m_VecNetConfig,result);
	if(result.GetResult()==0)
	{
		if(result.GetSendType()==_T("QUERY"))
		{
			//默认使用第一个IP和端口
			if(m_VecNetConfig.size()!=0)
			{
				XNetConfig* pNetConfig=m_VecNetConfig[0];

				m_szCurDeviceIP=pNetConfig->GetIP();
				m_nCurDevicePort=pNetConfig->GetPort();

				//如果读到更新界面
				if(NULL!=m_pDeviceNet)
				{
					m_pDeviceNet->ResetShowData(m_VecNetConfig);
				}
			}
		}
		else if(result.GetSendType()==_T("APPLY"))
		{
			//应用有可能失败，失败终止，重启设备，成功之后再保存 
			DWORD dwTime=GetTickCount();	
			if((long)dwTime-(long)m_dwApplyTime<3000)
			{
				if(NULL!=m_pDeviceNet)
				{
					if(m_VecNetConfig.size()!=0)
					{
						XNetConfig* pNetConfig=m_VecNetConfig[0];
						m_szCurDeviceIP=pNetConfig->GetIP();
						m_nCurDevicePort=pNetConfig->GetPort();
					}

					//生效 发送IP要改成当前IP
					m_pDeviceNet->StopTimer();
					m_pDeviceNet->SaveNetConfig();
				}
			}
		}
		else if(result.GetSendType()==_T("SAVE"))
		{
			//保存，成功后更改IP
			if(m_VecNetConfig.size()!=0)
			{
				XNetConfig* pNetConfig=m_VecNetConfig[0];

				m_szCurDeviceIP=pNetConfig->GetIP();
				m_nCurDevicePort=pNetConfig->GetPort();

				//要根据选择来保存配置文件
				CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
				if(m_nDeviceSelect==0)
				{
					HandleIni::WriteData(_T("Info"),_T("IP1"),pNetConfig->GetIP(),szIniPath);

					CString szPort1;
					szPort1.Format(_T("%d"),pNetConfig->GetPort());
					HandleIni::WriteData(_T("Info"),_T("Port1"),szPort1,szIniPath);
					HandleIni::WriteData(_T("Info"),_T("Mask1"),pNetConfig->GetMask(),szIniPath);
					HandleIni::WriteData(_T("Info"),_T("Gateway1"),pNetConfig->GetGateway(),szIniPath);
				}
				else if(m_nDeviceSelect==1)
				{
					HandleIni::WriteData(_T("Info"),_T("IP2"),pNetConfig->GetIP(),szIniPath);

					CString szPort1;
					szPort1.Format(_T("%d"),pNetConfig->GetPort());
					HandleIni::WriteData(_T("Info"),_T("Port2"),szPort1,szIniPath);
					HandleIni::WriteData(_T("Info"),_T("Mask2"),pNetConfig->GetMask(),szIniPath);
					HandleIni::WriteData(_T("Info"),_T("Gateway2"),pNetConfig->GetGateway(),szIniPath);
				}

				//保存之后，要更新数值
				InitIPAddr();

				if(NULL!=m_pDeviceNet)
				{
					m_pDeviceNet->CloseDialog();
				}	
			}
		}
	}
}

BOOL XInternalManage::SendData(char* pData,int nDataLen)
{
	BOOL bResult=FALSE;

	if((nullptr!=pData)&&(nDataLen>0))
	{
		if(NULL!=m_pBaseNetManage)
			bResult=m_pBaseNetManage->SendData(m_szCurDeviceIP,m_nCurDevicePort,pData,nDataLen);
	}

	return bResult;
}

void XInternalManage::SetIPAddr1(CString szIP)
{
	m_szIPAddr1=szIP;
}

void XInternalManage::SetIPAddr2(CString szIP)
{
	m_szIPAddr2=szIP;
}

void XInternalManage::SetPort1(int n)
{
	m_nPort1=n;
}

void XInternalManage::SetPort2(int n)
{
	m_nPort2=n;
}

void XInternalManage::InitIPAddr()
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	//首先获取设备选择
	m_nDeviceSelect=HandleIni::GetInt(_T("Info"),_T("DeviceSelect"),0,szIniPath);

	m_szIPAddr1=HandleIni::GetString(_T("Info"),_T("IP1"),_T(""),szIniPath);
	m_nPort1=HandleIni::GetInt(_T("Info"),_T("Port1"),0,szIniPath);
	m_szMask1=HandleIni::GetString(_T("Info"),_T("Mask1"),0,szIniPath);
	m_szGateway1=HandleIni::GetString(_T("Info"),_T("Gateway1"),0,szIniPath);

	m_szIPAddr2=HandleIni::GetString(_T("Info"),_T("IP2"),_T(""),szIniPath);
	m_nPort2=HandleIni::GetInt(_T("Info"),_T("Port2"),0,szIniPath);
	m_szMask2=HandleIni::GetString(_T("Info"),_T("Mask2"),0,szIniPath);
	m_szGateway2=HandleIni::GetString(_T("Info"),_T("Gateway2"),0,szIniPath);

	if(m_nDeviceSelect==0)
	{
		m_szCurDeviceIP=m_szIPAddr1;
		m_nCurDevicePort=m_nPort1;
	}
	else if(m_nDeviceSelect==1)
	{
		m_szCurDeviceIP=m_szIPAddr2;
		m_nCurDevicePort=m_nPort2;
	}
	//初始化状态栏IP
	XStatusBar::GetInstance()->SetDevideNet(m_szCurDeviceIP,m_nCurDevicePort);
}

void XInternalManage::OperateOfDeviceNet()
{
	XDeviceNet dlg;
	m_pDeviceNet=&dlg;
	dlg.SetDelegate(this);
	dlg.SetRadioSelect(m_nDeviceSelect);
	dlg.DoModal();

	m_pDeviceNet=nullptr;
}

static UINT SendHeatThread(void* p)
{
	XInternalManage* pManage=(XInternalManage*)p;
	while(pManage->m_bRunning)
	{
		pManage->OperateOfHeart();
		Sleep(2000);
	}

	if(NULL!=pManage->m_HeartThreadEvent)
	{
		SetEvent(pManage->m_HeartThreadEvent);
	}

	return 0;
}

BOOL XInternalManage::BeginHeartThread()
{
	m_bRunning=TRUE;
	m_HeartThreadEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	if(NULL!=m_HeartThreadEvent)
	{
		CWinThread* pThread=AfxBeginThread((AFX_THREADPROC)SendHeatThread,(void*)this);
		if(NULL==pThread)
		{
			CloseHeartThreadEvent();
			//TRACE("main_thread AfxBeginThread failed\n");
			m_bRunning=FALSE;
		}
	}
	else
	{
		m_bRunning=FALSE;
	}

	return m_bRunning;
}

void XInternalManage::StopHeartThread()
{
	m_bRunning=FALSE;
	if(m_HeartThreadEvent!=NULL)
	{
		WaitForSingleObject(m_HeartThreadEvent,INFINITE);
		CloseHandle(m_HeartThreadEvent);
		m_HeartThreadEvent=NULL;
	}
}

void XInternalManage::CloseHeartThreadEvent()
{
	if(m_HeartThreadEvent!=NULL)
	{
		CloseHandle(m_HeartThreadEvent);
		m_HeartThreadEvent=NULL;
	}
}

void XInternalManage::OperateOfHeart()
{
	m_dHeartTime=GetTickCount();
	XSendDataManage::GetInstance()->SendDataOfHeart(m_dHeartTime);
}

void XInternalManage::OperateOfReHeart(char* pData)
{
	long dCurTime=GetTickCount();

	long dHeartTime=0;
	memcpy(&dHeartTime,pData,4);

	if(abs(dCurTime-dHeartTime)>=1000)
	{
		m_bOnline=FALSE;
	}
	else
	{
		m_bOnline=TRUE;
	}
}

void XInternalManage::ChangeTheme(int nType)
{
	m_pDelagate->ChangeTheme(nType);
}

void XInternalManage::ClearConChannel()
{
	m_pNodeManage->ClearConChannel();
}

void XInternalManage::ClearNode()
{
	m_pNodeManage->ClearNode();
}

void XInternalManage::ClearCloumn()
{
	m_pNodeManage->ClearCloumn();
}

void XInternalManage::ClearUserLoginStatus()
{
	m_pNodeManage->ClearUserLoginStatus();
}

void XInternalManage::ClearUserIDALL()
{
	m_pUserManage->ClearUserIDALL();
}
void XInternalManage::ClearTree()
{
	XLeftWnd::GetInstance()->ClearTree();
}

void XInternalManage::ClearNodeGroup()
{
	m_pNodeManage->ClearNodeGroup();
}

void XInternalManage::ClearInfo(CString szGroupName)
{
	m_pSeatArrageManage->ClearInfo(szGroupName);
}

void XInternalManage::ClearPage()
{
	m_pSeatArrageManage->ClearPage();
}

void XInternalManage::ClearSceneTree()
{
	XScene::GetInstance()->ClearSceneTree();
}

void XInternalManage::UpdateGroupNameAfterAddArrage(CString szName)
{
	m_pSeatArrageManage->UpdateGroupNameAfterAddArrage(szName);
}

void XInternalManage::MatchSeatNameByGroupName()
{
	m_pSeatArrageManage->MatchSeatNameByGroupName();
}

void XInternalManage::UpdateGroupNameAfterChange(CString szGroupName,CString szName)
{
	m_pSeatArrageManage->UpdateGroupNameAfterChange(szGroupName,szName);
}

void XInternalManage::UpdateGroupArrageByRemoveNode(CString szGroupName,int nNodeID)
{
	m_pSeatArrageManage->UpdateGroupArrageByRemoveNode(szGroupName,nNodeID);
}

void XInternalManage::UpdateScreenAfterRemoveNode(int nNodeID)
{
	m_pSeatArrageManage->UpdateScreenAfterRemoveNode(nNodeID);
}

void XInternalManage::UpdateShowMasterAfterRemoveNode(int nMaster)
{
	m_pSeatArrageManage->UpdateShowMasterAfterRemoveNode(nMaster);
}

MAP_SUBUSER& XInternalManage::GetMapSubUser()
{
	return m_pUserManage->GetMapSubUser();
}

MAP_POWER& XInternalManage::GetMapPower()
{
	return m_pUserManage->GetMapPower();
}

MAP_MATRIX& XInternalManage::GetMapMatrix()
{
	return m_pNodeManage->GetMapMatrix();
}

MAP_NODE& XInternalManage::GetMapNode()
{
	return m_pNodeManage->GetMapNode();
}

MAP_NODEALL& XInternalManage::GetMapNodeAll()
{
	return m_pNodeManage->GetMapNodeAll();
}

MAP_NODEMAINSEC& XInternalManage::GetMapNodeMainSec()
{
	return m_pNodeManage->GetMapNodeMainSec();
}

MAP_NODEGROUP& XInternalManage::GetMapNodeGroup()
{
	return m_pNodeManage->GetMapNodeGroup();
}

MAP_GROUPMAINSEC& XInternalManage::GetMapNodeGroupMainSec()
{
	return m_pNodeManage->GetMapGroupMainSec();
}

VEC_DEL& XInternalManage::GetVecDel()
{
	return XLeftWnd::GetInstance()->GetVecDel();
}

VEC_USERIDALL& XInternalManage::GetVecUserIDAll()
{
	return m_pUserManage->GetVecUserAll();
}

MAP_BASEVIEW& XInternalManage::GetBaseView()
{
	return m_MapBaseView;
}

void XInternalManage::InsertItemToTree(CString szUserName)
{
	XLeftWnd::GetInstance()->InsertItemToTree(szUserName);
}

void XInternalManage::DeleteItemFromTree(CString szUserName)
{
	XLeftWnd::GetInstance()->DeleteItemFromTree(szUserName);
}

void XInternalManage::SetPropertyValue(CString szUserName)
{
	m_pNodeManage->SetPropertyValue(szUserName);
}

void XInternalManage::SetNodeSelected(CString szNodeName)
{
	m_pSeatArrageManage->SetNodeSelected(szNodeName);
}

void XInternalManage::DragEnd(CPoint& point,CRect& rect)
{
	m_pBaseViewManage->DragEnd(point,rect);
}

void XInternalManage::ShowGroupSeatArrage(CString szGroup)
{
	m_pSeatArrageManage->ShowGroupSeatArrage(szGroup);
}

void XInternalManage::SetViewColor(Color& color)
{
	m_pBaseViewManage->SetViewColor(color);
	//m_pNodeManage->SetViewColor(color);
	//m_pSeatArrageManage->SetViewColor(color);
	//m_pMatrixManage->SetViewColor(color);
}

void XInternalManage::DelNodeFromGroup(CString szGroupName,int nNodeID)
{
	m_pSeatArrageManage->DelNodeFromGroup(szGroupName,nNodeID);
}

BOOL XInternalManage::JudgetDelNodeFromGroup(CString szGroupName,int nNodeID)
{
	return m_pSeatArrageManage->JudgetDelNodeFromGroup(szGroupName,nNodeID);
}

void XInternalManage::DragGroupToSeat(CString szGroupName,CPoint& point)
{
	m_pSeatArrageManage->DragGroupToSeat(szGroupName,point);
}

void XInternalManage::SwitchPage(int nPage)
{
	m_pSeatArrageManage->SwitchPage(nPage);
}

void XInternalManage::HidePopMenuBtn()
{
	m_pSeatArrageManage->HidePopMenuBtn();
}

void XInternalManage::ShowPopMenuBtn()
{
	m_pSeatArrageManage->ShowPopMenuBtn();
}

void XInternalManage::DrawGroupInScreen(CString szGroupName)
{
	m_pSeatArrageManage->DrawGroupInScreen(szGroupName);
}

void XInternalManage::SetSeatSelected(CString szGroupName)
{
	m_pSeatArrageManage->SetSeatSelected(szGroupName);
}

void XInternalManage::HideMenuWnd()
{
	m_pSeatArrageManage->HideMenuWnd();
	m_pSeatArrageManage->HideBtn();
	m_pSeatArrageManage->Unselected();
	m_pSeatArrageManage->MoveSeatDrawWnd();
}

int XInternalManage::GetPageIndex()
{
	if(NULL!=m_pSeatArrageManage)
		return m_pSeatArrageManage->GetPageIndex();
	return 1;
}

void XInternalManage::ResetRibbonBar()
{
	m_pRibbonBarManage->ResetRibbonBar();
	//m_pRibbonBarManage->SetActiveCategory(1);
}

//void XInternalManage::OperateOfControl()
//{
//	//中控
//	XCenterControl dlg;
//	dlg.DoModal();
//}

void XInternalManage::OperateOfUpdate()
{
	//TRACE(_T("Update\n"));
	XUpdate update;
	update.SetDelegate(this);
	update.DoModal();
}

//调用场景
void XInternalManage::OpenScene(int nData)
{
	switch(nData)
	{
		case SCENETYPE_SCENE:
			{
				m_pBaseViewManage->Operate(OPERATETYPE_OPENTAKEOVERSCENE,NULL);
			}
			break;
		case SCENETYPE_SPLIT:
			{
				OperateOfOpenScene();
			}
			break;
		case SCENETYPE_SPLITWALL:
			{
				OperateOfOpenSceneOne();
			}
			break;
		default:
			break;
	}
}

void XInternalManage::OperateOfLog()
{
	//发送RTC时间
	XSendDataManage::GetInstance()->AddSendDataOfRTCTime();

	//日志
	XLog dlg;
	dlg.SetDelelgate(this);
	m_pLogDlg=&dlg;
	dlg.DoModal();
	m_pLogDlg=NULL;
}

void XInternalManage::OperateOfReLog(char* pData)
{
	if(NULL==m_pLogDlg)
		return;
	m_pLogDlg->OperateOfReLog(pData);
}

void XInternalManage::ResetMatrixArray()
{
	if(NULL!=m_pMatrixManage)
		m_pMatrixManage->ResetMatrixArray();
}

void XInternalManage::ResetMatrixSwitchStatus()
{
	if(NULL!=m_pMatrixManage)
		m_pMatrixManage->ResetMatrixSwitchStatus();
}

void XInternalManage::SetGroupNameByAddGroupIn(CString szName)
{
	m_pSeatArrageManage->SetGroupNameByAddGroupIn(szName);
}

void XInternalManage::OperateOfStatusTime()
{
	XStatusBar::GetInstance()->UpdateTime();
}

void XInternalManage::OperateOfClearSplitView()
{
	for(auto iter=m_MapBaseView.begin();iter!=m_MapBaseView.end();)
	{
		XBaseViewManage* pBaseView=iter->second;
		if(pBaseView->GetSplitName()!=_T(""))
		{
			int nIndex=pBaseView->GetBaseIndex();
			iter=m_MapBaseView.erase(iter);

			delete pBaseView;

			//关闭页面
			CMDIChildWnd* pChildWnd=dynamic_cast <CMDIChildWnd*>(m_pViewTabCtrl->GetTabWnd(3));
			((CChildFrame*)pChildWnd)->DestroyMDI();
		}
		else
		{
			++iter;
		}
	}
}

void XInternalManage::OperateOfAddSplit()
{
	//添加拼接屏(具体怎样添加，结合设备)
	XAddSplit dlg;
	if(IDOK==dlg.DoModal())
	{
		CString szName=dlg.GetSplitName();
		int nRow=dlg.GetRow();
		int nColumn=dlg.GetColumn();
		//先按默认创建

		XSplitResult splitInfo;
		splitInfo.m_szSplitName=szName;
		splitInfo.m_nSplitID=0;
		splitInfo.m_nCutUse=0;
		splitInfo.m_VecCutPix.push_back(8);
		splitInfo.m_VecCutPix.push_back(0);
		splitInfo.m_VecCutPix.push_back(8);
		splitInfo.m_VecCutPix.push_back(0);
		splitInfo.m_nPixIndex=0;
		splitInfo.m_nReaulationH=3840;
		splitInfo.m_nReaulationV=2160;
		splitInfo.m_nScreenCountX=nColumn;
		splitInfo.m_nScreenCountY=nRow;

		int nSplitCh=1;
		for(int i=0;i<nRow;i++)
		{
			for(int j=0;j<nColumn;j++)
			{
				splitInfo.m_VecSplitCh.push_back(nSplitCh);
				nSplitCh++;
			}
		}
		XSendDataManage::GetInstance()->AddSendDataOfAddSplit(splitInfo);
	}
}

void XInternalManage::OperateOfObtainSplit()
{
	//获取拼接墙
	XSendDataManage::GetInstance()->AddSendDataOfObtainSplit();
}

void XInternalManage::OperateOfSplit(char* pData)
{
	//拼接墙返回数据，放在这里
	XSplitResult result;
	XJsonManage::GetInstance()->ParseJsonToReSplit(pData,m_MapBaseView,result);

	if(result.GetSendType()==_T("LIST"))
	{
		//TRACE(_T("LIST\n"));
		if(result.GetResult()!=0)
			return;
		//根据结果查询拼接墙信息
		for(auto& map:m_MapBaseView)
		{
			XBaseViewManage* pBaseView=map.second;
			CString szSplitName=pBaseView->GetSplitName();
			if(_T("")!=szSplitName)
			{
				XSendDataManage::GetInstance()->AddSendDataOfQuerySplitWall(szSplitName);
				//获取拼接墙窗口
				XSendDataManage::GetInstance()->AddSendDataOfObtainSplitWindow(szSplitName,TRUE);
			}
		}
	}
	else if(result.GetSendType()==_T("QUERY"))
	{
		if(result.GetResult()!=0)
			return;

		CString szName=result.m_szSplitName;
		//创建拼接屏
		for(auto& map:m_MapBaseView)
		{
			XBaseViewManage* pBaseView=map.second;
			CString szSplitName=pBaseView->GetSplitName();
			if(szName!=_T("")&&szName==szSplitName)
			{
				((XSplitManage*)pBaseView)->SetDelegate(this);
				CString szTitle=GetDocTitle(pBaseView->GetSplitName());
				((XSplitManage*)pBaseView)->SetTitle(szTitle);
				((XSplitManage*)pBaseView)->Init();
				((XSplitManage*)pBaseView)->SetScreenInfo();

				AddDocument(pBaseView);
			}
		}
		//显示第一个
		if(NULL!=m_pViewTabCtrl)
		{
			m_pViewTabCtrl->SetActiveTab(0);
		}
	}
	else if(result.GetSendType()==_T("ADD"))
	{
		if(result.GetResult()!=0)
			return;

		CString szName=result.m_szSplitName;
		//创建拼接屏
		for(auto& map:m_MapBaseView)
		{
			XBaseViewManage* pBaseView=map.second;
			CString szSplitName=pBaseView->GetSplitName();
			if(szName!=_T("")&&szName==szSplitName)
			{
				((XSplitManage*)pBaseView)->SetDelegate(this);
				CString szTitle=GetDocTitle(pBaseView->GetSplitName());
				((XSplitManage*)pBaseView)->SetTitle(szTitle);
				((XSplitManage*)pBaseView)->Init();
				((XSplitManage*)pBaseView)->SetScreenInfo();

				AddDocument(pBaseView);
				//设置当前视图
				m_pBaseViewManage=((XSplitManage*)pBaseView);
				m_nSplitIndex=((XSplitManage*)pBaseView)->GetBaseIndex();
				m_pRibbonBarManage->SetActiveCategory(m_nSplitIndex);

				//TRACE(_T("Index=%d\n"),m_nSplitIndex);

				//配置生效
				XSendDataManage::GetInstance()->AddSendDataOfRefreashSplit(szName);
			}
		}
	}
	else if(result.GetSendType()==_T("DEL"))
	{
		if(result.GetResult()!=0)
			return;

		CString szName=result.m_szSplitName;
		if(szName!=_T(""))
		{
			//删除拼接墙		
			for(auto iter=m_MapBaseView.begin();iter!=m_MapBaseView.end();)
			{
				XBaseViewManage* pBaseView=iter->second;
				if(pBaseView->GetSplitName()==szName)
				{
					int nIndex=pBaseView->GetBaseIndex();
					//关闭页面
					CMDIChildWnd* pChildWnd=dynamic_cast <CMDIChildWnd*>(m_pViewTabCtrl->GetTabWnd(nIndex));
					((CChildFrame*)pChildWnd)->DestroyMDI();
					//////////////////////////////////////////////////////////////////////////
					//清理集合
					iter=m_MapBaseView.erase(iter);
					delete pBaseView;
					//设置当前激活页面
					int nTemp=nIndex-1;
					if(nTemp==-1)
					{
						m_pBaseViewManage=NULL;
					}
					else
					{
						if(m_MapBaseView.find(nTemp)!=m_MapBaseView.end())
						{
							m_pBaseViewManage=m_MapBaseView[nTemp];
							m_pViewTabCtrl->SetActiveTab(nTemp);
						}
					}

					//配置生效
					XSendDataManage::GetInstance()->AddSendDataOfRefreashSplit(szName);
				}
				else
				{
					++iter;
				}
			}
		}
	}
}

void XInternalManage::OperateOfSplitWindow(char* pData)
{
	XSplitWindow result;
	XJsonManage::GetInstance()->ParseJsonToReSplitWondow(pData,m_MapBaseView,result);

	if(result.GetSendType()==_T("LIST"))
	{
		if(result.GetResult()!=0)
			return;

		if(result.GetSubSendType()==_T("FIRST"))
		{
			//第一次查询 新建信号
			for(auto& map:m_MapBaseView)
			{
				XBaseViewManage* pBaseView=map.second;
				if(result.m_szSplitName!=_T("")&&result.m_szSplitName==pBaseView->GetSplitName())
				{
					auto& VecIdList=((XSplitManage*)pBaseView)->GetVecIdList();
					((XSplitManage*)pBaseView)->AddSignal(VecIdList);



					//auto& VecSignal=((XSplitManage*)pBaseView)->GetVecSignal();
					//((XSplitManage*)pBaseView)->ClearVecSignal();
					//auto& VecIdList=((XSplitManage*)pBaseView)->GetVecIdList();
					//int nLevel=1;
					//for(auto& nID:VecIdList)
					//{
					//	XSignal* pSignal=new XSignal;
					//	pSignal->SetSignalID(nID);
					//	pSignal->SetLevel(nLevel);
					//	VecSignal.push_back(pSignal);
					//	nLevel++;
					//	XSendDataManage::GetInstance()->AddSendDataOfObtainSplitWindowInfo(result.m_szSplitName,nID);
					//}
				}
			}
		}
		else if(result.GetSubSendType()==_T("NOFIRST"))
		{
			//TRACE(_T("NoFirst\n"));
			//只用于设置层次
			for(auto& map:m_MapBaseView)
			{
				XBaseViewManage* pBaseView=map.second;
				if(result.m_szSplitName!=_T("")&&result.m_szSplitName==pBaseView->GetSplitName())
				{
					auto& VecIdList=((XSplitManage*)pBaseView)->GetVecIdList();
					
					int nLevel=1;
					for(auto& nID:VecIdList)
					{
						((XSplitManage*)pBaseView)->SetSignalLevel(nID,nLevel);
						nLevel++;
					}

					//排序
					((XSplitManage*)pBaseView)->SortSignalByLevel();
				}
			}
		}
	}
	else if(result.GetSendType()==_T("QUERY"))
	{
		if(result.GetResult()!=0)
			return;

		//按照层次排序
		for(auto& map:m_MapBaseView)
		{
			XBaseViewManage* pBaseView=map.second;
			if(result.m_szSplitName!=_T("")&&result.m_szSplitName==pBaseView->GetSplitName())
			{
				//1.先排序
				((XSplitManage*)pBaseView)->SortSignalByLevel();
				//2.计算区域以及颜色
				((XSplitManage*)pBaseView)->SetSignalOtherInfo();
			}
		}
	}
	else if(result.GetSendType()==_T("ADD"))
	{
		if(result.GetResult()!=0)
			return;

		for(auto& map:m_MapBaseView)
		{
			XBaseViewManage* pBaseView=map.second;
			if(result.m_szSplitName!=_T("")&&result.m_szSplitName==pBaseView->GetSplitName())
			{
				//1.先排序
				((XSplitManage*)pBaseView)->SortSignalByLevel();
				//2.计算区域以及颜色
				((XSplitManage*)pBaseView)->SetSignalOtherInfo(result.m_nSignalID);
			}
		}

		//绘制指令
		XSendDataManage::GetInstance()->AddSendDataOfDraw(result.m_szSplitName);
		//配置生效
		XSendDataManage::GetInstance()->AddSendDataOfRefreashSplit(result.m_szSplitName);
		//查询窗口层次占用数
		XSendDataManage::GetInstance()->AddSendDataOfLevelUseList(result.m_szSplitName);
		//获取拼接墙窗口
		XSendDataManage::GetInstance()->AddSendDataOfObtainSplitWindow(result.m_szSplitName,FALSE);
	}
	else if(result.GetSendType()==_T("DEL"))
	{
		if(result.GetResult()!=0)
			return;

		for(auto& map:m_MapBaseView)
		{
			XBaseViewManage* pBaseView=map.second;
			if(result.m_szSplitName!=_T("")&&result.m_szSplitName==pBaseView->GetSplitName())
			{
				//关闭
				((XSplitManage*)pBaseView)->DeleteSignalByID(result.m_nSignalID);
			}
		}
		//绘制指令
		XSendDataManage::GetInstance()->AddSendDataOfDraw(result.m_szSplitName);
		//配置生效
		XSendDataManage::GetInstance()->AddSendDataOfRefreashSplit(result.m_szSplitName);
		//查询窗口层次占用数
		XSendDataManage::GetInstance()->AddSendDataOfLevelUseList(result.m_szSplitName);
	}
	else if(result.GetSendType()==_T("CLEAR"))
	{
	    if(result.GetResult()!=0)
		    return;

		for(auto& map:m_MapBaseView)
		{
			XBaseViewManage* pBaseView=map.second;
			if(result.m_szSplitName!=_T("")&&result.m_szSplitName==pBaseView->GetSplitName())
			{
				//关闭
				((XSplitManage*)pBaseView)->ClearSignal();
			}
		}
		//绘制指令
		XSendDataManage::GetInstance()->AddSendDataOfDraw(result.m_szSplitName);
		//配置生效
		XSendDataManage::GetInstance()->AddSendDataOfRefreashSplit(result.m_szSplitName);
		//查询窗口层次占用数
		XSendDataManage::GetInstance()->AddSendDataOfLevelUseList(result.m_szSplitName);
	}
	else if(result.GetSendType()==_T("LEVEL_USE"))
	{
		//TRACE(_T("LEVEL_USE\n"));
		if(result.GetResult()!=0)
			return;

		for(auto& map:m_MapBaseView)
		{
			XBaseViewManage* pBaseView=map.second;
			if(result.m_szSplitName!=_T("")&&result.m_szSplitName==pBaseView->GetSplitName())
			{
				//关闭
				((XSplitManage*)pBaseView)->SetLevelUse();
			}
		}
	}
	else if(result.GetSendType()==_T("WIN_LEVEL"))
	{
		if(result.GetResult()!=0)
			return;

		//获取拼接墙窗口
		XSendDataManage::GetInstance()->AddSendDataOfObtainSplitWindow(result.m_szSplitName,FALSE);
	}
}

void XInternalManage::CloseSplit(XBaseViewManage* pManage)
{
	int nIndex=pManage->GetBaseIndex();
	auto iter=m_MapBaseView.find(nIndex);
	if(iter!=m_MapBaseView.end())
	{
		XBaseViewManage* pBase=iter->second;
		m_MapBaseView.erase(iter);
		delete pBase;
	}
}

void XInternalManage::CloseSplit()
{
	//发送删除拼接墙
	if(NULL==m_pBaseViewManage)
		return;

	CString szName=m_pBaseViewManage->GetSplitName();
	XSendDataManage::GetInstance()->AddSendDataOfDelSplit(szName);
}

int XInternalManage::GetIndexByAdd()
{
	int nIndex=3;
	while(nIndex)
	{
		if(m_MapBaseView.find(nIndex)==m_MapBaseView.end())
			break;
		nIndex++;
	}
	return nIndex;
}

float XInternalManage::GetCurScale()
{
	return m_pBaseViewManage->GetCurScale();
}

void XInternalManage::OperateOfObtainSplitScene()
{
	XSendDataManage::GetInstance()->AddSendDataOfObtainSplitScene();
}

MAP_SPLITSCENE& XInternalManage::GetMapSplitScene()
{
	return m_MapSplitScene;
}

MAP_SPLITSCENEGROUP& XInternalManage::GetMapSplitSceneGroup()
{
	return m_MapSplitSceneGroup;
}

void XInternalManage::OperateOfOpenScene()
{
	CString szSceneName=XConstantData::GetInstance()->GetOpenSceneName();
	//TRACE(_T("SplitScene=%s\n"),szSceneName);
	//调用全部场景
	if(m_MapSplitScene.find(szSceneName)!=m_MapSplitScene.end())
	{
		XSplitScene* pScene=m_MapSplitScene[szSceneName];
		auto& VecWall=pScene->GetVecWallList();
		for(auto& szWall:VecWall)
		{
			//检查有没有该墙
			int nOpt=0;
			if(DecideWallExistence(szWall))
				nOpt=14;
			else
				nOpt=15;
	
			XSendDataManage::GetInstance()->AddSendDataOfOpenScene(szSceneName,szWall,nOpt);
		}
	}
}

void XInternalManage::OperateOfOpenSceneOne()
{
	CString szSceneName=XConstantData::GetInstance()->GetOpenSceneName();
	CString szWallName=XConstantData::GetInstance()->GetSceneWall();
	//TRACE(_T("SplitScene=%s\n"),szSceneName);
	//TRACE(_T("szWallName=%s\n"),szWallName);
	//调用场景其中一个
	int nOpt=0;
	if(DecideWallExistence(szWallName))
		nOpt=14;
	else
		nOpt=15;
	XSendDataManage::GetInstance()->AddSendDataOfOpenScene(szSceneName,szWallName,nOpt);
}

int XInternalManage::DecideWallExistence(CString szWall)
{
	for(auto& view:m_MapBaseView)
	{
		XBaseViewManage* pBase=view.second;
		if(pBase->GetSplitName()==szWall)
			return pBase->GetBaseIndex();
	}
	return 0;
}

BOOL XInternalManage::DecideSplitGroupHasOneScene(CString szName)
{
	for(auto& scene:m_MapSplitScene)
	{
		XSplitScene* pScene=scene.second;
		if(pScene->m_szSceneGroup==szName)
			return TRUE;
	}

	return FALSE;
}

void XInternalManage::OperateOfSaveSplitScene()
{
	//保存拼接场景
	XSaveSplitScene dlg;
	m_pSplitScene=&dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();

	m_pSplitScene=NULL;
}

void XInternalManage::OperateOfReSplitScene(char* pData)
{
	XSplitSceneResult result;
	XJsonManage::GetInstance()->ParseJsonToReSplitScene(pData,this,result);
	if(result.GetSendType()==_T("LIST"))
	{
		if(result.GetResult()!=0)
			return;
		//获取场景墙列表		
		for(auto& scene:m_MapSplitScene)
		{
			XSplitScene* pScene=scene.second;

			XSendDataManage::GetInstance()->AddSendDataOfObtainSceneGroup(pScene->GetSceneName());
			XSendDataManage::GetInstance()->AddSendDataOfObtainWallList(pScene->GetSceneName());
		}
	}
	else if(result.GetSendType()==_T("LIST_WALL"))
	{
		if(result.GetResult()!=0)
			return;


	}
	else if(result.GetSendType()==_T("ADD"))
	{
		if(result.GetResult()!=0)
			return;

		CString szSceneName=result.m_szSceneName;

		//此时已经添加场景成功（先不在这添加，等添加墙成功后在添加到集合，然后再添加到组）
		//XSplitScene* pScene=new XSplitScene;
		//pScene->SetSceneName(szSceneName);
		//m_MapSplitScene.insert(std::pair<CString,XSplitScene*>(szSceneName,pScene));

		if(NULL!=m_pSplitScene)
		{
			////先设置组 设置组时候 返回会自动添加到组 但是现在还没有墙信息
			//if(_T("")!=m_pSplitScene->GetGroup())
			//	XSendDataManage::GetInstance()->AddSendDataOfSetSceneGroup(szSceneName,m_pSplitScene->GetGroup());


			auto& VecSplit=m_pSplitScene->GetVecSplit();
			//记住最后一次
			int nSize=VecSplit.size();
			for(int i=0;i<nSize;i++)
			{
				CString szWallName=VecSplit[i];
				if(i==nSize-1)
					XSendDataManage::GetInstance()->AddSendDataOfSaveWallToNewScene(szSceneName,szWallName,TRUE);
				else
					XSendDataManage::GetInstance()->AddSendDataOfSaveWallToNewScene(szSceneName,szWallName,FALSE);
			}

			//添加墙成功之后 在划分组 全部添加到树行为都在划分组执行
		}
	}
	else if(result.GetSendType()==_T("SET_GROUP"))
	{
		if(result.GetResult()!=0)
			return;
		
		if(result.m_nAlter)
		{
			CString szOldName=XConstantData::GetInstance()->GetSplitGroup();
			if(result.m_szGroupName==_T(""))
			{
				//从组中删除
			
			    //先删除
				XScene::GetInstance()->DelSplitSceneByItem(result.m_szSceneName);
				//插到最后
				XScene::GetInstance()->AddSplitSceneAtLast(result.m_szSceneName);

				//判断组中有无元素 没有自动删除
				if(!DecideSplitGroupHasOneScene(szOldName))
				{
					auto iter=m_MapSplitSceneGroup.find(szOldName);
					if(iter!=m_MapSplitSceneGroup.end())
					{
						HTREEITEM hItem=m_MapSplitSceneGroup[szOldName];
						XScene::GetInstance()->DelSplitGroupByItem(hItem);

						m_MapSplitSceneGroup.erase(iter);
					}
				}
			}
			else
			{
				//更改组名称
				HTREEITEM hItem=NULL;
				auto iter=m_MapSplitSceneGroup.find(szOldName);
				if(iter!=m_MapSplitSceneGroup.end())
				{
					hItem=iter->second;
					m_MapSplitSceneGroup.erase(iter);
				}

				m_MapSplitSceneGroup.insert(std::pair<CString,HTREEITEM>(result.m_szGroupName,hItem));

			}
		}
		else
		{
			//设置到组
			if(result.m_bNewGroup)
			{
				//新组则添加添加在树中
				XScene::GetInstance()->AddSplitGroup(result.m_szGroupName,result.m_hItem);
			}
			//先删除
			XScene::GetInstance()->DelSplitSceneByItem(result.m_szSceneName);
			//把场景插到树中
			XScene::GetInstance()->AddSplitSceneToGroup(result.m_szGroupName,result.m_szSceneName);
		}
	}
	else if(result.GetSendType()==_T("DEL"))
	{
		if(result.GetResult()!=0)
			return;

		//删除
		auto iter=m_MapSplitScene.find(result.m_szSceneName);
		if(iter!=m_MapSplitScene.end())
		{
			XSplitScene* pScene=iter->second;
			
			HTREEITEM hItem=pScene->m_hItem;
			XScene::GetInstance()->DeleteSplitScene(hItem);

			m_MapSplitScene.erase(iter);
			delete pScene;
		}
	}
	else if(result.GetSendType()==_T("SAVE_WALL"))
	{
		if(result.GetResult()!=0)
			return;

		if(m_MapSplitScene.find(result.m_szSceneName)!=m_MapSplitScene.end())
		{
			XSplitScene* pScene=m_MapSplitScene[result.m_szSceneName];
			pScene->SetSceneName(result.m_szSceneName);
			auto& VecWall=pScene->GetVecWallList();
			VecWall.push_back(result.m_szWallName);
		}
		else
		{
			XSplitScene* pScene=new XSplitScene;
			pScene->SetSceneName(result.m_szSceneName);

			auto& VecWall=pScene->GetVecWallList();
			VecWall.push_back(result.m_szWallName);

			m_MapSplitScene.insert(std::pair<CString,XSplitScene*>(result.m_szSceneName,pScene));
		}

		//最后一次
		if(result.m_nLast)
		{
			//这里不会新建组，只是插在现有组中
			//成功一次就关闭了
			if(NULL!=m_pSplitScene)
			{
				//如果有组信息则 发送添加组信息，否则直接加到树后面
				if(_T("")!=m_pSplitScene->GetGroup())
				{
					XSendDataManage::GetInstance()->AddSendDataOfSetSceneGroup(result.m_szSceneName,m_pSplitScene->GetGroup());
				}
				else
				{
					//添加到树
					XScene::GetInstance()->AddSplitScene(result.m_szSceneName,m_pSplitScene->GetGroup());
				}

				m_pSplitScene->OnCloseDlg();
				m_pSplitScene=NULL;
			}
		}
	}
	else if(result.GetSendType()==_T("RECALL_WALL"))
	{
		if(result.GetResult()!=0)
			return;
		//查找墙信息
		CString szSceneName=result.m_szSceneName;
		CString szWallName=result.m_szWallName;

		XSendDataManage::GetInstance()->AddSendDataOfQuerySceneWall(szSceneName,szWallName);
	}
	else if(result.GetSendType()==_T("QUERY_WALL"))
	{
		if(result.GetResult()!=0)
			return;

		CString szSceneName=result.m_szSceneName;
		if(_T("")==szSceneName)
			return;

		if(result.m_bExist)
		{
			//墙存在 刷新信号
			for(auto& map:m_MapBaseView)
			{
				XBaseViewManage* pBaseView=map.second;
				if(result.m_szWallName!=_T("")&&result.m_szWallName==pBaseView->GetSplitName())
				{
					//1.先排序
					((XSplitManage*)pBaseView)->SortSignalByLevel();
					//2.计算区域以及颜色
					((XSplitManage*)pBaseView)->SetSignalOtherInfo();

					XSendDataManage::GetInstance()->AddSendDataOfLevelUseList(result.m_szWallName);
				}
			}
		}
		else
		{
			//先创建墙 在刷新信号
			for(auto& map:m_MapBaseView)
			{
				XBaseViewManage* pBaseView=map.second;
				CString szSplitName=pBaseView->GetSplitName();
				if(result.m_szWallName!=_T("")&&result.m_szWallName==szSplitName)
				{
					((XSplitManage*)pBaseView)->SetDelegate(this);
					CString szTitle=GetDocTitle(pBaseView->GetSplitName());
					((XSplitManage*)pBaseView)->SetTitle(szTitle);
					((XSplitManage*)pBaseView)->Init();
					((XSplitManage*)pBaseView)->SetScreenInfo();

					AddDocument(pBaseView);

					//1.先排序
					((XSplitManage*)pBaseView)->SortSignalByLevel();
					//2.计算区域以及颜色
					((XSplitManage*)pBaseView)->SetSignalOtherInfo();


					//设置当前视图
					//m_pBaseViewManage=((XSplitManage*)pBaseView);
					//m_nSplitIndex=((XSplitManage*)pBaseView)->GetBaseIndex();
					//m_pRibbonBarManage->SetActiveCategory(m_nSplitIndex);

					//配置生效
					//XSendDataManage::GetInstance()->AddSendDataOfRefreashSplit(result.m_szWallName);

					XSendDataManage::GetInstance()->AddSendDataOfLevelUseList(result.m_szWallName);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XInternalManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY)
{
	m_pBaseViewManage->ViewDraw(pDC,rect,noffsetX,noffsetY);
}

CSize XInternalManage::ViewGetSize()
{
	return m_pBaseViewManage->ViewGetSize();
}

void XInternalManage::ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseViewManage->ViewLButtonDown(nFlags,point,rect,noffsetX,noffsetY);
}

void XInternalManage::ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseViewManage->ViewLButtonDblClk(nFlags,point,rect,noffsetX,noffsetY);
}

void XInternalManage::ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseViewManage->ViewLButtonUp(nFlags,point,rect,noffsetX,noffsetY);
}

void XInternalManage::ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseViewManage->ViewMouseMove(nFlags,point,rect,noffsetX,noffsetY);
}

void XInternalManage::ViewMouseLeave()
{
	m_pBaseViewManage->ViewMouseLeave();
}

BOOL XInternalManage::ViewMouseWheel(short zDelta)
{
	return m_pBaseViewManage->ViewMouseWheel(zDelta);
}

void XInternalManage::ViewKeyUp(UINT nChar)
{
	m_pBaseViewManage->ViewKeyUp(nChar);
}

void XInternalManage::ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	m_pBaseViewManage->ViewRButtonUp(pWnd,nFlags,point,rect,noffsetX,noffsetY);
}

//////////////////////////////////////////////////////////////////////////
void XInternalManage::ControlDataChange(XDATATYPE type,void* pControl)
{
	switch(type)
	{
		case XDATATYPE_THEME:
			{
				m_pIniManage->ControlDataChange(type,pControl);
			}
			break;
		case XDATATYPE_SEATROW:
		case XDATATYPE_SEATCOLUMN:
			{
				m_pSeatArrageManage->ControlDataChange(type,pControl);
			}
			break;
		default:
			break;
	}
}

void XInternalManage::Operate(OPERATETYPE type,void* pData)
{
	switch(type)
	{
		case OPERATETYPE_RELOADINTERFACE:
			{
				ReloadInterface();
			}
			break;
		case OPERATETYPE_ABOUT:
			{
				OperateOfAbout();
			}
			break;
		case OPERATETYPE_THEMEWIN7:
		case OPERATETYPE_THEMEBLUE:
		case OPERATETYPE_THEMEBLACK:
		case OPERATETYPE_THEMESLIVER:
		case OPERATETYPE_THEMEAQUE:
			{
				m_pIniManage->Operate(type,NULL);
			}
			break;
		case OPERATETYPE_LANGUAGEZN:
		case OPERATETYPE_LANGUAGETW:
		case OPERATETYPE_LANGUAGEEN:
			{
				XTranslationManage::GetInstance()->Operate(type,NULL);
			}
			break;
		case OPERATETYPE_OPENNET:
		case OPERATETYPE_CLOSENET:
			{
				m_pBaseNetManage->Operate(type,NULL);
			}
			break;
		case OPERATETYPE_LOGIN:
		case OPERATETYPE_LOGINOUT:
			{
				m_pUserManage->Operate(type,NULL);
			}
			break;
		case OPERATETYPE_ADDSEAT:
			{
				OperateOfAddSeat();
			}
			break;
		case OPERATETYPE_DEVICENET:
			{
				OperateOfDeviceNet();
			}
			break;
		case OPERATETYPE_HEART:
			{
				OperateOfHeart();
			}
			break;
		case OPERATETYPE_REHEART:
			{
				OperateOfReHeart((char*)pData);
			}
			break;
		case OPERATETYPE_RENETCONFIG:
			{
				OperateOfReNetConfig((char*)pData);
			}
			break;
		case OPERATETYPE_RELOG:
			{
				OperateOfReLog((char*)pData);
			}
			break;
		//case OPERATETYPE_CONTROL:
		//	{
		//		OperateOfControl();
		//	}
		//	break;
		case OPERATETYPE_LOG:
			{
				OperateOfLog();
			}
			break;
		case OPERATETYPE_UPDATE:
			{
				OperateOfUpdate();
			}
			break;
		case OPERATETYPE_STATUSTIME:
			{
				OperateOfStatusTime();
			}
			break;
		case OPERATETYPE_RELOGIN:
		case OPERATETYPE_RELOGINOUT:
		case OPERATETYPE_POWER:
		case OPERATETYPE_REPOWER:
		case OPERATETYPE_REUSERLIST:
		case OPERATETYPE_RESTORELIST:
		case OPERATETYPE_FOLDER:
		case OPERATETYPE_REROOTFOLDER:
			{
				m_pUserManage->Operate(type,pData);
			}
			break;
		case OPERATETYPE_ALLNODE:
		case OPERATETYPE_DEVICEINFO:
		case OPERATETYPE_REDEVICEINFO:
		case OPERATETYPE_RENODECHANNEL:
		case OPERATETYPE_RENODEINFO:
		case OPERATETYPE_RENODEDETAILINFO:
		case OPERATETYPE_GETLOGINUSER:
		case OPERATETYPE_RELOGINUSER:
		case OPERATETYPE_RELOGINUSERSTATUS:
		case OPERATETYPE_RENODELOGIN:
		case OPERATETYPE_RENODELOGOUT:
		case OPERATETYPE_RETAKEOVER:
		case OPERATETYPE_RETAKEOVERCANCEL:
		case OPERATETYPE_PREVIEW:
		case OPERATETYPE_RENODESTATUS:
		case OPERATETYPE_ALTERNODENAME:
		case OPERATETYPE_MENUOUTOFLOGOUT:
		case OPERATETYPE_REMATRIX:
		case OPERATETYPE_MATRIXSTATUS:
		case OPERATETYPE_REMATRIXSTATUS:
		case OPERATETYPE_OSDIMAGE:
		case OPERATETYPE_REOSDIMAGE:
		case OPERATETYPE_REHIDEOSDIMAGE:
		case OPERATETYPE_READNODEGROUP:
		case OPERATETYPE_READONLINENODEGROUP:
		case OPERATETYPE_REREADNODEGROUP:
		case OPERATETYPE_RENODEGROUPINFO:
		case OPERATETYPE_REREFREASGGROUP:
		case OPERATETYPE_SYSTEMSTATUS:
		case OPERATETYPE_RESYSTEMSTATUS:
		case OPERATETYPE_REMAINANDSECOND:
		case OPERATETYPE_GETMAINANDSECOND:
		case OPERATETYPE_REMAINANDSECONDLIST:
		case OPERATETYPE_SAVESCENE:
			{
				m_pNodeManage->Operate(type,pData);
			}
			break;
		case OPERATETYPE_SAVESEAT:
		case OPERATETYPE_SENDSEAT:
		case OPERATETYPE_CLEARSEAT:
		case OPERATETYPE_BG:
		case OPERATETYPE_SEAT:
		case OPERATETYPE_ALIGNLEFT:
		case OPERATETYPE_ALIGNHORIZON:
		case OPERATETYPE_ALIGNRIGHT:
		case OPERATETYPE_ALIGNUP:
		case OPERATETYPE_ALIGNDOWN:
		case OPERATETYPE_ALIGNVERTICAL:
		case OPERATETYPE_ALIGNSAME:
		case OPERATETYPE_ALIGNHSAME:
		case OPERATETYPE_ALIGNVSAME:
		case OPERATETYPE_ALIGNWIDTH:
		case OPERATETYPE_ALIGNHEIGHT:
		case OPERATETYPE_SCREENARRAY:
			{
				m_pSeatArrageManage->Operate(type,pData);
			}
			break;
		case OPERATETYPE_SCALE200:
		case OPERATETYPE_SCALE175:
		case OPERATETYPE_SCALE150:
		case OPERATETYPE_SCALE125:
		case OPERATETYPE_SCALE100:
		case OPERATETYPE_SCALE75:
		case OPERATETYPE_SCALE50:
			{
				m_pBaseViewManage->Operate(type,pData);
			}
			break;
		case OPERATETYPE_MATRIXARRAY:
			{
				m_pMatrixManage->Operate(type,pData);
			}
			break;
		case OPERATETYPE_ADDSPLIT:
			{
				OperateOfAddSplit();
			}
			break;
		case OPERATETYPE_GETSPLITWALL:
			{
				OperateOfObtainSplit();
			}
			break;
		case OPERATETYPE_REGETSPLITWALL:
			{
				OperateOfSplit((char*)pData);
			}
			break;
		case OPERATETYPE_CLEARSPLITVIEW:
			{
				OperateOfClearSplitView();
			}
			break;
		case OPERATETYPE_SPLITSCALE:
		case OPERATETYPE_MENUUP:
		case OPERATETYPE_MENUDOWN:
		case OPERATETYPE_MENUTOP:
		case OPERATETYPE_MENUBOTTOM:
		case OPERATETYPE_CLEARSIGNAL:
		case OPERATETYPE_LIMIT:
		case OPERATETYPE_DELTOP:
		case OPERATETYPE_DELBOTTOM:
		//case OPERATETYPE_FULLSCREEN:
		//case OPERATETYPE_ADDDEFAULT:
		case OPERATETYPE_QUICKTOP:
		case OPERATETYPE_MENUFULLSCREEN:
		case OPERATETYPE_MENUEXTEND:
		case OPERATETYPE_MENURESTORE:
		case OPERATETYPE_MENUCLOSESIGNAL:
			{
				//拼接
				m_pBaseViewManage->Operate(type,NULL);
			}
			break;
		case OPERATETYPE_REGETSPLITWINDOW:
			{
				OperateOfSplitWindow((char*)pData);
			}
			break;
		case OPERATETYPE_INITSCENE:
			{
				m_pBaseViewManage->ResetSceneWnd();
			}
			break;
		case OPERATETYPE_SPLITSCENE:
			{
				OperateOfObtainSplitScene();
			}
			break;
		case OPERATETYPE_RESPLITSCENE:
			{
				OperateOfReSplitScene((char*)pData);
			}
			break;
		case OPERATETYPE_SAVESPLITSCENE:
			{
				OperateOfSaveSplitScene();
			}
			break;
		default:
			break;
	}
}

void XInternalManage::UpdateControlDataShow(XDATATYPE type,void* pControl)
{

}

void XInternalManage::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	switch(type)
	{
		case CMDUITYPE_LOGIN:
		case CMDUITYPE_LOGINOUT:
		case CMDUITYPE_POWER:
		case CMDUITYPE_OSDIMAGE:
		case CMDUITYPE_SPLITSCALE:
		//case CMDUITYPE_CONTROL:
		case CMDUITYPE_UPDATE:
		case CMDUITYPE_FOLDER:
		case CMDUITYPE_SAVESCENE:
		case CMDUITYPE_SAVESEAT:
		case CMDUITYPE_SENDSEAT:
		case CMDUITYPE_CLEARSEAT:
		case CMDUITYPE_ALIEN:
		case CMDUITYPE_LOG:
		case CMDUITYPE_MATRIXARRAY:
		case CMDUITYPE_ADDSPLIT:
		case CMDUITYPE_ADDMODEL:
		case CMDUITYPE_CLEARSIGNAL:
		case CMDUITYPE_LIMITNMODEL:
		case CMDUITYPE_SAVESPLITSCENE:
			{
				m_pUserManage->UpdateControlUI(type,pCmdUI);
			}
			break;
		case CMDUITYPE_THEMEWIN7:
		case CMDUITYPE_THEMEBLUE:
		case CMDUITYPE_THEMEBLACK:
		case CMDUITYPE_THEMESLIVER:
		case CMDUITYPE_THEMEAQUE:
			{
				m_pIniManage->UpdateControlUI(type,pCmdUI);
			}
			break;
		case CMDUITYPE_LANGUAGEZN:
		case CMDUITYPE_LANGUAGETW:
		case CMDUITYPE_LANGUAGEEN:
			{
				XTranslationManage::GetInstance()->UpdateControlUI(type,pCmdUI);
			}
			break;
		case CMDUITYPE_SCALE200:
		case CMDUITYPE_SCALE175:
		case CMDUITYPE_SCALE150:
		case CMDUITYPE_SCALE125:
		case CMDUITYPE_SCALE100:
		case CMDUITYPE_SCALE75:
		case CMDUITYPE_SCALE50:
		case CMDUITYPE_LIMIT:
		case CMDUITYPE_DELTOP:
		case CMDUITYPE_DELBOTTOM:
		case CMDUITYPE_ADDDEFAULT:
		case CMDUITYPE_FULLSCREEN:
		case CMDUITYPE_QUICKTOP:
			{
				m_pBaseViewManage->UpdateControlUI(type,pCmdUI);
			}
			break;
		case CMDUITYPE_SEAT:
			{
				m_pUserManage->UpdateControlUI(type,pCmdUI);
				m_pSeatArrageManage->UpdateControlUI(type,pCmdUI);
			}
			break;
		case CMDUITYPE_ALIGNLEFT:
		case CMDUITYPE_ALIGNHORIZON:
		case CMDUITYPE_ALIGNRIGHT:
		case CMDUITYPE_ALIGNUP:
		case CMDUITYPE_ALIGNDOWN:
		case CMDUITYPE_ALIGNVERTICAL:
		case CMDUITYPE_ALIGNSAME:
		case CMDUITYPE_ALIGNHSAME:
		case CMDUITYPE_ALIGNVSAME:
		case CMDUITYPE_ALIGNWIDTH:
		case CMDUITYPE_ALIGNHEIGHT:
		
			{
				m_pSeatArrageManage->UpdateControlUI(type,pCmdUI);
			}
			break;
		case CMDUITYPE_STATUSNET:
			{
				XStatusBar::GetInstance()->UpdateControlUI(type,pCmdUI);
			}
			break;
		default:
			break;
	}
}