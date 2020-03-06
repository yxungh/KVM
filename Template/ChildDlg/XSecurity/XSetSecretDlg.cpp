#include "stdafx.h"
#include "XSetSecretDlg.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"


// XSetSecretDlg 对话框

IMPLEMENT_DYNAMIC(XSetSecretDlg,XBaseDialog)

XSetSecretDlg::XSetSecretDlg(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XSetSecretDlg::IDD,pParent)
{

}

XSetSecretDlg::~XSetSecretDlg()
{
}

void XSetSecretDlg::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	//DDX_Control(pDX,IDC_STATIC_INFO,m_TextInfo);
	//DDX_Control(pDX,IDC_STATIC_COPYRIGHT,m_TextCopyRight);
	//DDX_Control(pDX,IDC_STATIC_FPGA,m_TextFPGA);
	//DDX_Control(pDX,IDC_STATIC_VER,m_TextVer);
	//DDX_Control(pDX,IDC_STATIC_UPDATELOG,m_TextUpdate);
	//DDX_Control(pDX,IDC_STATIC_VER2,m_TextVer2);
	//DDX_Control(pDX,IDC_STATIC_UPDATELOG2,m_TextUpdate2);
	//DDX_Control(pDX,IDC_STATIC_VER3,m_TextVer3);
	//DDX_Control(pDX,IDC_STATIC_UPDATELOG3,m_TextUpdate3);
	//DDX_Control(pDX,IDC_BTN_UPDATE,m_BtnUpdate);
	//DDX_Control(pDX,ID_BTN_OK,m_BtnOk);

}


BEGIN_MESSAGE_MAP(XSetSecretDlg,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XSetSecretDlg::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XSetSecretDlg::Init()
{
	SetWindowText(_C(_T("355"),_T("设置密保")));

	ReloadInterface();
}

void XSetSecretDlg::ReloadInterface()
{

}

LRESULT XSetSecretDlg::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{

	return 0;
}