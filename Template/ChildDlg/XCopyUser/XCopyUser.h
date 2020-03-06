#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"

class XDelegateCopyUser;

class XCopyUser:public XBaseDialog
{
	DECLARE_DYNAMIC(XCopyUser)

public:
	XCopyUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XCopyUser();

	virtual BOOL OnInitDialog();
	//virtual void OnOk();

	// 对话框数据
	enum { IDD = IDD_DIALOG_COPYUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedOk();
	afx_msg void OnUpdateEditUsername();
	DECLARE_MESSAGE_MAP()

public:
	inline void SetDelegate(XDelegateCopyUser* p){m_pDelegate=p;}
	inline CString GetUserName(){return m_szUserName;}
	inline CString GetPassWd(){return m_szPassWd;}
	void CloseDlg();

private:

	void Init();
	void InitData();
	void ReloadInterface();

private:
	XDelegateCopyUser* m_pDelegate=nullptr;
	CString m_szUserName=_T("");
	CString m_szPassWd=_T("");

	XThemeText m_TextName;
	XThemeText m_TextPasswd;
	XThemeText m_TextTip;

	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;
};


