#pragma once
#include "XResult.h"

class XNodeInfo:public XResult
{
public:

	XNodeInfo();
	~XNodeInfo();

public:


	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetNodeType(int n){m_nNodeType=n;}
	inline int GetNodeType(){return m_nNodeType;}

	inline void SetSendType(CString szType){m_szSendType=szType;}
	inline CString GetSendType(){return m_szSendType;}

	inline void SetUpdateMark(int n){m_nUpdateMark=n;}
	inline int GetUpdateMark(){return m_nUpdateMark;}

	inline void SetNodeGroup(int n){m_nGroup=n;}
	inline int GetNodeGroup(){return m_nGroup;}

	inline void SetQueryType(CString szType){m_szQueryType=szType;}
	inline CString GetQueryType(){return m_szQueryType;}

	inline void SetNodeMaster(int n){m_nMaster=n;}
	inline int GetNodeMaster(){return m_nMaster;}
	
private:

	int m_nNodeID=0;
	int m_nNodeType=0;
	CString m_szSendType=_T("");
	int m_nUpdateMark=0;
	int m_nGroup=0;
	int m_nMaster=0;
	CString m_szQueryType=_T("");
};