#include "stdafx.h"
#include "XStoreTree.h"


IMPLEMENT_DYNAMIC(XStoreTree,CTreeCtrl)

XStoreTree::XStoreTree()
{
}


XStoreTree::~XStoreTree()
{
}


BEGIN_MESSAGE_MAP(XStoreTree,CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG,&XStoreTree::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_GESTURE,OnGesture)
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,&XStoreTree::OnNMCustomdrawTreeCtrl)
END_MESSAGE_MAP()


ULONG XStoreTree::GetGestureStatus(CPoint ptTouch)
{
	return 0;
}

void XStoreTree::OnTvnBegindrag(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView=reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult=0;
	HTREEITEM item=pNMTreeView->itemNew.hItem;

	DWORD dwData=GetItemData(item);
	CString szItemText=GetItemText(item);


}

void XStoreTree::OnLButtonDown(UINT nFlags,CPoint point)
{
	HTREEITEM item=HitTest(point);




	CTreeCtrl::OnLButtonDown(nFlags,point);
}

void XStoreTree::OnMouseMove(UINT nFlags,CPoint point)
{
	

	CTreeCtrl::OnMouseMove(nFlags,point);
}

void XStoreTree::OnLButtonUp(UINT nFlags,CPoint point)
{
	CRect rect;
	GetClientRect(&rect);


}

void XStoreTree::OnLButtonDblClk(UINT nFlags,CPoint point)
{

	CTreeCtrl::OnLButtonDblClk(nFlags,point);
}


void XStoreTree::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==m_nHoverTimerID)
	{
		//鼠标停留展开树
		//KillTimer(m_nHoverTimerID);
		//m_nHoverTimerID=0;
		//HTREEITEM trItem=0;
		//UINT uFlag=0;
		//trItem=HitTest(m_HoverPoint,&uFlag);
		//if(trItem&&m_bDragging)
		//{
		//	SelectItem(trItem);
		//	Expand(trItem,TVE_EXPAND);
		//}
	}
	else if(nIDEvent==m_nScrollTimerID)
	{
		m_TimerTicks++;

		CPoint pt;
		GetCursorPos(&pt);

		CRect rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);

		HTREEITEM hItem=GetFirstVisibleItem();
		if(pt.y<rect.top+10)
		{
			//向上滚动
			int slowscroll=6-(rect.top+10-pt.y)/20;

			if(0==(m_TimerTicks%((slowscroll>0)?slowscroll:1)))
			{
				CImageList::DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL,SB_LINEUP);
				SelectDropTarget(hItem);
				m_hItemDragD=hItem;
				CImageList::DragShowNolock(TRUE);
			}
		}
		else if(pt.y>rect.bottom-10)
		{
			//向下滚动
			int slowscroll=6-(pt.y-rect.bottom+10)/20;

			if(0==(m_TimerTicks%((slowscroll>0)?slowscroll:1)))
			{
				CImageList::DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL,SB_LINEDOWN);
				int nCount=GetVisibleCount();
				for(int i=0;i<nCount-1;i++)
					hItem=GetNextVisibleItem(hItem);

				if(hItem)
					SelectDropTarget(hItem);

				m_hItemDragD=hItem;
				CImageList::DragShowNolock(true);
			}
		}
	}
	CTreeCtrl::OnTimer(nIDEvent);
}

void XStoreTree::OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR,LRESULT *pResult)
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