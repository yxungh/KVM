#pragma once
#include "XConstant.h"

class XMatrixManage;

class XCaculateMatrixManage
{
public:
	XCaculateMatrixManage();
	~XCaculateMatrixManage();

public:

	//��ͼ��ȡ��С
	static CSize ViewGetSize(XMatrixManage* pManage);

	//������ͼԭ��
	static void SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,CDC& dc);

	//��ԭ���ŵĵ�
	static void ReductionPoint(XMatrixManage* pManage,CRect& rect,int noffsetX,int noffsetY,CPoint& srcPoint,POINTF& desPoint);

	//////////////////////////////////////////////////////////////////////////
	static BOOL DecidePointInScreen(XMatrixManage* pManage,XMatrixScreen*& pSignal,POINTF& point);

	static XMatrixScreen* GetMatrixScreenByPoint(XMatrixManage* pManage,POINTF& point);

	static void Move(RECTF& rect,SIZEF& size);

private:

	//��ȡ��ͼ����ԭ��
	static void GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,CSize& size,float& dwScale,int& nOrgX,int& nOrgY);


};

