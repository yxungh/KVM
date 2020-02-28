#pragma once
#include "XConstant.h"

class XDelegateTranslationManage
{
public:
	XDelegateTranslationManage();
	~XDelegateTranslationManage();

public:

	virtual void Operate(OPERATETYPE type,void* pData)=0;

	virtual void ReloadDocTitle()=0;
	
};