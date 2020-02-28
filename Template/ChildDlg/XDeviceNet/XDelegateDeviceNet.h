#pragma once
#include "XConstant.h"

class XDelegateDeviceNet
{
public:
	XDelegateDeviceNet();
	~XDelegateDeviceNet();

public:

	virtual void SetIPAddr1(CString szIP)=0;
	virtual void SetIPAddr2(CString szIP)=0;
	virtual void SetPort1(int n)=0;
	virtual void SetPort2(int n)=0;

	virtual CString GetDeviceIP()=0;
	virtual int GetDevicePort()=0;
	virtual CString GetDevice2IP()=0;
	virtual int GetDevice2Port()=0;

	virtual CString GetDeviceMask()=0;
	virtual CString GetDevice2Mask()=0;

	virtual CString GetDeviceGateway()=0;
	virtual CString GetDevice2Gateway()=0;

	virtual void SetSendApplyTime(DWORD dwTime)=0;

	virtual BOOL GetLogin()=0;

	virtual void SetDeviceSelect(int nSelect)=0;

	virtual void ConnectNetSelect()=0;

	virtual BOOL GetNetStatus()=0;

	virtual void Operate(OPERATETYPE type,void* pData)=0;
};