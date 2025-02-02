#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"

// XSaveScene 对话框
class XSaveScene : public XBaseDialog
{
	DECLARE_DYNAMIC(XSaveScene)

public:
	XSaveScene(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~XSaveScene();
	virtual BOOL OnInitDialog();

	enum{IDD=IDD_DIALOG_SAVESCENE};


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	inline CString GetName(){return m_szName;}

private:
	void Init();
	void ReloadInterface();

private:
	CString m_szName=_T("");
	XThemeText m_TextName;

	
};
