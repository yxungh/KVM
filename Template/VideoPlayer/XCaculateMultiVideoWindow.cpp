#include "stdafx.h"
#include "XCaculateMultiVideoWindow.h"
#include "XMultiVideoWindow.h"

XCaculateMultiVideoWindow::XCaculateMultiVideoWindow()
{

}

XCaculateMultiVideoWindow::~XCaculateMultiVideoWindow()
{

}

CSize XCaculateMultiVideoWindow::ViewGetSize(XMultiVideoWindow* p)
{
	float fScale=p->GetMultiVideoWindowScale();

	CSize size;
	size.cx=LONG(DRAWDISTANCE_X*2+PAGE_WIDTH*fScale);
	size.cy=LONG(DRAWDISTANCE_Y*2+PAGE_HEIGHT*fScale);

	//TRACE(_T("sizeX=%d,sizeY=%d\n"),size.cx,size.cy);
	return size;
}

void XCaculateMultiVideoWindow::SetPageOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CSize& orgSize)
{
	SetPageOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,orgSize);
}

void XCaculateMultiVideoWindow::SetPageOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,const int& nDrawDistanceX,
										   const int& nDrawDistanceY,CSize& orgSize)
{
	int nOrgX=0;
	int nOrgY=0;

	GetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,nDrawDistanceX,nDrawDistanceY,nOrgX,nOrgY);

	orgSize.cx=nOrgX;
	orgSize.cy=nOrgY;
}

void XCaculateMultiVideoWindow::GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,
											   CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,int& nOrgX,int& nOrgY)
{
	int nWidth=rect.Width();
	int nHeight=rect.Height();

	if(nWidth>size.cx)
	{
		nOrgX=(nWidth-size.cx)/2;
	}
	else
	{
		nOrgX=0;
	}

	if(nHeight>size.cy)
	{
		nOrgY=(nHeight-size.cy)/2;
	}
	else
	{
		nOrgY=0;
	}

	nOrgX=nOrgX-noffsetX+nDrawDistanceX;
	nOrgY=nOrgY-noffsetY+nDrawDistanceY;
}