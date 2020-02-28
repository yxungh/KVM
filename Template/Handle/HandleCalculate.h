#pragma once
#include "XConstant.h"

class HandleCalculate
{
private:
	HandleCalculate(void);
	~HandleCalculate(void);

public:

	//������ͼԭ��
	static void SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,
							   CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,CDC& dc);

	//��ȡ��ͼ����ԭ��
	static void GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,
							   CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,int& nOrgX,int& nOrgY);

	//�ж�IP�Ƿ���ȷ
	static BOOL DecideIP(CString szIP);

	//�ж�RTSP��ַ�Ƿ���ȷ
	static BOOL DecideRTSPAddr(CString szRTSPAddr);

	static CString GetIPByRTSPAddr(CString szRTSPAddr);

	//����key��ȡID
	static int GetIDByJsonKey(CString szKey);
	//����key��ȡ���͡����ļ���������Ҫ
	static int GetTypeByJsonKey(CString szKey);
	//��ȡƴ�ӳ�������
	static CString GetSceneNameByJsonKey(CString szKey);

	static CString GetTimeBySecond(time_t time);

	//��ȡ��������
	static void GetRowAndColumnByMatrix(CString szMatrix,int& nRow,int& nColumn);

	//��ȡ������Ϣ
	static void GetMatrixByInfo(CString szInfo,VEC_ARRAGE& VecArrage);

	//����ID��ȡ
	static XNodeGroupInfo* GetNodeInfoByID(MAP_NODEGROUP& MapGroup,int nNodeGroupID,CString& szOldName,BOOL b);
	//����ַ�ת
	static void SplitCString(CString szSrc,std::map<int,HTREEITEM>& Map);


	//��ȡ��������
	static int GetScaleType(int nScale);

	//������־�¼�
	static CString AnalysisEvent(CString szEvent);




};

