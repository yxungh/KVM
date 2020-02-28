#pragma once
#include "XResult.h"


class XAlterNodeName:public XResult
{
public:
	XAlterNodeName();
	~XAlterNodeName();

public:

	inline void SetNodeName(CString szName){m_szNodeName=szName;}
	inline CString GetNodeName(){return m_szNodeName;}

	//inline void SetAlterType(int n){m_nAlterType=n;}
	//inline int GetAlterType(){return m_nAlterType;}

private:

	CString m_szNodeName=_T("");
	//int m_nAlterType;
};