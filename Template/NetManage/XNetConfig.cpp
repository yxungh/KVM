#include "stdafx.h"
#include "XNetConfig.h"


XNetConfig::XNetConfig()
{
}


XNetConfig::~XNetConfig()
{
}


void XNetConfig::CLear()
{
	m_nIndex=0;
	m_szIP=_T("");
	m_nPort=0;
	m_szMask=_T("");
	m_szGateway=_T("");

	m_bApply=FALSE;
	m_bSave=FALSE;
}