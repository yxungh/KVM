#pragma once
#include "XConstant.h"

class XMenuWnd;
class XSeatArrageManage;
//class XSeatDraw;

class XPage
{
public:
	XPage();
	~XPage();

public:

	inline void SetPageWidth(int n){m_nWidth=n;}
	inline int GetPageWidth(){return m_nWidth;}

	inline void SetPageHeight(int n){m_nHeight=n;}
	inline int GetPageHeight(){return m_nHeight;}

	inline void SetPhotoName(CString szPath){m_szPhotoName=szPath;}
	inline CString GetPhotoName(){return m_szPhotoName;}

	inline void SetModel(BOOL b){m_bModel=b;}
	inline BOOL GetModel(){return m_bModel;}

	void SetColor(Uint8 r,Uint8 g,Uint8 b);
	inline Uint8 GetColorR(){return m_nColorR;}
	inline Uint8 GetColorG(){return m_nColorG;}
	inline Uint8 GetColorB(){return m_nColorB;}

	inline void SetRect(RECTF rect){m_rect=rect;}
	inline RECTF GetRect(){return m_rect;}

	inline void SetIndex(int n){m_nIndex=n;}
	inline int GetIndex(){return m_nIndex;}

	inline VEC_SEAT& GetVecSeat(){return m_VecSeat;}
	inline VEC_SCREEN& GetVecScreen(){return m_VecScreen;}

	inline void SetGroupName(CString szName){m_szGroupName=szName;}
	inline CString GetGroupName(){return m_szGroupName;}

	inline XMenuWnd* GetInfoMenu(){return m_pMenuWnd;}
	inline void SetManage(XSeatArrageManage* p){m_pManage=p;}

public:

	void InitScreen(int nRow,int nColumn,int nScreenH,int nScreenV);
	void CreateMenuWnd();

public:

	void ClearVecSeat();
	void ClearVecScreen();

private:
	int m_nIndex=0;

	int m_nWidth=0;
	int m_nHeight=0;

	CString m_szPhotoName=_T("");
	BOOL m_bModel=FALSE;

	Uint8 m_nColorR=0;
	Uint8 m_nColorG=0;
	Uint8 m_nColorB=0;

	RECTF m_rect;

	CString m_szGroupName=_T("");

private:

	//坐席
	VEC_SEAT m_VecSeat;

	//屏幕编排
	VEC_SCREEN m_VecScreen;

	//菜单信息
	static XMenuWnd* m_pMenuWnd;

	XSeatArrageManage* m_pManage=NULL;
};