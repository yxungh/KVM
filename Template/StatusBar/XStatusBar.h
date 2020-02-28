#pragma once
#include "XConstant.h"

class XDelegateStatusBar;

class XStatusBar
{
public:
	XStatusBar();
	~XStatusBar();

public:
	static XStatusBar* GetInstance();
	void Init();
	inline void SetDelegate(XDelegateStatusBar* p){m_pDelegate=p;}
	void ReloadInterface();
	void SetCurUserName(CString szName);
	void UpdateTime();

	void SetDevideNet(CString szIPAddr,int nPort);

	void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);

private:
	void SetUserElement();
	void SetDeviceElement();

	
private:

	CMFCStatusBar m_StatusBar;
	XDelegateStatusBar* m_pDelegate=NULL;
	CString m_szUserName=_T("");
	CString m_szIP=_T("");
	int m_nPort=0;

};

