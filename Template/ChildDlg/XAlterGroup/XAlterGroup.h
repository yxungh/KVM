#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"


// XAlterGroup �Ի���

class XAlterGroup : public XBaseDialog
{
	DECLARE_DYNAMIC(XAlterGroup)

public:
	XAlterGroup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XAlterGroup();

	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALTERGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
