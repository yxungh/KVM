#pragma once

class XDelegateView
{
public:
	XDelegateView();
	~XDelegateView();

	//��ͼ����
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, 
		int noffsetY) = 0;

	//��ͼ��ȡ��С
	virtual CSize ViewGetSize() = 0;

	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//��ͼ˫��
	virtual void ViewLButtonDblClk(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//��ͼ�������
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//��ͼ����ƶ�
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//�����ֹ���
	virtual BOOL ViewMouseWheel(short zDelta)=0;

	//��ͼ����뿪
	virtual void ViewMouseLeave() = 0;

	//��ͼ��������
	virtual void ViewKeyUp(UINT nChar) = 0;

	//��ͼ�Ҽ�����
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, 
		CRect& rect, int noffsetX, int noffsetY) = 0;

	virtual void AdjustMultiVideoWindowSize()=0;
	virtual void HideMenuWnd()=0;


};