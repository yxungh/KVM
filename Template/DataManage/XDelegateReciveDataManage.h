#pragma once
#include "XConstant.h"

class XDelegateReciveDataManage
{
public:
	XDelegateReciveDataManage(void);
	~XDelegateReciveDataManage(void);

	//����
	virtual void Operate(OPERATETYPE type, void* pData) = 0;
};

