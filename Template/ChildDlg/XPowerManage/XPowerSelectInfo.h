#pragma once

class XPowerSelectInfo
{
public:

	XPowerSelectInfo();
	~XPowerSelectInfo();

public:

	inline void SetPowerName(CString szName){m_szPowerName=szName;}
	inline CString GetPowerName(){return m_szPowerName;}

	inline void SetPowerIndex(int n){m_nPowerIndex=n;}
	inline int GetPowerIndex(){return m_nPowerIndex;}

private:

	CString m_szPowerName;

	int m_nPowerIndex;

};