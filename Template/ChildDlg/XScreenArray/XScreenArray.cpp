// XScreenArray.cpp : 实现文件
//

#include "stdafx.h"
#include "XScreenArray.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"


// XScreenArray 对话框

IMPLEMENT_DYNAMIC(XScreenArray, XBaseDialog)

XScreenArray::XScreenArray(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XScreenArray::IDD, pParent),
	m_nScreenRow(0),
	m_nScreenColumn(0)
{

}

XScreenArray::~XScreenArray()
{
}

void XScreenArray::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_ROW,m_TextRow);
	DDX_Control(pDX,IDC_STATIC_COLUMN,m_TextColumn);
	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XScreenArray, XBaseDialog)
	ON_COMMAND(IDOK,OnClickOk)
END_MESSAGE_MAP()


// XScreenArray 消息处理程序
BOOL XScreenArray::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XScreenArray::Init()
{
	InitData();
	ReloadInterface();
}

void XScreenArray::InitData()
{
	CString szRow;
	szRow.Format(_T("%d"),m_nScreenRow);
	GetDlgItem(IDC_EDIT_ROW)->SetWindowText(szRow);

	CString szColumn;
	szColumn.Format(_T("%d"),m_nScreenColumn);
	GetDlgItem(IDC_EDIT_COLUMN)->SetWindowText(szColumn);
}

void XScreenArray::ReloadInterface()
{
	SetWindowText(GetTranslationString(_T("178"),_T("坐席屏幕排列")));

	m_TextRow.SetText(_C(_T("156"),_T("行数"))+_T(":"));
	m_TextColumn.SetText(_C(_T("157"),_T("列数"))+_T(":"));

	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
}

CString XScreenArray::GetTranslationString(CString szKey,CString szDefault/*=_T("")*/)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

void XScreenArray::OnClickOk()
{
	CString szRow;
	GetDlgItem(IDC_EDIT_ROW)->GetWindowText(szRow);
	szRow.Trim();
	if(_T("")==szRow)
	{
		_M(_T("179"),_T("行不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_ROW)->SetFocus();
		return;
	}
	m_nScreenRow=_ttoi(szRow);
	//////////////////////////////////////////////////////////////////////////
	CString szColumn;
	GetDlgItem(IDC_EDIT_COLUMN)->GetWindowText(szColumn);
	szColumn.Trim();
	if(_T("")==szColumn)
	{
		_M(_T("180"),_T("列不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_COLUMN)->SetFocus();
		return;
	}
	m_nScreenColumn=_ttoi(szColumn);

	XBaseDialog::OnOK();
}