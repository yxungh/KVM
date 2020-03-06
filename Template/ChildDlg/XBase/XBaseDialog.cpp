// XBaseDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "XBaseDialog.h"
#include "afXDialogex.h"
#include "HandlePath.h"
#include "XConstant.h"
#include "XBtn.h"
#include "XThemeColor.h"
#include "XThemeColor.h"

// XBaseDialog 对话框

IMPLEMENT_DYNAMIC(XBaseDialog,CDialogEx)

XBaseDialog::XBaseDialog(UINT nIDD,CWnd *pParent)
	: CDialogEx(nIDD,pParent)
{
}

XBaseDialog::~XBaseDialog()
{
	DestroyWindow();
}

void XBaseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(XBaseDialog,CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// XBaseDialog 消息处理程序

BOOL XBaseDialog::OnEraseBkgnd(CDC* pDC)
{
	DrawDlg(pDC);
	return TRUE;
}

void XBaseDialog::DrawDlg(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);

	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC,rt.Width(),rt.Height());

	CBitmap* pOldBitmap;
	pOldBitmap=tempDC.SelectObject(&bitmap);
	///////////////////////////////////////////////////////////////
	Gdiplus::Graphics graphics(tempDC);
	graphics.Clear(m_BgColor[XThemeColor::GetInstance()->GetThemeIndex()]);
	///////////////////////////////////////////////////////////////
	pDC->BitBlt(0,0,rt.Width(),rt.Height(),&tempDC,0,0,SRCCOPY);
	tempDC.SelectObject(pOldBitmap);
	tempDC.DeleteDC();
	bitmap.DeleteObject();
}

HBRUSH XBaseDialog::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hbr=CDialogEx::OnCtlColor(pDC,pWnd,nCtlColor);

	switch(nCtlColor)
	{
		case CTLCOLOR_STATIC:
			{
				pDC->SetBkMode(TRANSPARENT);
				return (HBRUSH)::GetStockObject(NULL_BRUSH);
			}
			break;
		case CTLCOLOR_EDIT:
			{
				if(pWnd->IsWindowEnabled())
				{
					pDC->SetBkMode(TRANSPARENT);
					HBRUSH b=CreateSolidBrush(RGB(255,255,255));
					return b;
				}
			}
			break;
		default:
			break;
	}

	return hbr;
}

BOOL XBaseDialog::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_RETURN://屏蔽回车  
				{
					if(!m_bEnableVK_RETURN)
					{
						return TRUE;
					}
				}
				break;
			case VK_ESCAPE://屏蔽Esc  
				{
					if(!m_bEnableVK_ESCAPE)
					{
						return TRUE;
					}
				}
				break;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

BOOL XBaseDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return TRUE;
}

void XBaseDialog::CreateBtn(CWnd* pParent,XBtn* pBtn,CRect rect,
							UINT nID,CString szPhotoPath)
{
	pBtn->Create(WS_CHILD|WS_VISIBLE,rect,pParent,nID);
	pBtn->ShowWindow(SW_SHOW);
	pBtn->UpdateWindow();
	pBtn->SetImage(szPhotoPath);
}