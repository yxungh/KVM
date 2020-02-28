#pragma once
class XNetConfig
{
public:
	XNetConfig();
	~XNetConfig();

public:
	inline void SetIP(CString szIP){m_szIP=szIP;}
	inline CString GetIP(){return m_szIP;}

	inline void SetPort(int nPort){m_nPort=nPort;}
	inline int GetPort(){return m_nPort;}

	inline void SetGateway(CString szGateway){m_szGateway=szGateway;}
	inline CString GetGateway(){return m_szGateway;}

	inline void SetMask(CString szMask){m_szMask=szMask;}
	inline CString GetMask(){return m_szMask;}

	inline void SetApply(BOOL b){m_bApply=b;}
	inline BOOL GetApply(){return m_bApply;}

	inline void SetSave(BOOL b){m_bSave=b;}
	inline BOOL GetSave(){return m_bSave;}

	void CLear();

private:
	int m_nIndex=0;
	CString m_szIP=_T("");
	int m_nPort=0;
	CString m_szMask=_T("");
	CString m_szGateway=_T("");

	BOOL m_bApply=FALSE;
	BOOL m_bSave=FALSE;
};

