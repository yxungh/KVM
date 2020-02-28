#pragma once
#include "XResult.h"


class XNodeStatus:public XResult
{
public:
	XNodeStatus();
	~XNodeStatus();

public:
	inline void SetHidModel(int n){m_nHidModel=n;}
	inline int GetHidModel(){return m_nHidModel;}


private:

	int m_nHidModel=-1;

};

