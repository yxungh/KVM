#include "stdafx.h"
#include "XSceneTree.h"
#include "XConstant.h"
#include "XScene.h"
#include "XConstantData.h"



IMPLEMENT_DYNAMIC(XSceneTree,CTreeCtrl)
XSceneTree::XSceneTree()
{
}


XSceneTree::~XSceneTree()
{
}


BEGIN_MESSAGE_MAP(XSceneTree,CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG,OnTvnBegindrag)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,OnNMCustomdrawTreeCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_GESTURE,OnGesture)
	ON_WM_TIMER()
END_MESSAGE_MAP()


ULONG XSceneTree::GetGestureStatus(CPoint ptTouch)
{
	return 0;
}


void XSceneTree::OnTvnBegindrag(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView=reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult=0;
	HTREEITEM item=pNMTreeView->itemNew.hItem;

	DWORD dwData=GetItemData(item);
	CString szItemText=GetItemText(item);

	XConstantData::GetInstance()->SetDragType(dwData);
	if(dwData==SCENETYPE_GROUP)
		return;

	m_hItemDragS=item;
	m_hItemDragD=NULL;
	m_pDragImage=CreateDragImage(m_hItemDragS);
	if(!m_pDragImage)
		return;

	m_bDragging=TRUE;
	m_pDragImage->BeginDrag(0,CPoint(10,10));
	CPoint pt=pNMTreeView->ptDrag;
	ClientToScreen(&pt);
	m_pDragImage->DragEnter(this,pt);
	m_nScrollTimerID=SetTimer(2,40,NULL);

	SelectItem(pNMTreeView->itemNew.hItem);
	SetCapture();
	CPoint point;
	GetCursorPos(&point);

	m_DragPoint=point;
	m_bDrag=TRUE;
}


void XSceneTree::OnLButtonDown(UINT nFlags,CPoint point)
{
	HTREEITEM item=HitTest(point);


	CTreeCtrl::OnLButtonDown(nFlags,point);
}


void XSceneTree::OnMouseMove(UINT nFlags,CPoint point)
{
	HTREEITEM hItem;
	UINT flags;

	//CRect rect;
	//GetClientRect(&rect);

	if(m_bDragging)
	{
		CPoint pt=point;
		CImageList::DragMove(pt);
		CImageList::DragShowNolock(FALSE);
		if((hItem=HitTest(point,&flags))!=NULL)
		{
			SelectDropTarget(hItem);
			m_hItemDragD=hItem;
		}
		CImageList::DragShowNolock(TRUE);
	}

	CTreeCtrl::OnMouseMove(nFlags,point);
}


void XSceneTree::OnLButtonUp(UINT nFlags,CPoint point)
{
	CRect rect;
	GetClientRect(&rect);

	if(m_bDragging)
	{
		m_bDragging=FALSE;
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImage;
		SelectDropTarget(NULL);
		KillTimer(m_nScrollTimerID);
		Expand(m_hItemDragD,TVE_EXPAND);

		//添加组
		if(m_hItemDragS!=NULL&&m_hItemDragD!=NULL)
		{
			if(XConstantData::GetInstance()->GetDragType()==SCENETYPE_SCENE)
			{
				XScene::GetInstance()->AddGroup(m_hItemDragS,m_hItemDragD);
			}
			else if(XConstantData::GetInstance()->GetDragType()==SCENETYPE_SPLIT)
			{
				XScene::GetInstance()->AddSplitGroup(m_hItemDragS,m_hItemDragD);
			}
		}	
	}

	CTreeCtrl::OnLButtonUp(nFlags,point);
}


void XSceneTree::OnLButtonDblClk(UINT nFlags,CPoint point)
{
	//防止过快
	DWORD time=GetTickCount();
	if(abs((long)time-(long)m_dwTime)<2000)
		return;
	m_dwTime=time;


	//TRACE(_T("OnLButtonDblClk\n"));

	HTREEITEM hItem=HitTest(point);
	if(hItem==NULL)
		return;

	DWORD dwData=GetItemData(hItem);
	if(dwData==SCENETYPE_GROUP)
		return;

	CString szItem=GetItemText(hItem);

	if(dwData==SCENETYPE_SPLITWALL)
	{
		HTREEITEM hParent=GetParentItem(hItem);
		if(NULL!=hParent)
		{
			CString szParent=GetItemText(hParent);
			XConstantData::GetInstance()->SetOpenSceneName(szParent);
			XConstantData::GetInstance()->SetSceneWall(szItem);
		}
	}
	else if(dwData==SCENETYPE_SPLIT||dwData==SCENETYPE_SCENE)
	{		
		XConstantData::GetInstance()->SetOpenSceneName(szItem);
	}

	XScene::GetInstance()->OpenScene(dwData);

	//CTreeCtrl::OnLButtonDblClk(nFlags,point);
}

void XSceneTree::OnTimer(UINT nIDEvent)
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

void XSceneTree::OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR,LRESULT *pResult)
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