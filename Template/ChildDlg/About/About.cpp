// XAbout.cpp : 实现文件
//

#include "stdafx.h"
#include "About.h"
#include "afXDialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"


// XAbout 对话框

IMPLEMENT_DYNAMIC(XAbout, XBaseDialog)

XAbout::XAbout(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAbout::IDD, pParent)
{

}

XAbout::~XAbout()
{
}

void XAbout::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_INFO,m_TextInfo);
	DDX_Control(pDX,IDC_STATIC_COPYRIGHT,m_TextCopyRight);
	DDX_Control(pDX,IDC_STATIC_FPGA,m_TextFPGA);
	DDX_Control(pDX,IDC_STATIC_VER,m_TextVer);
	DDX_Control(pDX,IDC_STATIC_UPDATELOG,m_TextUpdate);
	DDX_Control(pDX,IDC_STATIC_VER2,m_TextVer2);
	DDX_Control(pDX,IDC_STATIC_UPDATELOG2,m_TextUpdate2);
	DDX_Control(pDX,IDC_STATIC_VER3,m_TextVer3);
	DDX_Control(pDX,IDC_STATIC_UPDATELOG3,m_TextUpdate3);
	DDX_Control(pDX,IDC_BTN_UPDATE,m_BtnUpdate);
	DDX_Control(pDX,ID_BTN_OK,m_BtnOk);
	
}


BEGIN_MESSAGE_MAP(XAbout, XBaseDialog)
	//ON_BN_CLICKED(IDC_BTN_UPDATE,&XAbout::OnBnClickedBtnUpdate)
	//ON_BN_CLICKED(IDOK,&XAbout::OnBnClickedOk)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XAbout::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XAbout::Init()
{
	SetWindowText(_C(_T("111"),_T("关于")));

	//about
	CString szAbout;
	szAbout.Format(_T("%s %s"),APP_NAME,APP_VERSION);
	//m_TextInfo.SetLeft(TRUE);
	m_TextInfo.SetText(szAbout,TRUE);
	
	//CopyRight
	//m_TextCopyRight.SetLeft(TRUE);
	m_TextCopyRight.SetText(_T("Copyright (C) 2018-2019"),TRUE);

	//fpga
	CString szFPGA;
	szFPGA.Format(_T("%s %s"),_T("FPGA"),m_szFPGAVer);
	//m_TextFPGA.SetLeft(TRUE);
	m_TextFPGA.SetText(szFPGA,TRUE);

	//updateLog
	CString szUpdateLog;
	//GetDlgItem(IDC_STATIC_VER)->SetWindowText(_T("4.10.5.2"));
	
	m_TextVer.SetText(_T("4.10.5.2"));
	szUpdateLog.Format(_T("%s"),_C(_T("82"),_T("添加输入节点软、硬件版本、监听音频的源节点ID")));
	//m_TextUpdate.SetLeft(TRUE);
	m_TextUpdate.SetText(szUpdateLog,TRUE);

	m_TextVer2.SetText(_T("4.10.6"));
	szUpdateLog.Format(_T("%s"),_C(_T("83"),_T("添加快捷键")));
	//m_TextUpdate2.SetLeft(TRUE);
	m_TextUpdate2.SetText(szUpdateLog,TRUE);

	m_TextVer3.SetText(_T("4.10.7.2"));
	szUpdateLog.Format(_T("%s"),_C(_T("84"),_T("多线程读取节点信息，快捷键关闭")));
	//m_TextUpdate3.SetLeft(TRUE);
	m_TextUpdate3.SetText(szUpdateLog,TRUE);


	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnUpdate.SetCaption(_C(_T("308"),_T("版本日志")));


	SetLogStatus(FALSE);
	SetVerStatus(TRUE);
}

void XAbout::SetLogStatus(BOOL b)
{
	if(b)
	{
		GetDlgItem(IDC_STATIC_VER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_VER2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_VER3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_UPDATELOG)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_UPDATELOG2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_UPDATELOG3)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC_VER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_VER2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_VER3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_UPDATELOG)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_UPDATELOG2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_UPDATELOG3)->ShowWindow(SW_HIDE);
	}
}

void XAbout::SetVerStatus(BOOL b)
{
	if(b)
	{
		if(m_bLogin)
			GetDlgItem(IDC_STATIC_FPGA)->ShowWindow(SW_SHOW);
		else
			GetDlgItem(IDC_STATIC_FPGA)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_COPYRIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_APPICO)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC_FPGA)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_COPYRIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_APPICO)->ShowWindow(SW_HIDE);
	}
}

LRESULT XAbout::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	if(wParam==IDC_BTN_UPDATE)
	{
		//出现log
		SetLogStatus(TRUE);
		SetVerStatus(FALSE);
		GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(SW_HIDE);
		SetWindowText(_C(_T("287"),_T("软件更新日志")));
	}
	else if(wParam==ID_BTN_OK)
	{
		if(m_BtnUpdate.IsWindowVisible())
		{
			XBaseDialog::OnOK();
		}
		else
		{
			SetLogStatus(FALSE);
			SetVerStatus(TRUE);
			GetDlgItem(IDC_BTN_UPDATE)->ShowWindow(SW_SHOW);
			SetWindowText(_C(_T("111"),_T("关于")));
		}
	}

	return 0;
}