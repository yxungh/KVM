#include "stdafx.h"
#include "XMatrixManage.h"
#include "XDrawMatrixManage.h"
#include "XCaculateMatrixManage.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XDelegateMatrixManage.h"
#include "XLeftWnd.h"
#include "XNode.h"
#include "..\TemplateView.h"
#include "XMatrixScreen.h"
#include <math.h>
#include "HandleCalculate.h"
#include "XCaculateMatrixManage.h"
#include "XCaculateNodeManage.h"
#include "XPropertiesWnd.h"
#include "XConstantData.h"
#include "XSendDataManage.h"
#include "XMatrixArray.h"
#include "XScene.h"


XMatrixManage::XMatrixManage()
{
}

XMatrixManage::~XMatrixManage()
{
	ClearVecMatrixScreen();
}

void XMatrixManage::ClearVecMatrixScreen()
{
	for(auto& vec:m_VecMatrixScreen)
	{
		delete vec;
	}
	m_VecMatrixScreen.clear();
}

void XMatrixManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY)
{
	XDrawMatrixManage::ViewDraw(pDC,rect,noffsetX,noffsetY,this);
}

CSize XMatrixManage::ViewGetSize()
{
	return XCaculateMatrixManage::ViewGetSize(this);
}

Color XMatrixManage::GetViewColor()
{
	return m_Color;
}

void XMatrixManage::SetViewColor(Color& color)
{
	m_Color=color;
}

float XMatrixManage::GetScale()
{
	return m_nScale/100.0f;
}

CString XMatrixManage::GetTitle()
{
	return m_szTitle;
}

void XMatrixManage::SetTitle(CString szTitle)
{
	m_szTitle=szTitle;
}

MAP_NODE& XMatrixManage::GetMapNode()
{
	return m_pDelegate->GetMapNode();
}

void XMatrixManage::ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	XCaculateMatrixManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,m_Point);
	if(m_pTempScreen==NULL)
		return;

	if(m_pTempScreen->GetSwitch())
	{
		m_bDown=TRUE;
		XConstantData::GetInstance()->SetOutChannel(m_pTempScreen->GetChannel());
		XConstantData::GetInstance()->SetInChannel(m_pTempScreen->GetInChannel());
	}

	CString szRealName=m_pTempScreen->GetReadName();
	MAP_NODE& MapNode=GetMapNode();
	for(auto& map:MapNode)
	{
		XNode* pNode=map.second;
		if(pNode->GetRealID()==szRealName)
		{
			XPropertiesWnd::GetInstance()->SetNode(pNode);
			XPropertiesWnd::GetInstance()->SetNodeGroup(NULL);
			XPropertiesWnd::GetInstance()->SetSeat(NULL);
			pNode->SetPropertiesWnd();
		}
	}

	//TRACE(_T("ViewLButtonDown\n"));
}

void XMatrixManage::ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{

}

void XMatrixManage::ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	POINTF tempPoint;
	XCaculateMatrixManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,tempPoint);

	m_bDown=FALSE;

	if(!m_bCreateWnd)
		return;

	m_bCreateWnd=FALSE;
	//判断鼠标在不在屏幕上
	XMatrixScreen* pScreen=XCaculateMatrixManage::GetMatrixScreenByPoint(this,tempPoint);
	if(pScreen==NULL)
	{
		//不在屏幕上 
		int nOutChannel=XConstantData::GetInstance()->GetOutChannel();
		XSendDataManage::GetInstance()->AddSendDataOfMatrix(0,nOutChannel);
	}
	InvalidateView();
}

void XMatrixManage::ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	POINTF tempPoint;
	XCaculateMatrixManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,tempPoint);

	if(m_bDown)
	{
		//鼠标按下
		if(abs((int)tempPoint.X-(int)m_Point.X)>5||
		   abs((int)tempPoint.Y-(int)m_Point.Y)>5)
		{
			m_bCreateWnd=TRUE;
			Move(m_Point,tempPoint);
			//m_Point=tempPoint;
		}
	}
	else
	{
		XMatrixScreen* pScreen=NULL;
		if(XCaculateMatrixManage::DecidePointInScreen(this,pScreen,tempPoint))
		{
			if(pScreen==NULL)
			{
				return;
			}
			m_pTempScreen=pScreen;
			m_DragRect=m_pTempScreen->GetRect();
			m_CursorType=CURSORTYPE_HAND;
		}
		else
		{
			m_CursorType=CURSORTYPE_NORMAL;
			m_pTempScreen=NULL;
		}
	}
	
	SetCursor(m_CursorType);
}

void XMatrixManage::Move(POINTF& point1,POINTF& point2)
{
	RECTF tempRect=m_pTempScreen->GetRect();

	SIZEF size;
	size.Width=point2.X-point1.X;
	size.Height=point2.Y-point1.Y;

	XCaculateMatrixManage::Move(tempRect,size);
	//m_pTempScreen->SetRect(tempRect);
	m_DragRect=tempRect;

	InvalidateView();
}

void XMatrixManage::ViewMouseLeave()
{

}

void XMatrixManage::SetCursor(CURSORTYPE type)
{
	::SetCursor(GetCursor(type));
}

HCURSOR XMatrixManage::GetCursor(CURSORTYPE type)
{
	return XCaculateNodeManage::GetCursor(type);
}

BOOL XMatrixManage::ViewMouseWheel(short zDelta)
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

void XMatrixManage::ViewKeyUp(UINT nChar)
{

}

void XMatrixManage::ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{

}

void XMatrixManage::ControlDataChange(XDATATYPE type,void* pControl)
{

}

void XMatrixManage::UpdateControlDataShow(XDATATYPE type,void* pControl)
{

}

void XMatrixManage::Init()
{
	InitData();
}

void XMatrixManage::InitData()
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);
	int nType=HandleIni::GetInt(_T("Info"),_T("MatrixScale"),0,szPath);

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
				HandleIni::WriteData(_T("Info"),_T("MatrixScale"),szTemp,szPath);
			}
			break;
	}
}

void XMatrixManage::ReloadInterface()
{

}

void XMatrixManage::ResetView()
{
	ResetViewSize();
	InvalidateView();
}

void XMatrixManage::InvalidateView()
{
	CTemplateView* pView=m_pDelegate->GetView();
	if(NULL!=pView)
	{
		pView->Invalidate(TRUE);
	}
}

void XMatrixManage::ResetViewSize()
{
	CTemplateView* pView=m_pDelegate->GetView();
	if(NULL!=pView)
	{
		pView->ResetSize();
	}
}

void XMatrixManage::ResetLeftWnd()
{
	//切换左侧面板内容
	XLeftWnd::GetInstance()->InitTreeListItemOfMatrix();
	ResetMatrixArray();
}

void XMatrixManage::ResetSceneWnd()
{
	//接管预案
	XScene::GetInstance()->InitSceneOfTakeOver();
}

void XMatrixManage::ClearProperityWnd()
{

}

void XMatrixManage::DragEnd(CPoint& point,CRect& rect)
{
	UNUSED(rect);

	CView* pView=m_pDelegate->GetView();
	pView->ScreenToClient(&point);

	CRect rectView;
	pView->GetClientRect(&rectView);

	POINTF tempPoint;
	XCaculateMatrixManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),point,tempPoint);
	
	XMatrixScreen* pScreen=XCaculateMatrixManage::GetMatrixScreenByPoint(this,tempPoint);
	if(NULL==pScreen)
		return;
	int nInChannel=XConstantData::GetInstance()->GetInChannel();
	if(nInChannel!=0)
	{
		//切换矩阵
		XSendDataManage::GetInstance()->AddSendDataOfMatrix(nInChannel,pScreen->GetChannel());
	}
}

void XMatrixManage::ChangeScale(int nType)
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

void XMatrixManage::SaveDataOfScale(int nType)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szTemp=_T("");
	szTemp.Format(_T("%d"),nType);

	HandleIni::WriteData(_T("Info"),_T("MatrixScale"),szTemp,szIniPath);
}

void XMatrixManage::ResetMatrixArray()
{
	//TRACE(_T("ResetMatrixArray\n"));
	//执行时已经有了 矩阵切换状态
	MAP_MATRIX& MapMatrix=m_pDelegate->GetMapMatrix();



	ClearVecMatrixScreen();
	//登录成功初始化屏幕排列
	MAP_NODE& MapNode=GetMapNode();
	int nIndex=0;
	for(auto& map:MapNode)
	{
		XNode* pNode=map.second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			nIndex++;
			XMatrixScreen* pScreen=new XMatrixScreen;
			pScreen->SetName(pNode->GetNodeName());
			pScreen->SetChannel(pNode->GetChannel());
			pScreen->SetReadName(pNode->GetRealID());
			pScreen->SetID(pNode->GetNodeID());
			pScreen->SetIndex(nIndex);
			m_VecMatrixScreen.push_back(pScreen);
		}
	}
	//根据行列设置序号和区域
	int nSize=m_VecMatrixScreen.size();
	//TRACE(_T("nSize=%d\n"),nSize);
	if(nSize!=0)
	{
		//大致平分行列
		int nSqrt=(int)sqrt(nSize);
		int nTemp=GetNumBySize(nSize,nSqrt);
		if(nTemp!=0)
		{
			//if(m_nScreenCountH==0&&m_nScreenCountV==0)
			{
				m_nScreenCountH=nTemp;
				m_nScreenCountV=nSqrt;
			}
		}
		///////////////////////////////////
		float top=0.0f;
		float left=0.0f;
		int nScreenIndex=0;
		for(int i=0;i<m_nScreenCountV;i++)
		{
			left=0.0f;
			for(int j=0;j<m_nScreenCountH;j++)
			{
				RECTF screenRect(left,top,(Gdiplus::REAL)m_nScreenWidth,(Gdiplus::REAL)m_nScreenHeight);
				nScreenIndex++;

				XMatrixScreen* pScreen=GetScreenByIndex(nScreenIndex);
				if(pScreen!=NULL)
				{
					pScreen->SetRect(screenRect);

					//设置对应输入节点
					int nOutChannel=pScreen->GetChannel();
					if(MapMatrix.find(nOutChannel)!=MapMatrix.end())
					{
						int nInChannel=MapMatrix[nOutChannel];
						if(nInChannel!=0)
						{
							//根据通道获取名称
							CString szInName=GetNameByChannel(nInChannel);
							
							pScreen->SetInName(szInName);
							pScreen->SetInChannel(nInChannel);
							pScreen->SetSwitch(TRUE);
						}
					}
				}
				left+=m_nScreenWidth;
			}
			top+=m_nScreenHeight;
		}
	}

	ResetView();
}

CString XMatrixManage::GetNameByChannel(int nChannel)
{
	MAP_NODE& MapNode=GetMapNode();
	for(auto& node:MapNode)
	{
		XNode* pNode=node.second;
		if(pNode->GetChannel()==nChannel)
		{
			return pNode->GetNodeName();
		}
	}
	return _T("");
}

void XMatrixManage::ResetMatrixSwitchStatus()
{
	//TRACE(_T("ResetMatrixSwitchStatus\n"));
	////根据状态 设置矩阵页面
	MAP_MATRIX& MapMatrix=m_pDelegate->GetMapMatrix();

	for(auto& screen:m_VecMatrixScreen)
	{
		XMatrixScreen* pScreen=screen;
		int nOutChannel=pScreen->GetChannel();
		if(MapMatrix.find(nOutChannel)!=MapMatrix.end())
		{
			int nInChannel=MapMatrix[nOutChannel];
			if(nInChannel!=0)
			{
				//根据通道获取名称
				CString szInName=GetNameByChannel(nInChannel);

				pScreen->SetInName(szInName);
				pScreen->SetInChannel(nInChannel);
				pScreen->SetSwitch(TRUE);
			}	
			else
			{
				pScreen->SetInName(_T(""));
				pScreen->SetInChannel(0);
				pScreen->SetSwitch(FALSE);
			}
		}
	}
	ResetView();
}

XMatrixScreen* XMatrixManage::GetScreenByIndex(int nIndex)
{
	for(auto& vec:m_VecMatrixScreen)
	{
		XMatrixScreen* pScreen=vec;
		if(pScreen->GetIndex()==nIndex)
			return pScreen;
	}
	return NULL;
}

int XMatrixManage::GetNumBySize(int nSize,int nSqrt)
{
	for(int i=0;i<nSqrt;i++)
	{
		if((nSize+i)%nSqrt==0)
		{
			return (nSize+i)/nSqrt;
		}
	}
	return 0;
}

void XMatrixManage::OperateOfScreenArray()
{
	return;
	//节点排列
	XMatrixArray dlg;
	dlg.DoModal();



}

int XMatrixManage::GetNodeOutCount()
{
	int nCount=0;
	MAP_NODE& MapNode=GetMapNode();
	for(auto& map:MapNode)
	{
		XNode* pNode=map.second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			nCount++;
		}
	}
	return nCount;
}

//////////////////////////////////////////////////////////////////////////
void XMatrixManage::Operate(OPERATETYPE type,void* pData)
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
		case OPERATETYPE_MATRIXARRAY:
			{
				OperateOfScreenArray();
			}
			break;
		//case OPERATETYPE_INITMATRIXARRAY:
			//{
				//OperateOfInitScreenArray();
			//}
			//break;
		default:
			break;
	}
}

void XMatrixManage::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);
	int nType=HandleIni::GetInt(_T("Info"),_T("MatrixScale"),0,szPath);

	if(nType==type)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}