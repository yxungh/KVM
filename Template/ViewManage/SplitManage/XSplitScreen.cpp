#include "stdafx.h"
#include "XSplitScreen.h"
#include "XSplitSignal.h"


XSplitScreen::XSplitScreen()
{

}


XSplitScreen::~XSplitScreen()
{
	//ClearVecSplitSignal();
}

//void XSplitScreen::ClearVecSplitSignal()
//{
//	for(auto& vec:m_VecSplitSignal)
//	{
//		delete vec;
//	}
//	m_VecSplitSignal.clear();
//}

//void XSplitScreen::CloseSplitSignal(int nSignalID)
//{
//	for(auto iter=m_VecSplitSignal.begin();iter!=m_VecSplitSignal.end();)
//	{
//		XSplitSignal* pSignal=*iter;
//		if(pSignal->GetSignalID()==nSignalID)
//		{
//			iter=m_VecSplitSignal.erase(iter);
//			delete pSignal;
//		}
//		else
//		{
//			++iter;
//		}
//	}
//}

//void XSplitScreen::SetSplitSignalUp(int nSignalID)
//{
//	//上移，与上面交换位置
//	int nCount=m_VecSplitSignal.size();
//	if(nCount>1)
//	{
//		for(int i=0;i<nCount;i++)
//		{
//			unsigned int nID=m_VecSplitSignal[i]->GetSignalID();
//			if(nID==nSignalID)
//			{
//				if(i!=(nCount-1))
//				{
//					XSplitSignal* pTemp=NULL;
//					pTemp=m_VecSplitSignal[i];
//					m_VecSplitSignal[i]=m_VecSplitSignal[i+1];
//					m_VecSplitSignal[i+1]=pTemp;
//					break;
//				}
//			}
//		}
//	}
//}
//
//void XSplitScreen::SetSplitSignalDown(int nSignalID)
//{
//	int nCount=m_VecSplitSignal.size();
//	if(nCount>1)
//	{
//		for(int i=0;i<nCount;i++)
//		{
//			unsigned int nID=m_VecSplitSignal[i]->GetSignalID();
//			if(nID==nSignalID)
//			{
//				if(i!=0)
//				{
//					XSplitSignal* pTemp=NULL;
//					pTemp=m_VecSplitSignal[i-1];
//					m_VecSplitSignal[i-1]=m_VecSplitSignal[i];
//					m_VecSplitSignal[i]=pTemp;
//					break;
//				}
//			}
//		}
//	}
//}
//
//void XSplitScreen::SetSplitSignalTop(int nSignalID)
//{
//	if(m_VecSplitSignal.size()==1)
//		return;
//	for(auto iter=m_VecSplitSignal.begin();iter!=m_VecSplitSignal.end();++iter)
//	{
//		XSplitSignal* pSignal=*iter;
//		if(pSignal->GetSignalID()==nSignalID)
//		{
//			m_VecSplitSignal.erase(iter);
//			m_VecSplitSignal.push_back(pSignal);
//			break;
//		}
//	}
//}
//
//void XSplitScreen::SetSplitSignalBottom(int nSignalID)
//{
//	if(m_VecSplitSignal.size()==1)
//		return;
//	for(auto iter=m_VecSplitSignal.begin();iter!=m_VecSplitSignal.end();++iter)
//	{
//		XSplitSignal* pSignal=*iter;
//		if(pSignal->GetSignalID()==nSignalID)
//		{
//			m_VecSplitSignal.erase(iter);
//			m_VecSplitSignal.insert(m_VecSplitSignal.begin(),pSignal);
//			break;
//		}
//	}
//}
//
//XSplitSignal* XSplitScreen::GetSplitSignalByID(int nID)
//{
//	for(auto& pSignal:m_VecSplitSignal)
//	{
//		if(pSignal->GetSignalID()==nID)
//		{
//			return pSignal;
//		}
//	}
//	return NULL;
//}

