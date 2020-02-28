#include "stdafx.h"
#include <algorithm>
#include "XSeatArrageManage.h"
#include "HandleIni.h"
#include "HandlePath.h"
#include "HandleCalculate.h"
#include "XDelegateSeatArrageManage.h"
#include "..\TemplateView.h"
#include "XDrawSeatArrageManage.h"
#include "XLeftWnd.h"
#include "XSeat.h"
#include "XCaculateSeatArrageManage.h"
#include "XConstantData.h"
#include "XMessageBox.h"
#include "XNode.h"
#include "XSeatArrageData.h"
#include "XLeftWnd.h"
#include "XPropertiesWnd.h"
#include "XSeatArrageName.h"
#include "XNodeGroupInfo.h"
#include "XSendDataManage.h"
#include "XPage.h"
#include "XBackGround.h"
#include "XMultiVideoWindow.h"
#include "XTranslationManage.h"
#include "XScreen.h"
#include "XMenuWnd.h"
#include "XSeatMap.h"
#include "XSeatArrage.h"
#include "XSeatDraw.h"
#include "XAlign.h"
#include "XSeatImage.h"
#include "XPropSheet.h"
#include "XScreenArray.h"
#include "XScene.h"


//静态变量
BOOL XSeatArrageManage::m_bFlag=FALSE;
int XSeatArrageManage::m_nPageIndex=0;
CURSORTYPE XSeatArrageManage::m_CursorType=CURSORTYPE_NORMAL;
POSITIONTYPE XSeatArrageManage::m_PositionType=POSITIONTYPE_NULL;
XPage* XSeatArrageManage::m_pPage=NULL;
BOOL XSeatArrageManage::m_bFirstPage=TRUE;
BOOL XSeatArrageManage::m_bCreateDrag=FALSE;
XScreen* XSeatArrageManage::m_pTempScreen=NULL;
XMenuWnd* XSeatArrageManage::m_pMenuWnd=NULL;
XSeatMap* XSeatArrageManage::m_pSeatMap=NULL;
BOOL XSeatArrageManage::m_bMenuFlag=FALSE;
XSeat* XSeatArrageManage::m_pTempSeat=NULL;
XSeatArrage* XSeatArrageManage::m_pSeatArrage=NULL;
XSeatDraw* XSeatArrageManage::m_pSeatDraw=NULL;
BOOL XSeatArrageManage::m_bCreateAlignWnd=FALSE;

XSeatArrageManage::XSeatArrageManage()
{
}

XSeatArrageManage::~XSeatArrageManage()
{
	ClearMapPage();
	ClearVecArrage();
	ClearMapAlign();

	RELEASE(m_pMenuWnd);
	RELEASE(m_pSeatMap);
	RELEASE(m_pSeatArrage);
	RELEASE(m_pSeatDraw);
}

void XSeatArrageManage::ClearMapPage()
{
	for(auto& map:m_MapPage)
		delete map.second;
	m_MapPage.clear();
}

void XSeatArrageManage::ClearVecArrage()
{
	m_VecArrage.clear();
}

void XSeatArrageManage::ClearMapAlign()
{
	for(auto& map:m_MapAlign)
		delete map.second;
	m_MapAlign.clear();
}

void XSeatArrageManage::ClearDragFrame()
{
	if(NULL!=m_pDragFrame)
	{
		m_pMultiVideoWindow->DeleteFrame(m_nPageIndex,m_pDragFrame);
		m_pDragFrame=NULL;
	}
}

void XSeatArrageManage::SetViewColor(Color& color)
{
	m_Color=color;
	//设置预览墙颜色
	m_pDelegate->SetMultiVideoWindowBkColor(m_Color.GetR(),m_Color.GetG(),m_Color.GetB());
}

Color XSeatArrageManage::GetViewColor()
{
	return m_Color;
}

void XSeatArrageManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY)
{
	//XDrawSeatArrageManage::ViewDraw(pDC,rect,noffsetX,noffsetY,this);
}

CSize XSeatArrageManage::ViewGetSize()
{
	return XCaculateSeatArrageManage::ViewGetSize(this);
}

int XSeatArrageManage::GetPageIndex()
{
	return m_nPageIndex;
}

void XSeatArrageManage::ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	//没有登录 不执行
	if(!m_pDelegate->GetLogin())
		return;
	
	POINTF TempPoint;
	XCaculateSeatArrageManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,TempPoint);

	if(m_bFirstPage)
	{
		//在坐席上双击
		XSeat* pSeat=NULL;
		if(XCaculateSeatArrageManage::DecidedPointInSeat(this,m_Point,pSeat))
		{
			if(NULL==pSeat)
				return;
			m_pTempSeat=pSeat;

			int nSeatIndex=pSeat->GetIndex();
			//隐藏菜单按钮
			HideMenuWnd();
			//更改显示页并绘制预览墙
			m_bFirstPage=FALSE;
			//设置当前页面
			m_nPageIndex=m_nSecondPage;
			m_pPage=m_MapPage[m_nPageIndex];
			HideSeatDrawWnd();
			//重置工具栏
			m_pDelegate->ResetRibbonBar();

			CString szGroupName=pSeat->GetGroupName();
			//设置预览墙绘制
			m_pMultiVideoWindow->SetMultiVideoWindowDrawPage(m_bFirstPage);
			//更新文字
			CString szText;
			if(szGroupName==_T(""))
			{
				szText=_C(_T("141"),_T("屏幕编排"));
			}
			else
			{
				szText.Format(_T("%s(%s)-%s"),_C(_T("142"),_T("组")),
							  szGroupName,_C(_T("141"),_T("屏幕编排")));
			}
			m_pMultiVideoWindow->SetText(szText);

			//第二页保存当前组名称
			m_pPage->SetGroupName(szGroupName);
			//获取组信息
			XNodeGroupInfo* pInfo=NULL;
			MAP_NODEGROUP& MapNodeInfo=m_pDelegate->GetMapNodeGroup();
			MAP_NODEGROUP::iterator iterGroup=MapNodeInfo.find(szGroupName);
			if(iterGroup!=MapNodeInfo.end())
			{
				pInfo=iterGroup->second;
			}

			if(NULL!=pInfo)
			{
				//完成屏幕添加
				int nMaster=pInfo->GetMaster();
				int nRow=pInfo->GetMatrixRow();
				int nColumn=pInfo->GetMatrixColumn();

				m_pTempSeat->SetSeatRow(nRow);
				m_pTempSeat->SetSeatColumn(nColumn);
				//计算屏幕个数
				int nTempScreenH=0;
				int nTempScreenV=0;
				if(nColumn>5)
				{
					nTempScreenH=PAGE_WIDTH/nColumn;
					nTempScreenV=nTempScreenH*9/16;
				}
				else
				{
					nTempScreenH=SCREEN_H;
					nTempScreenV=SCREEN_V;
				}

				//根据行列初始化屏幕排列
				m_pPage->InitScreen(nRow,nColumn,nTempScreenH,nTempScreenV);
				m_pTempScreen=NULL;
				//清空预览墙
				m_pMultiVideoWindow->DeleteFrame(m_nPageIndex);

				//按照屏幕行列，计算屏幕在页面位置
				//总区域
				int nInterWidth=nColumn*nTempScreenH;
				int nInterHeight=nRow*nTempScreenV;
				//开始画线点
				int nX=(PAGE_WIDTH-nInterWidth)/2;
				int nY=(PAGE_HEIGHT-nInterHeight)/2;
				//记录屏幕开始偏移
				m_DeviationPoint=POINTF((Gdiplus::REAL)nX,(Gdiplus::REAL)nY);
				//设置预览墙绘制点
				m_pMultiVideoWindow->SetFramesPoint(m_nPageIndex,CPoint(nX,nY));
				//设置预览墙网格行列
				m_pMultiVideoWindow->SetFramesArrage(m_nPageIndex,nRow,nColumn,nTempScreenH,nTempScreenV);

				MAP_NODE& MapNode=m_pDelegate->GetMapNode();
				VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();

				int nIndex=0;
				for(auto& VecInt:VecArrage)
				{
					for(auto& nNodeID:VecInt)
					{
						nIndex++;
						if(nNodeID!=0)
						{
							//获取节点信息
							XNode* pNode=NULL;
							MAP_NODE::iterator iterNode=MapNode.find(nNodeID);
							if(iterNode!=MapNode.end())
							{
								pNode=iterNode->second;
							}
							if(NULL==pNode)
								return;

							XScreen* pScreen=GetScreenByIndex(nIndex);
							if(NULL==pScreen)
								return;

							pScreen->SetHas(TRUE);
							pScreen->SetNodeID(nNodeID);
							//添加预览绘制
							XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(m_nPageIndex,_T(""),pScreen->GetRect(),RECTF(0,0,1920,1088));
							auto iter=m_MapSecondFrame.find(nNodeID);
							if(iter!=m_MapSecondFrame.end())
							{
								iter->second=pFrame;
							}
							else
							{
								m_MapSecondFrame.insert(std::pair<int,XMultiVideoWindowFrame*>(nNodeID,pFrame));
							}

							CString szText;
							if(nMaster==nNodeID)
							{
								pScreen->SetMaster(TRUE);
								szText.Format(_T("%s(%s)"),pNode->GetNodeName(),_C(_T("137"),_T("主")));
							}
							else
							{
								pScreen->SetMaster(FALSE);
								szText=pNode->GetNodeName();
							}

							m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,szText);
							m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,RGB(255,255,255),14);
						}
					}
				}
			}
			else
			{
				//该组坐席为空时，清空原来坐席排列
				VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
				for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
				{
					XScreen* pScreen=*iter;
					pScreen->SetHas(FALSE);
					pScreen->SetNodeID(0);
				}
				m_pTempSeat->SetSeatRow(0);
				m_pTempSeat->SetSeatColumn(0);
				//////////////////////////////////////////////////////////////////////////
				//设置预览墙绘制点
				m_pMultiVideoWindow->SetFramesPoint(m_nPageIndex,CPoint(0,0));
				//设置预览墙网格行列
				m_pMultiVideoWindow->SetFramesArrage(m_nPageIndex,0,0,0,0);
				m_pMultiVideoWindow->DeleteFrame(m_nPageIndex);
			}
		}
	}
	else
	{
		if(m_CursorType==CURSORTYPE_NORMAL)
		{
			m_bFirstPage=TRUE;

			m_nPageIndex=m_nFirstPage;
			m_pPage=m_MapPage[m_nPageIndex];

			//重置工具栏
			m_pDelegate->ResetRibbonBar();

			ShowSeatDrawWnd();

			m_pMultiVideoWindow->SetMultiVideoWindowDrawPage(m_bFirstPage);
			m_pMultiVideoWindow->SetText(_C(_T("97"),_T("坐席")));

			ShowMenuWnd();
			//每次清空防止重复插不进去
			m_MapSecondFrame.clear();
		}
	}
}

XScreen* XSeatArrageManage::GetScreenByIndex(int nIndex)
{
	VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
	for(auto& pScreen:VecScreen)
	{
		if(pScreen->GetSeatIndex()==nIndex)
		{
			return pScreen;
		}
	}
	return NULL;
}

void XSeatArrageManage::ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	//没有登录 不执行
	if(!m_pDelegate->GetLogin())
		return;

	XCaculateSeatArrageManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,m_Point);
	//TRACE(_T("X=%f,Y=%f\n"),m_Point.X,m_Point.Y);

	if(m_bFirstPage)
	{
		HideMenuWnd();
		HideBtn();
		HideAlignWnd();

		if((int)nFlags==9)//按下Ctrl等于9？
		{
			if(m_CursorType==CURSORTYPE_MOVE)
			{
				XSeat* pSeat=NULL;
				if(XCaculateSeatArrageManage::DecidedPointInSeat(this,m_Point,pSeat))
				{
					if(NULL==pSeat)
						return;

					//单击选中缓存
					m_pTempSeat=pSeat;

					BOOL bSel=FALSE;
					if(pSeat->GetSelected())
						bSel=FALSE;
					else
						bSel=TRUE;

					//保存选中Seat
					if(bSel)
					{
						m_VecTempSeat.push_back(pSeat);
					}
					else
					{
						for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end();)
						{
							XSeat* pTemp=*iter;
							if(pTemp==pSeat)
								iter=m_VecTempSeat.erase(iter);
							else
								++iter;
						}
					}
					//选中
					SetSeatSelect(pSeat,bSel);
					//预览墙选中
					MAP_TEMPFRAME::iterator iter=m_MapFrame.find(pSeat->GetIndex());
					if(iter!=m_MapFrame.end())
					{
						XMultiVideoWindowFrame* pFrame=iter->second;
						m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,bSel);
					}

					m_bLBtnDown=TRUE;
					m_BeginPoint=m_Point;
					m_EndPoint=m_Point;
					//区域
					m_rect=pSeat->GetRect();
					//m_DragRect=pSeat->GetRect();

					//按下添加拖拽Frame
					//if(NULL==m_pDragFrame)
					//	AddDragFrame();				
					//if(m_pDragFrame)
					//	m_pMultiVideoWindow->SetFrame(m_nPageIndex,m_pDragFrame,124,175,221,150);
				}
			}
		}
		else
		{
			//鼠标按下
			if(XCaculateSeatArrageManage::DecidedPointInPage(this,m_Point))
			{
				if(m_CursorType==CURSORTYPE_DRAW)
				{
					m_bLBtnDown=TRUE;
					m_BeginPoint=m_Point;
					m_EndPoint=m_Point;

					m_rect=RECTF(m_BeginPoint,SIZEF(m_EndPoint.X-m_BeginPoint.X,m_EndPoint.Y-m_BeginPoint.Y));
				}
				else if(m_CursorType==CURSORTYPE_NORMAL)
				{
					//全部取消选中
					SetVecSeatUnselect();
					m_pMultiVideoWindow->SetVecFrameUnselect(m_nPageIndex);
					//清空选中集合
					m_VecTempSeat.clear();
					//清除坐席缓存
					m_pTempSeat=NULL;
				}
				else
				{
					XSeat* pSeat=NULL;
					if(XCaculateSeatArrageManage::DecidedPointInSeat(this,m_Point,pSeat))
					{
						if(NULL==pSeat)
							return;
						//单击选中缓存
						m_pTempSeat=pSeat;
						//如果坐席没名称，则行列为零
						if(m_pTempSeat->GetGroupName()==_T(""))
						{
							m_pTempSeat->SetSeatRow(0);
							m_pTempSeat->SetSeatColumn(0);
						}
						//保存选中（单选）
						m_VecTempSeat.clear();
						m_VecTempSeat.push_back(pSeat);

						SetVecSeatSelect(pSeat);
						//显示属性
						XPropertiesWnd::GetInstance()->SetNode(NULL);
						XPropertiesWnd::GetInstance()->SetNodeGroup(NULL);
						XPropertiesWnd::GetInstance()->SetSeat(pSeat);
						pSeat->SetPropertiesWnd();

						MAP_TEMPFRAME::iterator iter=m_MapFrame.find(pSeat->GetIndex());
						if(iter!=m_MapFrame.end())
						{
							XMultiVideoWindowFrame* pFrame=iter->second;
							m_pMultiVideoWindow->SetFrameSelect(m_nPageIndex,pFrame);
						}
						//坐席拖动
						//////////////////////////////////////////////////////////////////////////
						m_bLBtnDown=TRUE;
						m_BeginPoint=m_Point;
						m_EndPoint=m_Point;

						m_rect=pSeat->GetRect();
						m_DragRect=pSeat->GetRect();

						//按下添加拖拽Frame
						//if(NULL==m_pDragFrame)
						//	AddDragFrame();
						//if(m_pDragFrame)
						//	m_pMultiVideoWindow->SetFrame(m_nPageIndex,m_pDragFrame,124,175,221,150);

						XConstantData::GetInstance()->SetSeatIndex(pSeat->GetIndex());
					}
				}
			}
		}
	}
	else
	{
		//第二页操作
		POINTF TempP=m_Point;
		TempP.X-=m_DeviationPoint.X;
		TempP.Y-=m_DeviationPoint.Y;

		XScreen* pScreen=NULL;
		if(XCaculateSeatArrageManage::DecidedPointInScreen(this,TempP,pScreen))
		{
			if(NULL==pScreen)
				return;

			m_bLBtnDown=TRUE;
			m_pTempScreen=pScreen;

			if(m_CursorType==CURSORTYPE_MOVE)
			{
				m_BeginPoint=m_Point;
				m_EndPoint=m_Point;

				m_rect=pScreen->GetRect();
				m_DragRect=pScreen->GetRect();

				XConstantData::GetInstance()->SetNodeID(pScreen->GetNodeID());
				//属性（点击）
				//////////////////////////////////////////////////////////////////////////
				int nNodeID=pScreen->GetNodeID();
				XNode* pNode=GetNodeByID(nNodeID);
				if(NULL==pNode)
					return;
				XPropertiesWnd::GetInstance()->SetNode(pNode);
				XPropertiesWnd::GetInstance()->SetNodeGroup(NULL);
				XPropertiesWnd::GetInstance()->SetSeat(NULL);
				pNode->SetPropertiesWnd();
				//////////////////////////////////////////////////////////////////////////
				//点击选中（指定选中，其他非选中）
				SetVecScreenSelect(pScreen);
				auto iter=m_MapSecondFrame.find(nNodeID);
				if(iter!=m_MapSecondFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;
					m_pMultiVideoWindow->SetFrameSelect(m_nPageIndex,pFrame);
				}
			}
		}
	}
}

void XSeatArrageManage::ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	//没有登录 不执行
	if(!m_pDelegate->GetLogin())
	{
		SetCursor(CURSORTYPE_NORMAL);
		return;
	}

	POINTF TempPoint;
	XCaculateSeatArrageManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,TempPoint);

	//TRACE(_T("TempPoint X=%f,Y=%f\n"),TempPoint.X,TempPoint.Y);

	if(m_bFirstPage)
	{
		if(nFlags==9)
		{
			if(m_bLBtnDown)
			{
				//按下Ctrl复制
				MoveSignalOfCopy(m_BeginPoint,TempPoint);
			}
		}
		else
		{
			if(m_bLBtnDown&&MK_LBUTTON)
			{
				if(m_bFlag)
				{
					m_CursorType=CURSORTYPE_DRAW;
					MoveSignalOfNew(m_BeginPoint,TempPoint);
				}
				else if(m_CursorType!=CURSORTYPE_DRAW)
				{
					MoveSignal(m_BeginPoint,TempPoint);
				}
			}
			else
			{
				if(XCaculateSeatArrageManage::DecidedPointInPage(this,TempPoint))
				{
					//判断鼠标是否在坐席上
					XSeat* pSeat=NULL;
					if(XCaculateSeatArrageManage::DecidedPointInSeat(this,TempPoint,pSeat))
					{
						if(NULL==pSeat)
							return;

						m_PositionType=XCaculateSeatArrageManage::DecidePointInSeatPosition(this,pSeat->GetRect(),TempPoint);

						if(m_bFlag)
						{
							m_CursorType=CURSORTYPE_DRAW;
						}
						else
						{
							m_CursorType=XCaculateSeatArrageManage::GetCursorTypeByPositionType(m_PositionType);
						}
					}
					else
					{
						if(m_bFlag)
							m_CursorType=CURSORTYPE_DRAW;
						else
							m_CursorType=CURSORTYPE_NORMAL;
					}
				}
				else
					m_CursorType=CURSORTYPE_NORMAL;

			}
			SetCursor(m_CursorType);
		}
	}
	else
	{
		//第二页操作
		if(m_bLBtnDown&&MK_LBUTTON)
		{
			if(m_CursorType==CURSORTYPE_MOVE)
			{
				MoveSignal(m_BeginPoint,TempPoint);
			}
		}
		else
		{
			if(XCaculateSeatArrageManage::DecidedPointInPage(this,TempPoint))
			{
				m_CursorType=CURSORTYPE_NORMAL;

				POINTF TempP=TempPoint;
				TempP.X-=m_DeviationPoint.X;
				TempP.Y-=m_DeviationPoint.Y;
				//判断鼠标在屏幕上
				XScreen* pScreen=NULL;
				if(XCaculateSeatArrageManage::DecidedPointInScreen(this,TempP,pScreen))
				{
					if(NULL==pScreen)
						return;

					if(pScreen->GetHas())
						m_CursorType=CURSORTYPE_MOVE;
					else
						m_CursorType=CURSORTYPE_NORMAL;
				}
				else
				{
					m_CursorType=CURSORTYPE_NORMAL;
				}
			}
		}
		SetCursor(m_CursorType);
	}
}

void XSeatArrageManage::ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{
	if(!m_pDelegate->GetLogin())
		return;

	POINTF TempPoint;
	XCaculateSeatArrageManage::ReductionPoint(this,rect,noffsetX,noffsetY,point,TempPoint);

	if(m_bFirstPage)
	{
		if(nFlags==8)
		{
			m_bLBtnDown=FALSE;
			if(!m_bCreateDrag)
			{
				//CreateAlignWnd();
				ShowALignWnd();
				return;
			}

			if(m_CursorType==CURSORTYPE_NORMAL)
				return;

			ClearDragFrame();
			m_bCreateDrag=FALSE;

			XPage* pPage=m_pPage;
			RECTF rectPage=pPage->GetRect();
			VEC_SEAT& VecSeat=pPage->GetVecSeat();

			RECTF rectSeat;
			RECTF::Intersect(rectSeat,m_EndRect,rectPage);

			XSeat* pSeat=new XSeat;
			int nSeatIndex=XCaculateSeatArrageManage::GetSeatIndex(this);
			pSeat->SetIndex(nSeatIndex);
			pSeat->SetManage(this);
			pSeat->SetRect(rectSeat);
			pSeat->SetModel(m_pTempSeat->GetModel());
			pSeat->SetColor(m_pTempSeat->GetColorR(),m_pTempSeat->GetColorG(),m_pTempSeat->GetColorB(),m_pTempSeat->GetColorA());
			pSeat->SetPhotoName(m_pTempSeat->GetPhotoName());

			VecSeat.push_back(pSeat);

			//更新菜单按钮
			m_pTempSeat=pSeat;
			ShowMenuWnd();

			//绘制预览墙坐席
			RECTF rectImage(0,0,1920,1088);
			XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(m_nPageIndex,_T(""),rectSeat,rectImage);
			m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,TRUE);
			m_pMultiVideoWindow->SetFrameSelect(m_nPageIndex,pFrame);
			m_pMultiVideoWindow->SetFrameModel(m_nPageIndex,pFrame,pSeat->GetModel());
			m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,pSeat->GetColorR(),pSeat->GetColorG(),pSeat->GetColorB(),pSeat->GetColorA());
			m_pMultiVideoWindow->SetFramePic(m_nPageIndex,pFrame,pSeat->GetPhotoPath());

			//保存缓存Frame
			auto iter=m_MapFrame.find(nSeatIndex);
			if(iter!=m_MapFrame.end())
			{
				iter->second=pFrame;
			}
			else
			{
				m_MapFrame.insert(std::pair<int,XMultiVideoWindowFrame*>(nSeatIndex,pFrame));
			}

			//选中坐席
			SetVecSeatSelect(pSeat);
			//添加到选中集合,保存最后一个
			m_VecTempSeat.clear();
			m_VecTempSeat.push_back(pSeat);
		}
		else
		{
			m_bFlag=FALSE;
			m_bLBtnDown=FALSE;

			XPage* pPage=m_pPage;

			if(m_CursorType==CURSORTYPE_NORMAL)
				return;

			if(!m_bCreateDrag)
			{
				int nIndex=XConstantData::GetInstance()->GetSeatIndex();
				XSeat* pSeat=XCaculateSeatArrageManage::GetSeatByIndex(this,nIndex);
				if(NULL==pSeat)
					return;

				//单击选中缓存
				m_pTempSeat=pSeat;
				ShowMenuWnd();
				return;
			}

			ClearDragFrame();
			m_bCreateDrag=FALSE;

			RECTF rectPage=pPage->GetRect();
			VEC_SEAT& VecSeat=pPage->GetVecSeat();
			if(m_CursorType==CURSORTYPE_DRAW)
			{
				//判断鼠标在页面上
				if(XCaculateSeatArrageManage::DecidedPointInPage(this,TempPoint))
				{
					//新建
					RECTF rectSeat;
					RECTF::Intersect(rectSeat,m_EndRect,rectPage);

					XSeat* pSeat=new XSeat;
					int nSeatIndex=XCaculateSeatArrageManage::GetSeatIndex(this);
					pSeat->SetManage(this);
					pSeat->SetIndex(nSeatIndex);
					pSeat->SetRect(rectSeat);
					VecSeat.push_back(pSeat);

					//绘制预览墙坐席
					RECTF rectImage(0,0,1920,1088);
					XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(m_nPageIndex,_T(""),rectSeat,rectImage);
					m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,TRUE);
					m_pMultiVideoWindow->SetFrameSelect(m_nPageIndex,pFrame);

					//保存缓存Frame
					auto iter=m_MapFrame.find(nSeatIndex);
					if(iter!=m_MapFrame.end())
					{
						iter->second=pFrame;
					}
					else
					{
						m_MapFrame.insert(std::pair<int,XMultiVideoWindowFrame*>(nSeatIndex,pFrame));
					}
					//选中坐席
					SetVecSeatSelect(pSeat);
					//单击选中缓存
					m_pTempSeat=pSeat;
					ShowMenuWnd();
					//添加到选中集合,保存最后一个
					m_VecTempSeat.clear();
					m_VecTempSeat.push_back(pSeat);
				}
			}
			else
			{
				//移动
				RECTF rectSeat;
				RECTF::Intersect(rectSeat,m_DragRect,rectPage);

				int nIndex=XConstantData::GetInstance()->GetSeatIndex();
				XSeat* pSeat=XCaculateSeatArrageManage::GetSeatByIndex(this,nIndex);
				if(NULL==pSeat)
					return;

				if(XCaculateSeatArrageManage::DecidedPointInPage(this,TempPoint))
				{
					pSeat->SetIndex(nIndex);
					pSeat->SetRect(rectSeat);

					//单击选中缓存
					m_pTempSeat=pSeat;
					ShowMenuWnd();

					//更新预览墙
					MAP_TEMPFRAME::iterator iter=m_MapFrame.find(nIndex);
					if(iter!=m_MapFrame.end())
					{
						XMultiVideoWindowFrame* pFrame=iter->second;
						m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,rectSeat);
					}
				}
				else
				{
					//删除
					DeleteSeat(nIndex);
				}
			}
		}
	}
	else
	{
		//第二页
		m_bLBtnDown=FALSE;
		ClearDragFrame();

		if(m_CursorType==CURSORTYPE_NORMAL)
			return;

		if(XCaculateSeatArrageManage::DecidedPointInPage(this,TempPoint))
		{
			POINTF TempP=TempPoint;
			TempP.X-=m_DeviationPoint.X;
			TempP.Y-=m_DeviationPoint.Y;
			//判断鼠标在屏幕上
			XScreen* pScreen=NULL;
			if(XCaculateSeatArrageManage::DecidedPointInScreen(this,TempP,pScreen))
			{
				if(NULL==pScreen)
					return;

				if(pScreen->GetHas())
					return;

				if(NULL==m_pTempScreen)
					return;

				//移动
				pScreen->SetHas(m_pTempScreen->GetHas());
				pScreen->SetNodeID(m_pTempScreen->GetNodeID());
				pScreen->SetMaster(m_pTempScreen->GetMaster());

				//更新预览墙
				MAP_TEMPFRAME::iterator iter=m_MapSecondFrame.find(m_pTempScreen->GetNodeID());
				if(iter!=m_MapSecondFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;
					m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,pScreen->GetRect());
				}

				m_pTempScreen->SetHas(FALSE);
				m_pTempScreen->SetNodeID(0);
				m_pTempScreen->SetMaster(FALSE);

				m_pTempScreen=NULL;
			}
			else
			{
				//双击切换页面会执行Up,如果m_pTempScreen不置空，会随机删除屏幕
				//双击时置空
				//这里删除只是调整屏幕排列，不会移除分组
				if(NULL==m_pTempScreen)
					return;

				MAP_NODE& MapNode=m_pDelegate->GetMapNode();
				VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
				if(VecScreen.size()>1)
				{
					if(m_pTempScreen->GetMaster())
					{
						VEC_SCREEN::iterator iter=VecScreen.begin()+1;
						XScreen* pScreen=*iter;
						pScreen->SetMaster(TRUE);

						MAP_TEMPFRAME::iterator iterMap=m_MapSecondFrame.find(pScreen->GetNodeID());
						if(iterMap!=m_MapSecondFrame.end())
						{
							XMultiVideoWindowFrame* pFrame=iterMap->second;

							MAP_NODE::iterator iterNode=MapNode.find(pScreen->GetNodeID());
							if(iterNode!=MapNode.end())
							{
								XNode* pNode=iterNode->second;

								CString szText;
								szText.Format(_T("%s(%s)"),pNode->GetNodeName(),_C(_T("137"),_T("主")));
								m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,szText);
							}
						}
					}
				}

				//删除
				MAP_TEMPFRAME::iterator iter=m_MapSecondFrame.find(m_pTempScreen->GetNodeID());
				if(iter!=m_MapSecondFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;

					m_MapSecondFrame.erase(iter);
					m_pMultiVideoWindow->DeleteFrame(m_nPageIndex,pFrame);
				}

				m_pTempScreen->SetHas(FALSE);
				m_pTempScreen->SetMaster(FALSE);
				m_pTempScreen->SetNodeID(0);

				m_pTempScreen=NULL;
			}
		}
	}
}

void XSeatArrageManage::DeleteSeat(int nIndex)
{
	VEC_SEAT& VecSeat=m_pPage->GetVecSeat();
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();)
	{
		XSeat* pTemp=*iter;
		if(pTemp->GetIndex()==nIndex)
		{
			iter=VecSeat.erase(iter);
			delete pTemp;
		}
		else
			++iter;
	}

	MAP_TEMPFRAME::iterator iter=m_MapFrame.find(nIndex);
	if(iter!=m_MapFrame.end())
	{
		XMultiVideoWindowFrame* pFrame=iter->second;

		m_MapFrame.erase(iter);
		m_pMultiVideoWindow->DeleteFrame(m_nPageIndex,pFrame);
	}
}

void XSeatArrageManage::SetVecSeatSelect(XSeat* p)
{
	VEC_SEAT& VecSeat=m_pPage->GetVecSeat();
	for(auto& pTemp:VecSeat)
	{
		if(pTemp==p)
			pTemp->SetSelected(TRUE);
		else
			pTemp->SetSelected(FALSE);
	}
}

void XSeatArrageManage::SetSeatSelect(XSeat* p,BOOL b)
{
	VEC_SEAT& VecSeat=m_pPage->GetVecSeat();
	for(auto& pTemp:VecSeat)
	{
		if(pTemp==p)
			pTemp->SetSelected(b);
	}
}

void XSeatArrageManage::Unselected()
{
	SetVecSeatUnselect();
	if(NULL!=m_pMultiVideoWindow)
		m_pMultiVideoWindow->SetVecFrameUnselect(m_nPageIndex);
}

void XSeatArrageManage::SetVecSeatUnselect()
{
	VEC_SEAT& VecSeat=m_pPage->GetVecSeat();
	for(auto& pTemp:VecSeat)
	{
		pTemp->SetSelected(FALSE);
	}
}

void XSeatArrageManage::SetVecScreenSelect(XScreen* p)
{
	VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
	for(auto& pTemp:VecScreen)
	{
		if(pTemp==p)
			pTemp->SetSelected(TRUE);
		else
			pTemp->SetSelected(FALSE);
	}
}

void XSeatArrageManage::SetVecScreenUnselect()
{
	VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
	for(auto& pTemp:VecScreen)
	{
		pTemp->SetSelected(FALSE);
	}
}

void XSeatArrageManage::SetScreenSelect(XScreen* p,BOOL b)
{
	VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
	for(auto& pTemp:VecScreen)
	{
		if(pTemp==p)
			pTemp->SetSelected(b);
	}
}

void XSeatArrageManage::ViewMouseLeave()
{

}

void XSeatArrageManage::ViewKeyUp(UINT nChar)
{
	if(!m_pDelegate->GetLogin())
		return;

	switch(nChar)
	{
		case VK_ESCAPE:
			{
				//Esc
				if(m_bFirstPage)
				{
					HideMenuWnd();
					HideBtn();
					Unselected();
				}
				else
				{
					m_bFirstPage=TRUE;
					m_nPageIndex=m_nFirstPage;
					m_pPage=m_MapPage[m_nPageIndex];

					//重置工具栏
					m_pDelegate->ResetRibbonBar();

					ShowSeatDrawWnd();
					ShowMenuWnd();

					m_pMultiVideoWindow->SetMultiVideoWindowDrawPage(m_bFirstPage);
					m_pMultiVideoWindow->SetText(_C(_T("97"),_T("坐席")));
				}
			}
			break;
		case VK_DELETE:
			{
				//Del
				if(m_bFirstPage)
				{
					for(auto& pTemp:m_VecTempSeat)
					{
						int nIndex=pTemp->GetIndex();
						DeleteSeat(nIndex);
					}

					HideMenuWnd();
					//HideBtn();
					//////////////////////////////////////////////////////////////////////////
					m_VecTempSeat.clear();
				}
			}
			break;
		case VK_TAB:
			{
				//Tab
				VEC_SEAT& VecSeat=m_pPage->GetVecSeat();
				int nSize=VecSeat.size();
				if(nSize<=1)
					return;

				HideMenuWnd();
				HideBtn();

				if(m_VecTempSeat.size()==1)
				{
					int nIndex=GetVecSeatIndex(VecSeat);
					if(nIndex<nSize-1)
					{
						m_pTempSeat=VecSeat[nIndex+1];
					}
					else if(nIndex==nSize-1)
					{
						m_pTempSeat=VecSeat[0];
					}
				}
				else if(m_VecTempSeat.size()!=1)
				{
					m_pTempSeat=VecSeat[0];
				}

				m_VecTempSeat.clear();
				m_VecTempSeat.push_back(m_pTempSeat);
				SetVecSeatSelect(m_pTempSeat);
				ShowMenuWnd();

				MAP_TEMPFRAME::iterator iter=m_MapFrame.find(m_pTempSeat->GetIndex());
				if(iter!=m_MapFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;
					m_pMultiVideoWindow->SetFrameSelect(m_nPageIndex,pFrame);
				}
			}
			break;
		case VK_F1:
			{
				//Enter
				if(NULL==m_pTempSeat)
					return;

				if(m_bFirstPage)
				{
					//在坐席上双击
					XSeat* pSeat=m_pTempSeat;
					int nSeatIndex=pSeat->GetIndex();
					//隐藏菜单按钮
					HideMenuWnd();

					//更改显示页并绘制预览墙
					m_bFirstPage=FALSE;
					//设置当前页面
					m_nPageIndex=m_nSecondPage;
					m_pPage=m_MapPage[m_nPageIndex];
					//重置工具栏
					m_pDelegate->ResetRibbonBar();

					HideSeatDrawWnd();

					CString szGroupName=pSeat->GetGroupName();
					//设置预览墙绘制
					m_pMultiVideoWindow->SetMultiVideoWindowDrawPage(m_bFirstPage);
					//更新文字
					CString szText;
					if(szGroupName==_T(""))
					{
						szText=_C(_T("141"),_T("屏幕编排"));
					}
					else
					{
						szText.Format(_T("%s(%s)-%s"),_C(_T("142"),_T("组")),
									  szGroupName,_C(_T("141"),_T("屏幕编排")));
					}
					m_pMultiVideoWindow->SetText(szText);

					//第二页保存当前组名称
					m_pPage->SetGroupName(szGroupName);
					//获取组信息
					XNodeGroupInfo* pInfo=NULL;
					MAP_NODEGROUP& MapNodeInfo=m_pDelegate->GetMapNodeGroup();
					MAP_NODEGROUP::iterator iterGroup=MapNodeInfo.find(szGroupName);
					if(iterGroup!=MapNodeInfo.end())
					{
						pInfo=iterGroup->second;
					}

					if(NULL!=pInfo)
					{
						//完成屏幕添加
						int nMaster=pInfo->GetMaster();
						int nRow=pInfo->GetMatrixRow();
						int nColumn=pInfo->GetMatrixColumn();

						m_pTempSeat->SetSeatRow(nRow);
						m_pTempSeat->SetSeatColumn(nColumn);

						//计算屏幕个数
						int nTempScreenH=0;
						int nTempScreenV=0;
						if(nColumn>5)
						{
							nTempScreenH=PAGE_WIDTH/nColumn;
							nTempScreenV=nTempScreenH*9/16;
						}
						else
						{
							nTempScreenH=SCREEN_H;
							nTempScreenV=SCREEN_V;
						}

						//根据行列初始化屏幕排列
						m_pPage->InitScreen(nRow,nColumn,nTempScreenH,nTempScreenV);
						m_pTempScreen=NULL;
						//清空预览墙
						m_pMultiVideoWindow->DeleteFrame(m_nPageIndex);

						//按照屏幕行列，计算屏幕在页面位置
						//总区域
						int nInterWidth=nColumn*nTempScreenH;
						int nInterHeight=nRow*nTempScreenV;
						//开始画线点
						int nX=(PAGE_WIDTH-nInterWidth)/2;
						int nY=(PAGE_HEIGHT-nInterHeight)/2;
						//记录屏幕开始偏移
						m_DeviationPoint=POINTF((Gdiplus::REAL)nX,(Gdiplus::REAL)nY);
						//设置预览墙绘制点
						m_pMultiVideoWindow->SetFramesPoint(m_nPageIndex,CPoint(nX,nY));
						//设置预览墙网格行列
						m_pMultiVideoWindow->SetFramesArrage(m_nPageIndex,nRow,nColumn,nTempScreenH,nTempScreenV);

						MAP_NODE& MapNode=m_pDelegate->GetMapNode();
						VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();

						//每次清空防止重复插不进去
						//m_MapSecondFrame.clear();

						int nIndex=0;
						for(auto iter=VecArrage.begin();iter!=VecArrage.end();++iter)
						{
							std::vector<int> VecInt=*iter;
							for(auto iter=VecInt.begin();iter!=VecInt.end();++iter)
							{
								int nNodeID=*iter;
								nIndex++;

								if(nNodeID!=0)
								{
									//获取节点信息
									XNode* pNode=NULL;
									MAP_NODE::iterator iterNode=MapNode.find(nNodeID);
									if(iterNode!=MapNode.end())
									{
										pNode=iterNode->second;
									}
									if(NULL==pNode)
										return;

									XScreen* pScreen=GetScreenByIndex(nIndex);
									if(NULL==pScreen)
										return;

									pScreen->SetHas(TRUE);
									pScreen->SetNodeID(nNodeID);
									//添加预览绘制
									XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(m_nPageIndex,_T(""),pScreen->GetRect(),RECTF(0,0,1920,1088));
									auto iter=m_MapSecondFrame.find(nNodeID);
									if(iter!=m_MapSecondFrame.end())
									{
										iter->second=pFrame;
									}
									else
									{
										m_MapSecondFrame.insert(std::pair<int,XMultiVideoWindowFrame*>(nNodeID,pFrame));
									}

									CString szText;
									if(nMaster==nNodeID)
									{
										pScreen->SetMaster(TRUE);
										szText.Format(_T("%s(%s)"),pNode->GetNodeName(),_C(_T("137"),_T("主")));
									}
									else
									{
										pScreen->SetMaster(FALSE);
										szText=pNode->GetNodeName();
									}

									m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,szText);
									m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,RGB(255,255,255),14);
								}
							}
						}
					}
					else
					{
						//该组坐席为空时，清空原来坐席排列
						VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
						for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
						{
							XScreen* pScreen=*iter;
							pScreen->SetHas(FALSE);
							pScreen->SetNodeID(0);
						}
						//////////////////////////////////////////////////////////////////////////
						m_pTempSeat->SetSeatRow(0);
						m_pTempSeat->SetSeatColumn(0);
						//设置预览墙绘制点
						m_pMultiVideoWindow->SetFramesPoint(m_nPageIndex,CPoint(0,0));
						//设置预览墙网格行列
						m_pMultiVideoWindow->SetFramesArrage(m_nPageIndex,0,0,0,0);
						m_pMultiVideoWindow->DeleteFrame(m_nPageIndex);
					}
				}
			}
			break;
		default:
			break;
	}
}

int XSeatArrageManage::GetVecSeatIndex(VEC_SEAT& VecSeat)
{
	int nIndex=0;
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pSeat=*iter;
		if(pSeat==m_pTempSeat)
			return nIndex;
		nIndex++;
	}

	return 0;
}

void XSeatArrageManage::ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)
{

}

void XSeatArrageManage::MoveSignalOfNew(POINTF& point1,POINTF& point2)
{
	if((abs((int)point2.X-(int)point1.X)<=1)&&(abs((int)point2.Y-(int)point1.Y)<=1))
		return;
	//TRACE(_T("MoveSignalOfNew\n"));

	HideMenuWnd();

	RECTF tempRect=m_rect;
	if(m_CursorType==CURSORTYPE_DRAW)
	{
		if(NULL==m_pDragFrame)
		{
			AddDragFrame();
			m_bCreateDrag=TRUE;
		}
	}

	SIZEF size;
	size.Width=point2.X-point1.X;
	size.Height=point2.Y-point1.Y;
	XCaculateSeatArrageManage::MoveSignalOfNew(tempRect,size);

	m_EndRect=tempRect;
	if(NULL!=m_pDragFrame)
		m_pMultiVideoWindow->SetFrame(m_nPageIndex,m_pDragFrame,m_EndRect);
}

void XSeatArrageManage::AddDragFrame()
{
	RECTF rect(0,0,1920,1088);
	//rtsp地址（目前为空）
	CString szRTSPAddr=_T("");
	//页面序号位
	m_pDragFrame=m_pMultiVideoWindow->AddFrame(m_nPageIndex,szRTSPAddr,m_rect,rect);
}

void XSeatArrageManage::MoveSignal(POINTF& point1,POINTF& point2)
{
	//只是点击才会返回
	if((abs((int)point2.X-(int)point1.X)<=1)&&(abs((int)point2.Y-(int)point1.Y)<=1))
		return;

	HideMenuWnd();

	RECTF tempRect=m_rect;
	//移动再添加拖拽Frame
	if(NULL==m_pDragFrame)
	{
		AddDragFrame();
		m_bCreateDrag=TRUE;
	}
	m_pMultiVideoWindow->SetFrame(m_nPageIndex,m_pDragFrame,124,175,221,200);

	SIZEF size;
	size.Width=point2.X-point1.X;
	size.Height=point2.Y-point1.Y;

	XCaculateSeatArrageManage::MoveSignal(m_PositionType,tempRect,size);

	m_DragRect=tempRect;
	if(NULL!=m_pDragFrame)
		m_pMultiVideoWindow->SetFrame(m_nPageIndex,m_pDragFrame,m_DragRect);

	//移动时更新属性
	CMFCPropertyGridProperty* pX=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATRECTX);
	if(NULL!=pX)
		pX->SetValue(_variant_t((int)m_DragRect.X));

	CMFCPropertyGridProperty* pY=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATRECTY);
	if(NULL!=pY)
		pY->SetValue(_variant_t((int)m_DragRect.Y));

	CMFCPropertyGridProperty* pW=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATRECTW);
	if(NULL!=pW)
		pW->SetValue(_variant_t((int)m_DragRect.Width));

	CMFCPropertyGridProperty* pH=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATRECTH);
	if(NULL!=pH)
		pH->SetValue(_variant_t((int)m_DragRect.Height));
}

void XSeatArrageManage::MoveSignalOfCopy(POINTF& point1,POINTF& point2)
{
	if((abs((int)point2.X-(int)point1.X)<=1)&&(abs((int)point2.Y-(int)point1.Y)<=1))
		return;
	//TRACE(_T("MoveSignalOfCopy\n"));

	HideMenuWnd();

	RECTF tempRect=m_rect;
	//移动再添加拖拽Frame
	if(NULL==m_pDragFrame)
	{
		AddDragFrame();
		m_bCreateDrag=TRUE;
	}

	m_pMultiVideoWindow->SetFrame(m_nPageIndex,m_pDragFrame,124,175,221,200);

	SIZEF size;
	size.Width=point2.X-point1.X;
	size.Height=point2.Y-point1.Y;

	XCaculateSeatArrageManage::MoveSignal(m_PositionType,tempRect,size);

	m_EndRect=tempRect;
	if(NULL!=m_pDragFrame)
		m_pMultiVideoWindow->SetFrame(m_nPageIndex,m_pDragFrame,m_EndRect);
}

BOOL XSeatArrageManage::ViewMouseWheel(short zDelta)
{
	HideMenuWnd();
	HideBtn();
	HideAlignWnd();
	SetVecSeatUnselect();
	m_pMultiVideoWindow->SetVecFrameUnselect(m_nPageIndex);
	//////////////////////////////////////////////////////////////////////////
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
		//移动绘制按钮
		MoveSeatDrawWnd();

		//设置预览墙放缩
		float fScale=m_nScale/100.0f;
		m_pDelegate->SetMultiVideoWindowScale(fScale);
	}
	return TRUE;
}

void XSeatArrageManage::SetCursor(CURSORTYPE type)
{
	::SetCursor(GetCursor(type));
}

HCURSOR XSeatArrageManage::GetCursor(CURSORTYPE type)
{
	return XCaculateSeatArrageManage::GetCursor(type);
}

void XSeatArrageManage::Init()
{
	InitData();
	//////////////////////////////////////////////////////////////////////////
	//添加Page
	RECTF rect(0,0,(Gdiplus::REAL)PAGE_WIDTH,(Gdiplus::REAL)PAGE_HEIGHT);

	XPage* pPage1=new XPage;
	pPage1->SetPageWidth(PAGE_WIDTH);
	pPage1->SetPageHeight(PAGE_HEIGHT);
	pPage1->SetRect(rect);
	pPage1->SetIndex(m_nFirstPage);
	pPage1->SetManage(this);
	m_MapPage.insert(std::pair<int,XPage*>(m_nFirstPage,pPage1));

	XPage* pPage2=new XPage;
	pPage2->SetPageWidth(PAGE_WIDTH);
	pPage2->SetPageHeight(PAGE_HEIGHT);
	pPage2->SetRect(rect);
	pPage2->SetIndex(m_nSecondPage);
	m_MapPage.insert(std::pair<int,XPage*>(m_nSecondPage,pPage2));

	//初始化为第一页
	m_nPageIndex=m_nFirstPage;
	m_pPage=m_MapPage[m_nPageIndex];
}

void XSeatArrageManage::SaveData(CArchive& arch)
{
	XSeatArrageData::GetInstance()->SaveData(this,arch);
}

void XSeatArrageManage::GetData(CArchive& arch)
{
	XSeatArrageData::GetInstance()->GetData(this,arch);
}

void XSeatArrageManage::ResetData()
{
	//InitVecSeat();
	COLORREF color(RGB(166,202,240));
	for(auto iter=m_MapPage.begin();iter!=m_MapPage.end();++iter)
	{
		XPage* pPage=iter->second;
		pPage->SetModel(TRUE);
		pPage->SetColor(GetRValue(color),GetGValue(color),GetBValue(color));
		pPage->SetPhotoName(_T(""));
	}
}

void XSeatArrageManage::ReloadInterface()
{

}

CString XSeatArrageManage::GetTitle()
{
	return m_szTitle;
}

void XSeatArrageManage::SetTitle(CString szTitle)
{
	m_szTitle=szTitle;
}

void XSeatArrageManage::InitData()
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);
	int nType=HandleIni::GetInt(_T("Info"),_T("SeatArrageScale"),0,szPath);
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
				HandleIni::WriteData(_T("Info"),_T("SeatArrageScale"),szTemp,szPath);
			}
			break;
	}
	//设置预览墙放缩
	float fScale=m_nScale/100.0f;
	m_pDelegate->SetMultiVideoWindowScale(fScale);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XSeatArrageManage::AdjustMultiVideoWindowSize()
{
	CRect rect;
	GetClientRect(GetView()->GetSafeHwnd(),&rect);
	m_pDelegate->AdjustMultiVideoWindowSize(rect.Width(),rect.Height());
}

void XSeatArrageManage::DragGroupToSeat(CString szGroupName,CPoint& point)
{
	CView* pView=m_pDelegate->GetView();
	pView->ScreenToClient(&point);

	CRect rectView;
	pView->GetClientRect(&rectView);

	POINTF TempPoint;
	XCaculateSeatArrageManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),point,TempPoint);

	XSeat* pSeat=NULL;
	if(XCaculateSeatArrageManage::DecidedPointInSeat(this,TempPoint,pSeat))
	{
		if(NULL==pSeat)
			return;

		XNodeGroupInfo* pInfo=NULL;
		MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
		auto iterMap=MapNodeGroup.find(szGroupName);
		if(iterMap!=MapNodeGroup.end())
		{
			pInfo=iterMap->second;
		}

		if(NULL==pInfo)
			return;

		//坐席保存组名
		//pSeat->SetSeatShowName(szGroupName);
		pSeat->SetGroupName(szGroupName);
		pSeat->SetSeatRow(pInfo->GetMatrixRow());
		pSeat->SetSeatColumn(pInfo->GetMatrixColumn());
		//更新属性
		CMFCPropertyGridProperty* pRow=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATROW);
		if(NULL!=pRow)
			pRow->SetValue(_variant_t(pInfo->GetMatrixRow()));

		CMFCPropertyGridProperty* pColumn=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATCOLUMN);
		if(NULL!=pColumn)
			pColumn->SetValue(_variant_t(pInfo->GetMatrixColumn()));

		//设置预览墙显示组名称
		int nIndex=pSeat->GetIndex();
		auto iter=m_MapFrame.find(nIndex);
		if(iter!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iter->second;
			m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,szGroupName);
		}
	}
}

void XSeatArrageManage::DragEnd(CPoint& point,CRect& rect)
{
	UNUSED(rect);

	//拖拽节点
	CView* pView=m_pDelegate->GetView();
	pView->ScreenToClient(&point);

	CRect rectView;
	pView->GetClientRect(&rectView);

	POINTF TempPoint;
	XCaculateSeatArrageManage::ReductionPoint(this,rectView,pView->GetScrollPos(SB_HORZ),pView->GetScrollPos(SB_VERT),point,TempPoint);

	POINTF TempP=TempPoint;
	TempP.X-=m_DeviationPoint.X;
	TempP.Y-=m_DeviationPoint.Y;

	XScreen* pScreen=NULL;
	if(XCaculateSeatArrageManage::DecidedPointInScreen(this,TempP,pScreen))
	{
		if(NULL==pScreen)
			return;

		if(pScreen->GetHas())
			return;

		int nNodeID=XConstantData::GetInstance()->GetNodeID();
		CString szNodeName=XConstantData::GetInstance()->GetNodeName();
		//判断拖拽信号是否已经存在
		XScreen* pTemp=NULL;
		if(XCaculateSeatArrageManage::DecidedNodeInScreen(this,nNodeID,pTemp))
		{
			if(NULL==pTemp)
				return;

			pScreen->SetHas(TRUE);
			pScreen->SetMaster(pTemp->GetMaster());
			pScreen->SetNodeID(pTemp->GetNodeID());

			//更新预览墙
			auto iter=m_MapSecondFrame.find(nNodeID);
			if(iter!=m_MapSecondFrame.end())
			{
				XMultiVideoWindowFrame* pFrame=iter->second;
				m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,pScreen->GetRect());
			}

			pTemp->SetHas(FALSE);
			pTemp->SetMaster(0);
			pTemp->SetNodeID(0);
		}
		else
		{
			//判断是否为第一个
			if(XCaculateSeatArrageManage::DecidedFirstOne(this))
				pScreen->SetMaster(nNodeID);
			else
				pScreen->SetMaster(0);

			pScreen->SetHas(TRUE);
			pScreen->SetNodeID(nNodeID);

			XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(m_nPageIndex,_T(""),pScreen->GetRect(),RECTF(0,0,1920,1088));
			auto iter=m_MapSecondFrame.find(nNodeID);
			if(iter!=m_MapSecondFrame.end())
			{
				iter->second=pFrame;
			}
			else
			{
				m_MapSecondFrame.insert(std::pair<int,XMultiVideoWindowFrame*>(nNodeID,pFrame));
			}

			CString szText;
			if(pScreen->GetMaster()!=0)
				szText.Format(_T("%s(%s)"),szNodeName,_C(_T("137"),_T("主")));
			else
				szText=szNodeName;

			m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,szText);
			m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,RGB(255,255,255),14);
		}
	}
}

void XSeatArrageManage::SwitchPage(int nPage)
{
	if(nPage==1)
	{
		m_bFirstPage=TRUE;

		m_nPageIndex=m_nFirstPage;
		m_pPage=m_MapPage[m_nPageIndex];

		m_pMultiVideoWindow->SetMultiVideoWindowDrawPage(m_bFirstPage);
		m_pMultiVideoWindow->SetText(_C(_T("97"),_T("坐席")));
	}
	else if(nPage==2)
	{
		m_bFirstPage=FALSE;

		m_nPageIndex=m_nSecondPage;
		m_pPage=m_MapPage[m_nPageIndex];

		m_pMultiVideoWindow->SetMultiVideoWindowDrawPage(m_bFirstPage);
	}
}

void XSeatArrageManage::HidePopMenuBtn()
{
	HideMenuWnd();
	HideBtn();
	HideAlignWnd();
	HideSeatDrawWnd();
}

void XSeatArrageManage::ShowPopMenuBtn()
{
	ShowMenuWnd();
	ShowSeatDrawWnd();
}

void XSeatArrageManage::SetGroupNameByAddGroupIn(CString szGroupName)
{
	//添加输入组
	//首先把坐席缓存清空
	m_pTempSeat=NULL;

	//更新文字
	CString szText;
	if(szGroupName==_T(""))
	{
		szText=_C(_T("143"),_T("输入编排"));
	}
	else
	{
		szText.Format(_T("%s(%s)-%s"),_C(_T("142"),_T("组")),
					  szGroupName,_C(_T("143"),_T("输入编排")));
	}
	m_pMultiVideoWindow->SetText(szText);

	if(_T("")==szGroupName)
		return;

	m_pPage->SetGroupName(szGroupName);
}

void XSeatArrageManage::DrawGroupInScreen(CString szGroupName)
{
	//输入
	m_pTempSeat=NULL;

	//更新文字
	CString szText;
	if(szGroupName==_T(""))
	{
		szText=_C(_T("143"),_T("输入编排"));
	}
	else
	{
		szText.Format(_T("%s(%s)-%s"),_C(_T("142"),_T("组")),
					  szGroupName,_C(_T("143"),_T("输入编排")));
	}
	m_pMultiVideoWindow->SetText(szText);

	if(_T("")==szGroupName)
		return;

	m_pPage->SetGroupName(szGroupName);

	XNodeGroupInfo* pInfo=GetNodeGroupInfoByName(szGroupName);
	if(!pInfo)
		return;

	int nMaster=pInfo->GetMaster();
	int nRow=pInfo->GetMatrixRow();
	int nColumn=pInfo->GetMatrixColumn();
	VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();

	//更新工具栏
	m_nSeatRow=nRow;
	m_nSeatColumn=nColumn;

	//计算屏幕大小
	int nTempScreenH=0;
	int nTempScreenV=0;
	if(nColumn>5)
	{
		nTempScreenH=PAGE_WIDTH/nColumn;
		nTempScreenV=nTempScreenH*9/16;
	}
	else
	{
		nTempScreenH=SCREEN_H;
		nTempScreenV=SCREEN_V;
	}

	//根据行列初始化屏幕排列
	m_pPage->InitScreen(nRow,nColumn,nTempScreenH,nTempScreenV);
	m_pTempScreen=NULL;
	m_pMultiVideoWindow->DeleteFrame(m_nPageIndex);

	//按照屏幕行列，计算屏幕在页面位置
	//总区域
	int nInterWidth=nColumn*nTempScreenH;
	int nInterHeight=nRow*nTempScreenV;
	//开始画线点
	int nX=(PAGE_WIDTH-nInterWidth)/2;
	int nY=(PAGE_HEIGHT-nInterHeight)/2;
	//记录屏幕开始偏移
	m_DeviationPoint=POINTF((Gdiplus::REAL)nX,(Gdiplus::REAL)nY);
	//设置预览墙绘制点
	m_pMultiVideoWindow->SetFramesPoint(m_nPageIndex,CPoint(nX,nY));
	//设置预览墙网格行列
	m_pMultiVideoWindow->SetFramesArrage(m_nPageIndex,nRow,nColumn,nTempScreenH,nTempScreenV);

	//绘制节点
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	int nIndex=0;
	for(auto iter=VecArrage.begin();iter!=VecArrage.end();++iter)
	{
		std::vector<int> VecInt=*iter;
		for(auto iter=VecInt.begin();iter!=VecInt.end();++iter)
		{
			int nNodeID=*iter;
			nIndex++;

			if(nNodeID!=0)
			{
				//获取节点信息
				XNode* pNode=NULL;
				MAP_NODE::iterator iterNode=MapNode.find(nNodeID);
				if(iterNode!=MapNode.end())
					pNode=iterNode->second;

				if(NULL==pNode)
					return;

				XScreen* pScreen=GetScreenByIndex(nIndex);
				if(NULL==pScreen)
					return;

				pScreen->SetHas(TRUE);
				pScreen->SetNodeID(nNodeID);
				//添加预览绘制
				XMultiVideoWindowFrame* pFrame=m_pMultiVideoWindow->AddFrame(m_nPageIndex,_T(""),pScreen->GetRect(),RECTF(0,0,1920,1088));
				auto iter=m_MapSecondFrame.find(nNodeID);
				if(iter!=m_MapSecondFrame.end())
				{
					iter->second=pFrame;
				}
				else
				{
					m_MapSecondFrame.insert(std::pair<int,XMultiVideoWindowFrame*>(nNodeID,pFrame));
				}

				CString szText;
				if(nMaster==nNodeID)
				{
					pScreen->SetMaster(TRUE);
					szText.Format(_T("%s(%s)"),pNode->GetNodeName(),_C(_T("137"),_T("主")));
				}
				else
				{
					pScreen->SetMaster(FALSE);
					szText=pNode->GetNodeName();
				}

				m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,szText);
				m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,RGB(255,255,255),14);
			}
		}
	}
}

void XSeatArrageManage::SetSeatSelected(CString szGroupName)
{
	if(!m_bFirstPage)
		return;

	if(_T("")==szGroupName)
		return;

	//首先全部不选中
	m_VecTempSeat.clear();
	SetVecSeatUnselect();
	m_pMultiVideoWindow->SetVecFrameUnselect(m_nPageIndex);

	VEC_SEAT& VecSeat=m_pPage->GetVecSeat();
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pSeat=*iter;
		if(pSeat->GetGroupName()==szGroupName)
		{
			//保存选中Seat
			m_VecTempSeat.push_back(pSeat);
			//选中
			SetSeatSelect(pSeat,TRUE);
			//预览墙选中
			MAP_TEMPFRAME::iterator iter=m_MapFrame.find(pSeat->GetIndex());
			if(iter!=m_MapFrame.end())
			{
				XMultiVideoWindowFrame* pFrame=iter->second;
				m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,TRUE);
			}
		}
	}
}

XNodeGroupInfo* XSeatArrageManage::GetNodeGroupInfoByName(CString szGroupName)
{
	MAP_NODEGROUP& MapGroup=m_pDelegate->GetMapNodeGroup();
	MAP_GROUPMAINSEC& MapGroupMain=m_pDelegate->GetMapNodeGroupMainSec();

	XNodeGroupInfo* pInfo=NULL;
	auto iter=MapGroup.find(szGroupName);
	if(iter!=MapGroup.end())
		pInfo=iter->second;

	auto iter1=MapGroupMain.find(szGroupName);
	if(iter1!=MapGroupMain.end())
		pInfo=iter1->second;

	return pInfo;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
MAP_PAGE& XSeatArrageManage::GetMapPage()
{
	return m_MapPage;
}

MAP_TEMPFRAME& XSeatArrageManage::GetMapTempFrame()
{
	return m_MapFrame;
}

MAP_NODE& XSeatArrageManage::GetMapNode()
{
	return m_pDelegate->GetMapNode();
}

MAP_NODEGROUP& XSeatArrageManage::GetMapNodeGroup()
{
	return m_pDelegate->GetMapNodeGroup();
}

XPage* XSeatArrageManage::GetCurPage()
{
	return m_pPage;
}

void XSeatArrageManage::ResetView()
{
	ResetViewSize();
	InvalidateView();
}

void XSeatArrageManage::InvalidateView()
{
	//CTemplateView* pView=m_pDelegate->GetView();
	//if(NULL!=pView)
	//{
	//	pView->Invalidate(TRUE);
	//}
}

void XSeatArrageManage::ResetViewSize()
{
	CTemplateView* pView=m_pDelegate->GetView();
	if(NULL!=pView)
	{
		pView->ResetSize();
	}
}

void XSeatArrageManage::SaveDataOfScale(int nType)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szTemp=_T("");
	szTemp.Format(_T("%d"),nType);

	HandleIni::WriteData(_T("Info"),_T("SeatArrageScale"),szTemp,szIniPath);
}

float XSeatArrageManage::GetScale()
{
	return m_nScale/100.0f;
}

CWnd* XSeatArrageManage::GetCWND()
{
	return m_pDelegate->GetCWND();
}

int XSeatArrageManage::GetCurUserID()
{
	return m_pDelegate->GetCurUserID();
}

void XSeatArrageManage::ResetLeftWnd()
{
	XLeftWnd::GetInstance()->InitTreeListItemOfNode();
}

//重置场景面板
void XSeatArrageManage::ResetSceneWnd()
{
	//接管预案
	XScene::GetInstance()->InitSceneOfTakeOver();
}

void XSeatArrageManage::ClearProperityWnd()
{
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();
}
//////////////////////////////////////////////////////////////////////////
void XSeatArrageManage::ShowMenu()
{
	if(!m_bMenuFlag)
		ShowBtn();
	else
		HideBtn();
}

void XSeatArrageManage::ShowBtn()
{
	if(NULL!=m_pTempSeat)
	{
		ShowPopBtn();
		m_bMenuFlag=TRUE;
	}
}
void XSeatArrageManage::HideBtn()
{
	HidePopBtn();
	m_bMenuFlag=FALSE;
}

void XSeatArrageManage::ShowMenuWnd()
{
	if(NULL==m_pTempSeat)
		return;

	RECTF rect=m_pTempSeat->GetRect();
	CPoint point((int)(rect.GetRight()*GetScale()),(int)(rect.GetTop()*GetScale()));
	CreateMenuWnd(point);
}

void XSeatArrageManage::HideMenuWnd()
{
	if(NULL!=m_pMenuWnd)
		m_pMenuWnd->Hide();
}

void XSeatArrageManage::CreateMenuWnd(CPoint& point)
{
	CSize size;
	CacluOrgPoint(size);

	point.x+=size.cx;
	point.y+=size.cy;

	m_pPage->CreateMenuWnd();
	m_pPage->GetInfoMenu()->Move(point);
}

XMenuWnd* XSeatArrageManage::CreateMenuWnd()
{
	if(NULL==m_pMenuWnd)
	{
		int nWidth=16;
		int nHeight=16;
		CRect rect(CPoint(0,0),CSize(nWidth,nHeight));

		m_pMenuWnd=new XMenuWnd;
		CreateSuspendBtn(m_pMenuWnd,rect,_T("info.png"));
		m_pMenuWnd->SetManage(this);
	}

	m_pMenuWnd->Show();
	return m_pMenuWnd;
}

void XSeatArrageManage::ShowPopBtn()
{
	RECTF rect=m_pTempSeat->GetRect();
	CPoint point((int)(rect.GetRight()*GetScale()),(int)(rect.GetTop()*GetScale()));

	CSize size;
	CacluOrgPoint(size);

	point.x+=size.cx;
	point.y+=size.cy;

	CreateSeatMapWnd();
	m_pSeatMap->Move(point);

	CreateSeatArrageWnd();
	m_pSeatArrage->Move(point);
}

void XSeatArrageManage::HidePopBtn()
{
	if(NULL!=m_pSeatMap)
		m_pSeatMap->Hide();

	if(NULL!=m_pSeatArrage)
		m_pSeatArrage->Hide();
}

XSeatMap* XSeatArrageManage::CreateSeatMapWnd()
{
	if(NULL==m_pSeatMap)
	{
		int nWidth=28;
		int nHeight=28;
		CRect rect(CPoint(0,0),CSize(nWidth,nHeight));

		m_pSeatMap=new XSeatMap;
		m_pSeatMap->SetManage(this);
		CreateSuspendBtn(m_pSeatMap,rect,_T("map.png"));
		m_pSeatMap->SetTips(_C(_T("145"),_T("底图")));
		m_pSeatMap->InitTips();
	}

	m_pSeatMap->Show();
	return m_pSeatMap;
}

XSeatArrage* XSeatArrageManage::CreateSeatArrageWnd()
{
	if(NULL==m_pSeatArrage)
	{
		int nWidth=28;
		int nHeight=28;
		CRect rect(CPoint(0,0),CSize(nWidth,nHeight));

		m_pSeatArrage=new XSeatArrage;
		m_pSeatArrage->SetManage(this);
		CreateSuspendBtn(m_pSeatArrage,rect,_T("arr.png"));
		m_pSeatArrage->InitTips();
	}

	m_pSeatArrage->Show();
	return m_pSeatArrage;
}

void XSeatArrageManage::OnBtnBaseMap()
{
	//底图响应
	XSeatImage dlg;
	dlg.SetSeat(m_pTempSeat);

	if(IDOK==dlg.DoModal())
	{
		int nComboIndex=dlg.GetComboIndex();
		CString szPhotoName=dlg.GetPhotoName();
		COLORREF color=dlg.GetColor();

		if(nComboIndex==0)
			m_pTempSeat->SetModel(TRUE);
		else if(nComboIndex==1)
			m_pTempSeat->SetModel(FALSE);

		m_pTempSeat->SetPhotoName(szPhotoName);
		m_pTempSeat->SetColor(GetRValue(color),GetGValue(color),GetBValue(color),255);

		//更新预览墙
		MAP_TEMPFRAME::iterator iter=m_MapFrame.find(m_pTempSeat->GetIndex());
		if(iter!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iter->second;
			m_pMultiVideoWindow->SetFrameModel(m_nPageIndex,pFrame,m_pTempSeat->GetModel());
			m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,GetRValue(color),GetGValue(color),GetBValue(color),255);
			m_pMultiVideoWindow->SetFramePic(m_nPageIndex,pFrame,m_pTempSeat->GetPhotoPath());
		}
	}
}

void XSeatArrageManage::OnBtnArrage()
{
	//排列响应
	if(NULL==m_pTempSeat)
		return;

	XPropSheet propSheet(_T("屏幕排列向导"));
	propSheet.SetWizardMode();
	propSheet.GetPageOne()->SetDelegate(this);
	propSheet.GetPageTwo()->SetDelegate(this);

	if(ID_WIZFINISH==propSheet.DoModal())
	{
		//TRACE(_T("Finsh\n"));
	}
}

void XSeatArrageManage::MoveSeatDrawWnd()
{
	RECTF rect=m_pPage->GetRect();
	CPoint point((int)(rect.X*GetScale()),(int)(rect.Y*GetScale()));

	CSize size;
	CacluOrgPoint(size);

	point.x+=size.cx;
	point.y+=size.cy;

	if(NULL!=m_pSeatDraw)
		m_pSeatDraw->Move(point);
}


void XSeatArrageManage::ShowSeatDrawWnd()
{
	if(m_bFirstPage)
	{
		RECTF rect=m_pPage->GetRect();
		CPoint point((int)(rect.X*GetScale()),(int)(rect.Y*GetScale()));

		CreateSeatDrawWnd(point);
	}
}

void XSeatArrageManage::CreateSeatDrawWnd(CPoint& point)
{
	CSize size;
	CacluOrgPoint(size);

	point.x+=size.cx;
	point.y+=size.cy;

	CreateSeatDrawWnd();
	m_pSeatDraw->Move(point);
}

void XSeatArrageManage::CreateSeatDrawWnd()
{
	if(NULL==m_pSeatDraw)
	{
		int nWidth=32;
		int nHeight=32;
		CRect rect(CPoint(0,0),CSize(nWidth,nHeight));

		m_pSeatDraw=new XSeatDraw;
		m_pSeatDraw->SetManage(this);
		CreateSuspendBtn(m_pSeatDraw,rect,_T("drawseat.png"));
		m_pSeatDraw->SetTips(_C(_T("147"),_T("绘制坐席")));
		m_pSeatDraw->InitTips();

		//不能创建一次，可能是被预览墙挡住了，每次都创建一次，用集合保存，然后释放
		//暂时这样处理 原因没找到
		//m_VecTempDraw.push_back(m_pSeatDraw);

		//解决 --执行位置过早
	}
	m_pSeatDraw->Show();
	//创建首先为不可用状态，等待登录
	//m_pSeatDraw->EnableWindow(FALSE);
	//HideSeatDrawWnd();
}

void XSeatArrageManage::HideSeatDrawWnd()
{
	if(NULL!=m_pSeatDraw)
		m_pSeatDraw->Hide();
}

void XSeatArrageManage::EnableSeatDrawWnd(BOOL b)
{
	if(NULL!=m_pSeatDraw)
		m_pSeatDraw->EnableWindow(b);
}

void XSeatArrageManage::DrawSeat()
{
	if(!m_bFlag)
		m_bFlag=TRUE;
	else
		m_bFlag=FALSE;	
}

void XSeatArrageManage::ShowALignWnd()
{
	if(m_VecTempSeat.size()<=1)
		return;

	CreateAlignWnd();
	MoveAlignWnd();

	for(auto iter=m_MapAlign.begin();iter!=m_MapAlign.end();++iter)
	{
		XBaseWnd* pWnd=iter->second;
		pWnd->Show();
	}
}

void XSeatArrageManage::HideAlignWnd()
{
	for(auto iter=m_MapAlign.begin();iter!=m_MapAlign.end();++iter)
	{
		XBaseWnd* pWnd=iter->second;
		pWnd->Hide();
	}
}

void XSeatArrageManage::MoveAlignWnd()
{
	if(m_VecTempSeat.size()<=1)
		return;

	CSize size;
	CacluOrgPoint(size);
	//先计算选中后的大区域
	RECTF rect=GetRectBySelectedSeat(m_VecTempSeat);

	CPoint point((int)(rect.X*GetScale()),(int)(rect.Y*GetScale()));
	point.x+=size.cx;
	point.y+=size.cy;

	for(auto& map:m_MapAlign)
	{
		XBaseWnd* pWnd=map.second;
		pWnd->Move(point);
	}
}

void XSeatArrageManage::CreateAlignWnd()
{
	if(!m_bCreateAlignWnd)
	{
		int nWidth=28;
		int nHeight=28;
		CRect rectWnd(CPoint(0,0),CSize(nWidth,nHeight));

		//左对齐,定义序号为1
		XAlign* pALignLeft=new XAlign;
		CreateSuspendBtn(pALignLeft,rectWnd,_T("left.png"));
		pALignLeft->SetTips(_C(_T("126"),_T("左对齐")));
		pALignLeft->SetAlignType(ALIGN_LEFT);
		m_MapAlign.insert(std::pair<int,XBaseWnd*>(ALIGN_LEFT,pALignLeft));

		//水平居中
		XAlign* pALignHorizon=new XAlign;
		CreateSuspendBtn(pALignHorizon,rectWnd,_T("hor.png"));
		pALignHorizon->SetTips(_C(_T("127"),_T("水平居中")));
		pALignHorizon->SetAlignType(ALIGN_HORIZON);
		m_MapAlign.insert(std::pair<int,XBaseWnd*>(ALIGN_HORIZON,pALignHorizon));

		//右对齐(2)
		XAlign* pALignRight=new XAlign;
		CreateSuspendBtn(pALignRight,rectWnd,_T("right.png"));
		pALignRight->SetTips(_C(_T("128"),_T("右对齐")));
		pALignRight->SetAlignType(ALIGN_RIGHT);
		m_MapAlign.insert(std::pair<int,XBaseWnd*>(ALIGN_RIGHT,pALignRight));

		//顶端对齐
		XAlign* pAlignTop=new XAlign;
		CreateSuspendBtn(pAlignTop,rectWnd,_T("top.png"));
		pAlignTop->SetTips(_C(_T("129"),_T("顶端对齐")));
		pAlignTop->SetAlignType(ALIGN_TOP);
		m_MapAlign.insert(std::pair<int,XBaseWnd*>(ALIGN_TOP,pAlignTop));

		//垂直居中
		XAlign* pAlignVertical=new XAlign;
		CreateSuspendBtn(pAlignVertical,rectWnd,_T("ver.png"));
		pAlignVertical->SetTips(_C(_T("130"),_T("垂直居中")));
		pAlignVertical->SetAlignType(ALIGN_VERTICAL);
		m_MapAlign.insert(std::pair<int,XBaseWnd*>(ALIGN_VERTICAL,pAlignVertical));

		//底端对齐
		XAlign* pAlignBottom=new XAlign;
		CreateSuspendBtn(pAlignBottom,rectWnd,_T("bottom.png"));
		pAlignBottom->SetTips(_C(_T("131"),_T("底端对齐")));
		pAlignBottom->SetAlignType(ALIGN_BOTTOM);
		m_MapAlign.insert(std::pair<int,XBaseWnd*>(ALIGN_BOTTOM,pAlignBottom));

		for(auto& map:m_MapAlign)
		{
			XBaseWnd* pWnd=map.second;
			pWnd->SetManage(this);
			pWnd->InitTips();
		}
		m_bCreateAlignWnd=TRUE;
	}
}

void XSeatArrageManage::OnAlignLeft()
{
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.X=rectEnd.GetLeft();

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}

	MoveAlignWnd();
}
void XSeatArrageManage::OnAlignHorzion()
{
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.X=rectEnd.X+rectEnd.Width/2-rect.Width/2;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
	MoveAlignWnd();
}
void XSeatArrageManage::OnAlignRight()
{
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.X=rectEnd.GetRight()-rect.Width;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
	MoveAlignWnd();
}
void XSeatArrageManage::OnAlignTop()
{
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.Y=rectEnd.GetTop();

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
	MoveAlignWnd();
}
void XSeatArrageManage::OnAlignVertical()
{
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.Y=rectEnd.Y+rectEnd.Height/2-rect.Height/2;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	MoveAlignWnd();
}
void XSeatArrageManage::OnAlignBottom()
{
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.Y=rectEnd.GetBottom()-rect.Height;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
	MoveAlignWnd();
}

RECTF XSeatArrageManage::GetRectBySelectedSeat(VEC_SEAT& VecSeat)
{
	RECTF rect;
	BOOL bFirst=TRUE;

	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pSeat=*iter;
		RECTF rectSeat=pSeat->GetRect();

		if(bFirst)
		{
			rect=rectSeat;
			bFirst=FALSE;
		}
		else
		{
			rect.Union(rect,rect,rectSeat);
		}
	}
	return rect;
}

void XSeatArrageManage::CreateSuspendBtn(XBaseWnd* pWnd,CRect& rect,CString szImage)
{
	pWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pDelegate->GetView(),0);
	pWnd->SetImage(HandlePath::GetPhotoPath(szImage));
	pWnd->ShowWindow(SW_HIDE);
	pWnd->UpdateWindow();
}

void XSeatArrageManage::CacluOrgPoint(CSize& orgSize)
{
	CView* pView=m_pDelegate->GetView();
	if(NULL==pView)
		return;

	CRect rectView;
	pView->GetClientRect(&rectView);

	CSize size=ViewGetSize();
	int vPos=pView->GetScrollPos(SB_HORZ);
	int hPos=pView->GetScrollPos(SB_VERT);
	float fScale=GetScale();

	XCaculateSeatArrageManage::SetPageOrg(rectView,vPos,hPos,size,fScale,orgSize);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XSeatArrageManage::ResetSeatRange()
{
	//限制行列（现在页面做多容纳9*5）//10.10放开限制超过屏幕限制缩小区域大小
	int nRow=0;
	int nColumn=0;

	if(NULL==m_pTempSeat)
	{
		nRow=m_nSeatRow;
		nColumn=m_nSeatColumn;
	}
	else
	{
		nRow=m_pTempSeat->GetSeatRow();
		nColumn=m_pTempSeat->GteSeatCloumn();
	}

	if(nRow==0||nColumn==0)
		return;

	//if(nRow>9)
	//	nRow=9;
	//if(nColumn>5)
	//	nColumn=5;

	int nTempScreenH=0;
	int nTempScreenV=0;
	if(nColumn>5)
	{
		nTempScreenH=PAGE_WIDTH/nColumn;
		nTempScreenV=nTempScreenH*9/16;
	}
	else
	{
		nTempScreenH=SCREEN_H;
		nTempScreenV=SCREEN_V;
	}

	//调整坐席排列
	//按照屏幕行列，计算屏幕在页面位置
	int nInterWidth=nColumn*nTempScreenH;
	int nInterHeight=nRow*nTempScreenV;
	//开始画线点
	int nX=(PAGE_WIDTH-nInterWidth)/2;
	int nY=(PAGE_HEIGHT-nInterHeight)/2;
	//记录屏幕开始偏移
	m_DeviationPoint=POINTF((Gdiplus::REAL)nX,(Gdiplus::REAL)nY);
	//设置预览墙绘制点
	m_pMultiVideoWindow->SetFramesPoint(m_nPageIndex,CPoint(nX,nY));
	//设置预览墙网格行列
	m_pMultiVideoWindow->SetFramesArrage(m_nPageIndex,nRow,nColumn,nTempScreenH,nTempScreenV);
	//删除预览墙Frame
	m_pMultiVideoWindow->DeleteFrame(m_nPageIndex);
	//清空Frame缓存
	m_MapSecondFrame.clear();
	//根据行列设置初始化屏幕
	m_pPage->InitScreen(nRow,nColumn,nTempScreenH,nTempScreenV);
	m_pTempScreen=NULL;
}

void XSeatArrageManage::ShowGroupSeatArrage(CString szGroup)
{

}

void XSeatArrageManage::SetVecArrage()
{
	int nCount=0;
	if(NULL==m_pTempSeat)
	{
		nCount=m_nSeatRow;
	}
	else
	{
		nCount=m_pTempSeat->GetSeatRow();
	}

	ClearVecArrage();
	VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
	for(int i=0;i<nCount;i++)
	{
		int nRow=i+1;
		std::vector<int> VecInt;
		for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			if(nRow==pScreen->GetRowIndex())
			{
				if(pScreen->GetHas())
					VecInt.push_back(pScreen->GetNodeID());
				else
					VecInt.push_back(0);
			}
		}
		m_VecArrage.push_back(VecInt);
	}
}

CString XSeatArrageManage::GetArrayInfo()
{
	CString szValue=_T("");
	for(auto iter=m_VecArrage.begin();iter!=m_VecArrage.end();++iter)
	{
		CString szTempValue;
		std::vector<int> Vec=*iter;
		for(auto iter=Vec.begin();iter!=Vec.end();++iter)
		{
			int nValue=*iter;
			CString szTemp;
			szTemp.Format(_T("#%d;"),nValue);
			szTempValue+=szTemp;
		}
		szValue+=szTempValue;
		szValue+=_T("\n");
	}

	int nPos=szValue.ReverseFind('\n');
	return szValue.Left(nPos);
}

CString XSeatArrageManage::GetArrayMatrix()
{
	CString szMatrix=_T("");
	int nColumn=0;
	for(auto iter=m_VecArrage.begin();iter!=m_VecArrage.end();++iter)
	{
		std::vector<int> Vec=*iter;
		nColumn=Vec.size();
	}

	int nRow=m_VecArrage.size();
	szMatrix.Format(_T("%dx%d"),nColumn,nRow);

	return szMatrix;
}

void XSeatArrageManage::ClearInfo(CString szGroupName)
{
	//XPage* pPage=m_pPage;
	//清空第一页名称

	//两个页面同时执行
	{
		//第一页（清除坐席文字）
		XPage* pPage=m_MapPage[1];

		VEC_SEAT& VecSeat=pPage->GetVecSeat();
		for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
		{
			XSeat* pSeat=*iter;
			if(pSeat->GetGroupName()==szGroupName)
			{
				pSeat->SetGroupName(_T(""));
				pSeat->SetSelected(FALSE);

				MAP_TEMPFRAME::iterator iter=m_MapFrame.find(pSeat->GetIndex());
				if(iter!=m_MapFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;
					m_pMultiVideoWindow->SetFrameText(1,pFrame,_T(""));
				}

				//清空属性名称
				CMFCPropertyGridProperty* pName=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATNAME);
				if(NULL!=pName)
					pName->SetValue((_variant_t)_T(""));
			}
		}
	}

	{
		//第二页（清除屏幕以及网格）
		XPage* pPage=m_MapPage[2];
		//清理第二页(当前处于第二页时有效)
		pPage->ClearVecScreen();
		//清除frame
		m_pMultiVideoWindow->DeleteFrame(2);
		//清除网格
		m_pMultiVideoWindow->SetFramesArrage(2,0,0,0,0);
		m_MapSecondFrame.clear();
	}
}

void XSeatArrageManage::ClearPage()
{
	//注销清空页面信息
	//此时m_nFirstPage不适用为0
	//1.      1，2不会共存
	{
		//先全部隐藏菜单按钮
		HideMenuWnd();
		//第一页
		XPage* pPage=m_MapPage[1];

		VEC_SEAT& VecSeat=pPage->GetVecSeat();
		for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
		{
			XSeat* pSeat=*iter;
			//保留坐席名称 用于登录匹配名称
			//pSeat->SetGroupName(_T("")); 
			pSeat->SetSelected(FALSE);

			MAP_TEMPFRAME::iterator iter1=m_MapFrame.find(pSeat->GetIndex());
			if(iter1!=m_MapFrame.end())
			{
				XMultiVideoWindowFrame* pFrame=iter1->second;
				//m_pMultiVideoWindow->SetFrameText(1,pFrame,_T(""));
				m_pMultiVideoWindow->DeleteFrame(1,pFrame);
			}		
		}
		//清理Frame缓存key值
		m_MapFrame.clear();
	}
	//2.
	{
		//第二页（清除屏幕以及网格）
		XPage* pPage=m_MapPage[2];
		//清理第二页(当前处于第二页时有效)
		pPage->ClearVecScreen();
		//清除frame
		m_pMultiVideoWindow->DeleteFrame(2);
		//清除网格
		m_pMultiVideoWindow->SetFramesArrage(2,0,0,0,0);
		m_MapSecondFrame.clear();
	}
}

void XSeatArrageManage::UpdateGroupNameAfterAddArrage(CString szName)
{
	if(NULL==m_pTempSeat)
		return;

	m_pTempSeat->SetGroupName(szName);
	//更新预览墙文字
	auto iter=m_MapFrame.find(m_pTempSeat->GetIndex());
	if(iter!=m_MapFrame.end())
	{
		XMultiVideoWindowFrame* pFrame=iter->second;
		m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,szName);
	}
	//设置行列
	MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	auto iterMap=MapNodeGroup.find(szName);
	if(iterMap!=MapNodeGroup.end())
	{
		XNodeGroupInfo* pInfo=iterMap->second;
		m_pTempSeat->SetSeatRow(pInfo->GetMatrixRow());
		m_pTempSeat->SetSeatColumn(pInfo->GetMatrixColumn());
	}
}

void XSeatArrageManage::UpdateGroupNameAfterChange(CString szGroupName,CString szName)
{
	//在不在第一页 都更改名称
	XPage* pPage=m_MapPage[m_nFirstPage];
	VEC_SEAT& VecSeat=pPage->GetVecSeat();
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pSeat=*iter;
		if(pSeat->GetGroupName()==szGroupName)
		{
			pSeat->SetGroupName(szName);

			auto iter1=m_MapFrame.find(pSeat->GetIndex());
			if(iter1!=m_MapFrame.end())
			{
				XMultiVideoWindowFrame* pFrame=iter1->second;
				m_pMultiVideoWindow->SetFrameText(m_nFirstPage,pFrame,szName);
			}
		}
	}
	//更改预览墙标题
	CString szText;
	if(szName==_T(""))
	{
		szText=_C(_T("143"),_T("输入编排"));
	}
	else
	{
		szText.Format(_T("%s(%s)-%s"),_C(_T("142"),_T("组")),
					  szName,_C(_T("143"),_T("输入编排")));
	}
	m_pMultiVideoWindow->SetText(szText);
	//更改属性名称
	CMFCPropertyGridProperty* pName=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATNAME);
	if(NULL!=pName)
		pName->SetValue((_variant_t)szName);
}

void XSeatArrageManage::UpdateGroupArrageByRemoveNode(CString szGroupName,int nNodeID)
{
	//从组中删除（需不需要判断能不能删除）
	//JudgetDelNodeFromGroup（）
	XNodeGroupInfo* pInfo=GetNodeGroupInfoByName(szGroupName);
	if(NULL==pInfo)
		return;

	//1.直接更改集合信息（在第一页）
	VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
	CopyArray(VecArrage,nNodeID);
	CString szArray=GetArrayInfo();
	CString szMatrix=GetArrayMatrix();

	//更新
	XNodeGroupInfo nodeGroupInfo;
	nodeGroupInfo.SetGroupID(pInfo->GetGroupID());
	nodeGroupInfo.SetGroupName(pInfo->GetGroupName());
	nodeGroupInfo.SetArray(szArray);
	nodeGroupInfo.SetMatrix(szMatrix);

	//判断是不是主屏幕
	if(pInfo->GetMaster()!=nNodeID)
	{
		nodeGroupInfo.SetMaster(pInfo->GetMaster());
	}
	else
	{
		//删除了主屏幕
		//先求出下一个主屏
		int nMaster=GetMasterInArray();
		nodeGroupInfo.SetMaster(nMaster);
	}
	//更新坐席排列
	if(pInfo->GetMainSecond())
	{
		XSendDataManage::GetInstance()->AddSendDataOfUpdataMasterSeatArrage(nodeGroupInfo);
	}
	else
	{
		XSendDataManage::GetInstance()->AddSendDataOfUpdataSeatArrage(nodeGroupInfo);
	}
}

void XSeatArrageManage::UpdateScreenAfterRemoveNode(int nNodeID)
{
	//第二页才生效
	XScreen* pScreen=NULL;
	pScreen=GetScreenByNodeID(nNodeID);
	if(NULL==pScreen)
		return;

	pScreen->SetHas(FALSE);
	pScreen->SetNodeID(0);
	pScreen->SetMaster(FALSE);
	pScreen->SetSelected(FALSE);

	auto iter=m_MapSecondFrame.find(nNodeID);
	if(iter!=m_MapSecondFrame.end())
	{
		XMultiVideoWindowFrame* pFrame=iter->second;
		m_pMultiVideoWindow->DeleteFrame(2,pFrame);
	}
}

void XSeatArrageManage::UpdateShowMasterAfterRemoveNode(int nMaster)
{
	//第二页生效
	if(m_bFirstPage)
		return;

	XScreen* pScreen=NULL;
	pScreen=GetScreenByNodeID(nMaster);
	if(NULL==pScreen)
		return;

	pScreen->SetMaster(TRUE);

	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	MAP_TEMPFRAME::iterator iterMap=m_MapSecondFrame.find(pScreen->GetNodeID());
	if(iterMap!=m_MapSecondFrame.end())
	{
		XMultiVideoWindowFrame* pFrame=iterMap->second;

		MAP_NODE::iterator iterNode=MapNode.find(pScreen->GetNodeID());
		if(iterNode!=MapNode.end())
		{
			XNode* pNode=iterNode->second;

			CString szText;
			szText.Format(_T("%s(%s)"),pNode->GetNodeName(),_C(_T("137"),_T("主")));
			m_pMultiVideoWindow->SetFrameText(2,pFrame,szText);
		}
	}
}

XScreen* XSeatArrageManage::GetScreenByNodeID(int nNodeID)
{
	XPage* pPage=m_MapPage[2];
	VEC_SCREEN& VecScreen=pPage->GetVecScreen();
	for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		if(pScreen->GetNodeID()==nNodeID)
			return pScreen;
	}
	return NULL;
}

void XSeatArrageManage::CopyArray(VEC_ARRAGE& VecArrage,int nNodeID)
{
	ClearVecArrage();
	for(auto iter=VecArrage.begin();iter!=VecArrage.end();++iter)
	{
		std::vector<int> VecSub;

		std::vector<int> VecInt=*iter;
		for(auto iter=VecInt.begin();iter!=VecInt.end();++iter)
		{
			int nTempNodeID=*iter;
			if(nTempNodeID==nNodeID)
				VecSub.push_back(0);
			else
				VecSub.push_back(nTempNodeID);
		}
		m_VecArrage.push_back(VecSub);
	}
}

int XSeatArrageManage::GetMasterInArray()
{
	//查找第一个不为零的节点
	for(auto iter=m_VecArrage.begin();iter!=m_VecArrage.end();++iter)
	{
		auto VecSub=*iter;
		for(auto iter=VecSub.begin();iter!=VecSub.end();++iter)
		{
			int nNodeID=*iter;
			if(nNodeID!=0)
				return nNodeID;
		}
	}
	return 0;
}

BOOL XSeatArrageManage::JudgetDelNodeFromGroup(CString szGroupName,int nNodeID)
{
	//判断节点能不能从组中删除
	//XNodeGroupInfo* pInfo=NULL;
	//MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	//MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szGroupName);
	//if(iter!=MapNodeGroup.end())
	//{
	//	pInfo=iter->second;
	//}

	//if(NULL==pInfo)
	//	return FALSE;

	//VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
	//if(!JudgeNodeInVec(VecArrage,nNodeID))
	//{
	//	//集合中没有
	//	return TRUE;
	//}
	//else
	//{

	//}

	return TRUE;
}

void XSeatArrageManage::DelNodeFromGroup(CString szGroupName,int nNodeID)
{

}

void XSeatArrageManage::SetNodeSelected(CString szNodeName)
{
	//点击节点选中，并显示属性
	//选中
	if(m_bFirstPage)
		return;

	if(_T("")==szNodeName)
		return;

	int nNodeID=GetNodeIDByName(szNodeName);
	if(nNodeID==0)
		return;

	//设置屏幕选中
	VEC_SCREEN& VecScreen=m_pPage->GetVecScreen();
	for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		if(pScreen->GetNodeID()==nNodeID)
		{
			pScreen->SetSelected(TRUE);
		}
		else if(pScreen->GetNodeID()!=nNodeID)
		{
			pScreen->SetSelected(FALSE);
		}
	}

	//预览墙选中(知道在第二页)
	auto iterMap=m_MapSecondFrame.find(nNodeID);
	if(iterMap!=m_MapSecondFrame.end())
	{
		XMultiVideoWindowFrame* pFrame=iterMap->second;
		//指定Frame选中，其他不选中
		m_pMultiVideoWindow->SetFrameSelect(2,pFrame);
	}

	////////////////////////////////////////////////////////////////////////
	//更改属性
	//MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	//for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	//{
	//	XNode* pNode=iter->second;
	//	if(pNode->GetNodeName()==szNodeName)
	//	{
	//		XPropertiesWnd::GetInstance()->SetNodeGroup(NULL);
	//		XPropertiesWnd::GetInstance()->SetNode(pNode);
	//		XPropertiesWnd::GetInstance()->SetSeat(NULL);
	//		pNode->SetPropertiesWnd();
	//	}
	//}

}

int XSeatArrageManage::GetNodeIDByName(CString szNodeName)
{
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeName()==szNodeName)
			return pNode->GetNodeID();
	}
	return 0;
}

XNode* XSeatArrageManage::GetNodeByID(int nNodeID)
{
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeID()==nNodeID)
			return pNode;
	}
	return NULL;
}

BOOL XSeatArrageManage::JudgeNodeInVec(VEC_ARRAGE& VecArrage,int nNodeID)
{
	for(auto iter=VecArrage.begin();iter!=VecArrage.end();++iter)
	{
		std::vector<int> VecInt=*iter;
		for(auto iter=VecInt.begin();iter!=VecInt.end();++iter)
		{
			int nTempNodeID=*iter;
			if(nTempNodeID==nNodeID)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

void XSeatArrageManage::UpdateMultiWindowByPropertyChange(XSeat* pSeat,int nType)
{
	switch(nType)
	{
		case ID_SEATRECTX:
		case ID_SEATRECTY:
		case ID_SEATRECTW:
		case ID_SEATRECTH:
			{
				MAP_TEMPFRAME::iterator iter=m_MapFrame.find(pSeat->GetIndex());
				if(iter!=m_MapFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;
					m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,pSeat->GetRect());
				}

				//更新菜单按钮
				HideAlignWnd();
				HideBtn();
				ShowMenuWnd();
			}
			break;
		case ID_SEATCOLOR:
		case ID_SEATTRANS:
			{
				MAP_TEMPFRAME::iterator iter=m_MapFrame.find(pSeat->GetIndex());
				if(iter!=m_MapFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;
					m_pMultiVideoWindow->SetFrame(m_nPageIndex,pFrame,pSeat->GetColorR(),pSeat->GetColorG(),pSeat->GetColorB(),pSeat->GetColorA());
				}
			}
			break;
		case ID_SEATMODEL:
			{
				MAP_TEMPFRAME::iterator iter=m_MapFrame.find(pSeat->GetIndex());
				if(iter!=m_MapFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;
					m_pMultiVideoWindow->SetFrameModel(m_nPageIndex,pFrame,pSeat->GetModel());
				}
			}
			break;
		case ID_SEATPIC:
			{
				MAP_TEMPFRAME::iterator iter=m_MapFrame.find(pSeat->GetIndex());
				if(iter!=m_MapFrame.end())
				{
					XMultiVideoWindowFrame* pFrame=iter->second;
					m_pMultiVideoWindow->SetFramePic(m_nPageIndex,pFrame,pSeat->GetPhotoPath());
				}
			}
			break;
		case ID_SEATROW:
		case ID_SEATCOLUMN:
			{
				ResetSeatRange();
			}
			break;
		default:
			break;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XSeatArrageManage::OperateOfSaveSeat()
{
	//保存坐席(第二页)
	if(m_nPageIndex==2)
	{
		XPage* pPage=m_pPage;
		CString szGroupName=pPage->GetGroupName();

		if(_T("")==szGroupName)
			return;

		//保存屏幕排列信息
		SetVecArrage();

		//计算主屏幕
		int nMaster=0;
		VEC_SCREEN& VecScreen=pPage->GetVecScreen();
		for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
		{
			XScreen* pScreen=*iter;
			if(pScreen->GetMaster())
				nMaster=pScreen->GetNodeID();
		}

		//组信息
		XNodeGroupInfo* pInfo=GetNodeGroupInfoByName(szGroupName);
		if(NULL==pInfo)
			return;

		//更新
		XNodeGroupInfo nodeGroupInfo;
		nodeGroupInfo.SetGroupID(pInfo->GetGroupID());
		nodeGroupInfo.SetGroupName(pInfo->GetGroupName());

		CString szArray=GetArrayInfo();
		if(szArray!=_T(""))
		{
			if(szArray!=pInfo->GetArray())
			{
				nodeGroupInfo.SetArray(szArray);

				CString szMatrix=GetArrayMatrix();
				nodeGroupInfo.SetMatrix(szMatrix);
				nodeGroupInfo.SetMaster(nMaster);
				//更新坐席排列
				if(pInfo->GetMainSecond())
				{
					//保存主副屏坐席
					XSendDataManage::GetInstance()->AddSendDataOfUpdataMasterSeatArrage(nodeGroupInfo);
				}
				else
				{
					//保存坐席
					XSendDataManage::GetInstance()->AddSendDataOfUpdataSeatArrage(nodeGroupInfo);
				}
			}
		}
	}
}

void XSeatArrageManage::OperateOfSendSeat()
{

}

void XSeatArrageManage::OperateOfClearSeat()
{

}

void XSeatArrageManage::OperateOfSetBg()
{
	//设置背景
	XBackGround dlg;
	dlg.SetDelegate(this);
	if(IDOK==dlg.DoModal())
	{
		CString szPhotoName=dlg.GetPhotoName();
		int nIndex=dlg.GetComboIndex();
		COLORREF color=dlg.GetColor();

		XPage* pPage=m_pPage;
		pPage->SetPhotoName(szPhotoName);
		if(nIndex==0)
			pPage->SetModel(TRUE);
		else
			pPage->SetModel(FALSE);
		pPage->SetColor(GetRValue(color),GetGValue(color),GetBValue(color));
		//设置预览墙颜色
		m_pDelegate->SetMultiVideoFramesBg();
	}
}

void XSeatArrageManage::OperateOfSetBtnStatus()
{
	if(!m_bFlag)
		m_bFlag=TRUE;
	else
		m_bFlag=FALSE;
}

void XSeatArrageManage::OperateOfAlignLeft()
{
	OnAlignLeft();
}

void XSeatArrageManage::OperateOfAlignHorizon()
{
	OnAlignHorzion();
}

void XSeatArrageManage::OperateOfAlignRight()
{
	OnAlignRight();
}

void XSeatArrageManage::OperateOfAlignUp()
{
	OnAlignTop();
}

void XSeatArrageManage::OperateOfAlignDown()
{
	OnAlignBottom();
}

void XSeatArrageManage::OperateOfAlignVertical()
{
	OnAlignVertical();
}

void XSeatArrageManage::OperateOfAlignSame()
{
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.Width=rectEnd.Width;
		rect.Height=rectEnd.Height;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
	MoveAlignWnd();
}

void XSeatArrageManage::OperateOfAlignHSame()
{
	//宽度相同
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.Width=rectEnd.Width;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
	MoveAlignWnd();
}

void XSeatArrageManage::OperateOfAlignVSame()
{
	if(m_VecTempSeat.size()==0||m_VecTempSeat.size()==1)
		return;

	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;

	RECTF rectEnd=pEndSeat->GetRect();

	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		rect.Height=rectEnd.Height;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
	MoveAlignWnd();
}

BOOL compare1(XSeat* pSeat1,XSeat* pSeat2)
{
	RECTF rect1=pSeat1->GetRect();
	RECTF rect2=pSeat2->GetRect();
	if(rect1.GetLeft()<rect2.GetLeft())
		return TRUE;
	else
		return FALSE;
}

void XSeatArrageManage::OperateOfAlignWidth()
{
	int nSize=m_VecTempSeat.size();
	if(nSize==0||nSize==1)
		return;

	//先根据区域X排序
	sort(m_VecTempSeat.begin(),m_VecTempSeat.end(),compare1);
	//第一个
	XSeat *pBeginSeat=NULL;
	VEC_SEAT::iterator iterBegin=m_VecTempSeat.begin();
	pBeginSeat=*iterBegin;
	if(!pBeginSeat)
		return;
	//最后一个
	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;
	RECTF rectBegin=pBeginSeat->GetRect();
	RECTF rectEnd=pEndSeat->GetRect();

	float allDistance=rectEnd.GetRight()-rectBegin.GetLeft();

	float allRect=0.0;
	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end();++iter)
	{
		XSeat* pSeat=*iter;
		allRect+=pSeat->GetRect().Width;
	}

	float Distance=(allDistance-allRect)/(nSize-1);

	for(auto iter=m_VecTempSeat.begin()+1;iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		XSeat* pTemp=*(iter-1);
		rect.X=pTemp->GetRect().GetRight()+Distance;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
}

BOOL compare2(XSeat* pSeat1,XSeat* pSeat2)
{
	RECTF rect1=pSeat1->GetRect();
	RECTF rect2=pSeat2->GetRect();
	if(rect1.GetTop()<rect2.GetTop())
		return TRUE;
	else
		return FALSE;
}

void XSeatArrageManage::OperateOfAlignHeight()
{
	int nSize=m_VecTempSeat.size();
	if(nSize==0||nSize==1)
		return;
	//先根据区域X排序
	sort(m_VecTempSeat.begin(),m_VecTempSeat.end(),compare2);
	//第一个
	XSeat *pBeginSeat=NULL;
	VEC_SEAT::iterator iterBegin=m_VecTempSeat.begin();
	pBeginSeat=*iterBegin;
	if(!pBeginSeat)
		return;
	//最后一个
	XSeat *pEndSeat=NULL;
	VEC_SEAT::iterator iterEnd=m_VecTempSeat.end()-1;
	pEndSeat=*iterEnd;
	if(!pEndSeat)
		return;
	RECTF rectBegin=pBeginSeat->GetRect();
	RECTF rectEnd=pEndSeat->GetRect();

	float allDistance=rectEnd.GetBottom()-rectBegin.GetTop();

	float allRect=0.0;
	for(auto iter=m_VecTempSeat.begin();iter!=m_VecTempSeat.end();++iter)
	{
		XSeat* pSeat=*iter;
		allRect+=pSeat->GetRect().Height;
	}

	float Distance=(allDistance-allRect)/(nSize-1);

	for(auto iter=m_VecTempSeat.begin()+1;iter!=m_VecTempSeat.end()-1;++iter)
	{
		XSeat* pSeat=*iter;
		int nIndex=pSeat->GetIndex();
		RECTF rect=pSeat->GetRect();
		//求出新区域
		XSeat* pTemp=*(iter-1);
		rect.Y=pTemp->GetRect().GetBottom()+Distance;

		//更新坐席区域
		pSeat->SetRect(rect);
		//更新预览墙
		MAP_TEMPFRAME::iterator iterFrame=m_MapFrame.find(nIndex);
		if(iterFrame!=m_MapFrame.end())
		{
			XMultiVideoWindowFrame* pFrame=iterFrame->second;
			m_pMultiVideoWindow->SetFrame(nIndex,pFrame,rect);
		}
	}
}

void XSeatArrageManage::OperateOfScreenArray()
{
	//屏幕行列排列
	XScreenArray dlg;

	if(NULL==m_pTempSeat)
	{
		dlg.SetScreenRow(m_nSeatRow);
		dlg.SetScreenColumn(m_nSeatColumn);
	}
	else
	{
		dlg.SetScreenRow(m_pTempSeat->GetSeatRow());
		dlg.SetScreenColumn(m_pTempSeat->GteSeatCloumn());
	}

	if(IDOK==dlg.DoModal())
	{
		m_nSeatRow=dlg.GetScreenRow();
		m_nSeatColumn=dlg.GetScreenColumn();

		if(NULL!=m_pTempSeat)
		{
			m_pTempSeat->SetSeatRow(m_nSeatRow);
			m_pTempSeat->SetSeatColumn(m_nSeatColumn);
		}

		ResetSeatRange();
		//更新属性面板
		CMFCPropertyGridProperty* pRow=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATROW);
		if(NULL!=pRow)
			pRow->SetValue(_variant_t(m_nSeatRow));

		CMFCPropertyGridProperty* pColumn=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_SEATCOLUMN);
		if(NULL!=pColumn)
			pColumn->SetValue(_variant_t(m_nSeatColumn));
	}
}

void XSeatArrageManage::MatchSeatNameByGroupName()
{
	//登录完成匹配坐席名称
	if(m_bFirstPage)
	{
		MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();

		//XSeat* pSeat=NULL;
		XPage* pPage=m_MapPage[m_bFirstPage];
		VEC_SEAT& VecSeat=pPage->GetVecSeat();
		for(auto& pSeat:VecSeat)
		{
			CString szGroupName=_T("");

			auto iter=MapNodeGroup.find(pSeat->GetGroupName());
			if(iter!=MapNodeGroup.end())
			{
				szGroupName=pSeat->GetGroupName();
			}

			//设置预览墙显示组名称
			int nIndex=pSeat->GetIndex();
			MAP_TEMPFRAME::iterator iter1=m_MapFrame.find(nIndex);
			if(iter1!=m_MapFrame.end())
			{
				XMultiVideoWindowFrame* pFrame=iter1->second;
				m_pMultiVideoWindow->SetFrameText(m_nPageIndex,pFrame,szGroupName);
			}
		}
	}
}


void XSeatArrageManage::Operate(OPERATETYPE type,void* pData)
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
		case OPERATETYPE_SAVESEAT:
			{
				OperateOfSaveSeat();
			}
			break;
		case OPERATETYPE_SENDSEAT:
			{
				OperateOfSendSeat();
			}
			break;
		case OPERATETYPE_CLEARSEAT:
			{
				OperateOfClearSeat();
			}
			break;
		case OPERATETYPE_BG:
			{
				OperateOfSetBg();
			}
			break;
		case OPERATETYPE_SEAT:
			{
				OperateOfSetBtnStatus();
			}
			break;
		case OPERATETYPE_ALIGNLEFT:
			{
				OperateOfAlignLeft();
			}
			break;
		case OPERATETYPE_ALIGNHORIZON:
			{
				OperateOfAlignHorizon();
			}
			break;
		case OPERATETYPE_ALIGNRIGHT:
			{
				OperateOfAlignRight();
			}
			break;
		case OPERATETYPE_ALIGNUP:
			{
				OperateOfAlignUp();
			}
			break;
		case OPERATETYPE_ALIGNDOWN:
			{
				OperateOfAlignDown();
			}
			break;
		case OPERATETYPE_ALIGNVERTICAL:
			{
				OperateOfAlignVertical();
			}
			break;
		case OPERATETYPE_ALIGNSAME:
			{
				OperateOfAlignSame();
			}
			break;
		case OPERATETYPE_ALIGNHSAME:
			{
				OperateOfAlignHSame();
			}
			break;
		case OPERATETYPE_ALIGNVSAME:
			{
				OperateOfAlignVSame();
			}
			break;
		case OPERATETYPE_ALIGNWIDTH:
			{
				OperateOfAlignWidth();
			}
			break;
		case OPERATETYPE_ALIGNHEIGHT:
			{
				OperateOfAlignHeight();
			}
			break;
		case OPERATETYPE_SCREENARRAY:
			{
				OperateOfScreenArray();
			}
			break;
		default:
			break;
	}
}

void XSeatArrageManage::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	switch(type)
	{
		case CMDUITYPE_ALIGNLEFT:
			{
				pCmdUI->SetText(_C(_T("126"),_T("左对齐")));
			}
			break;
		case CMDUITYPE_ALIGNHORIZON:
			{
				pCmdUI->SetText(_C(_T("127"),_T("水平居中")));
			}
			break;
		case CMDUITYPE_ALIGNRIGHT:
			{
				pCmdUI->SetText(_C(_T("128"),_T("右对齐")));
			}
			break;
		case CMDUITYPE_ALIGNUP:
			{
				pCmdUI->SetText(_C(_T("129"),_T("顶端对齐")));
			}
			break;
		case CMDUITYPE_ALIGNDOWN:
			{
				pCmdUI->SetText(_C(_T("131"),_T("底端对齐")));
			}
			break;
		case CMDUITYPE_ALIGNVERTICAL:
			{
				pCmdUI->SetText(_C(_T("130"),_T("垂直居中")));
			}
			break;
		case CMDUITYPE_ALIGNSAME:
			{
				pCmdUI->SetText(_C(_T("132"),_T("大小相同")));
			}
			break;
		case CMDUITYPE_ALIGNHSAME:
			{
				pCmdUI->SetText(_C(_T("133"),_T("宽度相同")));
			}
			break;
		case CMDUITYPE_ALIGNVSAME:
			{
				pCmdUI->SetText(_C(_T("134"),_T("高度相同")));
			}
			break;
		case CMDUITYPE_ALIGNWIDTH:
			{
				pCmdUI->SetText(_C(_T("135"),_T("横向分布")));
			}
			break;
		case CMDUITYPE_ALIGNHEIGHT:
			{
				pCmdUI->SetText(_C(_T("136"),_T("纵向分布")));
			}
			break;
		case CMDUITYPE_SEAT:
			{
				pCmdUI->SetCheck(m_bFlag);
			}
			break;
		default:
			{
				CString szPath=HandlePath::GetIniPath(APP_ININAME);
				int nType=HandleIni::GetInt(_T("Info"),_T("SeatArrageScale"),0,szPath);

				if(nType==type)
					pCmdUI->SetCheck(1);
				else
					pCmdUI->SetCheck(0);
			}
	}
}

//////////////////////////////////////////////////////////////////////////
void XSeatArrageManage::ChangeScale(int nType)
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
	if(m_nScale!=nScale)
	{
		HideMenuWnd();
		HideBtn();
		HideAlignWnd();
		SetVecSeatUnselect();
		m_pMultiVideoWindow->SetVecFrameUnselect(m_nPageIndex);

		m_nScale=nScale;
		SaveDataOfScale(int(nType));
		ResetViewSize();
		//移动绘制按钮
		MoveSeatDrawWnd();

		//设置预览墙放缩
		float fScale=m_nScale/100.0f;
		m_pDelegate->SetMultiVideoWindowScale(fScale);
	}
}

void XSeatArrageManage::ControlDataChange(XDATATYPE type,void* pControl)
{
}

void XSeatArrageManage::UpdateControlDataShow(XDATATYPE type,void* pControl)
{
}