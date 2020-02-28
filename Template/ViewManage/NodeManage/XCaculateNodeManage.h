#pragma once
#include "XConstant.h"

class XNodeManage;

class XCaculateNodeManage
{
public:
	XCaculateNodeManage();
	~XCaculateNodeManage();

	//视图获取大小
	static CSize ViewGetSize(XNodeManage* pManage);

	//设置视图原点
	static void SetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale, CDC& dc);

	//还原
	static void ReductionPoint(XNodeManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint);

	//获取输入高度
	static int GetHightOfNodeIn(XNodeManage* pManage);

	//获取输入宽度
	static int GetWidthOfNodeIn(XNodeManage* pManage);

	//获取输出高度
	static int GetHightOfNodeOut(XNodeManage* pManage);

	//获取输出宽度
	static int GetWidthOfNodeOut(XNodeManage* pManage);

	//初始化输出分辨率信息
	static void InitMapResoluationInfo(XNodeManage* pManage);

	//初始化键盘值
	static void InitKeyValue(XNodeManage* pManage);

	//设置鼠标形状
	static HCURSOR GetCursor(CURSORTYPE type);

	//判断鼠标在在节点上
	static BOOL DecidePointInNode(XNodeManage* pManage,POINTF& point);

	//根据鼠标获取节点
	static XNode* GetNodeByPoint(XNodeManage* pManage,POINTF& point);

	//移动窗口
	static void MoveSignal(RECTF& rect,SIZEF& size);


private:

	//获取视图坐标原点
	static void GetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY,CSize& size, float& dwScale, int& nOrgX, int& nOrgY);
};