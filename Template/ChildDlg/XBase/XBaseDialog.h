#pragma once
#include "XThemeBtn.h"
#include "XThemeText.h"

class XBtn;

// XBaseDialog �Ի���

class XBaseDialog: public CDialogEx
{
	DECLARE_DYNAMIC(XBaseDialog)

public:
	XBaseDialog(UINT nIDD,CWnd *pParent);   // ��׼���캯��
	virtual ~XBaseDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	DECLARE_MESSAGE_MAP()

protected:

	//���ƶԻ���
	virtual void DrawDlg(CDC* pDC);

	//������ť
	void CreateBtn(CWnd* pParent,XBtn* pBtn,CRect rect,
				   UINT nID,CString szPhotoPath=_T(""));

protected:

	//VK_RETURN״̬
	BOOL m_bEnableVK_RETURN=FALSE;
	//VK_ESCAPE״̬
	BOOL m_bEnableVK_ESCAPE=FALSE;
	//������ɫ
	Color m_BkColor=Color(232,239,242);

	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;

};
