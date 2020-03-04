#include "stdafx.h"
#include "XSplitManage.h"
#include "XDelegateSplitManage.h"
#include "..\TemplateView.h"
#include "XDrawSplitManage.h"
#include "XCaculateSplitManage.h"
#include "XPropertiesWnd.h"
#include "XSplitScreen.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "HandleCalculate.h"
#include "XLeftWnd.h"
#include "XSplitSignal.h"
#include "XSignal.h"
#include "XConstantData.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XSendDataManage.h"
#include <algorithm>
#include "XSplitWindow.h"
#include "XScene.h"




XSplitManage::XSplitManage()
{
}


XSplitManage::~XSplitManage()
{
	ClearVecSplitScreen();
	ClearVecSignal();
}

void XSplitManage::ClearVecSplitScreen()
{
	for(auto& pScreen:m_VecSplitScreen)
	{
		delete pScreen;
	}
	m_VecSplitScreen.clear();
}

void XSplitManage::ClearVecSignal()
{ 
	for(auto& pSignal:m_VecSignal)
	{
		delete pSignal;
	}
	m_VecSignal.clear();
}

void XSplitManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY)
{
	XDrawSplitManage::ViewDraw(pDC,rect,noffsetX,noffsetY,this);
}

CSize XSplitManage::ViewGetSize()
{
	return XCaculateSplitManage::ViewGetSize(this);
}

void XSplitManage::ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{


}

void XSplitManage::ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	XCaculateSplitManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,m_Point);

	//判断在屏幕上
	XSplitScreen* pScreen=XCaculateSplitManage::DecidePointInScreen(this,m_Point);
	if(NULL==pScreen)
		return;

	//判断在信号上面
	XSignal* pSignal=XCaculateSplitManage::DecidePointInSignal(this,m_Point);
	if(NULL==pSignal)
		return;

	m_pTempSignal=pSignal;
	m_bDown=TRUE;

	//判断点在关闭按钮
	if(XCaculateSplitManage::DecidePointInColse(pSignal,m_Point))
	{
		if(m_CursorType==CURSORTYPE_NORMAL)
			CloseSignal(pSignal->GetSignalID());
	}
	else if(XCaculateSplitManage::DecidePointInFull(pSignal,m_Point))
	{
		if(m_CursorType==CURSORTYPE_NORMAL)
			SetFull();
	}
	else if(XCaculateSplitManage::DecidePointInMax(pSignal,m_Point))
	{
		if(m_CursorType==CURSORTYPE_NORMAL)
			SetMax();
	}
	else if(XCaculateSplitManage::DecidePointInMin(pSignal,m_Point))
	{
		if(m_CursorType==CURSORTYPE_NORMAL)
			SetMin();
	}
	else
	{
		m_Rect=m_pTempSignal->GetRect();
		//快速置顶
		if(m_bQuickTop)
		{
			std::vector<int> VecID;
			GetIntersectSignal(m_pTempSignal->GetRect(),VecID);
			//如果是最后一个不执行
			if(VecID.back()==m_pTempSignal->GetSignalID())
				return;

			XSignalLevel level;
			level.m_nSignalID=m_pTempSignal->GetSignalID();
			level.m_szType=_T("TOP");
			XSendDataManage::GetInstance()->AddSendDataOfAlterLevel(m_szSplitName,level);
		}
	}

	InvalidateView();
}

void XSplitManage::ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	POINTF pointf;
	XCaculateSplitManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,pointf);

	if(m_bDown&&(nFlags&MK_LBUTTON)&&NULL!=m_pTempSignal)
	{
		//判断在标题栏上或者鼠标类型
		//if(XCaculateSplitManage::DecidePointInTitle(m_pTempSignal,pointf))
		//{
		//	MoveSignal(m_Point,pointf);
		//}
		//else if(m_CursorType==CURSORTYPE_NESW||m_CursorType==CURSORTYPE_NS||
		//   m_CursorType==CURSORTYPE_NWSE||m_CursorType==CURSORTYPE_WE)
		//{
		//	MoveSignal(m_Point,pointf);	
		//}
		//else
		//{
		//	TRACE(_T("NoMome\n"));
		//}

		float f=fabs(m_Point.X-pointf.Y);
		if(fabs(m_Point.X-pointf.X)>3.0f||fabs(m_Point.Y-pointf.Y)>3.0f)
		{
			MoveSignal(m_Point,pointf);
		}
	
		InvalidateView();
	}
	else
	{
		//判断在信号上面
		XSignal* pSignal=XCaculateSplitManage::DecidePointInSignal(this,pointf);
		if(NULL!=pSignal)
		{
			m_pTempSignal=pSignal;

			m_Rect=pSignal->GetRect();
			m_PositionType=XCaculateSplitManage::DecidePointInSignalPosition(this,pSignal->GetRect(),pointf);
			m_CursorType=XCaculateSplitManage::GetCursorTypeByPositionType(m_PositionType);
		}
		else
		{
			m_CursorType=CURSORTYPE_NORMAL;
		}
	}

	SetCursor(m_CursorType);
}

void XSplitManage::ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	POINTF pointf;
	XCaculateSplitManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,pointf);

	XSplitScreen* pScreen=XCaculateSplitManage::DecidePointInScreen(this,m_Point);
	if(NULL==pScreen)
		return;

	m_bDown=FALSE;
	if(NULL==m_pTempSignal)
		return;

	RECTF rectSignal=m_pTempSignal->GetRect();
	int nSignalID=m_pTempSignal->GetSignalID();
	//首先设置显示信号区域
	VEC_SPLITSCREEN VecScreen;
	CalculateVecScreen(rectSignal,VecScreen);
	if(VecScreen.size()==0)
	{
		//删除信号
		CloseSignal(nSignalID);
		InvalidateView();
		return;
	}

	//计算与屏幕相交部分
	RECTF rectInter=XCaculateSplitManage::CalculateSignalRect(rectSignal,VecScreen);
	if(rectInter.Width<70||rectInter.Height<30)
	{
		CloseSignal(nSignalID);
		InvalidateView();
		return;
	}

	//限制模式
	//判断每个屏幕信号个数(限制模式)
	if(m_nLimitModel==CMDUITYPE_LIMIT)
	{
		CString szRet;
		if(!DecideSignalCount(VecScreen,szRet))
		{
			CString szTip;
			szTip.Format(_T("%s:%s%s"),_C(_T("333"),_T("信号个数超过限制")),_C(_T("334"),_T("屏幕")),szRet);
			_M(_T("0"),szTip,MB_OK);
			//设置回原位
			m_pTempSignal->SetRect(m_Rect);
		}
	}
	else if(m_nLimitModel==CMDUITYPE_DELTOP)
	{
		for(auto& pScreen:VecScreen)
		{
			int nLevelUse=pScreen->GetLevelUse();
			if(nLevelUse==4)
			{
				RECTF rect=pScreen->GetRect();

				std::vector<int> VecID;
				VecID.clear();
				GetIntersectSignal(rect,VecID);

				int nSignalID=VecID[VecID.size()-1];
				XSendDataManage::GetInstance()->AddSendDataOfDelSignal(m_szSplitName,nSignalID);
			}
		}

		m_pTempSignal->SetRect(rectInter);
	}
	else if(m_nLimitModel==CMDUITYPE_DELBOTTOM)
	{
		for(auto& pScreen:VecScreen)
		{
			int nLevelUse=pScreen->GetLevelUse();
			if(nLevelUse==4)
			{
				RECTF rect=pScreen->GetRect();

				std::vector<int> VecID;
				VecID.clear();
				GetIntersectSignal(rect,VecID);

				int nSignalID=VecID[0];
				XSendDataManage::GetInstance()->AddSendDataOfDelSignal(m_szSplitName,nSignalID);
			}
		}

		m_pTempSignal->SetRect(rectInter);
	}


	m_pTempSignal=NULL;
	InvalidateView();
}

void XSplitManage::ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	POINTF pointf;
	XCaculateSplitManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,pointf);


	//判断鼠标
	XSplitScreen* pScreen=XCaculateSplitManage::DecidePointInScreen(this,pointf);
	if(NULL==pScreen)
		return;
	
	//判断在信号上面
	XSignal* pSignal=XCaculateSplitManage::DecidePointInSignal(this,pointf);
	if(NULL!=pSignal)
	{
		//在信号上
		ShowMenu();
	}
	else
	{
		//在屏幕上
	}


}

void XSplitManage::MoveSignal(POINTF& point1,POINTF& point2)
{
	RECTF tempRect=m_Rect;

	SIZEF size;
	size.Width=point2.X-point1.X;
	size.Height=point2.Y-point1.Y;

	XCaculateSplitManage::MoveSignal(m_PositionType,tempRect,size);

	//限制大小
	RECTF rect=tempRect;
	//TRACE(_T("x=%f,y=%f,w=%f,h=%f\n"),rect.X,rect.Y,rect.Width,rect.Height);
	if(rect.Width<72)
		rect.Width=72;
	if(rect.Height<30)
		rect.Height=30;

	m_pTempSignal->SetRect(rect);
	m_pTempSignal->SetMainRect(rect);
}

void XSplitManage::SetCursor(CURSORTYPE type)
{
	::SetCursor(XCaculateSplitManage::GetCursor(type));
}

void XSplitManage::ViewMouseLeave()
{

}

BOOL XSplitManage::ViewMouseWheel(short zDelta)
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

	ChangeSignalPng(nScale);

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

void XSplitManage::ViewKeyUp(UINT nChar)
{

}


void XSplitManage::Init()
{
	InitData();
	InitScreen();
}

void XSplitManage::InitData()
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);

	CString szKey;
	szKey.Format(_T("%s_%d"),_T("SplitScale"),GetBaseIndex());
	int nType=HandleIni::GetInt(_T("Info"),szKey,0,szPath);

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

				CString szKey;
				szKey.Format(_T("%s_%d"),_T("SplitScale"),GetBaseIndex());
				HandleIni::WriteData(_T("Info"),szKey,szTemp,szPath);
			}
			break;
	}

	//////////////////////////////////////////////////////////////////////////
	//初始化添加模式
	CString szKey1;
	szKey1.Format(_T("%s_%d"),_T("LimitModel"),GetBaseIndex());
	m_nLimitModel=HandleIni::GetInt(_T("Info"),szKey1,152,szPath);

	//CString szKry2;
	//szKry2.Format(_T("%s_%d"),_T("AddModel"),GetBaseIndex());
	//m_nAddModel=HandleIni::GetInt(_T("Info"),szKry2,155,szPath);
}

void XSplitManage::InitScreen()
{
	//需要放在登录成功之后
	float top=0.0f;
	float left=0.0f;
	int nScreenIndex=0;
	for(int i=0;i<m_nScreenCountY;i++)
	{
		left=0.0f;
		for(int j=0;j<m_nScreenCountX;j++)
		{
			RECTF screenRect(left,top,(Gdiplus::REAL)m_nResulationX,(Gdiplus::REAL)m_nResulationY);
			nScreenIndex++;

			XSplitScreen* pScreen=new XSplitScreen;
			pScreen->SetIndex(nScreenIndex);
			pScreen->SetRect(screenRect);

			m_VecSplitScreen.push_back(pScreen);

			left+=m_nResulationX;
		}

		top+=m_nResulationY;
	}

	ResetView();
}

void XSplitManage::SetViewColor(Color& color)
{
	m_Color=color;
	InvalidateView();
}

Color XSplitManage::GetViewColor()
{
	return m_Color;
}

float XSplitManage::GetScale()
{
	return m_nScale/100.0f;
}

float XSplitManage::GetCurScale()
{
	return m_nScale/100.0f;
}

void XSplitManage::ReloadInterface()
{

}

CString XSplitManage::GetTitle()
{
	return m_szTitle;
}

void XSplitManage::SetTitle(CString szTitle)
{
	m_szTitle=szTitle;
}

void XSplitManage::ResetLeftWnd()
{
	//切换左侧树
	XLeftWnd::GetInstance()->InitTreeListItemOfSplit();

}

void XSplitManage::ResetSceneWnd()
{
	XScene::GetInstance()->InitSceneOfSplit();
}

void XSplitManage::ClearProperityWnd()
{
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();
}

void XSplitManage::DragEnd(CPoint& point,CRect& rect)
{
	UNUSED(point);

	//添加信号
	CView* pView=m_pDelegate->GetView();
	pView->ScreenToClient(&rect);

	CRect rectView;
	pView->GetClientRect(&rectView);

	POINTF tempPointLT;
	XCaculateSplitManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rect.TopLeft(),tempPointLT);
	POINTF tempPointRB;
	XCaculateSplitManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),rect.BottomRight(),tempPointRB);

	//整个区域
	RECTF rectNormal(tempPointLT.X,tempPointLT.Y,tempPointRB.X-tempPointLT.X,tempPointRB.Y-tempPointLT.Y);

	VEC_SPLITSCREEN VecScreen;
	CalculateVecScreen(rectNormal,VecScreen);
	if(VecScreen.size()==0)
		return;
	
	//添加整个信号
	//计算与屏幕相交部分
	RECTF rectIntersect=XCaculateSplitManage::CalculateSignalRect(rectNormal,VecScreen);
	if(rectIntersect.Width<70||rectIntersect.Height<30)
		return;

	//判断每个屏幕信号个数(限制模式)
	switch(m_nLimitModel)
	{
		case CMDUITYPE_LIMIT:
			{
				CString szRet;
				if(!DecideSignalCount(VecScreen,szRet))
				{
					CString szTip;
					szTip.Format(_T("%s:%s%s"),_C(_T("333"),_T("信号个数超过限制")),_C(_T("334"),_T("屏幕")),szRet);
					_M(_T("0"),szTip,MB_OK);
					return;
				}
			}
			break;
		case CMDUITYPE_DELTOP:
			{
				//TRACE(_T("DelTop\n"));
				//按屏幕 先确定哪个屏幕超过限制
				for(auto& pScreen:VecScreen)
				{
					int nLevelUse=pScreen->GetLevelUse();
					if(nLevelUse==4)
					{
						RECTF rect=pScreen->GetRect();

						std::vector<int> VecID;
						VecID.clear();
						GetIntersectSignal(rect,VecID);

						int nSignalID=VecID[VecID.size()-1];
						XSendDataManage::GetInstance()->AddSendDataOfDelSignal(m_szSplitName,nSignalID);
					}
				}
			}
			break;
		case CMDUITYPE_DELBOTTOM:
			{
				//TRACE(_T("DelBottom\n"));
				for(auto& pScreen:VecScreen)
				{
					int nLevelUse=pScreen->GetLevelUse();
					if(nLevelUse==4)
					{
						RECTF rect=pScreen->GetRect();

						std::vector<int> VecID;
						VecID.clear();
						GetIntersectSignal(rect,VecID);

						int nSignalID=VecID[0];
						XSendDataManage::GetInstance()->AddSendDataOfDelSignal(m_szSplitName,nSignalID);
					}
				}
			}
			break;
		default:
			break;
	}


	//信号ID
	//int nSignalID=(GetTickCount()*10000)%576+1;
	//信号颜色40种颜色
	int nColorIndex=rand()%40;

	XSignal signal;

	signal.SetRect(rectIntersect);
	//开窗设置为0
	signal.SetSignalID(0);
	signal.SetColor(g_Color[nColorIndex]);
	//添加时设置层次为0
	signal.SetLevel(0);
	signal.SetSignalName(XConstantData::GetInstance()->GetSignalName());
	signal.SetInputCh(XConstantData::GetInstance()->GetInputCh());
	//是否剪切
	signal.SetCutUse(0);
	signal.GetVecCutPix().push_back(0);
	signal.GetVecCutPix().push_back(0);
	signal.GetVecCutPix().push_back(0);
	signal.GetVecCutPix().push_back(0);
	//转换真实分辨率（先按分辨率一样计算）
	//RECTF rectInsertScreen=XCaculateSplitManage::CalculateInsertScreenRect(VecScreen);
	
	int nX=(int)(rectIntersect.X*m_nRealResulationX/m_nResulationX);
	int nY=(int)(rectIntersect.Y*m_nRealResulationY/m_nResulationY);
	int nWidth=(int)(rectIntersect.Width*m_nRealResulationX/m_nResulationX);
	int nHeight=(int)(rectIntersect.Height*m_nRealResulationY/m_nResulationY);
	RECTF rt(nX,nY,nWidth,nHeight);
	signal.SetRealRect(rt);


	XSendDataManage::GetInstance()->AddSendDataOfAddSignal(m_szSplitName,signal);

	//////////////////////////////////////////////////////////////////////////
	//测试

	//XSignal* pSignal=new XSignal;
	//int nSignalID=(GetTickCount()*10000)%576+1;
	//pSignal->SetSignalID(nSignalID);
	//pSignal->SetRect(rectInter);
	//pSignal->SetColor(g_Color[nColorIndex]);
	////signal.SetLevel(0);
	//pSignal->SetSignalName(XConstantData::GetInstance()->GetSignalName());
	//pSignal->SetInputCh(XConstantData::GetInstance()->GetInputCh());


	//m_VecSignal.push_back(pSignal);
	//InvalidateView();
	//////////////////////////////////////////////////////////////////////////
	
}

BOOL XSplitManage::DecideSignalCount(VEC_SPLITSCREEN& VecScreen,CString& szRet)
{
	for(auto& pScreen:VecScreen)
	{
		if(pScreen->GetLevelUse()>=4)
		{
			szRet.Format(_T("%d"),pScreen->GetIndex());
			return FALSE;
		}
	}
	szRet=_T("");
	return TRUE;
}

void XSplitManage::CalculateVecScreen(RECTF& rect,VEC_SPLITSCREEN& VecScreen)
{
	for(auto& pScreen:m_VecSplitScreen)
	{
		RECTF rt=pScreen->GetRect();
		if(rt.Intersect(rect))
		{
			VecScreen.push_back(pScreen);
		}
	}
}

void XSplitManage::InvalidateView()
{
	CTemplateView* pView=m_pDelegate->GetView();
	if(NULL!=pView)
	{
		pView->Invalidate(TRUE);
	}
}

void XSplitManage::ResetViewSize()
{
	CTemplateView* pView=m_pDelegate->GetView();
	if(NULL!=pView)
	{
		pView->ResetSize();
	}
}

void XSplitManage::ResetView()
{
	ResetViewSize();
	InvalidateView();
}

void XSplitManage::SetFull()
{
	//占用分块面积 对应扩展
	if(NULL==m_pTempSignal)
		return;

	VEC_SPLITSCREEN VecScreen;
	CalculateVecScreen(m_pTempSignal->GetRect(),VecScreen);
	RECTF rect=XCaculateSplitManage::CalculateBolckRect(m_pTempSignal->GetRect(),VecScreen);

	m_pTempSignal->SetRect(rect);
	m_pTempSignal->SetMainRect(rect);

}

void XSplitManage::OperateOfExtend()
{
	//扩展
}

void XSplitManage::SetMax()
{
	//全屏 对应全屏
	if(NULL==m_pTempSignal)
		return;
	RECTF rectAllScreen=XCaculateSplitManage::CalculateInsertScreenRect(m_VecSplitScreen);

	//VEC_SPLITSCREEN VecScreen;
	//CalculateVecScreen(m_pTempSignal->GetRect(),VecScreen);
	//RECTF rectAllScreen=XCaculateSplitManage::CalculateInsertScreenRect(VecScreen);

	m_pTempSignal->SetRect(rectAllScreen);
}

void XSplitManage::OperateOfFullScreen()
{
	//全屏

}

void XSplitManage::SetMin()
{
	//还原为原来区域  对应还原
	if(NULL==m_pTempSignal)
		return;

	RECTF rect=m_pTempSignal->GetRect();
	RECTF rectMian=m_pTempSignal->GetMainRect();
	
	if(rect.Equals(rectMian))
		return;

	m_pTempSignal->SetRect(m_pTempSignal->GetMainRect());
}

void XSplitManage::OperateOfRestore()
{
	//还原
}


void XSplitManage::ShowMenu()
{
	CPoint p;
	GetCursorPos(&p);

	CMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING,ID_MENU_TOP,_C(_T("329"),_T("置顶")));
	menu.AppendMenu(MF_STRING,ID_MENU_BOTTOM,_C(_T("330"),_T("置底")));
	//menu.AppendMenu(MF_STRING,ID_MENU_UP,_C(_T("331"),_T("上移")));
	//menu.AppendMenu(MF_STRING,ID_MENU_DOWN,_C(_T("332"),_T("下移")));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING,ID_MENU_FULLSCREEN,_C(_T("344"),_T("全屏")));
	menu.AppendMenu(MF_STRING,ID_MENU_RESTORE,_C(_T("345"),_T("还原")));
	menu.AppendMenu(MF_STRING,ID_MENU_EXTEND,_C(_T("346"),_T("扩展")));
	menu.AppendMenu(MF_STRING,ID_MENU_CLOSESIGNAL,_C(_T("20"),_T("关闭")));

	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING,ID_MENU_PROPERTY,_C(_T("342"),_T("属性")));
	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,p.x,p.y,m_pDelegate->GetCWND());
	menu.DestroyMenu();
}

void XSplitManage::DeleteSignalByID(int nID)
{
	CloseShowSignal(nID);

	m_pTempSignal=NULL;
	InvalidateView();
}

void XSplitManage::OperateOfCloseSignal()
{
	//关闭信号
	CloseSignal(m_pTempSignal->GetSignalID());
}

void XSplitManage::CloseSignal(int nID)
{
	//清除窗口
	if(NULL!=m_pTempSignal)
	{
		XSendDataManage::GetInstance()->AddSendDataOfDelSignal(m_szSplitName,m_pTempSignal->GetSignalID());
	}	
}

void XSplitManage::CloseShowSignal(int nID)
{
	for(auto iter=m_VecSignal.begin();iter!=m_VecSignal.end();)
	{
		XSignal* pSignal=*iter;
		if(pSignal->GetSignalID()==nID)
		{
			iter=m_VecSignal.erase(iter);
			delete pSignal;
		}
		else
		{
			++iter;
		}
	}
}

void XSplitManage::SetSignalUp()
{
	//1，求相交的信号
	if(NULL==m_pTempSignal)
		return;
	std::vector<int> VecID;
	GetIntersectSignal(m_pTempSignal->GetRect(),VecID);

	//如果是最后一个不执行(包含一个情况)
	int nBackID=VecID.back();
	if(nBackID==m_pTempSignal->GetSignalID())
		return;

	int nSize=VecID.size();
	for(int i=0;i<nSize;i++)
	{
		if(m_pTempSignal->GetSignalID()==VecID[i])
		{
			if(i!=(nSize-1))
			{
				XSignal* pCurSignal=GetSignalByID(VecID[i]);
				XSignal* pSignal=GetSignalByID(VecID[i+1]);
				if(NULL==pCurSignal||NULL==pSignal)
					return;

				XSignalLevel level;
				level.m_nSignalID=pCurSignal->GetSignalID();
				level.m_nLevel=pSignal->GetLevel();
				level.m_szType=_T("SET");
				
				XSendDataManage::GetInstance()->AddSendDataOfAlterLevel(m_szSplitName,level);

				break;
			}
		}
	}
}

void XSplitManage::SetSignalDown()
{
	if(NULL==m_pTempSignal)
		return;
	std::vector<int> VecID;
	GetIntersectSignal(m_pTempSignal->GetRect(),VecID);

	//如果是第一个不执行
	int nFrontID=VecID.front();
	if(nFrontID==m_pTempSignal->GetSignalID())
		return;

	int nSize=VecID.size();
	for(int i=0;i<nSize;i++)
	{
		if(m_pTempSignal->GetSignalID()==VecID[i])
		{
			if(i!=0)
			{
				XSignal* pCurSignal=GetSignalByID(VecID[i]);
				XSignal* pSignal=GetSignalByID(VecID[i-1]);
				if(NULL==pCurSignal||NULL==pSignal)
					return;

				XSignalLevel level;
				level.m_nSignalID=pCurSignal->GetSignalID();
				level.m_nLevel=pSignal->GetLevel();
				level.m_szType=_T("SET");

				XSendDataManage::GetInstance()->AddSendDataOfAlterLevel(m_szSplitName,level);

				break;
			}
		}
	}
}

void XSplitManage::SetSignalTop()
{
	if(NULL==m_pTempSignal)
		return;

	std::vector<int> VecID;
	GetIntersectSignal(m_pTempSignal->GetRect(),VecID);
	//如果是最后一个不执行
	if(VecID.back()==m_pTempSignal->GetSignalID())
		return;

	XSignalLevel level;
	level.m_nSignalID=m_pTempSignal->GetSignalID();
	level.m_szType=_T("TOP");

	//更改层次--先更改 然后查询窗口list,根据返回ID顺序确定信号层次
	XSendDataManage::GetInstance()->AddSendDataOfAlterLevel(m_szSplitName,level);
}

void XSplitManage::SetSignalBottom()
{
	if(NULL==m_pTempSignal)
		return;

	std::vector<int> VecID;
	GetIntersectSignal(m_pTempSignal->GetRect(),VecID);
	//如果是最后一个不执行
	if(VecID.front()==m_pTempSignal->GetSignalID())
		return;

	XSignalLevel level;
	level.m_nSignalID=m_pTempSignal->GetSignalID();
	level.m_szType=_T("BOTTOM");

	XSendDataManage::GetInstance()->AddSendDataOfAlterLevel(m_szSplitName,level);
}

void XSplitManage::GetIntersectSignal(RECTF& rect,std::vector<int>& VecID)
{
	for(auto& pSignal:m_VecSignal)
	{
		RECTF rt=pSignal->GetRect();
		if(rt.Intersect(rect))
		{
			VecID.push_back(pSignal->GetSignalID());
		}
	}
}

XSignal* XSplitManage::GetSignalByID(int nID)
{
	for(auto& pSignal:m_VecSignal)
	{
		if(pSignal->GetSignalID()==nID)
		{
			return pSignal;
		}
	}
	return NULL;
}

int XSplitManage::GetVecIndex(XSignal* pSignal)
{
	if(NULL==pSignal)
		return -1;

	auto iter=find(m_VecSignal.begin(),m_VecSignal.end(),pSignal);
	int nIndex=iter-m_VecSignal.begin();

	return nIndex;
}

void XSplitManage::OperateOfClearSignal()
{
	//需要返回成功之后
	XSendDataManage::GetInstance()->AddSendDataOfClearSignal(m_szSplitName);
}

void XSplitManage::ClearSignal()
{
	ClearVecSignal();
	m_pTempSignal=NULL;

	InvalidateView();
}

BOOL compare(XSignal* pSignal1,XSignal* pSignal2)
{
	if(pSignal1->GetLevel()<pSignal2->GetLevel())
		return TRUE;
	else
		return FALSE;
}

void XSplitManage::SortSignalByLevel()
{
	sort(m_VecSignal.begin(),m_VecSignal.end(),compare);

	InvalidateView();
}

void XSplitManage::SetSignalOtherInfo(int nID)
{
	for(auto& pSignal:m_VecSignal)
	{
		if(nID!=0)
		{
			if(pSignal->GetSignalID()!=nID)
				continue;
		}

		//颜色
		int nColorIndex=rand()%40;
		pSignal->SetColor(g_Color[nColorIndex]);
		//区域
		RECTF realRect=pSignal->GetRealRect();
		float X=(realRect.X*m_nResulationX)/m_nRealResulationX;
		float Y=(realRect.Y*m_nResulationY)/m_nRealResulationY;
		float Width=(realRect.Width*m_nResulationX)/m_nRealResulationX;
		float Height=(realRect.Height*m_nResulationY)/m_nRealResulationY;

		RECTF rect(X,Y,Width,Height);
		pSignal->SetRect(rect);
		pSignal->SetMainRect(rect);
		//名称根据输入通道获取
		CString szName;
		szName.Format(_T("%d"),pSignal->GetLevel());
		pSignal->SetSignalName(szName);
	}

	ChangeSignalPng(m_nScale);

	InvalidateView();
}

XSplitScreen* XSplitManage::GetScreenByIndex(int nIndex)
{
	for(auto& pScreen:m_VecSplitScreen)
	{
		if(pScreen->GetIndex()==nIndex)
			return pScreen;
	}
	return NULL;
}

void XSplitManage::SetScreenInfo()
{
	//真实分辨率
	for(auto& pScreen:m_VecSplitScreen)
	{
		pScreen->SetPixIndex(m_nPixIndex);
		pScreen->SetRealResulationX(m_nRealResulationX);
		pScreen->SetRealResulationY(m_nRealResulationY);
	}

	//对应通道
	int nIndex=1;
	for(auto& nCh:m_VecSplitCh)
	{

		XSplitScreen* pScreen=GetScreenByIndex(nIndex);
		if(NULL!=pScreen)
		{
			pScreen->SetSplitCh(nCh);
		}

		nIndex++;
	}

	//屏幕占用通道
	SetLevelUse();
}

void XSplitManage::SetLevelUse()
{
	int nIndex=1;
	for(auto& nLevel:m_VecLevelList)
	{
		XSplitScreen* pScreen=GetScreenByIndex(nIndex);
		if(NULL!=pScreen)
		{
			pScreen->SetLevelUse(nLevel);
		}
		nIndex++;
	}
}

void XSplitManage::SetSignalLevel(int nSignalID,int nLevel)
{
	XSignal* pSignal=GetSignalByID(nSignalID);
	if(NULL!=pSignal)
	{
		pSignal->SetLevel(nLevel);
	}
	//InvalidateView();
}

void XSplitManage::AddSignal(std::vector<int>& VecIdList)
{
	ClearVecSignal();

	int nLevel=1;
	for(auto& nID:VecIdList)
	{
		XSignal* pSignal=new XSignal;
		pSignal->SetSignalID(nID);
		pSignal->SetLevel(nLevel);
		m_VecSignal.push_back(pSignal);
		nLevel++;
		XSendDataManage::GetInstance()->AddSendDataOfObtainSplitWindowInfo(m_szSplitName,nID);
	}
}



//////////////////////////////////////////////////////////////////////////
void XSplitManage::ChangeScale(int nType)
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

	ChangeSignalPng(nScale);

	if(nScale!=m_nScale)
	{
		m_nScale=nScale;
		SaveDataOfScale(int(nType));
		ResetView();
	}
}

void XSplitManage::SaveDataOfScale(int nType)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szTemp=_T("");
	szTemp.Format(_T("%d"),nType);

	CString szKey;
	szKey.Format(_T("%s_%d"),_T("SplitScale"),GetBaseIndex());
	HandleIni::WriteData(_T("Info"),szKey,szTemp,szIniPath);
}

void XSplitManage::ChangeSignalPng(int nScale)
{
	CString szClose=_T("");
	CString szMax=_T("");
	CString szMin=_T("");
	CString szFull=_T("");
	switch(nScale)
	{
		case 200:
			{
				szClose=HandlePath::GetSignalPhoto(_T("close_34.png"));
				szMax=HandlePath::GetSignalPhoto(_T("max_34.png"));
				szMin=HandlePath::GetSignalPhoto(_T("min_34.png"));
				szFull=HandlePath::GetSignalPhoto(_T("full_34.png"));
			}
			break;
		case 175:
			{
				szClose=HandlePath::GetSignalPhoto(_T("close_29.png"));
				szMax=HandlePath::GetSignalPhoto(_T("max_29.png"));
				szMin=HandlePath::GetSignalPhoto(_T("min_29.png"));
				szFull=HandlePath::GetSignalPhoto(_T("full_29.png"));
			}
			break;
		case 150:
			{
				szClose=HandlePath::GetSignalPhoto(_T("close_25.png"));
				szMax=HandlePath::GetSignalPhoto(_T("max_25.png"));
				szMin=HandlePath::GetSignalPhoto(_T("min_25.png"));
				szFull=HandlePath::GetSignalPhoto(_T("full_25.png"));
			}
			break;
		case 125:
			{
				szClose=HandlePath::GetSignalPhoto(_T("close_21.png"));
				szMax=HandlePath::GetSignalPhoto(_T("max_21.png"));
				szMin=HandlePath::GetSignalPhoto(_T("min_21.png"));
				szFull=HandlePath::GetSignalPhoto(_T("full_21.png"));
			}
			break;
		case 100:
			{
				szClose=HandlePath::GetSignalPhoto(_T("close.png"));
				szMax=HandlePath::GetSignalPhoto(_T("max.png"));
				szMin=HandlePath::GetSignalPhoto(_T("min.png"));
				szFull=HandlePath::GetSignalPhoto(_T("full.png"));
			}
			break;
		case 75:
			{
				szClose=HandlePath::GetSignalPhoto(_T("close_12.png"));
				szMax=HandlePath::GetSignalPhoto(_T("max_12.png"));
				szMin=HandlePath::GetSignalPhoto(_T("min_12.png"));
				szFull=HandlePath::GetSignalPhoto(_T("full_12.png"));
			}
			break;
		case 50:
			{
				szClose=HandlePath::GetSignalPhoto(_T("close_8.png"));
				szMax=HandlePath::GetSignalPhoto(_T("max_8.png"));
				szMin=HandlePath::GetSignalPhoto(_T("min_8.png"));
				szFull=HandlePath::GetSignalPhoto(_T("full_8.png"));
			}
			break;
		default:
			break;
	}

	for(auto& pSignal:m_VecSignal)
	{
		pSignal->SetClosePng(szClose);
		pSignal->SetMaxPng(szMax);
		pSignal->SetMinPng(szMin);
		pSignal->SetFullPng(szFull);
	}
}

void XSplitManage::SetAddModel(int nType)
{
	//int nAddModel=0;
	//switch(nType)
	//{
	//	case OPERATETYPE_FULLSCREEN:
	//		{
	//			nAddModel=CMDUITYPE_FULLSCREEN;
	//		}
	//		break;
	//	case OPERATETYPE_ADDDEFAULT:
	//		{
	//			nAddModel=CMDUITYPE_ADDDEFAULT;
	//		}
	//		break;
	//	default:
	//		break;
	//}


	//m_nAddModel=nAddModel;

	//CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	//CString szTemp=_T("");
	//szTemp.Format(_T("%d"),m_nAddModel);

	//CString szKey;
	//szKey.Format(_T("%s_%d"),_T("AddModel"),GetBaseIndex());
	//HandleIni::WriteData(_T("Info"),szKey,szTemp,szIniPath);

}

void XSplitManage::SetLimitModel(int nType)
{
	int nLimitModel=0;
	switch(nType)
	{
		case OPERATETYPE_LIMIT:
			{
				nLimitModel=CMDUITYPE_LIMIT;
			}
			break;
		case OPERATETYPE_DELTOP:
			{
				nLimitModel=CMDUITYPE_DELTOP;
			}
			break;
		case OPERATETYPE_DELBOTTOM:
			{
				nLimitModel=CMDUITYPE_DELBOTTOM;
			}
			break;
		default:
			break;
	}


	m_nLimitModel=nLimitModel;

	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szTemp=_T("");
	szTemp.Format(_T("%d"),m_nLimitModel);

	CString szKey;
	szKey.Format(_T("%s_%d"),_T("LimitModel"),GetBaseIndex());
	HandleIni::WriteData(_T("Info"),szKey,szTemp,szIniPath);

}

void XSplitManage::Operate(OPERATETYPE type,void* pData)
{
	switch(type)
	{
		case OPERATETYPE_SPLITSCALE:
			{

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
				ChangeScale(type);
			}
			break;
		case OPERATETYPE_MENUUP:
			{
				SetSignalUp();
			}
			break;
		case OPERATETYPE_MENUDOWN:
			{
				SetSignalDown();
			}
			break;
		case OPERATETYPE_MENUTOP:
			{
				SetSignalTop();
			}
			break;
		case OPERATETYPE_MENUBOTTOM:
			{
				SetSignalBottom();
			}
			break;
		case OPERATETYPE_CLEARSIGNAL:
			{
				//清空信号
				OperateOfClearSignal();
			}
			break;
		case OPERATETYPE_MENUFULLSCREEN:
			{
				OperateOfFullScreen();
			}
			break;
		case OPERATETYPE_MENUEXTEND:
			{		
				OperateOfExtend();
			}
			break;
		case OPERATETYPE_MENURESTORE:
			{
				OperateOfRestore();
			}
			break;
		case OPERATETYPE_MENUCLOSESIGNAL:
			{
				OperateOfCloseSignal();
			}
			break;
		case OPERATETYPE_LIMIT:
		case OPERATETYPE_DELTOP:
		case OPERATETYPE_DELBOTTOM:
			{
				SetLimitModel(type);
			}
			break;
		//case OPERATETYPE_FULLSCREEN:
		//case OPERATETYPE_ADDDEFAULT:
		//	{
		//		//开创模式
		//		SetAddModel(type);
		//	}
		//	break;
		case OPERATETYPE_QUICKTOP:
			{
				if(!m_bQuickTop)
				{
					m_bQuickTop=TRUE;
				}
				else
				{
					m_bQuickTop=FALSE;
				}				
			}
			break;
		default:
			break;
	}
}

void XSplitManage::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	switch(type)
	{
		case CMDUITYPE_SCALE200:
		case CMDUITYPE_SCALE175:
		case CMDUITYPE_SCALE150:
		case CMDUITYPE_SCALE125:
		case CMDUITYPE_SCALE100:
		case CMDUITYPE_SCALE75:
		case CMDUITYPE_SCALE50:
			{
				CString szPath=HandlePath::GetIniPath(APP_ININAME);

				CString szKey;
				szKey.Format(_T("%s_%d"),_T("SplitScale"),GetBaseIndex());
				int nType=HandleIni::GetInt(_T("Info"),szKey,0,szPath);

				if(nType==type)
					pCmdUI->SetCheck(1);
				else
					pCmdUI->SetCheck(0);
			}
			break;
		case CMDUITYPE_LIMIT:
		case CMDUITYPE_DELTOP:
		case CMDUITYPE_DELBOTTOM:
			{
				CString szPath=HandlePath::GetIniPath(APP_ININAME);

				CString szKey;
				szKey.Format(_T("%s_%d"),_T("LimitModel"),GetBaseIndex());
				int nType=HandleIni::GetInt(_T("Info"),szKey,152,szPath);

				if(nType==type)
					pCmdUI->SetCheck(1);
				else
					pCmdUI->SetCheck(0);
			}
			break;
		case CMDUITYPE_ADDDEFAULT:
		case CMDUITYPE_FULLSCREEN:
			{
				CString szPath=HandlePath::GetIniPath(APP_ININAME);

				CString szKey;
				szKey.Format(_T("%s_%d"),_T("AddModel"),GetBaseIndex());
				int nType=HandleIni::GetInt(_T("Info"),szKey,155,szPath);

				if(nType==type)
					pCmdUI->SetCheck(1);
				else
					pCmdUI->SetCheck(0);
			}
			break;
		case CMDUITYPE_QUICKTOP:
			{
				pCmdUI->SetCheck(m_bQuickTop);
			}
			break;
		default:
			break;
	}
}

void XSplitManage::ControlDataChange(XDATATYPE type,void* pControl)
{

}

void XSplitManage::UpdateControlDataShow(XDATATYPE type,void* pControl)
{

}