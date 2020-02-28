#pragma once
#include "XConstant.h"

class CTemplateView;

class XDelegateMatrixManage
{
public:
	XDelegateMatrixManage();
	~XDelegateMatrixManage();

public:
	virtual MAP_NODE& GetMapNode()=0;
	virtual MAP_MATRIX& GetMapMatrix()=0;
	virtual CTemplateView* GetView()=0;
};

