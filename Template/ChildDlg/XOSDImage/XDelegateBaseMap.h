#pragma once
#include "XConstant.h"

class XDelegateBaseMap
{
public:
	XDelegateBaseMap();
	~XDelegateBaseMap();

public:

	virtual MAP_IMAGE& GetMapImage()=0;

	virtual int GetHardWareChannel()=0;

	virtual void SendDataOfOSDImage(int nIndex)=0;

	virtual void SetMatrixInputToOutput(int nInputChannel)=0;

};