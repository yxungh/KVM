#include "stdafx.h"
#include "XDrawSeatArrageManage.h"
#include "XSeatArrageManage.h"
#include "XCaculateSeatArrageManage.h"
#include "XSeat.h"
#include "XConstantData.h"

XDrawSeatArrageManage::XDrawSeatArrageManage()
{

}

XDrawSeatArrageManage::~XDrawSeatArrageManage()
{

}

void XDrawSeatArrageManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XSeatArrageManage* pSeatArrageManage)
{
//	float dwScale=pSeatArrageManage->GetScale();	
//	CSize size=pSeatArrageManage->ViewGetSize();
//
//	int nWidth=rect.Width();
//	int nHeight=rect.Height();
//
//	HDC hdc=pDC->GetSafeHdc();
//	CDC tempDC;
//	tempDC.CreateCompatibleDC(pDC);
//
//	XCaculateSeatArrageManage::SetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,tempDC);
//
//	HDC hMemdc=tempDC.GetSafeHdc();
//	HBITMAP hMembmp=CreateCompatibleBitmap(hdc,nWidth,nHeight);
//	HBITMAP hOldbmp=(HBITMAP)SelectObject(hMemdc,hMembmp);
//	Graphics graphics(hMemdc);
//
//	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
//	graphics.Clear(pSeatArrageManage->GetViewColor());
//
//	DrawSeat(graphics,pSeatArrageManage);
//
//	if(pSeatArrageManage->GetCreateDragRect())
//	{
//		DrawDrag(graphics,pSeatArrageManage);
//	}
//
//	BitBlt(hdc, noffsetX, noffsetY, nWidth, nHeight, hMemdc, 0, 0, SRCCOPY);
//	graphics.ReleaseHDC(hMemdc);
//	SelectObject(hMemdc, hOldbmp);
//	tempDC.DeleteDC();
//	DeleteObject(hMembmp);
//}
//
//void XDrawSeatArrageManage::DrawSeat(Graphics& graphics,XSeatArrageManage* pSeatArrageManage)
//{
//	float dwScale=pSeatArrageManage->GetScale();
//
//	graphics.SetTextRenderingHint(TextRenderingHintSystemDefault);  
//
//	//没添加节点
//	Gdiplus::Pen pen(Gdiplus::Color(200,151,189,216),0.5f);//直线画笔
//	Gdiplus::Pen penLine(Gdiplus::Color(255,0,0,0),0.5f);//直线画笔
//	Gdiplus::Pen penSelect(Gdiplus::Color(255,255,0,0),1.0f);//直线画笔
//	Gdiplus::Pen penMaster(Gdiplus::Color(255,255,97,0),1.0f);//直线画笔
//	Gdiplus::SolidBrush brush(Gdiplus::Color(150,203,221,236));//区域颜色
//	//Gdiplus::SolidBrush brush(Gdiplus::Color(50,0,255,0));//区域颜色
//	Gdiplus::SolidBrush brushNoFeasible(Gdiplus::Color(50,255,0,0));//不可行区域颜色
//
//	//添加节点
//	Gdiplus::Pen penNode(Gdiplus::Color(255,255,125,255),1.0f);//直线画笔
//	Gdiplus::SolidBrush brushNode(Gdiplus::Color(255,41,57,85));//区域颜色
//	//Gdiplus::SolidBrush brushMaster(Gdiplus::Color(255,65,105,225));//区域颜色
//
//	float dwTextSize=10*dwScale;
//	Gdiplus::FontFamily fontfamily(APP_FONT);
//	Gdiplus::Font font(&fontfamily, dwTextSize, FontStyleRegular,UnitPoint);
//	Gdiplus::SolidBrush textbrush(Color(255,91,155,213));
//	Gdiplus::SolidBrush textMaster(Color(255,255,0,0));
//	Gdiplus::SolidBrush namebrush(Color(255,255,255,255));
//
//	Gdiplus::StringFormat stringForamt;
//	stringForamt.SetAlignment(StringAlignmentCenter);
//	stringForamt.SetLineAlignment(StringAlignmentCenter);
//
//	Gdiplus::StringFormat stringForamtIndex;
//	stringForamtIndex.SetAlignment(StringAlignmentFar);
//	stringForamtIndex.SetLineAlignment(StringAlignmentFar);
//
//
//	VEC_SEAT& VecSeat=pSeatArrageManage->GetVecSeat();
//	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
//	{
//		XSeat* pSeat=*iter;
//		CRect rect=pSeat->GetRect();
//
//		RECTF drawRect(rect.left*dwScale,rect.top*dwScale,rect.Width()*dwScale,rect.Height()*dwScale);
//		if(pSeat->GetFeasible())
//		{
//			if(!pSeat->GetAddNode())
//			{
//				graphics.FillRectangle(&brush,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
//			}
//			else
//			{
//				graphics.FillRectangle(&brushNode,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
//
//				//绘制文字
//				CString szNodeName=pSeat->GetNodeName();
//				graphics.DrawString(szNodeName,-1,&font,drawRect,&stringForamt,&textbrush);
//
//				int nSeatIndex=pSeat->GetSeatIndex();
//				if(nSeatIndex!=0)
//				{
//					CString szSeatIndex;
//					szSeatIndex.Format(_T("%d"),nSeatIndex);
//
//					if(pSeat->GetMaster())
//					{
//						graphics.DrawString(szSeatIndex,-1,&font,drawRect,&stringForamtIndex,&textMaster);
//					}
//					else
//					{
//						graphics.DrawString(szSeatIndex,-1,&font,drawRect,&stringForamtIndex,&textbrush);
//					}
//				}
//			}
//
//			if(!pSeat->GetSelected())
//			{
//				graphics.DrawRectangle(&pen,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
//			}
//			else
//			{
//				graphics.DrawRectangle(&penSelect,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
//			}
//		}
//		else
//		{
//			graphics.FillRectangle(&brushNoFeasible,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
//		}
//	}
}

void XDrawSeatArrageManage::DrawDrag(Graphics& graphics,XSeatArrageManage* pSeatArrageManage)
{
//	float dwScale=pSeatArrageManage->GetScale();
//	RECTF rect=pSeatArrageManage->GetDragRect();
//
//	graphics.SetTextRenderingHint(TextRenderingHintSystemDefault);  
//	Gdiplus::SolidBrush brush(Gdiplus::Color(255,41,57,85));
//	Gdiplus::Pen pen(Gdiplus::Color(255,0,0,0),1.0f);
//	Gdiplus::SolidBrush textbrush(Color(255,151,189,216));
//
//	float dwTextSize=10*dwScale;
//	Gdiplus::FontFamily fontfamily(APP_FONT);
//	Gdiplus::Font font(&fontfamily,dwTextSize,FontStyleRegular,UnitPoint);
//
//	Gdiplus::StringFormat stringForamt;
//	stringForamt.SetAlignment(StringAlignmentCenter);
//	stringForamt.SetLineAlignment(StringAlignmentCenter);
//
//	RECTF drawRect(rect.X*dwScale,rect.Y*dwScale,rect.Width*dwScale,rect.Height*dwScale);
//
//	graphics.FillRectangle(&brush,drawRect);
//	//graphics.DrawRectangle(&pen,rect);
//
//	//////////////////////////////////////////////////////////////////////////
//	//文字
//	//int nNodeType=XConstantData::GetInstance()->GetNodeType();
//	//int nNodeID=XConstantData::GetInstance()->GetNodeID();
//	CString szText=XConstantData::GetInstance()->GetNodeName();
//
//	graphics.DrawString(szText,-1,&font,drawRect,&stringForamt,&textbrush);
}