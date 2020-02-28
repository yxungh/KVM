#pragma once
#include "XConstant.h"

class XDelegateUserManage
{
public:

	XDelegateUserManage();
	~XDelegateUserManage();

public:

	virtual void Operate(OPERATETYPE type,void* pData)=0;

	virtual void SetCurUserName(CString szName)=0;

	virtual void SetCurUserID(int n)=0;

	virtual CString GetCurUserName()=0;

	virtual int GetCurUserID()=0;

	virtual void SetLogin(BOOL b)=0;

	virtual BOOL GetLogin()=0;

	//virtual void SetStatusBarInfo()=0;

	virtual void ClearNode()=0;

	virtual void ClearCloumn()=0;

	virtual void ClearTree()=0;

	virtual void ClearNodeGroup()=0;

	virtual void ClearPage()=0;

	virtual void ClearConChannel()=0;

	virtual void ClearUserLoginStatus()=0;

	virtual void SaveData()=0;

	virtual void ClearUserIDALL()=0;

	virtual void ClearSceneTree()=0;

	virtual void InsertItemToTree(CString szUserName)=0;

	virtual void DeleteItemFromTree(CString szUserName)=0;

	//设备节点通道个数
	virtual void SetHardWareChannel(int n)=0;

	//矩阵型号
	virtual void SetMatrixModel(CString szModel)=0;

	virtual MAP_NODE& GetMapNode()=0;

	virtual MAP_NODEALL& GetMapNodeAll()=0;
};