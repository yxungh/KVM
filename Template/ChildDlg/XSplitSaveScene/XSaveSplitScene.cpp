#include "stdafx.h"
#include "XSaveSplitScene.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XSetListCtrl.h"
#include "XDelegateSaveSplitScene.h"
#include "XBaseViewManage.h"
#include "XHandleVerification.h"
#include "XMessageBox.h"
#include "XSendDataManage.h"



IMPLEMENT_DYNAMIC(XSaveSplitScene,XBaseDialog)

XSaveSplitScene::XSaveSplitScene(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XSaveSplitScene::IDD,pParent)
{

}

XSaveSplitScene::~XSaveSplitScene()
{
}

void XSaveSplitScene::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LIST_SPLIT,m_SplitList);
	DDX_Control(pDX,IDC_STATIC_NAME,m_TextName);
	DDX_Control(pDX,IDC_STATIC_SPLIT,m_TextList);
	DDX_Control(pDX,ID_OK,m_BtnOk);
	DDX_Control(pDX,ID_CANCEL,m_BtnCancel);
	//DDX_Control(pDX,IDC_STATIC_SCENE,m_TextScene);
	DDX_Control(pDX,IDC_STATIC_GROUP,m_TextGroup);
	
}


BEGIN_MESSAGE_MAP(XSaveSplitScene,XBaseDialog)
	ON_MESSAGE(MSG_BTN_LCLICK,OnBTNLClick)
	ON_EN_UPDATE(IDC_EDIT_NAME,OnUpdateEditName)
END_MESSAGE_MAP()


BOOL XSaveSplitScene::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XSaveSplitScene::Init()
{
	SetWindowText(_C(_T("350"),_T("��������")));

	m_BtnOk.SetCaption(_C(_T("1"),_T("ȷ��")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("ȡ��")));
	m_TextName.SetText(_C(_T("72"),_T("����"))+_T(":"));
	m_TextList.SetText(_C(_T("351"),_T("ƴ��ǽ�б�"))+_T(":"),TRUE);
	//m_TextScene.SetText(_C(_T("352"),_T("����")),TRUE);
	m_TextGroup.SetText(_C(_T("142"),_T("��")));

	InitList();
	InitData();
	InitCombo();
	ReloadInterface();
}

void XSaveSplitScene::InitList()
{
	XSetListCtrl::InitList(&m_SplitList,1,TRUE);
	m_SplitList.EnableToolTips(TRUE);
}

void XSaveSplitScene::InitData()
{
	auto& MapBaseView=m_pDelegate->GetBaseView();
	for(auto& view:MapBaseView)
	{
		XBaseViewManage* pManage=view.second;
		if(pManage->GetSplitName()!=_T(""))
		{
			AddListInfo(pManage->GetSplitName());
		}
	}
}

void XSaveSplitScene::InitCombo()
{
	((CComboBox*)GetDlgItem(IDC_COMBO_GROUP))->AddString(_C(_T("353"),_T("��")));

	auto& MapSceneGroup=m_pDelegate->GetMapSplitSceneGroup();
	for(auto& group:MapSceneGroup)
	{
		CString szGroup=group.first;
		((CComboBox*)GetDlgItem(IDC_COMBO_GROUP))->AddString(szGroup);
	}

	((CComboBox*)GetDlgItem(IDC_COMBO_GROUP))->SetCurSel(0);
}

int XSaveSplitScene::AddListInfo(CString szName)
{

	int nCount=0;
	nCount=m_SplitList.GetItemCount();
	m_SplitList.InsertItem(nCount,_T(""));
	SetListInfo(nCount,szName);
	return nCount;
}

void XSaveSplitScene::SetListInfo(int nCount,CString szName)
{
	m_SplitList.SetItemText(nCount,0,szName);
}

void XSaveSplitScene::ReloadInterface()
{
	CString szTemp=_T("");

	LVCOLUMN col;
	col.mask=LVCF_TEXT;

	szTemp=_C(_T("72"),_T("����"));
	col.pszText=szTemp.GetBuffer();
	m_SplitList.SetColumn(0,&col);
	szTemp.ReleaseBuffer();
}

void XSaveSplitScene::OnBtnOk()
{
	CString szUserName=_T("");
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(szUserName);
	szUserName.Trim();
	if(_T("")==szUserName)
	{
		_M(_T("247"),_T("���Ʋ���Ϊ�գ�"),MB_OK);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return;
	}

	if(!XHandleVerification::VerificationString(szUserName))
	{
		_M(_T("30"),_T("�û��������Ƿ��ַ���"),MB_OK);
		return;
	}
	m_szName=szUserName;
	XSendDataManage::GetInstance()->AddSendDataOfAddSplitScene(szUserName);
	//////////////////////////////////////////////////////////////////////////
	m_VecSplit.clear();
	int nCount=m_SplitList.GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		if(m_SplitList.GetCheck(i))
		{
			CString szText;
			szText=m_SplitList.GetItemText(i,0);
			m_VecSplit.push_back(szText);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	int nIndex=((CComboBox*)GetDlgItem(IDC_COMBO_GROUP))->GetCurSel();
	CString szGroup;
	((CComboBox*)GetDlgItem(IDC_COMBO_GROUP))->GetLBText(nIndex,szGroup);

	if(szGroup==_C(_T("353"),_T("��")))
		szGroup=_T("");

	m_szGroup=szGroup;
}

void XSaveSplitScene::OnUpdateEditName()
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

void XSaveSplitScene::OnCloseDlg()
{
	OnCancel();
}

LRESULT XSaveSplitScene::OnBTNLClick(WPARAM wParam,LPARAM lParam)
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