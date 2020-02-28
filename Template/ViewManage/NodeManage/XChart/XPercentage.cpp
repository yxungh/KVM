#include "stdafx.h"
#include "XPercentage.h"

int XPercentage::m_nCount=72;
XPercentage::XPercentage()
{
}

XPercentage::~XPercentage()
{
}

RECTF XPercentage::GetRect()
{
	return m_rect;
}

void XPercentage::SetCurRate(int n)
{
	m_nCurRate=n;
}

void XPercentage::SetCurRate(CString szTemper)
{
	if(_T("")==szTemper)
	{
		m_nCurRate=0;
	}
	else
	{
		int nPos=szTemper.Find('%');
		CString szTemp=szTemper.Left(nPos);
		szTemp.Trim();

		double nTemper=_ttof(szTemp);
		nTemper*=72;//一圈刻度数

		double nTemp=nTemper/100;

		m_nCurRate=(int)nTemp;
		if(nTemp<72)
		{
			m_nCurRate+=1;
		}
		else if(nTemp==72)
		{
			m_nCurRate=72;
		}
	}
}

void XPercentage::SetPrecentageColor(Color b,Color e,Color ba,Color f)
{
	m_colorBegin=b;
	m_colorEnd=e;
	m_colorBack=ba;
	m_colorFront=f;
}

void XPercentage::SetTitlt(CString szTitle)
{
	m_szTitle=szTitle;
}

void XPercentage::Draw(Graphics& graphics)
{
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,12*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::Font font1(&fontfamily,8*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrush(Color(255,204,153,51));
	Gdiplus::SolidBrush textbrush1(Color(255,0,255,255));

	Gdiplus::StringFormat stringForamtCenter;
	stringForamtCenter.SetAlignment(StringAlignmentCenter);
	stringForamtCenter.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::SolidBrush brush(m_colorBack);//底色
	Gdiplus::SolidBrush brush1(m_colorFront);//遮挡色
	Gdiplus::Pen pen(Color(255,255,0,0));
	//Gdiplus::Pen penL(Gdiplus::Color(255,0,255,255),1.0f);

	RECTF rectBase=m_rect;
	RectScale(rectBase);
	
	UINT8 rBegin=m_colorBegin.GetR();
	UINT8 gBegin=m_colorBegin.GetG();
	UINT8 bBegin=m_colorBegin.GetB();

	UINT8 rEnd=m_colorEnd.GetR();
	UINT8 gEnd=m_colorEnd.GetG();
	UINT8 bEnd=m_colorEnd.GetB();

	int rTemp=(rEnd-rBegin)/m_nCount;
	int gTemp=(gEnd-gBegin)/m_nCount;
	int bTemp=(bEnd-bBegin)/m_nCount;

	//外围圆
	RECTF rectTemp=rectBase;
	rectTemp.X-=8*m_dwScale;
	rectTemp.Y-=8*m_dwScale;
	rectTemp.Width+=16*m_dwScale;
	rectTemp.Height+=16*m_dwScale;
	graphics.FillEllipse(&brush,rectTemp);
	//graphics.DrawRectangle(&pen,rectTemp);

	RECTF rectTemp2=rectTemp;
	rectTemp2.X+=4*m_dwScale;
	rectTemp2.Y+=4*m_dwScale;
	rectTemp2.Width-=8*m_dwScale;
	rectTemp2.Height-=8*m_dwScale;
	graphics.FillEllipse(&brush1,rectTemp2);

	//绘制一圈底色
	int c=5;
	for(int i=0;i<m_nCount;i++)
	{
		graphics.FillPie(&brush,rectBase,(float)c*i,3);
	}
	//绘制进度格
	for(int i=0;i<m_nCurRate;i++)
	{
		Gdiplus::Color color(255,rBegin,gBegin,bBegin);
		Gdiplus::SolidBrush TempBrush(color);
		graphics.FillPie(&TempBrush,rectBase,(float)c*i,3);

		rBegin+=rTemp;
		if(rBegin>255)
			rBegin-=255;

		gBegin+=gTemp;
		if(gBegin>255)
			gBegin-=255;

		bBegin+=bTemp;
		if(bBegin>255)
			bBegin-=255;
	}

	//绘制中间遮挡圆
	RECTF rectShelter=rectBase;
	rectShelter.X+=10*m_dwScale;
	rectShelter.Y+=10*m_dwScale;
	rectShelter.Width-=20*m_dwScale;
	rectShelter.Height-=20*m_dwScale;
	graphics.FillEllipse(&brush1,rectShelter);
	//百分比
	int nRate=m_nCurRate*100/m_nCount;
	CString szRate;
	szRate.Format(_T("%d%%"),nRate);
	graphics.DrawString(szRate,-1,&font,rectShelter,&stringForamtCenter,&textbrush);

	//绘制标题
	RECTF rectText;
	rectText.X=rectTemp.X;
	rectText.Y=rectTemp.GetBottom()+5*m_dwScale;
	rectText.Width=rectTemp.Width;
	rectText.Height=20*m_dwScale;
	graphics.DrawString(m_szTitle,-1,&font1,rectText,&stringForamtCenter,&textbrush1);
}