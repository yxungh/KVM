#pragma once
#include "XConstant.h"

class XMatrixManage;

class XCaculateMatrixManage
{
public:
	XCaculateMatrixManage();
	~XCaculateMatrixManage();

public:

	//视图获取大小
	static CSize ViewGetSize(XMatrixManage* pManage);

	//设置视图原点
	static void SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CDC& dc);

	//还原缩放的点
	static void ReductionPoint(XMatrixManage* pManage,CRect& rect,int noffsetX,int noffsetY,CPoint& srcPoint,POINTF& desPoint);

	//////////////////////////////////////////////////////////////////////////
	static BOOL DecidePointInScreen(XMatrixManage* pManage,XMatrixScreen*& pSignal,POINTF& point);

	static XMatrixScreen* GetMatrixScreenByPoint(XMatrixManage* pManage,POINTF& point);

	static void Move(RECTF& rect,SIZEF& size);

private:

	//获取视图坐标原点
	static void GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,int& nOrgX,int& nOrgY);


};

