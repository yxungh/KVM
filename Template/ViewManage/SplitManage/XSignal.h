#pragma once
#include "XConstant.h"
#include "HandlePath.h"

class XSignal
{
public:
	XSignal();
	virtual ~XSignal();


public:
	inline void SetRect(RECTF rect){m_rect=rect;}
	inline RECTF GetRect(){return m_rect;}

	inline void SetMainRect(RECTF rect){m_RectMin=rect;}
	inline RECTF GetMainRect(){return m_RectMin;}

	inline void SetSignalID(int n){m_nSignalID=n;}
	inline int GetSignalID(){return m_nSignalID;}

	inline void SetSignalName(CString szName){m_szName=szName;}
	inline CString GetSignalName(){return m_szName;}

	inline void SetColor(Color c){m_Color=c;}
	inline Color GetColor(){return m_Color;}

	inline void SetInputCh(int n){m_nInputCh=n;}
	inline int GetInputCh(){return m_nInputCh;}

	inline void SetCutUse(int n){m_nCutUse=n;}
	inline int GetCutUse(){return m_nCutUse;}

	inline std::vector<int>& GetVecCutPix(){return m_VecCutPix;}

	inline void SetLevel(int n){m_nLevel=n;}
	inline int GetLevel(){return m_nLevel;}

	inline void SetRealRect(RECTF rect){m_RealRect=rect;}
	inline RECTF GetRealRect(){return m_RealRect;}

	inline void SetClosePng(CString szPng){m_szClose=szPng;}
	inline CString GetClosePng(){return m_szClose;}

	inline void SetMaxPng(CString szPng) { m_szMax=szPng; }
	inline CString GetMaxPng() { return m_szMax; }

	inline void SetMinPng(CString szPng) { m_szMin=szPng; }
	inline CString GetMinPng() { return m_szMin; }

	inline void SetFullPng(CString szPng) { m_szFull=szPng; }
	inline CString GetFullPng() { return m_szFull; }

public:
	RECTF GetRectUP();
	RECTF GetRectDown();
	RECTF GetRectColse();
	RECTF GetRectMenu();
	RECTF GetRectMax();
	RECTF GetRectMin();
	RECTF GetRectFull();

private:
	int m_nSignalID=0;
	RECTF m_rect;
	CString m_szName=_T("");
	Color m_Color;

	//获取信息
	int m_nInputCh=0;
	int m_nCutUse=0;
	std::vector<int> m_VecCutPix;
	int m_nLevel=0;
	RECTF m_RealRect;
	//原来大小
	RECTF m_RectMin;

	//图标
	CString m_szClose=HandlePath::GetSignalPhoto(_T("close.png"));
	CString m_szMax=HandlePath::GetSignalPhoto(_T("max.png"));
	CString m_szMin=HandlePath::GetSignalPhoto(_T("min.png"));
	CString m_szFull=HandlePath::GetSignalPhoto(_T("full.png"));
};

