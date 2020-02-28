#pragma once


class XOutResoluation
{
public:

	XOutResoluation();
	~XOutResoluation();

public:

	inline void SetValue(unsigned char c){m_Value=c;}
	inline unsigned char GetValue(){return m_Value;}

	inline void SetModel(int n){m_nModel=n;}
	inline int GetModel(){return m_nModel;}

	inline void SetResoluationH(int n){m_nResoluationH=n;}
	inline int GetResoluationH(){return m_nResoluationH;}

	inline void SetResoluationV(int n){m_nResoluationV=n;}
	inline int GetResoluationV(){return m_nResoluationV;}

	inline void SetRefreashRate(int n){m_nRefreshRate=n;}
	inline int GetRefreashRate(){return m_nRefreshRate;}

	inline void SetName(CString szName){m_szName=szName;}
	inline CString GetName(){return m_szName;}


private:

	unsigned char m_Value;

	int m_nModel;

	int m_nResoluationH;

	int m_nResoluationV;

	int m_nRefreshRate;

	CString m_szName;
};