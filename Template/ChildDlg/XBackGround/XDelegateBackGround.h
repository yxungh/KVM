#pragma once
#include "XConstant.h"
class XPage;

class XDelegateBackGround
{
public:
	XDelegateBackGround();
	~XDelegateBackGround();

	virtual MAP_PAGE& GetMapPage()=0;

	virtual XPage* GetCurPage()=0;
};