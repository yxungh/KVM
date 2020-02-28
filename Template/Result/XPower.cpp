#include "stdafx.h"
#include "XPower.h"

XPower::XPower()
{

}

XPower::~XPower()
{

}

void XPower::SetUserName(CString szUserName)
{
	m_szUserName=szUserName;
}

CString XPower::GetUserName()
{
	return m_szUserName;
}

void XPower::SetPassWd(CString szPassWd)
{
	m_szPassWd=szPassWd;
}
CString XPower::GetPassWd()
{
	return m_szPassWd;
}