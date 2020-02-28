#pragma once
#include "XConstant.h"

class XDelegateLeftWnd
{
public:

	XDelegateLeftWnd();
	~XDelegateLeftWnd();

public:

	virtual CWnd* GetCWND()=0;

	virtual MAP_POWER& GetMapPower()=0;

	virtual MAP_SUBUSER& GetMapSubUser()=0;

	virtual void SetPropertyValue(CString szUserName)=0;

	virtual void SetNodeSelected(CString szNodeName)=0;

	virtual void ShowGroupSeatArrage(CString szGroup)=0;

	virtual void DragEnd(CPoint& point,CRect& rect)=0;

	virtual MAP_NODE& GetMapNode()=0;

	virtual MAP_NODEMAINSEC& GetMapNodeMainSec()=0;

	virtual MAP_NODEGROUP& GetMapNodeGroup()=0;

	virtual MAP_GROUPMAINSEC& GetMapNodeGroupMainSec()=0;

	virtual int GetCurUserID()=0;

	virtual void DelNodeFromGroup(CString szGroupName,int nNodeID)=0;

	virtual BOOL JudgetDelNodeFromGroup(CString szGroupName,int nNodeID)=0;


	//////////////////////////////////////////////////////////////////////////
	virtual void DragGroupToSeat(CString szGroupName,CPoint& point)=0;
	virtual void SwitchPage(int nPage)=0;
	virtual void DrawGroupInScreen(CString szGroupName)=0;
	virtual void SetSeatSelected(CString szGroupName)=0;
	virtual void HidePopMenuBtn()=0;
	//显示按钮
	virtual void ShowPopMenuBtn()=0;
	//切换工具栏
	virtual void ResetRibbonBar()=0;
	//更改组名名称
	virtual void UpdateGroupNameAfterChange(CString szGroupName,CString szName)=0;
	//更新屏幕编排信息
	virtual void UpdateGroupArrageByRemoveNode(CString szGroupName,int nNodeID)=0;
	//获取当前拼接视图放缩
	virtual float GetCurScale()=0;
	
};