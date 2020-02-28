#pragma once

class XRTSPInfo
{
public:
	XRTSPInfo(void);
	~XRTSPInfo(void);

public:

	//��ʼ��
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

	//RTSP��ַ
	CString m_RTSPAddr;

	//RTSP HD��ַ
	CString m_RTSPHDAddr;

	//RTSP 4K��ַ
	CString m_RTSP4KAddr;

	//����
	CString m_Name;
};

