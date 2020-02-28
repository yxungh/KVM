#pragma once
#include "XResult.h"


class XStoreList:public XResult
{
public:
	XStoreList();
	~XStoreList();
public:

	inline void SetUserID(int n){m_nUserID=n;}
	inline int GetUserID(){return m_nUserID;}

private:
	int m_nUserID=0;

};

