#pragma once
#include "XResult.h"

class XNodeGroup:public XResult
{
public:
	XNodeGroup();
	~XNodeGroup();

public:

	inline void SetGroupName(CString szGroup){m_szGroupName=szGroup;}
	inline CString GetGroupName(){return m_szGroupName;}

	inline void SetGroupID(int n){m_nGroupID=n;}
	inline int GetGroupID(){return m_nGroupID;}

	inline void SetUpdateMark(int n){m_nUpdateMark=n;}
	inline int GetUpdateMark(){return m_nUpdateMark;}

	inline void SetGroupMaster(int n){m_nGroupMaster=n;}
	inline int GetGroupMaster(){return m_nGroupMaster;}

	inline void SetType(int n){m_nType=n;}
	inline int GetType(){return m_nType;}

	inline void SetCreateMode(int n){m_nCreateMode=n;}
	inline int GetCreateMode(){return m_nCreateMode;}

private:

	CString m_szGroupName=_T("");
	int m_nGroupID=0;
	int m_nUpdateMark=0;
	int m_nGroupMaster=0;
	int m_nType=0;
	int m_nCreateMode=0;

};