
// TemplateView.cpp : CTemplateView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Template.h"
#endif

#include "TemplateDoc.h"
#include "TemplateView.h"

#include "XDelegateView.h"
#include "MainFrm.h"
#include "XBaseViewManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTemplateView

IMPLEMENT_DYNCREATE(CTemplateView, CScrollView)

BEGIN_MESSAGE_MAP(CTemplateView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTemplateView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSELEAVE()
	ON_WM_SETCURSOR()

	ON_WM_SIZE()
END_MESSAGE_MAP()

// CTemplateView 构造/析构

CTemplateView::CTemplateView()
{
	m_pDelegate=nullptr;
	m_bMouseLeave=TRUE;
	m_pBaseManage=NULL;
}

CTemplateView::~CTemplateView()
{
}

BOOL CTemplateView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &=~ WS_BORDER;
	return CScrollView::PreCreateWindow(cs); 
}

void CTemplateView::SetBaseViewManage(XBaseViewManage* p)
{
	m_pBaseManage=p;
}

void CTemplateView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	GetParentFrame()->ModifyStyleEx(WS_EX_CLIENTEDGE,0,SWP_FRAMECHANGED); 
	Init();
}

void CTemplateView::Init()
{
	SetDelegate();
	ResetSize();
}

void CTemplateView::SetDelegate()
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	m_pDelegate=(XDelegateView*)pMainFrame;
}

void CTemplateView::ResetSize()
{
	if(nullptr!=m_pBaseManage)
	{
		CSize size=m_pBaseManage->ViewGetSize();

		//减1因为size是设置滚动最大值,从0到(宽度-1)
		size.cx-=1;
		size.cy-=1;

		//因为小于0会出现异常,所以加上判断
		size.cx=size.cx<0?0:size.cx;
		size.cy=size.cy<0?0:size.cy;
		SetScrollSizes(MM_TEXT,size);
	}
	else
	{
		SetScrollSizes(MM_TEXT,CSize(0,0));
	}
}

BOOL CTemplateView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

BOOL CTemplateView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return TRUE;
}

void CTemplateView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (nullptr != m_pDelegate)
	{
		CRect rect;
		GetClientRect(rect);
		SetCapture();
		m_pDelegate->ViewLButtonDown(nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	}
}

void CTemplateView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (nullptr != m_pDelegate)
	{

		SetCapture();

		CRect rect;
		GetClientRect(rect);
		
		m_pDelegate->ViewLButtonDblClk(nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	}
}

void CTemplateView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (nullptr != m_pDelegate)
	{
		if(GetCapture()==this)
		{
			ReleaseCapture();

			CRect rect;
			GetClientRect(rect);
			m_pDelegate->ViewLButtonUp(nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
			
		}
	}
}

void CTemplateView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nullptr != m_pDelegate)
	{
		if (m_bMouseLeave)
		{
			TRACKMOUSEEVENT evt = {0};
			evt.cbSize = sizeof(evt);
			evt.dwFlags = TME_LEAVE;
			evt.hwndTrack = m_hWnd;

			TrackMouseEvent(&evt);
			m_bMouseLeave = FALSE;
		}

		CRect rect;
		GetClientRect(rect);
		m_pDelegate->ViewMouseMove(nFlags, point, rect, GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	}
}

BOOL CTemplateView::OnMouseWheel(UINT fFlags, short zDelta, CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);

	if(!rect.PtInRect(point))
	{
		return __super::OnMouseWheel(fFlags,zDelta,point);
	}

	if(fFlags==MK_CONTROL)
	{
		if(NULL!=m_pDelegate)
		{
			return m_pDelegate->ViewMouseWheel(zDelta);
		}
	}

	return __super::OnMouseWheel(fFlags,zDelta,point);	
}

void CTemplateView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nullptr!=m_pDelegate)
	{
		m_pDelegate->ViewKeyUp(nChar);
	}
}

void CTemplateView::OnMouseLeave()
{
	if(nullptr!=m_pDelegate)
	{
		m_bMouseLeave=TRUE;
		m_pDelegate->ViewMouseLeave();
	}
}

void CTemplateView::OnDraw(CDC* pDC)
{
	CTemplateDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (nullptr!=m_pDelegate)
	{
		CRect rect;
		GetClientRect(rect);
		m_pDelegate->ViewDraw(pDC,rect,GetScrollPos(SB_HORZ),GetScrollPos(SB_VERT));
	}
}

void CTemplateView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if(nullptr!=m_pDelegate)
	{
		CRect rect;
		GetClientRect(rect);
		m_pDelegate->ViewRButtonUp(this,nFlags,point,rect,GetScrollPos(SB_HORZ),GetScrollPos(SB_VERT));
	}
}

// CTemplateView 打印

void CTemplateView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTemplateView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTemplateView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTemplateView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


void CTemplateView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTemplateView 诊断

#ifdef _DEBUG
void CTemplateView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTemplateView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTemplateDoc* CTemplateView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTemplateDoc)));
	return (CTemplateDoc*)m_pDocument;
}
#endif //_DEBUG


// CTemplateView 消息处理程序


void CTemplateView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType,cx,cy);

	if(NULL!=m_pDelegate)
	{
		m_pDelegate->AdjustMultiVideoWindowSize();
		m_pDelegate->HideMenuWnd();
	}
}
