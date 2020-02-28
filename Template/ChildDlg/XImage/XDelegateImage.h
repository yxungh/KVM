#pragma once
#include "XConstant.h"


class XDelegateImage
{
public:

	XDelegateImage();
	~XDelegateImage();

public:

	virtual MAP_IMAGE& GetMapImage()=0;

	virtual void SendDataOfOSDImage(int nIndex)=0;

	virtual void SetMatrixInputToOutput(int nInputChannel)=0;
};