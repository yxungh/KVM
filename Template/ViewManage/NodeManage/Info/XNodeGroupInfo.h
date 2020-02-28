#pragma once
#include "XConstant.h"

class XNodeGroupInfo
{
public:
	XNodeGroupInfo();
	~XNodeGroupInfo();

public:



	inline void SetGroupID(int n){m_nGroupID=n;}
	inline int GetGroupID(){return m_nGroupID;}

	inline void SetGroupName(CString szName){m_szGroupName=szName;}
	inline CString GetGroupName(){return m_szGroupName;}

	inline void SetOnLine(BOOL b){m_bOnLine=b;}
	inline BOOL GetOnLine(){return m_bOnLine;}

	inline void SetType(int n){m_nType=n;}
	inline int GetType(){return m_nType;}

	inline void SetMaster(int n){m_nMaster=n;}
	inline int GetMaster(){return m_nMaster;}

	inline void SetMatrixRow(int n){m_nMatrixRow=n;}
	inline int GetMatrixRow(){return m_nMatrixRow;}

	inline void SetMatrixColumn(int n){m_nMatrixColumn=n;}
	inline int GetMatrixColumn(){return m_nMatrixColumn;}

	inline void SetCreatorID(int n){m_nCreatorID=n;}
	inline int GetCreatorID(){return m_nCreatorID;}

	inline void SetCreateTime(time_t time){m_tCreateTime=time;}
	inline time_t GetCreateTime(){return m_tCreateTime;}

	inline VEC_ARRAGE& GetVecArrage(){return m_VecArrage;}

	inline void SetGroupItem(HTREEITEM hItem){m_hGroupItem=hItem;}
	inline HTREEITEM GetGroupItem(){return m_hGroupItem;}

	inline void SetArray(CString szArray){m_szArray=szArray;}
	inline CString GetArray(){return m_szArray;}

	inline void SetMatrix(CString szMatrix){m_szMatrix=szMatrix;}
	inline CString GetMatrix(){return m_szMatrix;}

	inline void SetCreateMode(int n){m_nCreateMode=n;}
	inline int GetCreateMode(){return m_nCreateMode;}

	inline void SetMainSecond(BOOL b){m_bMainSecond=b;}
	inline BOOL GetMainSecond(){return m_bMainSecond;}

public:

	void SetProprityWnd();

	//属性值改变
	void OnPropertyChanged(CMFCPropertyGridProperty* pProperty);

private:

	void SetNodeGroupInfo();
	void SetMainSecondGroupInfo();
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

private:

	int m_nGroupID=0;
	CString m_szGroupName=_T("");
	BOOL m_bOnLine=FALSE;
	int m_nType=0;
	int m_nMaster=0;
	int m_nMatrixRow=0;
	int m_nMatrixColumn=0;
	CString m_szArray=_T("");
	CString m_szMatrix=_T("");

	int m_nCreatorID=0;

	time_t m_tCreateTime=0;
	VEC_ARRAGE m_VecArrage;
	HTREEITEM m_hGroupItem;

	int m_nCreateMode=0;
	//是否为主副屏
	BOOL m_bMainSecond=FALSE;
};