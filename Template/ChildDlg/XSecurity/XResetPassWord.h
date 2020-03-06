
#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"


// XResetPassWord �Ի���


class XResetPassWord: public XBaseDialog
{
	DECLARE_DYNAMIC(XResetPassWord)

public:
	XResetPassWord(CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~XResetPassWord();

	// �Ի�������
	enum
	{
		IDD=IDD_DIALOG_RESETPW
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
