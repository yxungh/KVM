#pragma once
class XDelegateUpdate
{
public:
	XDelegateUpdate();
	~XDelegateUpdate();

	virtual CString GetCurIP()=0;
	virtual int GetCurPort()=0;



};

