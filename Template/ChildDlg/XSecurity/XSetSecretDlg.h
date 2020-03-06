#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"


// XSetSecretDlg �Ի���


class XSetSecretDlg: public XBaseDialog
{
	DECLARE_DYNAMIC(XSetSecretDlg)

public:
	XSetSecretDlg(CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~XSetSecretDlg();

	// �Ի�������
	enum
	{
		IDD=IDD_DIALOG_SECRET
	};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void ReloadInterface();


};


