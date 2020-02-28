#include "stdafx.h"
#include "XString.h"


XString::XString()
{
}

XString::~XString()
{
}

RECTF XString::GetRect()
{
	return m_rect;
}

void XString::SetDrawType(STRING nType)
{
	m_nDrawType=nType;
}

void XString::SetDrawInfo(CString szInfo)
{
	m_szDrawInfo=szInfo;
}

void XString::Draw(Graphics& graphics)
{
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,12*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::Font font1(&fontfamily,10*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::Font font2(&fontfamily,7*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrushTitle(Color(255,234,234,234));
	Gdiplus::SolidBrush textbrush(Color(255,204,153,51));
	Gdiplus::StringFormat stringForamt;

	Gdiplus::StringFormat stringForamtNear;
	stringForamtNear.SetAlignment(StringAlignmentNear);
	stringForamtNear.SetLineAlignment(StringAlignmentNear);

	Gdiplus::StringFormat stringForamtCenter;
	stringForamtCenter.SetAlignment(StringAlignmentCenter);
	stringForamtCenter.SetLineAlignment(StringAlignmentNear);
		
	switch(m_nDrawType)
	{
		case STRING::STRING_TITLE:
			{
				graphics.DrawString(m_szDrawInfo,-1,&font,m_rect,&stringForamtCenter,&textbrushTitle);
			}
			break;
		case STRING::STRING_ITEM:
			{
				graphics.DrawString(m_szDrawInfo,-1,&font1,m_rect,&stringForamtNear,&textbrushTitle);
			}
			break;
		case STRING::STRING_INFO:
			{
				graphics.DrawString(m_szDrawInfo,-1,&font1,m_rect,&stringForamtNear,&textbrush);
			}
			break;
		case STRING::STRING_INDEX:
			{
				graphics.DrawString(m_szDrawInfo,-1,&font2,m_rect,&stringForamtCenter,&textbrush);
			}
			break;
		default:		
			break;
	}
}