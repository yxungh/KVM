#pragma once
#include "..\resource.h"
#include "XConstant.h"
#include "XNetConfig.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"

// XDeviceNet 对话框
class XDelegateDeviceNet;

class XDeviceNet: public XBaseDialog
{
	DECLARE_DYNAMIC(XDeviceNet)

public:
	XDeviceNet(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XDeviceNet();
	virtual BOOL OnInitDialog();
	// 对话框数据
	enum { IDD=IDD_DIALOG_DEVICENET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadiosel1();

	afx_msg void OnBnClickedCheckOpen1();
	afx_msg void OnBnClickedCheckOpen2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:
	inline void SetDelegate(XDelegateDeviceNet* p) { m_pDelegate=p; }

public:

	void SetRadioSelect(int nSelect);
	void ResetShowData(VEC_NETCONFIG& vecConfig);
	void StopTimer();

	void SaveNetConfig();
	void CloseDialog();

private:

	void Init();
	void InitShowData();
	void InitRadio();
	void InitCheckBox();
	void ReloadInterface();
	void ShowControl();
	void GetNetConfig();

	void SaveIP1(CString szIP);
	void SaveIP2(CString szIP);
	void SavePort1(int nPort);
	void SavePort2(int nPort);

	void SetControlRect(int nID,int nTop,int nHeight/*,XThemeText* pText*/);
	void SetStstusByRadio();

	void Open();
	void Close();

private:
	XDelegateDeviceNet* m_pDelegate=NULL;
	DWORD m_dwTimer=0;
	XNetConfig m_config;
	int m_nRadioSel=0;

	//XThemeText m_TextDevice1;
	//XThemeText m_TextDevice2;
	XThemeText m_TextIP1;
	XThemeText m_TextPort1;
	XThemeText m_TextMask1;
	XThemeText m_TextGetWay1;
	XThemeText m_TextIP2;
	XThemeText m_TextPort2;
	XThemeText m_TextMask2;
	XThemeText m_TextGetWay2;
};
