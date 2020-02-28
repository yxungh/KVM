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

	//RTSP��ַ
	CString m_RTSPAddr;

	//��ʾ����
	SDL_Rect m_Rect;

	//��ʾͼ������,����1920*1088����
	RECTF m_RectImage;

	//�Ƿ񴴽�Texture
	BOOL m_CreateTexture;

	SDL_Texture* m_texture;

	int m_textureWidth;

	int m_textureHeight;

	//�Ƿ�������ʵͼ������
	BOOL m_SetRectImageReal;

	//��ʵͼ������
	SDL_Rect m_RectImageReal;

	//��ʾ״̬
	BOOL m_Show;

	//�Ƿ����
	BOOL m_Draw;

public://����

	void SetText(CString text);

	void SetText(COLORREF nTextColor,int nTextSize);

	BOOL GetCreateTextureText();

	void CreateTextureText();

	SDL_Texture* GetTextureText();

	int GetTextureTextWidth();

	int GetTextureTextHeight();

	void ClearTextureText();

private://����

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

private:
	//������ɫ
	SDL_Color m_ColorBG;

	//ѡ��
	BOOL m_bSelected;

	//ͼƬ
	CString m_szPhotoPath;

	BOOL m_bModel;

	//�ڶ�ҳѡ��
	//BOOL m_bSelectedInTwo;
};

