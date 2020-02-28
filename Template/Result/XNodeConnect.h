#pragma once
#include "XResult.h"
#include "XConstant.h"


class XNodeConnect:public XResult
{
public:
	XNodeConnect();
	~XNodeConnect();

public:

	inline void SetMaxItem(int n){m_nMaxItem=n;}

	inline int GetMaxItem(){return m_nMaxItem;}

	inline VEC_CONNECT& GetVecConnect(){return m_VecConnect;}

private:

	int m_nMaxItem=0;

	VEC_CONNECT m_VecConnect;
};