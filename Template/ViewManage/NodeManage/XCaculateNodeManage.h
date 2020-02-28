#pragma once
#include "XConstant.h"

class XNodeManage;

class XCaculateNodeManage
{
public:
	XCaculateNodeManage();
	~XCaculateNodeManage();

	//��ͼ��ȡ��С
	static CSize ViewGetSize(XNodeManage* pManage);

	//������ͼԭ��
	static void SetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale, CDC& dc);

	//��ԭ
	static void ReductionPoint(XNodeManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint);

	//��ȡ����߶�
	static int GetHightOfNodeIn(XNodeManage* pManage);

	//��ȡ������
	static int GetWidthOfNodeIn(XNodeManage* pManage);

	//��ȡ����߶�
	static int GetHightOfNodeOut(XNodeManage* pManage);

	//��ȡ������
	static int GetWidthOfNodeOut(XNodeManage* pManage);

	//��ʼ������ֱ�����Ϣ
	static void InitMapResoluationInfo(XNodeManage* pManage);

	//��ʼ������ֵ
	static void InitKeyValue(XNodeManage* pManage);

	//���������״
	static HCURSOR GetCursor(CURSORTYPE type);

	//�ж�������ڽڵ���
	static BOOL DecidePointInNode(XNodeManage* pManage,POINTF& point);

	//��������ȡ�ڵ�
	static XNode* GetNodeByPoint(XNodeManage* pManage,POINTF& point);

	//�ƶ�����
	static void MoveSignal(RECTF& rect,SIZEF& size);


private:

	//��ȡ��ͼ����ԭ��
	static void GetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY,CSize& size, float& dwScale, int& nOrgX, int& nOrgY);
};