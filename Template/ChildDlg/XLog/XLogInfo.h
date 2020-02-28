#pragma once
class XLogInfo
{
public:
	XLogInfo();
	~XLogInfo();

public:

	time_t m_Time=0;
	CString m_szEvent=_T("");
	CString m_szUser=_T("");
	CString m_szTargetUser=_T("");
	CString m_szIpAddr=_T("");
	CString m_szTermID=_T("");
	int m_nTermNo=0;
	int m_nTermCh=0;
	CString m_szTargetTermID=_T("");
	int m_nTargetTermNo=0;
	CString m_szNote=_T("");
};

