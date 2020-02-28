#include "StdAfx.h"
#include "XMultiVideoWindowFrames.h"
#include "XMultiVideoWindowFrame.h"
#include "XMultiVideoWindow.h"

XMultiVideoWindowFrames::XMultiVideoWindowFrames(void):
	m_nIndex(0),
	m_MultiVideoWindow(NULL),
	m_nPageHeight(0),
	m_nPageWidth(0),
	m_bModel(FALSE),
	m_szPhotoPath(_T("")),
	m_Point(CPoint(0,0)),
	m_nRow(0),
	m_nColumn(0)
{
	m_ColorBG.r=0;
	m_ColorBG.g=0;
	m_ColorBG.b=0;
	m_ColorBG.a=255;
}

XMultiVideoWindowFrames::~XMultiVideoWindowFrames(void)
{
	ClearVecFrame();
}

void XMultiVideoWindowFrames::SetMultiVideoWindow(XMultiVideoWindow* p)
{
	m_MultiVideoWindow=p;
}

XVideoPlayer* XMultiVideoWindowFrames::GetVideoPlayer()
{
	return m_MultiVideoWindow->GetVideoPlayer();
}

SDL_Renderer* XMultiVideoWindowFrames::GetRenderer()
{
	return m_MultiVideoWindow->GetRenderer();
}

void XMultiVideoWindowFrames::ClearVecFrame()
{
	for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecFrame.begin(); iter!=m_VecFrame.end(); iter++)
	{
		delete *iter;
	}

	m_VecFrame.clear();
}

VEC_MULTIVIDEOWINDOWFRAME& XMultiVideoWindowFrames::GetVecFrame()
{
	return m_VecFrame;
}

XMultiVideoWindowFrame* XMultiVideoWindowFrames::AddFrame(CString szRTSPAddr,RECTF rFrame,RECTF rImage,
														  BOOL bShow)
{
	XMultiVideoWindowFrame* pFrame=new XMultiVideoWindowFrame;

	pFrame->SetMultiVideoWindowFrames(this);

	pFrame->SetRTSPAddr(szRTSPAddr);

	pFrame->SetRect(rFrame);

	pFrame->SetRectImage(rImage);

	pFrame->Show(bShow);

	m_VecFrame.push_back(pFrame);

	return pFrame;
}

void XMultiVideoWindowFrames::SetFrame(XMultiVideoWindowFrame* pFrame,RECTF rFrame,RECTF rImage)
{
	if(pFrame!=NULL)
	{
		pFrame->SetRect(rFrame);

		pFrame->SetRectImage(rImage);
	}
}

void XMultiVideoWindowFrames::SetFrame(XMultiVideoWindowFrame* pFrame,RECTF rFrame)
{
	if(pFrame!=NULL)
	{
		pFrame->SetRect(rFrame);
	}
}

void XMultiVideoWindowFrames::SetFrame(XMultiVideoWindowFrame* pFrame,CString szRTSPAddr)
{
	if(pFrame!=NULL)
	{
		pFrame->SetRTSPAddr(szRTSPAddr);
	}
}

void XMultiVideoWindowFrames::SetFrame(XMultiVideoWindowFrame* pFrame,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	if(pFrame!=NULL)
	{
		pFrame->SetBackColor(r,g,b,a);
	}
}

void XMultiVideoWindowFrames::SetFramePic(XMultiVideoWindowFrame* pFrame,CString szPhotoPath)
{
	if(pFrame!=NULL)
	{
		pFrame->SetPhotoPath(szPhotoPath);
	}
}

void XMultiVideoWindowFrames::SetFrameModel(XMultiVideoWindowFrame* pFrame,BOOL bModel)
{
	if(pFrame!=NULL)
	{
		pFrame->SetModel(bModel);
	}
}

void XMultiVideoWindowFrames::SetFrameText(XMultiVideoWindowFrame* pFrame,CString text)
{
	if(pFrame!=NULL)
	{
		pFrame->SetText(text);
	}
}

void XMultiVideoWindowFrames::SetFrameText(XMultiVideoWindowFrame* pFrame,COLORREF nTextColor,int nTextSize)
{
	if(pFrame!=NULL)
	{
		pFrame->SetText(nTextColor,nTextSize);
	}
}

//////////////////////////////////////////////////////////////////////////
void XMultiVideoWindowFrames::SetFrameSelected(XMultiVideoWindowFrame* pFrame,BOOL bSelected)
{
	if(pFrame!=NULL)
	{
		pFrame->SetSelected(bSelected);
	}
}

void XMultiVideoWindowFrames::SetVecFrameSelect(XMultiVideoWindowFrame* pFrame)
{
	for(auto iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XMultiVideoWindowFrame* pTemp=*iter;

		if(pTemp==pFrame)
			pTemp->SetSelected(TRUE);
		else
			pTemp->SetSelected(FALSE);
	}
}

void XMultiVideoWindowFrames::SetVecFrameUnselect()
{
	for(auto iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
	{
		XMultiVideoWindowFrame* pTemp=*iter;

		pTemp->SetSelected(FALSE);
	}
}
//////////////////////////////////////////////////////////////////////////

//void XMultiVideoWindowFrames::SetFrameSelectInTwoPage(XMultiVideoWindowFrame* pFrame,BOOL b)
//{
//	if(NULL!=pFrame)
//		pFrame->SetSelectedInTwo(b);
//}
//
//void XMultiVideoWindowFrames::SetVecFrameSelectInTwoPage(XMultiVideoWindowFrame* pFrame)
//{
//	for(auto iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
//	{
//		XMultiVideoWindowFrame* pTemp=*iter;
//
//		if(pTemp==pFrame)
//			pTemp->SetSelectedInTwo(TRUE);
//		else
//			pTemp->SetSelectedInTwo(FALSE);
//	}
//}
//
//void XMultiVideoWindowFrames::SetFrameUnSelectInTwoPage()
//{
//	for(auto iter=m_VecFrame.begin();iter!=m_VecFrame.end();++iter)
//	{
//		XMultiVideoWindowFrame* pTemp=*iter;
//		pTemp->SetSelectedInTwo(FALSE);
//	}
//}

void XMultiVideoWindowFrames::SetFrameImage(XMultiVideoWindowFrame* pFrame,RECTF rImage)
{
	if(pFrame!=NULL)
	{
		pFrame->SetRectImage(rImage);
	}
}

void XMultiVideoWindowFrames::DeleteFrame(XMultiVideoWindowFrame* pFrame)
{
	for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecFrame.begin(); iter!=m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp=*iter;

		if(pTemp==pFrame)
		{
			delete pFrame;

			m_VecFrame.erase(iter);

			break;
		}
	}
}

void XMultiVideoWindowFrames::ShowFrame(XMultiVideoWindowFrame* pFrame,BOOL bShow)
{
	if(pFrame!=NULL)
	{
		pFrame->Show(bShow);
	}
}

void XMultiVideoWindowFrames::SetFrameTop(XMultiVideoWindowFrame* pFrame)
{
	for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecFrame.begin(); iter!=m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp=*iter;

		if(pTemp==pFrame)
		{
			m_VecFrame.erase(iter);

			m_VecFrame.push_back(pFrame);

			break;
		}
	}
}

void XMultiVideoWindowFrames::SetFrameBottom(XMultiVideoWindowFrame* pFrame)
{
	for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecFrame.begin(); iter!=m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp=*iter;

		if(pTemp==pFrame)
		{
			m_VecFrame.erase(iter);

			m_VecFrame.insert(m_VecFrame.begin(),pFrame);

			break;
		}
	}
}

void XMultiVideoWindowFrames::ChangeFramePos(XMultiVideoWindowFrame* pFrameFront,XMultiVideoWindowFrame* pFrame)
{
	if(pFrameFront==NULL)
	{
		return;
	}

	VEC_MULTIVIDEOWINDOWFRAME::iterator iterFront;

	VEC_MULTIVIDEOWINDOWFRAME::iterator iterPos;

	int nPosFront=-1;

	int nPos=-1;

	int nIndex=0;

	for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=m_VecFrame.begin(); iter!=m_VecFrame.end(); iter++)
	{
		XMultiVideoWindowFrame* pTemp=*iter;

		if(pTemp==pFrameFront)
		{
			nPosFront=nIndex;

			iterFront=iter;

			if(nPos!=-1)
			{
				break;
			}
		}
		else if(pTemp==pFrame)
		{
			nPos=nIndex;

			iterPos=iter;

			if(nPosFront!=-1)
			{
				break;
			}
		}

		nIndex++;
	}

	if(nPosFront==-1||nPos==-1)
	{
		return;
	}

	if(nPosFront>nPos)
	{
		m_VecFrame.insert(++iterFront,pFrame);

		m_VecFrame.erase(m_VecFrame.begin()+nPos);

		//afxDump<<"ChangeFramePos ip:"<<m_ScreenIP<<"\n";
	}
}

void XMultiVideoWindowFrames::SetBgColor(Uint8 r,Uint8 g,Uint8 b)
{
	m_ColorBG.r=r;
	m_ColorBG.g=g;
	m_ColorBG.b=b;
}
