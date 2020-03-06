#pragma once


//当作服务端时 连接的客户端
class XClient
{
public:
	XClient();
	virtual ~XClient();

public:
	CString m_szServerIP=_T("");
	int m_nServerPort=0;

	CString m_szClientName=_T("");
	CString m_szClientIP=_T("");
	int m_nUserID=0;




};

