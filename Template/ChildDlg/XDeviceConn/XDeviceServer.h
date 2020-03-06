#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"
#include "XListCtrl.h"


// XDeviceServer 对话框
class XAlterPort;
class XDelegateDeviceServer;

class XDeviceServer: public XBaseDialog
{
	DECLARE_DYNAMIC(XDeviceServer)

public:
	XDeviceServer(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XDeviceServer();

	// 对话框数据
	enum
	{
		IDD=IDD_DIALOG_DEVICESERVER
	};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	inline void SetDelegate(XDelegateDeviceServer* p){m_pDelegate=p;}

private:
	void Init();
	void ReloadInterface();
	void InitListServer();
	void InitListConnClient();
	void InitListData();

	void AddServerListInfo(CString szIP,int nPort);

	int AddClientListInfo(CString szName,CString szIP,int nUserID);
	void SetClientListInfo(int nCount,CString szName,CString szIP,CString szUser);

	CString GetUserNameByID(int nID);

	void AlterPort();
	void AddClient();
	void UpdateClient();
	void DelClient();

public:
	void CloseAlterPortDlg();

private:
	XDelegateDeviceServer* m_pDelegate=NULL;

	XThemeText m_TextServerInfo;
	XThemeText m_TextConnCLient;

	XThemeBtn m_BtnAlter;
	XThemeBtn m_BtnAddClient;
	XThemeBtn m_BtnUpdateClient;
	XThemeBtn m_BtnDelClient;


	XListCtrl m_ServerInfoList;
	XListCtrl m_ClientList;

	XAlterPort* m_pAlterPort=NULL;

};


