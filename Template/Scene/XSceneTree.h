#pragma once



class XSceneTree:public CTreeCtrl
{
	DECLARE_DYNAMIC(XSceneTree)

public:
	XSceneTree();
	virtual ~XSceneTree();

	virtual ULONG GetGestureStatus(CPoint ptTouch);

protected:
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnNMRClickTreeCtrl(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()




private:


	BOOL m_bDrag=FALSE;
	CPoint m_DragPoint;

	UINT m_TimerTicks;      //处理滚动的定时器所经过的时间
	UINT m_nScrollTimerID;  //处理滚动的定时器
	CPoint m_HoverPoint;      //鼠标位置
	UINT m_nHoverTimerID;   //鼠标敏感定时器

	//DWORD m_dwDragStart;     //按下鼠标左键那一刻的时间

	BOOL m_bDragging=FALSE;       //标识是否正在拖动过程中
	CImageList* m_pDragImage=NULL;      //拖动时显示的图象列表
	HTREEITEM m_hItemDragS=NULL;      //被拖动的标签
	HTREEITEM m_hItemDragD=NULL;      //接受拖动的标签
	DWORD m_dwTime=0;
};

