
#include "stdafx.h"
#include "XResetPassWord.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"


// XResetPassWord ∂‘ª∞øÚ

IMPLEMENT_DYNAMIC(XResetPassWord,XBaseDialog)

XResetPassWord::XResetPassWord(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XResetPassWord::IDD,pParent)
{

}

XResetPassWord::~XResetPassWord()
{
}

void XResetPassWord::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(XResetPassWord,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XResetPassWord::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XResetPassWord::Init()
{
	SetWindowText(_C(_T("357"),_T("÷ÿ÷√√‹¬Î")));

	ReloadInterface();
}

void XResetPassWord::ReloadInterface()
{

}

LRESULT XResetPassWord::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{

	return 0;
}