#pragma once
#include "XConstant.h"


class XDelegateImagePreview
{
public:

	XDelegateImagePreview();
	~XDelegateImagePreview();

public:

	virtual MAP_IMAGE& GetMapImage()=0;
};