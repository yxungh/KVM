#pragma once

class XDelegateAddUser
{
public:
	XDelegateAddUser();
	~XDelegateAddUser();

public:
	virtual void SetUserInfo(CString szUserName,CString szPassWd)=0;
	virtual void AddUser()=0;
};