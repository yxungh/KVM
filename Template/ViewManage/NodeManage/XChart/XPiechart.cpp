#include "stdafx.h"
#include "XPiechart.h"
#include "XPieChartInfo.h"


XPiechart::XPiechart()
{
	
}

XPiechart::~XPiechart()
{
	ClearMap();
}

void XPiechart::ClearMap()
{
	for(auto& map:m_MapPie)
	{
		delete map.second;
	}
	m_MapPie.clear();
}

RECTF XPiechart::GetRect()
{
	return m_rect;
}

void XPiechart::SetType(CString szType)
{
	m_szType=szType;
}

void XPiechart::SetInterRect(RECTF rect)
{
	m_InterRect=rect;
}

void XPiechart::SetColorFlag(BOOL b)
{
	m_bFalg=b;
}

void XPiechart::PushPieData(int nID,CString szTitle,int nDegress,Color color)
{
	XPieChartInfo* pInfo=new XPieChartInfo;
	pInfo->m_nID=nID;
	pInfo->m_szTitle=szTitle;
	pInfo->m_nDegress=nDegress;
	pInfo->m_color=color;

	if(m_MapPie.find(nID)!=m_MapPie.end())
	{
		m_MapPie[nID]=pInfo;
	}
	else
	{
		m_MapPie.insert(std::pair<int,XPieChartInfo*>(nID,pInfo));
	}
}

void XPiechart::PushPieData(int nID,XPieChartInfo* pInfo)
{
	if(m_MapPie.find(nID)!=m_MapPie.end())
	{
		m_MapPie[nID]=pInfo;
	}
	else
	{
		m_MapPie.insert(std::pair<int,XPieChartInfo*>(nID,pInfo));
	}
}

void XPiechart::Draw(Graphics& graphics)
{
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,12*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::Font font1(&fontfamily,8*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrush(Color(255,204,153,51));
	Gdiplus::SolidBrush textbrush1(Color(255,0,255,255));

	Gdiplus::StringFormat stringForamt;
	stringForamt.SetAlignment(StringAlignmentNear);
	stringForamt.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::SolidBrush brush(Gdiplus::Color(255,28,47,87));
	Gdiplus::Pen pen(Color(255,255,0,0));

	//各个区域
	//绘制底色
	RECTF rect=m_rect;
	rect.X-=15;
	rect.Y-=15;
	rect.Width+=30;
	rect.Height+=30;
	//饼图区域
	RECTF rectPie=m_rect;
	//外围区域
	RECTF InterRect=m_InterRect;
	//图例区域
	RECTF legendRect;
	legendRect.X=rect.GetRight();
	legendRect.Y=rect.Y;
	legendRect.Width=InterRect.GetRight()-rect.GetRight();
	legendRect.Height=rect.Height;

	//绘制底图
	RectScale(rect);
	graphics.FillEllipse(&brush,rect);

	int nSize=m_MapPie.size();
	if(nSize==0)
		return;

	//随机生成颜色
	if(m_bFalg)
	{
		for(auto& map:m_MapPie)
		{
			uint8_t r=(rand()%(200-30)+30);
			uint8_t g=(rand()%(200-30)+30);
			uint8_t b=(rand()%(200-30)+30);

			XPieChartInfo* pInfo=map.second;
			pInfo->m_color=Color(r,g,b);
		}

		m_bFalg=FALSE;
	}

	//绘制饼图
	RectScale(rectPie);
	//计算总度数
	int nSum=0;
	for(auto& map:m_MapPie)
	{
		XPieChartInfo* pInfo=map.second;
		int nDegress=pInfo->m_nDegress;
		nSum+=nDegress;
	}

	float nBegin=0;
	for(auto& map:m_MapPie)
	{
		XPieChartInfo* pInfo=map.second;
		int nData=pInfo->m_nDegress;
		Color color(pInfo->m_color);

		Gdiplus::SolidBrush brush(color);
		float nTemp=(float)nData*360/nSum;

		graphics.FillPie(&brush,rectPie,nBegin,nTemp);
		nBegin+=nTemp;
	}

	//绘制类型，图例
	//类型
	RECTF typeRect=InterRect;
	typeRect.Y+=40;
	typeRect.Width=80;
	typeRect.Height=30;
	RectScale(typeRect);
	//CString szText=_T("节点");
	graphics.DrawString(m_szType,-1,&font,typeRect,&stringForamt,&textbrush);
	//图例
	//RectScale(legendRect);
	float nY=legendRect.GetBottom()-10;
	for(auto iter=m_MapPie.rbegin();iter!=m_MapPie.rend();++iter)
	{
		RECTF sRect(legendRect.X+5,nY,15,10);
		RECTF colorRect=sRect;
		
		XPieChartInfo* pInfo=iter->second;
		
		Gdiplus::SolidBrush brush(pInfo->m_color);
		Gdiplus::Pen pen(pInfo->m_color);
		//绘制色块
		RectScale(colorRect);
		graphics.FillRectangle(&brush,colorRect);
		graphics.DrawRectangle(&pen,colorRect);
		//绘制文字
		RECTF titleRect=sRect;
		titleRect.X+=20;
		titleRect.Width=40;
		RectScale(titleRect);
		graphics.DrawString(pInfo->m_szTitle+_T(":"),-1,&font1,titleRect,&stringForamt,&textbrush);
		//绘制百分比
		RECTF perRect=sRect;
		perRect.X+=60;
		perRect.Width=40;
		RectScale(perRect);

		if(nSum==0)
		{

		}
		else
		{
			float nTemp=(float)(pInfo->m_nDegress)*100/nSum;
			CString szPer;
			szPer.Format(_T("%.1f%%"),nTemp);
			graphics.DrawString(szPer,-1,&font1,perRect,&stringForamt,&textbrush);
		}


		nY-=15;
	}
}