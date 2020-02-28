#pragma once

class XScreenInfo
{
public:
	XScreenInfo();
	~XScreenInfo();

public:
	inline void SetIndex(int n){m_nIndex=n;}
	inline int GetIndex(){return m_nIndex;}

	inline void SetNodeName(CString szName){m_szNodeName=szName;}
	inline CString GetNodeName(){return m_szNodeName;}

	inline void SetHave(BOOL b){m_bHave=b;}
	inline BOOL GetHave(){return m_bHave;}

	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetMaster(BOOL b){m_bMaster=b;}
	inline BOOL GetMaster(){return m_bMaster;}

	inline void SetRowIndex(int n){m_nRowIndex=n;}
	inline int GetRowIndex(){return m_nRowIndex;}
	inline void SetColumnIndex(int n){m_nColumnIndex=n;}
	inline int GetColumnIndex(){return m_nColumnIndex;}

private:

	int m_nIndex;
	CString m_szNodeName;
	int m_nNodeID;

	BOOL m_bHave;
	BOOL m_bMaster;

	int m_nRowIndex;
	int m_nColumnIndex;
};