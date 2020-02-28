#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"


class XAlterName:public XBaseDialog
{
	DECLARE_DYNAMIC(XAlterName)

public:
	XAlterName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XAlterName();

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	// �Ի�������
	enum { IDD = IDD_DIALOG_ALTERNODENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	inline CString GetNodeName(){return m_szNodeName;}

private:

	void Init();
	void InitData();
	void ReloadInterface();

private:

	CString m_szNodeName;
	XThemeText m_TextName;
	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;

};
