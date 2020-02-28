#include "stdafx.h"
#include "XImage.h"
#include "afxdialogex.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XConstant.h"
#include "XDelegateImage.h"
#include "XProgressCtrl.h"

#define TIMERID_IMAGE              1
#define TIMERSPACE_IMAGE           1000

#define TIMERID_SENDIMAGEORDER     2
#define TIMERSPACE_SENDIMAGEORDER  1000

#define TIMERID_OPERATE            3
#define TIMERSPACE_OPERATE         3000

IMPLEMENT_DYNAMIC(XImage, XDialog)

	XImage::XImage(CWnd* pParent,CString szPhotoPath)
	: XDialog(XImage::IDD, pParent,szPhotoPath),
	m_pDelegate(NULL),
	m_pProgress(NULL),
	m_nPicIndex(0),
	m_nPos(0),
	m_nInputChannel(0)
{

}

XImage::~XImage()
{
	RELEASE(m_pProgress);
}

void XImage::DoDataExchange(CDataExchange* pDX)
{
	XDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XImage, XDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// XImage ��Ϣ�������
BOOL XImage::OnInitDialog()
{
	XDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XImage::DrawDlg(CDC* pDC)
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
	graphics.Clear(Color(232,239,242));

	//���ƴ��ڱ���
	if(m_szPhotoPath!=_T(""))
	{
		Gdiplus::Image background(m_szPhotoPath);
		graphics.DrawImage(&background,0,0,rt.Width(),rt.Height());
	}

	///////////////////////////////////////////////////////////////
	pDC->BitBlt(0, 0, rt.Width(), rt.Height(), &tempDC, 0, 0, SRCCOPY);
	tempDC.SelectObject(pOldBitmap);
	tempDC.DeleteDC();
	bitmap.DeleteObject();
}

void XImage::OnOk()
{
	__super::OnOK();
}

void XImage::Init()
{
	ResetDlgSize();
	CreateProgressBar();

	SetShowImage(0);
	HideCursor(TRUE);

	//�����л�ָ��
	SetMatrixInputToOutput();
}

void XImage::ResetDlgSize()
{
	int cx,cy; 
	cx=GetSystemMetrics(SM_CXSCREEN); 
	cy=GetSystemMetrics(SM_CYSCREEN); 

	MoveWindow(0,0,cx,cy);
}

void XImage::SetShowImage(int nIndex)
{
	MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();
	int nSize=MapImage.size();

	if(MapImage.size()!=0&&nIndex<nSize)
		m_szPhotoPath=MapImage[nIndex];

	Invalidate(TRUE);
}

void XImage::CreateProgressBar()
{
	CRect rect;
	GetClientRect(&rect);
	int nCentre=rect.left+rect.Width()/2;

	int nWidth=rect.Width()/2;
	int nHeight=15;

	int nTop=rect.bottom-100;
	int nLeft=nCentre-rect.Width()/4;

	CRect rectProgress(nLeft,nTop,nLeft+nWidth,nTop+nHeight);

	XProgressCtrl* pProgress=new XProgressCtrl;
	pProgress->Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTHREVERSE,rectProgress,this,0);
	pProgress->ShowWindow(SW_HIDE);
	pProgress->UpdateWindow();
	pProgress->SetRange(0,160);

	m_pProgress=pProgress;
}

void XImage::SendDataOfOSDImage(int nIndex)
{
	m_pDelegate->SendDataOfOSDImage(nIndex);
}

void XImage::SetMatrixInputToOutput()
{
	if(m_nInputChannel!=0)
	{
		m_pDelegate->SetMatrixInputToOutput(m_nInputChannel);
	}
}

void XImage::SendOSDPicOrder()
{
	//��������-��һ��
	//��ʱ����
	SetTimer(TIMERID_SENDIMAGEORDER,TIMERSPACE_SENDIMAGEORDER,NULL);
}

void XImage::SetOperate(int nPixIndex)
{
	m_nPicIndex=nPixIndex;

	//���½�����ʾ������
	SetTimer(TIMERID_OPERATE,TIMERSPACE_OPERATE,NULL);
}

void XImage::HideCursor(BOOL bHide)
{
	if(bHide)
	{
		while(ShowCursor(FALSE)>=0)
			ShowCursor(FALSE);
	}
	else
	{
		while (ShowCursor(TRUE)<0)
			ShowCursor(TRUE);
	}
}

void XImage::OnTimer(UINT_PTR nIDEvent)
{
	switch((int)nIDEvent)
	{
	case TIMERID_IMAGE:
		{
			int nPos=m_nPos;
			m_nPos=m_pProgress->SetPos((float)nPos);
			m_nPos+=1;

			if(m_pProgress->GetPos()==160)
			{			
				m_nPos=0;
				m_pProgress->SetPos(0);
				m_pProgress->ShowWindow(SW_HIDE);

				MAP_IMAGE& MapImage=m_pDelegate->GetMapImage();
				int nSize=MapImage.size();
				m_nPicIndex+=1;
				if(m_nPicIndex<nSize)
				{
					HideCursor(TRUE);
					SetShowImage(m_nPicIndex);
					SendDataOfOSDImage(m_nPicIndex);
				}
				else
				{
					CDialog::OnOK();
				}

				KillTimer(TIMERID_IMAGE);
			}
		}
		break;
	case TIMERID_SENDIMAGEORDER:
		{
			SendDataOfOSDImage(0);
			KillTimer(TIMERID_SENDIMAGEORDER);
		}
		break;
	case TIMERID_OPERATE:
		{			
			//��ʾ���
			HideCursor(FALSE);
			//��ʾ������
			m_pProgress->ShowWindow(SW_SHOW);
			//������ʱ��
			SetTimer(TIMERID_IMAGE,TIMERSPACE_IMAGE,NULL);
			KillTimer(TIMERID_OPERATE);
		}
		break;
	default:
		break;
	}
	__super::OnTimer(nIDEvent);
}

BOOL XImage::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_RETURN://���λس�  
				{
					if(!m_bEnableVK_RETURN)
					{
						return TRUE;
					}
				}
				break;
			case VK_ESCAPE://����Esc  
				{
					if(!m_bEnableVK_ESCAPE)
					{
						return TRUE;
					}
				}
				break;
			case VK_NEXT:
				{
					DWORD dwTime=GetTickCount();
					if(((long)dwTime-(long)m_dwTime)>5000)
					{
						m_dwTime=GetTickCount();
						m_pProgress->SetPos(159);
						return TRUE;
					}
				}
				break;
			default:
				break;
		}
	}
	return __super::PreTranslateMessage(pMsg);
}