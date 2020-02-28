#pragma once
#include "XConstant.h"

class XSeatArrageManage;

class XCaculateSeatArrageManage
{
public:
	XCaculateSeatArrageManage();
	~XCaculateSeatArrageManage();

public:
	//��ͼ��ȡ��С
	static CSize ViewGetSize(XSeatArrageManage* pManage);

	//������ͼԭ��
	static void SetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale, CDC& dc);

	//��ԭ
	static void ReductionPoint(XSeatArrageManage* pManage,CRect& rect,int nOffsetX,int nOffsetY,CPoint& srcPoint,POINTF& desPoint);

	//���������״
	static HCURSOR GetCursor(CURSORTYPE type);

	//�ƶ��ź�
	static void MoveSignal(POSITIONTYPE PositionType,RECTF& rect,SIZEF& size);

	static void MoveSignalOfNew(RECTF& rect,SIZEF& size);

	//�ж������ҳ����
	static BOOL DecidedPointInPage(XSeatArrageManage* pManage,POINTF point);

	//��ȡ��ϯ���
	static int GetSeatIndex(XSeatArrageManage* pManage);
	static BOOL DecidedIndexIsExit(XSeatArrageManage* pManage,int nIndex);

	//�жϵ�����ϯ��
	static BOOL DecidedPointInSeat(XSeatArrageManage* pManage,POINTF point,XSeat*& pSeat);

	//��ȡ����ϯ����
	static POSITIONTYPE DecidePointInSeatPosition(XSeatArrageManage* pManage,RECTF& retc,POINTF& point); 

	//��ȡ�������
	static CURSORTYPE GetCursorTypeByPositionType(POSITIONTYPE positionType);

	//�ж���ϯ��ҳ����
	static XSeat* GetSeatByIndex(XSeatArrageManage* pManage,int nIndex);

	//�ж���������Ļ��
	static BOOL DecidedPointInScreen(XSeatArrageManage* pManage,POINTF point,XScreen*& pScreen);

	//�жϽڵ��Ƿ��Ѿ�����Ļ����
	static BOOL DecidedNodeInScreen(XSeatArrageManage* pManage,int nNodeID,XScreen*& pTemp);

	//�ж��Ƿ�Ϊ��һ��
	static BOOL DecidedFirstOne(XSeatArrageManage* pManage);

	static void SetPageOrg(CRect& rect, int& noffsetX, int& noffsetY, CSize& size, float& dwScale,CSize& orgSize);

	static void SetPageOrg(CRect& rect, int& noffsetX, int& noffsetY,CSize& size, float& dwScale, const int& nDrawDistanceX, 
		const int& nDrawDistanceY,CSize& orgSize);

private:

	//��ȡ��ͼ����ԭ��
	static void GetViewPortOrg(CRect& rect, int& noffsetX, int& noffsetY,CSize& size, float& dwScale, int& nOrgX, int& nOrgY);
};