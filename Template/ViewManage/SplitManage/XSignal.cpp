#include "stdafx.h"
#include "XSignal.h"


XSignal::XSignal()
{
	m_Color=Color(255,255,0,0);
}


XSignal::~XSignal()
{
}

RECTF XSignal::GetRectUP()
{
	RECTF rect=m_rect;
	rect.Height=20;
	return rect;
}

RECTF XSignal::GetRectDown()
{
	RECTF rect=m_rect;
	rect.Y+=20;
	rect.Height-=20;
	return rect;
}

RECTF XSignal::GetRectColse()
{
	RECTF rect;

	rect.X=REAL(m_rect.GetRight()-17);
	rect.Y=REAL(m_rect.Y);
	rect.Width=17;
	rect.Height=20;

	return rect;
}

RECTF XSignal::GetRectMax()
{
	RECTF rect;

	rect.X=REAL(m_rect.GetRight()-34);
	rect.Y=REAL(m_rect.Y);
	rect.Width=17;
	rect.Height=20;

	return rect;
}

RECTF XSignal::GetRectMin()
{
	RECTF rect;

	rect.X=REAL(m_rect.GetRight()-51);
	rect.Y=REAL(m_rect.Y);
	rect.Width=17;
	rect.Height=20;

	return rect;
}

RECTF XSignal::GetRectFull()
{
	RECTF rect;

	rect.X=REAL(m_rect.GetRight()-68);
	rect.Y=REAL(m_rect.Y);
	rect.Width=17;
	rect.Height=20;

	return rect;
}

RECTF XSignal::GetRectMenu()
{
	RECTF rect;

	rect.X=REAL(m_rect.GetRight()-81);
	rect.Y=REAL(m_rect.Y);
	rect.Width=17;
	rect.Height=20;

	return rect;
}

