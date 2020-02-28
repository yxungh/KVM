// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XLoginLoad.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"

// XLoginLoad 对话框

IMPLEMENT_DYNAMIC(XLoginLoad, CDialogEx)

	XLoginLoad::XLoginLoad(CWnd* pParent /*=NULL*/)
	: CDialogEx(XLoginLoad::IDD, pParent),
	m_szText(_T("")),
	m_nIndex(0)
{
}

XLoginLoad::~XLoginLoad()
{
}

void XLoginLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XLoginLoad, CDialogEx)

	ON_WM_TIMER()
END_MESSAGE_MAP()


// XLoginLoad 消息处理程序

void XLoginLoad::OnOK()
{
	__super::OnOK();
}

BOOL XLoginLoad::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Init();

	return TRUE;
}

void XLoginLoad::Init()
{
	m_szText=_C(_T("27"),_T("密码"));

	UpdateText();

	SetTimer(1, 500, NULL);
}

void XLoginLoad::OnTimer(UINT_PTR nIDEvent)
{
	UpdateText();
	__super::OnTimer(nIDEvent);
}

void XLoginLoad::UpdateText()
{
	m_nIndex++;

	CString szText=m_szText;

	for(int i=0;i<6;i++)
	{
		if (i<m_nIndex)
		{
			szText+=_T("．");
		}
		else
		{
			szText+=_T("　");
		}
	}

	if (m_nIndex>=6)
	{
		m_nIndex=0;
	}

	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(szText);

	CRect rectText;
	GetDlgItem(IDC_STATIC_INFO)->GetWindowRect(&rectText);
	ScreenToClient(&rectText);

	InvalidateRect(&rectText);
}
