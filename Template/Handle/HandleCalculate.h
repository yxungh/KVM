#pragma once
#include "XConstant.h"

class HandleCalculate
{
private:
	HandleCalculate(void);
	~HandleCalculate(void);

public:

	//设置视图原点
	static void SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,
							   CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,CDC& dc);

	//获取视图坐标原点
	static void GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,
							   CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,int& nOrgX,int& nOrgY);

	//判断IP是否正确
	static BOOL DecideIP(CString szIP);

	//判断RTSP地址是否正确
	static BOOL DecideRTSPAddr(CString szRTSPAddr);

	static CString GetIPByRTSPAddr(CString szRTSPAddr);

	//根据key获取ID
	static int GetIDByJsonKey(CString szKey);
	//根据key获取类型。仅文件夹类型需要
	static int GetTypeByJsonKey(CString szKey);
	//获取拼接场景名称
	static CString GetSceneNameByJsonKey(CString szKey);

	static CString GetTimeBySecond(time_t time);

	//获取排列行列
	static void GetRowAndColumnByMatrix(CString szMatrix,int& nRow,int& nColumn);

	//获取排列信息
	static void GetMatrixByInfo(CString szInfo,VEC_ARRAGE& VecArrage);

	//根据ID获取
	static XNodeGroupInfo* GetNodeInfoByID(MAP_NODEGROUP& MapGroup,int nNodeGroupID,CString& szOldName,BOOL b);
	//拆分字符转
	static void SplitCString(CString szSrc,std::map<int,HTREEITEM>& Map);


	//获取放缩类型
	static int GetScaleType(int nScale);

	//解析日志事件
	static CString AnalysisEvent(CString szEvent);




};

