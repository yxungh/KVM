#pragma once
#include "XConstant.h"


class XDelegateInternalManage;

class XBaseInternalManage
{
public:

	XBaseInternalManage();
	virtual ~XBaseInternalManage();

public:

	//��ʼ��
	virtual void Init()=0;

	//��ʼ��ͣ�����
	virtual void InitPane()=0;

	//�������ؼ����ݱ仯
	virtual void ControlDataChange(XDATATYPE type)=0;

	virtual BOOL AppClose()=0;

	virtual void HandleUDPMsg(WPARAM wParam,LPARAM lParam)=0;

	virtual void Operate(OPERATETYPE type,void* pData)=0;

	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)=0;

	virtual void AddDocument()=0;

	virtual void SetViewColor(Color& color)=0;

	virtual void AdjustMultiVideoWindowSize()=0;
	virtual void HideMenuWnd()=0;


public:

	//��ͼ����
	virtual void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY)=0;

	//��ͼ��ȡ��С
	virtual CSize ViewGetSize()=0;

	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//��ͼ˫��
	virtual void ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//��ͼ�������
	virtual void ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//��ͼ����ƶ�
	virtual void ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//��ͼ����뿪
	virtual void ViewMouseLeave()=0;

	//������
	virtual BOOL ViewMouseWheel(short zDelta)=0;

	//��ͼ��������
	virtual void ViewKeyUp(UINT nChar)=0;

	//��ͼ�Ҽ�����
	virtual void ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

public:

	//����ί��
	void SetDelegate(XDelegateInternalManage* p);

protected:

	XDelegateInternalManage* m_pDelagate;
};