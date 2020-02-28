#include "StdAfx.h"
#include "XMultiVideoWindowFrame.h"
#include "XRTSP.h"
#include "XVideoPlayer.h"
#include "XMultiVideoWindowFrames.h"

XMultiVideoWindowFrame::XMultiVideoWindowFrame(void)
{
	m_RTSPAddr=_T("");

	m_CreateTexture=FALSE;

	m_textureWidth=0;

	m_textureHeight=0;

	m_SetRectImageReal=FALSE;

	m_Show=TRUE;

	m_texture=NULL;

	m_MultiVideoWindowFrames=NULL;

	m_textureText=NULL;

	m_szText=_T("");

	m_ColorText.r=255;
	m_ColorText.g=255;
	m_ColorText.b=255;
	m_ColorText.a=255;

	m_ColorBG.r=91;
	m_ColorBG.g=155;
	m_ColorBG.b=213;
	m_ColorBG.a=255;

	m_nTextSize=16;

	m_CreateTextureText=FALSE;

	m_nTextureTextWidth=0;

	m_nTextureTextHeight=0;

	m_Draw=TRUE;

	m_bSelected=FALSE;

	m_szPhotoPath=_T("");

	m_bModel=TRUE;

	//m_bSelectedInTwo=FALSE;
}

XMultiVideoWindowFrame::~XMultiVideoWindowFrame(void)
{
	ClearTexture();

	ClearTextureText();
}

void XMultiVideoWindowFrame::SetMultiVideoWindowFrames(XMultiVideoWindowFrames* p)
{
	m_MultiVideoWindowFrames=p;
}

CString XMultiVideoWindowFrame::GetRTSPAddr()
{
	return m_RTSPAddr;
}

void XMultiVideoWindowFrame::SetRTSPAddr(CString s)
{
	m_RTSPAddr=s;
}

void XMultiVideoWindowFrame::SetRect(RECTF r)
{
	m_Rect.x=(int)(r.X);
	m_Rect.y=(int)(r.Y);
	m_Rect.w=(int)(r.Width+(r.X-m_Rect.x));
	m_Rect.h=(int)(r.Height+(r.Y-m_Rect.y));
}

SDL_Rect XMultiVideoWindowFrame::GetRect()
{
	return m_Rect;
}

void XMultiVideoWindowFrame::SetRectImage(RECTF r)
{
	m_RectImage=r;

	m_SetRectImageReal=FALSE;
}

BOOL XMultiVideoWindowFrame::CreateTexture(SDL_Renderer* renderer,XRTSP* pRTSP)
{
	if(m_CreateTexture)
	{
		if(m_textureWidth!=pRTSP->m_frame_yuv_Width||m_textureHeight!=pRTSP->m_frame_yuv_Height)
		{
			ClearTexture();
		}
	}

	if(m_CreateTexture)
	{
		return TRUE;
	}

	if(pRTSP->m_frame_yuv==NULL)
	{
		return FALSE;
	}

	SDL_Texture* texture=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_IYUV,SDL_TEXTUREACCESS_STREAMING,
										   pRTSP->m_frame_yuv_Width,pRTSP->m_frame_yuv_Height);

	if(!texture)
	{
		return FALSE;
	}

	m_textureWidth=pRTSP->m_frame_yuv_Width;

	m_textureHeight=pRTSP->m_frame_yuv_Height;

	m_texture=texture;

	m_CreateTexture=TRUE;

	return TRUE;
}

void XMultiVideoWindowFrame::ClearTexture()
{
	m_SetRectImageReal=FALSE;

	m_CreateTexture=FALSE;

	if(m_texture!=NULL)
	{
		SDL_DestroyTexture(m_texture);

		m_texture=NULL;
	}
}

SDL_Texture* XMultiVideoWindowFrame::GetTexture()
{
	return m_texture;
}

SDL_Rect XMultiVideoWindowFrame::GetRectImageReal()
{
	return m_RectImageReal;
}

BOOL XMultiVideoWindowFrame::GetSetRectImageReal()
{
	return m_SetRectImageReal;
}

RECTF& XMultiVideoWindowFrame::GetRectImage()
{
	return m_RectImage;
}

void XMultiVideoWindowFrame::SetRectImageReal()
{
	float nResolutionH=1920;
	float nResolutionV=1088;

	int nImageX=0;
	int nImageY=0;
	int nImageWidth=0;
	int nImageHeight=0;

	if(((nResolutionH-m_RectImage.Width)<0.01)&&((nResolutionV-m_RectImage.Height)<0.01))
	{
		nImageWidth=m_textureWidth;
		nImageHeight=m_textureHeight;
	}
	else
	{
		float imageWidth=(float)m_textureWidth;
		float imageHeight=(float)m_textureHeight;

		float dwLeft=m_RectImage.X * imageWidth/nResolutionH;
		int nLeft=(int)(dwLeft);

		float dwWidth=m_RectImage.Width * imageWidth/nResolutionH;
		int nWidth=(int)(dwWidth+(dwLeft-nLeft));

		float dwTop=m_RectImage.Y * imageHeight/nResolutionV;
		int nTop=(int)(dwTop);

		float dwHeight=m_RectImage.Height * imageHeight/nResolutionV;
		int nHeight=(int)(dwHeight+(dwTop-nTop));

		nImageX=nLeft;
		nImageY=nTop;
		nImageWidth=nWidth;
		nImageHeight=nHeight;
	}

	m_RectImageReal.x=nImageX;
	m_RectImageReal.y=nImageY;
	m_RectImageReal.w=nImageWidth;
	m_RectImageReal.h=nImageHeight;

	m_SetRectImageReal=TRUE;
}

void XMultiVideoWindowFrame::Show(BOOL bShow)
{
	m_Show=bShow;
}

BOOL XMultiVideoWindowFrame::GetShow()
{
	return m_Show;
}

void XMultiVideoWindowFrame::SetBackColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	m_ColorBG.r=r;
	m_ColorBG.g=g;
	m_ColorBG.b=b;
	m_ColorBG.a=a;
}

////////////////////////////////////////////////////////////////////

void XMultiVideoWindowFrame::ClearTextureText()
{
	if(NULL!=m_textureText)
	{
		SDL_DestroyTexture(m_textureText);

		m_textureText=NULL;
	}
}

void XMultiVideoWindowFrame::SetText(CString text)
{
	if(m_szText!=text)
	{
		m_szText=text;
		m_CreateTextureText=TRUE;
	}
}

BOOL XMultiVideoWindowFrame::GetCreateTextureText()
{
	return m_CreateTextureText;
}

int XMultiVideoWindowFrame::GetTextureTextWidth()
{
	return m_nTextureTextWidth;
}

int XMultiVideoWindowFrame::GetTextureTextHeight()
{
	return m_nTextureTextHeight;
}

void XMultiVideoWindowFrame::CreateTextureText()
{
	ClearTextureText();

	if(_T("")!=m_szText)
	{
		SDL_Renderer* pRenderer=m_MultiVideoWindowFrames->GetRenderer();

		XVideoPlayer* pVideoPlayer=m_MultiVideoWindowFrames->GetVideoPlayer();

		pVideoPlayer->CreateTextureOfText(pRenderer,m_szText,m_nTextSize,
										  m_ColorText,m_textureText,m_nTextureTextWidth,m_nTextureTextHeight);
	}

	m_CreateTextureText=FALSE;
}

SDL_Texture* XMultiVideoWindowFrame::GetTextureText()
{
	return m_textureText;
}

void XMultiVideoWindowFrame::SetText(COLORREF nTextColor,int nTextSize)
{
	m_nTextSize=nTextSize;

	m_ColorText.r=(Uint8)(nTextColor&0xFF);
	m_ColorText.g=(Uint8)((nTextColor&0xFF00)>>8);
	m_ColorText.b=(Uint8)((nTextColor&0xFF0000)>>16);
}