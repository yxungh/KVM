#include "stdafx.h"
#include "XConstantData.h"
#include "XDelegateConstantData.h"

XConstantData* XConstantData::m_pData=NULL;

XConstantData::XConstantData():
	m_nNodeID(0),
	m_nNodeType(-1),
	m_szUserName(_T("")),
	m_nNodeChannel(0),
	m_nDragType(-1),
	m_szNodeName(_T("")),
	m_bMaster(FALSE),
	m_hItem(NULL),
	m_nGroupID(0),
	m_nType(0),
	m_pDelegate(NULL),
	m_szGroupName(_T("")),
	m_nSeatIndex(0),
	m_szNodeCaption(_T("")),
	m_nAvliNodeID(0)
{

}

XConstantData::~XConstantData()
{

}

XConstantData* XConstantData::GetInstance()
{
	if(NULL==m_pData)
	{
		m_pData=new XConstantData;
	}

	return m_pData;
}

void XConstantData::Release()
{
	if(NULL!=m_pData)
	{
		delete m_pData;
		m_pData=NULL;
	}
}

//void XConstantData::SetSeatArrageMaster(int nMaster)
//{
//	m_pDelegate->SetSeatArrageMaster(nMaster);
//}