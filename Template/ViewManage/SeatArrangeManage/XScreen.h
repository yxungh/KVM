#pragma once
#include "XConstant.h"


class XScreen
{
public:
	XScreen();
	~XScreen();

public:

	constexpr inline void SetSeatIndex(int n){m_nSeatIndex=n;}
	constexpr inline int GetSeatIndex(){return m_nSeatIndex;}

	inline void SetRect(RECTF rect){m_rect=rect;}
	inline RECTF GetRect(){return m_rect;}

	inline void SetRTSPAddr(CString szRTSPAddr){m_szRTSPAddr=szRTSPAddr;}
	inline CString GetRTSPAddr(){return m_szRTSPAddr;}

	constexpr inline void SetRowIndex(int n){m_nRowIndex=n;}
	constexpr inline int GetRowIndex(){return m_nRowIndex;}

	constexpr inline void SetColumnIndex(int n){m_nColumnIndex=n;}
	constexpr inline int GetColumnIndex(){return m_nColumnIndex;}

	constexpr inline void SetHas(BOOL b){m_bHas=b;}
	constexpr inline BOOL GetHas(){return m_bHas;}

	constexpr inline void SetMaster(BOOL b){m_bMaster=b;}
	constexpr inline BOOL GetMaster(){return m_bMaster;}

	constexpr inline void SetNodeID(int n){m_nNodeID=n;}
	constexpr inline int GetNodeID(){return m_nNodeID;}

	constexpr inline void SetSelected(BOOL b){m_bSelected=b;}
	constexpr inline BOOL GetSelected(){return m_bSelected;}

private:

	//ÆÁÄ»±àÅÅËùÊô×øÏ¯
	int m_nSeatIndex=0;

	RECTF m_rect;

	CString m_szRTSPAddr=_T("");

	int m_nRowIndex=0;
	int m_nColumnIndex=0;

	BOOL m_bHas=FALSE;
	BOOL m_bMaster=FALSE;

	int m_nNodeID=0;
	BOOL m_bSelected=FALSE;
};