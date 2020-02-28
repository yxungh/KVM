#pragma once
#include "..\resource.h"


class XLoginLoad:public CDialogEx
{
	DECLARE_DYNAMIC(XLoginLoad)

public:
	XLoginLoad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XLoginLoad();

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

private:

	void Init();

	void UpdateText();

private:

	CString m_szText;

	int m_nIndex;

};
