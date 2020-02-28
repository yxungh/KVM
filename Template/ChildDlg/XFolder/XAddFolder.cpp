#include "stdafx.h"
#include "XAddFolder.h"
#include "XConstant.h"
#include "XHandleVerification.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"


IMPLEMENT_DYNAMIC(XAddFolder,XBaseDialog)

XAddFolder::XAddFolder(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAddFolder::IDD,pParent)
{
}

XAddFolder::~XAddFolder()
{
}

void XAddFolder::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_NAME,m_TextName);
	DDX_Control(pDX,ID_OK,m_BtnOk);
	DDX_Control(pDX,ID_CANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XAddFolder,XBaseDialog)
	ON_EN_UPDATE(IDC_EDIT_NAME,&XAddFolder::OnUpdateEdit)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


// XAddFolder ��Ϣ�������

void XAddFolder::OnOk()
{
	XBaseDialog::OnOK();
}

BOOL XAddFolder::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();

	return TRUE;
}

void XAddFolder::Init()
{

	ReloadInterface();
}

void XAddFolder::ReloadInterface()
{
	SetWindowText(_C(_T("323"),_T("���Ŀ¼")));
	m_TextName.SetText(_C(_T("72"),_T("����"))+_T(":"));
	m_BtnOk.SetCaption(_C(_T("1"),_T("ȷ��")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("ȡ��")));
}

void XAddFolder::OnBtnOk()
{
	CString szName;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szName);
	szName.Trim();
	if(szName==_T(""))
	{
		_M(_T("274"),_T("���Ʋ���Ϊ�գ�"),MB_OK);
		return;
	}

	m_szName=szName;

	__super::OnOK();
}

LRESULT XAddFolder::OnBTNLClick(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
		case ID_OK:
			{
				OnBtnOk();
			}
			break;
		case ID_CANCEL:
			{
				OnCancel();
			}
			break;
		default:
			break;
	}

	return 0;
}

void XAddFolder::OnUpdateEdit()
{
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_NAME);
	CString szContent;
	pEdit->GetWindowText(szContent);

	int nLen=XHandleVerification::GetWordLength(szContent);
	if(nLen>14)
	{
		pEdit->SetSel(0,-1);
		pEdit->ReplaceSel(szContent.Right(szContent.GetLength()-1));
	}
}