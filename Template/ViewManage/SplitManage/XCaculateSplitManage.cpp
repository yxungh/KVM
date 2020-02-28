#include "stdafx.h"
#include "XConstant.h"
#include "XCaculateSplitManage.h"
#include "HandleCalculate.h"
#include "XSplitManage.h"
#include "XSplitScreen.h"
#include "XSignal.h"




XCaculateSplitManage::XCaculateSplitManage()
{
}


XCaculateSplitManage::~XCaculateSplitManage()
{
}


CSize XCaculateSplitManage::ViewGetSize(XSplitManage* pManage)
{
	float dwScale=pManage->GetScale();

	CSize size;
	size.cx=LONG(DRAWDISTANCE_X*2+pManage->GetResulationX()*dwScale*pManage->GetScreenCountX());
	size.cy=LONG(DRAWDISTANCE_Y*2+pManage->GetResulationY()*dwScale*pManage->GetScreenCountY());

	//TRACE(_T("Size X=%d,Y=%d\n"),size.cx,size.cy);

	return size;
}

void XCaculateSplitManage::SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CDC& dc)
{
	HandleCalculate::SetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,dc);
}

void XCaculateSplitManage::ReductionPoint(XSplitManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint)
{
	CSize size=pManage->ViewGetSize();
	float dwScale=pManage->GetScale();

	int nResolutionH=pManage->GetResulationX();
	int nResolutionV=pManage->GetResulationY();

	float dwScaleResolutionH=nResolutionH*dwScale;
	float dwScaleResolutionV=nResolutionV*dwScale;

	int nOrgX=0;
	int nOrgY=0;

	GetViewPortOrg(rect,nOffsetX,nOffsetY,size,dwScale,nOrgX,nOrgY);

	int nTempX=srcPoint.x-nOrgX;
	int nTempY=srcPoint.y-nOrgY;

	desPoint.X=(float)(1.0f*nResolutionH/dwScaleResolutionH*nTempX);
	desPoint.Y=(float)(1.0f*nResolutionV/dwScaleResolutionV*nTempY);
}

void XCaculateSplitManage::GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,int& nOrgX,int& nOrgY)
{
	HandleCalculate::GetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,nOrgX,nOrgY);
}


RECTF XCaculateSplitManage::CalculateSignalRect(RECTF& rect,VEC_SPLITSCREEN& VecScreen)
{
	//先计算屏幕整体区域
	RECTF rectScreen;
	BOOL bFirst=TRUE;
	for(auto& pScreen:VecScreen)
	{
		RECTF tempRect=pScreen->GetRect();
		if(bFirst)
		{
			rectScreen=tempRect;
			bFirst=FALSE;
		}
		else
		{
			rectScreen.Union(rectScreen,rectScreen,tempRect);
		}
	}

	RECTF rectSignal;
	RECTF::Intersect(rectSignal,rect,rectScreen);
	return rectSignal;
}

RECTF XCaculateSplitManage::CalculateInsertScreenRect(VEC_SPLITSCREEN& VecScreen)
{
	RECTF rectScreen;
	BOOL bFirst=TRUE;
	for(auto& pScreen:VecScreen)
	{
		RECTF tempRect=pScreen->GetRect();
		if(bFirst)
		{
			rectScreen=tempRect;
			bFirst=FALSE;
		}
		else
		{
			rectScreen.Union(rectScreen,rectScreen,tempRect);
		}
	}
	return rectScreen;
}

RECTF XCaculateSplitManage::CalculateBolckRect(RECTF& rect,VEC_SPLITSCREEN& VecScreen)
{

	//1.先分块
	std::vector<RECTF> VecBolckRect;
	for(auto& pScreen:VecScreen)
	{
		RECTF rectScreen=pScreen->GetRect();

		RECTF r1(rectScreen.X,rectScreen.Y,rectScreen.Width/2,rectScreen.Height/2);
		VecBolckRect.push_back(r1);
		RECTF r2(rectScreen.X+rectScreen.Width/2,rectScreen.Y,rectScreen.Width/2,rectScreen.Height/2);
		VecBolckRect.push_back(r2);

		RECTF r3(rectScreen.X,rectScreen.Y+rectScreen.Height/2,rectScreen.Width/2,rectScreen.Height/2);
		VecBolckRect.push_back(r3);

		RECTF r4(rectScreen.X+rectScreen.Width/2,rectScreen.Y+rectScreen.Height/2,rectScreen.Width/2,rectScreen.Height/2);
		VecBolckRect.push_back(r4);
	}

	//2.求相交
	std::vector<RECTF> VecIntersect;
	for(auto& rt:VecBolckRect)
	{
		RECTF temp=rt;
		if(rt.Intersect(rect))
		{
			VecIntersect.push_back(temp);
		}
	}
	//3.
	RECTF rectRet;
	BOOL bFirst=TRUE;
	for(auto& rectBlock:VecIntersect)
	{
		if(bFirst)
		{
			rectRet=rectBlock;
			bFirst=FALSE;
		}
		else
		{
			rectRet.Union(rectRet,rectRet,rectBlock);
		}
	}

	return rectRet;
}

XSignal* XCaculateSplitManage::DecidePointInSignal(XSplitManage* pManage,POINTF& point)
{
	auto& VecSignal=pManage->GetVecSignal();	
	for(auto iter=VecSignal.rbegin();iter!=VecSignal.rend();++iter)
	{
		XSignal* pSignal=*iter;
		RECTF rect=pSignal->GetRect();
		if(rect.Contains(point))
		{
			return pSignal;
		}
	}
	return NULL;
}

XSplitScreen* XCaculateSplitManage::DecidePointInScreen(XSplitManage* pManage,POINTF& point)
{
	auto& VecScreen=pManage->GetVecScreen();
	for(auto& pScreen:VecScreen)
	{
		RECTF rect=pScreen->GetRect();
		if(rect.Contains(point))
		{
			return pScreen;
		}
	}
	return NULL;
}

BOOL XCaculateSplitManage::DecidePointInColse(XSignal* pSignal,POINTF& point)
{
	RECTF rectClose=pSignal->GetRectColse();
	if(rectClose.Contains(point))
		return TRUE;
	else
		return FALSE;
}

BOOL XCaculateSplitManage::DecidePointInMenu(XSignal* pSignal,POINTF& point)
{
	RECTF rectMenu=pSignal->GetRectMenu();
	if(rectMenu.Contains(point))
		return TRUE;
	else
		return FALSE;
}

BOOL XCaculateSplitManage::DecidePointInTitle(XSignal* pSignal,POINTF& point)
{
	RECTF rectUp=pSignal->GetRectUP();
	if(rectUp.Contains(point))
		return TRUE;
	else
		return FALSE;
}

BOOL XCaculateSplitManage::DecidePointInMax(XSignal* pSignal,POINTF& point)
{
	RECTF rectUp=pSignal->GetRectMax();
	if(rectUp.Contains(point))
		return TRUE;
	else
		return FALSE;
}

BOOL XCaculateSplitManage::DecidePointInMin(XSignal* pSignal,POINTF& point)
{
	RECTF rectUp=pSignal->GetRectMin();
	if(rectUp.Contains(point))
		return TRUE;
	else
		return FALSE;
}

BOOL XCaculateSplitManage::DecidePointInFull(XSignal* pSignal,POINTF& point)
{
	RECTF rectUp=pSignal->GetRectFull();
	if(rectUp.Contains(point))
		return TRUE;
	else
		return FALSE;
}

void XCaculateSplitManage::MoveSignal(POSITIONTYPE PositionType,RECTF& rect,SIZEF& size)
{
	float nRate=1.0*rect.Width/rect.Height;
	float nRateReciprocal=1.0*rect.Height/rect.Width;

	switch(PositionType)
	{
		case POSITIONTYPE_LT:
			{
				rect.X+=size.Width;
				rect.Width=rect.Width-size.Width;
				rect.Y+=size.Height;
				rect.Height-=size.Height;
			}
			break;
		case POSITIONTYPE_RT:
			{
				rect.Y+=size.Height;
				rect.Width+=size.Width;
				rect.Height-=size.Height;
			}
			break;
		case POSITIONTYPE_LB:
			{
				rect.X+=size.Width;
				rect.Width-=size.Width;
				rect.Height+=size.Height;
			}
			break;
		case POSITIONTYPE_RB:
			{
				rect.Width+=size.Width;
				rect.Height+=size.Height;
			}
			break;
		case POSITIONTYPE_L:
			{
				rect.X+=size.Width;
				rect.Width=rect.Width-size.Width;
			}
			break;
		case POSITIONTYPE_R:
			{
				rect.Width+=size.Width;
			}
			break;
		case POSITIONTYPE_T:
			{
				rect.Y+=size.Height;
				rect.Height-=size.Height;
			}
			break;
		case POSITIONTYPE_B:
			{
				rect.Height+=size.Height;
			}
			break;
		default:
			{
				rect.Offset(size.Width,size.Height);
			}
			break;
	}
}

POSITIONTYPE XCaculateSplitManage::DecidePointInSignalPosition(XSplitManage* pManage,RECTF& rect,POINTF& point)
{
	double dwScale=pManage->GetScale();
	int nDistance=(int)(5/dwScale);
	if((point.X-rect.GetLeft())<=nDistance)
	{
		if(point.Y-rect.GetTop()<=nDistance)
		{
			return POSITIONTYPE_LT;
		}
		else if((rect.GetBottom()-point.Y)<=nDistance)
		{
			return POSITIONTYPE_LB;
		}
		else
		{
			return POSITIONTYPE_L;
		}
	}
	else if((rect.GetRight()-point.X)<=nDistance)
	{
		if((point.Y-rect.GetTop())<=nDistance)
		{
			return POSITIONTYPE_RT;
		}
		else if((rect.GetBottom()-point.Y)<=nDistance)
		{
			return POSITIONTYPE_RB;
		}
		else
		{
			return POSITIONTYPE_R;
		}
	}
	else if((point.Y-rect.GetTop())<=nDistance)
	{
		return POSITIONTYPE_T;
	}
	else if((rect.GetBottom()-point.Y)<=nDistance)
	{
		return POSITIONTYPE_B;
	}

	return POSITIONTYPE_NULL;
}

CURSORTYPE XCaculateSplitManage::GetCursorTypeByPositionType(POSITIONTYPE positionType)
{
	CURSORTYPE cursortype=CURSORTYPE_NULL;

	switch(positionType)
	{
		case POSITIONTYPE_LT:
			{
				cursortype=CURSORTYPE_NWSE;
			}
			break;
		case POSITIONTYPE_LB:
			{
				cursortype=CURSORTYPE_NESW;
			}
			break;
		case POSITIONTYPE_RT:
			{
				cursortype=CURSORTYPE_NESW;
			}
			break;
		case POSITIONTYPE_RB:
			{
				cursortype=CURSORTYPE_NWSE;
			}
			break;
		case POSITIONTYPE_L:
			{
				cursortype=CURSORTYPE_WE;
			}
			break;
		case POSITIONTYPE_R:
			{
				cursortype=CURSORTYPE_WE;
			}
			break;
		case POSITIONTYPE_T:
			{
				cursortype=CURSORTYPE_NS;
			}
			break;
		case POSITIONTYPE_B:
			{
				cursortype=CURSORTYPE_NS;
			}
			break;
		default:
			{
				cursortype=CURSORTYPE_NORMAL;
			}
			break;
	}
	return cursortype;
}

HCURSOR XCaculateSplitManage::GetCursor(CURSORTYPE type)
{
	HCURSOR cursor=NULL;

	switch(type)
	{
		case CURSORTYPE_NORMAL:
			cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));
			break;
		case CURSORTYPE_MOVE:
			cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZEALL));
			break;
		case CURSORTYPE_NESW:
			cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZENESW));
			break;
		case CURSORTYPE_NS:
			cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZENS));
			break;
		case CURSORTYPE_NWSE:
			cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZENWSE));
			break;
		case CURSORTYPE_WE:
			cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZEWE));
			break;
		default:
			break;
	}
	return cursor;

}