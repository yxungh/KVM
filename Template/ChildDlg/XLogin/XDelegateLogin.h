#pragma once

class XDelegateLogin
{
public:

	XDelegateLogin();
	~XDelegateLogin();

	virtual void SetLoginUser(CString szUserName,CString szPassWd)=0;

};