#pragma once
#include "XBaseViewManage.h"
#include "XConstant.h"

class XDelegateNodeManage;

class XBaseNodeManage:public XBaseViewManage
{
public:
	XBaseNodeManage();
	virtual ~XBaseNodeManage();

public:

	//��ͼ����
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, int noffsetY)=0;

	//��ͼ��ȡ��С
	virtual CSize ViewGetSize()=0;

	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//��ͼ�������
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//��ͼ����ƶ�
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//��ͼ����뿪
	virtual void ViewMouseLeave()=0;

	//������
	virtual BOOL ViewMouseWheel(short zDelta)=0;

	//��ͼ��������
	virtual void ViewKeyUp(UINT nChar)=0;

	//��ͼ�Ҽ�����
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//������
	virtual void ControlDataChange(XDATATYPE type, void* pControl)=0;

	//���¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl)=0;

	//������ͼ
	virtual void ResetView()=0;

	//����������
	virtual void ResetLeftWnd()=0;

	//���ó������
	virtual void ResetSceneWnd()=0;

	//�л���ͼ������������
	virtual void ClearProperityWnd()=0;

	//��ȡ�ڵ�����
	virtual CString GetTitle()=0;

	//����ҳ������
	virtual void SetTitle(CString szTitle)=0;

	//����
	virtual void Operate(OPERATETYPE type, void* pData)=0;

	//�ı�UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)=0;

	//�������ͨ��
	virtual void ClearConChannel()=0;

	//����û���¼״̬
	virtual void  ClearUserLoginStatus()=0;

	//ע��
	virtual void ClearNode()=0;
	virtual void ClearCloumn()=0;

	//��սڵ���
	virtual void ClearNodeGroup()=0;

	//��ʼ��
	virtual void Init()=0;

	//�������ؽ���
	virtual void ReloadInterface()=0;

	//���������û�
	virtual void SetPropertyValue(CString szUserName)=0;

	//��ק����
	virtual void DragEnd(CPoint& point,CRect& rect)=0;

	//��ȡ�ڵ㼯��
	virtual MAP_NODE& GetMapNode()=0;

	virtual MAP_NODEALL& GetMapNodeAll()=0;

	virtual MAP_MATRIX& GetMapMatrix()=0;

	virtual MAP_NODEMAINSEC& GetMapNodeMainSec()=0;

	//��ȡ�ڵ��鼯��
	virtual MAP_NODEGROUP& GetMapNodeGroup()=0;

	virtual MAP_GROUPMAINSEC& GetMapGroupMainSec()=0;

	//������ͼ��ɫ
	virtual void SetViewColor(Color& color)=0;

	//������ͼ��ɫ
	virtual Color GetViewColor()=0;


public:

	inline void SetDelegate(XDelegateNodeManage* p){m_pDelegate=p;}

protected:

	XDelegateNodeManage* m_pDelegate=NULL;

};