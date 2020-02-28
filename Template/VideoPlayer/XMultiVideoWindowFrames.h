#pragma once

#include "XConstant.h"
#include "VideoPlayerConstant.h"

class XMultiVideoWindow;
class XVideoPlayer;

class XMultiVideoWindowFrames
{
public:
	XMultiVideoWindowFrames(void);
	~XMultiVideoWindowFrames(void);

public:

	inline void SetFramesIndex(int n) { m_nIndex=n; }
	inline int GetFramesIndex() { return m_nIndex; }

	inline void SetPageWidth(int n) { m_nPageWidth=n; }
	inline int GetPageWidth() { return m_nPageWidth; }

	inline void SetPageHeight(int n) { m_nPageHeight=n; }
	inline int GetPageHeight() { return m_nPageHeight; }

	inline void SetPoint(CPoint point) { m_Point=point; }
	inline CPoint GetPoint() { return m_Point; }

	inline void SetArrage(int nRow,int nColumn,int nScreenH,int nScreenV) { m_nRow=nRow;m_nColumn=nColumn;m_nScreenH=nScreenH;m_nScreenV=nScreenV; }
	inline int GetRow() { return m_nRow; }
	inline int GetColumn() { return m_nColumn; }
	inline int GetScreenH(){return m_nScreenH;}
	inline int GetScreenV(){return m_nScreenV;}

public:

	void SetMultiVideoWindow(XMultiVideoWindow* p);

	XVideoPlayer* GetVideoPlayer();

	SDL_Renderer* GetRenderer();

	//获取Frame集合
	VEC_MULTIVIDEOWINDOWFRAME& GetVecFrame();

	//添加Frame
	XMultiVideoWindowFrame* AddFrame(CString szRTSPAddr,RECTF rFrame,RECTF rImage,
									 BOOL bShow);

	//设置Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame,RECTF rFrame,RECTF rImage);

	//设置Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame,RECTF rFrame);

	//设置Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame,CString szRTSPAddr);

	//设置Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame,Uint8 r,Uint8 g,Uint8 b,Uint8 a);

	//设置Frame文字
	void SetFrameText(XMultiVideoWindowFrame* pFrame,CString text);

	//设置Frame文字
	void SetFrameText(XMultiVideoWindowFrame* pFrame,COLORREF nTextColor,int nTextSize);

	//设置Frame Image
	void SetFrameImage(XMultiVideoWindowFrame* pFrame,RECTF rImage);

	//设置frame选中
	void SetFrameSelected(XMultiVideoWindowFrame* pFrame,BOOL bSelected);

	//设置Frame背景
	void SetFramePic(XMultiVideoWindowFrame* pFrame,CString szPhotoPath);

	//设置Frame显示模式
	void SetFrameModel(XMultiVideoWindowFrame* pFrame,BOOL bModel);

	void SetVecFrameSelect(XMultiVideoWindowFrame* pFrame);

	void SetVecFrameUnselect();

	//第二页选中
	//void SetFrameSelectInTwoPage(XMultiVideoWindowFrame* pFrame,BOOL b);
	//void SetVecFrameSelectInTwoPage(XMultiVideoWindowFrame* pFrame);
	//void SetFrameUnSelectInTwoPage();

	//删除Frame
	void DeleteFrame(XMultiVideoWindowFrame* pFrame);

	//显示或隐藏Frame
	void ShowFrame(XMultiVideoWindowFrame* pFrame,BOOL bShow);

	//设置Frame置顶
	void SetFrameTop(XMultiVideoWindowFrame* pFrame);

	//设置Frame置底
	void SetFrameBottom(XMultiVideoWindowFrame* pFrame);

	//删除所有Frame
	void DeleteAllFrame();

	//改变Frame位置
	void ChangeFramePos(XMultiVideoWindowFrame* pFrameFront,XMultiVideoWindowFrame* pFrame);

	void ClearVecFrame();

	//////////////////////////////////////////////////////////////////////////
	void SetBgColor(Uint8 r,Uint8 g,Uint8 b);
	inline SDL_Color GetBgColor() { return m_ColorBG; }
	inline void SetModel(BOOL b) { m_bModel=b; }
	inline BOOL GetModel() { return m_bModel; }
	inline void SetPhotoPath(CString szPath) { m_szPhotoPath=szPath; }
	inline CString GetPhotoPath() { return m_szPhotoPath; }

public:

	XMultiVideoWindow* m_MultiVideoWindow;

	int  m_nIndex;

	int m_nPageWidth;
	int m_nPageHeight;

	BOOL m_bModel;
	CString m_szPhotoPath;
	SDL_Color m_ColorBG;
	CPoint m_Point;
	int m_nRow;
	int m_nColumn;
	int m_nScreenH=0;
	int m_nScreenV=0;


	VEC_MULTIVIDEOWINDOWFRAME m_VecFrame;
};