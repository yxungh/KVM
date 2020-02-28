// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XSeatArrageName.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XSeatSceneInfo.h"



// XSeatArrageName 对话框

IMPLEMENT_DYNAMIC(XSeatArrageName, CDialogEx)

	XSeatArrageName::XSeatArrageName(CWnd* pParent /*=NULL*/)
	: CDialogEx(XSeatArrageName::IDD, pParent),
	m_szName(_T("")),
	m_szGroup(_T("")),
	m_szTempGroup(_T(""))
{
}

XSeatArrageName::~XSeatArrageName()
{
}

void XSeatArrageName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XSeatArrageName, CDialogEx)
	ON_COMMAND(IDOK,OnBnClickedOk)
END_MESSAGE_MAP()


// XSeatArrageName 消息处理程序

void XSeatArrageName::OnOk()
{
	CDialogEx::OnOK();
}

BOOL XSeatArrageName::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Init();

	return TRUE;
}

void XSeatArrageName::Init()
{
	InitData();
	ReloadInterface();
}

void XSeatArrageName::InitData()
{
	InitCombo();
}

void XSeatArrageName::InitCombo()
{
	//MAP_SEATSCENE& MapSeatScene=XSeatArrageWnd::GetInstance()->GetMapSeatScene();
	//for(auto iter=MapSeatScene.begin();iter!=MapSeatScene.end();++iter)
	//{
	//	XSeatSceneInfo* pInfo=iter->second;
	//	CString szGroupName=pInfo->GetGroupName();

	//	if(szGroupName!=_T(""))
	//	{
	//		if(m_szTempGroup!=szGroupName)
	//		{
	//			m_Combo.AddString(szGroupName);
	//			m_szTempGroup=szGroupName;
	//		}
	//	}
	//}
}

void XSeatArrageName::ReloadInterface()
{
	SetWindowText(_C(_T("101"),_T("坐席")));
	//GetDlgItem(IDC_STATIC_SEAT)->SetWindowText(_C(_T("72"), _T("名称")) + _T(":"));
	GetDlgItem(IDC_STATIC_GROUP)->SetWindowText(_C(_T("105"), _T("组")) + _T(":"));
	//GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(_C(_T("106"), _T("提示：分组可编辑")));
}

void XSeatArrageName::OnBnClickedOk()
{
	CString szName=_T("");
	GetDlgItem(IDC_EDIT_SEAT)->GetWindowText(szName);
	szName.Trim();
	if (_T("")==szName)
	{
		_M(_T("73"),_T("名称不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_SEAT)->SetFocus();
		return;
	}

	if (!XHandleVerification::VerificationString(szName))
	{
		_M(_T("74"),_T("名称包含非法字符！"),MB_OK);
		return;
	}

	m_szName=szName;

	CDialogEx::OnOK();
}



