#include "stdafx.h"
#include "XCopyUser.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XDelegateCopyUser.h"

// XCopyUser �Ի���

IMPLEMENT_DYNAMIC(XCopyUser,XBaseDialog)

XCopyUser::XCopyUser(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XCopyUser::IDD,pParent)
{
}

XCopyUser::~XCopyUser()
{
}

void XCopyUser::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_USERNAME,m_TextName);
	DDX_Control(pDX,IDC_STATIC_PASSWD,m_TextPasswd);
	DDX_Control(pDX,IDC_STATIC_TIPS,m_TextTip);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XCopyUser,XBaseDialog)
	ON_COMMAND(IDOK,OnBnClickedOk)
	ON_EN_UPDATE(IDC_EDIT_USERNAME,&XCopyUser::OnUpdateEditUsername)
END_MESSAGE_MAP()


// XCopyUser ��Ϣ�������


void XCopyUser::CloseDlg()
{
	OnCancel();
}

BOOL XCopyUser::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XCopyUser::Init()
{
	InitData();
	ReloadInterface();
}

void XCopyUser::InitData()
{

}

void XCopyUser::ReloadInterface()
{
	SetWindowText(_C(_T("58"),_T("�����û�")));
	m_TextName.SetText(_C(_T("25"),_T("�û���"))+_T(":"));
	m_TextPasswd.SetText(_C(_T("26"),_T("����"))+_T(":"));

	m_BtnOk.SetCaption(_C(_T("1"),_T("ȷ��")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("ȡ��")));

	m_TextTip.SetText(_C(_T("50"),_T("��ʾ:������ѡ�û�Ȩ�ޣ����û������벻ͬ")));
}

void XCopyUser::OnBnClickedOk()
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


	//if(XHandleVerification::HasChinese(szPassWd))
	//{
	//	_M(_T("319"),_T("����Ϊ��ĸ�����飡"),MB_OK);
	//	return;
	//}

	//int nRet=XHandleVerification::VerificationPasswd(szPassWd);
	//if(nRet==1)
	//{
	//	_M(_T("320"),_T("����Ϊ����������λ4λ��"),MB_OK);
	//	return;
	//}
	//else if(nRet==2)
	//{
	//	_M(_T("319"),_T("����Ϊ��ĸ�����飡"),MB_OK);
	//	return;
	//}


	m_szUserName=szUserName;
	m_szPassWd=szPassWd;

	m_pDelegate->CopyUser();
	//XBaseDialog::OnOK();
}

void XCopyUser::OnUpdateEditUsername()
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



