#pragma once
#include "XConstant.h"


class XDelegateIniManage
{
public:

	XDelegateIniManage();
	~XDelegateIniManage();

public:

	virtual void Operate(OPERATETYPE type,void* pData)=0;

	virtual void ChangeTheme(int nType)=0;

};