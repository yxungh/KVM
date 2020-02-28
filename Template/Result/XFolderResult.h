#pragma once
#include "XResult.h"

class XFolderResult:public XResult
{
public:
	XFolderResult();
	~XFolderResult();

public:

	inline void SetSubType(CString szType){m_szSubType=szType;}
	inline CString GetSubType(){return m_szSubType;}



public:
	CString m_szSubType;
	int m_nID=0;
	int m_nParentID=0;
	CString m_szFolderName;

};

