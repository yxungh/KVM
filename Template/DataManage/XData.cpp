#include "stdafx.h"
#include "XData.h"

XData::XData():
	m_nDataLen(0),
	m_pData(NULL),
	m_nPacket(0),
	m_nPacketIndex(0)
{

}

XData::~XData()
{
	DeleteData();
}

void XData::DeleteData()
{
	if(NULL!=m_pData)
	{
		delete []m_pData;
		m_pData=NULL;
	}
}

void XData::SetData(unsigned char* pData)
{
	if(m_nDataLen!=0)
	{
		m_pData=new unsigned char[m_nDataLen];
		memcpy(m_pData,pData,m_nDataLen);
	}
}