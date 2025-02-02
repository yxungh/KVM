// XCenterControl.cpp: 实现文件
//

#include "stdafx.h"
#include "XCenterControl.h"
#include "afxdialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "HandleIni.h"
#include "HandlePath.h"
#include "XSendDataManage.h"


// XCenterControl 对话框

IMPLEMENT_DYNAMIC(XCenterControl, XBaseDialog)

XCenterControl::XCenterControl(CWnd* pParent /*=nullptr*/)
	: XBaseDialog(XCenterControl::IDD, pParent)
{

}

XCenterControl::~XCenterControl()
{
	RELEASE(m_pColorWnd1);
	RELEASE(m_pColorWnd2);
	RELEASE(m_pColorWnd3);
	RELEASE(m_pColorWnd4);
}

void XCenterControl::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_TIP,m_TextTip);
	DDX_Control(pDX,IDC_BTN1,m_Btn1);
	DDX_Control(pDX,IDC_BTN2,m_Btn2);
	DDX_Control(pDX,IDC_BTN3,m_Btn3);
	DDX_Control(pDX,IDC_BTN4,m_Btn4);

}


BEGIN_MESSAGE_MAP(XCenterControl, XBaseDialog)
	ON_BN_CLICKED(IDC_BTN1,&XCenterControl::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN2,&XCenterControl::OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN3,&XCenterControl::OnBnClickedBtn3)
	ON_BN_CLICKED(IDC_BTN4,&XCenterControl::OnBnClickedBtn4)
END_MESSAGE_MAP()


// XCenterControl 消息处理程序

BOOL XCenterControl::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	SetWindowText(_C(_T("236"),_T("中控")));
	m_TextTip.SetText(_C(_T("309"),_T("提示:文字以及颜色代表灯当前状态")),TRUE);
	return TRUE;
}

void XCenterControl::Init()
{
	InitColorWnd1();
	InitColorWnd2();
	InitColorWnd3();
	InitColorWnd4();
	InitShow();
}

void XCenterControl::InitShow()
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	int nStatus=HandleIni::GetInt(_T("Info"),_T("Button1"),0,szIniPath);
	if(nStatus)
	{
		CString szText;
		szText.Format(_T("%s%s"),_C(_T("241"),_T("灯1")),_C(_T("245"),_T("开")));

		m_pColorWnd1->SetClicked(TRUE);
		GetDlgItem(IDC_BTN1)->SetWindowText(szText);
		m_Btn1.SetCaption(szText);
	}
	else
	{
		CString szText;
		szText.Format(_T("%s%s"),_C(_T("241"),_T("灯1")),_C(_T("246"),_T("关")));

		m_pColorWnd1->SetClicked(FALSE);
		GetDlgItem(IDC_BTN1)->SetWindowText(szText);
		m_Btn1.SetCaption(szText);
	}
	//////////////////////////////////////////////////////////////////////////
	nStatus=HandleIni::GetInt(_T("Info"),_T("Button2"),0,szIniPath);
	if(nStatus)
	{
		CString szText;
		szText.Format(_T("%s%s"),_C(_T("242"),_T("灯2")),_C(_T("245"),_T("开")));

		m_pColorWnd2->SetClicked(TRUE);
		GetDlgItem(IDC_BTN2)->SetWindowText(szText);
		m_Btn2.SetCaption(szText);
	}
	else
	{
		CString szText;
		szText.Format(_T("%s%s"),_C(_T("242"),_T("灯2")),_C(_T("246"),_T("关")));

		m_pColorWnd2->SetClicked(FALSE);
		GetDlgItem(IDC_BTN2)->SetWindowText(szText);
		m_Btn2.SetCaption(szText);
	}
	//////////////////////////////////////////////////////////////////////////
	nStatus=HandleIni::GetInt(_T("Info"),_T("Button3"),0,szIniPath);
	if(nStatus)
	{
		CString szText;
		szText.Format(_T("%s%s"),_C(_T("243"),_T("灯3")),_C(_T("245"),_T("开")));

		m_pColorWnd3->SetClicked(TRUE);
		GetDlgItem(IDC_BTN3)->SetWindowText(szText);
		m_Btn3.SetCaption(szText);
	}
	else
	{
		CString szText;
		szText.Format(_T("%s%s"),_C(_T("243"),_T("灯3")),_C(_T("246"),_T("关")));

		m_pColorWnd3->SetClicked(FALSE);
		GetDlgItem(IDC_BTN3)->SetWindowText(szText);
		m_Btn3.SetCaption(szText);
	}
	//////////////////////////////////////////////////////////////////////////
	nStatus=HandleIni::GetInt(_T("Info"),_T("Button4"),0,szIniPath);
	if(nStatus)
	{
		CString szText;
		szText.Format(_T("%s%s"),_C(_T("244"),_T("灯4")),_C(_T("245"),_T("开")));

		m_pColorWnd4->SetClicked(TRUE);
		GetDlgItem(IDC_BTN4)->SetWindowText(szText);
		m_Btn4.SetCaption(szText);
	}
	else
	{
		CString szText;
		szText.Format(_T("%s%s"),_C(_T("244"),_T("灯4")),_C(_T("246"),_T("关")));

		m_pColorWnd4->SetClicked(FALSE);
		GetDlgItem(IDC_BTN4)->SetWindowText(szText);
		m_Btn4.SetCaption(szText);
	}
}

void XCenterControl::InitColorWnd1()
{
	CRect rect(CPoint(75,50),CSize(20,19));

	XColorWnd* pColor=new XColorWnd;
	pColor->Create(WS_CHILD|WS_VISIBLE,rect,this,1);
	pColor->ShowWindow(SW_SHOW);
	pColor->UpdateWindow();

	m_pColorWnd1=pColor;
}

void XCenterControl::InitColorWnd2()
{
	CRect rect(CPoint(75,94),CSize(20,19));

	XColorWnd* pColor=new XColorWnd;
	pColor->Create(WS_CHILD|WS_VISIBLE,rect,this,2);
	pColor->ShowWindow(SW_SHOW);
	pColor->UpdateWindow();

	m_pColorWnd2=pColor;
}

void XCenterControl::InitColorWnd3()
{
	CRect rect(CPoint(75,138),CSize(20,19));

	XColorWnd* pColor=new XColorWnd;
	pColor->Create(WS_CHILD|WS_VISIBLE,rect,this,3);
	pColor->ShowWindow(SW_SHOW);
	pColor->UpdateWindow();

	m_pColorWnd3=pColor;
}

void XCenterControl::InitColorWnd4()
{
	CRect rect(CPoint(75,183),CSize(20,19));

	XColorWnd* pColor=new XColorWnd;
	pColor->Create(WS_CHILD|WS_VISIBLE,rect,this,4);
	pColor->ShowWindow(SW_SHOW);
	pColor->UpdateWindow();

	m_pColorWnd4=pColor;
}

void XCenterControl::OnBnClickedBtn1()
{
	CString szText;
	GetDlgItem(IDC_BTN1)->GetWindowText(szText);
	szText.Trim();

	CString szText1;
	szText1.Format(_T("%s%s"),_C(_T("241"),_T("灯1")),_C(_T("245"),_T("开")));

	CString szText2;
	szText2.Format(_T("%s%s"),_C(_T("241"),_T("灯1")),_C(_T("246"),_T("关")));

	if(szText==szText1)
	{
		m_pColorWnd1->SetClicked(FALSE);
		SaveStatus(_T("Button1"),FALSE);
		GetDlgItem(IDC_BTN1)->SetWindowText(szText2);
		m_Btn1.SetCaption(szText2);

		XSendDataManage::GetInstance()->AddSendDataOfLightControl(1,0);
	}
	else if(szText==szText2)
	{
		m_pColorWnd1->SetClicked(TRUE);
		SaveStatus(_T("Button1"),TRUE);
		GetDlgItem(IDC_BTN1)->SetWindowText(szText1);
		m_Btn1.SetCaption(szText1);

		XSendDataManage::GetInstance()->AddSendDataOfLightControl(1,1);
	}

	m_pColorWnd1->Invalidate(TRUE);
}

void XCenterControl::OnBnClickedBtn2()
{
	CString szText;
	GetDlgItem(IDC_BTN2)->GetWindowText(szText);
	szText.Trim();

	CString szText1;
	szText1.Format(_T("%s%s"),_C(_T("242"),_T("灯2")),_C(_T("245"),_T("开")));

	CString szText2;
	szText2.Format(_T("%s%s"),_C(_T("242"),_T("灯2")),_C(_T("246"),_T("关")));

	if(szText==szText1)
	{
		m_pColorWnd2->SetClicked(FALSE);
		SaveStatus(_T("Button2"),FALSE);
		GetDlgItem(IDC_BTN2)->SetWindowText(szText2);
		m_Btn2.SetCaption(szText2);

		XSendDataManage::GetInstance()->AddSendDataOfLightControl(2,0);
	}
	else if(szText==szText2)
	{
		m_pColorWnd2->SetClicked(TRUE);
		SaveStatus(_T("Button2"),TRUE);
		GetDlgItem(IDC_BTN2)->SetWindowText(szText1);
		m_Btn2.SetCaption(szText1);

		XSendDataManage::GetInstance()->AddSendDataOfLightControl(2,1);
	}
	m_pColorWnd2->Invalidate(TRUE);
}

void XCenterControl::OnBnClickedBtn3()
{
	CString szText;
	GetDlgItem(IDC_BTN3)->GetWindowText(szText);
	szText.Trim();

	CString szText1;
	szText1.Format(_T("%s%s"),_C(_T("243"),_T("灯3")),_C(_T("245"),_T("开")));

	CString szText2;
	szText2.Format(_T("%s%s"),_C(_T("243"),_T("灯3")),_C(_T("246"),_T("关")));

	if(szText==szText1)
	{
		m_pColorWnd3->SetClicked(FALSE);
		SaveStatus(_T("Button3"),FALSE);
		GetDlgItem(IDC_BTN3)->SetWindowText(szText2);
		m_Btn3.SetCaption(szText2);

		XSendDataManage::GetInstance()->AddSendDataOfLightControl(3,0);
	}
	else if(szText==szText2)
	{
		m_pColorWnd3->SetClicked(TRUE);
		SaveStatus(_T("Button3"),TRUE);
		GetDlgItem(IDC_BTN3)->SetWindowText(szText1);
		m_Btn3.SetCaption(szText1);

		XSendDataManage::GetInstance()->AddSendDataOfLightControl(3,1);
	}

	m_pColorWnd3->Invalidate(TRUE);
}

void XCenterControl::OnBnClickedBtn4()
{
	CString szText;
	GetDlgItem(IDC_BTN4)->GetWindowText(szText);
	szText.Trim();

	CString szText1;
	szText1.Format(_T("%s%s"),_C(_T("244"),_T("灯4")),_C(_T("245"),_T("开")));

	CString szText2;
	szText2.Format(_T("%s%s"),_C(_T("244"),_T("灯4")),_C(_T("246"),_T("关")));

	if(szText==szText1)
	{
		m_pColorWnd4->SetClicked(FALSE);
		SaveStatus(_T("Button4"),FALSE);
		GetDlgItem(IDC_BTN4)->SetWindowText(szText2);
		m_Btn4.SetCaption(szText2);

		XSendDataManage::GetInstance()->AddSendDataOfLightControl(4,0);
	}
	else if(szText==szText2)
	{
		m_pColorWnd4->SetClicked(TRUE);
		SaveStatus(_T("Button4"),TRUE);
		GetDlgItem(IDC_BTN4)->SetWindowText(szText1);
		m_Btn4.SetCaption(szText1);

		XSendDataManage::GetInstance()->AddSendDataOfLightControl(4,1);
	}
	m_pColorWnd4->Invalidate(TRUE);
}

void XCenterControl::SaveStatus(CString szKey,BOOL b)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
	
	CString szStatus;
	szStatus.Format(_T("%d"),(int)b);
	HandleIni::WriteData(_T("Info"),szKey,szStatus,szIniPath);
}