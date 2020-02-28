#pragma once

class XPowerListInfo
{
public:
	XPowerListInfo();
	~XPowerListInfo();

public:

	inline void SetPowerIndex(int n){m_nPowerIndex=n;}

	inline int GetPowerIndex(){return m_nPowerIndex;}

	inline void SetSelected(BOOL b){m_bSelected=b;}

	inline BOOL GetSelected(){return m_bSelected;}

	inline void SetHas(BOOL b){m_bHas=b;}

	inline BOOL GetHas(){return m_bHas;}

	inline void SetPowerName(CString szPower){m_szPowerName=szPower;}

	inline CString GetPowerName(){return m_szPowerName;}

private:

	int m_nPowerIndex;

	BOOL m_bSelected;

	BOOL m_bHas;

	CString m_szPowerName;
};