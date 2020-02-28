#pragma once

class XSeatSceneInfo
{
public:
	XSeatSceneInfo();
	~XSeatSceneInfo();

public:

	inline void SetSeatSceneName(CString szName){m_szSceneName=szName;}
	inline CString GetSeatSceneName(){return m_szSceneName;}

	inline void SetGroupName(CString szGroup){m_szGroupName=szGroup;}
	inline CString GetGroupName(){return m_szGroupName;}

	inline void SetInGroup(BOOL b){m_bInGroup=b;}
	inline BOOL GetInGroup(){return m_bInGroup;}


private:
	CString m_szSceneName=_T("");
	CString m_szGroupName=_T("");
	BOOL m_bInGroup=FALSE;
};