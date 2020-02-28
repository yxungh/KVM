#pragma once


class XUserLogStatus
{
public:

	XUserLogStatus();
	~XUserLogStatus();

public:

	inline void SetUserName(CString szName){m_szUserName=szName;}
	inline CString GetUserName(){return m_szUserName;}

	inline void SetUserID(int n){m_nUserID=n;}
	inline int GetUserID(){return m_nUserID;}

	inline void SetNetLogin(BOOL b){m_bNetLogin=b;}
	inline BOOL GetNetLogin(){return m_bNetLogin;}

	inline void SetIP(CString szIP){m_szIP=szIP;}
	inline CString GetIP(){return m_szIP;}

	inline void SetPort(int n){m_nPort=n;}
	inline int GetPort(){return m_nPort;}

	inline void SetNodeLogin(BOOL b){m_bNodeLogin=b;}
	inline BOOL GetNodeLogin(){return m_bNodeLogin;}

	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}
	

private:

	CString m_szUserName;

	int m_nUserID;

	BOOL m_bNetLogin;

	CString m_szIP;

	int m_nPort;

	BOOL m_bNodeLogin;

	int m_nNodeID;

};