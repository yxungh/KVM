#pragma once
#include "XConstant.h"

class XSplitManage;

class XDrawSplitManage
{
public:
	XDrawSplitManage();
	virtual ~XDrawSplitManage();

public:

	// ”ÕºªÊ÷∆
	static void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XSplitManage* pNodeManage);
private:
	static void DrawScreen(Graphics& graphics,XSplitManage* pManage);
	static void DrawSignal(Graphics& graphics,XSplitManage* pManage);

	static RECTF Scale(RECTF& rect,float dwScale);

};

