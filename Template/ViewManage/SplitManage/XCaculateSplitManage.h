#pragma once
#include "XConstant.h"

class XSplitManage;

class XCaculateSplitManage
{
public:
	XCaculateSplitManage();
	virtual ~XCaculateSplitManage();

public:

	//视图获取大小
	static CSize ViewGetSize(XSplitManage* pManage);

	//设置视图原点
	static void SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CDC& dc);

	//还原
	static void ReductionPoint(XSplitManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint);

	//计算信号整体区域
	static RECTF CalculateSignalRect(RECTF& rect,VEC_SPLITSCREEN& VecScreen);
	//计算相交屏幕区域和
	static RECTF CalculateInsertScreenRect(VEC_SPLITSCREEN& VecScreen);
	//获取分块区域和
	static RECTF CalculateBolckRect(RECTF& rect,VEC_SPLITSCREEN& VecScreen);

	//判断鼠标在信号上面
	static XSignal* DecidePointInSignal(XSplitManage* pManage,POINTF& point);
	static XSplitScreen* DecidePointInScreen(XSplitManage* pManage,POINTF& point);

	//获取鼠标类型
	static POSITIONTYPE DecidePointInSignalPosition(XSplitManage* pManage,RECTF& rect,POINTF& point);
	static CURSORTYPE GetCursorTypeByPositionType(POSITIONTYPE positionType);

	//鼠标
	static HCURSOR GetCursor(CURSORTYPE type);
	//点在关闭上
	static BOOL DecidePointInColse(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInMenu(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInTitle(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInMax(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInMin(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInFull(XSignal* pSignal,POINTF& point);

	static void MoveSignal(POSITIONTYPE PositionType,RECTF& rect,SIZEF& size);



private:

	//获取视图坐标原点
	static void GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,int& nOrgX,int& nOrgY);

};

