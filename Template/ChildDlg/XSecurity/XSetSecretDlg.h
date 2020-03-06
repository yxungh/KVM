#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"


// XSetSecretDlg 对话框


class XSetSecretDlg: public XBaseDialog
{
	DECLARE_DYNAMIC(XSetSecretDlg)

public:
	XSetSecretDlg(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XSetSecretDlg();

	// 对话框数据
	enum
	{
		IDD=IDD_DIALOG_SECRET
	};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void ReloadInterface();


};


