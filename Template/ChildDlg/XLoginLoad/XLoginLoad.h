#pragma once
#include "..\resource.h"


class XLoginLoad:public CDialogEx
{
	DECLARE_DYNAMIC(XLoginLoad)

public:
	XLoginLoad(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XLoginLoad();

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

private:

	void Init();

	void UpdateText();

private:

	CString m_szText;

	int m_nIndex;

};
