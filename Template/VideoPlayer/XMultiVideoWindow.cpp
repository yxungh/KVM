#include "StdAfx.h"
#include "XMultiVideoWindow.h"
#include "XMultiVideoWindowFrame.h"
#include "XMultiVideoWindowFrames.h"
#include "XRTSP.h"
#include "XVideoPlayer.h"
#include "XHandleCode.h"
#include "XCaculateMultiVideoWindow.h"


BOOL XMultiVideoWindow::m_bDrawFirstPage=TRUE;
XMultiVideoWindow::XMultiVideoWindow(void)
{
	m_CreateWindow=FALSE;
	m_CreateRender=FALSE;
	m_bResetVideoShow=FALSE;
	m_window=NULL;
	m_renderer=NULL;
	m_HWND=NULL;
	m_Row=0;
	m_Column=0;
	m_textureBGImage=NULL;
	m_szBGImagePath=_T("");
	m_textureFrameBGImage=NULL;
	m_szFrameBGImagePath=_T("");


	m_VideoPlayer=NULL;
	m_pManage=NULL;
	m_MushHardCode=FALSE;

	m_ColorBG.r=40;
	m_ColorBG.g=41;
	m_ColorBG.b=45;
	m_ColorBG.a=0;

	m_ColorLine.r=50;
	m_ColorLine.g=50;
	m_ColorLine.b=50;
	m_ColorLine.a=255;

	m_fScale=1.0f;

	m_nOrgX=0;
	m_nOrgY=0;

	m_textureText=NULL;
	m_szText=_T("");

	m_ColorText.r=0;
	m_ColorText.g=0;
	m_ColorText.b=237;
	m_ColorText.a=255;

	m_nTextSize=16;
	m_CreateTextureText=FALSE;
	m_nTextureTextWidth=0;
	m_nTextureTextHeight=0;

	InitializeCriticalSection(&m_CS);
	InitializeCriticalSection(&m_CSBGImage);
}


XMultiVideoWindow::~XMultiVideoWindow(void)
{
	ClearData();
	ClearMapFrames();
	ClearTextureText();
	DeleteCriticalSection(&m_CS);
	DeleteCriticalSection(&m_CSBGImage);
}

BOOL XMultiVideoWindow::CreateSDLWindow()
{
	WNDPROC wndproc=(WNDPROC)GetWindowLongPtr(m_HWND,GWLP_WNDPROC);	// 获取窗口处理函数

	SDL_Window* window=SDL_CreateWindowFrom(m_HWND);

	if(!window)
	{
		return FALSE;
	}

	///*
	WNDPROC sdlproc=(WNDPROC)GetWindowLongPtr(m_HWND,GWLP_WNDPROC);
	if(sdlproc!=wndproc)
	{
		SetWindowLongPtr(m_HWND,GWLP_WNDPROC,(LONG_PTR)wndproc);
	}
	//*/

	::UnregisterTouchWindow(m_HWND);

	m_window=window;

	m_CreateWindow=TRUE;

	return TRUE;
}

BOOL XMultiVideoWindow::CreateSDLRenderer()
{
	if(!m_CreateWindow)
	{
		return FALSE;
	}

	SDL_Renderer* renderer=NULL;

	if(m_MushHardCode||(m_VideoPlayer!=NULL&&m_VideoPlayer->GetHardDecode()))
	{
		renderer=SDL_CreateRenderer(m_window,0,SDL_RENDERER_ACCELERATED);
	}
	else
	{
		renderer=SDL_CreateRenderer(m_window,-1,SDL_RENDERER_SOFTWARE);
	}

	if(!renderer)
	{
		return FALSE;
	}

	m_renderer=renderer;
	m_CreateRender=TRUE;

	return TRUE;
}

void XMultiVideoWindow::ClearData()
{
	m_CreateWindow=FALSE;

	ClearTextureBGImage();
	ClearFrameTextureBGImage();

	ClearRenderer();

	if(NULL!=m_window)
	{
		SDL_DestroyWindow(m_window);

		m_window=NULL;
	}

	if(NULL!=m_HWND)
	{
		ShowWindow(m_HWND,SW_SHOW);
	}
}

void XMultiVideoWindow::ClearRenderer()
{
	m_CreateRender=FALSE;
	if(m_renderer!=NULL)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer=NULL;
	}
}

BOOL XMultiVideoWindow::GetCreateSDLWindow()
{
	return m_CreateWindow;
}

BOOL XMultiVideoWindow::GetCreateSDLRenderer()
{
	return m_CreateRender;
}

HWND XMultiVideoWindow::GetHWND()
{
	return m_HWND;
}

void XMultiVideoWindow::SetMushHardCode(BOOL b)
{
	m_MushHardCode=b;
}

void XMultiVideoWindow::SetHWND(HWND h)
{
	m_HWND=h;
}

void XMultiVideoWindow::SetFrame(int nRow,int nColumn)
{
	m_Row=nRow;
	m_Column=nColumn;
}

void XMultiVideoWindow::SetVideoPlayer(XVideoPlayer* p)
{
	m_VideoPlayer=p;
}

XVideoPlayer* XMultiVideoWindow::GetVideoPlayer()
{
	return m_VideoPlayer;
}

SDL_Renderer* XMultiVideoWindow::GetRenderer()
{
	return m_renderer;
}

void XMultiVideoWindow::SetMultiVideoWindowScale(float fScale)
{
	EnterCriticalSection(&m_CS);
	m_fScale=fScale;
	LeaveCriticalSection(&m_CS);
}

float XMultiVideoWindow::GetMultiVideoWindowScale()
{
	return m_fScale;
}

void XMultiVideoWindow::Draw()
{
	EnterCriticalSection(&m_CS);
	if(m_CreateRender)
	{
		DrawBGColor();
		DrawPage();
		DrawText();

		SDL_RenderPresent(m_renderer);
	}
	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DrawBGColor()
{
	SDL_SetRenderDrawColor(m_renderer,m_ColorBG.r,m_ColorBG.g,m_ColorBG.b,m_ColorBG.a);
	SDL_RenderClear(m_renderer);
}

void XMultiVideoWindow::DrawBGImage()
{
	EnterCriticalSection(&m_CSBGImage);

	//DWORD dwBegin = GetTickCount();

	if(m_textureBGImage!=NULL)
	{
		SDL_RenderCopy(m_renderer,m_textureBGImage,NULL,NULL);
	}

	//DWORD dwEnd = GetTickCount();
	//TRACE("DrawBGImage:%d\n", dwEnd - dwBegin);

	LeaveCriticalSection(&m_CSBGImage);
}

void XMultiVideoWindow::DrawBGImage(SDL_Rect rect)
{
	EnterCriticalSection(&m_CSBGImage);

	if(m_textureBGImage!=NULL)
	{
		SDL_RenderCopy(m_renderer,m_textureBGImage,NULL,&rect);
	}

	LeaveCriticalSection(&m_CSBGImage);
}

void XMultiVideoWindow::DrawFrameBgImage(SDL_Rect rect)
{
	EnterCriticalSection(&m_CSBGImage);

	if(m_textureFrameBGImage!=NULL)
	{
		SDL_RenderCopy(m_renderer,m_textureFrameBGImage,NULL,&rect);
	}

	LeaveCriticalSection(&m_CSBGImage);
}

void XMultiVideoWindow::SetMultiVideoWindowDrawPage(BOOL b)
{
	m_bDrawFirstPage=b;
}

void XMultiVideoWindow::DrawText()
{
	if(GetCreateTextureText())
		CreateTextureText();

	SDL_Texture* pTextureText=GetTextureText();

	if(NULL!=pTextureText)
	{
		int nTextWidth=GetTextureTextWidth();
		int nTextHeight=GetTextureTextHeight();

		SDL_Rect rectText;
		rectText.x=m_nOrgX;
		rectText.y=m_nOrgY-nTextHeight;
		rectText.w=nTextWidth;
		rectText.h=nTextHeight;

		SDL_RenderCopy(m_renderer,pTextureText,NULL,&rectText);
	}
}

void XMultiVideoWindow::DrawPage()
{
	CRect rect;
	GetClientRect(m_HWND,&rect);

	CSize size=XCaculateMultiVideoWindow::ViewGetSize(this);
	int nPosH=GetScrollPos(m_HWND,SB_HORZ);
	int nPosV=GetScrollPos(m_HWND,SB_VERT);

	CSize cOrgSize;
	XCaculateMultiVideoWindow::SetPageOrg(rect,nPosH,nPosV,size,m_fScale,cOrgSize);

	//原点偏移
	m_nOrgX=cOrgSize.cx;
	m_nOrgY=cOrgSize.cy;

	XMultiVideoWindowFrames* pFrames=NULL;
	if(m_bDrawFirstPage)
		pFrames=m_MapFrames[1];
	else
		pFrames=m_MapFrames[2];

	if(NULL==pFrames)
		return;

	BOOL bModel=pFrames->GetModel();
	SDL_Color color=pFrames->GetBgColor();

	int nPageWidth=pFrames->GetPageWidth();
	int nPageHeight=pFrames->GetPageHeight();
	CString szPhotoPath=pFrames->GetPhotoPath();

	SDL_Rect sdl_rect;
	sdl_rect.x=m_nOrgX;
	sdl_rect.y=m_nOrgY;
	sdl_rect.w=(int)(nPageWidth*m_fScale);
	sdl_rect.h=(int)(nPageHeight*m_fScale);

	if(bModel)
	{
		SDL_SetRenderDrawColor(m_renderer,color.r,color.g,color.b,255);
		SDL_RenderFillRect(m_renderer,&sdl_rect);
	}
	else
	{
		SetBGImage(szPhotoPath);
		DrawBGImage(sdl_rect);
	}

	//绘制Frame
	DrawFrames(pFrames);

	//第二页绘制网格
	if(!m_bDrawFirstPage)
	{
		SDL_SetRenderDrawColor(m_renderer,m_ColorLine.r,m_ColorLine.g,m_ColorLine.b,m_ColorLine.a);

		CPoint point=pFrames->GetPoint();
		int nRow=pFrames->GetRow();
		int nColumn=pFrames->GetColumn();
		int nScreenH=pFrames->GetScreenH();
		int nScreenV=pFrames->GetScreenV();

		if(nRow==0||nColumn==0)
			return;

		int nWidth=nColumn*nScreenH;
		int nHeight=nRow*nScreenV;

		//画网格
		int nLeft=(int)(m_nOrgX+point.x*m_fScale);
		int nTop=(int)(m_nOrgY+point.y*m_fScale);
		//画横线		
		for(int i=0;i<=nRow;i++)
		{
			SDL_RenderDrawLine(m_renderer,nLeft,nTop,(int)(nLeft+nWidth*m_fScale-1),nTop);
			nTop+=(int)(nScreenV*m_fScale);
		}
		//画竖线
		int nLeft1=(int)(m_nOrgX+point.x*m_fScale);
		int nTop1=(int)(m_nOrgY+point.y*m_fScale);
		for(int j=0;j<=nColumn;j++)
		{
			SDL_RenderDrawLine(m_renderer,nLeft1,nTop1,nLeft1,(int)(nTop1+nHeight*m_fScale-1));
			nLeft1+=(int)(nScreenH*m_fScale);
		}
	}
}

void XMultiVideoWindow::ClearMapFrames()
{
	for(MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=m_MapFrames.begin(); iter!=m_MapFrames.end(); iter++)
	{
		delete iter->second;
	}

	m_MapFrames.clear();
}

XMultiVideoWindowFrames* XMultiVideoWindow::AddPage(int nIndex,int nWidth,int nHeight)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetPageWidth(nWidth);
	pFrames->SetPageHeight(nHeight);

	LeaveCriticalSection(&m_CS);
	return pFrames;
}

void XMultiVideoWindow::SetFramesShowModel(int nIndex,BOOL bModel)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetModel(bModel);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesBgPic(int nIndex,CString szPhotoPath)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetPhotoPath(szPhotoPath);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesBgColor(int nIndex,Uint8 r,Uint8 g,Uint8 b)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetBgColor(r,g,b);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesPoint(int nIndex,CPoint point)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetPoint(point);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramesArrage(int nIndex,int nRow,int nColumn,int nScreenH,int nScreenV)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetArrage(nRow,nColumn,nScreenH,nScreenV);

	LeaveCriticalSection(&m_CS);
}

XMultiVideoWindowFrame* XMultiVideoWindow::AddFrame(int nIndex,CString szRTSPAddr,RECTF rFrame,
													RECTF rImage,BOOL bShow)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	XMultiVideoWindowFrame* pFrame=pFrames->AddFrame(szRTSPAddr,rFrame,rImage,bShow);
	LeaveCriticalSection(&m_CS);

	return pFrame;
}

void XMultiVideoWindow::SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rFrame,RECTF rImage)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrame(pFrame,rFrame,rImage);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,CString szRTSPAddr)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrame(pFrame,szRTSPAddr);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrame(pFrame,rFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bSelected)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrameSelected(pFrame,bSelected);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameModel(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bModel)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrameModel(pFrame,bModel);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFramePic(int nIndex,XMultiVideoWindowFrame* pFrame,CString szPhotoPath)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFramePic(pFrame,szPhotoPath);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrame(pFrame,r,g,b,a);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameSelect(int nIndex,XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetVecFrameSelect(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetVecFrameUnselect(int nIndex)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetVecFrameUnselect();

	LeaveCriticalSection(&m_CS);
}


//void XMultiVideoWindow::SetFrameSelectInTwoPage(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL b)
//{
//	EnterCriticalSection(&m_CS);
//
//	XMultiVideoWindowFrames* pFrames = GetFrames(nIndex);
//
//	pFrames->SetFrameSelectInTwoPage(pFrame,b);
//
//	LeaveCriticalSection(&m_CS);
//}
//void XMultiVideoWindow::SetVecFrameSelectInTwoPage(int nIndex,XMultiVideoWindowFrame* pFrame)
//{
//	EnterCriticalSection(&m_CS);
//
//	XMultiVideoWindowFrames* pFrames = GetFrames(nIndex);
//
//	pFrames->SetVecFrameSelectInTwoPage(pFrame);
//
//	LeaveCriticalSection(&m_CS);
//}
//
//void XMultiVideoWindow::SetFrameUnSelectInTwoPage(int nIndex)
//{
//	EnterCriticalSection(&m_CS);
//
//	XMultiVideoWindowFrames* pFrames = GetFrames(nIndex);
//
//	pFrames->SetFrameUnSelectInTwoPage();
//
//	LeaveCriticalSection(&m_CS);
//}


void XMultiVideoWindow::SetFrameImage(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rImage)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrameImage(pFrame,rImage);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameText(int nIndex,XMultiVideoWindowFrame* pFrame,CString text)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrameText(pFrame,text);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameText(int nIndex,XMultiVideoWindowFrame* pFrame,COLORREF nTextColor,int nTextSize)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrameText(pFrame,nTextColor,nTextSize);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DeleteFrame(int nIndex,XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->DeleteFrame(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DeleteFrame(int nIndex)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->ClearVecFrame();

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::ShowFrame(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bShow)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->ShowFrame(pFrame,bShow);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameTop(int nIndex,XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrameTop(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetFrameBottom(int nIndex,XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->SetFrameBottom(pFrame);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DeleteAllFrame()
{
	EnterCriticalSection(&m_CS);

	ClearMapFrames();

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::ChangeFramePos(int nIndex,XMultiVideoWindowFrame* pFrameFront,XMultiVideoWindowFrame* pFrame)
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFrames=GetFrames(nIndex);
	pFrames->ChangeFramePos(pFrameFront,pFrame);

	LeaveCriticalSection(&m_CS);
}

XMultiVideoWindowFrames* XMultiVideoWindow::GetFrames(int nIndex)
{
	MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=m_MapFrames.find(nIndex);

	if(m_MapFrames.end()==iter)
	{
		XMultiVideoWindowFrames* pFrames=new XMultiVideoWindowFrames;
		pFrames->SetMultiVideoWindow(this);
		pFrames->SetFramesIndex(nIndex);
		m_MapFrames.insert(std::pair<int,XMultiVideoWindowFrames*>(nIndex,pFrames));

		return pFrames;
	}
	else
	{
		return iter->second;
	}
}

void XMultiVideoWindow::SetBGImage(CString szPath)
{
	EnterCriticalSection(&m_CSBGImage);

	m_szBGImagePath=szPath;

	if(m_CreateRender)
	{
		char path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		XHandleCode::GetUTF8FromUnicode(szPath,path);
		SDL_Texture* texture=GetImageTexture(m_renderer,path);

		szPath.ReleaseBuffer();

		ClearTextureBGImage();
		m_textureBGImage=texture;
	}

	LeaveCriticalSection(&m_CSBGImage);
}

void XMultiVideoWindow::DeleteBGImage()
{
	EnterCriticalSection(&m_CSBGImage);

	m_szBGImagePath=_T("");
	ClearTextureBGImage();

	LeaveCriticalSection(&m_CSBGImage);
}

void XMultiVideoWindow::SetFrameGBImage(CString szPath)
{
	EnterCriticalSection(&m_CSBGImage);

	m_szFrameBGImagePath=szPath;

	if(m_CreateRender)
	{
		char path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		XHandleCode::GetUTF8FromUnicode(szPath,path);
		SDL_Texture* texture=GetImageTexture(m_renderer,path);

		szPath.ReleaseBuffer();

		ClearFrameTextureBGImage();
		m_textureFrameBGImage=texture;
	}

	LeaveCriticalSection(&m_CSBGImage);
}

void XMultiVideoWindow::DeleteFrameBGImage()
{
	EnterCriticalSection(&m_CSBGImage);

	m_szFrameBGImagePath=_T("");
	ClearFrameTextureBGImage();

	LeaveCriticalSection(&m_CSBGImage);
}

SDL_Texture* XMultiVideoWindow::GetImageTexture(SDL_Renderer *pRenderer,char *szFile)
{
	//SDL_Surface *pSurface=IMG_Load(szFile);

	//if(pSurface==NULL)
	//{
	//	return NULL;
	//}

	//SDL_Surface *pScaleSurface=NULL;
	//SDL_Texture *pTexture=NULL;

	//SDL_Rect rectDes;
	//rectDes.x=0;
	//rectDes.y=0;
	//rectDes.w=800;
	//rectDes.h=800;

	//pScaleSurface=SDL_CreateRGBSurface(0,
	//								   rectDes.w,
	//								   rectDes.h,
	//								   pSurface->format->BitsPerPixel,
	//								   pSurface->format->Rmask,
	//								   pSurface->format->Gmask,
	//								   pSurface->format->Bmask,
	//								   pSurface->format->Amask);

	//if(pScaleSurface!=NULL)
	//{
	//	if(SDL_BlitScaled(pSurface,NULL,pScaleSurface,&rectDes)==0)
	//	{
	//		pTexture=SDL_CreateTextureFromSurface(pRenderer,pScaleSurface);
	//	}
	//}

	//SDL_FreeSurface(pSurface);

	//if(pScaleSurface!=NULL)
	//{
	//	SDL_FreeSurface(pScaleSurface);
	//}

	//return pTexture;


	SDL_Surface *pSurface=IMG_Load(szFile);

	if(pSurface==NULL)
	{
		return NULL;
	}

	SDL_Texture *pTexture;

	pTexture=SDL_CreateTextureFromSurface(pRenderer,pSurface);

	SDL_FreeSurface(pSurface);

	return pTexture;




	//////////////////////////////////////////////////////////////////////////
	//SDL_Texture *pTexture;

	//pTexture=SDL_CreateTextureFromSurface(pRenderer,pSurface);

	//SDL_FreeSurface(pSurface);
	//return pTexture;
}

void XMultiVideoWindow::ClearTextureBGImage()
{
	if(m_textureBGImage!=NULL)
	{
		SDL_DestroyTexture(m_textureBGImage);
		m_textureBGImage=NULL;
	}
}

void XMultiVideoWindow::ClearFrameTextureBGImage()
{
	if(m_textureFrameBGImage!=NULL)
	{
		SDL_DestroyTexture(m_textureFrameBGImage);
		m_textureFrameBGImage=NULL;
	}
}

void XMultiVideoWindow::DrawFrames()
{
	SDL_SetRenderDrawBlendMode(m_renderer,SDL_BLENDMODE_BLEND);

	XMultiVideoWindowFrames* pFramesDrag=NULL;

	for(MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=m_MapFrames.begin();iter!=m_MapFrames.end();iter++)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;
		//对于拖动信号添加的IP为0.0.0.0，要特别处理
		if(pFrames->GetFramesIndex()==100)
		{
			pFramesDrag=pFrames;
		}
		else
		{
			DrawFrames(pFrames);
		}
	}

	///////////////////////////////////////////////////////
	if(pFramesDrag!=NULL)
	{
		DrawFrames(pFramesDrag);
	}
}

void XMultiVideoWindow::DrawFrames(XMultiVideoWindowFrames* pFrames)
{
	SDL_SetRenderDrawBlendMode(m_renderer,SDL_BLENDMODE_BLEND);

	SetFramesDraw(pFrames);
	MAP_RTSP& MapRTSP=m_VideoPlayer->GetMapRTSP();

	CPoint point=pFrames->GetPoint();
	VEC_MULTIVIDEOWINDOWFRAME& VecFrame=pFrames->GetVecFrame();
	for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter=VecFrame.begin();iter!=VecFrame.end();iter++)
	{
		XMultiVideoWindowFrame* pFrame=*iter;

		if(!pFrame->GetShow())
			continue;

		if(!pFrame->m_Draw)
			continue;

		SDL_Rect rectFrame=pFrame->GetRect();
		rectFrame.x=(int)(rectFrame.x*m_fScale+point.x*m_fScale+m_nOrgX);
		rectFrame.y=(int)(rectFrame.y*m_fScale+point.y*m_fScale+m_nOrgY);
		rectFrame.w=(int)(rectFrame.w*m_fScale);
		rectFrame.h=(int)(rectFrame.h*m_fScale);

		SDL_Color color=pFrame->GetBackColor();
		BOOL bModel=pFrame->GetModel();
		CString szPhotoPath=pFrame->GetPhotoPath();
		///////////////////////////////////////////////////////图像
		BOOL bRenderCopyImage=FALSE;
		CString szRTSPAddr=pFrame->GetRTSPAddr();
		if(szRTSPAddr!=_T(""))
		{
			MAP_RTSP::iterator iterRTSP=MapRTSP.find(szRTSPAddr);
			if(MapRTSP.end()!=iterRTSP)
			{
				XRTSP* pRTSP=iterRTSP->second;
				EnterCriticalSection(&pRTSP->m_CSFrameYUV);

				if(pFrame->CreateTexture(m_renderer,pRTSP))
				{
					if(pRTSP->m_frame_yuv!=NULL&&(pRTSP->m_is_file||pRTSP->m_RecvFlagKey))
					{
						if(!pFrame->GetSetRectImageReal())
							pFrame->SetRectImageReal();

						SDL_Rect rectImage=pFrame->GetRectImageReal();
						SDL_Texture* pTextTure=pFrame->GetTexture();
						SDL_UpdateTexture(pTextTure,NULL,pRTSP->m_frame_yuv->data[0],pRTSP->m_frame_yuv->linesize[0]);
						SDL_RenderClear(m_renderer);
						SDL_RenderCopy(m_renderer,pTextTure,&rectImage,&rectFrame);
						bRenderCopyImage=TRUE;
					}
				}
				LeaveCriticalSection(&pRTSP->m_CSFrameYUV);
			}
		}

		//////////////////////////////////////////////////////////////////////////
		if(!bRenderCopyImage)
		{
			if(bModel)
			{
				//绘制纯色
				if(m_bDrawFirstPage)
				{
					//第一页
					SDL_SetRenderDrawColor(m_renderer,color.r,color.g,color.b,color.a);
				}
				else
				{
					//第二页
					if(pFrame->GetSelected())
					{
						//选中(特定颜色)
						SDL_SetRenderDrawColor(m_renderer,0,128,0,255);
					}
					else
					{
						SDL_SetRenderDrawColor(m_renderer,color.r,color.g,color.b,color.a);
					}
				}
				SDL_RenderFillRect(m_renderer,&rectFrame);
			}
			else
			{
				//画图片
				SetFrameGBImage(szPhotoPath);
				DrawFrameBgImage(rectFrame);
			}
		}

		if(m_bDrawFirstPage)
		{
			//绘制边框
			if(!pFrame->GetSelected())
			{
				if(bModel)
				{
					SDL_SetRenderDrawColor(m_renderer,50,50,50,255);
					SDL_RenderDrawRect(m_renderer,&rectFrame);
				}
				else
				{
					//图片不绘制边框
				}
			}
			else
			{
				SDL_SetRenderDrawColor(m_renderer,230,230,230,255);
				SDL_RenderDrawRect(m_renderer,&rectFrame);

				//绘制8个点
				SDL_Rect rectLT;
				rectLT.x=rectFrame.x-3;
				rectLT.y=rectFrame.y-3;
				rectLT.w=6;
				rectLT.h=6;
				SDL_RenderFillRect(m_renderer,&rectLT);

				SDL_Rect rectLB;
				rectLB.x=rectFrame.x-3;
				rectLB.y=rectFrame.y+rectFrame.h-3;
				rectLB.w=6;
				rectLB.h=6;
				SDL_RenderFillRect(m_renderer,&rectLB);

				SDL_Rect rectRT;
				rectRT.x=rectFrame.x+rectFrame.w-3;
				rectRT.y=rectFrame.y-3;
				rectRT.w=6;
				rectRT.h=6;
				SDL_RenderFillRect(m_renderer,&rectRT);

				SDL_Rect rectRB;
				rectRB.x=rectFrame.x+rectFrame.w-3;
				rectRB.y=rectFrame.y+rectFrame.h-3;
				rectRB.w=6;
				rectRB.h=6;
				SDL_RenderFillRect(m_renderer,&rectRB);

				SDL_Rect rectL;
				rectL.x=rectFrame.x-3;
				rectL.y=rectFrame.y+rectFrame.h/2-3;
				rectL.w=6;
				rectL.h=6;
				SDL_RenderFillRect(m_renderer,&rectL);

				SDL_Rect rectT;
				rectT.x=rectFrame.x+rectFrame.w/2-3;
				rectT.y=rectFrame.y-3;
				rectT.w=6;
				rectT.h=6;
				SDL_RenderFillRect(m_renderer,&rectT);

				SDL_Rect rectR;
				rectR.x=rectFrame.x+rectFrame.w-3;
				rectR.y=rectFrame.y+rectFrame.h/2-3;
				rectR.w=6;
				rectR.h=6;
				SDL_RenderFillRect(m_renderer,&rectR);

				SDL_Rect rectB;
				rectB.x=rectFrame.x+rectFrame.w/2-3;
				rectB.y=rectFrame.y+rectFrame.h-3;
				rectB.w=6;
				rectB.h=6;
				SDL_RenderFillRect(m_renderer,&rectB);
			}
		}
		else
		{
			//SDL_SetRenderDrawColor(m_renderer,50,50,50,255);
			//SDL_RenderDrawRect(m_renderer,&rectFrame);
			//第二页绘制 (没有边框)
		}

		///////////////////////////////////////////////////////文字
		if(pFrame->GetCreateTextureText())
			pFrame->CreateTextureText();

		SDL_Texture* pTextureText=pFrame->GetTextureText();

		if(NULL!=pTextureText)
		{
			int nTextWidth=pFrame->GetTextureTextWidth();
			int nTextHeight=pFrame->GetTextureTextHeight();

			SDL_Rect rectText;
			rectText.x=rectFrame.x+rectFrame.w/2-nTextWidth/2;
			rectText.y=rectFrame.y+rectFrame.h/2-nTextHeight/2;
			rectText.w=nTextWidth;
			rectText.h=nTextHeight;

			SDL_RenderCopy(m_renderer,pTextureText,NULL,&rectText);
		}
	}
}

void XMultiVideoWindow::SetFramesDraw(XMultiVideoWindowFrames* pFrames)
{
	VEC_RECT VecRect;

	VEC_MULTIVIDEOWINDOWFRAME& VecFrame=pFrames->GetVecFrame();

	for(VEC_MULTIVIDEOWINDOWFRAME::reverse_iterator iter=VecFrame.rbegin(); iter!=VecFrame.rend(); iter++)
	{
		XMultiVideoWindowFrame* pFrame=*iter;

		pFrame->m_Draw=FALSE;

		if(!pFrame->GetShow())
		{
			continue;
		}

		SDL_Rect rectFrame=pFrame->GetRect();

		CRect crectFrame(rectFrame.x,rectFrame.y,rectFrame.x+rectFrame.w,rectFrame.y+rectFrame.h);

		if(!DecideRectInVecRect(VecRect,crectFrame))
		{
			VecRect.push_back(crectFrame);

			pFrame->m_Draw=TRUE;
		}
	}
}

BOOL XMultiVideoWindow::DecideRectInVecRect(VEC_RECT& VecRect,CRect& rect)
{
	for(VEC_RECT::iterator iter=VecRect.begin(); iter!=VecRect.end(); iter++)
	{
		CRect& rectTemp=*iter;

		CRect temp;

		if(temp.IntersectRect(rectTemp,rect))
		{
			if(temp.EqualRect(rect))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

void XMultiVideoWindow::ResetVideoShow()
{
	ClearRenderer();
	CreateSDLRenderer();

	ReloadBGImage();
	ReloadFrameBGImage();

	ClearMapFramesTexture();
}

void XMultiVideoWindow::ReloadBGImage()
{
	ClearTextureBGImage();

	if(m_szBGImagePath!=_T(""))
	{
		SetBGImage(m_szBGImagePath);
	}
}

void XMultiVideoWindow::ReloadFrameBGImage()
{
	ClearFrameTextureBGImage();

	if(m_szFrameBGImagePath!=_T(""))
	{
		SetFrameGBImage(m_szFrameBGImagePath);
	}
}

void XMultiVideoWindow::ClearMapFramesTexture()
{
	EnterCriticalSection(&m_CS);

	XMultiVideoWindowFrames* pFramesDrag=NULL;

	for(MAP_MULTIVIDEOWINDOWFRAMES::iterator iter=m_MapFrames.begin(); iter!=m_MapFrames.end(); iter++)
	{
		XMultiVideoWindowFrames* pFrames=iter->second;

		VEC_MULTIVIDEOWINDOWFRAME& VecFrame=pFrames->GetVecFrame();

		for(VEC_MULTIVIDEOWINDOWFRAME::iterator iter1=VecFrame.begin(); iter1!=VecFrame.end(); iter1++)
		{
			XMultiVideoWindowFrame* pFrame=*iter1;

			pFrame->ClearTexture();
		}
	}

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::SetResetVideoShow(BOOL b)
{
	m_bResetVideoShow=b;
}

BOOL XMultiVideoWindow::GetResetVideoShow()
{
	return m_bResetVideoShow;
}

void XMultiVideoWindow::SetBGColor(Uint8 r,Uint8 g,Uint8 b)
{
	m_ColorBG.r=r;
	m_ColorBG.g=g;
	m_ColorBG.b=b;
}

void XMultiVideoWindow::SetText(CString text)
{
	EnterCriticalSection(&m_CS);
	if(m_szText!=text)
	{
		m_szText=text;
		m_CreateTextureText=TRUE;
	}
	LeaveCriticalSection(&m_CS);
}
BOOL XMultiVideoWindow::GetCreateTextureText()
{
	return m_CreateTextureText;
}
void XMultiVideoWindow::CreateTextureText()
{
	ClearTextureText();

	if(_T("")!=m_szText)
	{
		m_VideoPlayer->CreateTextureOfText(m_renderer,m_szText,m_nTextSize,
										   m_ColorText,m_textureText,m_nTextureTextWidth,m_nTextureTextHeight);
	}

	m_CreateTextureText=FALSE;
}
SDL_Texture* XMultiVideoWindow::GetTextureText()
{
	return m_textureText;
}
int XMultiVideoWindow::GetTextureTextWidth()
{
	return m_nTextureTextWidth;
}
int XMultiVideoWindow::GetTextureTextHeight()
{
	return m_nTextureTextHeight;
}
void XMultiVideoWindow::ClearTextureText()
{
	if(NULL!=m_textureText)
	{
		SDL_DestroyTexture(m_textureText);
		m_textureText=NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XMultiVideoWindow::SetLineColor(Uint8 r,Uint8 g,Uint8 b)
{
	m_ColorLine.r=r;
	m_ColorLine.g=g;
	m_ColorLine.b=b;
}

void XMultiVideoWindow::AddLineH(int n)
{
	EnterCriticalSection(&m_CS);

	m_VecLineH.push_back(n);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::AddLineV(int n)
{
	EnterCriticalSection(&m_CS);

	m_VecLineV.push_back(n);

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DeleteAllLine()
{
	EnterCriticalSection(&m_CS);

	m_VecLineH.clear();
	m_VecLineV.clear();

	LeaveCriticalSection(&m_CS);
}

void XMultiVideoWindow::DrawLine(CRect& rc)
{
	//CRect rc;
	//GetClientRect(m_HWND, &rc);

	SDL_SetRenderDrawColor(m_renderer,m_ColorLine.r,m_ColorLine.g,m_ColorLine.b,m_ColorLine.a);

	if(m_VecLineV.size()>0)
	{
		for(VEC_NUM::iterator iter=m_VecLineV.begin(); iter!=m_VecLineV.end(); iter++)
		{
			int nNum=*iter;
			SDL_RenderDrawLine(m_renderer,nNum,rc.top,nNum,rc.bottom);
		}
	}
	else
	{
		if(m_Column>1)
		{
			double width=1.0 * rc.Width()/m_Column;

			for(int i=1; i<m_Column; i++)
			{
				int nTemp=(int)(width * i);

				SDL_RenderDrawLine(m_renderer,nTemp,rc.top,nTemp,rc.bottom);
			}
		}
	}

	if(m_VecLineH.size()>0)
	{
		for(VEC_NUM::iterator iter=m_VecLineH.begin(); iter!=m_VecLineH.end(); iter++)
		{
			int nNum=*iter;

			SDL_RenderDrawLine(m_renderer,rc.left,nNum,rc.right,nNum);
		}
	}
	else
	{
		if(m_Row>1)
		{
			double height=1.0 * rc.Height()/m_Row;

			for(int i=1; i<m_Row; i++)
			{
				int nTemp=(int)(height * i);

				SDL_RenderDrawLine(m_renderer,rc.left,nTemp,rc.right,nTemp);
			}
		}
	}

	if(m_Column>=1&&m_Row>=1)
	{
		SDL_Rect rect;
		rect.x=0;
		rect.y=0;
		rect.w=rc.right;
		rect.h=rc.bottom;
		SDL_RenderDrawRect(m_renderer,&rect);
	}
}
