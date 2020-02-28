#pragma once

#include "XConstant.h"

class XRTSP;
class XMultiVideoWindowFrames;

class XMultiVideoWindowFrame
{
public:
	XMultiVideoWindowFrame(void);
	~XMultiVideoWindowFrame(void);

public:

	void SetMultiVideoWindowFrames(XMultiVideoWindowFrames* p);

	CString GetRTSPAddr();

	void SetRTSPAddr(CString s);

	void SetRect(RECTF r);

	SDL_Rect GetRect();

	void SetRectImage(RECTF r);

	RECTF& GetRectImage();

	BOOL CreateTexture(SDL_Renderer* renderer,XRTSP* pRTSP);

	void ClearTexture();

	SDL_Texture* GetTexture();

	SDL_Rect GetRectImageReal();

	BOOL GetSetRectImageReal();

	void SetRectImageReal();

	void Show(BOOL bShow);

	BOOL GetShow();

	void SetBackColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a);
	inline SDL_Color GetBackColor() { return m_ColorBG; }
	//////////////////////////////////////////////////////////////////////////
	inline void SetSelected(BOOL b) { m_bSelected=b; }
	inline BOOL GetSelected() { return m_bSelected; }

	inline void SetPhotoPath(CString szPhotoPath) { m_szPhotoPath=szPhotoPath; }
	inline CString GetPhotoPath() { return m_szPhotoPath; }

	inline void SetModel(BOOL b) { m_bModel=b; }
	inline BOOL GetModel() { return m_bModel; }

	//inline void SetSelectedInTwo(BOOL b){m_bSelectedInTwo=b;}
	//inline BOOL GetSelectedInTwo(){return m_bSelectedInTwo;}


public:

	XMultiVideoWindowFrames* m_MultiVideoWindowFrames;

	//RTSP地址
	CString m_RTSPAddr;

	//显示区域
	SDL_Rect m_Rect;

	//显示图像区域,按照1920*1088比例
	RECTF m_RectImage;

	//是否创建Texture
	BOOL m_CreateTexture;

	SDL_Texture* m_texture;

	int m_textureWidth;

	int m_textureHeight;

	//是否设置真实图像区域
	BOOL m_SetRectImageReal;

	//真实图像区域
	SDL_Rect m_RectImageReal;

	//显示状态
	BOOL m_Show;

	//是否绘制
	BOOL m_Draw;

public://文字

	void SetText(CString text);

	void SetText(COLORREF nTextColor,int nTextSize);

	BOOL GetCreateTextureText();

	void CreateTextureText();

	SDL_Texture* GetTextureText();

	int GetTextureTextWidth();

	int GetTextureTextHeight();

	void ClearTextureText();

private://文字

	//文字Texture
	SDL_Texture* m_textureText;

	//文字
	CString m_szText;

	//文字颜色
	SDL_Color m_ColorText;

	//文字大小
	int m_nTextSize;

	//是否创建文字
	BOOL m_CreateTextureText;

	//文字宽度
	int m_nTextureTextWidth;

	//文字高度
	int m_nTextureTextHeight;

private:
	//背景颜色
	SDL_Color m_ColorBG;

	//选中
	BOOL m_bSelected;

	//图片
	CString m_szPhotoPath;

	BOOL m_bModel;

	//第二页选中
	//BOOL m_bSelectedInTwo;
};

