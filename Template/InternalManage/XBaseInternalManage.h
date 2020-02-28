#pragma once
#include "XConstant.h"


class XDelegateInternalManage;

class XBaseInternalManage
{
public:

	XBaseInternalManage();
	virtual ~XBaseInternalManage();

public:

	//初始化
	virtual void Init()=0;

	//初始化停靠面板
	virtual void InitPane()=0;

	//工具栏控件数据变化
	virtual void ControlDataChange(XDATATYPE type)=0;

	virtual BOOL AppClose()=0;

	virtual void HandleUDPMsg(WPARAM wParam,LPARAM lParam)=0;

	virtual void Operate(OPERATETYPE type,void* pData)=0;

	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)=0;

	virtual void AddDocument()=0;

	virtual void SetViewColor(Color& color)=0;

	virtual void AdjustMultiVideoWindowSize()=0;
	virtual void HideMenuWnd()=0;


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

public:

	//设置委托
	void SetDelegate(XDelegateInternalManage* p);

protected:

	XDelegateInternalManage* m_pDelagate;
};