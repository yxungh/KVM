#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"

// XAddGroup 对话框

class XAddGroup : public XBaseDialog
{
	DECLARE_DYNAMIC(XAddGroup)

public:
	XAddGroup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XAddGroup();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_DIALOG_ALTERGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBtnClick();
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void ReloadInterface();
	BOOL DecidedExist(CString szName);

public:
	inline CString GetGroupName(){return m_szGroupName;}
	inline void SetTitle(CString szTitle){m_szTitle=szTitle;}
	inline void SetMainSec(BOOL b){m_bMainSec=b;}

private:
	CString m_szGroupName=_T("");
	CString m_szTitle=_T("");
	BOOL m_bMainSec=FALSE;
	XThemeText m_TextName;

};
