#include "stdafx.h"
#include "XMenuWnd.h"
#include "XSeatArrageManage.h"


IMPLEMENT_DYNAMIC(XMenuWnd, XBaseWnd)

	XMenuWnd::XMenuWnd()
{

}

XMenuWnd::~XMenuWnd()
{

}

BEGIN_MESSAGE_MAP(XMenuWnd, CWnd)
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

//BOOL XMenuWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
//{
//	return CWnd::CreateEx(0, AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,::LoadCursor(NULL, IDC_ARROW), NULL, NULL), 0, dwStyle, rect, pParentWnd, nID);
//}

BOOL XMenuWnd::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_RETURN://ÆÁ±Î»Ø³µ  
			{
				return TRUE;  
			}
			break;
		case VK_ESCAPE://ÆÁ±ÎEsc  
			{
				return TRUE;  
			}
			break;
		default:
			break;
		}  
	} 

	return __super::PreTranslateMessage(pMsg);
}

BOOL XMenuWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XMenuWnd::OnPaint()
{
	CPaintDC dc(this); 
	DrawItem(&dc);
}

BOOL XMenuWnd::DrawItem( CDC *pDC )
{
	CRect rt;
	GetClientRect(&rt);

	HDC hdc = pDC->GetSafeHdc();

	HDC hMemdc = CreateCompatibleDC(hdc);

	HBITMAP hMembmp = CreateCompatibleBitmap(hdc, rt.Width(), rt.Height());
	HBITMAP hOldbmp = (HBITMAP)SelectObject( hMemdc, hMembmp);

	Graphics graphics(hMemdc);

	graphics.Clear(m_FillColor);

	DrawImg(graphics, rt);

	//DrawText(graphics, rt);

	DrawRect(graphics, rt);

	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);

	graphics.ReleaseHDC( hMemdc);

	SelectObject(hMemdc, hOldbmp);

	DeleteDC(hMemdc);

	DeleteObject(hMembmp);

	return TRUE;
}

void XMenuWnd::DrawRect(Graphics& graphics,CRect& rt)
{
	Pen pen(Color(94,157,235),1);
	CRect rtTemp=rt;
	rtTemp.DeflateRect(0,0,1,1);
	graphics.DrawRectangle(&pen,Rect(rtTemp.left,rtTemp.top,rtTemp.Width(),rtTemp.Height()));
}

void XMenuWnd::OnMouseMove(UINT nFlags, CPoint point)
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

void XMenuWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDowned)
	{
		m_dwState = State_Focus;
		Invalidate(FALSE);
		//PostLClickMsg();
		m_pManage->ShowMenu();
		m_bDowned = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void XMenuWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	return;
}

void XMenuWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDowned = TRUE;
	m_dwState = State_Press;

	if ((GetWindowLong( m_hWnd, GWL_STYLE) &WS_TABSTOP ) )
		SetFocus();

	Invalidate(FALSE);
	CWnd::OnLButtonDown(nFlags, point);
}

LRESULT XMenuWnd::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseLeave = TRUE;

	if (m_dwState != State_Disable)
	{
		m_dwState = State_Normal;
		Invalidate(FALSE);
	}

	return 0;
}

void XMenuWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;
	Invalidate(FALSE);
}

void XMenuWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	m_bFocus = FALSE;
	Invalidate(FALSE);
}

void XMenuWnd::OnEnable(BOOL bEnable)
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

void XMenuWnd::Move(CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	CRect newRect(CPoint(point.x+10,point.y),CSize(nWidth,nHeight));

	MoveWindow(newRect);

	if(!IsWindowVisible())
	{
		ShowWindow(SW_SHOW);
	}
}
