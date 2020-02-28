

#include "stdafx.h"
#include "XAddUser.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XDelegateAddUser.h"

// XAddUser �Ի���

IMPLEMENT_DYNAMIC(XAddUser,XBaseDialog)

XAddUser::XAddUser(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XAddUser::IDD,pParent)
{
}

XAddUser::~XAddUser()
{
}

void XAddUser::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_USERNAME,m_TextName);
	DDX_Control(pDX,IDC_STATIC_PASSWD,m_TextPassWd);
	DDX_Control(pDX,IDC_STATIC_TIPS,m_TextTip);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XAddUser,XBaseDialog)
	ON_COMMAND(IDOK,OnBnClickedOk)
	ON_EN_UPDATE(IDC_EDIT_USERNAME,&XAddUser::OnUpdateEditUsername)
END_MESSAGE_MAP()


// XAddUser ��Ϣ�������

void XAddUser::OnOk()
{
	XBaseDialog::OnOK();
}

BOOL XAddUser::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();

	return TRUE;
}

void XAddUser::Init()
{
	//((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetLimitText(14);

	InitData();
	ReloadInterface();
}

void XAddUser::InitData()
{

}

void XAddUser::ReloadInterface()
{
	SetWindowText(_C(_T("44"),_T("����û�")));
	m_TextName.SetText(_C(_T("25"),_T("�û���"))+_T(":"));
	m_TextPassWd.SetText(_C(_T("26"),_T("����"))+_T(":"));
	//m_TextTip.SetLeft(TRUE);
	m_TextTip.SetText(_C(_T("297"),_T("��ʾ����Ȩ���б��з���Ȩ��")),TRUE);

	m_BtnOk.SetCaption(_C(_T("1"),_T("ȷ��")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("ȡ��")));
}

void XAddUser::OnBnClickedOk()
{
	CString szUserName=_T("");
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(szUserName);
	szUserName.Trim();
	if(_T("")==szUserName)
	{
		_M(_T("28"),_T("�û�������Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
		return;
	}

	CString szPassWd=_T("");
	GetDlgItem(IDC_EDIT_PASSWD)->GetWindowText(szPassWd);
	szPassWd.Trim();
	if(_T("")==szPassWd)
	{
		_M(_T("29"),_T("���벻��Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
		return;
	}

	if(!XHandleVerification::VerificationString(szUserName))
	{
		_M(_T("30"),_T("�û��������Ƿ��ַ���"),MB_OK);
		return;
	}

	if(!XHandleVerification::VerificationString(szPassWd))
	{
		_M(_T("31"),_T("��������Ƿ��ַ���"),MB_OK);
		return;
	}

	if(XHandleVerification::HasChinese(szPassWd))
	{
		_M(_T("319"),_T("����Ϊ��ĸ�����飡"),MB_OK);
		return;
	}

	int nRet=XHandleVerification::VerificationPasswd(szPassWd);
	if(nRet==1)
	{
		_M(_T("320"),_T("����Ϊ����������λ4λ��"),MB_OK);
		return;
	}
	else if(nRet==2)
	{
		_M(_T("319"),_T("����Ϊ��ĸ�����飡"),MB_OK);
		return;
	}

	m_pDelegate->SetUserInfo(szUserName,szPassWd);
	m_pDelegate->AddUser();
}

void XAddUser::OnUpdateEditUsername()
{
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_USERNAME);
	CString szContent;
	pEdit->GetWindowText(szContent);

	int nLen=XHandleVerification::GetWordLength(szContent);
	if(nLen>14)
	{
		pEdit->SetSel(0,-1);
		pEdit->ReplaceSel(szContent.Right(szContent.GetLength()-1));
	}
}

