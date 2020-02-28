#pragma once
#include "XConstant.h"

class XSeatArrageManage;

class XCaculateSeatArrageManage
{
public:
	XCaculateSeatArrageManage();
	~XCaculateSeatArrageManage();

public:
	//视图获取大小
	static CSize ViewGetSize(XSeatArrageManage* pManage);

	//设置视图原点
	static void SetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale, CDC& dc);

	//还原
	static void ReductionPoint(XSeatArrageManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint);

	//设置鼠标形状
	static HCURSOR GetCursor(CURSORTYPE type);

	//移动信号
	static void MoveSignal(POSITIONTYPE PositionType,RECTF& rect,SIZEF& size);

	static void MoveSignalOfNew(RECTF& rect,SIZEF& size);

	//判断鼠标在页面内
	static BOOL DecidedPointInPage(XSeatArrageManage* pManage,POINTF point);

	//获取坐席编号
	static int GetSeatIndex(XSeatArrageManage* pManage);
	static BOOL DecidedIndexIsExit(XSeatArrageManage* pManage,int nIndex);

	//判断点在坐席上
	static BOOL DecidedPointInSeat(XSeatArrageManage* pManage,POINTF point,XSeat*& pSeat);

	//获取在坐席类型
	static POSITIONTYPE DecidePointInSeatPosition(XSeatArrageManage* pManage,RECTF& retc,POINTF& point); 

	//获取鼠标类型
	static CURSORTYPE GetCursorTypeByPositionType(POSITIONTYPE positionType);

	//判断坐席在页面内
	static XSeat* GetSeatByIndex(XSeatArrageManage* pManage,int nIndex);

	//判断鼠标点在屏幕上
	static BOOL DecidedPointInScreen(XSeatArrageManage* pManage,POINTF point,XScreen*& pScreen);

	//判断节点是否已经在屏幕上面
	static BOOL DecidedNodeInScreen(XSeatArrageManage* pManage,int nNodeID,XScreen*& pTemp);

	//判断是否为第一个
	static BOOL DecidedFirstOne(XSeatArrageManage* pManage);

	static void SetPageOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale,CSize& orgSize);

	static void SetPageOrg(CRect& rect, int& noffsetX, int& noffsetY,CSize& size, float& dwScale, const int& nDrawDistanceX, 
		const int& nDrawDistanceY,CSize& orgSize);

private:

	//获取视图坐标原点
	static void GetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY,CSize& size, float& dwScale, int& nOrgX, int& nOrgY);
};