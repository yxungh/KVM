#pragma once

class XSeatArrageManage;

class XDrawSeatArrageManage
{
public:
	XDrawSeatArrageManage();
	~XDrawSeatArrageManage();

public:

	//��ͼ����
	static void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XSeatArrageManage* pSeatArrageManage);

private:

	static void DrawSeat(Graphics& graphics,XSeatArrageManage* pSeatArrageManage);

	//�����϶���
	static void DrawDrag(Graphics& graphics,XSeatArrageManage* pSeatArrageManage);

};