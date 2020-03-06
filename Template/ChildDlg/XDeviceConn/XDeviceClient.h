#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"


// XDeviceClient �Ի���


class XDeviceClient: public XBaseDialog
{
	DECLARE_DYNAMIC(XDeviceClient)

public:
	XDeviceClient(CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~XDeviceClient();

	// �Ի�������
	enum
	{
		IDD=IDD_DIALOG_DEVICECLIENT
	};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void ReloadInterface();


};
