// XSeatImage.cpp : 实现文件
//

#include "stdafx.h"
#include "XSeatImage.h"
#include "afxdialogex.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "FileHandle.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XMessageBox.h"
#include "XSeat.h"



// XSeatImage 对话框

IMPLEMENT_DYNAMIC(XSeatImage, XBaseDialog)

	XSeatImage::XSeatImage(CWnd* pParent /*=NULL*/)
	: XBaseDialog(XSeatImage::IDD, pParent),
	m_szPhotoName(_T("")),
	m_szFilePath(_T("")),
	m_nComboIndex(0),
	m_pDelegate(NULL),
	m_pSeat(NULL)
{

}

XSeatImage::~XSeatImage()
{
}

void XSeatImage::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_COMBO_MODEL,m_Combox);
	DDX_Control(pDX,IDC_COLOR,m_Color);

	DDX_Control(pDX,IDC_STATIC_MODEL,m_TextModel);
	DDX_Control(pDX,IDC_STATIC_BGCOLOR,m_TextColor);
	DDX_Control(pDX,IDC_STATIC_BGPIC,m_TextImage);
	DDX_Control(pDX,IDC_STATIC_TIP,m_TextTip);

	DDX_Control(pDX,IDOK,m_BtnOk);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
	DDX_Control(pDX,IDC_BTN_SEL,m_BtnSel);
}

BEGIN_MESSAGE_MAP(XSeatImage, XBaseDialog)
	ON_COMMAND(IDOK,OnBtnOk)
	ON_COMMAND(IDC_BTN_SEL,OnBtnSel)
END_MESSAGE_MAP()


// XSeatImage 消息处理程序
BOOL XSeatImage::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XSeatImage::Init()
{
	InitCombo();
	InitData();

	ReLoadInterface();
}

void XSeatImage::InitData()
{
	if(NULL==m_pSeat)
		return;

	BOOL bModel=m_pSeat->GetModel();
	if(bModel)
		m_Combox.SetCurSel(0);
	else
		m_Combox.SetCurSel(1);

	COLORREF color(RGB(m_pSeat->GetColorR(),m_pSeat->GetColorG(),m_pSeat->GetColorB()));
	m_Color.SetColor(color);

	CString szPhotoName=m_pSeat->GetPhotoName();
	m_szPhotoName=szPhotoName;
	GetDlgItem(IDC_EDIT_BGPIC)->SetWindowText(szPhotoName);
}

void XSeatImage::InitCombo()
{
	m_Combox.AddString(_C(_T("122"),_T("纯色")));
	m_Combox.AddString(_C(_T("123"),_T("背景")));

	m_Combox.SetCurSel(0);
}

void XSeatImage::ReLoadInterface()
{
	SetWindowText(_C(_T("124"),_T("设置背景")));

	m_TextModel.SetText(_C(_T("313"),_T("背景模式"))+_T(":"));
	m_TextColor.SetText(_C(_T("314"),_T("背景颜色"))+_T(":"));
	m_TextImage.SetText(_C(_T("315"),_T("背景图片"))+_T(":"));
	m_TextTip.SetText(_C(_T("317"),_T("提示:请选择与窗体大小合适的底图，分辨率太大会导致失真或卡顿")),TRUE,TRUE);
	m_BtnOk.SetCaption(_C(_T("1"),_T("确定")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
	m_BtnSel.SetCaption(_T("..."));
}

void XSeatImage::OnBtnOk()
{
	CMFCColorButton* pBtnColor=(CMFCColorButton*)GetDlgItem(IDC_COLOR);
	m_BgColor=pBtnColor->GetColor();
	m_nComboIndex=m_Combox.GetCurSel();
	/////////////////////////////////////////////////////////////////////////

	XBaseDialog::OnOK();
}

void XSeatImage::OnBtnSel()
{
	CString szFileName;
	CString szFilePath;
	if(OpenSelectPhotoFileDialog(szFileName,szFilePath))
	{
		m_szFilePath=szFilePath;
		m_szPhotoName=szFileName;

		//获取图片分辨率
		Image image(szFilePath);
		int nWidth=image.GetWidth();
		int nHeight=image.GetHeight();
		if(nWidth>300||nHeight>300)
		{
			_M(_T("318"),_T("请选择较小分辨率底图！"),MB_OK);
			return;
		}

		GetDlgItem(IDC_EDIT_BGPIC)->SetWindowText(m_szPhotoName);

		//复制图片到程序路径
		if(!FileHandle::copyFile(m_szFilePath,HandlePath::GetMapPhotoPath(m_szPhotoName)))
		{
			_M(_T("121"),_T("拷贝背景图片失败！"),MB_OK);
		}

		//保存图片名称
		CString szIniPath=HandlePath::GetIniPath(APP_ININAME);
		HandleIni::WriteData(_T("Info"),_T("PhotoName"),szFileName,szIniPath);
	}
}

BOOL XSeatImage::OpenSelectPhotoFileDialog(CString& szFileName,CString& szFilePath)
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
