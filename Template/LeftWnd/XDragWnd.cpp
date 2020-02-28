// lrButton.cpp : 实现文件
//

#include "stdafx.h"
#include "XDragWnd.h"
#include "XConstant.h"
#include "XTranslationManage.h"


// XDragWnd
#define FRAMESINDEX 1001

IMPLEMENT_DYNAMIC(XDragWnd,CWnd)

XDragWnd::XDragWnd():
	m_pLeftWnd(NULL),
	m_szCaption(_T(""))
{
}

XDragWnd::~XDragWnd()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(XDragWnd,CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// XDragWnd 消息处理程序

BOOL XDragWnd::Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID)
{
	return CWnd::CreateEx(0,AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,::LoadCursor(NULL,IDC_ARROW),NULL,NULL),0,dwStyle,rect,pParentWnd,nID);
}


BOOL XDragWnd::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_RETURN://屏蔽回车  
				{
					return TRUE;
				}
				break;
				//case VK_ESCAPE://屏蔽Esc  
				//	{
				//		return TRUE;  
				//	}
				//	break;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

BOOL XDragWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle|=WS_EX_TOOLWINDOW;

	return CWnd::PreCreateWindow(cs);
}

BOOL XDragWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void XDragWnd::OnPaint()
{
	CPaintDC dc(this);
	//
	CRect rt;
	GetClientRect(&rt);

	Graphics graphics(dc.GetSafeHdc());

	graphics.Clear(Gdiplus::Color(151,190,217));

	Gdiplus::Pen pen(Color(0,0,0),1);
	graphics.DrawRectangle(&pen,Rect(rt.left,rt.top,rt.Width()-1,rt.Height()-1));

	Gdiplus::FontFamily fontfamily(APP_FONT);

	Gdiplus::Font font(&fontfamily,10,FontStyleRegular,UnitPoint);

	Gdiplus::StringFormat stringformat;
	stringformat.SetAlignment(StringAlignmentCenter);
	stringformat.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::SolidBrush brush(Color(0,0,0));

	Gdiplus::RectF reF(0.0f,0.0f,(Gdiplus::REAL)rt.Width(),(Gdiplus::REAL)rt.Height());

	//CString szTemp=XTranslationManage::GetInstance()->GetTranslationString(_T("24"),_T("登录"));
	graphics.DrawString(m_szCaption,-1,&font,reF,&stringformat,&brush);
}

void XDragWnd::Show()
{
	KillTimer(1);
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
}

void XDragWnd::Hide()
{
	//通过定时器隐藏是因为直接隐藏的话，那会造成显示墙闪一下，显示墙添加的信号没有那么快显示出来
	SetTimer(1,50,NULL);
	ShowWindow(SW_HIDE);
}

void XDragWnd::OnTimer(UINT_PTR nIDEvent)
{
	if(1==nIDEvent)
	{
		KillTimer(1);
		ShowWindow(SW_HIDE);
	}
}

void XDragWnd::Move(CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	CRect newRect(CPoint(point.x-nWidth/2,point.y-nHeight/2),CSize(nWidth,nHeight));

	MoveWindow(newRect);

	if(!IsWindowVisible())
	{
		ShowWindow(SW_SHOW);
	}
}