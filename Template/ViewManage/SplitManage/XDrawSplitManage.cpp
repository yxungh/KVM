#include "stdafx.h"
#include "XDrawSplitManage.h"
#include "XSplitManage.h"
#include "XCaculateSplitManage.h"
#include "XSplitScreen.h"
#include "XSplitSignal.h"
#include "XSignal.h"
#include "HandlePath.h"
#include "XTranslationManage.h"



XDrawSplitManage::XDrawSplitManage()
{
}


XDrawSplitManage::~XDrawSplitManage()
{
}

void XDrawSplitManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XSplitManage* pManage)
{
	float dwScale=pManage->GetScale();
	CSize size=pManage->ViewGetSize();

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	HDC hdc=pDC->GetSafeHdc();
	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);

	XCaculateSplitManage::SetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,tempDC);

	HDC hMemdc=tempDC.GetSafeHdc();
	HBITMAP hMembmp=CreateCompatibleBitmap(hdc,nWidth,nHeight);
	HBITMAP hOldbmp=(HBITMAP)SelectObject(hMemdc,hMembmp);
	Graphics graphics(hMemdc);

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.Clear(pManage->GetViewColor());
	//////////////////////////////////////////////////////////////////////////
	DrawScreen(graphics,pManage);
	DrawSignal(graphics,pManage);
	//////////////////////////////////////////////////////////////////////////
	BitBlt(hdc,noffsetX,noffsetY,nWidth,nHeight,hMemdc,0,0,SRCCOPY);
	graphics.ReleaseHDC(hMemdc);
	SelectObject(hMemdc,hOldbmp);
	tempDC.DeleteDC();
	DeleteObject(hMembmp);
}

void XDrawSplitManage::DrawScreen(Graphics& graphics,XSplitManage* pManage)
{
	float dwScale=pManage->GetScale();

	Gdiplus::Pen pen(Gdiplus::Color(255,151,190,217));//直线画笔
	Gdiplus::Pen pen1(Gdiplus::Color(255,255,255,255),2.0f);
	Gdiplus::Pen penSignal(Gdiplus::Color(255,0,0,0));//直线画笔

	Gdiplus::Pen penMiddle(Gdiplus::Color(255,200,200,200),1.0f);//虚线画笔
	penMiddle.SetDashStyle(DashStyleDashDot);

	Gdiplus::SolidBrush brush(Gdiplus::Color(255,151,190,217));//信号颜色
	Gdiplus::SolidBrush brushScreen(Gdiplus::Color(255,91,155,213));//屏幕颜色

	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,9,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrush(Color(255,234,234,234));

	Gdiplus::StringFormat stringForamt;
	stringForamt.SetAlignment(StringAlignmentNear);
	stringForamt.SetLineAlignment(StringAlignmentNear);

	auto& VecScreen=pManage->GetVecScreen();
	for(auto& pScreen:VecScreen)
	{
		RECTF rect=pScreen->GetRect();
		RECTF drawRect(rect.X*dwScale,rect.Y*dwScale,rect.Width*dwScale,rect.Height*dwScale);

		graphics.DrawRectangle(&pen1,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
		graphics.FillRectangle(&brushScreen,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
		

		//每个屏幕绘制格子
		POINTF p1((rect.X+rect.Width/2)*dwScale-1,rect.Y*dwScale);
		POINTF p2((rect.X+rect.Width/2)*dwScale-1,(rect.Y+rect.Height)*dwScale);
		graphics.DrawLine(&penMiddle,p1,p2);

		POINTF p3(rect.X*dwScale,(rect.Y+rect.Height/2)*dwScale-1);
		POINTF p4((rect.X+rect.Width)*dwScale,(rect.Y+rect.Height/2)*dwScale-1);
		graphics.DrawLine(&penMiddle,p3,p4);

		//绘制文字
		CString szInfo;
		szInfo.Format(_T("%s:%d %s:%d"),_C(_T("334"),_T("屏幕")),pScreen->GetIndex(),_C(_T("336"),_T("拼接卡")),pScreen->GetSplitCh());
		graphics.DrawString(szInfo,-1,&font,drawRect,&stringForamt,&textbrush);
	}
}

void XDrawSplitManage::DrawSignal(Graphics& graphics,XSplitManage* pManage)
{
	float dwScale=pManage->GetScale();

	Gdiplus::SolidBrush brush(Gdiplus::Color(255,134,95,197));//标题颜色
	Gdiplus::SolidBrush brushSignal(Gdiplus::Color(255,151,190,217));//信号颜色
	//Gdiplus::Pen pen(Gdiplus::Color(255,134,95,197));//直线画笔

	float fontSize=10*dwScale;
	if(dwScale<0.75)
		fontSize=6;
	
	//TRACE(_T("scale=%f\n"),dwScale);
	//TRACE(_T("size=%f\n"),fontSize);

	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,fontSize,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrush(Color(255,234,234,234));
	
	Gdiplus::FontFamily fontfamily1(APP_FONT);
	Gdiplus::Font font1(&fontfamily1,8,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrush1(Color(255,50,50,50));


	Gdiplus::StringFormat stringForamtCenter;
	stringForamtCenter.SetAlignment(StringAlignmentNear);
	stringForamtCenter.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::StringFormat stringForamtNear;
	stringForamtNear.SetAlignment(StringAlignmentNear);
	stringForamtNear.SetLineAlignment(StringAlignmentNear);

	auto& VecSignal=pManage->GetVecSignal();
	for(auto& pSignal:VecSignal)
	{
		Color color=pSignal->GetColor();
		Gdiplus::SolidBrush brush(color);
		Gdiplus::Pen pen(color);

		RECTF rect=pSignal->GetRect();
		if(rect.Width==0||rect.Height==0)
			continue;

		RECTF rectUp=pSignal->GetRectUP();
		RECTF drawUp=Scale(rectUp,dwScale);
		RECTF drawRect=Scale(rect,dwScale);

		graphics.DrawRectangle(&pen,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
		graphics.FillRectangle(&brushSignal,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);

		graphics.DrawRectangle(&pen,drawUp.X,drawUp.Y,drawUp.Width-1,drawUp.Height-1);
		graphics.FillRectangle(&brush,drawUp.X,drawUp.Y,drawUp.Width-1,drawUp.Height-1);

		//绘制文字
		RECTF rectText=rectUp;
		rectText.Width-=70;
		RECTF drawText=Scale(rectText,dwScale);
		CString szID;
		szID.Format(_T("%d"),pSignal->GetSignalID());
		graphics.DrawString(szID,-1,&font,drawText,&stringForamtCenter,&textbrush);

		//信号源
		//计算实际位置
		int nX=rect.X*pManage->GetRealResulationX()/pManage->GetResulationX();
		int nY=rect.Y*pManage->GetRealResulationY()/pManage->GetResulationY();
		int nW=rect.Width*pManage->GetRealResulationX()/pManage->GetResulationX()-1;
		int nH=rect.Height*pManage->GetRealResulationY()/pManage->GetResulationY()-1;

		RECTF rectInput=pSignal->GetRectDown();
		RECTF drawInput=Scale(rectInput,dwScale);
		CString szInput;
		szInput.Format(_T("%s:%s\n%s:[%d,%d]\n%s:[%d,%d]"),
					   _C(_T("339"),_T("输入源")),
					   pSignal->GetSignalName(),
					   _C(_T("340"),_T("位置")),
					   nX,
					   nY,
					   _C(_T("341"),_T("大小")),
					   nW,
					   nH);
		graphics.DrawString(szInput,-1,&font1,drawInput,&stringForamtNear,&textbrush1);

		//绘制图片
		RECTF rectClose=pSignal->GetRectColse();
		RECTF drawClose=Scale(rectClose,dwScale);
		Image imageColse(pSignal->GetClosePng());

		graphics.DrawImage(&imageColse,drawClose,0.0f,0.0f,(Gdiplus::REAL)imageColse.GetWidth(),(Gdiplus::REAL)imageColse.GetHeight(),Gdiplus::UnitPixel,NULL,NULL,NULL);

		RECTF rectMax=pSignal->GetRectMax();
		RECTF drawMax=Scale(rectMax,dwScale);
		Image imageMax(pSignal->GetMaxPng());
		graphics.DrawImage(&imageMax,drawMax,0.0f,0.0f,(Gdiplus::REAL)imageMax.GetWidth(),(Gdiplus::REAL)imageMax.GetHeight(),Gdiplus::UnitPixel,NULL,NULL,NULL);


		RECTF rectMin=pSignal->GetRectMin();
		RECTF drawMin=Scale(rectMin,dwScale);
		Image imageMin(pSignal->GetMinPng());
		graphics.DrawImage(&imageMin,drawMin,0.0f,0.0f,(Gdiplus::REAL)imageMin.GetWidth(),(Gdiplus::REAL)imageMin.GetHeight(),Gdiplus::UnitPixel,NULL,NULL,NULL);


		RECTF rectFull=pSignal->GetRectFull();
		RECTF drawFull=Scale(rectFull,dwScale);
		Image imageFull(pSignal->GetFullPng());
		graphics.DrawImage(&imageFull,drawFull,0.0f,0.0f,(Gdiplus::REAL)imageFull.GetWidth(),(Gdiplus::REAL)imageFull.GetHeight(),Gdiplus::UnitPixel,NULL,NULL,NULL);


		//RECTF rectMenu=pSignal->GetRectMenu();
		//RECTF drawMenu=Scale(rectMenu,dwScale);
		//Image imageMenu(HandlePath::GetPhotoPath(_T("menu.png")));
		//graphics.DrawImage(&imageMenu,drawMenu,0.0f,0.0f,(Gdiplus::REAL)imageMenu.GetWidth(),(Gdiplus::REAL)imageMenu.GetHeight(),Gdiplus::UnitPixel,NULL,NULL,NULL);
	}
}

RECTF XDrawSplitManage::Scale(RECTF& rect,float dwScale)
{
	RECTF rectF;

	rectF.X=(int)(rect.X*dwScale);
	rectF.Y=(int)(rect.Y*dwScale);
	rectF.Width=(int)(rect.Width*dwScale);
	rectF.Height=(int)(rect.Height*dwScale);

	return rectF;
}