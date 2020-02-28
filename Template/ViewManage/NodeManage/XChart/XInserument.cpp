#include "stdafx.h"
#include "XInserument.h"


XInserument::XInserument()
{
}

XInserument::~XInserument()
{
}

RECTF XInserument::GetRect()
{
	return m_rect;
}

void XInserument::SetInstrumentColor(Color b,Color e,Color ba,Color f)
{
	//UNUSED(b);
	m_colorBegin=b;
	m_colorEnd=e;
	m_colorBack=ba;
	m_colorFront=f;
}

void XInserument::SetDegress(int nTemper)
{
	m_nTemper=nTemper;
	if(nTemper==0)
	{
		m_nDegress=0;
	}
	else
	{
		float nTemp=(float)nTemper*241/100;
		m_nDegress=nTemp;
	}
}

void XInserument::SetTitlt(CString szTitle)
{
	m_szTitle=szTitle;
}

void XInserument::Draw(Graphics& graphics)
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
	Gdiplus::Pen pen(m_colorBack);
	Gdiplus::Pen pen1(Color(255,8,16,39));

	Gdiplus::SolidBrush brush2(m_colorBack);
	Gdiplus::SolidBrush brush3(m_colorBegin);


	RECTF rectBase=m_rect;
	RectScale(rectBase);

	////外围圆
	RECTF rectTemp=rectBase;
	rectTemp.X-=8*m_dwScale;
	rectTemp.Y-=8*m_dwScale;
	rectTemp.Width+=16*m_dwScale;
	rectTemp.Height+=16*m_dwScale;
	graphics.FillEllipse(&brush,rectTemp);

	RECTF rectTemp2=rectTemp;
	rectTemp2.X+=4*m_dwScale;
	rectTemp2.Y+=4*m_dwScale;
	rectTemp2.Width-=8*m_dwScale;
	rectTemp2.Height-=8*m_dwScale;
	graphics.FillEllipse(&brush1,rectTemp2);

	//graphics.DrawRectangle(&pen,rectBase);
	int c=6;
	for(int i=0;i<60;i++)
	{
		graphics.FillPie(&brush2,rectBase,(float)c*i,2);
	}

	RECTF rectShelter=rectBase;
	rectShelter.X+=13*m_dwScale;
	rectShelter.Y+=13*m_dwScale;
	rectShelter.Width-=26*m_dwScale;
	rectShelter.Height-=26*m_dwScale;
	graphics.FillEllipse(&brush1,rectShelter);

	RECTF rectShelter2=rectBase;
	rectShelter2.X+=8*m_dwScale;
	rectShelter2.Y+=8*m_dwScale;
	rectShelter2.Width-=16*m_dwScale;
	rectShelter2.Height-=16*m_dwScale;

	//遮挡 出现长针
	{
		graphics.FillPie(&brush1,rectShelter2,2,25);
		graphics.FillPie(&brush1,rectShelter2,32,25);
		graphics.FillPie(&brush1,rectShelter2,62,25);
		graphics.FillPie(&brush1,rectShelter2,92,25);
		graphics.FillPie(&brush1,rectShelter2,122,25);
		graphics.FillPie(&brush1,rectShelter2,152,25);
		graphics.FillPie(&brush1,rectShelter2,182,25);
		graphics.FillPie(&brush1,rectShelter2,212,25);
		graphics.FillPie(&brush1,rectShelter2,242,25);
		graphics.FillPie(&brush1,rectShelter2,272,25);
		graphics.FillPie(&brush1,rectShelter2,302,25);
		graphics.FillPie(&brush1,rectShelter2,332,25);

	}
	RECTF rectShelter14=rectBase;
	rectShelter14.X+=14*m_dwScale;
	rectShelter14.Y+=14*m_dwScale;
	rectShelter14.Width-=28*m_dwScale;
	rectShelter14.Height-=28*m_dwScale;
	graphics.DrawEllipse(&pen1,rectShelter14);

	//画椭圆刻度
	RECTF rectShelter3=rectBase;
	rectShelter3.X+=15*m_dwScale;
	rectShelter3.Y+=15*m_dwScale;
	rectShelter3.Width-=30*m_dwScale;
	rectShelter3.Height-=30*m_dwScale;
	graphics.DrawEllipse(&pen,rectShelter3);

	RECTF rectShelter4=rectBase;
	rectShelter4.X+=25*m_dwScale;
	rectShelter4.Y+=25*m_dwScale;
	rectShelter4.Width-=50*m_dwScale;
	rectShelter4.Height-=50*m_dwScale;
	graphics.DrawEllipse(&pen,rectShelter4);

	//遮挡下面90度
	RECTF rectTemp3=rectBase;
	rectTemp3.Height+=2*m_dwScale;
	graphics.FillPie(&brush1,rectTemp3,32,118);
	graphics.FillPie(&brush2,rectBase,149,1);
	graphics.FillPie(&brush2,rectBase,31,1);

	//画刻度底色
	graphics.FillPie(&brush2,rectShelter3,149,243);

	//////////////////////////////////////////////////////////////////////////
	//计算数值-刻度  最大241度
	int nPos=120;
	UINT8 rBegin=m_colorBegin.GetR();
	UINT8 gBegin=m_colorBegin.GetG();
	UINT8 bBegin=m_colorBegin.GetB();

	UINT8 rEnd=m_colorEnd.GetR();
	UINT8 gEnd=m_colorEnd.GetG();
	UINT8 bEnd=m_colorEnd.GetB();

	int rTemp=(rEnd-rBegin)/nPos;
	int gTemp=(gEnd-gBegin)/nPos;
	int bTemp=(bEnd-bBegin)/nPos;

	int nCount=(int)(150+m_nDegress/2);
	for(int i=150;i<nCount;i++)
	{
		Gdiplus::Color color(255,rBegin,gBegin,bBegin);
		Gdiplus::SolidBrush TempBrush(color);
		graphics.FillPie(&TempBrush,rectShelter3,(float)(150+(i-150)*2),2);

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

	//graphics.FillPie(&brush3,rectShelter3,150,m_nDegress);
	//////////////////////////////////////////////////////////////////////////
	//最后遮挡圆
	graphics.FillEllipse(&brush1,rectShelter4);

	//绘制温度
	CString szTemper;
	szTemper.Format(_T("%d℃"),m_nTemper);
	graphics.DrawString(szTemper,-1,&font,rectShelter4,&stringForamtCenter,&textbrush);

	//绘制标题
	RECTF rectTemp4=rectBase;
	rectTemp4.Y=rectBase.GetBottom()-30*m_dwScale;
	rectTemp4.Height=30*m_dwScale;
	graphics.DrawString(m_szTitle,-1,&font1,rectTemp4,&stringForamtCenter,&textbrush1);
}