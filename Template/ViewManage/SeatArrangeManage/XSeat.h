#pragma once
#include "XConstant.h"

class XSeatArrageManage;
class XPropertyGridFile;
class XPropertyGrid;

class XSeat
{
public:
	XSeat();
	~XSeat();

public:

	constexpr inline void SetManage(XSeatArrageManage* p){m_pManage=p;}

	constexpr inline void SetIndex(int n){m_nIndex=n;}
	constexpr inline int GetIndex(){return m_nIndex;}

	constexpr inline Uint8 GetColorR() { return m_nColorR; }
	constexpr inline Uint8 GetColorG() { return m_nColorG; }
	constexpr inline Uint8 GetColorB() { return m_nColorB; }
	constexpr inline Uint8 GetColorA() { return m_nColorA; }

	constexpr inline void SetSeatRow(int n) { m_nSeatRow=n; }
	constexpr inline int GetSeatRow() { return m_nSeatRow; }
	constexpr inline void SetSeatColumn(int n) { m_nSeatColumn=n; }
	constexpr inline int GteSeatCloumn() { return m_nSeatColumn; }

	inline void SetRect(RECTF rect){m_rect=rect;}
	inline RECTF GetRect(){return m_rect;}

	inline void SetSelected(BOOL b){m_bSelseced=b;}
	inline BOOL GetSelected(){return m_bSelseced;}

	inline void SetGroupName(CString szName){m_szGroupName=szName;}
	inline CString GetGroupName(){return m_szGroupName;}

	//inline void SetSeatShowName(CString szName){m_szShowName=szName;}
	//inline CString GetSeatShowName(){return m_szShowName;}

	inline void SetPhotoName(CString szName){m_szPhotoName=szName;}
	inline CString GetPhotoName(){return m_szPhotoName;}

	inline void SetModel(BOOL b){m_bModel=b;}
	inline BOOL GetModel(){return m_bModel;}

	inline void SetColorA(Uint8 a){m_nColorA=a;}
	void SetColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a);
	CString GetPhotoPath();

public:

	//��������ҳ��
	void SetPropertiesWnd();

public:

	BOOL OnDblClkPropertyGridFile(XPropertyGridFile* pPropertyGridFile);
	//�������Կ�
	void OnClickButtonPropertyGridFile(XPropertyGridFile* pPropertyGridFile);
	//����ֵ�ı�
	void OnPropertyChanged(CMFCPropertyGridProperty* pProperty);
	//˫������
	BOOL OnDblClkPropertyGrid(XPropertyGrid* pPropertyGrid);

private:

	BOOL OpenSelectPhotoFileDialog(CString& szFileName,CString& szFilePath);

private:

	//��ͼ���
	int m_nIndex=0;
	//����
	RECTF m_rect;
	BOOL m_bSelseced=FALSE;

private:

	XSeatArrageManage* m_pManage=NULL;

	CString m_szGroupName=_T("");
	//CString m_szShowName=_T("");

	CString m_szPhotoName=_T("");
	BOOL m_bModel=TRUE;

	Uint8 m_nColorR=91;
	Uint8 m_nColorG=155;
	Uint8 m_nColorB=213;
	Uint8 m_nColorA=255;

	//��
	int m_nSeatRow=0;
	int m_nSeatColumn=0;
};