// XArragePageOne.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XArragePageOne.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XArragePageTwo.h"
#include "XDelegateArragePageOne.h"
#include "XNodeGroupInfo.h"


// XArragePageOne �Ի���

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


// XArragePageOne ��Ϣ�������
BOOL XArragePageOne::OnSetActive()
{
	CPropertySheet* pSheet=(CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_NEXT);
	pSheet->GetDlgItem(ID_WIZBACK)->ShowWindow(SW_HIDE);
	pSheet->GetDlgItem(ID_WIZNEXT)->SetWindowText(GetTranslationString(_T("154"),_T("��һ��"))+_T(">"));

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
	SetWindowText(GetTranslationString(_T("150"),_T("��ϯ��Ļ����")));

	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(GetTranslationString(_T("72"),_T("����"))+_T(":"));
	GetDlgItem(IDC_STATIC_ROW)->SetWindowText(GetTranslationString(_T("156"),_T("����"))+_T(":"));
	GetDlgItem(IDC_STATIC_COLUMN)->SetWindowText(GetTranslationString(_T("157"),_T("����"))+_T(":"));

	GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(GetTranslationString(_T("160"),_T("��ʾ:����Ϊ��ϯ���ƣ�����Ϊ����ϯ��Ļ����")));
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
		_M(_T("73"),_T("���Ʋ���Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return -1;
	}
	//�ж��Ƿ�����
	if(DecidedNameExist(szSeatName))
	{
		_M(_T("161"),_T("�����Ѵ��ڣ�"),MB_OK);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return -1;
	}

	//////////////////////////////////////////////////////////////////////////
	CString szRow=_T("");
	GetDlgItem(IDC_EDIT_ROW)->GetWindowText(szRow);
	szRow.Trim();
	if(szRow==_T(""))
	{
		_M(_T("151"),_T("��ϯ��Ļ�����в���Ϊ�գ�"),MB_OK);
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
		_M(_T("152"),_T("��ϯ��Ļ�����в���Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_COLUMN)->SetFocus();
		return -1;
	}

	int nColumn=_ttoi(szColumn);
	if(nColumn>9)
		nColumn=9;

	//��һ��Ҫִ�еڶ�ҳ��ʼ������
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

