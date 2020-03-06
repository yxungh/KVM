#pragma once
#include "XConstant.h"

class XDelegateDeviceServer
{
public:
	XDelegateDeviceServer();
	virtual ~XDelegateDeviceServer();

public:
	virtual VEC_CLIENT& GetVecClient()=0;
	virtual MAP_POWER& GetMapPower()=0;
};

