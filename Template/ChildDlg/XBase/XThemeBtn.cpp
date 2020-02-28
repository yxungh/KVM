// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XThemeBtn.h"
#include "XConstant.h"
#include "XThemeColor.h"

#pragma comment( lib, "UxTheme.lib")

// XThemeBtn

IMPLEMENT_DYNAMIC(XThemeBtn,CWnd)

XThemeBtn::XThemeBtn()
{
	m_FillColor=m_BtnColor[XThemeColor::GetInstance()->GetThemeIndex()][0];
}

XThemeBtn::~XThemeBtn()
{

}

BEGIN_MESSAGE_MAP(XThemeBtn,CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
END_MESSAGE_MAP()



// XThemeBtn 消息处理程序

BOOL XThemeBtn::Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID)
{
	return CreateEx(0,AfxRegisterWndClass(0),0,dwStyle,rect,pParentWnd,nID);
}

BOOL XThemeBtn::DrawItem(CDC *pDC)
{
	CRect rt;
	GetClientRect(&rt);

	HDC hdc=pDC->GetSafeHdc();
	HDC hMemdc=CreateCompatibleDC(hdc);

	HBITMAP hMembmp=CreateCompatibleBitmap(hdc,rt.Width(),rt.Height());
	HBITMAP hOldbmp=(HBITMAP)SelectObject(hMemdc,hMembmp);

	Graphics graphics(hMemdc);
	graphics.Clear(m_FillColor);

	DrawText(graphics,rt);

	BitBlt(hdc,0,0,rt.Width(),rt.Height(),hMemdc,0,0,SRCCOPY);
	graphics.ReleaseHDC(hMemdc);
	SelectObject(hMemdc,hOldbmp);
	DeleteDC(hMemdc);
	DeleteObject(hMembmp);

	return TRUE;
}

void XThemeBtn::DrawText(Graphics& graphics,CRect& rt)
{
	if(_T("")==m_strText)
		return;

	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,9,FontStyleRegular,UnitPoint);

	Gdiplus::StringFormat stringformat;
	stringformat.SetAlignment(StringAlignmentCenter);
	stringformat.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::SolidBrush brush(m_TextColor[XThemeColor::GetInstance()->GetThemeIndex()]);
	Gdiplus::RectF reF(0.0f,0.0f,(Gdiplus::REAL)rt.Width(),(Gdiplus::REAL)rt.Height());
	graphics.DrawString(m_strText,-1,&font,reF,&stringformat,&brush);
}

void XThemeBtn::OnPaint()
{
	CPaintDC dc(this);
	DrawItem(&dc);
}

void XThemeBtn::OnMouseMove(UINT nFlags,CPoint point)
{
	if(m_bMouseLeave)
	{
		TRACKMOUSEEVENT evt={0};
		evt.cbSize=sizeof(evt);
		evt.dwFlags=TME_LEAVE;
		evt.hwndTrack=m_hWnd;

		TrackMouseEvent(&evt);
		m_bMouseLeave=FALSE;
		m_dwState=State_Focus;
		m_FillColor=m_BtnColor[XThemeColor::GetInstance()->GetThemeIndex()][1];
		Invalidate(FALSE);
	}

	CWnd::OnMouseMove(nFlags,point);
}

void XThemeBtn::OnLButtonUp(UINT nFlags,CPoint point)
{
	if(m_bDowned)
	{
		m_dwState=State_Focus;
		m_FillColor=m_BtnColor[XThemeColor::GetInstance()->GetThemeIndex()][1];
		Invalidate(FALSE);
		PostLClickMsg();
		m_bDowned=FALSE;
	}

	CWnd::OnLButtonUp(nFlags,point);
}

void XThemeBtn::PostLClickMsg()
{
	GetParent()->PostMessage(MSG_BTN_LCLICK,GetDlgCtrlID(),0);
}

void XThemeBtn::OnLButtonDown(UINT nFlags,CPoint point)
{
	m_bDowned=TRUE;
	m_dwState=State_Press;

	if((GetWindowLong(m_hWnd,GWL_STYLE) &WS_TABSTOP))
		SetFocus();

	m_FillColor=m_BtnColor[XThemeColor::GetInstance()->GetThemeIndex()][2];
	Invalidate(FALSE);
	CWnd::OnLButtonDown(nFlags,point);
}

void XThemeBtn::SetCaption(CString szText)
{
	m_strText=szText;
	Invalidate(FALSE);
}

LRESULT XThemeBtn::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	m_bMouseLeave=TRUE;

	if(m_dwState!=State_Disable)
	{
		m_dwState=State_Normal;
		m_FillColor=m_BtnColor[XThemeColor::GetInstance()->GetThemeIndex()][0];
		Invalidate(FALSE);
	}

	return 0;
}

void XThemeBtn::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	m_bFocus=TRUE;
	Invalidate(FALSE);
}

void XThemeBtn::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
	m_bFocus=FALSE;
	Invalidate(FALSE);
}


BOOL XThemeBtn::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XThemeBtn::SetFillColor(Gdiplus::Color col)
{
	m_FillColor=col;
}

void XThemeBtn::OnEnable(BOOL bEnable)
{
	CWnd::OnEnable(bEnable);

	if(bEnable)
	{
		m_dwState=State_Normal;
	}
	else
	{
		m_dwState=State_Disable;
	}

	Invalidate(FALSE);
}