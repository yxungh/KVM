#pragma once
#include "..\resource.h"


class XSeatArrageName:public CDialogEx
{
	DECLARE_DYNAMIC(XSeatArrageName)

public:
	XSeatArrageName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XSeatArrageName();

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	// �Ի�������
	enum { IDD = IDD_DIALOG_SEATARRAGENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	inline CString GetName(){return m_szName;}

	inline CString GetGroup(){return m_szGroup;}

private:

	void Init();
	void InitData();
	void InitCombo();
	void ReloadInterface();

private:

	CString m_szName;
	CString m_szGroup;
	CString m_szTempGroup;


};