#pragma once
#include "XThemeBtn.h"
#include "XThemeText.h"

class XBtn;

// XBaseDialog 对话框

class XBaseDialog: public CDialogEx
{
	DECLARE_DYNAMIC(XBaseDialog)

public:
	XBaseDialog(UINT nIDD,CWnd *pParent);   // 标准构造函数
	virtual ~XBaseDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	DECLARE_MESSAGE_MAP()

protected:

	//绘制对话框
	virtual void DrawDlg(CDC* pDC);

	//创建按钮
	void CreateBtn(CWnd* pParent,XBtn* pBtn,CRect rect,
				   UINT nID,CString szPhotoPath=_T(""));

protected:

	//VK_RETURN状态
	BOOL m_bEnableVK_RETURN=FALSE;
	//VK_ESCAPE状态
	BOOL m_bEnableVK_ESCAPE=FALSE;
	//背景颜色
	Color m_BkColor=Color(232,239,242);

	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;

};
