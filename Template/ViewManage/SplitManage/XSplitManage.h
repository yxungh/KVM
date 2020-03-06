#pragma once
#include "XBaseSplitManage.h"
#include "XConstant.h"


class XSplitManage:public XBaseSplitManage
{
public:
	XSplitManage();
	virtual ~XSplitManage();


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
	void SetTitle(CString szTitle);
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
	//获取当前拼接视图放缩
	virtual float GetCurScale();

public:
	void ClearVecSignal();
	void ClearVecSplitScreen();

private:
	//初始化屏幕
	void InitScreen();
	void InitData();

	void InvalidateView();
	void ResetViewSize();
	void ChangeScale(int nType);
	void SaveDataOfScale(int nType);
	void ChangeSignalPng(int nScale);
	

	//计算信号所占屏幕
	void CalculateVecScreen(RECTF& rect,VEC_SPLITSCREEN& VecScreen);
	void SetCursor(CURSORTYPE type);
	//关闭按钮
	void CloseSignal(int nID);
	
	void CloseShowSignal(int nID);
	//显示菜单
	void ShowMenu();
	void SetMax();
	void SetMin();
	void SetFull();

	void SetSignalUp();
	void SetSignalDown();
	void SetSignalTop();
	void SetSignalBottom();

	//判断屏幕信号个数
	BOOL DecideSignalCount(VEC_SPLITSCREEN& VecScreen,CString& szRet);
	//求相交信号ID集合
	void GetIntersectSignal(RECTF& rect,std::vector<int>& VecID);
	//获取层次
	//int GetSignalLevel();
	//BOOL IsLevelHas(int nLevel);
	//根据id获取信号
	XSignal* GetSignalByID(int nID);
	int GetVecIndex(XSignal* pSignal);
	//移动信号
	void MoveSignal(POINTF& point1,POINTF& point2);

	//设置添加模式
	void SetLimitModel(int nType);
	void SetAddModel(int nType);

private:

	//清空信号
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
	//把信息设置给屏幕
	void SetScreenInfo();
	//设置层次占用信息
	void SetLevelUse();
	//添加信号
	//void AddSignal(XSignal* pSignal);
	//根据ID关闭信号
	void DeleteSignalByID(int nID);
	//清空
	void ClearSignal();
	//设置层次
	void SetSignalLevel(int nSignalID,int nLevel);
	//添加信号
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
	//缩放
	int m_nScale=100;
	//视图虚拟屏幕宽
	int m_nResulationX=200;
	//视图虚拟屏幕高
	int m_nResulationY=112;
	//鼠标点击
	POINTF m_Point;
	//信号区域（移动不变）
	RECTF m_Rect;
	//鼠标按下
	BOOL m_bDown=FALSE;
	//鼠标类型
	CURSORTYPE m_CursorType=CURSORTYPE_NORMAL;
	//鼠标在信号的位置,用于拉伸信号
	POSITIONTYPE m_PositionType=POSITIONTYPE_NULL;
	//颜色序号
	//int m_nColorIndex=0;
	//信号缓存(现在只用于菜单功能)
	XSignal* m_pTempSignal=NULL;
	//信号层次
	//int m_nLevel=0;
	//限制模式
	int m_nLimitModel=0;

	//是否快速置顶
	BOOL m_bQuickTop=FALSE;


private:

	//获取到数据
	//默认屏幕排列
	int m_nScreenCountX=4;
	int m_nScreenCountY=4;
	//状态
	int m_nStatus=0;
	//ID
	int m_nSplitID=0;
	//自定义分辨率是否生效
	int m_nCutUse=0;
	//裁剪分辨率上下左右(要保存到屏幕)
	std::vector<int> m_VecCutPix;
	//分辨率序号
	int m_nPixIndex;
	//屏幕真实分辨率
	int m_nRealResulationX=1920;
	int m_nRealResulationY=1080;
	//拼接通道
	std::vector<int> m_VecSplitCh;
	//通道占用
	std::vector<int> m_VecLevelList;
	//信号ID(代表层次)
	std::vector<int> m_VecIDList;


private:

	VEC_SPLITSCREEN m_VecSplitScreen;
	//整体信号，用于绘制以及其他操作
	VEC_SIGNAL m_VecSignal;

};

