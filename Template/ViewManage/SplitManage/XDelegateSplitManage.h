#pragma once


class CTemplateView;


class XDelegateSplitManage
{
public:
	XDelegateSplitManage();
	virtual ~XDelegateSplitManage();

public:
	virtual CTemplateView* GetView()=0;
	virtual CWnd* GetCWND()=0;

};

