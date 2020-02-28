#pragma once


class XStoreTree:public CTreeCtrl
{
	DECLARE_DYNAMIC(XStoreTree)

public:
	XStoreTree();
	virtual ~XStoreTree();

	virtual ULONG GetGestureStatus(CPoint ptTouch);

protected:
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()


private:

	UINT m_TimerTicks=0;      //��������Ķ�ʱ����������ʱ��
	UINT m_nScrollTimerID=0;  //��������Ķ�ʱ��
	CPoint m_HoverPoint=0;      //���λ��
	UINT m_nHoverTimerID=0;   //������ж�ʱ��
	BOOL m_bDragging=FALSE;       //��ʶ�Ƿ������϶�������
	CImageList* m_pDragImage;      //�϶�ʱ��ʾ��ͼ���б�
	HTREEITEM m_hItemDragS=NULL;      //���϶��ı�ǩ
	HTREEITEM m_hItemDragD=NULL;      //�����϶��ı�ǩ
};

