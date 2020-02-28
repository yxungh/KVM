#pragma once

#include "XConstant.h"
#include "videoinc.h"
#include "VideoPlayerConstant.h"

class XMultiVideoWindowFrames;
class XVideoPlayer;
class XMultiVideoWindowFrame;
class XBaseScreenManage;

class XMultiVideoWindow
{
public:
	XMultiVideoWindow(void);
	~XMultiVideoWindow(void);

public:

	void SetVideoPlayer(XVideoPlayer* p);

	XVideoPlayer* GetVideoPlayer();

	BOOL CreateSDLWindow();

	BOOL CreateSDLRenderer();

	BOOL GetCreateSDLWindow();

	//获取是否创建SDLRenderer
	BOOL GetCreateSDLRenderer();

	HWND GetHWND();

	void SetHWND(HWND h);

	//设置边框
	void SetFrame(int nRow,int nColumn);

	//绘制
	void Draw();

	//添加绘制页面
	XMultiVideoWindowFrames* AddPage(int nIndex,int nWidth,int nheight);

	//设置背景模式
	void SetFramesShowModel(int nIndex,BOOL bModel);
	//设置背景图片
	void SetFramesBgPic(int nIndex,CString szPhotoPath);
	//设置背景颜色
	void SetFramesBgColor(int nIndex,Uint8 r,Uint8 g,Uint8 b);
	//设置页面网格开始点
	void SetFramesPoint(int nIndex,CPoint point);
	//设置页面网格行列
	void SetFramesArrage(int nIndex,int nRow,int nColumn,int nScreenH,int nScreenV);

	//////////////////////////////////////////////////////////////////////////

	//添加Frame
	XMultiVideoWindowFrame* AddFrame(int nIndex,CString szRTSPAddr,RECTF rFrame,
									 RECTF rImage,BOOL bShow=TRUE);

	//设置Frame
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rFrame,RECTF rImage);

	//设置Frame
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rFrame);

	//设置Frame
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,CString szRTSPAddr);

	//设置frame选中
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bSelected);

	//设置frame显示模式
	void SetFrameModel(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bModel);

	//设置Frame背景tu
	void SetFramePic(int nIndex,XMultiVideoWindowFrame* pFrame,CString szPhotoPath);

	//设置Frame
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,Uint8 r,Uint8 g,Uint8 b,Uint8 a);

	//设置选中
	void SetFrameSelect(int nIndex,XMultiVideoWindowFrame* pFrame);

	//设置全部不选中
	void SetVecFrameUnselect(int nIndex);

	//第二页选中
	//void SetFrameSelectInTwoPage(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL b);
	//void SetVecFrameSelectInTwoPage(int nIndex,XMultiVideoWindowFrame* pFrame);
	//void SetFrameUnSelectInTwoPage(int nIndex);

	//设置Frame Image
	void SetFrameImage(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rImage);

	//设置Frame文字
	void SetFrameText(int nIndex,XMultiVideoWindowFrame* pFrame,CString text);

	//设置Frame文字
	void SetFrameText(int nIndex,XMultiVideoWindowFrame* pFrame,COLORREF nTextColor,int nTextSize);

	//删除Frame
	void DeleteFrame(int nIndex,XMultiVideoWindowFrame* pFrame);

	void DeleteFrame(int nIndex);

	//显示或隐藏Frame
	void ShowFrame(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bShow);

	//设置Frame置顶
	void SetFrameTop(int nIndex,XMultiVideoWindowFrame* pFrame);

	//设置Frame置底
	void SetFrameBottom(int nIndex,XMultiVideoWindowFrame* pFrame);

	//删除所有Frame
	void DeleteAllFrame();

	//改变Frame位置
	void ChangeFramePos(int nIndex,XMultiVideoWindowFrame* pFrameFront,XMultiVideoWindowFrame* pFrame);

	//设置背景图片
	void SetBGImage(CString szPath);
	void SetFrameGBImage(CString szPath);

	//设置背景颜色
	void SetBGColor(Uint8 r,Uint8 g,Uint8 b);

	//设置分隔线颜色
	void SetLineColor(Uint8 r,Uint8 g,Uint8 b);

	//删除背景图片
	void DeleteBGImage();
	void DeleteFrameBGImage();

	//设置重置视频显示
	void SetResetVideoShow(BOOL b);

	//获取重置视频显示
	BOOL GetResetVideoShow();

	void ResetVideoShow();

	SDL_Renderer* GetRenderer();

	void SetMushHardCode(BOOL b);

	//添加水平直线
	void AddLineH(int n);

	//添加垂直直线
	void AddLineV(int n);

	//删除所有直线
	void DeleteAllLine();

	//////////////////////////////////////////////////////////////////////////
	//设置放缩
	void SetMultiVideoWindowScale(float fScale);

	float GetMultiVideoWindowScale();

	//设置绘制页面
	void SetMultiVideoWindowDrawPage(BOOL b);

	//////////////////////////////////////////////////////////////////////////
	void SetText(CString text);
	BOOL GetCreateTextureText();
	void CreateTextureText();
	SDL_Texture* GetTextureText();
	int GetTextureTextWidth();
	int GetTextureTextHeight();
	void ClearTextureText();

private:

	//清除数据
	void ClearData();
	//绘制背景颜色
	void DrawBGColor();
	//绘制边框
	void DrawLine(CRect& rect);
	//绘制画图页面
	void DrawPage();
	void DrawText();

	void ClearMapFrames();

	void DrawFrames();
	void DrawFrames(XMultiVideoWindowFrames* pFrames);

	//绘制页面
	void DrawBGImage();
	void DrawBGImage(SDL_Rect rect);
	//绘制frame
	void DrawFrameBgImage(SDL_Rect rect);

	XMultiVideoWindowFrames* GetFrames(int nIndex);

	SDL_Texture* GetImageTexture(SDL_Renderer *pRenderer,char *szFile);

	void ClearTextureBGImage();
	void ClearFrameTextureBGImage();

	void ClearRenderer();
	void ClearMapFramesTexture();

	void ReloadBGImage();
	void ReloadFrameBGImage();

	void SetFramesDraw(XMultiVideoWindowFrames* pFrames);
	BOOL DecideRectInVecRect(VEC_RECT& VecRect,CRect& rect);

public:

	XVideoPlayer* m_VideoPlayer;

	XBaseScreenManage* m_pManage;

	//句柄
	HWND m_HWND;

	//是否创建Window
	BOOL m_CreateWindow;

	SDL_Window* m_window;

	SDL_Renderer* m_renderer;

	//是否创建renderer
	BOOL m_CreateRender;

	int m_Row;

	int m_Column;

	CRITICAL_SECTION m_CS;

	CRITICAL_SECTION m_CSBGImage;

	//页面背景
	SDL_Texture* m_textureBGImage;
	CString m_szBGImagePath;
	//Framebeijing
	SDL_Texture* m_textureFrameBGImage;
	CString m_szFrameBGImagePath;

	MAP_MULTIVIDEOWINDOWFRAMES m_MapFrames;

	BOOL m_bResetVideoShow;

	//背景颜色
	SDL_Color m_ColorBG;

	//分隔线颜色
	SDL_Color m_ColorLine;

	//是否必需硬解
	BOOL m_MushHardCode;

	//水平直线
	VEC_NUM m_VecLineH;

	//垂直直线
	VEC_NUM m_VecLineV;

	//缩放
	float m_fScale;

	//远点偏移
	int m_nOrgX;
	int m_nOrgY;

	//绘制第一页
	static BOOL m_bDrawFirstPage;

	//////////////////////////////////////////////////////////////////////////
	//绘制文字
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

};