#pragma once

class XLeftWnd;
class XDragWnd;
class XNode;

class XTreeCtrl:public CTreeCtrl
{
	DECLARE_DYNAMIC(XTreeCtrl)

public:
	XTreeCtrl();
	virtual ~XTreeCtrl();

	virtual ULONG GetGestureStatus(CPoint ptTouch);

protected:
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR,LRESULT *pResult);
	//afx_msg void OnNMRClickTreeCtrl(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnNMCustomdrawTreeCtrl(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	inline void SetLeftWnd(XLeftWnd* p){m_pLeftWnd=p;}

private:

	//�����϶�����
	void CreateDragWnd();
	//�ƶ��϶�����
	void MoveDragWnd(CPoint& point);
	//�ƶ��϶����ڽ���
	void MoveDragWndEnd();

	XNode* GetNodeByName(CString szName);

private:

	XLeftWnd* m_pLeftWnd;
	XDragWnd* m_DragWnd;
	XNode* m_pTempNode;
	BOOL m_bDrag;
	CPoint m_DragPoint;
	//����� ��ֹ����ˢ�¹�����
	int m_dwData;
private:

	UINT m_TimerTicks;      //��������Ķ�ʱ����������ʱ��
	UINT m_nScrollTimerID;  //��������Ķ�ʱ��
	CPoint m_HoverPoint;      //���λ��
	UINT m_nHoverTimerID;   //������ж�ʱ��

	//DWORD m_dwDragStart;     //������������һ�̵�ʱ��

	BOOL m_bDragging;       //��ʶ�Ƿ������϶�������
	CImageList* m_pDragImage;      //�϶�ʱ��ʾ��ͼ���б�
	HTREEITEM m_hItemDragS;      //���϶��ı�ǩ
	HTREEITEM m_hItemDragD;      //�����϶��ı�ǩ

};