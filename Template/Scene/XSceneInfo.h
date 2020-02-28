#pragma once
class XSceneInfo
{
public:
	XSceneInfo();
	~XSceneInfo();

public:
	inline void SetSceneName(CString szName){m_szName=szName;}
	inline CString GetSceneName(){return m_szName;}

	inline void SetSceneGroupName(CString szName){m_szGroupName=szName;}
	inline CString GetSceneGroupName(){return m_szGroupName;}

private:

	CString m_szName=_T("");
	CString m_szGroupName=_T("");

};

