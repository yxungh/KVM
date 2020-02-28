#include "stdafx.h"
#include "XTreeCtrl.h"
#include "XConstant.h"
#include "XLeftWnd.h"
#include "XConstantData.h"
#include "XDragWnd.h"
#include "XNode.h"
#include "XTranslationManage.h"
#include "XPropertiesWnd.h"
#include "XNodeGroupInfo.h"
#include "XSendDataManage.h"
#include "XMessageBox.h"


IMPLEMENT_DYNAMIC(XTreeCtrl,CTreeCtrl)

XTreeCtrl::XTreeCtrl():
	m_pLeftWnd(NULL),
	m_bDragging(FALSE),
	m_bDrag(FALSE),
	m_DragWnd(NULL),
	m_pTempNode(NULL),
	m_hItemDragS(NULL),
	m_hItemDragD(NULL),
	m_dwData(0)
{
}

XTreeCtrl::~XTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(XTreeCtrl,CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG,&XTreeCtrl::OnTvnBegindrag)
	//ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,&XTreeCtrl::OnNMCustomdrawTreeCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_GESTURE,OnGesture)
	ON_WM_TIMER()
END_MESSAGE_MAP()


ULONG XTreeCtrl::GetGestureStatus(CPoint ptTouch)
{
	return 0;
}

void XTreeCtrl::OnTvnBegindrag(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView=reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult=0;
	HTREEITEM item=pNMTreeView->itemNew.hItem;

	DWORD dwData=GetItemData(item);
	CString szItemText=GetItemText(item);

	switch(dwData)
	{
		case ITEMDATA_USER://用户
		case ITEMDATA_NODE://节点
		case ITEMDATA_NODEGROUPOUT:
		case ITEMDATA_MATRIXNODE://矩阵
		case ITEMDATA_SPLITNODE://拼接
			{
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
			}
			break;
		case ITEMDATA_USERGROUP:
		case ITEMDATA_NODEOUT:
		case ITEMDATA_NODEIN:
		case ITEMDATA_NODEGROUPIN:
			{
				return;
			}
			break;
		default:
			break;
	}

	SelectItem(pNMTreeView->itemNew.hItem);
	SetCapture();
	CPoint point;
	GetCursorPos(&point);

	m_DragPoint=point;
	m_bDrag=TRUE;

	//////////////////////////////////////////////////////////////////////////
	XConstantData::GetInstance()->SetDragType(dwData);
	switch(dwData)
	{
		case ITEMDATA_USER:
			{
				XConstantData::GetInstance()->SetUserName(szItemText);
			}
			break;
		case ITEMDATA_NODE:
			{
				XNode* pNode=GetNodeByName(szItemText);
				if(NULL!=pNode)
				{
					m_pTempNode=pNode;

					int nNodeID=pNode->GetNodeID();
					XConstantData::GetInstance()->SetNodeID(nNodeID);
					XConstantData::GetInstance()->SetGroupID(pNode->GetGroup());
					XConstantData::GetInstance()->SetType(pNode->GetNodeType());
				}
				XConstantData::GetInstance()->SetNodeName(szItemText);
			}
			break;
		case ITEMDATA_NODEGROUPIN:
		case ITEMDATA_NODEGROUPOUT:
			{
				XConstantData::GetInstance()->SetGroupName(szItemText);
			}
			break;
		case ITEMDATA_MATRIXNODE:
			{
				XNode* pNode=GetNodeByName(szItemText);
				if(NULL!=pNode)
				{
					XConstantData::GetInstance()->SetInChannel(pNode->GetChannel());
				}
			}
			break;
		case ITEMDATA_SPLITNODE:
			{
				//拼接
				XConstantData::GetInstance()->SetSignalName(szItemText);
				//先设置为默认
				XConstantData::GetInstance()->SetInputCh(1);
			}
			break;
		default:
			break;
	}
}

XNode* XTreeCtrl::GetNodeByName(CString szName)
{
	MAP_NODE& MapNode=m_pLeftWnd->GetMapNode();
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

void XTreeCtrl::OnLButtonDown(UINT nFlags,CPoint point)
{
	HTREEITEM item=HitTest(point);
	if(item!=NULL)
	{
		int dwData=GetItemData(item);
		switch(dwData)
		{
			case ITEMDATA_NODE:
				{
					CString szItemText=GetItemText(item);
					m_pLeftWnd->SetNodeSelected(szItemText);
				}
				break;
			case ITEMDATA_USER:
				{
					CString szItemText=GetItemText(item);
					m_pLeftWnd->SetPropertyValue(szItemText);
				}
				break;
			case ITEMDATA_NODEGROUPIN:
				{
					//单击输入
					//////////////////////////////////////////////////////////////////////////
					//显示属性
					CString szItemText=GetItemText(item);
					MAP_NODEGROUP& MapNodeGroup=m_pLeftWnd->GetMapNodeGroup();
					auto iter=MapNodeGroup.find(szItemText);
					if(iter!=MapNodeGroup.end())
					{
						XNodeGroupInfo* pInfo=iter->second;
						if(pInfo!=NULL)
						{
							XPropertiesWnd::GetInstance()->SetNodeGroup(pInfo);
							XPropertiesWnd::GetInstance()->SetNode(NULL);
							XPropertiesWnd::GetInstance()->SetSeat(NULL);
							pInfo->SetProprityWnd();
						}
					}

					MAP_GROUPMAINSEC& MapGroupMainSec=m_pLeftWnd->GetMapNodeGroupMainSec();
					if(MapGroupMainSec.find(szItemText)!=MapGroupMainSec.end())
					{
						XNodeGroupInfo* pInfo=MapGroupMainSec[szItemText];
						if(pInfo!=NULL)
						{
							XPropertiesWnd::GetInstance()->SetNodeGroup(pInfo);
							XPropertiesWnd::GetInstance()->SetNode(NULL);
							XPropertiesWnd::GetInstance()->SetSeat(NULL);
							pInfo->SetProprityWnd();
						}
					}

					//////////////////////////////////////////////////////////////////////////
					//切换页面到第二页
					m_pLeftWnd->SwitchPage(2);
					//绘制输入屏幕
					m_pLeftWnd->DrawGroupInScreen(szItemText);
					//隐藏悬浮按钮
					m_pLeftWnd->HidePopMenuBtn();
					//切换工具栏
					//if(m_dwData!=ITEMDATA_NODEGROUPIN)
					//{
					m_pLeftWnd->ResetRibbonBar();
					//	m_dwData=ITEMDATA_NODEGROUPIN;
					//}
				}
				break;
			case ITEMDATA_NODEGROUPOUT:
				{
					//单击输出
					//////////////////////////////////////////////////////////////////////////
					//显示属性
					CString szItemText=GetItemText(item);
					MAP_NODEGROUP& MapNodeGroup=m_pLeftWnd->GetMapNodeGroup();
					XNodeGroupInfo* pInfo=MapNodeGroup[szItemText];
					if(pInfo!=NULL)
					{
						XPropertiesWnd::GetInstance()->SetNodeGroup(pInfo);
						XPropertiesWnd::GetInstance()->SetNode(NULL);
						XPropertiesWnd::GetInstance()->SetSeat(NULL);
						pInfo->SetProprityWnd();
					}
					//////////////////////////////////////////////////////////////////////////
					//记录点击类型
					XConstantData::GetInstance()->SetNodeType(dwData);
					//////////////////////////////////////////////////////////////////////////
					//切换页面到第一页
					m_pLeftWnd->SwitchPage(1);
					//////////////////////////////////////////////////////////////////////////
					//页面中选中所点击分组
					m_pLeftWnd->SetSeatSelected(szItemText);
					//////////////////////////////////////////////////////////////////////////
					//显示悬浮按钮
					m_pLeftWnd->ShowPopMenuBtn();
					//切换工具栏
					//if(m_dwData!=ITEMDATA_NODEGROUPOUT)
					//{
					m_pLeftWnd->ResetRibbonBar();
					//	m_dwData=ITEMDATA_NODEGROUPOUT;
					//}

					//设置其他组为非
					//XLeftWnd::GetInstance()->LimitOtherGroup(szItemText);
					//XLeftWnd::GetInstance()->ShowGroupSeatArrage(szItemText);		
				}
				break;
			default:
				break;
		}
	}

	CTreeCtrl::OnLButtonDown(nFlags,point);
}

void XTreeCtrl::OnMouseMove(UINT nFlags,CPoint point)
{
	HTREEITEM hItem;
	UINT flags;

	CRect rect;
	GetClientRect(&rect);

	if(point.x<rect.right)
	{
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
	}
	else
	{
		if(m_bDragging)
		{
			m_bDragging=FALSE;
			CImageList::DragLeave(this);
			CImageList::EndDrag();
			delete m_pDragImage;
			SelectDropTarget(NULL);
			KillTimer(m_nScrollTimerID);
		}

		if(NULL!=m_pTempNode)
		{
			if(!m_pTempNode->GetDrag())
				return;
		}

		//if(ITEMDATA_NODEGROUPIN==XConstantData::GetInstance()->GetDragType())
			//return;


		ClientToScreen(&point);
		if(m_DragWnd==NULL)
			CreateDragWnd();
		MoveDragWnd(point);
	}

	CTreeCtrl::OnMouseMove(nFlags,point);
}

void XTreeCtrl::OnLButtonUp(UINT nFlags,CPoint point)
{
	CRect rect;
	GetClientRect(&rect);

	m_pTempNode=NULL;
	if(point.x<rect.right)
	{
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

			int nType=XConstantData::GetInstance()->GetDragType();
			if(nType!=ITEMDATA_NODEGROUPIN||nType!=ITEMDATA_NODEGROUPOUT)
			{
				//添加组
				if(m_hItemDragS!=NULL&&m_hItemDragD!=NULL)
					XLeftWnd::GetInstance()->AddGroup(m_hItemDragS,m_hItemDragD);
			}
		}
	}
	else
	{
		if(this==GetCapture())
			ReleaseCapture();
		m_bDrag=FALSE;
		MoveDragWndEnd();
	}
}

void XTreeCtrl::OnLButtonDblClk(UINT nFlags,CPoint point)
{
	//HTREEITEM item=HitTest(point);
	//if(NULL!=item)
	//{
	//	CString szItemText=GetItemText(item);
	//	int nData=GetItemData(item);
	//	switch(nData)
	//	{
	//	case ITEMDATA_NODEGROUPIN:
	//	case ITEMDATA_NODEGROUPOUT:
	//		{
	//			//设置其他组为非
	//			XLeftWnd::GetInstance()->LimitOtherGroup(szItemText);
	//			XLeftWnd::GetInstance()->ShowGroupSeatArrage(szItemText);

	//			XConstantData::GetInstance()->SetNodeType(nData);
	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//取消双击展开
	CTreeCtrl::OnLButtonDblClk(nFlags,point);
}

void XTreeCtrl::CreateDragWnd()
{
	m_DragWnd=m_pLeftWnd->CreateDragWnd();

	CString szCaption;
	int nType=XConstantData::GetInstance()->GetDragType();
	switch(nType)
	{
		case ITEMDATA_USER:
			{
				float dwScale=XLeftWnd::GetInstance()->GetCurScale();

				CRect rect(CPoint(0,0),CSize((int)(80*dwScale),(int)(30*dwScale)));
				m_DragWnd->MoveWindow(rect);

				szCaption=_C(_T("24"),_T("登录"));
			}
			break;
		case ITEMDATA_NODE:
			{
				szCaption.Format(_T("%d"),XConstantData::GetInstance()->GetNodeID());
			}
			break;
		case ITEMDATA_NODEGROUPIN:
		case ITEMDATA_NODEGROUPOUT:
			{
				szCaption=XConstantData::GetInstance()->GetGroupName();
				//szCaption=XTranslationManage::GetInstance()->GetTranslationString(_T("104"),_T("删除"));
			}
			break;
		case ITEMDATA_MATRIXNODE:
			{
				szCaption.Format(_T("CH:%d"),XConstantData::GetInstance()->GetInChannel());
			}
			break;
		case ITEMDATA_SPLITNODE:
			{
				//获取到放缩比例
				float dwScale=XLeftWnd::GetInstance()->GetCurScale();

				CRect rect(CPoint(0,0),CSize((int)(160*dwScale),(int)(90*dwScale)));
				m_DragWnd->MoveWindow(rect);

				szCaption=XConstantData::GetInstance()->GetSignalName();
			}
			break;
		default:
			break;
	}

	m_DragWnd->SetCaption(szCaption);
}

void XTreeCtrl::MoveDragWnd(CPoint& point)
{
	if(m_DragWnd!=NULL)
		m_DragWnd->Move(point);
}

void XTreeCtrl::MoveDragWndEnd()
{
	if(m_DragWnd!=NULL)
	{
		CRect rectDrag;
		m_DragWnd->GetWindowRect(&rectDrag);

		CPoint point;
		GetCursorPos(&point);

		m_DragWnd->Hide();

		int nType=XConstantData::GetInstance()->GetDragType();
		switch(nType)
		{
			case ITEMDATA_USER:
			case ITEMDATA_NODE:
			case ITEMDATA_MATRIXNODE:
			case ITEMDATA_SPLITNODE:
				{
					m_pLeftWnd->DragEnd(point,rectDrag);
				}
				break;
			case ITEMDATA_NODEGROUPIN:
				{
					//拖拽输入


				}
				break;
			case ITEMDATA_NODEGROUPOUT:
				{
					//拖拽输出
					CString szNodeGroupName=XConstantData::GetInstance()->GetGroupName();
					m_pLeftWnd->DragGroupToSeat(szNodeGroupName,point);

					//////////////////////////////////////////////////////////////////////////
					//之前删除组
					//if(IDYES==XMessageBox::GetInstance()->MessageBoxByKey(_T("109"),_T("是否删除组？"),MB_YESNO))
					//{
						//删除节点组
						//CString szNodeGroupName=XConstantData::GetInstance()->GetGroupName();
						//m_pLeftWnd->DragDelGroup(szNodeGroupName);


						//////////////////////////////////////////////////////////////////////////

						//MAP_NODEGROUP& MapNodeGroup=m_pLeftWnd->GetMapNodeGroup();
						//MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szNodeGroupName);
						//if(iter!=MapNodeGroup.end())
						//{
						//	//先发送，等返回成功，再改集合
						//	XNodeGroupInfo* pInfo=iter->second;

						//	XNodeGroupInfo nodeGroupInfo;
						//	nodeGroupInfo.SetGroupName(pInfo->GetGroupName());
						//	nodeGroupInfo.SetGroupID(pInfo->GetGroupID());

						//	XSendDataManage::GetInstance()->AddSendDataOfDelNodeGroup(nodeGroupInfo);
						//}
					//}
				}
				break;
			default:
				break;
		}

		m_DragWnd=NULL;
	}
}

void XTreeCtrl::OnTimer(UINT nIDEvent)
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

void XTreeCtrl::OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR,LRESULT *pResult)
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