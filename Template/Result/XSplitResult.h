#pragma once
#include "XResult.h"

class XSplitResult:public XResult
{
public:
	XSplitResult();
	virtual ~XSplitResult();

public:



public:
	CString m_szSplitName=_T("");

	//Add
	int m_nSplitID=0;
	int m_nCutUse=0;
	std::vector<int> m_VecCutPix;
	int m_nPixIndex=0;
	int m_nReaulationH=1920;
	int m_nReaulationV=1080;
	int m_nScreenCountX=0;
	int m_nScreenCountY=0;
	std::vector<int> m_VecSplitCh;
};

