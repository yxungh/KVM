#include "stdafx.h"
#include "XUserLogStatus.h"

XUserLogStatus::XUserLogStatus():
	m_szUserName(_T("")),
	m_nUserID(0),
	m_bNetLogin(FALSE),
	m_szIP(_T("")),
	m_nPort(0),
	m_bNodeLogin(FALSE),
	m_nNodeID(0)
{

}

XUserLogStatus::~XUserLogStatus()
{

}