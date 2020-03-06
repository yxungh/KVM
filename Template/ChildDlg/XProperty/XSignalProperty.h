#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"




class XSignalProperty:public XBaseDialog
{
	DECLARE_DYNAMIC(XSignalProperty)

public:
	XSignalProperty(CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~XSignalProperty();

	// �Ի�������
	enum{IDD=IDD_DIALOG_SPROPERTY};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	void Init();
	void ReloadInterface();

private:
	void OnBtnOk();

private:
	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;




};

