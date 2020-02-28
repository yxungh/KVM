#pragma once
#include "XResult.h"


class XUpdateUserInfo:public XResult
{
public:

	XUpdateUserInfo();
	~XUpdateUserInfo();

public:

	inline void SetType(CString szType){m_szType=szType;}
	inline CString GetType(){return m_szType;}

	inline void SetUserName(CString szName){m_szUserName=szName;}
	inline CString GetUserName(){return m_szUserName;}

	inline void SetUserID(int n){m_nUserID=n;}
	inline int GetUserID(){return m_nUserID;}

	inline void SetUserType(CString szUserType){m_szUserType=szUserType;}
	inline CString GetUserType(){return m_szUserType;}

private:

	CString m_szType=_T("");

	CString m_szUserName=_T("");
	int m_nUserID=0;

	CString m_szUserType=_T("");
};


