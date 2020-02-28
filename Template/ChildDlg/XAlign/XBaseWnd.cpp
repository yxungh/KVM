// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XBaseWnd.h"
#include "XConstant.h"

#pragma comment( lib, "UxTheme.lib")

// XBaseWnd

IMPLEMENT_DYNAMIC(XBaseWnd, CWnd)

	XBaseWnd::XBaseWnd()
{
	m_dwState = State_Normal;

	m_bMouseLeave = TRUE;

	m_bDowned = FALSE;

	m_bFocus = FALSE;

	m_bFillColor = FALSE;

	m_strText = _T("");

	m_strImg = _T("");

	m_pManage=NULL;

	m_szTips=_T("");
}

XBaseWnd::~XBaseWnd()
{

}

BEGIN_MESSAGE_MAP(XBaseWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()



// XBaseWnd 消息处理程序

BOOL XBaseWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CreateEx( 0, AfxRegisterWndClass(0), 0, dwStyle, rect, pParentWnd, nID);
}

BOOL XBaseWnd::DrawItem( CDC *pDC )
{
	CRect rt;
	GetClientRect(&rt);

	HDC hdc = pDC->GetSafeHdc();

	HDC hMemdc = CreateCompatibleDC(hdc);

	HBITMAP hMembmp = CreateCompatibleBitmap(hdc, rt.Width(), rt.Height());
	HBITMAP hOldbmp = (HBITMAP)SelectObject( hMemdc, hMembmp);

	Graphics graphics(hMemdc);

	if (m_bFillColor)
	{
		graphics.Clear(m_FillColor);
	}
	else
	{
		DrawThemeParentBackground(m_hWnd, hMemdc, &rt);
	}

	DrawImg(graphics, rt);

	DrawText(graphics, rt);

	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC( hMemdc);

	SelectObject(hMemdc, hOldbmp);

	DeleteDC(hMemdc);

	DeleteObject(hMembmp);

	return TRUE;
}

void XBaseWnd::DrawImg(Graphics& graphics, CRect& rt)
{
	if (_T("") == m_strImg)
		return;

	Gdiplus::Image* pImage = Gdiplus::Image::FromFile(m_strImg);	

	if (pImage->GetLastStatus() == Gdiplus::Ok)
	{
		UINT nImageWidth = pImage->GetWidth();

		UINT nImageHeight = pImage->GetHeight();

		graphics.DrawImage(pImage,
			RectF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height()), 
			m_dwState * nImageWidth/4.0f, 
			0, 
			nImageWidth/4.0f, 
			(Gdiplus::REAL)nImageHeight, 
			UnitPixel);
	}

	delete pImage;
}

void XBaseWnd::DrawText(Graphics& graphics, CRect& rt)
{
	if (_T("") == m_strText)
		return;

	Gdiplus::FontFamily fontfamily(APP_FONT);

	Gdiplus::Font font(&fontfamily, 9, FontStyleRegular, UnitPoint);

	Gdiplus::StringFormat stringformat;
	stringformat.SetAlignment(StringAlignmentCenter);
	stringformat.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::SolidBrush brush(Color(254, 254, 254));

	Gdiplus::RectF reF(0.0f, 0.0f, (Gdiplus::REAL)rt.Width(), (Gdiplus::REAL)rt.Height());

	graphics.DrawString(m_strText, -1, &font, reF, &stringformat, &brush);
}

void XBaseWnd::SetImage(CString szImg )
{
	m_strImg = szImg;
}

void XBaseWnd::OnPaint()
{
	CPaintDC dc(this); 

	DrawItem( &dc);
}

void XBaseWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bMouseLeave)
	{
		TRACKMOUSEEVENT evt = {0};
		evt.cbSize = sizeof(evt);
		evt.dwFlags = TME_LEAVE;
		evt.hwndTrack = m_hWnd;

		TrackMouseEvent( &evt);

		m_bMouseLeave = FALSE;

		m_dwState = State_Focus;

		Invalidate(FALSE);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void XBaseWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDowned)
	{
		m_dwState = State_Focus;

		Invalidate(FALSE);

		PostLClickMsg();

		m_bDowned = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void XBaseWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	return;
}

void XBaseWnd::PostLClickMsg()
{
	GetParent()->PostMessage(MSG_BTN_LCLICK, GetDlgCtrlID(), 0);
}

void XBaseWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDowned = TRUE;

	m_dwState = State_Press;

	if ((GetWindowLong( m_hWnd, GWL_STYLE) &WS_TABSTOP ) )
		SetFocus();

	Invalidate(FALSE);

	CWnd::OnLButtonDown(nFlags, point);
}

void XBaseWnd::SetCaption(CString szText)
{
	m_strText = szText;

	Invalidate(FALSE);
}

LRESULT XBaseWnd::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseLeave = TRUE;

	if (m_dwState != State_Disable)
	{
		m_dwState = State_Normal;

		Invalidate(FALSE);
	}

	return 0;
}

void XBaseWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;

	Invalidate(FALSE);
}

void XBaseWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	m_bFocus = FALSE;

	Invalidate(FALSE);
}


BOOL XBaseWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XBaseWnd::SetFillColor(Gdiplus::Color col)
{
	m_FillColor = col;

	m_bFillColor = TRUE;
}

void XBaseWnd::OnEnable(BOOL bEnable)
{
	CWnd::OnEnable(bEnable);

	if (bEnable)
	{
		m_dwState = State_Normal;
	}
	else
	{
		m_dwState = State_Disable;
	}

	Invalidate(FALSE);
}

void XBaseWnd::SetStatus(BOOL b)
{
	if (b)
	{
		m_dwState = State_Normal;
	}
	else
	{
		m_dwState = State_Disable;
	}

	Invalidate(FALSE);
}

void XBaseWnd::InitTips()
{
	m_TipCtrl.Create(this);
	m_TipCtrl.SetDelayTime(200); 
	//m_TipCtrl.SetTipTextColor(RGB(255,0,0));
	m_TipCtrl.SetTipBkColor(RGB(240,240,240));
	m_TipCtrl.Activate(TRUE); 

	m_TipCtrl.AddTool(this,m_szTips);
}

void XBaseWnd::ReloadInterface()
{
	m_TipCtrl.AddTool(this,m_szTips);
}


void XBaseWnd::Show()
{
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	if(!IsWindowVisible())
	{
		ShowWindow(SW_SHOW);
	}
}

void XBaseWnd::Hide()
{
	ShowWindow(SW_HIDE);
}

void XBaseWnd::Move(CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	CRect newRect(CPoint(point.x,point.y-5),CSize(nWidth,nHeight));

	MoveWindow(newRect);
}