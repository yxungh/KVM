#pragma once
#include "XConstant.h"

class XSplitManage;

class XCaculateSplitManage
{
public:
	XCaculateSplitManage();
	virtual ~XCaculateSplitManage();

public:

	//��ͼ��ȡ��С
	static CSize ViewGetSize(XSplitManage* pManage);

	//������ͼԭ��
	static void SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CDC& dc);

	//��ԭ
	static void ReductionPoint(XSplitManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint);

	//�����ź���������
	static RECTF CalculateSignalRect(RECTF& rect,VEC_SPLITSCREEN& VecScreen);
	//�����ཻ��Ļ�����
	static RECTF CalculateInsertScreenRect(VEC_SPLITSCREEN& VecScreen);
	//��ȡ�ֿ������
	static RECTF CalculateBolckRect(RECTF& rect,VEC_SPLITSCREEN& VecScreen);

	//�ж�������ź�����
	static XSignal* DecidePointInSignal(XSplitManage* pManage,POINTF& point);
	static XSplitScreen* DecidePointInScreen(XSplitManage* pManage,POINTF& point);

	//��ȡ�������
	static POSITIONTYPE DecidePointInSignalPosition(XSplitManage* pManage,RECTF& rect,POINTF& point);
	static CURSORTYPE GetCursorTypeByPositionType(POSITIONTYPE positionType);

	//���
	static HCURSOR GetCursor(CURSORTYPE type);
	//���ڹر���
	static BOOL DecidePointInColse(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInMenu(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInTitle(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInMax(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInMin(XSignal* pSignal,POINTF& point);
	static BOOL DecidePointInFull(XSignal* pSignal,POINTF& point);

	static void MoveSignal(POSITIONTYPE PositionType,RECTF& rect,SIZEF& size);



private:

	//��ȡ��ͼ����ԭ��
	static void GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,int& nOrgX,int& nOrgY);

};

