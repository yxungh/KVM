#pragma once
#include "XConstant.h"


class XDelegateIniManage;

class XIniManage
{
public:

	XIniManage();
	~XIniManage();

public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate(XDelegateIniManage* p);

	//更新控件数据显示
	void UpdateControlDataShow(XDATATYPE type,void* pControl);

	//控件数据改变
	void ControlDataChange(XDATATYPE type,void* pControl);

	void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);

	void Operate(OPERATETYPE type,void* pData);

public:


	inline int GetThememIndex()
	{
		return m_nThemeIndex;
	}

private:

	void GetIniData();


private:

	//保存主题
	void SaveDataOfTheme(int n);

private:

	XDelegateIniManage* m_pDelegate;

private:

	//设备IP
	CString m_DeviceIP;

	//设备端口
	int m_DevicePort;

	CString m_szSecondDeviceIP;
	int m_nSecondDevicePort;

	int m_nThemeIndex;

};