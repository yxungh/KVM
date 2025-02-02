// XSaveScene.cpp: 实现文件
//

#include "stdafx.h"
#include "XSaveScene.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"


// XSaveScene 对话框

IMPLEMENT_DYNAMIC(XSaveScene, XBaseDialog)

XSaveScene::XSaveScene(CWnd* pParent /*=nullptr*/)
	: XBaseDialog(XSaveScene::IDD, pParent)
{

}

XSaveScene::~XSaveScene()
{
}

void XSaveScene::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_NAME,m_TextName);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XSaveScene, XBaseDialog)
	ON_BN_CLICKED(IDOK,&XSaveScene::OnBnClickedOk)
END_MESSAGE_MAP()


// XSaveScene 消息处理程序
BOOL XSaveScene::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XSaveScene::Init()
{
	ReloadInterface();
}

void XSaveScene::ReloadInterface()
{
	SetWindowText(_C(_T("240"),_T("保存预案")));
	m_TextName.SetText(_C(_T("72"),_T("名称"))+_T(":"));
	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
}

void XSaveScene::OnBnClickedOk()
{
	CString szName=_T("");
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szName);
	szName.Trim();
	if(_T("")==szName)
	{
		_M(_T("247"),_T("名不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return;
	}
	m_szName=szName;

	XBaseDialog::OnOK();
}
