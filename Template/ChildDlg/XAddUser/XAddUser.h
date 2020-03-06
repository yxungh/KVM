#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"

class XDelegateAddUser;

class XAddUser:public XBaseDialog
{
	DECLARE_DYNAMIC(XAddUser)

public:
	XAddUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XAddUser();

	virtual BOOL OnInitDialog();
	//virtual void OnOk();

	// �Ի�������
	enum { IDD = IDD_DIALOG_ADDUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnBnClickedOk();
	afx_msg void OnUpdateEditUsername();
	DECLARE_MESSAGE_MAP()

public:

	inline void SetDelegate(XDelegateAddUser* p){m_pDelegate=p;}

	void CloseDlg();

private:

	void Init();
	void InitData();
	void ReloadInterface();

private:

	XDelegateAddUser* m_pDelegate=nullptr;
	XThemeText m_TextName;
	XThemeText m_TextPassWd;
	XThemeText m_TextTip;

	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;


	
};
