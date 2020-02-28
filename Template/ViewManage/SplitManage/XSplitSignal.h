#pragma once
#include "XConstant.h"

class XSplitSignal
{
public:
	XSplitSignal();
	virtual ~XSplitSignal();

public:

	inline void SetSignalID(int n){m_nSignalID=n;}
	inline int GetSignalID(){return m_nSignalID;}

	inline void SetRect(RECTF rect){m_rect=rect;}
	inline RECTF GetRect(){return m_rect;}

private:

	int m_nSignalID=0;
	RECTF m_rect;


};

