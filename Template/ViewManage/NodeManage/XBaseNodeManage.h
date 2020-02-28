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

	//视图绘制
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, int noffsetY)=0;

	//视图获取大小
	virtual CSize ViewGetSize()=0;

	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

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

	//工具栏
	virtual void ControlDataChange(XDATATYPE type, void* pControl)=0;

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl)=0;

	//重置视图
	virtual void ResetView()=0;

	//重置左侧面板
	virtual void ResetLeftWnd()=0;

	//重置场景面板
	virtual void ResetSceneWnd()=0;

	//切换视图，清空属性面板
	virtual void ClearProperityWnd()=0;

	//获取节点名称
	virtual CString GetTitle()=0;

	//设置页面名称
	virtual void SetTitle(CString szTitle)=0;

	//操作
	virtual void Operate(OPERATETYPE type, void* pData)=0;

	//改变UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)=0;

	//清空连接通道
	virtual void ClearConChannel()=0;

	//清空用户登录状态
	virtual void  ClearUserLoginStatus()=0;

	//注销
	virtual void ClearNode()=0;
	virtual void ClearCloumn()=0;

	//清空节点组
	virtual void ClearNodeGroup()=0;

	//初始化
	virtual void Init()=0;

	//翻译重载界面
	virtual void ReloadInterface()=0;

	//设置属性用户
	virtual void SetPropertyValue(CString szUserName)=0;

	//拖拽结束
	virtual void DragEnd(CPoint& point,CRect& rect)=0;

	//获取节点集合
	virtual MAP_NODE& GetMapNode()=0;

	virtual MAP_NODEALL& GetMapNodeAll()=0;

	virtual MAP_MATRIX& GetMapMatrix()=0;

	virtual MAP_NODEMAINSEC& GetMapNodeMainSec()=0;

	//获取节点组集合
	virtual MAP_NODEGROUP& GetMapNodeGroup()=0;

	virtual MAP_GROUPMAINSEC& GetMapGroupMainSec()=0;

	//设置视图颜色
	virtual void SetViewColor(Color& color)=0;

	//设置视图颜色
	virtual Color GetViewColor()=0;


public:

	inline void SetDelegate(XDelegateNodeManage* p){m_pDelegate=p;}

protected:

	XDelegateNodeManage* m_pDelegate=NULL;

};