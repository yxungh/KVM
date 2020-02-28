#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"

// XAddGroup �Ի���

class XAddGroup : public XBaseDialog
{
	DECLARE_DYNAMIC(XAddGroup)

public:
	XAddGroup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XAddGroup();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_DIALOG_ALTERGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
