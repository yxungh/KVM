#include "stdafx.h"
#include "XDrawMatrixManage.h"
#include "XMatrixManage.h"
#include "XCaculateMatrixManage.h"
#include "XMatrixScreen.h"
#include "XConstantData.h"


XDrawMatrixManage::XDrawMatrixManage()
{
}


XDrawMatrixManage::~XDrawMatrixManage()
{
}


void XDrawMatrixManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XMatrixManage* pMatrixManage)
{
	//long dwBegin=GetTickCount();
	//TRACE(_T("begin=%d\n"),dwBegin);

	float dwScale=pMatrixManage->GetScale();
	CSize size=pMatrixManage->ViewGetSize();

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	HDC hdc=pDC->GetSafeHdc();
	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);

	XCaculateMatrixManage::SetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,tempDC);

	HDC hMemdc=tempDC.GetSafeHdc();
	HBITMAP hMembmp=CreateCompatibleBitmap(hdc,nWidth,nHeight);
	HBITMAP hOldbmp=(HBITMAP)SelectObject(hMemdc,hMembmp);
	Graphics graphics(hMemdc);

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.Clear(pMatrixManage->GetViewColor());
	//////////////////////////////////////////////////////////////////////////
	DrawVecScreen(graphics,pMatrixManage);
	//////////////////////////////////////////////////////////////////////////
	BitBlt(hdc,noffsetX,noffsetY,nWidth,nHeight,hMemdc,0,0,SRCCOPY);
	graphics.ReleaseHDC(hMemdc);
	SelectObject(hMemdc,hOldbmp);
	tempDC.DeleteDC();
	DeleteObject(hMembmp);

	//long dwEnd=GetTickCount();
	//TRACE(_T("end=%d\n"),dwEnd);
}

void XDrawMatrixManage::DrawVecScreen(Graphics& graphics,XMatrixManage* pManage)
{
	float dwScale=pManage->GetScale();
	graphics.SetTextRenderingHint(TextRenderingHintSystemDefault);
	Gdiplus::Pen pen(Gdiplus::Color(255,0,0,0),0.5f);//ֱ�߻���
	Gdiplus::SolidBrush brush(Gdiplus::Color(255,151,190,217));//������ɫ
	Gdiplus::SolidBrush brushSwitch(Gdiplus::Color(255,91,155,213));//������ɫ
	//Gdiplus::SolidBrush brushDisenable(Gdiplus::Color(255,230,230,230));//����������ɫ
	//Gdiplus::SolidBrush brushSignal(Gdiplus::Color(90,198,149));//�ź���ɫ

	//Gdiplus::Pen penMiddle(Gdiplus::Color(255,0,0,0),1.0f);//���߻���
	//Gdiplus::REAL dashVal[4]={1,4,1,4};
	//penMiddle.SetDashPattern(dashVal,4);

	float dwTextSize=10*dwScale;
	//float dwTextSizeSignal=14*dwScale;

	Gdiplus::SolidBrush textbrush(Color(255,255,255,255));
	//Gdiplus::SolidBrush textbrushSignal(Color(255,0,0,255));
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,dwTextSize,FontStyleRegular,UnitPoint);
	//Gdiplus::Font fontSignal(&fontfamily,dwTextSizeSignal,FontStyleBold,UnitPoint);

	Gdiplus::StringFormat stringForamtCenter;
	stringForamtCenter.SetAlignment(StringAlignmentCenter);
	stringForamtCenter.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::StringFormat stringForamtNear;
	stringForamtNear.SetAlignment(StringAlignmentNear);
	stringForamtNear.SetLineAlignment(StringAlignmentNear);

	Gdiplus::StringFormat stringForamtFar;
	stringForamtFar.SetAlignment(StringAlignmentFar);
	stringForamtFar.SetLineAlignment(StringAlignmentFar);

	VEC_MATRIXSCREEN& VecMatrixScreen=pManage->GetVecMatrixScreen();
	for(auto& VecScreen:VecMatrixScreen)
	{
		XMatrixScreen* pScreen=VecScreen;

		CString szNodeName=pScreen->GetName();
		CString szInNodeName=pScreen->GetInName();
		int nChannel=pScreen->GetChannel();
		RECTF rect=pScreen->GetRect();
		RECTF drawRect(rect.X*dwScale,rect.Y*dwScale,rect.Width*dwScale,rect.Height*dwScale);

		graphics.DrawRectangle(&pen,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);

		CString szChannel;
		if(pScreen->GetSwitch())
		{
			//�л����
			int nInChannel=pScreen->GetInChannel();
			graphics.FillRectangle(&brushSwitch,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);

			szChannel.Format(_T("%dV%d"),nInChannel,nChannel);
		}
		else
		{
			graphics.FillRectangle(&brush,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
			szChannel.Format(_T("CH:%d"),nChannel);
		}

		//��������
		//graphics.DrawString(szNodeName,-1,&font,Gdiplus::PointF(drawRect.X,drawRect.Y),&textbrush);
		graphics.DrawString(szNodeName,-1,&font,drawRect,&stringForamtFar,&textbrush);
		graphics.DrawString(szChannel,-1,&font,drawRect,&stringForamtCenter,&textbrush);
		if(szInNodeName!=_T(""))
		{
			graphics.DrawString(szInNodeName,-1,&font,drawRect,&stringForamtNear,&textbrush);
		}
	}

	if(pManage->GetCreateWnd())
	{
		DrawDragWnd(graphics,pManage);
	}
}

void XDrawMatrixManage::DrawDragWnd(Graphics& graphics,XMatrixManage* pManage)
{
	float dwScale=pManage->GetScale();
	
	graphics.SetTextRenderingHint(TextRenderingHintSystemDefault);
	Gdiplus::Pen pen(Gdiplus::Color(255,0,0,0),0.5f);//ֱ�߻���
	Gdiplus::SolidBrush brushSwitch(Gdiplus::Color(255,91,155,213));//������ɫ
	
	float dwTextSize=10*dwScale;
	//float dwTextSizeSignal=14*dwScale;

	Gdiplus::SolidBrush textbrush(Color(255,255,255,255));
	//Gdiplus::SolidBrush textbrushSignal(Color(255,0,0,255));
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,dwTextSize,FontStyleRegular,UnitPoint);
	//Gdiplus::Font fontSignal(&fontfamily,dwTextSizeSignal,FontStyleBold,UnitPoint);

	Gdiplus::StringFormat stringForamtCenter;
	stringForamtCenter.SetAlignment(StringAlignmentCenter);
	stringForamtCenter.SetLineAlignment(StringAlignmentCenter);


	RECTF rect=pManage->GetDragRect();
	RECTF drawRect(rect.X*dwScale,rect.Y*dwScale,rect.Width*dwScale,rect.Height*dwScale);

	graphics.DrawRectangle(&pen,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);
	graphics.FillRectangle(&brushSwitch,drawRect.X,drawRect.Y,drawRect.Width-1,drawRect.Height-1);


	int nInChannel=XConstantData::GetInstance()->GetInChannel();
	int nOutChannel=XConstantData::GetInstance()->GetOutChannel();

	CString szTitle;
	szTitle.Format(_T("%dV%d"),nInChannel,nOutChannel);


	graphics.DrawString(szTitle,-1,&font,drawRect,&stringForamtCenter,&textbrush);

}