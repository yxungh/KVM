#include "stdafx.h"
#include "XSetPassWord.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"


// XSetPassWord 对话框

IMPLEMENT_DYNAMIC(XSetPassWord,XBaseDialog)

XSetPassWord::XSetPassWord(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XSetPassWord::IDD,pParent)
{

}

XSetPassWord::~XSetPassWord()
{
}

void XSetPassWord::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(XSetPassWord,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XSetPassWord::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XSetPassWord::Init()
{
	SetWindowText(_C(_T("356"),_T("更改密码")));

	ReloadInterface();
}

void XSetPassWord::ReloadInterface()
{

}

LRESULT XSetPassWord::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{

	return 0;
}