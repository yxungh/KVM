#pragma once
class XDelegateStatusBar
{
public:
	XDelegateStatusBar();
	~XDelegateStatusBar();

public:

	//ªÒ»°CWnd
	virtual CWnd* GetCWND()=0;
};

