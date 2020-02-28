#pragma once
#include "XConstant.h"

class CTemplateView;
class XMultiVideoWindow;

class XBaseViewManage
{
public:
	XBaseViewManage();
	virtual ~XBaseViewManage();

public:

	//��ͼ����
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, int noffsetY)=0;

	//��ͼ��ȡ��С
	virtual CSize ViewGetSize()=0;

	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//��ͼ˫��
	virtual void ViewLButtonDblClk(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

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

	//����������
	virtual void ControlDataChange(XDATATYPE type, void* pControl)=0;

	//���¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl)=0;

	//����
	virtual void Operate(OPERATETYPE type, void* pData)=0;

	//�ı�UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)=0;

	//��ʼ��
	virtual void Init()=0;

	//�������ؽ���
	virtual void ReloadInterface()=0;

	//��ȡҳ������
	virtual CString GetTitle()=0;

	//������ͼ
	virtual void ResetView()=0;

	//����������
	virtual void ResetLeftWnd()=0;

	//���ó������
	virtual void ResetSceneWnd()=0;

	//�л���ͼ������������
	virtual void ClearProperityWnd()=0;

	//��ק����
	virtual void DragEnd(CPoint& point,CRect& rect)=0;

	//������ͼ��ɫ
	virtual void SetViewColor(Color& color)=0;

	//������ͼ��ɫ
	virtual Color GetViewColor()=0;


	//���麯��
	//��ȡ��ǰƴ����ͼ����(ƴ����д)
	virtual float GetCurScale() {return 1.0f;}



public:

	inline void SetMultiVideoWindow(XMultiVideoWindow* p){m_pMultiVideoWindow=p;}

	inline CTemplateView* GetView(){return m_pView;}

	inline void SetView(CTemplateView* p){m_pView=p;}
	inline void SetBaseIndex(int nIndex){m_nBaseIndex=nIndex;}
	inline int GetBaseIndex(){return m_nBaseIndex;}

	inline void SetSplitName(CString szName){m_szSplitName=szName;}
	inline CString GetSplitName(){return m_szSplitName;}

protected:

	CTemplateView* m_pView=NULL;
	XMultiVideoWindow* m_pMultiVideoWindow=NULL;

protected:

	CString m_szTitle=_T("");
	//�������
	CURSORTYPE m_CursorType=CURSORTYPE_NORMAL;
	//��ͼ��ɫ
	Color m_Color;
	//���
	int m_nBaseIndex=-1;
	//ƴ������
	CString m_szSplitName=_T("");

};