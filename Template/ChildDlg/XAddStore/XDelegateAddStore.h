#pragma once
#include "XConstant.h"
class XDelegateAddStore
{
public:
	XDelegateAddStore();
	~XDelegateAddStore();

public:
	virtual MAP_NODE& GetMapNode()=0;
	virtual MAP_STORE& GetMapStore()=0;
};

