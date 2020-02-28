#pragma once
#include "..\resource.h"
#include "XListCtrl.h"
#include "XBaseDialog.h"

class XDelegateNodeLoginUser;

class XNodeLoginUser:public XBaseDialog
{
	DECLARE_DYNAMIC(XNodeLoginUser)

public:
	XNodeLoginUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XNodeLoginUser();

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	// 对话框数据
	enum { IDD = IDD_DIALOG_NODELOGINUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	void SetDelegate(XDelegateNodeLoginUser* p);

	inline CString GetUserName(){return m_szUserName;}

	inline CString GetPassWd(){return m_szPassWd;}

	inline int GetUserID(){return m_nUserID;}

private:

	void Init();

	void InitList();

	void SetList();

	void ReloadInterface();

	int AddListInfo(int nUserID,CString szUserName);

	void SetListInfo(int nCount,int nUserID,CString szUserName);

private:

	XDelegateNodeLoginUser* m_pDelegate;
	CString m_szUserName;
	CString m_szPassWd;
	int m_nUserID;
	XListCtrl m_ListNodeLogin;
};
