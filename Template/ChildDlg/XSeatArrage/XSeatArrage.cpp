#include "stdafx.h"
#include "XSeatArrage.h"
#include "XSeatArrageManage.h"
#include "XTranslationManage.h"



IMPLEMENT_DYNAMIC(XSeatArrage, XBaseWnd)

XSeatArrage::XSeatArrage():
m_szTips(_T(""))
{

}

XSeatArrage::~XSeatArrage()
{

}

BEGIN_MESSAGE_MAP(XSeatArrage, CWnd)
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


BOOL XSeatArrage::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_RETURN://屏蔽回车  
			{
				return TRUE;  
			}
			break;
		case VK_ESCAPE://屏蔽Esc  
			{
				return TRUE;  
			}
			break;
		default:
			break;
		}  
	} 
	else if(pMsg->message==WM_MOUSEMOVE)
	{
		m_TipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

BOOL XSeatArrage::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XSeatArrage::OnPaint()
{
	CPaintDC dc(this); 
	DrawItem(&dc);
}

BOOL XSeatArrage::DrawItem( CDC *pDC )
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

	DrawRect(graphics, rt);

	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC( hMemdc);

	SelectObject(hMemdc, hOldbmp);

	DeleteDC(hMemdc);

	DeleteObject(hMembmp);

	return TRUE;
}

void XSeatArrage::DrawRect(Graphics& graphics,CRect& rt)
{
	Pen pen(Color(94,157,235),1);
	CRect rtTemp=rt;
	rtTemp.DeflateRect(0,0,1,1);
	graphics.DrawRectangle(&pen,Rect(rtTemp.left,rtTemp.top,rtTemp.Width(),rtTemp.Height()));
}

void XSeatArrage::OnMouseMove(UINT nFlags, CPoint point)
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

void XSeatArrage::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDowned)
	{
		m_dwState = State_Focus;
		Invalidate(FALSE);
		//PostLClickMsg();
		m_pManage->OnBtnArrage();
		m_bDowned = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void XSeatArrage::OnRButtonUp(UINT nFlags, CPoint point)
{
	return;
}

void XSeatArrage::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDowned = TRUE;
	m_dwState = State_Press;

	if ((GetWindowLong( m_hWnd, GWL_STYLE) &WS_TABSTOP ) )
		SetFocus();

	Invalidate(FALSE);
	CWnd::OnLButtonDown(nFlags, point);
}

LRESULT XSeatArrage::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseLeave = TRUE;

	if (m_dwState != State_Disable)
	{
		m_dwState = State_Normal;
		Invalidate(FALSE);
	}

	return 0;
}

void XSeatArrage::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;
	Invalidate(FALSE);
}

void XSeatArrage::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	m_bFocus = FALSE;
	Invalidate(FALSE);
}

void XSeatArrage::OnEnable(BOOL bEnable)
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


//////////////////////////////////////////////////////////////////////////
void XSeatArrage::InitTips()
{
	m_TipCtrl.Create(this);
	m_TipCtrl.SetDelayTime(200); 
	//m_TipCtrl.SetTipTextColor(RGB(255,0,0));
	m_TipCtrl.SetTipBkColor(RGB(240,240,240));
	m_TipCtrl.Activate(TRUE); 

	m_szTips=_C(_T("146"),_T("排列"));
	m_TipCtrl.AddTool(this,m_szTips);
}

void XSeatArrage::ReloadInterface()
{
	m_szTips=_C(_T("146"),_T("排列"));
	m_TipCtrl.AddTool(this,m_szTips);
}

void XSeatArrage::Show()
{
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
}

void XSeatArrage::Hide()
{
	ShowWindow(SW_HIDE);
}

void XSeatArrage::Move(CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	CRect newRect(CPoint(point.x+4,point.y+52),CSize(nWidth,nHeight));

	MoveWindow(newRect);

	if(!IsWindowVisible())
	{
		ShowWindow(SW_SHOW);
	}
}