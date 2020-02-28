#pragma once
#include "XResult.h"

class XLoginInfo:public XResult
{
public:
	XLoginInfo();
	~XLoginInfo();

public:

	inline void SetUserName(CString szUser){m_szUserName=szUser;}

	inline CString GetUserName(){return m_szUserName;}

	inline void SetPassWd(CString szPassWd){m_szPassWd=szPassWd;}

	inline CString GetPassWd(){return m_szPassWd;}

	inline void SetUserID(int n){m_nID=n;}

	inline int GetUserID(){return m_nID;}


private:

	CString m_szUserName=_T("");
	CString m_szPassWd=_T("");
	int m_nID=0;

};