#pragma once

class XMatrixManage;

class XDrawMatrixManage
{
public:
	XDrawMatrixManage();
	~XDrawMatrixManage();


public:

	// ”ÕºªÊ÷∆
	static void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XMatrixManage* pMatrixManage);

	static void DrawVecScreen(Graphics& graphics,XMatrixManage* pManage);

	static void DrawDragWnd(Graphics& graphics,XMatrixManage* pManage);
};

