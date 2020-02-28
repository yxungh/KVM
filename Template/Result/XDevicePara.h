#pragma once
#include "XResult.h"

class XDevicePara:public XResult
{
public:

	XDevicePara();
	~XDevicePara();

public:

	inline void SetHardWareChannel(int n){m_nHardWareChannel=n;}
	inline int GetHardWareChannel(){return m_nHardWareChannel;}

	inline void SetMatrixModel(CString szMode){m_szMatrixModel=szMode;}
	inline CString GetMatrixModel(){return m_szMatrixModel;}

	inline void SetFPGAVer(CString szVer){m_szFPGAVer=szVer;}
	inline CString GetFPGAVer(){return m_szFPGAVer;}

private:

	int m_nHardWareChannel=0;
	CString m_szMatrixModel=_T("");
	CString m_szFPGAVer=_T("");
};
