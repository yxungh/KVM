#pragma once
#include "XConstant.h"

class XDelegateAlterUser
{
public:
	XDelegateAlterUser();
	~XDelegateAlterUser();

	virtual MAP_POWER& GetMapPower()=0;
	virtual CString GetUserName()=0;
	virtual int GetPowerIndexByName(CString szPowerName)=0;

	virtual void AlterUser()=0;
};