#pragma once
#include "XConstant.h"

class XNodeManage;

class XDrawNodeManage
{
public:
	XDrawNodeManage();
	~XDrawNodeManage();

public:

	//��ͼ����
	static void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XNodeManage* pNodeManage);

	//����ڵ���ź�����
	static void SetNodeIndexAndRect(XNodeManage* pNodeManage);

	//���ƽڵ�
	static void DrawNode(Graphics& graphics,XNodeManage* pNodeManage);

	//�����϶���
	static void DrawDrag(Graphics& graphics,XNodeManage* pNodeManage);

	//������άͼƬ
	static void DrawOperationPic(Graphics& graphics,XNodeManage* pNodeManage);

	//�����豸��
	static void DrawDevicePlate(Graphics& graphics,XNodeManage* pNodeManage);

	//�����û���
	static void DrawUserPlate(Graphics& graphics,XNodeManage* pNodeManage);

	//���ƽڵ���
	static void DrawNodePlate(Graphics& graphics,XNodeManage* pNodeManage);

	//���ƽڵ���
	static void DrawNodeGroupPlate(Graphics& graphics,XNodeManage* pNodeManage);

	//�����п�
	static void DrawCentreRectangle(Graphics& graphics,XNodeManage* pNodeManage);

	//����ϵͳ״��
	static void DrawSystemStatus(Graphics& graphics,XNodeManage* pNodeManage);

	static void RectScale(RECTF& rect,float dwScale);

private:

	static CRect m_rectTextIn;
	static CRect m_rectTextOut;
};

