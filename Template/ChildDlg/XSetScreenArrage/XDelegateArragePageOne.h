#pragma once
#include "XConstant.h"

class XDelegateArragePageOne
{
public:
	XDelegateArragePageOne();
	~XDelegateArragePageOne();

public:

	virtual MAP_NODE& GetMapNode()=0;
	virtual MAP_NODEGROUP& GetMapNodeGroup()=0;
	virtual CWnd* GetCWND()=0;
};