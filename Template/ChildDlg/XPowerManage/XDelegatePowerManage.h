#pragma once
#include "XConstant.h"

class XDelegatePowerManage
{
public:
	XDelegatePowerManage();
	~XDelegatePowerManage();

public:
	virtual MAP_POWER& GetMapPower()=0;

	virtual MAP_SUBUSER& GetMapSubUser()=0;

	virtual MAP_STORE& GetMapStore()=0;

	virtual CString GetUserName()=0;

	virtual int GetUserID()=0;

	virtual MAP_NODE& GetMapNode()=0;
	virtual MAP_NODEALL& GetMapNodeAll()=0;
};