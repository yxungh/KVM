#pragma once
#include "XResult.h"



class XTakeOver:public XResult
{
public:

	XTakeOver();
	~XTakeOver();

public:

	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetTargetID(int n){m_nTargetID=n;}
	inline int GetTargetID(){return m_nTargetID;}

	inline void SetExclusive(BOOL b){m_bExclusive=b;}
	inline BOOL GetExclusive(){return m_bExclusive;}


private:

	int m_nNodeID=0;
	int m_nTargetID=0;
	BOOL m_bExclusive=FALSE;
};