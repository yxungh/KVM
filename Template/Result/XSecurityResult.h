#pragma once
#include "XResult.h"


class XSecurityResult:public XResult
{
public:
	XSecurityResult();
	virtual ~XSecurityResult();

public:
	CString m_szUserType=_T("");
	CString m_szUserName=_T("");
	int m_nUserID=0;
};

