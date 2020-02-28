#pragma once

class XRTSPInfo
{
public:
	XRTSPInfo(void);
	~XRTSPInfo(void);

public:

	//初始化
	void Init(CString szRTSPAddr,CString szRTSPHDAddr,CString szRTSP4KAddr,
			  CString szName);

	CString GetRTSPAddr();

	CString GetRTSPHDAddr();

	CString GetRTSP4KAddr();

	CString GetName();

	void SetRTSPAddr(CString s);

	void SetRTSPHDAddr(CString s);

	void SetRTSP4KAddr(CString s);

	void SetName(CString s);

	void ClearData();

public:

	//RTSP地址
	CString m_RTSPAddr;

	//RTSP HD地址
	CString m_RTSPHDAddr;

	//RTSP 4K地址
	CString m_RTSP4KAddr;

	//名称
	CString m_Name;
};

