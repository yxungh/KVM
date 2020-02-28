#pragma once
#include "XConstant.h"

class XChannel
{
public:
	XChannel(void);
	~XChannel(void);
public:
	inline void SetIndex(int n){m_nIndex=n;}
	inline int GetIndex(){return m_nIndex;}

	inline void SetRect(RECTF rect){m_rect=rect;}
	inline RECTF GetRect(){return m_rect;}

private:

	int m_nIndex;
	RECTF m_rect;
};

