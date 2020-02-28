#include "stdafx.h"
#include "XSeatArrageData.h"
#include "XSeatArrageManage.h"
#include "XPage.h"
#include "XSeat.h"


XSeatArrageData* XSeatArrageData::m_pSeatData=NULL;

XSeatArrageData::XSeatArrageData()
{

}

XSeatArrageData::~XSeatArrageData()
{

}

XSeatArrageData* XSeatArrageData::GetInstance()
{
	if(NULL==m_pSeatData)
		m_pSeatData=new XSeatArrageData;

	return m_pSeatData;
}

void XSeatArrageData::Release()
{
	if(NULL!=m_pSeatData)
	{
		delete m_pSeatData;
		m_pSeatData=NULL;
	}
}

void XSeatArrageData::GetData(XSeatArrageManage* pManage,CArchive& arch)
{
	int nRow=0;
	arch>>nRow;

	int nColumn=0;
	arch>>nColumn;

	pManage->SetSeatRow(nRow);
	pManage->SetSeatColumn(nColumn);
	//////////////////////////////////////////////////////////////////////////
	MAP_PAGE& MapPage=pManage->GetMapPage();

	int nSize=0;
	arch>>nSize;

	for(int i=0;i<nSize;i++)
	{
		int nFirst=0;
		arch>>nFirst;

		MAP_PAGE::iterator iter=MapPage.find(nFirst);
		if(iter!=MapPage.end())
		{
			XPage* pPage=iter->second;

			int nWidth=0;
			arch>>nWidth;

			int nHeight=0;
			arch>>nHeight;

			CString szPhotoPath;
			arch>>szPhotoPath;

			BOOL bModel=FALSE;
			arch>>bModel;

			Uint8 r=0;
			arch>>r;

			Uint8 g=0;
			arch>>g;

			Uint8 b=0;
			arch>>b;

			pPage->SetPageWidth(nWidth);
			pPage->SetPageHeight(nHeight);
			pPage->SetModel(bModel);
			pPage->SetColor(r,g,b);
			pPage->SetPhotoName(szPhotoPath);

			if(nFirst==1)
				GetSeatData(pPage,arch);

			//////////////////////////////////////////////////////////////////////////
			VEC_SEAT& VecSeat=pPage->GetVecSeat();
			for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
			{
				XSeat* p=*iter;
				p->SetManage(pManage);
			}
		}
	}
}

void XSeatArrageData::GetSeatData(XPage* p,CArchive& arch)
{
	p->ClearVecSeat();
	VEC_SEAT& VecSeat=p->GetVecSeat();

	int nSize=0;
	arch>>nSize;

	for(int i=0;i<nSize;i++)
	{
		int nIndex=0;
		arch>>nIndex;

		RECTF rect;
		arch>>rect.X
			>>rect.Y
			>>rect.Width
			>>rect.Height;

		CString szPhotoName;
		arch>>szPhotoName;

		BOOL bModal;
		arch>>bModal;

		Uint8 ColorR;
		arch>>ColorR;

		Uint8 ColorG;
		arch>>ColorG;

		Uint8 ColorB;
		arch>>ColorB;

		Uint8 ColorA;
		arch>>ColorA;

		CString szGroupName;
		arch>>szGroupName;

		XSeat* pSeat=new XSeat;
		pSeat->SetIndex(nIndex);
		pSeat->SetSelected(FALSE);
		pSeat->SetRect(rect);

		pSeat->SetPhotoName(szPhotoName);
		pSeat->SetModel(bModal);
		pSeat->SetColor(ColorR,ColorG,ColorB,ColorA);
		pSeat->SetGroupName(szGroupName);

		VecSeat.push_back(pSeat);
	}
}

//////////////////////////////////////////////////////////////////////////
void XSeatArrageData::SaveData(XSeatArrageManage* pManage,CArchive& arch)
{
	arch<<pManage->GetSeatRow()
		<<pManage->GetSeatColumn();
	//////////////////////////////////////////////////////////////////////////
	MAP_PAGE& MapPage=pManage->GetMapPage();

	int nSize=MapPage.size();
	arch<<nSize;

	for(auto iter=MapPage.begin();iter!=MapPage.end();++iter)
	{
		int nFirst=iter->first;
		arch<<nFirst;

		XPage* pPage=iter->second;
		arch<<pPage->GetPageWidth()
			<<pPage->GetPageHeight()
			<<pPage->GetPhotoName()
			<<pPage->GetModel()
			<<pPage->GetColorR()
			<<pPage->GetColorG()
			<<pPage->GetColorB();

		if(nFirst==1)
			SaveSeatData(pPage,arch);
	}
}

void XSeatArrageData::SaveSeatData(XPage* p,CArchive& arch)
{
	VEC_SEAT& VecSeat=p->GetVecSeat();
	
	arch<<VecSeat.size();
	for(auto iter=VecSeat.begin();iter!=VecSeat.end();++iter)
	{
		XSeat* pSeat=*iter;

		arch<<pSeat->GetIndex()
			<<pSeat->GetRect().X
			<<pSeat->GetRect().Y
			<<pSeat->GetRect().Width
			<<pSeat->GetRect().Height
			<<pSeat->GetPhotoName()
			<<pSeat->GetModel()
			<<pSeat->GetColorR()
			<<pSeat->GetColorG()
			<<pSeat->GetColorB()
			<<pSeat->GetColorA()
			<<pSeat->GetGroupName();
	}
}
