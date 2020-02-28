#pragma once

#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"

// XMessageBoxDlg �Ի���

class XMessageBoxDlg : public XBaseDialog
{
	DECLARE_DYNAMIC(XMessageBoxDlg)

public:
	XMessageBoxDlg(CString szText, CString szCaption, UINT uType, 
		CWnd* pParent = NULL);

	virtual ~XMessageBoxDlg();

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	// �Ի�������
	enum { IDD = IDD_DIALOG_MESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()


private:

	//��ʼ���ؼ�
	void InitControl();

	//��ʼ����̬�ı��ؼ�
	void InitControlOfStatic();

	//��ʼ����ť�ؼ�
	void InitControlOfButtn();

	//��������
	void AdjustLayout();

	//������̬�ı�����
	void AdjustLayoutOfStatic(CRect& rectDlg);

	//������ť����
	void AdjustLayoutOfButtn(CRect& rectDlg);

	//���
	void Clear();


private:

	CString m_szText;

	CString m_szCaption;

	UINT m_uType;

	XThemeText* m_pStatic;

	XThemeBtn* m_pBtnArr;

	int m_nBtnCount;
};
