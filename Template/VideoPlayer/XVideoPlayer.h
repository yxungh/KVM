#pragma once

#include "VideoPlayerConstant.h"

class XMultiVideoWindow;

class XVideoPlayer
{
public:
	XVideoPlayer(void);
	~XVideoPlayer(void);

public:

	static void InitFFMPEG();

public:

	//��ʼ��
	int Init();

	//�������
	void ClearData();

	//����RTSP��ʾ
	void HandleRTSPShow();

	MAP_RTSP& GetMapRTSP();

public:

	//���RTSP
	void AddRTSP(CString szRTSPAddr,int nCount);

	//ɾ��RTSP
	void DeleteRTSP(CString szRTSPAddr);

	void SetRTSPAddrCount(CString szRTSPAddr,int nCount);

	//��ȡRTSP��ַ����״̬
	int GetRTSPConnectState(CString szRTSPAddr);

public:

	//�����Ƿ�Ӳ��
	void SetHardDecode(BOOL bHardDecode);

	//��ȡ�Ƿ�Ӳ����
	BOOL GetHardDecode();

public:

	//���RTSP HWND
	void AddRTSPHWND(HWND h);

	//���RTSP HWND
	void AddRTSPHWND(HWND h,CString szRSTPAddr);

	//����RTSP HWND RTSP��ַ
	void SetRTSPHWNDRTSPAddr(HWND h,CString szRSTPAddr);

	//����RTSP HWND ������ɫ
	void SetRTSPHWNDBGColor(HWND h,Uint8 r,Uint8 g,Uint8 b);

	//ɾ��RTSP HWND
	void DeleteRTSPHWND(HWND h);

	//���MultiVideoWindow
	XMultiVideoWindow* AddMultiVideoWindow(HWND h);

	//���MultiVideoWindow
	XMultiVideoWindow* AddMultiVideoWindow(HWND h,Uint8 g,Uint8 b,Uint8 a);

	//����RTSP HWND�����С
	void AdjustRTSPHWNDSize(HWND h,int nWidth,int nHeight);

	void AdjustMultiVideoWindowSize(XMultiVideoWindow* p,int nWidth,int nHeight);

	//����RTSP HWND����
	void SetRTSPHWNDText(HWND h,CString szText);

	//����RTSP HWND������ɫ
	void SetRTSPHWNDTextColor(HWND h,Uint8 r,Uint8 g,Uint8 b);

	//����RTSP HWND���ִ�С
	void SetRTSPHWNDTextSize(HWND h,int n);

	//����RTSP HWND���ֹ���
	void SetRTSPHWNDTextScrollRect(HWND h,int nLeft,int nTop,int nRight);

	//����RTSP HWND���ֹ���ʱ��Ͳ���
	void SetRTSPHWNDTextScrollTimeAndStep(HWND h,int nDistanceTime,int nStep);

public:

	//��������·��
	void SetFontPath(CString szFontPath);

	//��ȡ����Texture
	void CreateTextureOfText(SDL_Renderer* pRenderer,CString szText,int nTextSize,
							 SDL_Color color,SDL_Texture*& pTexture,int& nWidth,int& nHeight);

	//��ȡ����Surface
	SDL_Surface* CreateSurfaceOfText(CString szText,int nTextSize,SDL_Color color);

public:

	//����RTSP��Ƶ��
	void Display_rtsphwnd();

	//������Ƶǽ
	void Display_multiVideoWindow();

private:

	//��ʼ������
	void InitData();

	//�˳�
	void Quit();

	void ClearMapRTSP();

	void ClearVecRTSPHWND();

	void ClearVecMultiVideoWindow();

	void ClearMapRTSPAddrShowCount();

	//ֹͣ����RTSP����
	void StopAllRTSPRunning();

	//���RTSP��ַ
	void AddRTSPAddr(CString szRTSPAddr,int nCount);

	//���RTSP��ַ��ʾ����
	void AddRTSPAddrShowCount(CString szRTSPAddr);

	//����RTSP��ַ��ʾ����
	void SetRTSPAddrShowCount(CString szRTSPAddr,int n);

	//���RTSP��ַ��ʾ����
	void DeleteRTSPAddrShowCount(CString szRTSPAddr);

	//��ȡRTSPAddr��ʾ����
	unsigned int GetCount(MAP_RTSPADDRSHOWCOUNT& MapCount,CString szRTSPAddr);

	//��ȡRTSP HWND
	XRTSPHWND* GetRTSPHWND(HWND h);

	//ת�����ݵ�UTF8
	void ChangeDataToUTF8(CString szFontPath,char* pUTF8Data);

	//��ʼ���߳�
	BOOL BeginMainThread();

	//ֹͣ���߳�
	void StopMainThread();

	//�ر����߳�Event
	void CloseMainThreadEvent();

private:

	MAP_RTSP m_MapRTSP;

	VEC_RTSPHWND m_VecRTSPHWND;

	VEC_MULTIVIDEOWINDOW m_VecMultiVideoWindow;

public:

	CRITICAL_SECTION m_CSRTSP;

	CRITICAL_SECTION m_CSRTSPHWND;

	CRITICAL_SECTION m_CSRTSPADDRSHOWCOUNT;

	CRITICAL_SECTION m_CSMultiVideoWindow;

	//XVideoPreviewPane* m_PreviewPan;

	HANDLE m_MainThreadEvent;

	BOOL m_Running;

	BOOL m_HardDecode;

	BOOL m_TCP;

	//�����ļ�·��
	char m_FontPath[MAX_PATH];

	//�Ƿ������������ļ�·��
	BOOL m_SetFontPath;
};

