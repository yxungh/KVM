#pragma once
#include "XResult.h"

class XMatrix:public XResult
{
public:
	XMatrix();
	~XMatrix();

public:

	inline void SetOutputChannel(int n){m_nOutPutChannel=n;}
	inline int GetOutputChannel(){return m_nOutPutChannel;}

	inline void SetMatrixType(CString szType){m_szMatrixType=szType;}
	inline CString GetMatrixType(){return m_szMatrixType;}

private:

	int m_nOutPutChannel=0;
	CString m_szMatrixType=_T("");
};