#include "stdafx.h"
#include "XProgressBar.h"


XProgressBar::XProgressBar()
{
}


XProgressBar::~XProgressBar()
{
}

RECTF XProgressBar::GetRect()
{
	return m_rect;
}

void XProgressBar::SetWidth(int m,int n)
{
	m_nWidth=m;
	m_nProWidth=n;
}

void XProgressBar::SetColor(Color c1,Color c2)
{
	m_colorFront=c1;
	m_colorBack=c2;
}

void XProgressBar::Draw(Graphics& graphics)
{
	Gdiplus::SolidBrush brush(m_colorBack);
	Gdiplus::SolidBrush brushUP(m_colorFront);
	Gdiplus::Pen pen(m_colorBack);
	Gdiplus::Pen penUp(m_colorFront);

	Gdiplus::SolidBrush textbrushFar(Color(255,91,213,231));

	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,10*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::StringFormat stringForamtNear;
	stringForamtNear.SetAlignment(StringAlignmentNear);
	stringForamtNear.SetLineAlignment(StringAlignmentNear);

	Gdiplus::StringFormat stringForamtFar;
	stringForamtFar.SetAlignment(StringAlignmentFar);
	stringForamtFar.SetLineAlignment(StringAlignmentFar);

	graphics.FillRectangle(&brush,m_rect);
	graphics.DrawRectangle(&penUp,m_rect);
	if(m_nWidth!=0&&m_nWidth!=-1)
	{
		CString szChennal;
		szChennal.Format(_T("%d"),m_nWidth);
		graphics.DrawString(szChennal,-1,&font,m_rect,&stringForamtFar,&textbrushFar);
		//////////////////////////////////////////////////////////////////////////
		float nWidth=(float)m_nProWidth*300/m_nWidth;
		RECTF rectProUp=m_rect;
		rectProUp.Width=nWidth*m_dwScale;
		graphics.FillRectangle(&brushUP,rectProUp);

		if(m_nProWidth!=0||m_nProWidth!=-1)
		{
			CString szConnect;
			szConnect.Format(_T("%d"),m_nProWidth);
			RECTF r=rectProUp;
			r.X+=nWidth*m_dwScale;
			graphics.DrawString(szConnect,-1,&font,r,&stringForamtNear,&textbrushFar);
		}
	}
}