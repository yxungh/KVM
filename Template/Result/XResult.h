#pragma once

class XResult
{
public:
	XResult();
	~XResult();

public:

	inline void SetResult(int n){m_nResult=n;}
	inline int GetResult(){return m_nResult;}

	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetSendType(CString szType){m_szSendType=szType;}
	inline CString GetSendType(){return m_szSendType;}

	inline void SetSubSendType(CString szType){m_szSubType=szType;}
	inline CString GetSubSendType(){return m_szSubType;}

private:

	int m_nResult=-1;
	int m_nNodeID=0;
	CString m_szSendType=_T("");
	CString m_szSubType=_T("");


};