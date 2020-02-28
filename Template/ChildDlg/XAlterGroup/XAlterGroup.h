#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"


// XAlterGroup 对话框

class XAlterGroup : public XBaseDialog
{
	DECLARE_DYNAMIC(XAlterGroup)

public:
	XAlterGroup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XAlterGroup();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_ALTERGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
	
private:
	void Init();
	void ReloadInterface();
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));
	BOOL DecidedExist(CString szName);

public:

	inline CString GetGroupName(){return m_szGroupName;}


private:
	CString m_szGroupName;
	XThemeText m_TextName;
};
