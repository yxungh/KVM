// XMessageBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XMessageBoxDlg.h"
#include "afxdialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"


#define DLG_WIDTH	400
#define DLG_HEIGHT	150

#define BTN_WIDTH	80
#define BTN_HEIGHT	25

// XMessageBoxDlg 对话框

IMPLEMENT_DYNAMIC(XMessageBoxDlg,XBaseDialog)

XMessageBoxDlg::XMessageBoxDlg(CString szText,CString szCaption,UINT uType,
							   CWnd* pParent): XBaseDialog(XMessageBoxDlg::IDD,pParent)
{
	m_szText=szText;
	m_szCaption=szCaption;
	m_uType=uType;
	m_pStatic=NULL;
	m_pBtnArr=NULL;
	m_nBtnCount=0;
}

XMessageBoxDlg::~XMessageBoxDlg()
{
	Clear();
}

void XMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XMessageBoxDlg,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


// XMessageBoxDlg 消息处理程序

BOOL XMessageBoxDlg::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	SetWindowText(m_szCaption);

	InitControl();
	AdjustLayout();
	CenterWindow();

	return TRUE;
}

void XMessageBoxDlg::InitControl()
{
	InitControlOfStatic();
	InitControlOfButtn();
}

void XMessageBoxDlg::InitControlOfStatic()
{
	m_pStatic=new XThemeText();
	m_pStatic->Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_STATIC_MESSAGEBOXDLG_TEXT);
	//m_pStatic->SetLeft(TRUE);
	m_pStatic->SetText(m_szText,TRUE);
}

void XMessageBoxDlg::InitControlOfButtn()
{
	CString szCaption=_T("");
	CRect rect(0,0,0,0);
	CFont* pFont=GetFont();

	switch(m_uType)
	{
		case MB_OK:
			{
				m_nBtnCount=1;
				m_pBtnArr=new XThemeBtn[m_nBtnCount];
				szCaption=XTranslationManage::GetInstance()->GetTranslationString(_T("1"),_T("确定"));
				m_pBtnArr[0].Create(WS_CHILD|WS_VISIBLE,rect,this,IDC_BTN_MESSAGEBOXDLG_1);
				m_pBtnArr[0].SetCaption(szCaption);
			}
			break;
		case MB_OKCANCEL:
			{
				m_nBtnCount=2;
				m_pBtnArr=new XThemeBtn[m_nBtnCount];
				szCaption=XTranslationManage::GetInstance()->GetTranslationString(_T("2"),_T("取消"));
				m_pBtnArr[0].Create(WS_CHILD|WS_VISIBLE,rect,this,IDC_BTN_MESSAGEBOXDLG_1);
				m_pBtnArr[0].SetCaption(szCaption);


				szCaption=XTranslationManage::GetInstance()->GetTranslationString(_T("1"),_T("确定"));
				m_pBtnArr[1].Create(WS_CHILD|WS_VISIBLE,rect,this,IDC_BTN_MESSAGEBOXDLG_1);
				m_pBtnArr[1].SetCaption(szCaption);


			}
			break;
		case MB_YESNO:
			{
				m_nBtnCount=2;

				m_pBtnArr=new XThemeBtn[m_nBtnCount];

				szCaption=XTranslationManage::GetInstance()->GetTranslationString(_T("4"),_T("否"));
				m_pBtnArr[0].Create(WS_CHILD|WS_VISIBLE,rect,this,IDC_BTN_MESSAGEBOXDLG_1);
				m_pBtnArr[0].SetCaption(szCaption);

				szCaption=XTranslationManage::GetInstance()->GetTranslationString(_T("3"),_T("是"));
				m_pBtnArr[1].Create(WS_CHILD|WS_VISIBLE,rect,this,IDC_BTN_MESSAGEBOXDLG_2);
				m_pBtnArr[1].SetCaption(szCaption);
			}
			break;
		default:
			break;
	}
}

void XMessageBoxDlg::AdjustLayout()
{
	MoveWindow(0,0,DLG_WIDTH,DLG_HEIGHT);

	CRect rect;
	GetClientRect(&rect);

	AdjustLayoutOfStatic(rect);
	AdjustLayoutOfButtn(rect);
}

void XMessageBoxDlg::AdjustLayoutOfStatic(CRect& rectDlg)
{
	CRect rect(20,20,rectDlg.Width()-20,rectDlg.Height()-50);
	m_pStatic->MoveWindow(rect);
}

void XMessageBoxDlg::AdjustLayoutOfButtn(CRect& rectDlg)
{
	CRect rect;

	int nRight=rectDlg.right-10;

	int nBottom=rectDlg.bottom-10;

	for(int i=0; i<m_nBtnCount; i++)
	{
		rect.SetRect(nRight-BTN_WIDTH,nBottom-BTN_HEIGHT,nRight,nBottom);

		nRight=nRight-BTN_WIDTH-10;

		m_pBtnArr[i].MoveWindow(rect);
	}
}

void XMessageBoxDlg::Clear()
{
	if(nullptr!=m_pStatic)
	{
		delete m_pStatic;
		m_pStatic=nullptr;
	}

	if(0!=m_nBtnCount)
	{
		delete[] m_pBtnArr;
		m_pBtnArr=nullptr;
	}
}

void XMessageBoxDlg::OnOK()
{
	switch(m_uType)
	{
		case MB_OK:
			{
				EndDialog(IDOK);
			}
			break;
		case MB_OKCANCEL:
			{
				EndDialog(IDOK);
			}
			break;
		case MB_YESNO:
			{
				EndDialog(IDYES);
			}
			break;
		default:
			break;
	}
}

void XMessageBoxDlg::OnCancel()
{
	switch(m_uType)
	{
		case MB_OK:
			{
				EndDialog(IDOK);
			}
			break;
		case MB_OKCANCEL:
			{
				EndDialog(IDCANCEL);
			}
			break;
		case MB_YESNO:
			{
				EndDialog(IDNO);
			}
			break;
		default:
			break;
	}
}


LRESULT XMessageBoxDlg::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	if(wParam==IDC_BTN_MESSAGEBOXDLG_1)
	{
		switch(m_uType)
		{
			case MB_OK:
				{
					EndDialog(IDOK);
				}
				break;
			case MB_OKCANCEL:
				{
					EndDialog(IDCANCEL);
				}
				break;
			case MB_YESNO:
				{
					EndDialog(IDNO);
				}
				break;
			default:
				break;
		}
	}
	else if(wParam==IDC_BTN_MESSAGEBOXDLG_2)
	{
		switch(m_uType)
		{
			case MB_OK:
				{
					EndDialog(IDOK);
				}
				break;
			case MB_OKCANCEL:
				{
					EndDialog(IDOK);
				}
				break;
			case MB_YESNO:
				{
					EndDialog(IDYES);
				}
				break;
			default:
				break;
		}
	}
	else if(wParam==IDC_BTN_MESSAGEBOXDLG_3)
	{

	}

	return 0;
}