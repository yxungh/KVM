#pragma once
#include "..\resource.h"
#include "XTree.h"
#include "XConstant.h"


// XArragePageTwo �Ի���
class XDelegateArragePageTwo;
class XDragWnd;

class XArragePageTwo : public CPropertyPage
{
	DECLARE_DYNAMIC(XArragePageTwo)

public:
	XArragePageTwo();   // ��׼���캯��
	virtual ~XArragePageTwo();
	virtual BOOL OnInitDialog();
	

// �Ի�������
	enum { IDD = IDD_DIALOG_SETSCREENARRAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();	

public:
	void Init();
	void InitData();
	void InitTree();
	void ReloadInterface();
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));
	void ClearVecScreenInfo();

	MAP_NODE& GetMapNode();

public:

	inline void SetDelegate(XDelegateArragePageTwo* p){m_pDelegate=p;}
	inline void SetScreenRow(int n){m_nScreenRow=n;}
	inline int GetScreenRow(){return m_nScreenRow;}
	inline void SetScreenColumn(int n){m_nScreenColumn=n;}
	inline int GetScreenColumn(){return m_nScreenColumn;}

	inline void SetGroupName(CString szName){m_szGroupName=szName;}
	inline CString GetGroupName(){return m_szGroupName;}
	
private:
	//��ʼ�����οؼ�
	BOOL InitTreeCtrl();
	//��ʼ��ͼƬ�б�
	BOOL InitImageList();
	//��������
	void AdjustLayout();
	//������Ļ������
	void DrawArea(Graphics& graphics,CRect rect);
	//������Ļ
	void DrawScreen(Graphics& graphics,CRect rect);
	//�ж�������Ļ�Ƿ��Ѿ����ڸýڵ�
	BOOL DecidedNodeExist(XScreenInfo* pInfo,XScreenInfo*& pScreenInfo,int nNodeID);
	//�ж��ǲ��ǵ�һ����ק
	BOOL DecidedMaster();

	void SetVecArrage();
	int GetMasterNode();
	CString GetArrayInfo();
	CString GetArrayMatrix();

public:

	XDragWnd* CreateDragWnd();
	void CreateWnd();
	void DragEnd(CPoint point);

	void ClearVecArrage();

private:

	XDelegateArragePageTwo* m_pDelegate;

	XTree m_TreeCtrl;
	CImageList m_ImageList;

	int m_nScreenRow;
	int m_nScreenColumn;

	CString m_szGroupName;
	XDragWnd* m_pDragWnd;

private:

	VEC_SCREENINFO m_VecScreenInfo;

	//��Ļ����
	VEC_ARRAGE m_VecArrage;
};
