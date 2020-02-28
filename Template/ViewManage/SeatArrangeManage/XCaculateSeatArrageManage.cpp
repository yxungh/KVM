#include "stdafx.h"
#include "XCaculateSeatArrageManage.h"
#include "XSeatArrageManage.h"
#include "HandleCalculate.h"
#include "XSeat.h"
#include "XPage.h"
#include "XScreen.h"

XCaculateSeatArrageManage::XCaculateSeatArrageManage()
{

}

XCaculateSeatArrageManage::~XCaculateSeatArrageManage()
{

}

CSize XCaculateSeatArrageManage::ViewGetSize(XSeatArrageManage* pManage)
{
	float dwScale=pManage->GetScale();
	//int nWidth=pManage->GetSeatWidth();
	//int nHeight=pManage->GetSeatHeight();

	//int nSeatRow=pManage->GetSeatRow();
	//int nSeatColumn=pManage->GetSeatColumn();

	int nWidth=PAGE_WIDTH;
	int nHeight=PAGE_HEIGHT;

	CSize size;
	size.cx=LONG(DRAWDISTANCE_X*2+nWidth*dwScale);
	size.cy=LONG(DRAWDISTANCE_Y*2+nHeight*dwScale);

	//TRACE(_T("XCaculateSeatArrageManage cx=%d,cy=%d\n"),size.cx,size.cy);

	return size;
}

void XCaculateSeatArrageManage::SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CDC& dc)
{
	HandleCalculate::SetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,dc);
}

void XCaculateSeatArrageManage::SetPageOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CSize& orgSize)
{
	SetPageOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,orgSize);
}

void XCaculateSeatArrageManage::SetPageOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,const int& nDrawDistanceX,
										   const int& nDrawDistanceY,CSize& orgSize)
{
	int nOrgX=0;
	int nOrgY=0;

	GetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,nOrgX,nOrgY);

	orgSize.cx=nOrgX;
	orgSize.cy=nOrgY;
}

void XCaculateSeatArrageManage::ReductionPoint(XSeatArrageManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint)
{
	CSize size=pManage->ViewGetSize();
	float dwScale=pManage->GetScale();

	//int nResolutionH=pManage->GetSeatWidth();
	//int nResolutionV=pManage->GetSeatHeight();

	int nResolutionH=PAGE_WIDTH;
	int nResolutionV=PAGE_HEIGHT;

	float dwScaleResolutionH=PAGE_WIDTH*dwScale;
	float dwScaleResolutionV=PAGE_HEIGHT*dwScale;

	int nOrgX=0;
	int nOrgY=0;

	GetViewPortOrg(rect,nOffsetX,nOffsetY,size,dwScale,nOrgX,nOrgY);

	int nTempX=srcPoint.x-nOrgX;
	int nTempY=srcPoint.y-nOrgY;

	desPoint.X=(float)(1.0f*nResolutionH/dwScaleResolutionH*nTempX);
	desPoint.Y=(float)(1.0f*nResolutionV/dwScaleResolutionV*nTempY);
}

void XCaculateSeatArrageManage::GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,int& nOrgX,int& nOrgY)
{
	HandleCalculate::GetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,nOrgX,nOrgY);
}

void XCaculateSeatArrageManage::MoveSignal(POSITIONTYPE PositionType,RECTF& rect,SIZEF& size)
{
	//RECTF tempRect;

	switch(PositionType)
	{
		case POSITIONTYPE_LT:
			{
				rect.X+=size.Width;
				rect.Y+=size.Height;
				rect.Width=rect.Width-size.Width;
				rect.Height=rect.Height-size.Height;
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



	//////////////////////////////////////////////////////////////////////////
	//rect.Offset(size.Width,size.Height);

	/*float nRate=1.0*rect.Width/rect.Height;
	float nRateReciprocal=1.0*rect.Height/rect.Width;

	switch(PositionType)
	{
	case POSITIONTYPE_LT:
		{
			rect.X+=size.Width;

			float nTemp=1.0*(size.Width)*nRateReciprocal;

			rect.Width=rect.Width-size.Width;

			rect.Y+=nTemp;

			rect.Height-=nTemp;
		}
		break;
	case POSITIONTYPE_RT:
		{
			rect.Y+=size.Height;

			float nTemp=1.0*(size.Height)*nRate;

			rect.Width-=nTemp;

			rect.Height-=size.Height;
		}
		break;
	case POSITIONTYPE_LB:
		{
			rect.X+=size.Width;

			float nTemp=1.0*(size.Width)*nRateReciprocal;

			rect.Width-=size.Width;

			rect.Height-=nTemp;
		}
		break;
	case POSITIONTYPE_RB:
		{
			rect.Width+=size.Width;

			float nTemp=1.0*(size.Width)*nRateReciprocal;

			rect.Height+=nTemp;
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
	}*/
}

void XCaculateSeatArrageManage::MoveSignalOfNew(RECTF& rect,SIZEF& size)
{
	rect.Width+=size.Width;
	rect.Height+=size.Height;
}

HCURSOR XCaculateSeatArrageManage::GetCursor(CURSORTYPE type)
{
	HCURSOR cursor=NULL;

	switch(type)
	{
		case CURSORTYPE_NORMAL:
			{
				cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));
				break;
			}
		case CURSORTYPE_MOVE:
			{
				cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZEALL));
				break;
			}
		case CURSORTYPE_NESW:
			{
				cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZENESW));
				break;
			}
		case CURSORTYPE_NS:
			{
				cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZENS));
				break;
			}
		case CURSORTYPE_NWSE:
			{
				cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZENWSE));
				break;
			}
		case CURSORTYPE_WE:
			{
				cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZEWE));
				break;
			}
		case CURSORTYPE_HAND:
			{
				cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_HAND));
				break;
			}
		case CURSORTYPE_DRAW:
			{
				cursor=LoadCursor(NULL,MAKEINTRESOURCE(IDC_CROSS));
				break;
			}
		default:
			break;
	}

	return cursor;
}

BOOL XCaculateSeatArrageManage::DecidedPointInPage(XSeatArrageManage* pManage,POINTF point)
{
	MAP_PAGE& MapPage=pManage->GetMapPage();
	for(auto iter=MapPage.begin();iter!=MapPage.end();++iter)
	{
		int nFirst=iter->first;
		XPage* pPage=iter->second;

		RECTF rect=pPage->GetRect();
		if(rect.Contains(point))
		{
			return TRUE;
		}
	}
	return FALSE;
}

int XCaculateSeatArrageManage::GetSeatIndex(XSeatArrageManage* pManage)
{
	int nIndex=1;

	while(TRUE)
	{
		if(!DecidedIndexIsExit(pManage,nIndex))
			return nIndex;
		else
			nIndex++;
	}
}

BOOL XCaculateSeatArrageManage::DecidedIndexIsExit(XSeatArrageManage* pManage,int nIndex)
{
	XPage* pPage=pManage->GetCurPage();
	VEC_SEAT& VecSeat=pPage->GetVecSeat();
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pSeat=*iter;
		if(pSeat->GetIndex()==nIndex)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL XCaculateSeatArrageManage::DecidedPointInSeat(XSeatArrageManage* pManage,POINTF point,XSeat*& pSeat)
{
	XPage* pPage=pManage->GetCurPage();
	VEC_SEAT& VecSeat=pPage->GetVecSeat();
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pTemp=*iter;
		RECTF rect=pTemp->GetRect();
		if(rect.Contains(point))
		{
			pSeat=pTemp;
			return TRUE;
		}
	}
	pSeat=NULL;
	return FALSE;
}

XSeat* XCaculateSeatArrageManage::GetSeatByIndex(XSeatArrageManage* pManage,int nIndex)
{
	XPage* pPage=pManage->GetCurPage();
	VEC_SEAT& VecSeat=pPage->GetVecSeat();
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pTemp=*iter;

		if(nIndex==pTemp->GetIndex())
			return pTemp;
	}

	return NULL;
}

BOOL XCaculateSeatArrageManage::DecidedPointInScreen(XSeatArrageManage* pManage,POINTF point,XScreen*& pScreen)
{
	XPage* pPage=pManage->GetCurPage();
	VEC_SCREEN& VecScreen=pPage->GetVecScreen();
	for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pTemp=*iter;
		RECTF rect=pTemp->GetRect();
		if(rect.Contains(point))
		{
			pScreen=pTemp;
			return TRUE;
		}
	}
	pScreen=NULL;
	return FALSE;
}

BOOL XCaculateSeatArrageManage::DecidedNodeInScreen(XSeatArrageManage* pManage,int nNodeID,XScreen*& pTemp)
{
	XPage* pPage=pManage->GetCurPage();
	VEC_SCREEN& VecScreen=pPage->GetVecScreen();
	for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		if(pScreen->GetNodeID()==nNodeID)
		{
			pTemp=pScreen;
			return TRUE;
		}
	}
	pTemp=NULL;
	return FALSE;
}

BOOL XCaculateSeatArrageManage::DecidedFirstOne(XSeatArrageManage* pManage)
{
	XPage* pPage=pManage->GetCurPage();
	VEC_SCREEN& VecScreen=pPage->GetVecScreen();
	for(auto iter=VecScreen.begin();iter!=VecScreen.end();++iter)
	{
		XScreen* pScreen=*iter;
		if(pScreen->GetHas())
			return FALSE;
	}
	return TRUE;
}

POSITIONTYPE XCaculateSeatArrageManage::DecidePointInSeatPosition(XSeatArrageManage* pManage,RECTF& rect,POINTF& point)
{
	float fScale=pManage->GetScale();

	int nDistance=(int)(5/fScale);

	//先计算出8个点
	POINTF pointLT(rect.GetLeft(),rect.GetTop());
	POINTF pointLB(rect.GetLeft(),rect.GetBottom());
	POINTF pointRT(rect.GetRight(),rect.GetTop());
	POINTF pointRB(rect.GetRight(),rect.GetBottom());

	POINTF pointL(rect.GetLeft(),rect.Y+rect.Height/2);
	POINTF pointT(rect.GetLeft()+rect.Width/2,rect.GetTop());
	POINTF pointR(rect.GetRight(),rect.Y+rect.Height/2);
	POINTF pointB(rect.GetLeft()+rect.Width/2,rect.GetBottom());

	if(abs(point.X-pointLT.X)<=nDistance&&abs(point.Y-pointLT.Y)<=nDistance)
		return POSITIONTYPE_LT;
	else if(abs(point.X-pointLB.X)<=nDistance&&abs(point.Y-pointLB.Y)<=nDistance)
		return POSITIONTYPE_LB;
	else if(abs(point.X-pointRT.X)<=nDistance&&abs(point.Y-pointRT.Y)<=nDistance)
		return POSITIONTYPE_RT;
	else if(abs(point.X-pointRB.X)<=nDistance&&abs(point.Y-pointRB.Y)<=nDistance)
		return POSITIONTYPE_RB;
	else if(abs(point.X-pointL.X)<=nDistance&&abs(point.Y-pointL.Y)<=nDistance)
		return POSITIONTYPE_L;
	else if(abs(point.X-pointT.X)<=nDistance&&abs(point.Y-pointT.Y)<=nDistance)
		return POSITIONTYPE_T;
	else if(abs(point.X-pointR.X)<=nDistance&&abs(point.Y-pointR.Y)<=nDistance)
		return POSITIONTYPE_R;
	else if(abs(point.X-pointB.X)<=nDistance&&abs(point.Y-pointB.Y)<=nDistance)
		return POSITIONTYPE_B;

	return POSITIONTYPE_NULL;
}

CURSORTYPE XCaculateSeatArrageManage::GetCursorTypeByPositionType(POSITIONTYPE positionType)
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
				cursortype=CURSORTYPE_MOVE;
			}
			break;
	}
	return cursortype;
}