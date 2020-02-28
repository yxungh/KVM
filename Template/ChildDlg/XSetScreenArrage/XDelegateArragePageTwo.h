#pragma once
#include "XConstant.h"

class XDelegateArragePageTwo
{
public:
	XDelegateArragePageTwo();
	~XDelegateArragePageTwo();

public:

	virtual MAP_NODE& GetMapNode()=0;
	virtual MAP_NODEGROUP& GetMapNodeGroup()=0;
	virtual CWnd* GetCWND()=0;
	virtual int GetCurUserID()=0;

};