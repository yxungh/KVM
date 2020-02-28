// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XBaseMap.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XHandleVerification.h"
#include "XDelegateBaseMap.h"
#include "XImagePreview.h"
#include "XImage.h"
#include "HandleIni.h"
#include "HandlePath.h"



// XBaseMap 对话框


IMPLEMENT_DYNAMIC(XBaseMap, XBaseDialog)

	XBaseMap::XBaseMap(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XBaseMap::IDD, pParent),
	m_pDelegate(NULL),
	m_szFilePath(_T("")),
	m_szPhotoName(_T("")),
	m_pImage(NULL)
{
}

XBaseMap::~XBaseMap()
{
}

void XBaseMap::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_COMBO_INPUTCHANNEL,m_ComboInput);
	DDX_Control(pDX,IDC_STATIC_INPUTCHANNEL,m_TextChannel);
	DDX_Control(pDX,IDC_STATIC_IMAGE1,m_TextMap1);
	DDX_Control(pDX,IDC_STATIC_IMAGE2,m_TextMap2);
	DDX_Control(pDX,IDC_STATIC_IMAGE3,m_TextMap3);
	DDX_Control(pDX,IDC_STATIC_IMAGE4,m_TextMap4);
	DDX_Control(pDX,IDC_STATIC_IMAGE5,m_TextMap5);
	DDX_Control(pDX,IDC_STATIC_IMAGE6,m_TextMap6);

	DDX_Control(pDX,IDC_BTN_IMAGE1,m_BtnImage1);
	DDX_Control(pDX,IDC_BTN_IMAGE2,m_BtnImage2);
	DDX_Control(pDX,IDC_BTN_IMAGE3,m_BtnImage3);
	DDX_Control(pDX,IDC_BTN_IMAGE4,m_BtnImage4);
	DDX_Control(pDX,IDC_BTN_IMAGE5,m_BtnImage5);
	DDX_Control(pDX,IDC_BTN_IMAGE6,m_BtnImage6);

	DDX_Control(pDX,ID_PREVIEWIMAGE,m_BtnPreview);
	DDX_Control(pDX,ID_WRITE,m_BtnSend);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XBaseMap, XBaseDialog)
	ON_COMMAND(ID_WRITE,OnBnClickedWrite)
	ON_COMMAND(ID_PREVIEWIMAGE,OnBnClickedPreview)
	ON_COMMAND(IDC_BTN_IMAGE1,OnBnClickedImage1)
	ON_COMMAND(IDC_BTN_IMAGE2,OnBnClickedImage2)
	ON_COMMAND(IDC_BTN_IMAGE3,OnBnClickedImage3)
	ON_COMMAND(IDC_BTN_IMAGE4,OnBnClickedImage4)
	ON_COMMAND(IDC_BTN_IMAGE5,OnBnClickedImage5)
	ON_COMMAND(IDC_BTN_IMAGE6,OnBnClickedImage6)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// XBaseMap 消息处理程序

void XBaseMap::OnOk()
{
	XBaseDialog::OnOK();
}

MAP_IMAGE& XBaseMap::GetMapImage()
{
	return m_pDelegate->GetMapImage();
}

void XBaseMap::SendDataOfOSDImage(int nIndex)
{
	m_pDelegate->SendDataOfOSDImage(nIndex);
}

BOOL XBaseMap::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XBaseMap::Init()
{
	InitData();
	ReloadInterface();
}

void XBaseMap::InitData()
{
	InitCombo();
	InitShowData();
}

void XBaseMap::InitShowData()
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szFilePath;
	szFilePath=HandleIni::GetString(_T("Info"), _T("0"),_T(""),szIniPath);
	GetDlgItem(IDC_EDIT_IMAGE1)->SetWindowText(szFilePath);

	szFilePath=HandleIni::GetString(_T("Info"), _T("1"),_T(""),szIniPath);
	GetDlgItem(IDC_EDIT_IMAGE2)->SetWindowText(szFilePath);

	szFilePath=HandleIni::GetString(_T("Info"), _T("2"),_T(""),szIniPath);
	GetDlgItem(IDC_EDIT_IMAGE3)->SetWindowText(szFilePath);

	szFilePath=HandleIni::GetString(_T("Info"), _T("3"),_T(""),szIniPath);
	GetDlgItem(IDC_EDIT_IMAGE4)->SetWindowText(szFilePath);

	szFilePath=HandleIni::GetString(_T("Info"), _T("4"),_T(""),szIniPath);
	GetDlgItem(IDC_EDIT_IMAGE5)->SetWindowText(szFilePath);

	szFilePath=HandleIni::GetString(_T("Info"),_T("5"),_T(""),szIniPath);
	GetDlgItem(IDC_EDIT_IMAGE6)->SetWindowText(szFilePath);
}

void XBaseMap::InitCombo()
{
	int nHardWareChannel=m_pDelegate->GetHardWareChannel();

	for(int i=1;i<=nHardWareChannel;i++)
	{
		CString szChannel;
		szChannel.Format(_T("%d"),i);

		m_ComboInput.AddString(szChannel);
	}

	m_ComboInput.SetCurSel(0);
}

void XBaseMap::ReloadInterface()
{
	SetWindowText(_C(_T("78"),_T("OSD底图")));

	m_TextChannel.SetText(_C(_T("80"),_T("输入通道"))+_T(":"));
	m_TextMap1.SetText(_C(_T("81"),_T("底图"))+_T("1")+_T(":"));
	m_TextMap2.SetText(_C(_T("81"),_T("底图"))+_T("2")+_T(":"));
	m_TextMap3.SetText(_C(_T("81"),_T("底图"))+_T("3")+_T(":"));
	m_TextMap4.SetText(_C(_T("81"),_T("底图"))+_T("4")+_T(":"));
	m_TextMap5.SetText(_C(_T("81"),_T("底图"))+_T("5")+_T(":"));
	m_TextMap6.SetText(_C(_T("81"),_T("底图"))+_T("6")+_T(":"));

	m_BtnImage1.SetCaption(_T("..."));
	m_BtnImage2.SetCaption(_T("..."));
	m_BtnImage3.SetCaption(_T("..."));
	m_BtnImage4.SetCaption(_T("..."));
	m_BtnImage5.SetCaption(_T("..."));
	m_BtnImage6.SetCaption(_T("..."));

	m_BtnPreview.SetCaption(_C(_T("86"),_T("预览")));
	m_BtnSend.SetCaption(_C(_T("87"),_T("发送")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));

}

//void XBaseMap::OnComboSelChange()
//{
//	CString szInputChannel;
//	m_ComboInput.GetLBText(m_ComboInput.GetCurSel(),szInputChannel);
//	int nInputChannel=_ttoi(szInputChannel);
//
//	TRACE(_T("nInputChannel=%d\n"),nInputChannel);
//
//}

void XBaseMap::OnBnClickedImage1()
{
	int nIndex=0;
	SelectBaseMap(nIndex);
	GetDlgItem(IDC_EDIT_IMAGE1)->SetWindowText(m_szFilePath);

	SaveFilePath(nIndex,m_szFilePath);
}

void XBaseMap::OnBnClickedImage2()
{
	int nIndex=1;
	SelectBaseMap(nIndex);
	GetDlgItem(IDC_EDIT_IMAGE2)->SetWindowText(m_szFilePath);

	SaveFilePath(nIndex,m_szFilePath);
}

void XBaseMap::OnBnClickedImage3()
{
	int nIndex=2;
	SelectBaseMap(nIndex);
	GetDlgItem(IDC_EDIT_IMAGE3)->SetWindowText(m_szFilePath);

	SaveFilePath(nIndex,m_szFilePath);
}

void XBaseMap::OnBnClickedImage4()
{
	int nIndex=3;
	SelectBaseMap(nIndex);
	GetDlgItem(IDC_EDIT_IMAGE4)->SetWindowText(m_szFilePath);

	SaveFilePath(nIndex,m_szFilePath);
}

void XBaseMap::OnBnClickedImage5()
{
	int nIndex=4;
	SelectBaseMap(nIndex);
	GetDlgItem(IDC_EDIT_IMAGE5)->SetWindowText(m_szFilePath);

	SaveFilePath(nIndex,m_szFilePath);
}

void XBaseMap::OnBnClickedImage6()
{
	int nIndex=5;
	SelectBaseMap(nIndex);
	GetDlgItem(IDC_EDIT_IMAGE6)->SetWindowText(m_szFilePath);

	SaveFilePath(nIndex,m_szFilePath);
}

void XBaseMap::SaveFilePath(int nIndex,CString szFilePath)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szKey;
	szKey.Format(_T("%d"),nIndex);

	HandleIni::WriteData(_T("Info"),szKey,szFilePath,szIniPath);
}

void XBaseMap::SetOperate(int nPixIndex)
{
	m_pImage->SetOperate(nPixIndex);
}

void XBaseMap::SendOSDPicOrder()
{
	m_pImage->SendOSDPicOrder();
}

void XBaseMap::OnBnClickedWrite()
{
	SetImageMap();
	MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();
	if(MapImage.size()==0)
	{
		_M(_T("89"),_T("请先选择图片！"),MB_OK);
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	//先把输入全部切到输出
	CString szInputChannel;
	m_ComboInput.GetLBText(m_ComboInput.GetCurSel(),szInputChannel);
	int nInputChannel=_ttoi(szInputChannel);
	//////////////////////////////////////////////////////////////////////////
	//写入
	XImage dlg;
	m_pImage=&dlg;

	dlg.SetDelegate(this);
	dlg.SetInputChannel(nInputChannel);
	dlg.DoModal();

	m_pImage=NULL;
}

void XBaseMap::SetMatrixInputToOutput(int nInputChannal)
{
	m_pDelegate->SetMatrixInputToOutput(nInputChannal);
}

void XBaseMap::OnBnClickedPreview()
{
	SetImageMap();
	MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();
	if(MapImage.size()==0)
	{
		_M(_T("89"),_T("请先选择图片！"),MB_OK);
		return;
	}

	//预览
	XImagePreview dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();
}

void XBaseMap::OnTimer(UINT_PTR nIDEvent)
{

	__super::OnTimer(nIDEvent);
}

void XBaseMap::SetImageMap()
{
	int nIndex=0;
	CString szFilePath;
	GetDlgItem(IDC_EDIT_IMAGE1)->GetWindowText(szFilePath);
	if(szFilePath!=_T(""))
	{
		SetImageMap(nIndex,szFilePath);
	}
	//////////////////////////////////////////////////////////////////////////
	nIndex=1;
	GetDlgItem(IDC_EDIT_IMAGE2)->GetWindowText(szFilePath);
	if(szFilePath!=_T(""))
	{
		SetImageMap(nIndex,szFilePath);
	}
	//////////////////////////////////////////////////////////////////////////
	nIndex=2;
	GetDlgItem(IDC_EDIT_IMAGE3)->GetWindowText(szFilePath);
	if(szFilePath!=_T(""))
	{
		SetImageMap(nIndex,szFilePath);
	}
	//////////////////////////////////////////////////////////////////////////
	nIndex=3;
	GetDlgItem(IDC_EDIT_IMAGE4)->GetWindowText(szFilePath);
	if(szFilePath!=_T(""))
	{
		SetImageMap(nIndex,szFilePath);
	}
	//////////////////////////////////////////////////////////////////////////
	nIndex=4;
	GetDlgItem(IDC_EDIT_IMAGE5)->GetWindowText(szFilePath);
	if(szFilePath!=_T(""))
	{
		SetImageMap(nIndex,szFilePath);
	}
	//////////////////////////////////////////////////////////////////////////
	nIndex=5;
	GetDlgItem(IDC_EDIT_IMAGE6)->GetWindowText(szFilePath);
	if(szFilePath!=_T(""))
	{
		SetImageMap(nIndex,szFilePath);
	}
}

void XBaseMap::SetImageMap(int nIndex,CString szFilePath)
{
	MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();
	MAP_IMAGE::iterator iter=MapImage.find(nIndex);
	if(iter!=MapImage.end())
	{
		iter->second=szFilePath;
	}
	else
	{
		MapImage.insert(std::pair<int,CString>(nIndex,szFilePath));
	}
}

void XBaseMap::SelectBaseMap(int nIndex)
{
	CString szFileName;
	CString szFilePath;
	if (OpenSelectPhotoFileDialog(szFileName, szFilePath))
	{
		m_szFilePath=szFilePath;
		m_szPhotoName=szFileName;
		
		MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();
		MAP_IMAGE::iterator iter=MapImage.find(nIndex);
		if(iter!=MapImage.end())
		{
			iter->second=m_szFilePath;
		}
		else
		{
			MapImage.insert(std::pair<int,CString>(nIndex,m_szFilePath));
		}
	}
}

BOOL XBaseMap::OpenSelectPhotoFileDialog(CString& szFileName, CString& szFilePath)
{
	CFileDialog fileDlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,FILTER_PHOTO);

	CString szTitle=_C(_T("79"),_T("选择图片"));
	fileDlg.m_ofn.lpstrTitle=szTitle;

	if(fileDlg.DoModal()==IDOK)
	{
		szFilePath=fileDlg.GetPathName();
		szFileName=fileDlg.GetFileName();
		return TRUE;
	}
	return FALSE;
}
