#include "stdafx.h"
#include "XCaculateMatrixManage.h"
#include "HandleCalculate.h"
#include "XMatrixManage.h"
#include "XMatrixScreen.h"



XCaculateMatrixManage::XCaculateMatrixManage()
{
}

XCaculateMatrixManage::~XCaculateMatrixManage()
{
}

CSize XCaculateMatrixManage::ViewGetSize(XMatrixManage* pManage)
{
	float dwScale=pManage->GetScale();
	int n1=pManage->GetScreenCountH();
	int n2=pManage->GetScreenCountV();


	CSize size;
	size.cx=LONG(DRAWDISTANCE_X*2+pManage->GetScreenWidth()*dwScale*pManage->GetScreenCountH());
	size.cy=LONG(DRAWDISTANCE_Y*2+pManage->GetScreenHeight()*dwScale*pManage->GetScreenCountV());

	return size;
}

void XCaculateMatrixManage::SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CDC& dc)
{
	HandleCalculate::SetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,dc);
}

void XCaculateMatrixManage::GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,int& nOrgX,int& nOrgY)
{
	HandleCalculate::GetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,nOrgX,nOrgY);
}

void XCaculateMatrixManage::ReductionPoint(XMatrixManage* pManage,CRect& rect,int noffsetX,int noffsetY,CPoint& srcPoint,POINTF& desPoint)
{
	CSize size=pManage->ViewGetSize();
	float dwScale=pManage->GetScale();

	int nResolutionH=pManage->GetScreenWidth();
	int nResolutionV=pManage->GetScreenHeight();

	float dwScaleResolutionH=nResolutionH*dwScale;
	float dwScaleResolutionV=nResolutionV*dwScale;

	int nOrgX=0;
	int nOrgY=0;

	GetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,nOrgX,nOrgY);

	int nTempX=srcPoint.x-nOrgX;
	int nTempY=srcPoint.y-nOrgY;

	desPoint.X=(float)(1.0f*nResolutionH/dwScaleResolutionH*nTempX);
	desPoint.Y=(float)(1.0f*nResolutionV/dwScaleResolutionV*nTempY);
}

BOOL XCaculateMatrixManage::DecidePointInScreen(XMatrixManage* pManage,XMatrixScreen*& pTemp,POINTF& point)
{
	VEC_MATRIXSCREEN& VecScreen=pManage->GetVecMatrixScreen();
	for(auto& vec:VecScreen)
	{
		XMatrixScreen* pScreen=vec;
		RECTF rect=pScreen->GetRect();
		if(rect.Contains(point))
		{
			pTemp=pScreen;
			return TRUE;
		}
	}
	pTemp=NULL;
	return FALSE;
}

XMatrixScreen* XCaculateMatrixManage::GetMatrixScreenByPoint(XMatrixManage* pManage,POINTF& point)
{
	VEC_MATRIXSCREEN& VecScreen=pManage->GetVecMatrixScreen();
	for(auto& screen:VecScreen)
	{
		XMatrixScreen* pScreen=screen;
		RECTF rect=pScreen->GetRect();
		if(rect.Contains(point))
		{
			return pScreen;
		}
	}
	return NULL;
}

void XCaculateMatrixManage::Move(RECTF& rect,SIZEF& size)
{
	rect.Offset(size.Width,size.Height);
}