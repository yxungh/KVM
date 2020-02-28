#pragma once
#include "XBaseMatrixManage.h"



class XMatrixManage:public XBaseMatrixManage
{
public:
	XMatrixManage();
	~XMatrixManage();

public:

	//��ͼ����
	virtual void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY);
	//��ͼ��ȡ��С
	virtual CSize ViewGetSize();
	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//��ͼ˫��
	virtual void ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//��ͼ�������
	virtual void ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//��ͼ����ƶ�
	virtual void ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//��ͼ����뿪
	virtual void ViewMouseLeave();
	//������
	virtual BOOL ViewMouseWheel(short zDelta);
	//��ͼ��������
	virtual void ViewKeyUp(UINT nChar);
	//��ͼ�Ҽ�����
	virtual void ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//����������
	virtual void ControlDataChange(XDATATYPE type,void* pControl);
	//���¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type,void* pControl);
	//����
	virtual void Operate(OPERATETYPE type,void* pData);
	//�ı�UI
	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);
	//��ʼ��
	virtual void Init();
	//�������ؽ���
	virtual void ReloadInterface();
	//��ȡҳ������
	virtual CString GetTitle();
	//����ҳ������
	virtual void SetTitle(CString szTitle);
	//������ͼ
	virtual void ResetView();
	//����������
	virtual void ResetLeftWnd();
	//���ó������
	virtual void ResetSceneWnd();
	//�л���ͼ������������
	virtual void ClearProperityWnd();
	//��ק����
	virtual void DragEnd(CPoint& point,CRect& rect);
	//������ͼ��ɫ
	virtual void SetViewColor(Color& color);
	//������ͼ��ɫ
	virtual Color GetViewColor();

	//���¾���������Ϣ
	virtual void ResetMatrixArray();
	//���ݷֻ�״̬���� ҳ��״̬
	virtual void ResetMatrixSwitchStatus();

public:
	float GetScale();

private:
	void InitData();
	void SaveDataOfScale(int nType);
	void ChangeScale(int type);
	MAP_NODE& GetMapNode();
	int GetNodeOutCount();
	void InvalidateView();
	void ResetViewSize();
	int GetNumBySize(int nSize,int nSqrt);
	XMatrixScreen* GetScreenByIndex(int nIndex);
	void SetCursor(CURSORTYPE type);
	HCURSOR GetCursor(CURSORTYPE type);

	CString GetNameByChannel(int nChannel);
	void ClearVecMatrixScreen();

	void Move(POINTF& point1,POINTF& point2);

private:
	//void OperateOfInitScreenArray();
	void OperateOfScreenArray();

public:
	inline int GetScreenWidth(){return m_nScreenWidth;}
	inline int GetScreenHeight(){return m_nScreenHeight;}
	inline int GetScreenCountH(){return m_nScreenCountH;}
	inline int GetScreenCountV(){return m_nScreenCountV;}
	inline BOOL GetDown(){return m_bDown;}
	inline BOOL GetCreateWnd(){return m_bCreateWnd;}
	inline RECTF GetDragRect(){return m_DragRect;}
	inline VEC_MATRIXSCREEN& GetVecMatrixScreen(){return m_VecMatrixScreen;}

private:

	int m_nScale=100;
	int m_nScreenWidth=200;
	int m_nScreenHeight=112;
	int m_nScreenCountH=2;
	int m_nScreenCountV=2;
	//��갴��λ��
	POINTF m_Point=POINTF(0,0);
	XMatrixScreen* m_pTempScreen=NULL;
	//�������
	CURSORTYPE m_CursorType;
	//�Ƿ���
	BOOL m_bDown=FALSE;
	//��������
	BOOL m_bCreateWnd=FALSE;
	//��ק������
	RECTF m_DragRect;

private:
	VEC_MATRIXSCREEN m_VecMatrixScreen;

};

