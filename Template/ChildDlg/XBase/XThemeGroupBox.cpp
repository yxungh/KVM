#include "stdafx.h"
#include "XThemeGroupBox.h"


IMPLEMENT_DYNAMIC(XThemeGroupBox,CStatic)
XThemeGroupBox::XThemeGroupBox()
{
	m_crBorder=RGB(157,185,224);
	COLORREF cr3[]={RGB(255,255,255),RGB(202,220,246),RGB(150,180,222)};
	m_crText=0;
	m_nHeaderHeight=0;
	SetHeaderTheme(cr3,11);
}

XThemeGroupBox::~XThemeGroupBox()
{
}

BEGIN_MESSAGE_MAP(XThemeGroupBox,CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void XThemeGroupBox::SetHeaderTheme(COLORREF clrs[],UINT nEffect)
{
	//m_dsHeader.SetBkColor(clrs,nEffect);
}

void XThemeGroupBox::SetHeaderHeight(int nY)
{
	m_nHeaderHeight=nY;
	if(m_nHeaderHeight>0)
	{
		CRect rect;
		GetClientRect(&rect);
		//m_dsHeader.SetArea(CSize(rect.Width(),m_nHeaderHeight));
	}
}

void XThemeGroupBox::OnPaint()
{
	// �˴���Ĺؼ��������Լ�������֮������
	// ���粻�����Լ��Ļ�,��Ҫ������ܵ�����Ϣ,ת�������Լ����ǵ�sibling�ؼ�,
	// �����൱�鷳,�������׶���ػ�,������˸
	ShowWindow(SW_HIDE);
}
void XThemeGroupBox::Draw(CDC *pDC)
{
	BOOL bReleaseDC=FALSE;
	if(pDC==NULL)
	{
		pDC=GetParent()->GetDC();
		bReleaseDC=FALSE;
	}
	int nSaveDC=pDC->SaveDC();
	CRect rc;
	GetWindowRect(rc);
	GetParent()->ScreenToClient(&rc);
	// ��ͷ
	if(m_nHeaderHeight<=0)
		SetHeaderHeight(22);
	CRect rcTemp=rc;
	rcTemp.bottom=rc.top+m_nHeaderHeight;
	//m_dsHeader.Draw(pDC->GetSafeHdc(),NULL,&rcTemp);
	// ��ͷ����
	CString sText;
	GetWindowText(sText);
	CFont *pFont=GetParent()->GetFont();
	CFont *pOldFont=pDC->SelectObject(pFont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_crText);
	pDC->DrawText(sText,&rcTemp,DT_SINGLELINE|DT_END_ELLIPSIS|DT_CENTER|DT_VCENTER);
	pDC->SelectObject(pOldFont);
	// �߽�
	CBrush bru;
	bru.CreateSolidBrush(m_crBorder);
	pDC->FrameRect(&rc,&bru);
	bru.DeleteObject();
	// �ؽ�DC
	pDC->RestoreDC(nSaveDC);
	//�ͷ�
	if(bReleaseDC)
		GetParent()->ReleaseDC(pDC);
}