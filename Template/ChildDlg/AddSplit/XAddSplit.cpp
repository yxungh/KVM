#include "stdafx.h"
#include "XAddSplit.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"



IMPLEMENT_DYNAMIC(XAddSplit,XBaseDialog)

XAddSplit::XAddSplit(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAddSplit::IDD,pParent)
{

}

XAddSplit::~XAddSplit()
{
}

void XAddSplit::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_NAME,m_TextName);
	DDX_Control(pDX,IDC_STATIC_H,m_TextRow);
	DDX_Control(pDX,IDC_STATIC_V,m_TextColumn);
	DDX_Control(pDX,ID_OK,m_BtnOk);
	DDX_Control(pDX,ID_CANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XAddSplit,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
END_MESSAGE_MAP()


BOOL XAddSplit::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XAddSplit::Init()
{


	ReloadInterface();
}

void XAddSplit::ReloadInterface()
{
	SetWindowText(_C(_T("328"),_T("���ƴ����")));
	m_TextName.SetText(_C(_T("72"),_T("����"))+_T(":"));
	m_TextRow.SetText(_C(_T("93"),_T("��"))+_T(":"));
	m_TextColumn.SetText(_C(_T("94"),_T("��"))+_T(":"));

	m_BtnOk.SetCaption(_C(_T("1"),_T("ȷ��")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("ȡ��")));
}

void XAddSplit::OnBtnOk()
{
	CString szName=_T("");
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szName);
	szName.Trim();
	if(szName==_T(""))
	{
		_M(_T("73"),_T("���Ʋ���Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return;
	}
	m_szName=szName;
	//////////////////////////////////////////////////////////////////////////
	CString szRow=_T("");
	GetDlgItem(IDC_EDIT_H)->GetWindowText(szRow);
	szRow.Trim();
	if(szRow==_T(""))
	{
		_M(_T("526"),_T("���в���Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_H)->SetFocus();
		return;
	}
	m_nRow=_ttoi(szRow);
	//////////////////////////////////////////////////////////////////////////
	CString szColumn=_T("");
	GetDlgItem(IDC_EDIT_V)->GetWindowText(szColumn);
	szColumn.Trim();
	if(szColumn==_T(""))
	{
		_M(_T("526"),_T("���в���Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_V)->SetFocus();
		return;
	}
	m_nColumn=_ttoi(szColumn);

	XBaseDialog::OnOK();
}

LRESULT XAddSplit::OnBTNLClick(WPARAM wParam,LPARAM lParam)
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