#pragma once
#include "XConstant.h"

class XDelegateNodeLoginUser
{
public:

	XDelegateNodeLoginUser();
	~XDelegateNodeLoginUser();

public:

	virtual MAP_SUBUSER& GetMapSubUser()=0;

	virtual MAP_POWER& GetMapPower()=0;
};