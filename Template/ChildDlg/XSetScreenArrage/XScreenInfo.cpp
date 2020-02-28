#include "stdafx.h"
#include "XScreenInfo.h"

XScreenInfo::XScreenInfo():
	m_nIndex(0),
	m_szNodeName(_T("")),
	m_bHave(FALSE),
	m_nNodeID(0),
	m_bMaster(FALSE),
	m_nColumnIndex(0),
	m_nRowIndex(0)
{

}

XScreenInfo::~XScreenInfo()
{

}