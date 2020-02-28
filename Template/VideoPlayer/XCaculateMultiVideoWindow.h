#pragma once
#include "XConstant.h"


class XMultiVideoWindow;

class XCaculateMultiVideoWindow
{
public:
	XCaculateMultiVideoWindow();
	~XCaculateMultiVideoWindow();


public:

	static CSize ViewGetSize(XMultiVideoWindow* p);

	static void SetPageOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CSize& orgSize);

	static void SetPageOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,CSize& orgSize);

	static void XCaculateMultiVideoWindow::GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,
														  CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,int& nOrgX,int& nOrgY);
};