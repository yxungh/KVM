#pragma once

class XRTSP;
class XVideoPlayer;

class XRTSPHWND
{
public:
	XRTSPHWND(void);
	~XRTSPHWND(void);

public:

	void SetVideoPlayer(XVideoPlayer* p);

	BOOL CreateSDLWindow();

	BOOL CreateSDLRenderer();

	BOOL CreateTexture(XRTSP* pRTSP);

	HWND GetHWND();

	void SetHWND(HWND h);

	CString GetRTSPAddr();

	void SetRTSPAddr(CString s);

	//��ȡ�Ƿ񴴽�SDLWindow
	BOOL GetCreateSDLWindow();

	//��ȡ�Ƿ񴴽�SDLRenderer
	BOOL GetCreateSDLRenderer();

	//�������
	void ClearData();

	void ClearRenderer();

	void ClearTexture();

	//����������Ƶ��ʾ
	void SetResetVideoShow(BOOL b);

	//��ȡ������Ƶ��ʾ
	BOOL GetResetVideoShow();

	//������Ƶ��ʾ
	void ResetVideoShow();

	//���ñ�����ɫ
	void SetBGColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a);

public:

	//��������
	void SetText(CString szText);

	//����������ɫ
	void SetTextColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a);

	//�������ִ�С
	void SetTextSize(int n);

	//�������Texture
	void ClearTextureText();

	//��������Texture
	void CreateTextureText();

public:

	//�������ֹ�������
	void SetTextScrollRect(int nLeft,int nTop,int nRight);

	//�������ֹ���ʱ��Ͳ���
	void SetHWNDTextScrollTimeAndStep(int nDistanceTime,int nStep);

	//��ʼ���ֹ���
	void BeginTextScroll();

	//��ȡ���ֹ�����ʼ����
	SDL_Rect GetTextScrollSrcRect();

	//��ȡ���ֹ���Ŀ������
	SDL_Rect GetTextScrollDesRect();

	//���ֹ���
	void TextScroll();

public:

	XVideoPlayer* m_VideoPlayer;

	//���
	HWND m_HWND;

	//RTSP��ַ
	CString m_RTSPAddr;

	//�Ƿ񴴽�Window
	BOOL m_CreateWindow;

	//�Ƿ񴴽�renderer
	BOOL m_CreateRender;

	//�Ƿ񴴽�Texture
	BOOL m_CreateTexture;

	SDL_Window* m_window;

	SDL_Renderer* m_renderer;

	SDL_Texture* m_texture;

	int m_textureWidth;

	int m_textureHeight;

	BOOL m_bResetVideoShow;

	//������ɫ
	SDL_Color m_BGColor;

	int m_HWNDWidth;

	int m_HWNDHeight;

public://����

	//����Texture
	SDL_Texture* m_textureText;

	//����
	CString m_szText;

	//������ɫ
	SDL_Color m_TextColor;

	//���ִ�С
	int m_nTextSize;

	//�Ƿ���Ҫ��������
	BOOL m_CreateTextureText;

	//���ֿ��
	int m_nTextureTextWidth;

	//���ָ߶�
	int m_nTextureTextHeight;

public:

	//������
	int m_ScrollLeft;

	//������
	int m_ScrollTop;

	//������
	int m_ScrollRight;

	//��������X
	int m_ScrollX;

	//����ʱ��
	int64_t m_ScrollTime;

	//��������
	int m_ScrollStep;

	//����ʱ����(΢��)
	int m_ScrollDistanceTime;
};