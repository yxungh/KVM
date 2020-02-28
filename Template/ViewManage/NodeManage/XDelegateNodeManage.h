#pragma once
#include "XConstant.h"

class CTemplateView;

class XDelegateNodeManage
{
public:
	XDelegateNodeManage();
	~XDelegateNodeManage();

public:

	virtual CTemplateView* GetView()=0;

	virtual void SetHardWareChannel(int n)=0;

	virtual void SetMatrixModel(CString szModel)=0;

	virtual void SetFPGAVersion(CString szVer)=0;

	virtual MAP_SUBUSER& GetMapSubUser()=0;

	virtual MAP_POWER& GetMapPower()=0;

	virtual VEC_DEL& GetVecDel()=0;

	virtual VEC_USERIDALL& GetVecUserIDAll()=0;

	virtual CWnd* GetCWND()=0;

	virtual CString GetCurUserName()=0;

	virtual BOOL GetLogin()=0;

	//virtual void SetSeatArrageMaster(int nMaster)=0;

	virtual void ClearInfo(CString szGroupName)=0;

	//更新坐席名称
	virtual void UpdateGroupNameAfterAddArrage(CString szName)=0;
	//移除节点更新第二页
	virtual void UpdateScreenAfterRemoveNode(int nNodeID)=0;
	//更新主屏显示（主）
	virtual void UpdateShowMasterAfterRemoveNode(int nMaster)=0;
	//匹配坐席名称
	virtual void MatchSeatNameByGroupName()=0;

	//更新矩阵排列信息
	virtual void ResetMatrixArray()=0;
	//根据分会状态设置 页面状态
	virtual void ResetMatrixSwitchStatus()=0;
	//右键创建组时，把组名称赋给页面
	virtual void SetGroupNameByAddGroupIn(CString szName)=0;

};