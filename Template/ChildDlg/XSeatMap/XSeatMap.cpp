#include "stdafx.h"
#include "XSeatMap.h"
#include "XSeatArrageManage.h"
#include "XTranslationManage.h"


IMPLEMENT_DYNAMIC(XSeatMap, XBaseWnd)

XSeatMap::XSeatMap()
{

}

XSeatMap::~XSeatMap()
{

}

BEGIN_MESSAGE_MAP(XSeatMap, CWnd)
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


BOOL XSeatMap::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_RETURN://���λس�  
			{
				return TRUE;  
			}
			break;
		case VK_ESCAPE://����Esc  
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

BOOL XSeatMap::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XSeatMap::OnPaint()
{
	CPaintDC dc(this); 
	DrawItem(&dc);
}

BOOL XSeatMap::DrawItem( CDC *pDC )
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
	DrawRect(graphics, rt);

	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);
	graphics.ReleaseHDC( hMemdc);
	SelectObject(hMemdc, hOldbmp);
	DeleteDC(hMemdc);
	DeleteObject(hMembmp);

	return TRUE;
}

void XSeatMap::DrawRect(Graphics& graphics,CRect& rt)
{
	Pen pen(Color(94,157,235),1);
	CRect rtTemp=rt;
	rtTemp.DeflateRect(0,0,1,1);
	graphics.DrawRectangle(&pen,Rect(rtTemp.left,rtTemp.top,rtTemp.Width(),rtTemp.Height()));
}

void XSeatMap::OnMouseMove(UINT nFlags, CPoint point)
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

void XSeatMap::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDowned)
	{
		m_dwState = State_Focus;
		Invalidate(FALSE);
		//PostLClickMsg();
		m_pManage->OnBtnBaseMap();
		m_bDowned = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void XSeatMap::OnRButtonUp(UINT nFlags, CPoint point)
{
	return;
}

void XSeatMap::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDowned = TRUE;
	m_dwState = State_Press;

	if ((GetWindowLong( m_hWnd, GWL_STYLE) &WS_TABSTOP ) )
		SetFocus();

	Invalidate(FALSE);
	CWnd::OnLButtonDown(nFlags, point);
}

LRESULT XSeatMap::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseLeave = TRUE;

	if (m_dwState != State_Disable)
	{
		m_dwState = State_Normal;
		Invalidate(FALSE);
	}

	return 0;
}

void XSeatMap::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;
	Invalidate(FALSE);
}

void XSeatMap::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	m_bFocus = FALSE;
	Invalidate(FALSE);
}

void XSeatMap::OnEnable(BOOL bEnable)
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
void XSeatMap::ReloadInterface()
{
	m_szTips=XTranslationManage::GetInstance()->GetTranslationString(_T("145"),_T("��ͼ"));
	m_TipCtrl.AddTool(this,m_szTips);
}

void XSeatMap::Move(CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	CRect newRect(CPoint(point.x+4,point.y+20),CSize(nWidth,nHeight));

	MoveWindow(newRect);

	if(!IsWindowVisible())
	{
		ShowWindow(SW_SHOW);
	}
}