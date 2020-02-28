#pragma once

enum STATETYPE
{
	STATETYPE_OPEN,//��״̬
	STATETYPE_CLOSE,//�ر�״̬
	STATETYPE_STOP,//ֹͣ״̬

	STATETYPE_NULL
};

class XVideoPlayer;

class XRTSP
{
public:
	XRTSP(void);
	~XRTSP(void);

public:

	void SetVideoPlayer(XVideoPlayer* p);

	//��ʼ��
	void Init();

	//��
	void Open();

	//ֹͣ
	void Stop();

	//�ر�
	void Close();

	//�������
	void ClearData();

	//���ͼ������
	void ClearFrameYUVData();

	//��������״̬
	void SetRunning(BOOL b);

	CString GetRSTPAddr();

	CString GetRSTPHDAddr();

	CString GetName();

	BOOL GetTF680();

	void SetRSTPAddr(CString s);

	void SetRSTPHDAddr(CString s);

	void SetName(CString s);

	//��ȡ״̬
	STATETYPE GetStateType();

	//����״̬
	void SetStateType(STATETYPE s);

	//�߳�����״̬
	BOOL ThreadRunState();

	//����TCP
	void SetTCP(BOOL b);

	//�������ӳ�ʱʱ��
	void SetConnectTimeOut(int n);

	void SetCount(int n);

	int GetCount();

public:

	void OpenURL();

	void StopOpenThread();

	void CloseOpenThreadEvent();

	void StopDecodeThread();

	void CloseDecodeThreadEvent();

	BOOL StartDecodeThread();

	BOOL StartOpenThread();

public:

	XVideoPlayer* m_VideoPlayer;

	//RTSP��ַ
	CString m_RSTPAddr;

	//RTSP HD��ַ
	CString m_RSTPHDAddr;

	//����
	CString m_Name;

	//RTSP��ַ
	char m_cRSTPAddr[MAX_PATH];

	HANDLE m_OpenThreadEvent;

	volatile BOOL m_bOpenThread;

	AVCodecContext* m_codec_ctx;

	AVCodec* m_codec;

	struct SwsContext * m_sws_ctx;

	AVFrame* m_frame;

	AVFrame* m_frame_yuv;

	int m_frame_yuv_Width;

	int m_frame_yuv_Height;

	uint8_t* m_out_buffer;

	HANDLE m_DecodeThreadEvent;

	volatile BOOL m_bDecodeThread;

	int m_video_index;

	int64_t m_pts;

	AVFormatContext* m_fmt_ctx;

	int64_t m_seek_to_msec;

	BOOL m_is_file;

	int64_t m_wait_time;

	volatile BOOL m_Running;

	STATETYPE m_StateType;

	BOOL m_RecvFlagKey;

	//�Ƿ����sws_scale����
	BOOL m_SwsScale;

	CRITICAL_SECTION m_CSFrameYUV;

	BOOL m_TCP;

	int m_ConnectTimeOut;

	int m_nCount;
};

