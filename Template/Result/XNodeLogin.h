#pragma once
#include "XResult.h"

class XNodeLogin:public XResult
{
public:
	XNodeLogin();
	~XNodeLogin();

public:

	inline void SetUserName(CString szName){m_szUserName=szName;}

	inline CString GetUserName(){return m_szUserName;}

	inline void SetNodeID(int n){m_nNodeID=n;}

	inline int GetNodeID(){return m_nNodeID;}

private:

	CString m_szUserName=_T("");
	int m_nNodeID=0;
};
