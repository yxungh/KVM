#pragma once
#include "XConstant.h"


class XDelegateIniManage;

class XIniManage
{
public:

	XIniManage();
	~XIniManage();

public:

	//��ʼ��
	void Init();

	//����ί��
	void SetDelegate(XDelegateIniManage* p);

	//���¿ؼ�������ʾ
	void UpdateControlDataShow(XDATATYPE type,void* pControl);

	//�ؼ����ݸı�
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

	//��������
	void SaveDataOfTheme(int n);

private:

	XDelegateIniManage* m_pDelegate;

private:

	//�豸IP
	CString m_DeviceIP;

	//�豸�˿�
	int m_DevicePort;

	CString m_szSecondDeviceIP;
	int m_nSecondDevicePort;

	int m_nThemeIndex;

};