#pragma once
#include "XResult.h"

class XOSDImage:public XResult
{
public:
	XOSDImage();
	~XOSDImage();

public:

	inline void SetPicIndex(int n){m_nPicIndex=n;}
	inline int GetPicIndex(){return m_nPicIndex;}


private:

	int m_nPicIndex=0;
};
