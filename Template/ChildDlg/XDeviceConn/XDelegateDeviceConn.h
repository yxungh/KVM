#pragma once
#include "XConstant.h"

class XDelegateDeviceConn
{
public:
	XDelegateDeviceConn();
	virtual ~XDelegateDeviceConn();

public:
	virtual VEC_CLIENT& GetVecClient()=0;
	virtual MAP_POWER& GetMapPower()=0;

};

