
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "Template.h"

#include "ChildFrm.h"
#include "XInternalManage.h"
#include "XBaseViewManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)

	ON_WM_MDIACTIVATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame():
	m_pBaseManage(NULL),
	m_pInternalManage(NULL)
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWnd::OnMDIActivate(bActivate,pActivateWnd,pDeactivateWnd);

	if(NULL==m_pInternalManage)
		return;

	if(bActivate)
	{
		//if(m_pBaseManage!=NULL)
			//TRACE(_T("ChildFrame=%s\n"),m_pBaseManage->GetTitle());

		m_pInternalManage->SetViewManage(m_pBaseManage);
	}
	else
	{
		if(pActivateWnd==NULL)
		{
			m_pInternalManage->SetViewManage(NULL);
		}
	}
}

void CChildFrame::OnClose()
{
	if(NULL==m_pBaseManage)
		return;

	if(m_pBaseManage->GetBaseIndex()==0||
	   m_pBaseManage->GetBaseIndex()==1||
	   m_pBaseManage->GetBaseIndex()==2)
		return;

	if(NULL==m_pInternalManage)
		return;

	m_pInternalManage->CloseSplit();
}

void CChildFrame::DestroyMDI()
{
	//TRACE(_T("Destory\n"));
	MDIDestroy();
}

