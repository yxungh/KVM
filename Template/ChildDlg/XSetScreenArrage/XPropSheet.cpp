// XPropSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "XPropSheet.h"
#include "XTranslationManage.h"


// XPropSheet

IMPLEMENT_DYNAMIC(XPropSheet, CPropertySheet)

XPropSheet::XPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_PageOne);
	AddPage(&m_PageTwo);
}

XPropSheet::XPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_PageOne);
	AddPage(&m_PageTwo);
}

XPropSheet::~XPropSheet()
{
}


BEGIN_MESSAGE_MAP(XPropSheet, CPropertySheet)
END_MESSAGE_MAP()


// XPropSheet 消息处理程序
BOOL XPropSheet::OnInitDialog()
{
	CPropertySheet::OnInitDialog();

	SetWindowText(_C(_T("158"),_T("屏幕排列向导")));

	return TRUE;
}