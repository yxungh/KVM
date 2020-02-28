#pragma once
class XSceneGroupInfo
{
public:
	XSceneGroupInfo();
	~XSceneGroupInfo();

public:
	inline void SetGroupName(CString szName){m_szGroupName=szName;}
	inline CString GetGroupName(){return m_szGroupName;}

private:
	CString m_szGroupName=_T("");

};

