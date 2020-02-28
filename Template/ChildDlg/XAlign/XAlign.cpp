#include "stdafx.h"
#include "XAlign.h"
#include "XTranslationManage.h" 
#include "XSeatArrageManage.h"




IMPLEMENT_DYNAMIC(XAlign, XBaseWnd)

	XAlign::XAlign():
m_nAlignType(ALIGN_NULL)
{

}

XAlign::~XAlign()
{

}

BEGIN_MESSAGE_MAP(XAlign, CWnd)
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


BOOL XAlign::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN)  
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
	else if(pMsg->message==WM_MOUSEMOVE)
	{
		m_TipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

BOOL XAlign::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XAlign::OnPaint()
{
	CPaintDC dc(this); 
	DrawItem(&dc);
}

BOOL XAlign::DrawItem( CDC *pDC )
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
	if(m_dwState==State_Focus||m_dwState==State_Press)
		DrawRect(graphics, rt);

	BitBlt(hdc, 0, 0, rt.Width(), rt.Height(), hMemdc, 0, 0, SRCCOPY);
	graphics.ReleaseHDC( hMemdc);
	SelectObject(hMemdc, hOldbmp);
	DeleteDC(hMemdc);
	DeleteObject(hMembmp);
	return TRUE;
}

void XAlign::DrawRect(Graphics& graphics,CRect& rt)
{
	Pen pen(Color(94,157,235),1);
	CRect rtTemp=rt;
	rtTemp.DeflateRect(0,0,1,1);
	graphics.DrawRectangle(&pen,Rect(rtTemp.left,rtTemp.top,rtTemp.Width(),rtTemp.Height()));
}

void XAlign::OnMouseMove(UINT nFlags, CPoint point)
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

void XAlign::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDowned)
	{
		m_dwState = State_Focus;
		Invalidate(FALSE);

		switch(m_nAlignType)
		{
		case ALIGN_LEFT:
			{
				m_pManage->OnAlignLeft();
			}
			break;
		case ALIGN_HORIZON:
			{
				m_pManage->OnAlignHorzion();
			}
			break;
		case ALIGN_RIGHT:
			{
				m_pManage->OnAlignRight();
			}
			break;
		case ALIGN_TOP:
			{
				m_pManage->OnAlignTop();
			}
			break;
		case ALIGN_VERTICAL:
			{
				m_pManage->OnAlignVertical();
			}
			break;
		case ALIGN_BOTTOM:
			{
				m_pManage->OnAlignBottom();
			}
			break;
		default:
			break;
		}

		m_bDowned = FALSE;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void XAlign::OnRButtonUp(UINT nFlags, CPoint point)
{
	return;
}

void XAlign::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDowned = TRUE;
	m_dwState = State_Press;

	if ((GetWindowLong( m_hWnd, GWL_STYLE) &WS_TABSTOP ) )
		SetFocus();

	Invalidate(FALSE);
	CWnd::OnLButtonDown(nFlags, point);
}

LRESULT XAlign::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	m_bMouseLeave = TRUE;

	if (m_dwState != State_Disable)
	{
		m_dwState = State_Normal;
		Invalidate(FALSE);
	}

	return 0;
}

void XAlign::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;
	Invalidate(FALSE);
}

void XAlign::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	m_bFocus = FALSE;
	Invalidate(FALSE);
}

void XAlign::OnEnable(BOOL bEnable)
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

void XAlign::Move(CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	CRect newRect(0,0,0,0);
	switch(m_nAlignType)
	{
	case ALIGN_LEFT:
		{
			newRect=CRect(CPoint(point.x,point.y-32),CSize(nWidth,nHeight));
		}
		break;
	case ALIGN_HORIZON:
		{
			newRect=CRect(CPoint(point.x+28/*+4*/,point.y-32),CSize(nWidth,nHeight));
		}
		break;
	case ALIGN_RIGHT:
		{
			newRect=CRect(CPoint(point.x+28*2/*+4*2*/,point.y-32),CSize(nWidth,nHeight));
		}
		break;
	case ALIGN_TOP:
		{
			newRect=CRect(CPoint(point.x+28*3/*+4*3*/,point.y-32),CSize(nWidth,nHeight));
		}
		break;
	case ALIGN_VERTICAL:
		{
			newRect=CRect(CPoint(point.x+28*4/*+4*4*/,point.y-32),CSize(nWidth,nHeight));
		}
		break;
	case ALIGN_BOTTOM:
		{
			newRect=CRect(CPoint(point.x+28*5/*+4*5*/,point.y-32),CSize(nWidth,nHeight));
		}
		break;
	default:
		break;
	}

	MoveWindow(newRect);
}