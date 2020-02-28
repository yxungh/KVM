#pragma once
#include "XConstant.h"


class XMatrixScreen
{
public:
	XMatrixScreen();
	~XMatrixScreen();

public:
	inline void SetIndex(int n){m_nIndex=n;}
	inline int GetIndex(){return m_nIndex;}

	inline void SetRect(RECTF rect){m_rect=rect;}
	inline RECTF GetRect(){return m_rect;}

	inline void SetName(CString szName){m_szName=szName;}
	inline CString GetName(){return m_szName;}

	inline void SetChannel(int n){m_nChannel=n;}
	inline int GetChannel(){return m_nChannel;}

	inline void SetInName(CString szName){m_szInName=szName;}
	inline CString GetInName(){return m_szInName;}

	inline void SetInChannel(int n) { m_nInChannel=n; }
	inline int GetInChannel() { return m_nInChannel; }

	inline void SetReadName(CString szName){m_szReadName=szName;}
	inline CString GetReadName(){return m_szReadName;}

	inline void SetID(int n){m_nID=n;}
	inline int GetID(){return m_nID;}

	inline void SetSwitch(BOOL b){m_bSwitch=b;}
	inline BOOL GetSwitch(){return m_bSwitch;}

private:
	//屏幕序号
	int m_nIndex=0;
	//区域
	RECTF m_rect;
	//节点名称（屏幕）
	CString m_szName=_T("");
	//节点通道
	int m_nChannel=0;
	//输入节点名称
	CString m_szInName=_T("");
	//输入节点通道
	int m_nInChannel=0;
	//真实ID
	CString m_szReadName=_T("");
	//ID
	int m_nID=0;
	//是否切换矩阵
	BOOL m_bSwitch=FALSE;
};

