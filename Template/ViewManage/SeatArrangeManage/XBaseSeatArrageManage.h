#pragma once
#include "XBaseViewManage.h"

class XDelegateSeatArrageManage;

class XBaseSeatArrageManage:public XBaseViewManage
{
public:
	XBaseSeatArrageManage();
	virtual ~XBaseSeatArrageManage();

public:

	//视图绘制
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, int noffsetY)=0;

	//视图获取大小
	virtual CSize ViewGetSize()=0;

	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//视图双击
	virtual void ViewLButtonDblClk(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//视图鼠标离开
	virtual void ViewMouseLeave()=0;

	//鼠标滚轮
	virtual BOOL ViewMouseWheel(short zDelta)=0;

	//视图按键提起
	virtual void ViewKeyUp(UINT nChar)=0;

	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//工具栏控制
	virtual void ControlDataChange(XDATATYPE type, void* pControl)=0;

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl)=0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData)=0;

	//改变UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)=0;

	//拖拽结束
	virtual void DragEnd(CPoint& point,CRect& rect)=0;

	//重置视图
	virtual void ResetView()=0;

	//重置左侧面板
	virtual void ResetLeftWnd()=0;

	//重置场景面板
	virtual void ResetSceneWnd()=0;

	//切换视图，清空属性面板
	virtual void ClearProperityWnd()=0;

	//初始化
	virtual void Init()=0;

	//翻译重载界面
	virtual void ReloadInterface()=0;

	//获取页面名称
	virtual CString GetTitle()=0;

	//设置标题
	virtual void SetTitle(CString szTitle)=0;

	//保存数据
	virtual void SaveData(CArchive& arch)=0;

	//读取数据
	virtual void GetData(CArchive& arch)=0;

	//重置数据
	virtual void ResetData()=0;

	//单击选中节点
	virtual void SetNodeSelected(CString szNodeName)=0;

	//显示组坐席
	virtual void ShowGroupSeatArrage(CString szGroup)=0;

	//清空坐席集合
	virtual void ClearInfo(CString szGroupName)=0;
	
	//注销清空页面
	virtual void ClearPage()=0;

	//更新坐席名称
	virtual void UpdateGroupNameAfterAddArrage(CString szName)=0;

	//匹配坐席名称
	virtual void MatchSeatNameByGroupName()=0;

	//更改组名名称
	virtual void UpdateGroupNameAfterChange(CString szGroupName,CString szName)=0;

	//更新屏幕编排信息
	virtual void UpdateGroupArrageByRemoveNode(CString szGroupName,int nNodeID)=0;

	//移除节点更新第二页
	virtual void UpdateScreenAfterRemoveNode(int nNodeID)=0;

	//更新主屏显示（主）
	virtual void UpdateShowMasterAfterRemoveNode(int nMaster)=0;

	//设置视图颜色
	virtual void SetViewColor(Color& color)=0;

	//设置视图颜色
	virtual Color GetViewColor()=0;

	//获取坐席排列删除节点
	//virtual VEC_DEL& GetVecDel()=0;

	//从组中删除节点
	virtual void DelNodeFromGroup(CString szGroupName,int nNodeID)=0;

	//判断能不能删除
	virtual BOOL JudgetDelNodeFromGroup(CString szGroupName,int nNodeID)=0;

	virtual void AdjustMultiVideoWindowSize()=0;

	virtual MAP_PAGE& GetMapPage()=0;

	virtual MAP_TEMPFRAME& GetMapTempFrame()=0;

	//拖拽组到坐席上
	virtual void DragGroupToSeat(CString szGroupName,CPoint& point)=0;

	//点击组切换页面
	virtual void SwitchPage(int nPage)=0;

	//点击输入隐藏菜单按钮
	virtual void HidePopMenuBtn()=0;
	//显示按钮
	virtual void ShowPopMenuBtn()=0;

	//绘制输入组屏幕
	virtual void DrawGroupInScreen(CString szGroupName)=0;

	//点击输出选中页面坐席
	virtual void SetSeatSelected(CString szGroupName)=0;

	//隐藏菜单按钮
	virtual void HideMenuWnd()=0;
	virtual void HideBtn()=0;
	virtual void Unselected()=0;

	//显示绘制坐席按钮
	virtual void ShowSeatDrawWnd()=0;
	virtual void HideSeatDrawWnd()=0;

	virtual void MoveSeatDrawWnd()=0;
	virtual void EnableSeatDrawWnd(BOOL b)=0;

	//获取坐席页面序号
	virtual int GetPageIndex()=0;

	//右键创建组时，把组名称赋给页面
	virtual void SetGroupNameByAddGroupIn(CString szName)=0;


public:

	inline void SetDelegate(XDelegateSeatArrageManage* p){m_pDelegate=p;}

protected:

	XDelegateSeatArrageManage* m_pDelegate;

};