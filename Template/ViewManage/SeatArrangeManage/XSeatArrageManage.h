#pragma once
#include "XBaseSeatArrageManage.h"
#include "XDelegateBackGround.h"
#include "XDelegateArragePageTwo.h"
#include "XDelegateArragePageOne.h"

class XMultiVideoWindowFrame; 
class XMenuWnd;
class XSeatMap;
class XSeatArrage;
class XSeatDraw;
class XAlignLeft;
class XBaseWnd;
class XSetScreenArrage;
class XSeatArrageDlg;

class XSeatArrageManage:public XBaseSeatArrageManage,
						public XDelegateBackGround,
						public XDelegateArragePageTwo,
						public XDelegateArragePageOne
{
public:
	XSeatArrageManage();
	virtual ~XSeatArrageManage();

public:

	//视图绘制
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, int noffsetY);
	//视图获取大小
	virtual CSize ViewGetSize();
	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//视图双击
	virtual void ViewLButtonDblClk(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//视图鼠标离开
	virtual void ViewMouseLeave();
	//鼠标滚轮
	virtual BOOL ViewMouseWheel(short zDelta);
	//视图按键提起
	virtual void ViewKeyUp(UINT nChar);
	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//工具栏
	virtual void ControlDataChange(XDATATYPE type, void* pControl);
	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl);
	//操作
	virtual void Operate(OPERATETYPE type, void* pData);
	//改变UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI);
	//保存数据
	virtual void SaveData(CArchive& arch);
	//读取数据
	virtual void GetData(CArchive& arch);
	//重置数据
	virtual void ResetData();
	//拖拽结束
	virtual void DragEnd(CPoint& point,CRect& rect);
	//重置视图
	virtual void ResetView();
	//重置左侧面板
	virtual void ResetLeftWnd();
	//重置场景面板
	virtual void ResetSceneWnd();
	//切换视图，清空属性面板
	virtual void ClearProperityWnd();
	//初始化
	virtual void Init();
	//翻译重载界面
	virtual void ReloadInterface();
	//获取页面名称
	virtual CString GetTitle();
	//设置标题
	virtual void SetTitle(CString szTitle);
	//显示组坐席
	virtual void ShowGroupSeatArrage(CString szGroup);
	//单击选中节点
	virtual void SetNodeSelected(CString szNodeName);
	//清空坐席集合
	virtual void ClearInfo(CString szGroupName);
	//注销清空页面
	virtual void ClearPage();
	//更新坐席名称
	virtual void UpdateGroupNameAfterAddArrage(CString szName);
	//匹配坐席名称
	virtual void MatchSeatNameByGroupName();
	//更改组名名称
	virtual void UpdateGroupNameAfterChange(CString szGroupName,CString szName);
	//更新屏幕编排信息
	virtual void UpdateGroupArrageByRemoveNode(CString szGroupName,int nNodeID);
	//移除节点更新第二页
	virtual void UpdateScreenAfterRemoveNode(int nNodeID);
	//更新主屏显示（主）
	virtual void UpdateShowMasterAfterRemoveNode(int nMaster);
	//设置视图颜色
	virtual void SetViewColor(Color& color);
	//设置视图颜色
	virtual Color GetViewColor();
	//获取坐席排列删除节点
	//virtual VEC_DEL& GetVecDel();

	//从组中删除节点
	virtual void DelNodeFromGroup(CString szGroupName,int nNodeID);
	//判断能不能删除
	BOOL JudgetDelNodeFromGroup(CString szGroupName,int nNodeID);	
	virtual void AdjustMultiVideoWindowSize();
	virtual MAP_PAGE& GetMapPage();
	virtual MAP_TEMPFRAME& GetMapTempFrame();
	virtual MAP_NODE& GetMapNode();
	virtual MAP_NODEGROUP& GetMapNodeGroup();
	virtual CWnd* GetCWND();

	//获取当前用户
	virtual int GetCurUserID();
	//拖拽组到坐席上
	virtual void DragGroupToSeat(CString szGroupName,CPoint& point);
	//获取当前页面
	virtual XPage* GetCurPage();
	//点击组切换页面
	virtual void SwitchPage(int nPage);
	//点击输入隐藏菜单按钮
	virtual void HidePopMenuBtn();
	//显示按钮
	virtual void ShowPopMenuBtn();
	//绘制输入组屏幕
	virtual void DrawGroupInScreen(CString szGroupName);
	//点击输出选中页面坐席
	virtual void SetSeatSelected(CString szGroupName);

	//隐藏菜单按钮
	virtual void HideMenuWnd();
	virtual void HideBtn();
	virtual void Unselected();

	//显示绘制坐席按钮
	virtual void ShowSeatDrawWnd();
	virtual void HideSeatDrawWnd();
	virtual void MoveSeatDrawWnd();
	virtual void EnableSeatDrawWnd(BOOL b);

	//获取坐席页面序号
	virtual int GetPageIndex();

	//右键创建组时，把组名称赋给页面
	virtual void SetGroupNameByAddGroupIn(CString szName);

public:

	constexpr inline int GetSeatRow(){return m_nSeatRow;}
	constexpr inline int GetSeatColumn(){return m_nSeatColumn;}
	constexpr inline void SetSeatRow(int n){m_nSeatRow=n;}
	constexpr inline void SetSeatColumn(int n){m_nSeatColumn=n;}

private:

	void InitData();
	//刷新视图
	void InvalidateView();
	//重置视图大小
	void ResetViewSize();
	//改变缩放
	void ChangeScale(int nTYpe);
	//保存缩放
	void SaveDataOfScale(int nType);
	//重置
	void ResetSeatRange();
	//光标
	void SetCursor(CURSORTYPE type);
	//鼠标
	HCURSOR GetCursor(CURSORTYPE type);
	//移动信号
	void MoveSignal(POINTF& point1,POINTF& point2);
	void MoveSignalOfNew(POINTF& point1, POINTF& point2);
	void MoveSignalOfCopy(POINTF& point1, POINTF& point2);

	//判断节点是否在组集合中
	BOOL JudgeNodeInVec(VEC_ARRAGE& VecArrage,int nNodeID);
	
	//添加拖拽frame
	void AddDragFrame();

	//设置全部非选中坐席
	void SetVecSeatSelect(XSeat* p);
	void SetVecSeatUnselect();
	void SetSeatSelect(XSeat* p,BOOL b);
	//选中屏幕
	void SetVecScreenSelect(XScreen* p);
	void SetVecScreenUnselect();
	void SetScreenSelect(XScreen* p,BOOL b);

	//根据坐标
	XScreen* GetScreenByIndex(int nIndex);
	//保存屏幕排列信息
	void SetVecArrage();
	//获取排列矩阵
	CString GetArrayInfo();
	//获取矩阵排列
	CString GetArrayMatrix();
	//根据节点名称获取ID
	int GetNodeIDByName(CString szNodeName);
	XNode* GetNodeByID(int nNodeID);

	//删除坐席
	void DeleteSeat(int nIndex);

	//获取元素序号
	int GetVecSeatIndex(VEC_SEAT& VecSeat);
	//拷贝排列集合(去除删除的)
	void CopyArray(VEC_ARRAGE& VecArrage,int nNodeID);
	//删除主之后，查找第一个不为零的节点
	int GetMasterInArray();
	//根据节点ID查找屏幕
	XScreen* GetScreenByNodeID(int nNodeID);
	//获取组信息
	XNodeGroupInfo* GetNodeGroupInfoByName(CString szGroupName);

public:

	//获取比例
	float GetScale();

	//坐席按钮菜单
	XMenuWnd* CreateMenuWnd();
	void CreateMenuWnd(CPoint& point);
	void ShowMenuWnd();
	void ShowMenu();

	void ShowBtn();
	void ShowPopBtn();
	void HidePopBtn();

	//底图
	XSeatMap* CreateSeatMapWnd();
	void OnBtnBaseMap();

	//排列
	XSeatArrage* CreateSeatArrageWnd();
	void OnBtnArrage();

	//绘制坐席按钮
	void CreateSeatDrawWnd();
	void CreateSeatDrawWnd(CPoint& point);
	void DrawSeat();
	
	//创建对齐悬浮按钮
	void CreateAlignWnd();
	RECTF GetRectBySelectedSeat(VEC_SEAT& VecSeat);
	void ShowALignWnd();
	void MoveAlignWnd();
	void HideAlignWnd();

	//对齐响应函数
	void OnAlignLeft();
	void OnAlignHorzion();
	void OnAlignRight();
	void OnAlignTop();
	void OnAlignVertical();
	void OnAlignBottom();

	//创建悬浮按钮
	void CreateSuspendBtn(XBaseWnd* pWnd,CRect& rect,CString szImage);

	//计算原点位置
	void CacluOrgPoint(CSize& size);

	
public:

	//属性更新
	void UpdateMultiWindowByPropertyChange(XSeat* pSeat,int nType);

private:

	void OperateOfSaveSeat();
	void OperateOfSendSeat();
	void OperateOfClearSeat();
	void OperateOfSetBg();
	void OperateOfSetBtnStatus();

	void OperateOfAlignLeft();
	void OperateOfAlignHorizon();
	void OperateOfAlignRight();
	void OperateOfAlignUp();
	void OperateOfAlignDown();
	void OperateOfAlignVertical();
	void OperateOfAlignSame();

	void OperateOfAlignHSame();
	void OperateOfAlignVSame();
	void OperateOfAlignWidth();
	void OperateOfAlignHeight();

	void OperateOfScreenArray();
public:

	void ClearDragFrame();

private:

	void ClearMapPage();
	void ClearVecArrage();
	void ClearMapAlign();

private:

	//缩放
	int m_nScale=100;
	//行
	int m_nSeatRow=0;
	//列
	int m_nSeatColumn=0;
	//鼠标点击点
	POINTF m_Point;
	//左键按下
	BOOL m_bLBtnDown=FALSE;
	//鼠标点击开始点
	POINTF m_BeginPoint=POINTF(0,0);
	//鼠标结束点
	POINTF m_EndPoint=POINTF(0,0);
	//坐席区域
	RECTF m_rect;
	//新建完成区域
	RECTF m_EndRect;
	//移动完成
	RECTF m_DragRect;
	//屏幕相对于页面偏移
	POINTF m_DeviationPoint=POINTF(0,0);

private:
	//点击工具栏坐席按钮
	static BOOL m_bFlag;

	//页面序号
	static int m_nPageIndex;

	const int m_nFirstPage=1;
	const int m_nSecondPage=2;

	//鼠标形状
	static CURSORTYPE m_CursorType;
	//鼠标在信号的位置,用于拉伸信号
	static POSITIONTYPE m_PositionType;
	
	//拖拽Frame
	XMultiVideoWindowFrame* m_pDragFrame=NULL;

	//当前页面（目前两个页面）
	static XPage* m_pPage;
	static BOOL m_bFirstPage;

	//按下Ctrl是否，创建拖动页面
	static BOOL m_bCreateDrag;
	//屏幕缓存
	static XScreen* m_pTempScreen;
	//坐席缓存
	static XSeat* m_pTempSeat;

	//菜单按钮
	static XMenuWnd* m_pMenuWnd;
	static XSeatMap* m_pSeatMap;
	static XSeatArrage* m_pSeatArrage;

	//绘制坐席按钮
	static XSeatDraw* m_pSeatDraw;
	static BOOL m_bMenuFlag;

	//是否创建对齐按钮
	static BOOL m_bCreateAlignWnd;

private:
	//坐席页面
	MAP_PAGE m_MapPage;
	//选中坐席(不用清空)
	VEC_SEAT m_VecTempSeat;
	//临时Frame集合。用于选中某个frame，不用清空
	MAP_TEMPFRAME m_MapFrame;
	//第二页缓存
	MAP_TEMPFRAME m_MapSecondFrame;
	//屏幕排列
	VEC_ARRAGE m_VecArrage;
	//对齐悬浮按钮
	MAP_ALIGN m_MapAlign;
};
