#pragma once
#include "XConstant.h"


class XNodePage
{
public:
	XNodePage();
	~XNodePage();

public:

	inline void SetRectUp(RECTF rect){m_rectUp=rect;}
	inline RECTF GetRectUp(){return m_rectUp;}

	inline void SetRectDown(RECTF rect){m_rectDown=rect;}
	inline RECTF GetRectDown(){return m_rectDown;}


private:

	RECTF m_rectUp;
	RECTF m_rectDown;
};