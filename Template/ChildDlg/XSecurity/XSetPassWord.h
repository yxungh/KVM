#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"


// XSetPassWord �Ի���


class XSetPassWord: public XBaseDialog
{
	DECLARE_DYNAMIC(XSetPassWord)

public:
	XSetPassWord(CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~XSetPassWord();

	// �Ի�������
	enum
	{
		IDD=IDD_DIALOG_SETPASSED
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