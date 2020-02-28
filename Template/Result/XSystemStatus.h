#pragma once
#include "XResult.h"
class XSystemStatus:public XResult
{
public:
	XSystemStatus();
	~XSystemStatus();

public:
	static XSystemStatus* GetInstance();

public:

	int m_nCpuTemp=0;
	int m_nMatrixTemp=0;
	CString m_szCpuUse=_T("");
	CString m_szMemUse=_T("");
};

