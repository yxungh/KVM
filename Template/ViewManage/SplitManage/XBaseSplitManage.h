#pragma once
#include "XBaseViewManage.h"
class XDelegateSplitManage;

class XBaseSplitManage:public XBaseViewManage
{
public:
	XBaseSplitManage();
	virtual ~XBaseSplitManage();

public:

	//视图绘制
	virtual void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY)=0;

	//视图获取大小
	virtual CSize ViewGetSize()=0;

	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//视图双击
	virtual void ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//视图鼠标离开
	virtual void ViewMouseLeave()=0;

	//鼠标滚轮
	virtual BOOL ViewMouseWheel(short zDelta)=0;

	//视图按键提起
	virtual void ViewKeyUp(UINT nChar)=0;

	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY)=0;

	//工具栏控制
	virtual void ControlDataChange(XDATATYPE type,void* pControl)=0;

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type,void* pControl)=0;

	//操作
	virtual void Operate(OPERATETYPE type,void* pData)=0;

	//改变UI
	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)=0;

	//初始化
	virtual void Init()=0;

	//翻译重载界面
	virtual void ReloadInterface()=0;

	//获取页面名称
	virtual CString GetTitle()=0;

	//设置页面名称
	virtual void SetTitle(CString szTitle)=0;

	//重置视图
	virtual void ResetView()=0;

	//重置左侧面板
	virtual void ResetLeftWnd()=0;

	//重置场景面板
	virtual void ResetSceneWnd()=0;

	//切换视图，清空属性面板
	virtual void ClearProperityWnd()=0;

	//拖拽结束
	virtual void DragEnd(CPoint& point,CRect& rect)=0;

	//设置视图颜色
	virtual void SetViewColor(Color& color)=0;

	//设置视图颜色
	virtual Color GetViewColor()=0;

	//获取当前拼接视图放缩
	virtual float GetCurScale()=0;

public:
	inline void SetDelegate(XDelegateSplitManage* p){m_pDelegate=p;}

protected:
	XDelegateSplitManage* m_pDelegate=NULL;

};

