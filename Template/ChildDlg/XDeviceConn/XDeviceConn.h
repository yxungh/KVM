#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XBtn.h"
#include "XDelegateDeviceServer.h"
#include "XConstant.h"


// XDeviceConn 对话框
class XDeviceServer;
class XDelegateDeviceConn;

class XDeviceConn: public XBaseDialog,
	public XDelegateDeviceServer
{
	DECLARE_DYNAMIC(XDeviceConn)

public:
	XDeviceConn(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XDeviceConn();

	// 对话框数据
	enum
	{
		IDD=IDD_DIALOG_DEVICECONN
	};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	VEC_CLIENT& GetVecClient() override;
	MAP_POWER& GetMapPower() override;

public:
	inline void SetDelegate(XDelegateDeviceConn* p){m_pDelegate=p;}

public:
	void CloseAlterPortDlg();

private:
	void Init();
	void ReloadInterface();

	void SetServer();
	void SetClient();

private:
	XDelegateDeviceConn* m_pDelegate=NULL;

	XBtn m_BtnServer;
	XBtn m_BtnClient;

	XThemeText m_TextSetver;
	XThemeText m_TextClient;
	XThemeText m_TextTip;


	XDeviceServer* m_pDeviceServer=NULL;


};



