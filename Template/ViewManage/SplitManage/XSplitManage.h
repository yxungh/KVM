#pragma once
#include "XBaseSplitManage.h"
#include "XConstant.h"


class XSplitManage:public XBaseSplitManage
{
public:
	XSplitManage();
	virtual ~XSplitManage();


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
	void SetTitle(CString szTitle);
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
	//��ȡ��ǰƴ����ͼ����
	virtual float GetCurScale();

public:
	void ClearVecSignal();
	void ClearVecSplitScreen();

private:
	//��ʼ����Ļ
	void InitScreen();
	void InitData();

	void InvalidateView();
	void ResetViewSize();
	void ChangeScale(int nType);
	void SaveDataOfScale(int nType);
	void ChangeSignalPng(int nScale);
	

	//�����ź���ռ��Ļ
	void CalculateVecScreen(RECTF& rect,VEC_SPLITSCREEN& VecScreen);
	void SetCursor(CURSORTYPE type);
	//�رհ�ť
	void CloseSignal(int nID);
	
	void CloseShowSignal(int nID);
	//��ʾ�˵�
	void ShowMenu();
	void SetMax();
	void SetMin();
	void SetFull();

	void SetSignalUp();
	void SetSignalDown();
	void SetSignalTop();
	void SetSignalBottom();

	//�ж���Ļ�źŸ���
	BOOL DecideSignalCount(VEC_SPLITSCREEN& VecScreen,CString& szRet);
	//���ཻ�ź�ID����
	void GetIntersectSignal(RECTF& rect,std::vector<int>& VecID);
	//��ȡ���
	//int GetSignalLevel();
	//BOOL IsLevelHas(int nLevel);
	//����id��ȡ�ź�
	XSignal* GetSignalByID(int nID);
	int GetVecIndex(XSignal* pSignal);
	//�ƶ��ź�
	void MoveSignal(POINTF& point1,POINTF& point2);

	//�������ģʽ
	void SetLimitModel(int nType);
	void SetAddModel(int nType);

private:

	//����ź�
	void OperateOfClearSignal();
	void OperateOfFullScreen();
	void OperateOfRestore();
	void OperateOfExtend();
	void OperateOfCloseSignal();
	void OperateOfSignalProperty();


public:
	float GetScale();

	void SortSignalByLevel();
	void SetSignalOtherInfo(int nID=0);
	XSplitScreen* GetScreenByIndex(int nIndex);
	//����Ϣ���ø���Ļ
	void SetScreenInfo();
	//���ò��ռ����Ϣ
	void SetLevelUse();
	//����ź�
	//void AddSignal(XSignal* pSignal);
	//����ID�ر��ź�
	void DeleteSignalByID(int nID);
	//���
	void ClearSignal();
	//���ò��
	void SetSignalLevel(int nSignalID,int nLevel);
	//����ź�
	void AddSignal(std::vector<int>& VecIdList);


public:
	inline void SetResulationX(int n){m_nResulationX=n;}
	inline int GetResulationX(){return m_nResulationX;}
	inline void SetResulationY(int n){m_nResulationY=n;}
	inline int GetResulationY(){return m_nResulationY;}

	inline void SetScreenCountX(int n){m_nScreenCountX=n;}
	inline int GetScreenCountX(){return m_nScreenCountX;}
	inline void SetScreenCountY(int n){m_nScreenCountY=n;}
	inline int GetScreenCountY(){return m_nScreenCountY;}
	inline VEC_SPLITSCREEN& GetVecScreen(){return m_VecSplitScreen;}
	inline VEC_SIGNAL& GetVecSignal(){return m_VecSignal;}


	inline void SetStatus(int n){m_nStatus=n;}
	inline int GetStatus(){return m_nStatus;}
	inline void SetSplitID(int n){m_nSplitID=n;}
	inline int GetSplitID(){return m_nSplitID;}
	inline void SetCutUse(int n){m_nCutUse=n;}
	inline int GetCutUse(){return m_nCutUse;}
	inline std::vector<int>& GetVecCutPix(){return m_VecCutPix;}
	inline void SetPixIndex(int n) { m_nPixIndex=n; }
	inline int GetPixIndex() { return m_nPixIndex; }
	inline void SetRealResulationX(int n) { m_nRealResulationX=n; }
	inline int GetRealResulationX() { return m_nRealResulationX; }
	inline void SetRealResulationY(int n) { m_nRealResulationY=n; }
	inline int GetRealResulationY() { return m_nRealResulationY; }
	inline std::vector<int>& GetVecSplitCh(){return m_VecSplitCh;}
	inline std::vector<int>& GetVecLevelList(){return m_VecLevelList;}
	inline std::vector<int>& GetVecIdList(){return m_VecIDList;}

private:
	//����
	int m_nScale=100;
	//��ͼ������Ļ��
	int m_nResulationX=200;
	//��ͼ������Ļ��
	int m_nResulationY=112;
	//�����
	POINTF m_Point;
	//�ź������ƶ����䣩
	RECTF m_Rect;
	//��갴��
	BOOL m_bDown=FALSE;
	//�������
	CURSORTYPE m_CursorType=CURSORTYPE_NORMAL;
	//������źŵ�λ��,���������ź�
	POSITIONTYPE m_PositionType=POSITIONTYPE_NULL;
	//��ɫ���
	//int m_nColorIndex=0;
	//�źŻ���(����ֻ���ڲ˵�����)
	XSignal* m_pTempSignal=NULL;
	//�źŲ��
	//int m_nLevel=0;
	//����ģʽ
	int m_nLimitModel=0;

	//�Ƿ�����ö�
	BOOL m_bQuickTop=FALSE;


private:

	//��ȡ������
	//Ĭ����Ļ����
	int m_nScreenCountX=4;
	int m_nScreenCountY=4;
	//״̬
	int m_nStatus=0;
	//ID
	int m_nSplitID=0;
	//�Զ���ֱ����Ƿ���Ч
	int m_nCutUse=0;
	//�ü��ֱ�����������(Ҫ���浽��Ļ)
	std::vector<int> m_VecCutPix;
	//�ֱ������
	int m_nPixIndex;
	//��Ļ��ʵ�ֱ���
	int m_nRealResulationX=1920;
	int m_nRealResulationY=1080;
	//ƴ��ͨ��
	std::vector<int> m_VecSplitCh;
	//ͨ��ռ��
	std::vector<int> m_VecLevelList;
	//�ź�ID(������)
	std::vector<int> m_VecIDList;


private:

	VEC_SPLITSCREEN m_VecSplitScreen;
	//�����źţ����ڻ����Լ���������
	VEC_SIGNAL m_VecSignal;

};

