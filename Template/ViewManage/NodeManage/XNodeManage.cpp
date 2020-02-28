#include "stdafx.h"
#include "XNodeManage.h"
#include "XDelegateNodeManage.h"
#include "XTranslationManage.h"
#include "..\TemplateView.h"
#include "HandleCalculate.h"
#include "XDrawNodeManage.h"
#include "XCaculateNodeManage.h"
#include "XNode.h"
#include "XNodeAll.h"
#include "XSendDataManage.h"
#include "XDevicePara.h"
#include "XJsonManage.h"
#include "XNodeConnect.h"
#include "XNodeInfo.h"
#include "XPropertiesWnd.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XUserLogStatus.h"
#include "XPower.h"
#include "XNodeLogin.h"
#include "XTakeOver.h"
#include "XOutResoluation.h"
#include "XAlterNodeName.h"
#include "XConstantData.h"
#include "XAlterName.h"
#include "XBaseMap.h"
#include "XOSDImage.h"
#include "XMatrix.h"
#include "XLeftWnd.h"
#include "XNodeGroupInfo.h"
#include "XNodeGroup.h"
#include "XChannel.h"
#include "XChart.h"
#include "XSystemStatus.h"
#include "XSubUserInfo.h"
#include "XSaveScene.h"
#include "XScene.h"
#include "XSceneData.h"
#include "XMessageBox.h"
#include "XTakeOver.h"
#include "XNodeStatus.h"
//#include <thread>
//#include <mutex>



XNodeManage::XNodeManage()
{

}

XNodeManage::~XNodeManage()
{
	ClearMapChannel();
	ClearMapNode();
	ClearNodeList();
	ClearNodeID();
	ClearMapUserLoginStatus();
	ClearMapResoluationInfo();
	ClearMapMatrix();
	ClearMapImage();
	ClearMapNodeGroup();
	ClearMapNodeAll();
	ClearVecCheBridge();
	ClearMapGroupMainSec();
	ClearMapNodeMainSec();
	ClearMapTakeOver();
}

void XNodeManage::ClearMapChannel()
{
	m_MapChannel.clear();
}

void XNodeManage::ClearMapNode()
{
	for(auto& map:m_MapNode)
	{
		delete map.second;
	}
	m_MapNode.clear();
}

void XNodeManage::ClearMapNodeAll()
{
	for(auto& map:m_MapNodeAll)
	{
		delete map.second;
	}
	m_MapNodeAll.clear();
}

void XNodeManage::ClearNodeList()
{
	m_VecNodeList.clear();
}

void XNodeManage::ClearNodeID()
{
	m_VecNodeID.clear();
}

void XNodeManage::ClearMapUserLoginStatus()
{
	for(auto& map:m_MapUserLoginStatus)
	{
		delete map.second;
	}
	m_MapUserLoginStatus.clear();
}

void XNodeManage::ClearMapResoluationInfo()
{
	for(auto& map:m_MapResoluationInfo)
	{
		delete map.second;
	}
	m_MapResoluationInfo.clear();
}

void XNodeManage::ClearMapMatrix()
{
	m_MapMatrix.clear();
}

void XNodeManage::ClearMapImage()
{
	m_MapImage.clear();
}

void XNodeManage::ClearMapNodeGroup()
{
	for(auto& map:m_MapNodeGroup)
	{
		delete map.second;
	}
	m_MapNodeGroup.clear();
}

void XNodeManage::ClearVecCheBridge()
{
	for(auto& map:m_VecCheBridge)
	{
		delete map;
	}
	m_VecCheBridge.clear();
}

void XNodeManage::ClearMapGroupMainSec()
{
	for(auto& map:m_MapGroupMainSec)
	{
		delete map.second;
	}
	m_MapGroupMainSec.clear();
}

void XNodeManage::ClearMapNodeMainSec()
{
	//for(auto& map:m_MapNodeMainSec)
	//{
	//	delete map.second;
	//}
	m_MapNodeMainSec.clear();
}

void XNodeManage::ClearMapTakeOver()
{
	for(auto& map:m_MapTakeOver)
	{
		delete map.second;
	}
	m_MapTakeOver.clear();
}

void XNodeManage::Init()
{
	InitData();
	InitMapResoluationInfo();
	InitKeyValue();
}

CString XNodeManage::GetTitle()
{
	return m_szTitle;
}

void XNodeManage::SetTitle(CString szTitle)
{
	m_szTitle=szTitle;
}

void XNodeManage::InitData()
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);
	int nType=HandleIni::GetInt(_T("Info"),_T("NodeScale"),0,szPath);

	switch(nType)
	{
	case OPERATETYPE_SCALE200:
		{
			m_nScale=200;
		}
		break;
	case OPERATETYPE_SCALE175:
		{
			m_nScale=175;
		}
		break;
	case OPERATETYPE_SCALE150:
		{
			m_nScale=150;
		}
		break;
	case OPERATETYPE_SCALE125:
		{
			m_nScale=125;
		}
		break;
	case OPERATETYPE_SCALE100:
		{
			m_nScale=100;
		}
		break;
	case OPERATETYPE_SCALE75:
		{
			m_nScale=75;
		}
		break;
	case OPERATETYPE_SCALE50:
		{
			m_nScale=50;
		}
		break;
	default:
		{
			m_nScale=100;
			CString szTemp=_T("");
			szTemp.Format(_T("%d"),nType);
			HandleIni::WriteData(_T("Info"),_T("NodeScale"),szTemp,szPath);
		}
		break;
	}
}

void XNodeManage::InitMapResoluationInfo()
{
	XCaculateNodeManage::InitMapResoluationInfo(this);
}

void XNodeManage::InitKeyValue()
{
	//先把键值装进来
	XCaculateNodeManage::InitKeyValue(this);
}

void XNodeManage::ReloadInterface()
{
	//XPropertiesWnd::GetInstance()->ReloadInterface();
	InvalidateView();
}

void XNodeManage::SetViewColor(Color& color)
{
	m_Color=color;
	InvalidateView();
}

Color XNodeManage::GetViewColor()
{
	return m_Color;
}

void XNodeManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY)
{
	XDrawNodeManage::ViewDraw(pDC,rect,noffsetX,noffsetY,this);
}

CSize XNodeManage::ViewGetSize()
{
	//每个页面视图大小
	return XCaculateNodeManage::ViewGetSize(this);
}

void XNodeManage::ResetView()
{
	ResetViewSize();
	InvalidateView();
}

void XNodeManage::InvalidateView()
{
	CTemplateView* pView=m_pDelegate->GetView();
	if(NULL!=pView)
	{
		pView->Invalidate(TRUE);
	}
}

void XNodeManage::ResetViewSize()
{
	CTemplateView* pView=m_pDelegate->GetView();
	if(NULL!=pView)
	{
		pView->ResetSize();
	}
}

void XNodeManage::ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	POINTF tempPoint;
	XCaculateNodeManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,tempPoint);
	XNode* pNode=XCaculateNodeManage::GetNodeByPoint(this,tempPoint);
	if(NULL==pNode)
		return;

	//更改名称
	//XAlterName dlg;
	//if(IDOK==dlg.DoModal())
	//{
		//CString szNodeName=dlg.GetNodeName();

		//XAlterNodeName alterNodeName;
		//alterNodeName.SetNodeName(szNodeName);
		//alterNodeName.SetNodeID(pNode->GetNodeID())


		//XSendDataManage::GetInstance()->AddSendDataOfAlterNodeName(pNode->GetNodeID(),szNodeName);
	//}
}

void XNodeManage::ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	XCaculateNodeManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,m_Point);
	m_TempPoint=m_Point;

	XNode* pNode=XCaculateNodeManage::GetNodeByPoint(this,m_Point);
	if(NULL==pNode)
	{
		//选中缓存设置为NULL
		m_pNodeSel=NULL;

		//点在图片上
		POINTF TempPoint=m_Point;
		TempPoint.X*=GetScale();
		TempPoint.Y*=GetScale();
		TempPoint.Y+=(PIC_HEIGHT*GetScale()+TEXT_HEIGHT);

		//点击柱形图
		PointInCloumn(TempPoint);	
		//点击各个区域
		PointInRect(TempPoint);
		return;
	}
		
	m_bLBtnDown=TRUE;
	//属性
	if(m_pNodeSel!=pNode)
	{
		//点击设置节点属性
		m_pNodeSel=pNode;
		SetNodeSelected(pNode);
		XPropertiesWnd::GetInstance()->SetNode(pNode);
		XPropertiesWnd::GetInstance()->SetNodeGroup(NULL);
		XPropertiesWnd::GetInstance()->SetSeat(NULL);
		pNode->SetPropertiesWnd();

		//点击节点等闪烁
		auto& VecBlinkNodeID=XConstantData::GetInstance()->GetVecBlinkNodeID();
		VecBlinkNodeID.clear();
		VecBlinkNodeID.push_back(pNode->GetNodeID());
		XSendDataManage::GetInstance()->AddSendDataOfBlink();

		//柱形图选中 (根据通道选中)
		XChart* pColumn=XChart::Get(CHART::CHART_CLOUMN_NODE);
		if(!pColumn)
			return;
		CString szChannel;
		szChannel.Format(_T("%d"),pNode->GetChannel());
		pColumn->SetColumnSelect(szChannel);
	}

	//节点信息
	XConstantData::GetInstance()->SetNodeID(pNode->GetNodeID());
	XConstantData::GetInstance()->SetNodeType(pNode->GetNodeType());
	XConstantData::GetInstance()->SetNodeChannel(pNode->GetChannel());

	InvalidateView();
}

void XNodeManage::PointInCloumn(POINTF& point)
{
	XChart* pCloumn=NULL;
	RECTF rect;
	pCloumn=XChart::Get(CHART::CHART_CLOUMN_NODE);
	if(!pCloumn)
		return;
	rect=pCloumn->GetRect();
	if(rect.Contains(point))
	{
		pCloumn->SetShowIndex();
		InvalidateView();
		return;
	}
	//***************************//
	pCloumn=XChart::Get(CHART::CHART_CLOUMN_USER);
	if(!pCloumn)
		return;
	rect=pCloumn->GetRect();
	if(rect.Contains(point))
	{
		pCloumn->SetShowIndex();
		InvalidateView();
		return;
	}
	//***************************//
	pCloumn=XChart::Get(CHART::CHART_CLOUMN_GROUP);
	if(!pCloumn)
		return;
	rect=pCloumn->GetRect();
	if(rect.Contains(point))
	{
		pCloumn->SetShowIndex();
		InvalidateView();
		return;
	}
}

void XNodeManage::PointInRect(POINTF& point)
{
	RECTF rectDevide(178,45,80,20);
	RectScale(rectDevide,GetScale());
	RECTF rectUser(1095,45,80,20);
	RectScale(rectUser,GetScale());
	RECTF rectNode(178,480,80,20);
	RectScale(rectNode,GetScale());
	RECTF rectGroup(1060,480,140,25);
	RectScale(rectGroup,GetScale());

	XChart* pPieChart=XChart::Get(CHART::CHART_PIE);
	if(NULL==pPieChart)
		return;

	if(rectDevide.Contains(point))
	{
		int nChannel=this->GetHardWareChannel();
		int nConnect=this->GetChannelConnect();
		int nTemp=nChannel-nConnect;

		//91 155 213
		//237 125 49
		//165 165 165
		//255 192 0
		//112 171 71
		//68 114 196
		//158 72 14

		pPieChart->ClearMap();
		pPieChart->SetColorFlag(TRUE);
		pPieChart->SetType(_C(_T("214"),_T("设备通道")));
		pPieChart->PushPieData(1,_C(_T("215"),_T("连接")),nConnect);
		pPieChart->PushPieData(2,_C(_T("216"),_T("未连接")),nTemp);
	}
	else if(rectUser.Contains(point))
	{
		int nCount=this->GetUserCount();
		int nLoginUser=this->GetLoginUser(USERLOGIN_ALL);
		int nTemp=nCount-nLoginUser;

		pPieChart->ClearMap();
		pPieChart->SetColorFlag(TRUE);
		pPieChart->SetType(_C(_T("217"),_T("子用户")));
		pPieChart->PushPieData(1,_C(_T("33"),_T("在线")),nLoginUser);
		pPieChart->PushPieData(2,_C(_T("218"),_T("离线")),nTemp);
	}
	else if(rectNode.Contains(point))
	{
		int nNodeAll=this->GetNodeAll();
		int nNode=this->GetNodeOnline(TERM_ALL);
		int nTemp=nNodeAll-nNode;

		pPieChart->ClearMap();
		pPieChart->SetColorFlag(TRUE);
		pPieChart->SetType(_C(_T("95"),_T("节点")));
		pPieChart->PushPieData(1,_C(_T("33"),_T("在线")),nNode);
		pPieChart->PushPieData(2,_C(_T("218"),_T("离线")),nTemp);
	}
	else if(rectGroup.Contains(point))
	{
		int nNodeGroupMain=this->GetNodeGroupByType(NODEGROUP_MAINSEC);
		int nNodeGroupIn=this->GetNodeGroupByType(NODEGROUP_IN);
		int nNodeGroupOut=this->GetNodeGroupByType(NODEGROUP_OUT);

		pPieChart->ClearMap();
		pPieChart->SetColorFlag(TRUE);
		pPieChart->SetType(_C(_T("196"),_T("节点组")));
		pPieChart->PushPieData(1,_C(_T("219"),_T("主副屏")),nNodeGroupMain);
		pPieChart->PushPieData(2,_C(_T("223"),_T("输入组")),nNodeGroupIn);
		pPieChart->PushPieData(3,_C(_T("224"),_T("输出组")),nNodeGroupOut);
	}
	InvalidateView();
}

void XNodeManage::RectScale(RECTF& rect,float dwScale)
{
	rect.X*=dwScale;
	rect.Y*=dwScale;
	rect.Width*=dwScale;
	rect.Height*=dwScale;
}

void XNodeManage::ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	POINTF tempPoint;
	XCaculateNodeManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,tempPoint);

	if(m_bLBtnDown)
	{
		if(m_CursorType==CURSORTYPE_HAND)
		{
			if(NULL==m_pNodeSel)
				return;
			if(m_pNodeSel->GetNodeType()==TERM_IN)
			{
				if((abs(tempPoint.X-m_TempPoint.X)>10)||(abs(tempPoint.Y-m_TempPoint.Y)>10))
					m_bCreateDragRect=TRUE;
				MoveSignal(m_Point,tempPoint);
				m_Point=tempPoint;
			}
		}
	}
	else
	{
		if(XCaculateNodeManage::DecidePointInNode(this,tempPoint))
		{
			XNode* pNode=XCaculateNodeManage::GetNodeByPoint(this,tempPoint);
			if(NULL==pNode)
				return;
			//拖拽区域
			RECTF rect(tempPoint.X-40,tempPoint.Y-25+PIC_HEIGHT+TEXT_HEIGHT,80,30);
			m_DragRect=rect;

			m_CursorType=CURSORTYPE_HAND;
		}
		else
		{
			m_CursorType=CURSORTYPE_NORMAL;
		}
	}
	SetCursor(m_CursorType);
}

void XNodeManage::ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	if(m_CursorType==CURSORTYPE_NORMAL)
		return;

	POINTF tempPoint;
	XCaculateNodeManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,tempPoint);

	XNode* pNode=XCaculateNodeManage::GetNodeByPoint(this,tempPoint);
	if((NULL==pNode)||(pNode->GetNodeType()==XConstantData::GetInstance()->GetNodeType()))
	{
		m_bLBtnDown=FALSE;
		m_bCreateDragRect=FALSE;
		InvalidateView();
		return;
	}

	m_bLBtnDown=FALSE;
	m_bCreateDragRect=FALSE;

	if(XConstantData::GetInstance()->GetNodeType()==TERM_IN)
	{
		//int nInNodeChannel=XConstantData::GetInstance()->GetNodeChannel();
		//XSendDataManage::GetInstance()->AddSendDataOfMatrix(nInNodeChannel,pNode->GetChannel());
		int nNodeID=XConstantData::GetInstance()->GetNodeID();
		//缓存拖拽节点ID
		//nTakeOverID=pNode->GetNodeID();
		//nTargetID=nNodeID;
		//共享接管
		XSendDataManage::GetInstance()->AddSendDataOfTakeOver(pNode->GetNodeID(),nNodeID,FALSE);
	}

	InvalidateView();
}

void XNodeManage::ViewMouseLeave()
{
	//TRACE0("ViewMouseLeave\n");
}

BOOL XNodeManage::ViewMouseWheel(short zDelta)
{
	int nScale=0;
	if(zDelta>0)
		nScale=m_nScale+25;
	else
		nScale=m_nScale-25;

	if(nScale>=200)
		nScale=200;
	else if(nScale<=50)
		nScale=50;

	if(m_nScale!=nScale)
	{
		m_nScale=nScale;

		int nType=HandleCalculate::GetScaleType(m_nScale);
		SaveDataOfScale(nType);

		ResetViewSize();
		InvalidateView();
	}
	return TRUE;
}

void XNodeManage::ViewKeyUp(UINT nChar)
{
	//防止刷新太快
	DWORD dwTime=GetTickCount();
	switch(nChar)
	{
	case VK_F5:
		{
			if(((long)dwTime-(long)m_dwCurTime)>3000)
			{
				m_dwCurTime=GetTickCount();

				OperateOfGetAllNode();
				OperateOfGetDeviceInfo();
				//OperateOfGetNodeByChannel();
				OperateOfGetLoginUser();
				OperateOfGetMatrixStatus();
				OperateOfReadNodeGroup();
				OperateOfReadOnLineNodeGroup();
				OperateOfMainAndSecondList();

				//刷新属性面板
				if(NULL!=m_pNodeSel)
				{
					XPropertiesWnd::GetInstance()->SetNode(m_pNodeSel);
					XPropertiesWnd::GetInstance()->SetNodeGroup(NULL);
					XPropertiesWnd::GetInstance()->SetSeat(NULL);
					m_pNodeSel->SetPropertiesWnd();
				}	
				ResetView();
			}
		}
		break;
	default:
		break;
	}
}

void XNodeManage::ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	POINTF tempPoint;
	XCaculateNodeManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,tempPoint);

	XNode* pNode=XCaculateNodeManage::GetNodeByPoint(this,tempPoint);
	if(NULL==pNode)
		return;

	m_pNodeSel=pNode;
	//右键数据
	XConstantData::GetInstance()->SetNodeID(pNode->GetNodeID());

	if(pNode->GetNodeType()==TERM_IN)
	{
		ShowMeunOfIn();
	}
	else if(pNode->GetNodeType()==TERM_OUT)
	{
		ShowMeunOfOut();
	}
}

void XNodeManage::MoveSignal(POINTF& point1,POINTF& point2)
{
	RECTF tempRect=m_DragRect;

	SIZEF size;
	size.Width=point2.X-point1.X;
	size.Height=point2.Y-point1.Y;

	XCaculateNodeManage::MoveSignal(tempRect,size);
	m_DragRect=tempRect;

	InvalidateView();
}

void XNodeManage::ShowMeunOfIn()
{
	//CPoint p;
	//GetCursorPos(&p);

	//CMenu menu; 
	//menu.CreatePopupMenu();

	//menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, p.x, p.y, m_pDelegate->GetCWND());

	//menu.DestroyMenu(); 
}

void XNodeManage::ShowMeunOfOut()
{
	CPoint p;
	GetCursorPos(&p);

	CMenu menu;
	menu.CreatePopupMenu();

	if(m_pNodeSel->GetOutStatus()==TERM_OUT_LOG)
	{
		menu.AppendMenu(MF_STRING,ID_MENUOUTOFLOGOUT,_C(_T("22"),_T("注销")));
	}

	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,p.x,p.y,m_pDelegate->GetCWND());
	menu.DestroyMenu();
}

void XNodeManage::OperateOfMeunOutOfLogout()
{
	//注销
	int nNodeID=XConstantData::GetInstance()->GetNodeID();
	XSendDataManage::GetInstance()->AddSendDataOfNodeLogOut(nNodeID);
}

void XNodeManage::SetCursor(CURSORTYPE type)
{
	::SetCursor(GetCursor(type));
}

HCURSOR XNodeManage::GetCursor(CURSORTYPE type)
{
	return XCaculateNodeManage::GetCursor(type);
}

void XNodeManage::SetNodeSelected(XNode* pNode)
{
	for(auto iter=m_MapNode.begin();iter!=m_MapNode.end();++iter)
	{
		XNode* pTemp=iter->second;
		if(pTemp==pNode)
			pTemp->SetSelected(TRUE);
		else
			pTemp->SetSelected(FALSE);
	}
}

void XNodeManage::ClearConChannel()
{
	ClearMapChannel();
}

void XNodeManage::ClearUserLoginStatus()
{
	ClearMapUserLoginStatus();
}

void XNodeManage::ClearNode()
{
	ClearMapNode();

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();

	InvalidateView();
}

void XNodeManage::ClearCloumn()
{
	XChart* pCloumn=XChart::Get(CHART::CHART_CLOUMN_NODE);
	if(!pCloumn)
		return;
	pCloumn->Clear();
	InvalidateView();
}

void XNodeManage::ClearNodeGroup()
{
	ClearMapNodeGroup();

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();

	InvalidateView();
}

void XNodeManage::SaveDataOfScale(int nType)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szTemp=_T("");
	szTemp.Format(_T("%d"),nType);

	HandleIni::WriteData(_T("Info"),_T("NodeScale"),szTemp,szIniPath);
}

float XNodeManage::GetScale()
{
	return m_nScale/100.0f;
}

MAP_SUBUSER& XNodeManage::GetMapSubUser()
{
	return m_pDelegate->GetMapSubUser();
}

MAP_POWER& XNodeManage::GetMapPower()
{
	return m_pDelegate->GetMapPower();
}

MAP_IMAGE& XNodeManage::GetMapImage()
{
	return m_MapImage;
}

int XNodeManage::GetUserIDByName(CString szUserName)
{
	int nUserID=0;
	MAP_POWER& MapPower=GetMapPower();
	MAP_POWER::iterator iter=MapPower.find(szUserName);
	if(iter!=MapPower.end())
	{
		XPower* pPower=iter->second;
		nUserID=pPower->GetUserID();
	}
	return nUserID;
}

void XNodeManage::SetPropertyValue(CString szUserName)
{
	CMFCPropertyGridProperty* pLoginUser=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODELOGINUSER);
	if(pLoginUser)
	{
		if(pLoginUser->IsEnabled())
		{
			pLoginUser->SetValue((_variant_t)szUserName);

			int nUserID=GetUserIDByName(szUserName);
			MAP_USERLOGINSTATUS::iterator iter=m_MapUserLoginStatus.find(nUserID);
			if(iter!=m_MapUserLoginStatus.end())
			{
				XUserLogStatus* pInfo=iter->second;
				CString szIP=pInfo->GetIP();

				CString szPort;
				if(pInfo->GetPort()!=0)
					szPort.Format(_T("%d"),pInfo->GetPort());
				else
					szPort=_T("");

				CMFCPropertyGridProperty* pIP=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_LOGINIP);
				if(NULL!=pIP)
					pIP->SetValue((_variant_t)szIP);

				CMFCPropertyGridProperty* pPort=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_LOGINPORT);
				if(NULL!=pPort)
					pPort->SetValue((_variant_t)szPort);
			}
			else
			{
				CMFCPropertyGridProperty* pIP=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_LOGINIP);
				if(NULL!=pIP)
					pIP->SetValue((_variant_t)_T(""));

				CMFCPropertyGridProperty* pPort=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_LOGINPORT);
				if(NULL!=pPort)
					pPort->SetValue((_variant_t)_T(""));
			}
		}
	}
}

int XNodeManage::GetHightOfNodeIn()
{
	return XCaculateNodeManage::GetHightOfNodeIn(this);
}

int XNodeManage::GetHightOfNodeOut()
{
	return XCaculateNodeManage::GetHightOfNodeOut(this);
}

int XNodeManage::GetWidthOfNodeIn()
{
	return XCaculateNodeManage::GetWidthOfNodeIn(this);
}

int XNodeManage::GetWidthOfNodeOut()
{
	return XCaculateNodeManage::GetWidthOfNodeOut(this);
}

void XNodeManage::DragEnd(CPoint& point,CRect& rect)
{
	UNUSED(rect);

	//登录功能（先添加）
	CView* pView=m_pDelegate->GetView();
	pView->ScreenToClient(&point);

	CRect rectView;
	pView->GetClientRect(&rectView);

	POINTF tempPoint;
	XCaculateNodeManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),point,tempPoint);
	XNode* pNode=XCaculateNodeManage::GetNodeByPoint(this,tempPoint);
	if(NULL==pNode)
		return;

	int nNodeType=pNode->GetNodeType();
	if(nNodeType==TERM_OUT)
	{
		//输出
		int nNodeID=pNode->GetNodeID();
		CString szUserName=XConstantData::GetInstance()->GetUserName();
		XSendDataManage::GetInstance()->AddSendDataOfNodeLogin(nNodeID,szUserName);
	}
	else if(nNodeType==TERM_IN)
	{

	}
}

void XNodeManage::ResetLeftWnd()
{
	XLeftWnd::GetInstance()->InitTreeListItemOfUser();
	//切换时 重新插入节点组数据（插入组柱形图数据）
	InsertNodeGroupColumnData();
}

void XNodeManage::ResetSceneWnd()
{
	//接管预案
	XScene::GetInstance()->InitSceneOfTakeOver();
}

void XNodeManage::ClearProperityWnd()
{
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();
}

BOOL XNodeManage::GetLogin()
{
	return m_pDelegate->GetLogin();
}

int XNodeManage::GetHardWareChannel()
{
	int nCount=0;
	if(!m_pDelegate->GetLogin())
	{
		nCount=-1;
	}
	else
	{
		nCount=m_nHardWareChannel;
	}
	return nCount;
}

CString XNodeManage::GetMatrixType()
{
	if(!m_pDelegate->GetLogin())
		return _T("");
	else
		return m_szMatrixModel;
}

int XNodeManage::GetChannelConnect()
{
	//0开始
	int nNum=0;
	if(!m_pDelegate->GetLogin())
	{
		nNum=-1;
	}
	else
	{
		for(auto& map:m_MapChannel)
		{
			BOOL isConnect=map.second;
			if(isConnect)
				nNum++;
		}

	}
	return nNum;
}

std::vector<int> XNodeManage::GetVecConnectChannel()
{
	std::vector<int> VecChannel;
	for(auto& map:m_MapChannel)
	{
		int nIndex=map.first;
		BOOL isConnect=map.second;
		if(isConnect)
		{
			nIndex++;
			VecChannel.push_back(nIndex);
		}
	}
	return VecChannel;
}

void XNodeManage::InitVecChannelAbridge(int nRow,int nColumn,POINTF& point)
{
	ClearVecCheBridge();

	float top=point.Y;
	float left=point.X;
	int nIndex=1;
	for(int i=0;i<nRow;i++)
	{
		left=point.X;
		for(int j=0;j<nColumn;j++)
		{
			RECTF rect(left,top,(Gdiplus::REAL)CHANNEL_W,(Gdiplus::REAL)CHANNEL_H);
			XChannel* pChannel=new XChannel;
			pChannel->SetIndex(nIndex);
			pChannel->SetRect(rect);

			m_VecCheBridge.push_back(pChannel);

			left+=CHANNEL_W;
			nIndex++;
		}
		top+=CHANNEL_H;
	}
}

XNode* XNodeManage::GetNodeByChannel(int nChannel)
{
	for(auto& map:m_MapNode)
	{ 
		XNode* pNode=map.second;
		int nChe=pNode->GetChannel();
		if(nChe==nChannel)
			return pNode;
	}
	return NULL;
}

int XNodeManage::GetAllUserCount()
{
	int nCount=0;
	if(!m_pDelegate->GetLogin())
	{
		nCount=-1;
	}
	else
	{
		VEC_USERIDALL& VecUserIDAll=m_pDelegate->GetVecUserIDAll();
		nCount=VecUserIDAll.size();
	}
	return nCount;
}

CString XNodeManage::GetCurUser()
{
	return m_pDelegate->GetCurUserName();
}

int XNodeManage::GetUserCount()
{
	int nCount=0;
	if(!m_pDelegate->GetLogin())
	{
		nCount=-1;
	}
	else
	{
		MAP_SUBUSER MapSunUser=m_pDelegate->GetMapSubUser();
		for(auto& map:MapSunUser)
		{
			XSubUserInfo* pInfo=map.second;
			if(pInfo->GetUserName()==m_pDelegate->GetCurUserName())
				continue;
			nCount++;
		}	
	}
	return nCount;
}

int XNodeManage::GetLoginUser(int nType)
{
	int nCount=0;
	if(!m_pDelegate->GetLogin())
	{
		nCount=-1;
	}
	else
	{
		MAP_POWER& MapPower=m_pDelegate->GetMapPower();

		switch(nType)
		{
		case USERLOGIN_NODE:
			{
				for(auto& map:m_MapUserLoginStatus)
				{
					XUserLogStatus* pUserStatus=map.second;
					if(pUserStatus->GetNodeLogin())
					{
						for(auto& mapPower:MapPower)
						{
							XPower* pPower=mapPower.second;
							if(pUserStatus->GetUserID()==pPower->GetUserID())
							{
								if(pUserStatus->GetUserName()!=m_pDelegate->GetCurUserName())
									nCount+=1;
							}
								
						}
					}	
				}
			}
			break;
		case USERLOGIN_NET:
			{
				for(auto& map:m_MapUserLoginStatus)
				{
					XUserLogStatus* pUserStatus=map.second;
					if(pUserStatus->GetNetLogin())
					{
						for(auto& mapPower:MapPower)
						{
							XPower* pPower=mapPower.second;
							if(pUserStatus->GetUserID()==pPower->GetUserID())
							{ 
								if(pUserStatus->GetUserName()!=m_pDelegate->GetCurUserName())
									nCount+=1;
							}						
						}
					}
				}
			}
			break;
		case USERLOGIN_ALL:
			{
				//nCount=m_MapUserLoginStatus.size();
				for(auto& map:m_MapUserLoginStatus)
				{
					XUserLogStatus* pUserStatus=map.second;
					for(auto& mapPower:MapPower)
					{
						XPower* pPower=mapPower.second;
						if(pUserStatus->GetUserID()==pPower->GetUserID())
						{
							if(pUserStatus->GetUserName()!=m_pDelegate->GetCurUserName())
								nCount+=1;
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}

	return nCount;
}

int XNodeManage::GetNodeAll()
{
	int nCount=0;
	if(!m_pDelegate->GetLogin())
		nCount=-1;
	else
		nCount=m_nNodeAll;
	return nCount;
}

int XNodeManage::GetNodeOnline(TERMTYPE type)
{
	int nNodeNum=0;
	if(!m_pDelegate->GetLogin())
	{
		nNodeNum=-1;
	}
	else
	{
		for(auto& map:m_MapNode)
		{
			XNode* pNode=map.second;
			switch(type)
			{
			case TERM_IN:
			case TERM_OUT:
				{
					if(pNode->GetNodeType()==type)
					{
						nNodeNum++;
					}
				}
				break;
			case TERM_ALL:
				{
					//总结的个数
					return m_MapNode.size();
				}
				break;
			default:
				break;
			}
		}
	}
	return nNodeNum;
}

int XNodeManage::GetNodeGroupByType(NODEGROUP type)
{
	int nNum=0;
	if(!m_pDelegate->GetLogin())
	{
		nNum=-1;
	}
	else
	{
		switch(type)
		{
		case NODEGROUP_ONLINE:
			{
				int nOnline=0;
				for(auto& map:m_MapNodeGroup)
				{
					XNodeGroupInfo* pInfo=map.second;
					if(NULL!=pInfo)
					{
						if(pInfo->GetOnLine())
							nOnline++;
					}
				}
				nNum=nOnline;
			}
			break;
		case NODEGROUP_OUTLINE:
			{
				int nOutline=0;
				for(auto& map:m_MapNodeGroup)
				{
					XNodeGroupInfo* pInfo=map.second;
					if(NULL!=pInfo)
					{
						if(!pInfo->GetOnLine())
							nOutline++;
					}

				}
				nNum=nOutline;
			}
			break;
		case NODEGROUP_IN:
			{
				int nIn=0;
				for(auto& map:m_MapNodeGroup)
				{
					XNodeGroupInfo* pInfo=map.second;
					if(NULL!=pInfo)
					{
						//if(pInfo->GetOnLine())
						{
							if(pInfo->GetType()==1)
								nIn++;
						}
					}
				}
				nNum=nIn;
			}
			break;
		case NODEGROUP_OUT:
			{
				int nOut=0;
				for(auto& map:m_MapNodeGroup)
				{
					XNodeGroupInfo* pInfo=map.second;
					if(NULL!=pInfo)
					{
						//if(pInfo->GetOnLine())
						{
							if(pInfo->GetType()==3)
								nOut++;
						}
					}
				}
				nNum=nOut;
			}
			break;
		case NODEGROUP_MAINSEC:
			{
				nNum=m_MapGroupMainSec.size();
			}
			break;
		case NODEGROUP_GROUP:
			{
				nNum=m_MapNodeGroup.size();
			}
			break;
		case NODEGROUP_ALL:
			{
				int nGroup=m_MapNodeGroup.size();
				int nMainSec=m_MapGroupMainSec.size();
				nNum=nGroup+nMainSec;
			}
			break;
		default:
			break;
		}
	}
	return nNum;
}

void XNodeManage::QueryNodeAll()
{
	//TRACE(_T("QueryNode\n"));
	//先不加锁（以后需要再添加）
	for(auto& nNodeID:m_VecNodeID)
	{
		//接着查询详细信息
		XSendDataManage::GetInstance()->AddSendDataOfGetNodeAllDetailInfo(nNodeID); //3 7
		Sleep(1);
	}
}

static UINT QueryNode(void* p)
{
	XNodeManage* pManage=(XNodeManage*)p;
	pManage->QueryNodeAll();
	return 0;
}

void XNodeManage::BeginQueryNodeThread()
{
	AfxBeginThread((AFX_THREADPROC)QueryNode,(void*)this);
}

int XNodeManage::GetTakeOverByID(int nNodeID)
{
	int nCount=0;
	for(auto& map:m_MapNode)
	{
		XNode* pNode=map.second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			if(pNode->GetTakeOverNodeID()==nNodeID)
			{
				nCount++;
			}
		}
	}
	return nCount;
}

void XNodeManage::InsertNodeColumnData()
{
	XChart* pColumn=XChart::Get(CHART::CHART_CLOUMN_NODE);
	if(!pColumn)
		return;
	pColumn->Clear();

	for(auto& map:m_MapNode)
	{
		XNode* pNode=map.second;
		int nNodeID=pNode->GetNodeID();
		int nChannel=pNode->GetChannel();

		if(pNode->GetNodeType()==TERM_IN)
		{
			int nTakeOver=GetTakeOverByID(nNodeID);
			//键值 显示通道
			CString szChannel;
			szChannel.Format(_T("%d"),nChannel);
			pColumn->InsertColumnData(szChannel,nTakeOver);
		}
	}
}

void XNodeManage::InsertDevicePieData()
{
	XChart* pPieChart=XChart::Get(CHART::CHART_PIE);
	if(NULL==pPieChart)
		return;

	int nChannel=this->GetHardWareChannel();
	int nConnect=this->GetChannelConnect();
	int nTemp=nChannel-nConnect;

	pPieChart->ClearMap();
	pPieChart->SetColorFlag(TRUE);
	pPieChart->SetType(_C(_T("214"),_T("设备通道")));
	pPieChart->PushPieData(1,_C(_T("215"),_T("连接")),nConnect);
	pPieChart->PushPieData(2,_C(_T("216"),_T("未连接")),nTemp);
}

int XNodeManage::GetNodeNumByGroupID(int nGroupID,BOOL bMainSecond)
{
	int nCount=0;
	if(bMainSecond)
	{
		for(auto& node:m_MapNode)
		{
			XNode* pNode=node.second;
			if(pNode->GetMaster()==nGroupID)
			{
				nCount++;
			}
		}
	}
	else
	{
		for(auto& node:m_MapNode)
		{
			XNode* pNode=node.second;
			if(pNode->GetGroup()==nGroupID)
			{
				nCount++;
			}
		}
	}

	return nCount;
}

int XNodeManage::GetNodeChannelByID(int nNodeID)
{
	for(auto& map:m_MapNode)
	{
		XNode* pNode=map.second;
		if(nNodeID==pNode->GetNodeID())
			return pNode->GetChannel();
	}
	return 0;
}

void XNodeManage::InsertNodeGroupColumnData()
{
	XChart* pColumn=XChart::Get(CHART::CHART_CLOUMN_GROUP);
	if(!pColumn)
		return;
	pColumn->Clear();

	for(auto& map:m_MapGroupMainSec)
	{
		XNodeGroupInfo* pNodeGroup=map.second;
		int nID=pNodeGroup->GetGroupID();

		int nNodeNum=GetNodeNumByGroupID(nID,TRUE);
		CString szKey;
		szKey.Format(_T("%s%d"),_T("m"),nID);
		pColumn->InsertColumnData(szKey,nNodeNum,TRUE);
	}

	for(auto& map:m_MapNodeGroup)
	{
		XNodeGroupInfo* pNodeGroup=map.second;
		int nID=pNodeGroup->GetGroupID();
		//if(pNodeGroup->GetOnLine())
		{
			int nNodeNum=GetNodeNumByGroupID(nID,FALSE);
			CString szKey;
			szKey.Format(_T("%s%d"),_T("g"),nID);
			pColumn->InsertColumnData(szKey,nNodeNum,FALSE);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//获取数据库中的全部节点
void XNodeManage::OperateOfGetAllNode()
{
	//3 7 list 获取64个16位数据（表示节点ID）
	XSendDataManage::GetInstance()->AddSendDataOfGetAllNode();
}
//下面根据设备通道连接情况 获取在线节点
void XNodeManage::OperateOfGetDeviceInfo()
{
	// 1 10 硬件通道数，硬件类型
	XSendDataManage::GetInstance()->AddSendDataOfGetDeviceInfo();
}

//void XNodeManage::OperateOfGetNodeByChannel()
//{
//	//0 11 按位表示连接状态
//	XSendDataManage::GetInstance()->AddSendDataOfGetNodeByChannel();
//}

void XNodeManage::OperateOfGetLoginUser()
{
	//2 11 登录用户列表
	XSendDataManage::GetInstance()->AddSendDataOfGetLoginUser();
}

void XNodeManage::OperateOfGetMatrixStatus()
{
	//4 11
	XSendDataManage::GetInstance()->AddSendDataOfGetMatrixStatus();
}

void XNodeManage::OperateOfOSDImage()
{
	XBaseMap dlg;
	m_pBaseMapDlg=&dlg;

	dlg.SetDelegate(this);
	dlg.DoModal();
	m_pBaseMapDlg=NULL;
}

void XNodeManage::SendDataOfOSDImage(int nIndex)
{
	XSendDataManage::GetInstance()->AddSendDataOfOSDImage(this,nIndex);
}

void XNodeManage::SetMatrixInputToOutput(int nInputChannel)
{
	XSendDataManage::GetInstance()->AddSendDataOfMatrix(this,nInputChannel);
}

void XNodeManage::OperateOfMainAndSecondList()
{
	//0 8
	XSendDataManage::GetInstance()->AddSendDataOfMainAndSecondList();
}

void XNodeManage::OperateOfReadNodeGroup()
{
	//1 8
	XSendDataManage::GetInstance()->AddSendDataOfReadNodeGroup();
}

void XNodeManage::OperateOfReadOnLineNodeGroup()
{
	//1 8
	XSendDataManage::GetInstance()->AddSendDataOfReadOnLineNodeGroup();
}

void XNodeManage::OperateOfSystemStatus()
{
	//5 11
	XSendDataManage::GetInstance()->AddSendDataSystemStatus();
}

//////////////////////////////////////////////////////////////////////////
void XNodeManage::OperateOfReDeviceInfo(char* pData)
{
	XDevicePara devicePara;
	XJsonManage::GetInstance()->ParseJsonToReDeviceInfo(pData,devicePara);

	if(devicePara.GetResult()==0)
	{
		m_nHardWareChannel=devicePara.GetHardWareChannel();
		m_szMatrixModel=devicePara.GetMatrixModel();

		CString szFPGAVer=devicePara.GetFPGAVer();
		//TRACE(_T("fpgaVer=%s\n"),szFPGAVer);

		m_pDelegate->SetFPGAVersion(devicePara.GetFPGAVer());
		m_pDelegate->SetHardWareChannel(devicePara.GetHardWareChannel());
		m_pDelegate->SetMatrixModel(devicePara.GetMatrixModel());
		//////////////////////////////////////////////////////////////////////////
		//按照通道个数创建集合（FALSE）
		ClearMapChannel();
		for(int i=0;i<devicePara.GetHardWareChannel();i++)
		{
			m_MapChannel.insert(std::pair<int,BOOL>(i,FALSE));
		}

		//获取到通道集合再根据通道查找连接状况
		//0 11 按位表示连接状态
		XSendDataManage::GetInstance()->AddSendDataOfGetNodeByChannel();
	}
}

void XNodeManage::OperateOfReNodeByChannel(char* pData)
{
	XNodeConnect nodeConnect;
	XJsonManage::GetInstance()->ParseJsonToReNodeByChannel(pData,nodeConnect);

	if(nodeConnect.GetResult()==0)
	{
		//更新节点连接状态(16位标识)
		VEC_CONNECT& VecConnect=nodeConnect.GetVecConnect();
		int nIndex=0;

		for(auto& nFlag:VecConnect)
		{
			for(int i=0;i<16;i++)
			{
				BOOL bConnect=FALSE;
				if((nFlag&(1<<i))!=0)
					bConnect=TRUE;
				else
					bConnect=FALSE;
				//////////////////////////////////////////////////////////////////////////
				int nChannel=i+(nIndex*16);
				MAP_CHANNEL::iterator iter=m_MapChannel.find(nChannel);
				if(iter!=m_MapChannel.end())
				{
					iter->second=bConnect;
				}
			}
			nIndex++;
		}

		//开始 添加饼图
		InsertDevicePieData();
		
		//每次查找之前 先清空节点集合 (插拔没有通知，所以每次清空集合)
		ClearMapNode();

		//根据连接状态查找节点情况（每次最多查询24个）
		m_VecChannel.clear();
		for(auto& map:m_MapChannel)
		{
			int nChannel=map.first;
			BOOL bConnect=map.second;

			if(bConnect)
				m_VecChannel.push_back(nChannel);

			if(m_VecChannel.size()>=24)
			{
				XSendDataManage::GetInstance()->AddSendDataOfGetNodeInfo(this); //1 11
				m_VecChannel.clear();
			}
		}

		XSendDataManage::GetInstance()->AddSendDataOfGetNodeInfo(this);
		m_VecChannel.clear();
	}
}

void XNodeManage::QueryNodeDetailInfo()
{
	XSendDataManage::GetInstance()->AddSendDataOfGetNodeDetailInfo(this);
}

static UINT QueryDetailInfo(void* p)
{
	XNodeManage* pManage=(XNodeManage*)p;
	pManage->QueryNodeDetailInfo();
	return 0;
}

void XNodeManage::BeginNodeNodeDetailInfoThread()
{
	AfxBeginThread((AFX_THREADPROC)QueryDetailInfo,(void*)this);
}

void XNodeManage::OperateOfReNodeInfo(char* pData)
{
	//包含初始化节点集合
	XJsonManage::GetInstance()->ParseJsonToReNodeInfo(pData,m_MapNode);
	for(auto iter=m_MapNode.begin();iter!=m_MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		pNode->SetNodeManage(this);
	}
	ResetView();
	//接着查询详细信息
	//添加线程 11.14 太快会不出现名称
	BeginNodeNodeDetailInfoThread();
	//XSendDataManage::GetInstance()->AddSendDataOfGetNodeDetailInfo(this); //3 7

	//查询节点状态（每次最多查询24个）
	m_VecNodeStatus.clear();
	for(auto& map:m_MapNode)
	{
		int nNodeID=map.first;
		m_VecNodeStatus.push_back(nNodeID);

		if(m_VecNodeStatus.size()>=24)
		{
			XSendDataManage::GetInstance()->AddSendDataOfGetNodeStatus(this);//7 9
			m_VecNodeStatus.clear();
		}
	}

	XSendDataManage::GetInstance()->AddSendDataOfGetNodeStatus(this);
	m_VecNodeStatus.clear();
}

void XNodeManage::OperateOfReNodeDetailInfo(char* pData)
{
	//TRACE(_T("OperateOfReNodeDetailInfo\n"));
	//节点详细信息
	XNodeInfo nodeInfo;
	XJsonManage::GetInstance()->ParseJsonToReNodeDetailInfo(pData,this,nodeInfo);

	if(nodeInfo.GetSendType()==_T("LIST"))
	{
		//转换为全部节点
		m_VecNodeID.clear();
		int nIndex=0;
		for(auto& nValue:m_VecNodeList)
		{
			for(int i=0;i<16;i++)
			{
				if((nValue&(1<<i))!=0)
				{
					//节点ID从0开始算
					int nNodeID=i+(nIndex*16);
					m_VecNodeID.push_back(nNodeID);
				}
			}
			nIndex++;
		}
		//获取节点总数
		m_nNodeAll=m_VecNodeID.size();
		//开启一个线程来获取所有节点信息（最大1024个）
		BeginQueryNodeThread();
		//TRACE(_T("main\n"));
	}
	else if(nodeInfo.GetSendType()==_T("QUERY"))
	{
		if(nodeInfo.GetQueryType()==_T("NODEONLINE"))
		{
			if(nodeInfo.GetResult()==0)
			{
				//另存在线节点
				for(auto& map:m_MapNode)
				{
					XNode* pNode=map.second;
					m_MapNodeMainSec.insert(std::pair<int,HTREEITEM>(pNode->GetNodeID(),NULL));
				}
			}
			//节点详细信息之后，刷新矩阵屏幕排列
			m_pDelegate->ResetMatrixArray();
		}
	}
	else if(nodeInfo.GetSendType()==_T("UPDATE"))
	{
		//返回在线节点
		switch(nodeInfo.GetUpdateMark())
		{
			case UPDATAMAKE_GROUP:
				{
					//从组中删除，添加带后面
					//MAP_NODE::iterator iter=m_MapNode.find();
					if(m_MapNode.find(nodeInfo.GetNodeID())!=m_MapNode.end())
					{
						XNode* pNode=m_MapNode[nodeInfo.GetNodeID()];

						int nNodeID=pNode->GetNodeID();
						int nType=pNode->GetNodeType();
						HTREEITEM hItem=pNode->GetTreeItem();

						if(nodeInfo.GetNodeGroup()==0)
						{			
							if(hItem!=NULL)
							{
								//先删除
								XLeftWnd::GetInstance()->DeleteNodeGroupFromTree(hItem);
								//添加在后面
								XLeftWnd::GetInstance()->AddNodeInTreeLast(pNode,nType);

								//更新第二页的屏幕
								m_pDelegate->UpdateScreenAfterRemoveNode(nodeInfo.GetNodeID());
							}
						}
						else
						{
							if(hItem!=NULL)
							{
								//先删除
								XLeftWnd::GetInstance()->DeleteNodeGroupFromTree(hItem);
								//添加到组内
								XLeftWnd::GetInstance()->AddNodeInGroup(pNode,nodeInfo.GetNodeGroup());
							}
						}
					}
				}
				break;
			case UPDATAMAKE_MASTER:
				{
					//从组中删除，不添加到后面了
					if(m_MapNodeMainSec.find(nodeInfo.GetNodeID())!=m_MapNodeMainSec.end())
					{
						HTREEITEM hItem=m_MapNodeMainSec[nodeInfo.GetNodeID()];
						if(nodeInfo.GetNodeMaster()==0)
						{
							XLeftWnd::GetInstance()->DeleteNodeGroupFromTree(hItem);
							//更新第二页的屏幕
							m_pDelegate->UpdateScreenAfterRemoveNode(nodeInfo.GetNodeID());
						}
						else
						{
							//添加到组
							XLeftWnd::GetInstance()->AddNodeInGroupMaster(nodeInfo.GetNodeID(),nodeInfo.GetNodeMaster());
						}
					}
				}
				break;
			case UPDATAMAKE_CONTROL:
				{

				}
				break;
			default:
				break;
		}

		//节点详细信息之后，刷新矩阵屏幕排列
		m_pDelegate->ResetMatrixArray();
	}
	else if(nodeInfo.GetSendType()==_T("DEL"))
	{

	}

	ResetView();
}

void XNodeManage::OperateOfReNodeStatus(char* pData)
{
	//TRACE(_T("OperateOfReNodeStatus\n"));
	//节点状态（7 9）
	XNodeStatus result;
	XJsonManage::GetInstance()->ParseJsonToReNodeStatus(pData,m_MapNode,result);

	if(result.GetResult()==0)
	{
		if(result.GetSendType()==_T("BLINK"))
		{

		}
		else if(result.GetSendType()==_T("NODEALL"))
		{
			//设置节点柱形图数据  有可能会插入多次（//节点闪烁不执行）
			InsertNodeColumnData();
		}
		else if(result.GetSendType()==_T("TAKEOVER"))
		{
			//设置节点柱形图数据  有可能会插入多次（//节点闪烁不执行）
			InsertNodeColumnData();

			//更新属性面板
			CMFCPropertyGridProperty* pTakeOver=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_TAKEOVERNODE);
			if(NULL!=pTakeOver)
			{
				if(NULL==m_pNodeSel)
					return;

				int nTakeOverNodeChannel=0;
				MAP_NODE& MapNode=GetMapNode();
				MAP_NODE::iterator iter=MapNode.find(m_pNodeSel->GetNodeID());
				if(iter!=MapNode.end())
				{
					XNode* pNode=iter->second;
					nTakeOverNodeChannel=pNode->GetChannel();
				}

				pTakeOver->SetValue(_variant_t((long)nTakeOverNodeChannel));
			}

			CMFCPropertyGridProperty* pTarget=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_TARGETNODE);
			if(NULL!=pTarget)
			{
				if(NULL==m_pNodeSel)
					return;

				CString szBeTakeOver;
				MAP_NODE& MapNode=GetMapNode();
				for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
				{
					XNode* pNode=iter->second;
					if(m_pNodeSel->GetNodeID()==pNode->GetTakeOverNodeID())
					{
						CString szTemp;
						szTemp.Format(_T("%d;"),pNode->GetChannel());
						szBeTakeOver+=szTemp;
					}
				}
				pTarget->SetValue(_variant_t(szBeTakeOver));
			}

			ResetView();
		}
		else if(result.GetSendType()==_T("ALTER"))
		{
			//用于改变后更改其他属性（暂时用到系统更改）
			//TRACE(_T("Alter\n"));
			if(result.GetSubSendType()==_T("SCREEN_MODEL"))
			{
				//TRACE(_T("Alter SCREEN MODEL\n"));
			}

			//改变节点属性
			if(result.GetSubSendType()==_T("HID_MODEL"))
			{
				//改变系统时，设置分屏状态
				int nHideModel=result.GetHidModel();

				CMFCPropertyGridProperty* pSplitScreen=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SPLITSCREEN);
				if(NULL!=pSplitScreen)
				{
					if(nHideModel==3||nHideModel==4)
						pSplitScreen->Enable(TRUE);
					else
						pSplitScreen->Enable(FALSE);
				}
			}
		}
	}
}

void XNodeManage::OperateOfReLoginUser(char* pData)
{
	XJsonManage::GetInstance()->ParseJsonToReLoginUser(pData,m_MapUserLoginStatus);

	//查询登录用户状态（用可能需要分开查询）
	m_VecLoginUser.clear();
	for(auto iter=m_MapUserLoginStatus.begin();iter!=m_MapUserLoginStatus.end();++iter)
	{
		int nUserID=iter->first;
		m_VecLoginUser.push_back(nUserID);

		if(m_VecLoginUser.size()>=24)
		{
			XSendDataManage::GetInstance()->AddSendDataOfGetLoginUserStatus(this);
			m_VecLoginUser.clear();
		}
	}

	XSendDataManage::GetInstance()->AddSendDataOfGetLoginUserStatus(this);
	m_VecLoginUser.clear();
}

void XNodeManage::OperateOfReLoginUserStatus(char* pData)
{
	XJsonManage::GetInstance()->ParseJsonToReLoginUserStatus(pData,m_MapUserLoginStatus);
}

void XNodeManage::OperateOfReNodeLogin(char* pData)
{
	XNodeLogin nodeLogin;
	XJsonManage::GetInstance()->ParseJsonToReNodeLogin(pData,nodeLogin);
	if(nodeLogin.GetResult()>0)
	{
		//登录成功
		//查找
		int nUserID=nodeLogin.GetResult();
		//int nUserID=GetUserIDByName(nodeLogin.GetUserName());
		XSendDataManage::GetInstance()->AddSendDataOfGetLoginUserStatus(nUserID);

		//更新属性
		CMFCPropertyGridProperty* pUser=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODELOGINUSER);
		if(NULL!=pUser)
			pUser->Enable(FALSE);
		//更新状态
		CMFCPropertyGridProperty* pNodeLogin=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODELOGIN);
		if(NULL!=pNodeLogin)
			pNodeLogin->SetValue(_variant_t(_T("True")));
	}
}

void XNodeManage::OperateOfReNodeLogOut(char* pData)
{
	XResult result;
	XJsonManage::GetInstance()->ParseJsonToReNodeLogOut(pData,result);
	if(result.GetResult()==0)
	{
		//退出成功
		//CMFCPropertyGridProperty* pTemp=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODELOGINUSER);
		//CString szUserName=(_variant_t)pTemp->GetValue();

		//int nUserID=GetUserIDByName(szUserName);
		//在获取在线用户情况
		//OperateOfGetLoginUser();

		//更新属性
		CMFCPropertyGridProperty* pTemp=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODELOGINUSER);
		if(NULL!=pTemp)
			pTemp->Enable(TRUE);
		//更新状态
		CMFCPropertyGridProperty* pNodeLogin=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODELOGIN);
		if(NULL!=pNodeLogin)
			pNodeLogin->SetValue(_variant_t(_T("False")));
	}
}

void XNodeManage::OperateOfReTakeOver(char* pData)
{
	//接管
	XTakeOver takeOver;
	XJsonManage::GetInstance()->ParseJsonToReTakeOver(pData,takeOver);
	if(takeOver.GetResult()==2)
	{
		//每次接管成功，要保存接管状态
		XTakeOver* pTakeOver=new XTakeOver;
		pTakeOver->SetNodeID(takeOver.GetNodeID());
		pTakeOver->SetTargetID(takeOver.GetTargetID());
		pTakeOver->SetExclusive(takeOver.GetExclusive());
		if(m_MapTakeOver.find(takeOver.GetNodeID())==m_MapTakeOver.end())
		{
			m_MapTakeOver.insert(std::pair<int,XTakeOver*>(takeOver.GetNodeID(),pTakeOver));
		}
		else
		{
			m_MapTakeOver[takeOver.GetNodeID()]=pTakeOver;
		}

		//准备重新获取两个拖拽节点状态
		XSendDataManage::GetInstance()->AddSendDataOfGetNodeStatus(takeOver.GetNodeID(),takeOver.GetTargetID());
	}
}

void XNodeManage::OperateOfReTakeOverCancel(char *pData)
{
	//取消接管或者预览
	XTakeOver takeOver;
	XJsonManage::GetInstance()->ParseJsonToReTakeOverCancel(pData,takeOver);
	if(takeOver.GetResult()==0)
	{
		//取消接管成功
		//更新属性
		CMFCPropertyGridProperty* pTakeOver=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_TAKEOVERNODE);
		if(NULL!=pTakeOver)
			pTakeOver->SetValue(_variant_t((long)0));

		CMFCPropertyGridProperty* pTarget=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_TARGETNODE);
		if(NULL!=pTarget)
			pTarget->SetValue(_variant_t((long)0));

		CMFCPropertyGridProperty* pPreview=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_PREVIEW);
		if(NULL!=pPreview)
			pPreview->SetValue(_variant_t((long)0));

		CMFCPropertyGridProperty* pTargetPreview=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_PREVIEWTARGET);
		if(NULL!=pTargetPreview)
			pTargetPreview->SetValue(_variant_t((long)0));

		//获取节点状态
	}
}

void XNodeManage::OperateOfRePreview(char* pData)
{
	//预览
	XTakeOver takeOver;
	XJsonManage::GetInstance()->ParseJsonToPreview(pData,takeOver);
	if(takeOver.GetResult()==1)
	{
		//预览成功
		//CMFCPropertyGridProperty* pPreview=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_PREVIEW);
		//if(NULL!=pPreview)
		//{
		//	int nChannelID=GetNodeChannelByID(takeOver.GetTargetID());
		//	if(nChannelID!=0)
		//		pPreview->SetValue(_variant_t((long)nChannelID));
		//}

		//CMFCPropertyGridProperty* pTarget=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_PREVIEWTARGET);
		//if(NULL!=pTarget)
		//{
		//	int nChannelID=GetNodeChannelByID(takeOver.GetNodeID());
		//	if(nChannelID!=0)
		//		pTarget->SetValue(_variant_t((long)nChannelID));
		//}
		//查询节点状态
	}
}

void XNodeManage::OperateOfReAlterNodeName(char* pData)
{
	XAlterNodeName alterNodeName;
	XJsonManage::GetInstance()->ParseJsonToAlterNodeName(pData,alterNodeName);
	if(alterNodeName.GetResult()==0)
	{
		//更改成功
		CMFCPropertyGridProperty* pNodeName=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODENAME);
		if(NULL!=pNodeName)
		{
			pNodeName->SetValue(_variant_t(alterNodeName.GetNodeName()));
		}

		for(auto iter=m_MapNode.begin();iter!=m_MapNode.end();++iter)
		{
			XNode* pNode=iter->second;
			if(pNode->GetNodeID()==alterNodeName.GetNodeID())
			{
				pNode->SetNodeName(alterNodeName.GetNodeName());

				HTREEITEM item=pNode->GetTreeItem();
				if(NULL!=item)
					XLeftWnd::GetInstance()->ChangeNodeItemText(item,alterNodeName.GetNodeName());
			}
		}
		InvalidateView();
	}
}

void XNodeManage::OperateOfReMatrixStatus(char* pData)
{
	XJsonManage::GetInstance()->ParseJsonToReMatrixStatus(pData,m_MapMatrix);
	//返回切换状态后 设置切换页面 状态
	m_pDelegate->ResetMatrixSwitchStatus();
}

void XNodeManage::OperateOfReMatrix(char* pData)
{
	//矩阵切换
	//要判断是什么情况下回的数据
	XMatrix matrix;
	XJsonManage::GetInstance()->ParseJsonToReMatrix(pData,m_MapMatrix,matrix);
	//更新输出属性
	OperateOfGetMatrixStatus();
	//传输OSD底图时，会将输入切给全部输出
	CString szType=matrix.GetMatrixType();
	if(szType==_T("MATRIXALL"))
	{
		//定时发送
		m_pBaseMapDlg->SendOSDPicOrder();
	}
}

void XNodeManage::OperateOfReOSDImage(char* pData)
{
	//获取图片序号和结果
	XOSDImage osdImage;
	XJsonManage::GetInstance()->ParseJsonToReOSDImage(pData,osdImage);

	if(osdImage.GetResult()==1)
	{
		//图片序号返回
		//Sleep(3000);
		m_pBaseMapDlg->SetOperate(osdImage.GetPicIndex());
	}
}

void XNodeManage::OperateOfReHideOSDImage(char* pData)
{
	//返回隐藏OSD底图

}

void XNodeManage::OperateOfReReadNodeGroup(char* pData)
{
	//节点组
	XJsonManage::GetInstance()->ParseJsonToReReadNodeGroup(pData,m_MapNodeGroup);

	//读取节点详细信息--这时组集合已经有元素，因为查了两遍所以会出现回两遍情况（所以每次要清空排列信息集合）
	XSendDataManage::GetInstance()->AddSendDataOfNodeGroupInfo(this);

	//获取到节点组 之后匹配坐席名称
	m_pDelegate->MatchSeatNameByGroupName();
}

void XNodeManage::OperateOfReNodeGroupInfo(char* pData)
{
	//节点组信息
	XNodeGroup nodeGroup;
	XJsonManage::GetInstance()->ParseJsonToReNodeGroupInfo(pData,m_MapNodeGroup,nodeGroup);

	//TRACE(_T("SendType=%s\n"),nodeGroup.GetSendType());
	//TRACE(_T("result=%d\n"),nodeGroup.GetResult());

	if(nodeGroup.GetSendType()==_T("ADD"))
	{
		if(nodeGroup.GetResult()==101)
		{
			//先添加组
			int nType=nodeGroup.GetType();
			XLeftWnd::GetInstance()->AddNodeGroup(nodeGroup.GetGroupName(),nType,FALSE);

			if(nodeGroup.GetCreateMode()==CREATEMODE_ARRAGE)
			{
				//根据坐席添加组
				//将组成员更改组ID
				MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
				MAP_NODEGROUP::iterator iter=MapNodeGroup.find(nodeGroup.GetGroupName());
				if(iter!=MapNodeGroup.end())
				{
					XNodeGroupInfo* pInfo=iter->second;

					int nGroupID=pInfo->GetGroupID();
					VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
					for(auto iter=VecArrage.begin();iter!=VecArrage.end();++iter)
					{
						std::vector<int> VecInt=*iter;
						for(auto iter=VecInt.begin();iter!=VecInt.end();++iter)
						{
							int nNodeID=*iter;

							int nMark=UPDATAMAKE_GROUP;
							XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(nNodeID,nGroupID,nMark);
						}
					}
				}
				//更新坐席名称
				m_pDelegate->UpdateGroupNameAfterAddArrage(nodeGroup.GetGroupName());
			}
			else if(nodeGroup.GetCreateMode()==CREATEMODE_DRAG)
			{
				//右键创建组，同一种方式，只是没有两个拖拽节点。
				if(nodeGroup.GetType()==1)
				{
					//1为输入组，把组名称传递给第二页面
					m_pDelegate->SetGroupNameByAddGroupIn(nodeGroup.GetGroupName());
				}

				//拖拽添加组
				//VecArrage中没有成员，把两个拖拽两个节点插入组内
				VEC_DRAG& VecDrag=XLeftWnd::GetInstance()->GetVecDrag();
				for(auto iter=VecDrag.begin();iter!=VecDrag.end();++iter)
				{
					int nNodeID=*iter;

					int nMark=UPDATAMAKE_GROUP;
					XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(nNodeID,nodeGroup.GetGroupID(),nMark);
				}
				VecDrag.clear();
			}

			//发送刷新组成员
			XSendDataManage::GetInstance()->AddSendDataOfRefreashGroup(nodeGroup.GetGroupID());
		}
	}
	else if(nodeGroup.GetSendType()==_T("UPDATE"))
	{
		if(nodeGroup.GetResult()==101)
		{
			switch(nodeGroup.GetUpdateMark())
			{
			case UPDATAMAKE_GROUPARRAGE:
				{
					//更新组排列，有成员从0添加到组里	
					{
						//移除出组不会执行
						MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
						MAP_NODEGROUP::iterator iter=MapNodeGroup.find(nodeGroup.GetGroupName());
						if(iter!=MapNodeGroup.end())
						{
							XNodeGroupInfo* pInfo=iter->second;
							int nGroupID=pInfo->GetGroupID();

							VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
							for(auto iter=VecArrage.begin();iter!=VecArrage.end();++iter)
							{
								std::vector<int> VecInt=*iter;
								for(auto iter=VecInt.begin();iter!=VecInt.end();++iter)
								{
									int nNodeID=*iter;

									MAP_NODE::iterator iterNode=m_MapNode.find(nNodeID);
									if(iterNode!=m_MapNode.end())
									{
										XNode* pNode=iterNode->second;
										if(pNode->GetGroup()==0)
										{
											int nMark=UPDATAMAKE_GROUP;
											XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(nNodeID,nGroupID,nMark);
										}
									}
								}
							}
						}
					}

					//1,2,3不会同时存在
					{
						//1,删除的组员
						VEC_DEL& VecDel=m_pDelegate->GetVecDel();
						for(auto iter=VecDel.begin();iter!=VecDel.end();++iter)
						{
							int nNodeID=*iter;
							if(nNodeID!=0)
							{
								int nMark=UPDATAMAKE_GROUP;
								XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(nNodeID,0,nMark);
							}
						}
						VecDel.clear();
						//如果主更改，更新预览墙
						MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
						MAP_NODEGROUP::iterator iter=MapNodeGroup.find(nodeGroup.GetGroupName());
						if(iter!=MapNodeGroup.end())
						{
							XNodeGroupInfo* pInfo=iter->second;
							m_pDelegate->UpdateShowMasterAfterRemoveNode(pInfo->GetMaster());
						}
					}


					//2,从组中拖拽删除
					//VEC_DRAG& VecDrag=XLeftWnd::GetInstance()->GetVecDrag();
					//for(auto iter=VecDrag.begin();iter!=VecDrag.end();++iter)
					//{
					//	int nNodeID=*iter;
					//	if(nNodeID!=0)
					//	{
					//		int nMark=UPDATAMAKE_GROUP;
					//		XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(nNodeID,0,nMark);
					//	}
					//}
					//VecDrag.clear();

					//3,移动到其他组（更新组ID）
					//移至其他组
					//MAP_DRAG& MapDrag=XLeftWnd::GetInstance()->GetMapDrag();
					//for(auto iter=MapDrag.begin();iter!=MapDrag.end();++iter)
					//{
					//	int nFirstNodeID=iter->first;
					//	int nSecondNodeID=iter->second;

					//	int nMark=UPDATAMAKE_GROUP;
					//	XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(nFirstNodeID,nSecondNodeID,nMark);
					//}
					//MapDrag.clear();

					//发送刷新组成员
					XSendDataManage::GetInstance()->AddSendDataOfRefreashGroup(nodeGroup.GetGroupID());
				}
				break;
			case UPDATAMAKE_GROUPNAME:
				{
					MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
					MAP_NODEGROUP::iterator iter=MapNodeGroup.find(nodeGroup.GetGroupName());
					if(iter!=MapNodeGroup.end())
					{
						XNodeGroupInfo* pInfo=iter->second;
						HTREEITEM item=pInfo->GetGroupItem();
						if(item!=NULL)
						{
							//先改变坐席名称
							XLeftWnd::GetInstance()->UpdateGroupNameAfterChange(item,nodeGroup.GetGroupName());
							//然后改变树节点
							XLeftWnd::GetInstance()->ChangeGroupItemText(item,nodeGroup.GetGroupName());
							//改变属性名称
							CMFCPropertyGridProperty* pGroupName=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODEGROUPNAME);
							if(NULL!=pGroupName)
								pGroupName->SetValue(_variant_t(nodeGroup.GetGroupName()));
						}
					}
				}
				break;
			case UPDATAMAKE_GROUPMASTER:
				{
					//更改坐席 主节点
					//int nNodeID=nodeGroup.GetNodeID();
					//m_pDelegate->SetSeatArrageMaster(nNodeID);
				}
				break;
			default:
				break;
			}
		}
	}
	else if(nodeGroup.GetSendType()==_T("DEL"))
	{
		if(nodeGroup.GetResult()==0)
		{
			//TRACE(_T("nodeGroup.GetSendType()\n"));
			//节点组成员组改为0
			MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
			for(auto iter=m_MapNode.begin();iter!=m_MapNode.end();++iter)
			{
				XNode* pNode=iter->second;
				if(pNode->GetGroup()==nodeGroup.GetGroupID())
				{
					int nNodeID=pNode->GetNodeID();

					int nMark=UPDATAMAKE_GROUP;
					XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(nNodeID,0,nMark);
				}
			}


			//发送刷新组成员
			XSendDataManage::GetInstance()->AddSendDataOfRefreashGroup(nodeGroup.GetGroupID());
			//////////////////////////////////////////////////////////////////////////
			//删除树项
			//从集合中删除
			MAP_NODEGROUP::iterator iter1=MapNodeGroup.find(nodeGroup.GetGroupName());
			if(iter1!=MapNodeGroup.end())
			{
				XNodeGroupInfo* pInfo=iter1->second;
				HTREEITEM item=pInfo->GetGroupItem();

				XLeftWnd::GetInstance()->DeleteNodeGroupFromTree(item);
				MapNodeGroup.erase(iter1);

				delete pInfo;
			}

			//清除第一个名称
			//删除组时
			m_pDelegate->ClearInfo(nodeGroup.GetGroupName());

			//清空属性
			XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
			XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();
		}
	}

	//每次更新组都会进入这里（插入组柱形图数据）
	InsertNodeGroupColumnData();
}

void XNodeManage::OperateOfReRefreashGroup()
{
	//更新组成员信息
	//组于主副屏  返回信息没处理
}

void XNodeManage::OperateOfReMainAndSecondList(char* pData)
{
	//返回主副屏列表
	//std::map<int,CString> MapMainSecondList;
	XJsonManage::GetInstance()->ParseJsonToReMainAndSecondList(pData,m_MapGroupMainSec);
	//查询主副屏
	for(auto& map:m_MapGroupMainSec)
	{
		XNodeGroupInfo* pInfo=map.second;
		XSendDataManage::GetInstance()->AddSendDataOfQueryMainAndSecond(pInfo->GetGroupID());
	}
}

void XNodeManage::OperateOfReMainAndSecond(char* pData)
{
	//主副屏组
	XNodeGroup nodeGroup;
	XJsonManage::GetInstance()->ParseJsonToReMainAndSecond(pData,m_MapGroupMainSec,nodeGroup);

	if(nodeGroup.GetSendType()==_T("ADD"))
	{
		if(nodeGroup.GetResult()==101)
		{
			//添加到 输入
			XLeftWnd::GetInstance()->AddNodeGroup(nodeGroup.GetGroupName(),1,TRUE);

			//把组名称传递给第二页面
			m_pDelegate->SetGroupNameByAddGroupIn(nodeGroup.GetGroupName());

			//发送刷新组成员
			XSendDataManage::GetInstance()->AddSendDataOfRefreashMainSecGroup(nodeGroup.GetGroupID());
		}
	}
	else if(nodeGroup.GetSendType()==_T("QUERY"))
	{

	}
	else if(nodeGroup.GetSendType()==_T("DEL"))
	{
		if(nodeGroup.GetResult()==0)
		{
			//节点组成员主副屏改为0		
			for(auto iter=m_MapNode.begin();iter!=m_MapNode.end();++iter)
			{
				XNode* pNode=iter->second;
				if(pNode->GetMaster()==nodeGroup.GetGroupID())
				{
					int nNodeID=pNode->GetNodeID();

					int nMark=UPDATAMAKE_MASTER;
					XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(nNodeID,0,nMark);
				}
			}
			
			//发送刷新组成员
			XSendDataManage::GetInstance()->AddSendDataOfRefreashMainSecGroup(nodeGroup.GetGroupID());
			//////////////////////////////////////////////////////////////////////////
			//删除树项
			//从集合中删除
			MAP_GROUPMAINSEC& MapNodeGroup=GetMapGroupMainSec();
			MAP_GROUPMAINSEC::iterator iter1=MapNodeGroup.find(nodeGroup.GetGroupName());
			if(iter1!=MapNodeGroup.end())
			{
				XNodeGroupInfo* pInfo=iter1->second;
				HTREEITEM item=pInfo->GetGroupItem();

				XLeftWnd::GetInstance()->DeleteNodeGroupFromTree(item);
				MapNodeGroup.erase(iter1);

				delete pInfo;
			}

			//清除第一个坐席桌面名称
			//删除组时
			m_pDelegate->ClearInfo(nodeGroup.GetGroupName());

			//清空属性
			XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
			XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();
		}
	}
	else if(nodeGroup.GetSendType()==_T("UPDATE"))
	{
		if(nodeGroup.GetResult()==101)
		{
			switch(nodeGroup.GetUpdateMark())
			{
				case UPDATAMAKE_MASTERNAME://ok
					{
						MAP_GROUPMAINSEC& MapNodeGroup=GetMapGroupMainSec();
						MAP_GROUPMAINSEC::iterator iter=MapNodeGroup.find(nodeGroup.GetGroupName());
						if(iter!=MapNodeGroup.end())
						{
							XNodeGroupInfo* pInfo=iter->second;
							HTREEITEM item=pInfo->GetGroupItem();
							if(item!=NULL)
							{
								//先改变坐席名称
								XLeftWnd::GetInstance()->UpdateGroupNameAfterChange(item,nodeGroup.GetGroupName());
								//然后改变树节点
								XLeftWnd::GetInstance()->ChangeGroupItemText(item,nodeGroup.GetGroupName());
								//改变属性名称
								CMFCPropertyGridProperty* pGroupName=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_MAINSECGROUPNAME);
								if(NULL!=pGroupName)
									pGroupName->SetValue(_variant_t(nodeGroup.GetGroupName()));
							}
						}
					}
					break;
				case UPDATAMAKE_MASTERARRAGE:
					{
						//更新组排列，有成员从0添加到组里	
						{
							//移除出组不会执行
							MAP_GROUPMAINSEC& MapNodeGroup=GetMapGroupMainSec();
							MAP_GROUPMAINSEC::iterator iter=MapNodeGroup.find(nodeGroup.GetGroupName());
							if(iter!=MapNodeGroup.end())
							{
								XNodeGroupInfo* pInfo=iter->second;
								int nGroupID=pInfo->GetGroupID();

								VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
								for(auto iter=VecArrage.begin();iter!=VecArrage.end();++iter)
								{
									std::vector<int> VecInt=*iter;
									for(auto iter=VecInt.begin();iter!=VecInt.end();++iter)
									{
										int nNodeID=*iter;

										MAP_NODE::iterator iterNode=m_MapNode.find(nNodeID);
										if(iterNode!=m_MapNode.end())
										{
											XNode* pNode=iterNode->second;
											if(pNode->GetMaster()==0)
											{
												int nMark=UPDATAMAKE_MASTER;
												XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(nNodeID,nGroupID,nMark);
											}
										}
									}
								}
							}
						}

						//1,2,3不会同时存在
						{
							//1,删除的组员
							VEC_DEL& VecDel=m_pDelegate->GetVecDel();
							for(auto iter=VecDel.begin();iter!=VecDel.end();++iter)
							{
								int nNodeID=*iter;
								if(nNodeID!=0)
								{
									int nMark=UPDATAMAKE_MASTER;
									XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(nNodeID,0,nMark);
								}
							}
							VecDel.clear();
							//如果主更改，更新预览墙
							MAP_NODEGROUP& MapNodeGroup=GetMapNodeGroup();
							MAP_NODEGROUP::iterator iter=MapNodeGroup.find(nodeGroup.GetGroupName());
							if(iter!=MapNodeGroup.end())
							{
								XNodeGroupInfo* pInfo=iter->second;
								m_pDelegate->UpdateShowMasterAfterRemoveNode(pInfo->GetMaster());
							}
						}
					}
					break;
				default:
					break;

			}

			//发送刷新组成员
			XSendDataManage::GetInstance()->AddSendDataOfRefreashMainSecGroup(nodeGroup.GetGroupID());
		}
	}
}

void XNodeManage::OperateOfReSystemStatus(char* pData)
{
	XSystemStatus* pSystemStatus=XSystemStatus::GetInstance();
	XJsonManage::GetInstance()->ParseJsonToReSystemStatus(pData,pSystemStatus);
	if(pSystemStatus->GetResult()==0)
	{
		//TRACE(_T("cpuT=%d\n"),pSystemStatus->m_nCpuTemp);
		//TRACE(_T("MatrT=%d\n"),pSystemStatus->m_nMatrixTemp);
		//TRACE(_T("cpu=%s\n"),pSystemStatus->m_szCpuUse);
		//TRACE(_T("Mem=%s\n"),pSystemStatus->m_szMemUse);
		InvalidateView();
	}
}

void XNodeManage::OperateOfSaveScene()
{
	//单独保存接管状态
	XSaveScene dlg;
	if(IDOK==dlg.DoModal())
	{
		CString szName=dlg.GetName();
		//把所有接管都添加到集合中
		SaveAllTakeOver();
		//保存文件
		CString szPath=HandlePath::GetPlanPath(szName);
		if(XSceneData::SaveData(this,szPath))
		{
			//添加到树
			XScene::GetInstance()->AddSceneToTree(szName);
		}
		else
		{
			_M(_T("248"),_T("保存预案失败！"),MB_OK);
		}
	}
}

void XNodeManage::SaveAllTakeOver()
{
	for(auto& node:m_MapNode)
	{
		XNode* pNode=node.second;
		XTakeOver* pTakeOver=new XTakeOver;
		pTakeOver->SetNodeID(pNode->GetNodeID());
		pTakeOver->SetTargetID(pNode->GetTakeOverNodeID());
		//pTakeOver->SetExclusive(pN);现在只有一种接管方式

		if(m_MapTakeOver.find(pNode->GetNodeID())==m_MapTakeOver.end())
		{
			m_MapTakeOver.insert(std::pair<int,XTakeOver*>(pNode->GetNodeID(),pTakeOver));
		}
		else
		{
			m_MapTakeOver[pNode->GetNodeID()]=pTakeOver;
		}
	}
}

void XNodeManage::OperateOfOpenScene()
{
	CString szSceneName=XConstantData::GetInstance()->GetOpenSceneName();
	//TRACE(_T("SceneName=%s\n"),szSceneName);

	CString szPath=HandlePath::GetPlanPath(szSceneName);
	if(XSceneData::GetData(this,szPath))
	{
		for(auto& map:m_MapTakeOver)
		{
			XTakeOver* pTakeOver=map.second;
			XSendDataManage::GetInstance()->AddSendDataOfTakeOver(pTakeOver->GetNodeID(),pTakeOver->GetTargetID(),pTakeOver->GetExclusive());
		}
	}
}

//void XNodeManage::OperateOfInitScene()
//{
//	//XScene::GetInstance()->InitScene();
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XNodeManage::Operate(OPERATETYPE type,void* pData)
{
	switch(type)
	{
	case OPERATETYPE_SCALE200:
	case OPERATETYPE_SCALE175:
	case OPERATETYPE_SCALE150:
	case OPERATETYPE_SCALE125:
	case OPERATETYPE_SCALE100:
	case OPERATETYPE_SCALE75:
	case OPERATETYPE_SCALE50:
		{
			ChangeScale(type);
		}
		break;
	case OPERATETYPE_ALLNODE:
		{
			OperateOfGetAllNode();
		}
		break;
	case OPERATETYPE_DEVICEINFO:
		{
			OperateOfGetDeviceInfo();
		}
		break;
	case OPERATETYPE_REDEVICEINFO:
		{
			OperateOfReDeviceInfo((char*)pData);
		}
		break;
	//case OPERATETYPE_GETNODECHANNEL:
	//	{
	//		OperateOfGetNodeByChannel();
	//	}
	//	break;
	case OPERATETYPE_RENODECHANNEL:
		{
			OperateOfReNodeByChannel((char*)pData);
		}
		break;
	case OPERATETYPE_RENODEINFO:
		{
			OperateOfReNodeInfo((char*)pData);
		}
		break;
	case OPERATETYPE_RENODEDETAILINFO:
		{
			OperateOfReNodeDetailInfo((char*)pData);
		}
		break;
	case OPERATETYPE_RENODESTATUS:
		{
			OperateOfReNodeStatus((char*)pData);
		}
		break;
	case OPERATETYPE_GETLOGINUSER:
		{
			OperateOfGetLoginUser();
		}
		break;
	case OPERATETYPE_RELOGINUSER:
		{
			OperateOfReLoginUser((char*)pData);
		}
		break;
	case OPERATETYPE_RELOGINUSERSTATUS:
		{
			OperateOfReLoginUserStatus((char*)pData);
		}
		break;
	case OPERATETYPE_RENODELOGIN:
		{
			OperateOfReNodeLogin((char*)pData);
		}
		break;
	case OPERATETYPE_RENODELOGOUT:
		{
			OperateOfReNodeLogOut((char*)pData);
		}
		break;
	case OPERATETYPE_RETAKEOVER:
		{
			OperateOfReTakeOver((char*)pData);
		}
		break;
	case OPERATETYPE_RETAKEOVERCANCEL:
		{
			OperateOfReTakeOverCancel((char*)pData);
		}
		break;
	case OPERATETYPE_PREVIEW:
		{
			OperateOfRePreview((char*)pData);
		}
		break;
	case OPERATETYPE_ALTERNODENAME:
		{
			OperateOfReAlterNodeName((char*)pData);
		}
		break;
	case OPERATETYPE_MENUOUTOFLOGOUT:
		{
			OperateOfMeunOutOfLogout();
		}
		break;
	case OPERATETYPE_MATRIXSTATUS:
		{
			OperateOfGetMatrixStatus();
		}
		break;
	case OPERATETYPE_REMATRIXSTATUS:
		{
			OperateOfReMatrixStatus((char*)pData);
		}
		break;
	case OPERATETYPE_REMATRIX:
		{
			OperateOfReMatrix((char*)pData);
		}
		break;
	case OPERATETYPE_OSDIMAGE:
		{
			OperateOfOSDImage();
		}
		break;
	case OPERATETYPE_REOSDIMAGE:
		{
			OperateOfReOSDImage((char*)pData);
		}
		break;
	case OPERATETYPE_REHIDEOSDIMAGE:
		{
			OperateOfReHideOSDImage((char*)pData);
		}
		break;
	case OPERATETYPE_READNODEGROUP:
		{
			OperateOfReadNodeGroup();
		}
		break;
	case OPERATETYPE_READONLINENODEGROUP:
		{
			OperateOfReadOnLineNodeGroup();
		}
		break;
	case OPERATETYPE_REREADNODEGROUP:
		{
			OperateOfReReadNodeGroup((char*)pData);
		}
		break;
	case OPERATETYPE_RENODEGROUPINFO:
		{
			OperateOfReNodeGroupInfo((char*)pData);
		}
		break;
	case OPERATETYPE_GETMAINANDSECOND:
		{
			OperateOfMainAndSecondList();
		}
		break;
	case OPERATETYPE_REMAINANDSECONDLIST:
		{
			OperateOfReMainAndSecondList((char*)pData);
		}
		break;
	case OPERATETYPE_REMAINANDSECOND:
		{
			OperateOfReMainAndSecond((char*)pData);
		}
		break;
	case OPERATETYPE_REREFREASGGROUP:
		{
			OperateOfReRefreashGroup();
		}
		break;
	case OPERATETYPE_SYSTEMSTATUS:
		{
			OperateOfSystemStatus();
		}
		break;
	case OPERATETYPE_RESYSTEMSTATUS:
		{
			OperateOfReSystemStatus((char*)pData);
		}
		break;
	case OPERATETYPE_SAVESCENE:
		{
			OperateOfSaveScene();
		}
		break;
	case OPERATETYPE_OPENTAKEOVERSCENE:
		{
			OperateOfOpenScene();
		}
		break;
	default:
		break;
	}
}

void XNodeManage::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);
	int nType=HandleIni::GetInt(_T("Info"),_T("NodeScale"),0,szPath);

	if(nType==type)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void XNodeManage::ChangeScale(int nType)
{
	int nScale=0;
	switch(nType)
	{
	case OPERATETYPE_SCALE200:
		{
			nScale=200;
		}
		break;
	case OPERATETYPE_SCALE175:
		{
			nScale=175;
		}
		break;
	case OPERATETYPE_SCALE150:
		{
			nScale=150;
		}
		break;
	case OPERATETYPE_SCALE125:
		{
			nScale=125;
		}
		break;
	case OPERATETYPE_SCALE100:
		{
			nScale=100;
		}
		break;
	case OPERATETYPE_SCALE75:
		{
			nScale=75;
		}
		break;
	case OPERATETYPE_SCALE50:
		{
			nScale=50;
		}
		break;
	}

	if(nScale!=m_nScale)
	{
		m_nScale=nScale;
		SaveDataOfScale(int(nType));
		ResetView();
	}
}

void XNodeManage::ControlDataChange(XDATATYPE type,void* pControl)
{

}


void XNodeManage::UpdateControlDataShow(XDATATYPE type,void* pControl)
{

}