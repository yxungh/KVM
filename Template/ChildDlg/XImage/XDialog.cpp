// XDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XDialog.h"
#include "afxdialogex.h"
#include "HandlePath.h"
#include "XConstant.h"

// XDialog �Ի���

IMPLEMENT_DYNAMIC(XDialog, CDialogEx)

XDialog::XDialog(UINT nIDD,CWnd *pParent,CString szPhotoPath)  
	: CDialogEx(nIDD,pParent),
	m_szPhotoPath(szPhotoPath),
	m_bEnableVK_RETURN(FALSE),
	m_bEnableVK_ESCAPE(FALSE),
	m_bNcHitTest(TRUE)
{
}

XDialog::~XDialog()
{
}

void XDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(XDialog, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// XDialog ��Ϣ�������
BOOL XDialog::OnEraseBkgnd(CDC* pDC)
{
	DrawDlg(pDC);
	return TRUE;
}

void XDialog::DrawDlg(CDC* pDC)
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
	graphics.Clear(Color(232, 239, 242));
	
	//���Ʊ���������
	//Gdiplus::Image titlebg(HandlePath::GetPhotoPath(_T("TitleBarbg.png")));
	//graphics.DrawImage(&titlebg, 0, 0, rt.Width(), TITLEBAR_HEIGHT);

	//���ƴ��ڱ���
	if(m_szPhotoPath!=_T(""))
	{
		Gdiplus::Image background(m_szPhotoPath);
		graphics.DrawImage(&background, 0, 0, rt.Width(), rt.Height());
	}

	////���Ʊ�������
	//CString strText=_T("");
	//GetWindowText(strText);
	//if (_T("")!=strText)
	//{
	//	FontFamily fontfamily(APP_FONT);
	//	Gdiplus::Font font(&fontfamily, (Gdiplus::REAL)FONT_SIZE, FontStyleBold, UnitPoint);

	//	SolidBrush whitebrush(Color(254,254,254));

	//	Gdiplus::StringFormat stringformat;
	//	stringformat.SetAlignment(StringAlignmentCenter);
	//	stringformat.SetLineAlignment(StringAlignmentCenter);

	//	Gdiplus::RectF reF(2.0f, 0.0f, (Gdiplus::REAL)rt.Width(),(Gdiplus::REAL)titlebg.GetHeight());

	//	graphics.DrawString(strText, -1, &font, reF, &stringformat, &whitebrush);
	//}

	////���Ʊ߿���ɫ
	//Pen pen(Color(0,99,177),1);
	//CRect rtTemp = rt;
	//rtTemp.DeflateRect(0,0,1,1);
	//graphics.DrawRectangle(&pen, Rect(rtTemp.left,rtTemp.top,rtTemp.Width(), rtTemp.Height()));

	///////////////////////////////////////////////////////////////
	pDC->BitBlt(0, 0, rt.Width(), rt.Height(), &tempDC, 0, 0, SRCCOPY);
	tempDC.SelectObject(pOldBitmap);
	tempDC.DeleteDC();
	bitmap.DeleteObject();
}

HBRUSH XDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr=CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

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

LRESULT XDialog::OnNcHitTest(CPoint point)
{
	//if(m_bNcHitTest)
	//{
		//CPoint pt(point);

		//ScreenToClient(&pt);

		//if(pt.y<30)
		//{
		//	return HTCAPTION;
		//}
	//}

	return CDialogEx::OnNcHitTest(point);
}

BOOL XDialog::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)  
	{  
		//switch(pMsg->wParam)  
		//{  
		//case VK_RETURN://���λس�  
		//	{
		//		if (!m_bEnableVK_RETURN)
		//		{
		//			return TRUE;  
		//		}
		//	}
		//	break;
		//case VK_ESCAPE://����Esc  
		//	{
		//		if (!m_bEnableVK_ESCAPE)
		//		{
		//			return TRUE;  
		//		}
		//	}
		//	break;
		//}  
	} 

	return __super::PreTranslateMessage(pMsg);
}

BOOL XDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return TRUE;
}
