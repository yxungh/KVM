#pragma once



class XSubUserInfo
{
public:
	XSubUserInfo();
	~XSubUserInfo();

public:

	inline void SetUserName(CString szName){m_szUserName=szName;}

	inline CString GetUserName(){return m_szUserName;}

	inline void SetID(int n){m_nID=n;}

	inline int GetID(){return m_nID;}

private:

	CString m_szUserName;

	int m_nID;
};