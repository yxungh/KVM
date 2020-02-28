#pragma once
#include "XResult.h"

class XLogPack:public XResult
{
public:
	XLogPack();
	~XLogPack();


public:

	time_t m_time=0;
	CString m_szUserName=_T("");
	CString m_szRealName=_T("");
	CString m_szType=_T("");
	int m_nCount=0;



};

