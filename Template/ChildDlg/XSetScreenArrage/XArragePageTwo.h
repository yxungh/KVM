#pragma once
#include "..\resource.h"
#include "XTree.h"
#include "XConstant.h"


// XArragePageTwo 对话框
class XDelegateArragePageTwo;
class XDragWnd;

class XArragePageTwo : public CPropertyPage
{
	DECLARE_DYNAMIC(XArragePageTwo)

public:
	XArragePageTwo();   // 标准构造函数
	virtual ~XArragePageTwo();
	virtual BOOL OnInitDialog();
	

// 对话框数据
	enum { IDD = IDD_DIALOG_SETSCREENARRAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
	//初始化树形控件
	BOOL InitTreeCtrl();
	//初始化图片列表
	BOOL InitImageList();
	//调整布局
	void AdjustLayout();
	//绘制屏幕网格线
	void DrawArea(Graphics& graphics,CRect rect);
	//绘制屏幕
	void DrawScreen(Graphics& graphics,CRect rect);
	//判断其他屏幕是否已经存在该节点
	BOOL DecidedNodeExist(XScreenInfo* pInfo,XScreenInfo*& pScreenInfo,int nNodeID);
	//判断是不是第一次拖拽
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

	//屏幕排列
	VEC_ARRAGE m_VecArrage;
};
