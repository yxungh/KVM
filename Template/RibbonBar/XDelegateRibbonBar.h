#pragma once

//Ribbon工具栏委托类
class XDelegateRibbonBar
{
public:
	XDelegateRibbonBar(void);
	~XDelegateRibbonBar(void);

	//Ribbon显示的类别
	virtual void RibbonBarShowCategory(DWORD_PTR dwData)=0;
};

