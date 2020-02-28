#include "stdafx.h"
#include "XCaculateNodeManage.h"
#include "XNodeManage.h"
#include "HandleCalculate.h"
#include "XNode.h"
#include "XOutResoluation.h"


XCaculateNodeManage::XCaculateNodeManage()
{

}

XCaculateNodeManage::~XCaculateNodeManage()
{

}

CSize XCaculateNodeManage::ViewGetSize(XNodeManage* pManage)
{
	float dwScale=pManage->GetScale();

	//TRACE(_T("nCountH=%d,nCountV=%d\n"),nCountH,nCountV);

	//int nWight=(GetWidthOfNodeIn(pManage)>=GetWidthOfNodeOut(pManage))?GetWidthOfNodeIn(pManage):GetWidthOfNodeOut(pManage);
	//int nHeight=GetHightOfNodeIn(pManage)+GetHightOfNodeOut(pManage)+DISTANCE;
	int nWight=PIC_WIDTH;
	int nHeight=PIC_HEIGHT+GetHightOfNodeIn(pManage)+GetHightOfNodeOut(pManage)+DISTANCE;
	//int nWight=1240;

	CSize size;
	size.cx=LONG(DRAWDISTANCE_X*2+nWight*dwScale);
	size.cy=LONG(DRAWDISTANCE_Y*2+nHeight*dwScale);

	//TRACE(_T("size XCaculateNodeManage X=%d,sizeY=%d\n"),size.cx,size.cy);
	//TRACE(_T("X=%d,Y=%d\n"),GetHightOfNodeIn(pManage),GetHightOfNodeOut(pManage));

	return size;
}

void XCaculateNodeManage::SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CDC& dc)
{
	HandleCalculate::SetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,dc);
}

void XCaculateNodeManage::ReductionPoint(XNodeManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint)
{
	CSize size=pManage->ViewGetSize();
	float dwScale=pManage->GetScale();

	int nResolutionH=NODE_WIDTH;
	int nResolutionV=NODE_HEIGHT;

	float dwScaleResolutionH=NODE_WIDTH*dwScale;
	float dwScaleResolutionV=NODE_HEIGHT*dwScale;

	int nOrgX=0;
	int nOrgY=0;

	GetViewPortOrg(rect,nOffsetX,nOffsetY,size,dwScale,nOrgX,nOrgY);

	int nTempX=srcPoint.x-nOrgX;
	int nTempY=(int)(srcPoint.y-nOrgY-PIC_HEIGHT*dwScale-DISTANCE_V);

	desPoint.X=(float)(1.0f*nResolutionH/dwScaleResolutionH*nTempX);
	desPoint.Y=(float)(1.0f*nResolutionV/dwScaleResolutionV*nTempY);
	//TRACE(_T("X=%f,Y=%f\n"),desPoint.X,desPoint.Y);
}

void XCaculateNodeManage::GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,int& nOrgX,int& nOrgY)
{
	HandleCalculate::GetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,DRAWDISTANCE_X,DRAWDISTANCE_Y,nOrgX,nOrgY);
}

BOOL XCaculateNodeManage::DecidePointInNode(XNodeManage* pManage,POINTF& point)
{
	MAP_NODE& MapNode=pManage->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		CRect rect=pNode->GetRect();

		CPoint tempPoint((int)point.X,(int)point.Y);
		if(rect.PtInRect(tempPoint))
		{
			return TRUE;
		}
	}

	return FALSE;
}

XNode* XCaculateNodeManage::GetNodeByPoint(XNodeManage* pManage,POINTF& point)
{
	MAP_NODE& MapNode=pManage->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		CRect rect=pNode->GetRect();

		CPoint TempPoint((int)point.X,(int)point.Y);

		if(rect.PtInRect(TempPoint))
			return pNode;
	}

	return NULL;
}

void XCaculateNodeManage::MoveSignal(RECTF& rect,SIZEF& size)
{
	rect.Offset(size.Width,size.Height);
}

int XCaculateNodeManage::GetHightOfNodeIn(XNodeManage* pManage)
{
	MAP_NODE& MapNode=pManage->GetMapNode();
	int nIndex=0;
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_IN)
		{
			nIndex++;
		}
	}

	int nCountH=0;
	int nCountV=0;
	if(nIndex<=NODECOUNT_H)
	{
		nCountH=nIndex;
		nCountV=((nIndex%NODECOUNT_H)==0)?(nIndex/NODECOUNT_H):(nIndex/NODECOUNT_H+1);
	}
	else
	{
		nCountH=NODECOUNT_H;
		nCountV=((nIndex%NODECOUNT_H)==0)?(nIndex/NODECOUNT_H):(nIndex/NODECOUNT_H+1);
	}

	int nHeight=TEXT_HEIGHT+NODE_HEIGHT*nCountV;

	return nHeight;
}

int XCaculateNodeManage::GetHightOfNodeOut(XNodeManage* pManage)
{
	MAP_NODE& MapNode=pManage->GetMapNode();
	int nIndex=0;
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			nIndex++;
		}
	}

	int nCountH=0;
	int nCountV=0;
	if(nIndex<=NODECOUNT_H)
	{
		nCountH=nIndex;
		nCountV=((nIndex%NODECOUNT_H)==0)?(nIndex/NODECOUNT_H):(nIndex/NODECOUNT_H+1);
	}
	else
	{
		nCountH=NODECOUNT_H;
		nCountV=((nIndex%NODECOUNT_H)==0)?(nIndex/NODECOUNT_H):(nIndex/NODECOUNT_H+1);
	}

	int nHeight=TEXT_HEIGHT+NODE_HEIGHT*nCountV;

	return nHeight;
}

int XCaculateNodeManage::GetWidthOfNodeIn(XNodeManage* pManage)
{
	MAP_NODE& MapNode=pManage->GetMapNode();
	int nIndex=0;
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_IN)
		{
			nIndex++;
		}
	}

	int nCountH=0;
	int nCountV=0;
	if(nIndex<=NODECOUNT_H)
	{
		nCountH=nIndex;
		nCountV=((nIndex%NODECOUNT_H)==0)?(nIndex/NODECOUNT_H):(nIndex/NODECOUNT_H+1);
	}
	else
	{
		nCountH=NODECOUNT_H;
		nCountV=((nIndex%NODECOUNT_H)==0)?(nIndex/NODECOUNT_H):(nIndex/NODECOUNT_H+1);
	}

	int nWidth=nCountH*NODE_WIDTH+(nCountH-1)*DISTANCE;

	return nWidth;
}

int XCaculateNodeManage::GetWidthOfNodeOut(XNodeManage* pManage)
{
	MAP_NODE& MapNode=pManage->GetMapNode();
	int nIndex=0;
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			nIndex++;
		}
	}

	int nCountH=0;
	int nCountV=0;
	if(nIndex<=NODECOUNT_H)
	{
		nCountH=nIndex;
		nCountV=((nIndex%NODECOUNT_H)==0)?(nIndex/NODECOUNT_H):(nIndex/NODECOUNT_H+1);
	}
	else
	{
		nCountH=NODECOUNT_H;
		nCountV=((nIndex%NODECOUNT_H)==0)?(nIndex/NODECOUNT_H):(nIndex/NODECOUNT_H+1);
	}

	int nWidth=nCountH*NODE_WIDTH+(nCountH-1)*DISTANCE;

	return nWidth;
}

void XCaculateNodeManage::InitMapResoluationInfo(XNodeManage* pManage)
{
	MAP_RESULATIONINFO& MapResoluationInfo=pManage->GetMapResoluationInfo();

	//添加到集合 0
	XOutResoluation* pInfo=new XOutResoluation;
	pInfo->SetValue(0x00);
	pInfo->SetModel(0);
	pInfo->SetResoluationH(1920*2);
	pInfo->SetResoluationV(1080*2);
	pInfo->SetRefreashRate(30);
	pInfo->SetName(_T("4K 30Hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(0,pInfo));
	//1
	XOutResoluation* pInfo1=new XOutResoluation;
	pInfo1->SetValue(0x01);
	pInfo1->SetModel(0);
	pInfo1->SetResoluationH(1920);
	pInfo1->SetResoluationV(1080);
	pInfo1->SetRefreashRate(60);
	pInfo1->SetName(_T("1080p 60Hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(1,pInfo1));
	//2
	XOutResoluation* pInfo2=new XOutResoluation;
	pInfo2->SetValue(0x02);
	pInfo2->SetModel(0);
	pInfo2->SetResoluationH(1920);
	pInfo2->SetResoluationV(1080);
	pInfo2->SetRefreashRate(50);
	pInfo2->SetName(_T("1080p 50Hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(2,pInfo2));
	//3
	XOutResoluation* pInfo3=new XOutResoluation;
	pInfo3->SetValue(0x03);
	pInfo3->SetModel(0);
	pInfo3->SetResoluationH(1920);
	pInfo3->SetResoluationV(1080);
	pInfo3->SetRefreashRate(30);
	pInfo3->SetName(_T("1080p 30Hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(3,pInfo3));
	//4
	XOutResoluation* pInfo4=new XOutResoluation;
	pInfo4->SetValue(0x04);
	pInfo4->SetModel(0);
	pInfo4->SetResoluationH(1920);
	pInfo4->SetResoluationV(1080);
	pInfo4->SetRefreashRate(25);
	pInfo4->SetName(_T("1080p 25Hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(4,pInfo4));
	//5
	XOutResoluation* pInfo5=new XOutResoluation;
	pInfo5->SetValue(0x05);
	pInfo5->SetModel(1);
	pInfo5->SetResoluationH(1920);
	pInfo5->SetResoluationV(1080);
	pInfo5->SetRefreashRate(60);
	pInfo5->SetName(_T("1080i 60Hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(5,pInfo5));
	//6
	XOutResoluation* pInfo6=new XOutResoluation;
	pInfo6->SetValue(0x06);
	pInfo6->SetModel(1);
	pInfo6->SetResoluationH(1920);
	pInfo6->SetResoluationV(1080);
	pInfo6->SetRefreashRate(50);
	pInfo6->SetName(_T("1080i 50Hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(6,pInfo6));
	//7
	XOutResoluation* pInfo7=new XOutResoluation;
	pInfo7->SetValue(0x07);
	pInfo7->SetModel(0);
	pInfo7->SetResoluationH(1280);
	pInfo7->SetResoluationV(720);
	pInfo7->SetRefreashRate(60);
	pInfo7->SetName(_T("720p 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(7,pInfo7));
	//8
	XOutResoluation* pInfo8=new XOutResoluation;
	pInfo8->SetValue(0x08);
	pInfo8->SetModel(0);
	pInfo8->SetResoluationH(1920);
	pInfo8->SetResoluationV(1200);
	pInfo8->SetRefreashRate(60);
	pInfo8->SetName(_T("1920*1200 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(8,pInfo8));
	//9
	XOutResoluation* pInfo9=new XOutResoluation;
	pInfo9->SetValue(0x09);
	pInfo9->SetModel(0);
	pInfo9->SetResoluationH(1680);
	pInfo9->SetResoluationV(1050);
	pInfo9->SetRefreashRate(60);
	pInfo9->SetName(_T("1680*1050 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(9,pInfo9));
	//10
	XOutResoluation* pInfo10=new XOutResoluation;
	pInfo10->SetValue(0x0A);
	pInfo10->SetModel(0);
	pInfo10->SetResoluationH(1600);
	pInfo10->SetResoluationV(1200);
	pInfo10->SetRefreashRate(60);
	pInfo10->SetName(_T("1440*900 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(10,pInfo10));
	//11
	XOutResoluation* pInfo11=new XOutResoluation;
	pInfo11->SetValue(0x0B);
	pInfo11->SetModel(0);
	pInfo11->SetResoluationH(1440);
	pInfo11->SetResoluationV(900);
	pInfo11->SetRefreashRate(60);
	pInfo11->SetName(_T("1440*900 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(11,pInfo11));
	//12
	XOutResoluation* pInfo12=new XOutResoluation;
	pInfo12->SetValue(0x0C);
	pInfo12->SetModel(0);
	pInfo12->SetResoluationH(1366);
	pInfo12->SetResoluationV(768);
	pInfo12->SetRefreashRate(60);
	pInfo12->SetName(_T("1366*768 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(12,pInfo12));
	//13
	XOutResoluation* pInfo13=new XOutResoluation;
	pInfo13->SetValue(0x0D);
	pInfo13->SetModel(0);
	pInfo13->SetResoluationH(1360);
	pInfo13->SetResoluationV(768);
	pInfo13->SetRefreashRate(60);
	pInfo13->SetName(_T("1360*768 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(13,pInfo13));
	//14
	XOutResoluation* pInfo14=new XOutResoluation;
	pInfo14->SetValue(0x0E);
	pInfo14->SetModel(0);
	pInfo14->SetResoluationH(1280);
	pInfo14->SetResoluationV(768);
	pInfo14->SetRefreashRate(60);
	pInfo14->SetName(_T("1280*768 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(14,pInfo14));
	//15
	XOutResoluation* pInfo15=new XOutResoluation;
	pInfo15->SetValue(0x0F);
	pInfo15->SetModel(0);
	pInfo15->SetResoluationH(1024);
	pInfo15->SetResoluationV(768);
	pInfo15->SetRefreashRate(60);
	pInfo15->SetName(_T("1024*768 60hz"));
	MapResoluationInfo.insert(std::pair<int,XOutResoluation*>(15,pInfo15));
}

void XCaculateNodeManage::InitKeyValue(XNodeManage* pManage)
{
	MAP_KEYVALUE& MapKeyValue=pManage->GetMapKeyValue();

	MapKeyValue.insert(std::pair<CString,int>(_T("A"),0x04));
	MapKeyValue.insert(std::pair<CString,int>(_T("B"),0x05));
	MapKeyValue.insert(std::pair<CString,int>(_T("C"),0x06));
	MapKeyValue.insert(std::pair<CString,int>(_T("D"),0x07));
	MapKeyValue.insert(std::pair<CString,int>(_T("E"),0x08));
	MapKeyValue.insert(std::pair<CString,int>(_T("F"),0x09));
	MapKeyValue.insert(std::pair<CString,int>(_T("G"),0x0A));
	MapKeyValue.insert(std::pair<CString,int>(_T("H"),0x0B));
	MapKeyValue.insert(std::pair<CString,int>(_T("I"),0x0C));
	MapKeyValue.insert(std::pair<CString,int>(_T("J"),0x0D));
	MapKeyValue.insert(std::pair<CString,int>(_T("K"),0x0E));
	MapKeyValue.insert(std::pair<CString,int>(_T("L"),0x0F));
	MapKeyValue.insert(std::pair<CString,int>(_T("M"),0x10));
	MapKeyValue.insert(std::pair<CString,int>(_T("N"),0x11));
	MapKeyValue.insert(std::pair<CString,int>(_T("O"),0x12));
	MapKeyValue.insert(std::pair<CString,int>(_T("P"),0x13));
	MapKeyValue.insert(std::pair<CString,int>(_T("Q"),0x14));
	MapKeyValue.insert(std::pair<CString,int>(_T("R"),0x15));
	MapKeyValue.insert(std::pair<CString,int>(_T("S"),0x16));
	MapKeyValue.insert(std::pair<CString,int>(_T("T"),0x17));
	MapKeyValue.insert(std::pair<CString,int>(_T("U"),0x18));
	MapKeyValue.insert(std::pair<CString,int>(_T("V"),0x19));
	MapKeyValue.insert(std::pair<CString,int>(_T("W"),0x1A));
	MapKeyValue.insert(std::pair<CString,int>(_T("X"),0x1B));
	MapKeyValue.insert(std::pair<CString,int>(_T("Y"),0x1C));
	MapKeyValue.insert(std::pair<CString,int>(_T("Z"),0x1D));
													  
	MapKeyValue.insert(std::pair<CString,int>(_T("1"),0x1E));
	MapKeyValue.insert(std::pair<CString,int>(_T("2"),0x1F));
	MapKeyValue.insert(std::pair<CString,int>(_T("3"),0x20));
	MapKeyValue.insert(std::pair<CString,int>(_T("4"),0x21));
	MapKeyValue.insert(std::pair<CString,int>(_T("5"),0x22));
	MapKeyValue.insert(std::pair<CString,int>(_T("6"),0x23));
	MapKeyValue.insert(std::pair<CString,int>(_T("7"),0x24));
	MapKeyValue.insert(std::pair<CString,int>(_T("8"),0x25));
	MapKeyValue.insert(std::pair<CString,int>(_T("9"),0x26));
	MapKeyValue.insert(std::pair<CString,int>(_T("0"),0x27));

	//MapKeyValue.insert(std::pair<CString,int>(_T("F1"),0x3A));
	MapKeyValue.insert(std::pair<CString,int>(_T("F2"),0x3B));
	//MapKeyValue.insert(std::pair<CString,int>(_T("F3"),0x3C));
	MapKeyValue.insert(std::pair<CString,int>(_T("F4"),0x3D));
	//MapKeyValue.insert(std::pair<CString,int>(_T("F5"),0x3E));
	//MapKeyValue.insert(std::pair<CString,int>(_T("F6"),0x3F));
	MapKeyValue.insert(std::pair<CString,int>(_T("F7"),0x40));
	MapKeyValue.insert(std::pair<CString,int>(_T("F8"),0x41));
	MapKeyValue.insert(std::pair<CString,int>(_T("F9"),0x42));
	MapKeyValue.insert(std::pair<CString,int>(_T("F10"),0x43));
	MapKeyValue.insert(std::pair<CString,int>(_T("F11"),0x44));
	MapKeyValue.insert(std::pair<CString,int>(_T("F12"),0x45));

	//MapKeyValue.insert(std::pair<CString,int>(_T("上箭头"),0x52));
	//MapKeyValue.insert(std::pair<CString,int>(_T("下箭头"),0x51));
	//MapKeyValue.insert(std::pair<CString,int>(_T("左箭头"),0x50));
	//MapKeyValue.insert(std::pair<CString,int>(_T("右箭头"),0x4F));

	MapKeyValue.insert(std::pair<CString,int>(_T("数字键1"),0x59));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键2"),0x5A));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键3"),0x5B));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键4"),0x5C));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键5"),0x5D));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键6"),0x5E));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键7"),0x5F));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键8"),0x60));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键9"),0x61));
	MapKeyValue.insert(std::pair<CString,int>(_T("数字键0"),0x62));
}

HCURSOR XCaculateNodeManage::GetCursor(CURSORTYPE type)
{
	HCURSOR cursor=NULL;

	switch(type)
	{
		case CURSORTYPE_NORMAL:
			{
				cursor=LoadCursor(NULL,(LPCWSTR)MAKEINTRESOURCE(IDC_ARROW));
				break;
			}
		case CURSORTYPE_MOVE:
			{
				cursor=LoadCursor(NULL,(LPCWSTR)MAKEINTRESOURCE(IDC_SIZEALL));
				break;
			}
		case CURSORTYPE_NESW:
			{
				cursor=LoadCursor(NULL,(LPCWSTR)MAKEINTRESOURCE(IDC_SIZENESW));
				break;
			}
		case CURSORTYPE_NS:
			{
				cursor=LoadCursor(NULL,(LPCWSTR)MAKEINTRESOURCE(IDC_SIZENS));
				break;
			}
		case CURSORTYPE_NWSE:
			{
				cursor=LoadCursor(NULL,(LPCWSTR)MAKEINTRESOURCE(IDC_SIZENWSE));
				break;
			}
		case CURSORTYPE_WE:
			{
				cursor=LoadCursor(NULL,(LPCWSTR)MAKEINTRESOURCE(IDC_SIZEWE));
				break;
			}
		case CURSORTYPE_HAND:
			{
				cursor=LoadCursor(NULL,(LPCWSTR)MAKEINTRESOURCE(IDC_HAND));
				break;
			}
		default:
			break;
	}

	return cursor;
}