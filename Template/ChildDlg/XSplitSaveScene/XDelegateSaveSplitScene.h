#pragma once
#include "XConstant.h"


class XDelegateSaveSplitScene
{
public:
	XDelegateSaveSplitScene();
	virtual ~XDelegateSaveSplitScene();

public:
	virtual MAP_BASEVIEW& GetBaseView()=0;
	virtual MAP_SPLITSCENEGROUP& GetMapSplitSceneGroup()=0;

};

