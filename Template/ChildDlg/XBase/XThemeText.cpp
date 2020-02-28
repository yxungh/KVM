// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XThemeText.h"
#include "XConstant.h"
#include "XThemeColor.h"

// XThemeText
IMPLEMENT_DYNAMIC(XThemeText,CWnd)

XThemeText::XThemeText()
{

}

XThemeText::~XThemeText()
{

}

BEGIN_MESSAGE_MAP(XThemeText,CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// XThemeText 消息处理程序

BOOL XThemeText::Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID)
{
	return CreateEx(0,AfxRegisterWndClass(0),0,dwStyle,rect,pParentWnd,nID);
}

void XThemeText::PreSubclassWindow()
{
	ModifyStyle(0,BS_OWNERDRAW);

	CWnd::PreSubclassWindow();
}

void XThemeText::SetText(CString szText,BOOL bLeft/*=FALSE*/,BOOL bCenter/*=FALSE*/)
{
	m_Left=bLeft;
	m_Text=szText;
	m_Center=bCenter;
	InvalidateRect(NULL);
}

void XThemeText::SetFillColor(COLORREF color)
{
	m_FillColor=color;
}

//void XThemeText::SetTextColor(COLORREF color)
//{
//	m_TextColor=color;
//}

void XThemeText::SetVertical(BOOL b)
{
	m_Vertical=b;
}

//void XThemeText::SetLeft(BOOL b)
//{
//	m_Left=b;
//}

void XThemeText::SetTextSize(int nSize)
{
	m_nTextSize=nSize;
}

BOOL XThemeText::OnEraseBkgnd(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	HDC hdc=pDC->GetSafeHdc();
	HDC hMemdc=CreateCompatibleDC(hdc);

	HBITMAP hMembmp=CreateCompatibleBitmap(hdc,rt.Width(),rt.Height());
	HBITMAP hOldbmp=(HBITMAP)SelectObject(hMemdc,hMembmp);

	Graphics graphics(hMemdc);
	Gdiplus::Color color(GetRValue(m_FillColor),GetGValue(m_FillColor),GetBValue(m_FillColor));
	graphics.Clear(m_BgColor[XThemeColor::GetInstance()->GetThemeIndex()]);

	DrawText(graphics,rt);
	BitBlt(hdc,0,0,rt.Width(),rt.Height(),hMemdc,0,0,SRCCOPY);
	graphics.ReleaseHDC(hMemdc);
	SelectObject(hMemdc,hOldbmp);
	DeleteDC(hMemdc);
	DeleteObject(hMembmp);

	return TRUE;
}

void XThemeText::DrawText(Graphics& graphics,CRect& rt)
{
	if(_T("")==m_Text)
		return;

	Gdiplus::FontFamily fontfamily(_T("微软雅黑"));
	Gdiplus::Font font(&fontfamily,(Gdiplus::REAL)m_nTextSize,FontStyleRegular,UnitPoint);
	Gdiplus::StringFormat stringformat;

	if(m_Left)
	{
		stringformat.SetAlignment(StringAlignmentNear);
		stringformat.SetLineAlignment(StringAlignmentNear);
	}
	else
	{
		stringformat.SetAlignment(StringAlignmentFar);
		stringformat.SetLineAlignment(StringAlignmentFar);
	}

	if(m_Center)
	{
		stringformat.SetAlignment(StringAlignmentCenter);
		stringformat.SetLineAlignment(StringAlignmentCenter);
	}

	if(m_Vertical)
	{
		stringformat.SetFormatFlags(StringFormatFlagsDirectionVertical);
	}

	//Gdiplus::Color color(GetRValue(m_TextColor),GetGValue(m_TextColor),GetBValue(m_TextColor));
	Gdiplus::SolidBrush brush(m_TextColor[XThemeColor::GetInstance()->GetThemeIndex()]);
	Gdiplus::RectF reF(0.0f,0.0f,(Gdiplus::REAL)rt.Width(),(Gdiplus::REAL)rt.Height());
	graphics.DrawString(m_Text,-1,&font,reF,&stringformat,&brush);
}

void XThemeText::OnPaint()
{
	CPaintDC dc(this);

	//CRect rt;
	//GetClientRect(&rt);

	//CBrush bruDB;
	//bruDB.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	//dc.FillRect(&rt, &bruDB);

	//Graphics graphics(dc.GetSafeHdc());

	//graphics.Clear(Gdiplus::Color(90, 198, 149));

	//Gdiplus::Pen pen(Color(0, 0, 0), 1);
	//graphics.DrawRectangle(&pen, Rect(rt.left,rt.top,rt.Width() - 1, rt.Height() - 1));

	//Gdiplus::FontFamily fontfamily(APP_FONT);

	//Gdiplus::Font font(&fontfamily, 12, FontStyleRegular, UnitPoint);

	//Gdiplus::StringFormat stringformat;
	//stringformat.SetAlignment(StringAlignmentNear);
	//stringformat.SetLineAlignment(StringAlignmentNear);

	//Gdiplus::SolidBrush brush(Color(0, 0, 255));

	//Gdiplus::RectF reF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height());
}