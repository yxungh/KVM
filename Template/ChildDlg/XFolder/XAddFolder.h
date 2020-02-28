#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"


class XAddFolder:public XBaseDialog
{

	DECLARE_DYNAMIC(XAddFolder)

public:
	XAddFolder(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XAddFolder();

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	// 对话框数据
	enum
	{
		IDD=IDD_DIALOG_ADDFOLDER
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	afx_msg void OnUpdateEdit();
	DECLARE_MESSAGE_MAP()


public:
	inline CString GetName(){return m_szName;}

private:
	void Init();
	void ReloadInterface();
	void OnBtnOk();


private:
	XThemeText m_TextName;
	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;

	CString m_szName=_T("");

};

