#pragma once


class XDelegateSendDataManage
{
public:
	XDelegateSendDataManage();
	~XDelegateSendDataManage();
public:

	virtual BOOL SendData(char* pData, int nDataLen)=0;
	virtual CString GetCurIP()=0;
};