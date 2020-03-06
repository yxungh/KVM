#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"


// XAlterPort 对话框


class XAlterPort: public XBaseDialog
{
	DECLARE_DYNAMIC(XAlterPort)

public:
	XAlterPort(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XAlterPort();

	// 对话框数据
	enum
	{
		IDD=IDD_DIALOG_ALTERPORT
	};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	void CloseDlg();

private:
	void Init();
	void ReloadInterface();

	void OnBtnOk();

private:
	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;
	XThemeText m_TextPort;
	XThemeText m_TextTip;



};

