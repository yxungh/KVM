#pragma once

class XSeatArrageManage;

class XDrawSeatArrageManage
{
public:
	XDrawSeatArrageManage();
	~XDrawSeatArrageManage();

public:

	//视图绘制
	static void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XSeatArrageManage* pSeatArrageManage);

private:

	static void DrawSeat(Graphics& graphics,XSeatArrageManage* pSeatArrageManage);

	//绘制拖动框
	static void DrawDrag(Graphics& graphics,XSeatArrageManage* pSeatArrageManage);

};