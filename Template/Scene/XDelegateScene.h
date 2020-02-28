#pragma once
#include "XConstant.h"

class XDelegateScene
{
public:
	XDelegateScene();
	~XDelegateScene();

	virtual CWnd* GetCWND()=0;
	virtual void OpenScene(int nData)=0;
	virtual MAP_SPLITSCENE& GetMapSplitScene()=0;
	virtual MAP_SPLITSCENEGROUP& GetMapSplitSceneGroup()=0;
};

