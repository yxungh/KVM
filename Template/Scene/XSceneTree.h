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

	UINT m_TimerTicks;      //��������Ķ�ʱ����������ʱ��
	UINT m_nScrollTimerID;  //��������Ķ�ʱ��
	CPoint m_HoverPoint;      //���λ��
	UINT m_nHoverTimerID;   //������ж�ʱ��

	//DWORD m_dwDragStart;     //������������һ�̵�ʱ��

	BOOL m_bDragging=FALSE;       //��ʶ�Ƿ������϶�������
	CImageList* m_pDragImage=NULL;      //�϶�ʱ��ʾ��ͼ���б�
	HTREEITEM m_hItemDragS=NULL;      //���϶��ı�ǩ
	HTREEITEM m_hItemDragD=NULL;      //�����϶��ı�ǩ
	DWORD m_dwTime=0;
};

