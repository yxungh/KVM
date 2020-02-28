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

	//��ȡ�Ƿ񴴽�SDLRenderer
	BOOL GetCreateSDLRenderer();

	HWND GetHWND();

	void SetHWND(HWND h);

	//���ñ߿�
	void SetFrame(int nRow,int nColumn);

	//����
	void Draw();

	//��ӻ���ҳ��
	XMultiVideoWindowFrames* AddPage(int nIndex,int nWidth,int nheight);

	//���ñ���ģʽ
	void SetFramesShowModel(int nIndex,BOOL bModel);
	//���ñ���ͼƬ
	void SetFramesBgPic(int nIndex,CString szPhotoPath);
	//���ñ�����ɫ
	void SetFramesBgColor(int nIndex,Uint8 r,Uint8 g,Uint8 b);
	//����ҳ������ʼ��
	void SetFramesPoint(int nIndex,CPoint point);
	//����ҳ����������
	void SetFramesArrage(int nIndex,int nRow,int nColumn,int nScreenH,int nScreenV);

	//////////////////////////////////////////////////////////////////////////

	//���Frame
	XMultiVideoWindowFrame* AddFrame(int nIndex,CString szRTSPAddr,RECTF rFrame,
									 RECTF rImage,BOOL bShow=TRUE);

	//����Frame
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rFrame,RECTF rImage);

	//����Frame
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rFrame);

	//����Frame
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,CString szRTSPAddr);

	//����frameѡ��
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bSelected);

	//����frame��ʾģʽ
	void SetFrameModel(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bModel);

	//����Frame����tu
	void SetFramePic(int nIndex,XMultiVideoWindowFrame* pFrame,CString szPhotoPath);

	//����Frame
	void SetFrame(int nIndex,XMultiVideoWindowFrame* pFrame,Uint8 r,Uint8 g,Uint8 b,Uint8 a);

	//����ѡ��
	void SetFrameSelect(int nIndex,XMultiVideoWindowFrame* pFrame);

	//����ȫ����ѡ��
	void SetVecFrameUnselect(int nIndex);

	//�ڶ�ҳѡ��
	//void SetFrameSelectInTwoPage(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL b);
	//void SetVecFrameSelectInTwoPage(int nIndex,XMultiVideoWindowFrame* pFrame);
	//void SetFrameUnSelectInTwoPage(int nIndex);

	//����Frame Image
	void SetFrameImage(int nIndex,XMultiVideoWindowFrame* pFrame,RECTF rImage);

	//����Frame����
	void SetFrameText(int nIndex,XMultiVideoWindowFrame* pFrame,CString text);

	//����Frame����
	void SetFrameText(int nIndex,XMultiVideoWindowFrame* pFrame,COLORREF nTextColor,int nTextSize);

	//ɾ��Frame
	void DeleteFrame(int nIndex,XMultiVideoWindowFrame* pFrame);

	void DeleteFrame(int nIndex);

	//��ʾ������Frame
	void ShowFrame(int nIndex,XMultiVideoWindowFrame* pFrame,BOOL bShow);

	//����Frame�ö�
	void SetFrameTop(int nIndex,XMultiVideoWindowFrame* pFrame);

	//����Frame�õ�
	void SetFrameBottom(int nIndex,XMultiVideoWindowFrame* pFrame);

	//ɾ������Frame
	void DeleteAllFrame();

	//�ı�Frameλ��
	void ChangeFramePos(int nIndex,XMultiVideoWindowFrame* pFrameFront,XMultiVideoWindowFrame* pFrame);

	//���ñ���ͼƬ
	void SetBGImage(CString szPath);
	void SetFrameGBImage(CString szPath);

	//���ñ�����ɫ
	void SetBGColor(Uint8 r,Uint8 g,Uint8 b);

	//���÷ָ�����ɫ
	void SetLineColor(Uint8 r,Uint8 g,Uint8 b);

	//ɾ������ͼƬ
	void DeleteBGImage();
	void DeleteFrameBGImage();

	//����������Ƶ��ʾ
	void SetResetVideoShow(BOOL b);

	//��ȡ������Ƶ��ʾ
	BOOL GetResetVideoShow();

	void ResetVideoShow();

	SDL_Renderer* GetRenderer();

	void SetMushHardCode(BOOL b);

	//���ˮƽֱ��
	void AddLineH(int n);

	//��Ӵ�ֱֱ��
	void AddLineV(int n);

	//ɾ������ֱ��
	void DeleteAllLine();

	//////////////////////////////////////////////////////////////////////////
	//���÷���
	void SetMultiVideoWindowScale(float fScale);

	float GetMultiVideoWindowScale();

	//���û���ҳ��
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

	//�������
	void ClearData();
	//���Ʊ�����ɫ
	void DrawBGColor();
	//���Ʊ߿�
	void DrawLine(CRect& rect);
	//���ƻ�ͼҳ��
	void DrawPage();
	void DrawText();

	void ClearMapFrames();

	void DrawFrames();
	void DrawFrames(XMultiVideoWindowFrames* pFrames);

	//����ҳ��
	void DrawBGImage();
	void DrawBGImage(SDL_Rect rect);
	//����frame
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

	//���
	HWND m_HWND;

	//�Ƿ񴴽�Window
	BOOL m_CreateWindow;

	SDL_Window* m_window;

	SDL_Renderer* m_renderer;

	//�Ƿ񴴽�renderer
	BOOL m_CreateRender;

	int m_Row;

	int m_Column;

	CRITICAL_SECTION m_CS;

	CRITICAL_SECTION m_CSBGImage;

	//ҳ�汳��
	SDL_Texture* m_textureBGImage;
	CString m_szBGImagePath;
	//Framebeijing
	SDL_Texture* m_textureFrameBGImage;
	CString m_szFrameBGImagePath;

	MAP_MULTIVIDEOWINDOWFRAMES m_MapFrames;

	BOOL m_bResetVideoShow;

	//������ɫ
	SDL_Color m_ColorBG;

	//�ָ�����ɫ
	SDL_Color m_ColorLine;

	//�Ƿ����Ӳ��
	BOOL m_MushHardCode;

	//ˮƽֱ��
	VEC_NUM m_VecLineH;

	//��ֱֱ��
	VEC_NUM m_VecLineV;

	//����
	float m_fScale;

	//Զ��ƫ��
	int m_nOrgX;
	int m_nOrgY;

	//���Ƶ�һҳ
	static BOOL m_bDrawFirstPage;

	//////////////////////////////////////////////////////////////////////////
	//��������
	//����Texture
	SDL_Texture* m_textureText;
	//����
	CString m_szText;
	//������ɫ
	SDL_Color m_ColorText;
	//���ִ�С
	int m_nTextSize;
	//�Ƿ񴴽�����
	BOOL m_CreateTextureText;
	//���ֿ��
	int m_nTextureTextWidth;
	//���ָ߶�
	int m_nTextureTextHeight;

};