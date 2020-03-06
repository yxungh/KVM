#pragma once


class XUserSecurity
{
public:
	XUserSecurity();
	virtual ~XUserSecurity();

public:

	int m_nUserID=0;
	CString m_szKeyMd5=_T("00000000000000000000000000000000");
	int m_nSecurityMark=0;
	int m_nAnswerNum=0;
	std::vector<CString> m_VecQuestion;
	std::vector<CString> m_VecAnswer;


	//·µ»Ø
	//
	CString m_szBanReason=_T("");
	int m_nBanUntilTime=0;
	int m_nTermLogFailTime=0;
	int m_nNetLogFailTime=0;
	int m_nLastSuccessTime=0;
	CString m_szLastLogInfo=_T("");
};

