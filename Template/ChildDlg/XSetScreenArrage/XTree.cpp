#include "StdAfx.h"
#include "XTree.h"
#include "XArragePageTwo.h"
#include "XDragWnd.h"
#include "XConstantData.h"
#include "XNode.h"


IMPLEMENT_DYNAMIC(XTree,CTreeCtrl)

	XTree::XTree():
	m_bDragging(FALSE),
	m_hItemDragS(NULL),
	m_hItemDragD(NULL),
	m_pScreenArrage(NULL),
	m_bDrag(FALSE),
	m_DragWnd(NULL)
{
}

XTree::~XTree()
{
}

BEGIN_MESSAGE_MAP(XTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG,OnTvnBegindrag)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,OnNMCustomdrawTreeCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_GESTURE,OnGesture)
	ON_WM_TIMER()
END_MESSAGE_MAP()


ULONG XTree::GetGestureStatus(CPoint ptTouch)
{
	return 0;
}

void XTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView=reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult=0;
	HTREEITEM item=pNMTreeView->itemNew.hItem;
	CString szItemText=GetItemText(item);

	//根据名称获取Node
	XNode* pNode=GetNodeByName(szItemText);
	if(NULL!=pNode)
	{
		XConstantData::GetInstance()->SetAvliNodeID(pNode->GetNodeID());
	}
	XConstantData::GetInstance()->SetNodeCaption(szItemText);

	SelectItem(item);
	SetCapture();
	CPoint point;
	GetCursorPos(&point);

	m_DragPoint=point;
	m_bDrag=TRUE;
}

void XTree::OnLButtonDown(UINT nFlags,CPoint point)
{
	CTreeCtrl::OnLButtonDown(nFlags,point);

}

void XTree::OnMouseMove(UINT nFlags,CPoint point)
{
	CTreeCtrl::OnMouseMove(nFlags, point);

	if(!m_bDrag)
		return;

	ClientToScreen(&point);
	if(m_DragWnd==NULL)
		CreateDragWnd();
	MoveDragWnd(point);
}

void XTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags, point);

	if(this==GetCapture())
		ReleaseCapture();
	m_bDrag=FALSE;
	MoveDragWndEnd();
}

void XTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonDblClk(nFlags, point);


}

void XTree::OnTimer(UINT nIDEvent)
{
	CTreeCtrl::OnTimer(nIDEvent);



}

void XTree::CreateDragWnd()
{
	m_DragWnd=m_pScreenArrage->CreateDragWnd();

	CString szCaption=XConstantData::GetInstance()->GetNodeCaption();
	m_DragWnd->SetCaption(szCaption);
}

void XTree::MoveDragWnd(CPoint& point)
{
	if (m_DragWnd!=NULL)
		m_DragWnd->Move(point);
}

void XTree::MoveDragWndEnd()
{
	if(m_DragWnd!=NULL)
	{
		CPoint point;
		GetCursorPos(&point);

		m_DragWnd->Hide();
		m_pScreenArrage->DragEnd(point);
		m_DragWnd=NULL;
	}
}

void XTree::OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVCUSTOMDRAW pNMCD=reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);

	NMCUSTOMDRAW nmCustomDraw=pNMCD->nmcd;
	switch(nmCustomDraw.dwDrawStage)
	{
	case CDDS_ITEMPREPAINT:
		{
			if(nmCustomDraw.uItemState&CDIS_SELECTED)
				pNMCD->clrTextBk=RGB(51,153,255);
		}
		break;
	default:
		break;
	}

	*pResult=0;
	*pResult|=CDRF_NOTIFYPOSTPAINT;
	*pResult|=CDRF_NOTIFYITEMDRAW;

	return;
}


XNode* XTree::GetNodeByName(CString szName)
{
	MAP_NODE& MapNode=m_pScreenArrage->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(szName==pNode->GetNodeName())
		{
			return pNode;
		}
	}
	return NULL;
}