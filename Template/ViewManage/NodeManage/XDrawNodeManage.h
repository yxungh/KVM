#pragma once
#include "XConstant.h"

class XNodeManage;

class XDrawNodeManage
{
public:
	XDrawNodeManage();
	~XDrawNodeManage();

public:

	//视图绘制
	static void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XNodeManage* pNodeManage);

	//分配节点序号和区域
	static void SetNodeIndexAndRect(XNodeManage* pNodeManage);

	//绘制节点
	static void DrawNode(Graphics& graphics,XNodeManage* pNodeManage);

	//绘制拖动框
	static void DrawDrag(Graphics& graphics,XNodeManage* pNodeManage);

	//绘制运维图片
	static void DrawOperationPic(Graphics& graphics,XNodeManage* pNodeManage);

	//绘制设备栏
	static void DrawDevicePlate(Graphics& graphics,XNodeManage* pNodeManage);

	//绘制用户栏
	static void DrawUserPlate(Graphics& graphics,XNodeManage* pNodeManage);

	//绘制节点栏
	static void DrawNodePlate(Graphics& graphics,XNodeManage* pNodeManage);

	//绘制节点组
	static void DrawNodeGroupPlate(Graphics& graphics,XNodeManage* pNodeManage);

	//绘制中框
	static void DrawCentreRectangle(Graphics& graphics,XNodeManage* pNodeManage);

	//绘制系统状况
	static void DrawSystemStatus(Graphics& graphics,XNodeManage* pNodeManage);

	static void RectScale(RECTF& rect,float dwScale);

private:

	static CRect m_rectTextIn;
	static CRect m_rectTextOut;
};

