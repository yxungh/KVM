#include "stdafx.h"
#include "XProgressCtrl.h"

IMPLEMENT_DYNAMIC(XProgressCtrl,CProgressCtrl)

	XProgressCtrl::XProgressCtrl()
{
	m_prgsColor=RGB(4,176,38);
	m_freeColor=RGB(202,237,241);
	m_prgsTextColor=RGB(255,0,0);
	m_freeTextColor=RGB(0,0,255);
}

XProgressCtrl::~XProgressCtrl()
{

}

BEGIN_MESSAGE_MAP(XProgressCtrl,CProgressCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void XProgressCtrl::OnPaint()
{
	//�����ж������Ƿ���Ч
	if(m_nMin>=m_nMax) 
		return;

	CPaintDC dc(this);
	//��Ϊ��ͼ��Ϣ���� CProgressCtrl::OnPaint()

	//��ȡ��Ч�Ľ�������λ�úʹ�С
	CRect LeftRect,RightRect,ClientRect;
	GetClientRect(ClientRect);
	LeftRect=RightRect=ClientRect;

	//������ʾ���ȵı���
	float Fraction=(float)(m_nPos-m_nMin)/((float)(m_nMax-m_nMin));
	//��ʾ����
	CString str;
	str.Format(_T("%.1f%%"),Fraction*100.0);

	//���������������е���Ч����
	LeftRect.right=LeftRect.left+(int)((LeftRect.right-LeftRect.left)*Fraction);
	dc.FillSolidRect(LeftRect,m_prgsColor);
	//����ʣ�����
	RightRect.left=LeftRect.right;
	dc.FillSolidRect(RightRect,m_freeColor);

	//�������ֱ�����ɫΪ͸��
	dc.SetBkMode(TRANSPARENT);

	//Ϊ���ܹ��ڽ��Ⱥ�ʣ���������ʾ��ͬ��ɫ�����壬��Ҫ�ֱ��������ߵ�������ɫ����ͼ
	CRgn rgn;
	rgn.CreateRectRgn(LeftRect.left,LeftRect.top,LeftRect.right,LeftRect.bottom);
	dc.SelectClipRgn(&rgn);
	dc.SetTextColor(m_prgsTextColor);
	dc.DrawText(str,ClientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	rgn.DeleteObject();
	rgn.CreateRectRgn(RightRect.left,RightRect.top,RightRect.right,RightRect.bottom);
	dc.SelectClipRgn(&rgn);
	dc.SetTextColor(m_freeTextColor);
	dc.DrawText(str,ClientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	//�����������������ֻ��ʾһ��������ɫ����ô����ֱ�ӵ���
	//dc.SetTextColor(m_freeTextColor);
	//dc.DrawText(str,ClientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

int XProgressCtrl::SetPos(float nPos)
{
	if(!::IsWindow(m_hWnd))
		return -1;

	int nOldPos=m_nPos;
	m_nPos=nPos;

	CRect rect;
	GetClientRect(rect);

	//�����ȼ���Ҫ��ʾ�Ľ�������ȣ������ͬһ���ȶ�λ��ƴ���
	float Fraction=(float)(m_nPos-m_nMin)/((float)(m_nMax-m_nMin));
	float nBarWidth=(float)(Fraction*rect.Width());

	if(abs(nBarWidth-m_nBarWidth)<1e-6)
	{

	}
	else
	{
		m_nBarWidth=nBarWidth;
		RedrawWindow();
	}

	return nOldPos;
}

int XProgressCtrl::GetPos()
{
	return m_nPos;
}

void XProgressCtrl::SetRange(int nLower,int nUpper)
{
	m_nMax=nUpper;
	m_nMin=nLower;
	m_nPos=m_nMin;
	m_nBarWidth=0;
}

void XProgressCtrl::SetPrgsColor(COLORREF cloor)
{
	m_prgsColor=cloor;
}

void XProgressCtrl::SetFreeColor(COLORREF cloor)
{
	m_freeColor=cloor;
}

void XProgressCtrl::SetPrgsTextColor(COLORREF cloor)
{
	m_prgsTextColor=cloor;
}

void XProgressCtrl::SetFreeTextColor(COLORREF cloor)
{
	m_freeTextColor=cloor;
}
