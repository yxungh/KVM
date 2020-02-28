// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XImagePreview.h"
#include "XConstant.h"
#include "XTranslationManage.h"
#include "XDelegateImagePreview.h"
#include "HandlePath.h"
#include "XBtn.h"


// XImagePreview 对话框

IMPLEMENT_DYNAMIC(XImagePreview, CDialogEx)

	XImagePreview::XImagePreview(CWnd* pParent /*=NULL*/)
	: CDialogEx(XImagePreview::IDD, pParent),
	m_szPhotoPath(_T("")),
	m_pDelegate(NULL),
	m_nImageCount(0),
	m_pFront(NULL),
	m_pBack(NULL),
	m_nImageIndex(0)
{
}

XImagePreview::~XImagePreview()
{
	RELEASE(m_pFront);
	RELEASE(m_pBack);
}

void XImagePreview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(XImagePreview, CDialogEx)
	ON_COMMAND(ID_OK,OnBnClickedOk)
	ON_MESSAGE(MSG_BTN_LCLICK, OnBTNLClick)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// XImagePreview 消息处理程序

void XImagePreview::OnOk()
{
	CDialogEx::OnOK();
}

BOOL XImagePreview::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Init();

	return TRUE;
}

void XImagePreview::Init()
{
	InitData();

	CreateBtn();

	UpdateBtnStatus();

	ReloadInterface();
}

void XImagePreview::InitData()
{
	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA,0,(PVOID)&rt,0);
	MoveWindow(&rt);

	//////////////////////////////////////////////////////////////////////////
	MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();
	m_nImageCount=MapImage.size();
	m_nImageIndex=0;

	if(m_nImageCount!=0)
	{
		m_szPhotoPath=MapImage[m_nImageIndex];
	}
}

void XImagePreview::ReloadInterface()
{
	SetWindowText(XTranslationManage::GetInstance()->GetTranslationString(_T("88"),_T("图片预览")));
}

BOOL XImagePreview::OnEraseBkgnd(CDC* pDC)
{
	DrawDlg(pDC);
	return TRUE;
}

void XImagePreview::DrawDlg(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rt.Width(), rt.Height());

	CBitmap* pOldBitmap;
	pOldBitmap = tempDC.SelectObject(&bitmap);

	///////////////////////////////////////////////////////////////
	Gdiplus::Graphics graphics(tempDC);
	//graphics.Clear(Color(232, 239, 242));

	//绘制窗口背景
	if(m_szPhotoPath!=_T(""))
	{
		Gdiplus::Image background(m_szPhotoPath);
		graphics.DrawImage(&background,0,0,rt.Width(),rt.Height());
	}

	//if(NULL==m_pFront)
	//{
	//	CreateFrontBtn();
	//}

	///////////////////////////////////////////////////////////////
	pDC->BitBlt(0, 0, rt.Width(), rt.Height(), &tempDC, 0, 0, SRCCOPY);
	tempDC.SelectObject(pOldBitmap);
	tempDC.DeleteDC();
	bitmap.DeleteObject();
}

void XImagePreview::CreateBtn()
{
	CRect rt;
	GetClientRect(&rt);
	int nCentre=rt.left+rt.Width()/2;

	int nBtnWidth=50;
	int nBtnHeight=100;
	int nTop=rt.bottom-100;

	int nLeft=0;
	nLeft=nCentre-150;
	CRect rtFront(nLeft,nTop,nLeft+nBtnWidth,nTop+nBtnHeight);
	
	//////////////////////////////////////////////////////////////////////////
	XBtn* pFrontBtn=new XBtn;
	pFrontBtn->Create(WS_CHILD|WS_VISIBLE,rtFront,this,ID_BTN_FRONT);
	pFrontBtn->SetImage(HandlePath::GetPhotoPath(_T("front.png")));
	pFrontBtn->ShowWindow(SW_SHOW);
	pFrontBtn->UpdateWindow();
	m_pFront=pFrontBtn;

	//////////////////////////////////////////////////////////////////////////
	nLeft=nCentre+150;
	CRect rtBack(nLeft,nTop,nLeft+nBtnWidth,nTop+nBtnHeight);

	XBtn* pBtnBack=new XBtn;
	pBtnBack->Create(WS_CHILD|WS_VISIBLE,rtBack,this,ID_BTN_BACK);
	pBtnBack->SetImage(HandlePath::GetPhotoPath(_T("back.png")));
	pBtnBack->ShowWindow(SW_SHOW);
	pBtnBack->UpdateWindow();

	m_pBack=pBtnBack;
}

void XImagePreview::OnBnClickedOk()
{

}

void XImagePreview::OnBtnFront()
{
	MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();

	if(m_nImageIndex>=0&&m_nImageIndex<m_nImageCount)
	{
		m_nImageIndex-=1;
	}

	if(m_nImageIndex>=0)
	{
		m_szPhotoPath=MapImage[m_nImageIndex];
	}

	Invalidate(TRUE);

	UpdateBtnStatus();
}

void XImagePreview::OnBtnBack()
{
	MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();

	if(m_nImageIndex>=0&&m_nImageIndex<m_nImageCount)
	{
		m_nImageIndex+=1;
	}

	if(m_nImageIndex<m_nImageCount)
	{
		m_szPhotoPath=MapImage[m_nImageIndex];
	}
	Invalidate(TRUE);

	UpdateBtnStatus();
}

void XImagePreview::UpdateBtnStatus()
{
	MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();
	int nCount=MapImage.size();
	if(nCount==1)
	{
		m_pFront->EnableWindow(FALSE);
		m_pBack->EnableWindow(FALSE);
	}
	else if(nCount>=1&&m_nImageIndex==0)
	{
		m_pBack->EnableWindow(TRUE);
		m_pFront->EnableWindow(FALSE);
	}
	else if(nCount>=1&&m_nImageIndex==nCount-1)
	{
		m_pBack->EnableWindow(FALSE);
		m_pFront->EnableWindow(TRUE);
	}
	else
	{
		m_pBack->EnableWindow(TRUE);
		m_pFront->EnableWindow(TRUE);
	}
}

LRESULT XImagePreview::OnBTNLClick(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case ID_BTN_FRONT:
		{
			OnBtnFront();
		}
		break;
	case  ID_BTN_BACK:
		{
			OnBtnBack();
		}
		break;
	default:
		break;
		
	}

	return 0;
}