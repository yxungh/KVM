#include "StdAfx.h"
#include "XRTSPInfo.h"

XRTSPInfo::XRTSPInfo(void)
{
	m_RTSPAddr=_T("");

	m_RTSPHDAddr=_T("");

	m_RTSP4KAddr=_T("");

	m_Name=_T("");
}

XRTSPInfo::~XRTSPInfo(void)
{

}

CString XRTSPInfo::GetRTSPAddr()
{
	return m_RTSPAddr;
}

CString XRTSPInfo::GetRTSPHDAddr()
{
	return m_RTSPHDAddr;
}

CString XRTSPInfo::GetRTSP4KAddr()
{
	return m_RTSP4KAddr;
}

CString XRTSPInfo::GetName()
{
	return m_Name;
}

void XRTSPInfo::SetRTSPAddr(CString s)
{
	m_RTSPAddr=s;
}

void XRTSPInfo::SetName(CString s)
{
	m_Name=s;
}

void XRTSPInfo::SetRTSPHDAddr(CString s)
{
	m_RTSPHDAddr=s;
}

void XRTSPInfo::SetRTSP4KAddr(CString s)
{
	m_RTSP4KAddr=s;
}

void XRTSPInfo::Init(CString szRTSPAddr,CString szRTSPHDAddr,CString szRTSP4KAddr,
					 CString szName)
{
	m_RTSPAddr=szRTSPAddr;

	m_RTSPHDAddr=szRTSPHDAddr;

	m_RTSP4KAddr=szRTSP4KAddr;

	m_Name=szName;
}

void XRTSPInfo::ClearData()
{
	m_RTSPAddr=_T("");

	m_RTSPHDAddr=_T("");

	m_RTSP4KAddr=_T("");

	m_Name=_T("");
}