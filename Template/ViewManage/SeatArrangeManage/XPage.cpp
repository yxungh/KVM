#include "stdafx.h"
#include "XPage.h"
#include "XSeat.h"
#include "XScreen.h"
#include "XMenuWnd.h"
#include "XSeatArrageManage.h"


XMenuWnd* XPage::m_pMenuWnd=NULL;
XPage::XPage()
{
}

XPage::~XPage()
{
	ClearVecSeat();
	ClearVecScreen();
}

void XPage::ClearVecSeat()
{
	for(auto& seat:m_VecSeat)
	{
		delete seat;
	}
	m_VecSeat.clear();
}

void XPage::ClearVecScreen()
{
	for(auto& screen:m_VecScreen)
	{
		delete screen;
	}
	m_VecScreen.clear();
}

void XPage::SetColor(Uint8 r,Uint8 g,Uint8 b)
{
	m_nColorR=r;
	m_nColorG=g;
	m_nColorB=b;
}

void XPage::CreateMenuWnd()
{
	m_pMenuWnd=m_pManage->CreateMenuWnd();
	//TRACE(_T("XPage\n"));
}

void XPage::InitScreen(int nRow,int nColumn,int nScreenH,int nScreenV)
{
	ClearVecScreen();

	float top=0.0f;
	float left=0.0f;
	int nIndex=1;

	for(int i=0;i<nRow;i++)
	{
		left=0.0f;
		for(int j=0;j<nColumn;j++)
		{
			RECTF screenRect(left,top,(Gdiplus::REAL)nScreenH,(Gdiplus::REAL)nScreenV);

			XScreen* pScreen=new XScreen;
			pScreen->SetRect(screenRect);
			pScreen->SetSeatIndex(nIndex);
			pScreen->SetRowIndex(i+1);
			pScreen->SetColumnIndex(j+1);

			m_VecScreen.push_back(pScreen);

			left+=nScreenH;
			nIndex++;
		}
		top+=nScreenV;
	}
}