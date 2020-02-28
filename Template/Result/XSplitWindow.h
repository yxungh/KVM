#pragma once
#include "XResult.h"

class XSignal;

class XSplitWindow:public XResult
{
public:
	XSplitWindow();
	virtual ~XSplitWindow();

public:
	CString m_szSplitName=_T("");
	int m_nSignalID=0;
	XSignal* m_pSignal=NULL;

};

class XSignalLevel
{
public:
	int m_nSignalID=0;
	CString m_szType=_T("");
	int m_nLevel=0;

};

