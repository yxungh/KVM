#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XBtn.h"




class XSecurityDlg:public XBaseDialog
{

	DECLARE_DYNAMIC(XSecurityDlg)

public:
	XSecurityDlg(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XSecurityDlg();

	// 对话框数据
	enum
	{
		IDD=IDD_DIALOG_SECURITY
	};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	void Init();
	void ReloadInterface();

private:

	void SetSecret();
	void AlterPassWd();
	void ResetPassWd();

private:

	XBtn m_BtnSecret;
	XBtn m_BtnPassWd;
	XBtn m_BtnResetPassWd;

	XThemeText m_TextSecret;
	XThemeText m_TextPassWd;
	XThemeText m_TextResetPassWd;



};

