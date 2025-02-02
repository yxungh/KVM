#pragma once

class XDelegateView
{
public:
	XDelegateView();
	~XDelegateView();

	//视图绘制
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, 
		int noffsetY) = 0;

	//视图获取大小
	virtual CSize ViewGetSize() = 0;

	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//视图双击
	virtual void ViewLButtonDblClk(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, 
		int noffsetX, int noffsetY) = 0;

	//鼠标滚轮滚动
	virtual BOOL ViewMouseWheel(short zDelta)=0;

	//视图鼠标离开
	virtual void ViewMouseLeave() = 0;

	//视图按键提起
	virtual void ViewKeyUp(UINT nChar) = 0;

	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, 
		CRect& rect, int noffsetX, int noffsetY) = 0;

	virtual void AdjustMultiVideoWindowSize()=0;
	virtual void HideMenuWnd()=0;


};