#pragma once
#include "XBaseMatrixManage.h"



class XMatrixManage:public XBaseMatrixManage
{
public:
	XMatrixManage();
	~XMatrixManage();

public:

	//视图绘制
	virtual void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY);
	//视图获取大小
	virtual CSize ViewGetSize();
	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//视图双击
	virtual void ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//视图鼠标离开
	virtual void ViewMouseLeave();
	//鼠标滚轮
	virtual BOOL ViewMouseWheel(short zDelta);
	//视图按键提起
	virtual void ViewKeyUp(UINT nChar);
	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);
	//工具栏控制
	virtual void ControlDataChange(XDATATYPE type,void* pControl);
	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type,void* pControl);
	//操作
	virtual void Operate(OPERATETYPE type,void* pData);
	//改变UI
	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);
	//初始化
	virtual void Init();
	//翻译重载界面
	virtual void ReloadInterface();
	//获取页面名称
	virtual CString GetTitle();
	//设置页面名称
	virtual void SetTitle(CString szTitle);
	//重置视图
	virtual void ResetView();
	//重置左侧面板
	virtual void ResetLeftWnd();
	//重置场景面板
	virtual void ResetSceneWnd();
	//切换视图，清空属性面板
	virtual void ClearProperityWnd();
	//拖拽结束
	virtual void DragEnd(CPoint& point,CRect& rect);
	//设置视图颜色
	virtual void SetViewColor(Color& color);
	//设置视图颜色
	virtual Color GetViewColor();

	//更新矩阵排列信息
	virtual void ResetMatrixArray();
	//根据分会状态设置 页面状态
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
	//鼠标按下位置
	POINTF m_Point=POINTF(0,0);
	XMatrixScreen* m_pTempScreen=NULL;
	//鼠标类型
	CURSORTYPE m_CursorType;
	//是否按下
	BOOL m_bDown=FALSE;
	//创建窗口
	BOOL m_bCreateWnd=FALSE;
	//推拽框区域
	RECTF m_DragRect;

private:
	VEC_MATRIXSCREEN m_VecMatrixScreen;

};

