#include "stdafx.h"
#include "XColorWnd.h"


IMPLEMENT_DYNAMIC(XColorWnd,CWnd)

XColorWnd::XColorWnd()
{
}


XColorWnd::~XColorWnd()
{
}

BEGIN_MESSAGE_MAP(XColorWnd,CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL XColorWnd::Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID)
{
	return CWnd::CreateEx(0,AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,::LoadCursor(NULL,IDC_ARROW),NULL,NULL),0,dwStyle,rect,pParentWnd,nID);
}

BOOL XColorWnd::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
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

BOOL XColorWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.dwExStyle|=WS_EX_TOOLWINDOW;
	return CWnd::PreCreateWindow(cs);
}

BOOL XColorWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XColorWnd::OnPaint()
{
	CPaintDC dc(this);

	CRect rt;
	GetClientRect(&rt);

	Graphics graphics(dc.GetSafeHdc());
	graphics.Clear(Gdiplus::Color(151,190,217));

	Gdiplus::Pen pen(Color(0,0,0),1);
	graphics.DrawRectangle(&pen,Rect(rt.left,rt.top,rt.Width()-1,rt.Height()-1));

	if(m_bClicked)
	{
		Gdiplus::SolidBrush brush(Color(0,255,0));
		graphics.FillRectangle(&brush,Rect(rt.left,rt.top,rt.Width(),rt.Height()));
	}
	else
	{
		Gdiplus::SolidBrush brush(Color(255,0,0));
		graphics.FillRectangle(&brush,Rect(rt.left,rt.top,rt.Width(),rt.Height()));
	}
}


