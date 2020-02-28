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
	//首先判断设置是否有效
	if(m_nMin>=m_nMax) 
		return;

	CPaintDC dc(this);
	//不为绘图消息调用 CProgressCtrl::OnPaint()

	//获取有效的进度条的位置和大小
	CRect LeftRect,RightRect,ClientRect;
	GetClientRect(ClientRect);
	LeftRect=RightRect=ClientRect;

	//计算显示进度的比例
	float Fraction=(float)(m_nPos-m_nMin)/((float)(m_nMax-m_nMin));
	//显示进度
	CString str;
	str.Format(_T("%.1f%%"),Fraction*100.0);

	//绘制整个进度条中的有效进度
	LeftRect.right=LeftRect.left+(int)((LeftRect.right-LeftRect.left)*Fraction);
	dc.FillSolidRect(LeftRect,m_prgsColor);
	//绘制剩余进度
	RightRect.left=LeftRect.right;
	dc.FillSolidRect(RightRect,m_freeColor);

	//设置文字背景颜色为透明
	dc.SetBkMode(TRANSPARENT);

	//为了能够在进度和剩余进度中显示不同颜色的字体，需要分别设置两边的字体颜色并绘图
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

	//如果在整个进度条中只显示一种字体颜色，那么可以直接调用
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

	//这里先计算要显示的进度条宽度，避免对同一进度多次绘制窗口
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
