#pragma once
class XDelegateStatusBar
{
public:
	XDelegateStatusBar();
	~XDelegateStatusBar();

public:

	//��ȡCWnd
	virtual CWnd* GetCWND()=0;
};

