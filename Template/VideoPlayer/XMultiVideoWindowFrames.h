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

	//��ȡFrame����
	VEC_MULTIVIDEOWINDOWFRAME& GetVecFrame();

	//���Frame
	XMultiVideoWindowFrame* AddFrame(CString szRTSPAddr,RECTF rFrame,RECTF rImage,
									 BOOL bShow);

	//����Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame,RECTF rFrame,RECTF rImage);

	//����Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame,RECTF rFrame);

	//����Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame,CString szRTSPAddr);

	//����Frame
	void SetFrame(XMultiVideoWindowFrame* pFrame,Uint8 r,Uint8 g,Uint8 b,Uint8 a);

	//����Frame����
	void SetFrameText(XMultiVideoWindowFrame* pFrame,CString text);

	//����Frame����
	void SetFrameText(XMultiVideoWindowFrame* pFrame,COLORREF nTextColor,int nTextSize);

	//����Frame Image
	void SetFrameImage(XMultiVideoWindowFrame* pFrame,RECTF rImage);

	//����frameѡ��
	void SetFrameSelected(XMultiVideoWindowFrame* pFrame,BOOL bSelected);

	//����Frame����
	void SetFramePic(XMultiVideoWindowFrame* pFrame,CString szPhotoPath);

	//����Frame��ʾģʽ
	void SetFrameModel(XMultiVideoWindowFrame* pFrame,BOOL bModel);

	void SetVecFrameSelect(XMultiVideoWindowFrame* pFrame);

	void SetVecFrameUnselect();

	//�ڶ�ҳѡ��
	//void SetFrameSelectInTwoPage(XMultiVideoWindowFrame* pFrame,BOOL b);
	//void SetVecFrameSelectInTwoPage(XMultiVideoWindowFrame* pFrame);
	//void SetFrameUnSelectInTwoPage();

	//ɾ��Frame
	void DeleteFrame(XMultiVideoWindowFrame* pFrame);

	//��ʾ������Frame
	void ShowFrame(XMultiVideoWindowFrame* pFrame,BOOL bShow);

	//����Frame�ö�
	void SetFrameTop(XMultiVideoWindowFrame* pFrame);

	//����Frame�õ�
	void SetFrameBottom(XMultiVideoWindowFrame* pFrame);

	//ɾ������Frame
	void DeleteAllFrame();

	//�ı�Frameλ��
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