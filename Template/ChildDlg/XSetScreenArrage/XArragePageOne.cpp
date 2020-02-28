// XArragePageOne.cpp : 实现文件
//

#include "stdafx.h"
#include "XArragePageOne.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XArragePageTwo.h"
#include "XDelegateArragePageOne.h"
#include "XNodeGroupInfo.h"


// XArragePageOne 对话框

IMPLEMENT_DYNAMIC(XArragePageOne, CPropertyPage)

XArragePageOne::XArragePageOne()
	: CPropertyPage(XArragePageOne::IDD),
	m_pDelegate(NULL)
{

}

XArragePageOne::~XArragePageOne()
{
}

void XArragePageOne::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XArragePageOne, CPropertyPage)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// XArragePageOne 消息处理程序
BOOL XArragePageOne::OnSetActive()
{
	CPropertySheet* pSheet=(CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_NEXT);
	pSheet->GetDlgItem(ID_WIZBACK)->ShowWindow(SW_HIDE);
	pSheet->GetDlgItem(ID_WIZNEXT)->SetWindowText(GetTranslationString(_T("154"),_T("下一步"))+_T(">"));

	return CPropertyPage::OnSetActive();
}

void XArragePageOne::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CPropertyPage::OnShowWindow(bShow,nStatus);

	//if(bShow)
	//{
	//	GetParent()->ShowWindow(SW_HIDE);
	//	GetParent()->SetWindowPos(NULL,0,0,400,400,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
	//	GetParent()->ShowWindow(SW_SHOW);
	//}
}

BOOL XArragePageOne::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	Init();
	return TRUE;
}

void XArragePageOne::Init()
{
	InitData();
	ReloadInterface();
}
void XArragePageOne::InitData()
{

}

void XArragePageOne::ReloadInterface()
{
	SetWindowText(GetTranslationString(_T("150"),_T("坐席屏幕排列")));

	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(GetTranslationString(_T("72"),_T("名称"))+_T(":"));
	GetDlgItem(IDC_STATIC_ROW)->SetWindowText(GetTranslationString(_T("156"),_T("行数"))+_T(":"));
	GetDlgItem(IDC_STATIC_COLUMN)->SetWindowText(GetTranslationString(_T("157"),_T("列数"))+_T(":"));

	GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(GetTranslationString(_T("160"),_T("提示:名称为坐席名称，行列为该坐席屏幕排列")));
}

CString XArragePageOne::GetTranslationString(CString szKey,CString szDefault/*=_T("")*/)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

LRESULT XArragePageOne::OnWizardNext()
{
	CString szSeatName;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szSeatName);
	szSeatName.Trim();
	if(szSeatName==_T(""))
	{
		_M(_T("73"),_T("名称不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return -1;
	}
	//判断是否重名
	if(DecidedNameExist(szSeatName))
	{
		_M(_T("161"),_T("名称已存在！"),MB_OK);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return -1;
	}

	//////////////////////////////////////////////////////////////////////////
	CString szRow=_T("");
	GetDlgItem(IDC_EDIT_ROW)->GetWindowText(szRow);
	szRow.Trim();
	if(szRow==_T(""))
	{
		_M(_T("151"),_T("坐席屏幕排列行不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_ROW)->SetFocus();
		return -1;
	}

	int nRow=_ttoi(szRow);
	if(nRow>5)
		nRow=5;

	//////////////////////////////////////////////////////////////////////////
	CString szColumn=_T("");
	GetDlgItem(IDC_EDIT_COLUMN)->GetWindowText(szColumn);
	szColumn.Trim();
	if(szColumn==_T(""))
	{
		_M(_T("152"),_T("坐席屏幕排列列不能为空！"),MB_OK);
		GetDlgItem(IDC_EDIT_COLUMN)->SetFocus();
		return -1;
	}

	int nColumn=_ttoi(szColumn);
	if(nColumn>9)
		nColumn=9;

	//下一步要执行第二页初始化操作
	CPropertySheet* pSheet=(CPropertySheet*)GetParent();
	XArragePageTwo* pPage=(XArragePageTwo*)pSheet->GetPage(1);

	pPage->SetGroupName(szSeatName);
	pPage->SetScreenRow(nRow);
	pPage->SetScreenColumn(nColumn);
	pPage->InitData();

	return CPropertyPage::OnWizardNext();
}

BOOL XArragePageOne::DecidedNameExist(CString szName)
{
	MAP_NODEGROUP& MapNodeGroup=m_pDelegate->GetMapNodeGroup();
	for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
	{
		XNodeGroupInfo* pInfo=iter->second;
		if(pInfo->GetGroupName()==szName)
			return TRUE;
	}
	return FALSE;
}

