#pragma once


//���������ʱ ���ӵĿͻ���
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

