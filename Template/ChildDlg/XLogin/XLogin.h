#pragma once

#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"

class XDelegateLogin;

class XLogin:public XBaseDialog
{
	DECLARE_DYNAMIC(XLogin)

public:
	XLogin(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XLogin();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	//virtual void OnOk();

	// 对话框数据
	enum { IDD=IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持	
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:

	inline void SetDelegate(XDelegateLogin* p){m_pDelegate=p;}

public:

	void SetDlgStatus(BOOL b);
	void StopTimer();

	void CloseDlg();

private:

	void Init();
	void InitData();
	void ReloadInterface();
	void SaveUserName(CString szUserName);
	void SetLoginLoad();
	void UpdateText();
	void ClickOk();

private:

	XDelegateLogin* m_pDelegate=nullptr;

private:

	CString m_szText=_T("");
	int m_nIndex=0;
	long m_dLoginTime=0;

	XThemeText m_TextName;
	XThemeText m_TextPassWd;
	XThemeText m_TextLoad;

	XThemeBtn m_BtnOK;
	XThemeBtn m_BtnCancel;
};
