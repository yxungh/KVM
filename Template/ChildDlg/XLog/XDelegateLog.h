#pragma once
#include "XConstant.h"
class XDelegateLog
{
public:
	XDelegateLog();
	~XDelegateLog();

public:
	virtual MAP_POWER& GetMapPower()=0;
	virtual MAP_NODE& GetMapNode()=0;
};

