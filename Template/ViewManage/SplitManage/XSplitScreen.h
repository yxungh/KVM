#pragma once
#include "XConstant.h"


class XSplitScreen
{
public:
	XSplitScreen();
	virtual ~XSplitScreen();

public:
	inline void SetRect(RECTF rect) { m_rect=rect; }
	inline RECTF GetRect() { return m_rect; }

	inline void SetIndex(int n) { m_nIndex=n; }
	inline int GetIndex() { return m_nIndex; }

	//inline void SetScreenName(CString szName){m_szName=szName;}
	//inline CString GetScreenName(){return m_szName;}

	inline void SetSplitCh(int n) { m_nSplitCh=n; }
	inline int GetSplitCh() { return m_nSplitCh; }

	inline void SetLevelUse(int n) { m_nLevelUse=n; }
	inline int GetLevelUse() { return m_nLevelUse; }

	inline void SetPixIndex(int n) { m_nPixIndex=n; }
	inline int GetPixIndex() { return m_nPixIndex; }
	inline void SetRealResulationX(int n) { m_nRealResulationX=n; }
	inline int GetRealResulationX() { return m_nRealResulationX; }
	inline void SetRealResulationY(int n) { m_nRealResulationY=n; }
	inline int GetRealResulationY() { return m_nRealResulationY; }

public:
	//void SetSplitSignalUp(int nSignalID);
	//void SetSplitSignalDown(int nSignalID);
	//void SetSplitSignalTop(int nSignalID);
	//void SetSplitSignalBottom(int nSignalID);
	//void CloseSplitSignal(int nSignalID);

	//XSplitSignal* GetSplitSignalByID(int nID);

	//void ClearVecSplitSignal();

private:

	int m_nIndex=0;
	RECTF m_rect;
	//CString m_szName=_T("");

private:

	//分块信号用于开窗发送信号
	//VEC_SPLITSIGNAL m_VecSplitSignal;

private:
	//拼接通道
	int m_nSplitCh=0;
	//层次占用
	int m_nLevelUse=0;
	//分辨率序号
	int m_nPixIndex;
	//屏幕真实分辨率
	int m_nRealResulationX=0;
	int m_nRealResulationY=0;


};

