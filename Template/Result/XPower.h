#pragma once
#include "XResult.h"
#include "XConstant.h"


class XPrivilegeViewBase
{
public:

	XPrivilegeViewBase(){m_nType=0;}

	inline void SetType(int n){m_nType=n;}
	inline int GetType(){return m_nType;}

	inline void SetVecPrivilege(VEC_PRIVILEGE& Vec) { m_VecPrivilege=Vec; }
	inline VEC_PRIVILEGE& GetVecPrivilege() { return m_VecPrivilege; }

private:

	int m_nType;
	VEC_PRIVILEGE m_VecPrivilege;
};

class XPrivilegeView:public XPrivilegeViewBase{};
class XPrivilegeLogin:public XPrivilegeViewBase{};
class XPrivilegeCtrl:public XPrivilegeViewBase{};

class XPower:public XResult
{
public:
	XPower();
	~XPower();

public:

	inline void SetType(CString type){m_szType=type;}
	inline CString GetType(){return m_szType;}

	inline void SetUserID(int n){m_nUserID=n;}
	inline int GetUserID(){return m_nUserID;}

	//inline void SetUserName(CString szUserName){m_szUserName=szUserName;}
	//inline CString GetUserName(){return m_szUserName;}

	//inline void SetPassWd(CString szPassWd){m_szPassWd=szPassWd;}
	//inline CString GetPassWd(){return m_szPassWd;}

	void SetUserName(CString szUserName);
	CString GetUserName();

	void SetPassWd(CString szPassWd);
	CString GetPassWd();

	inline void SetCreateID(int n){m_nCreateID=n;}
	inline int GetCreateID(){return m_nCreateID;}

	inline void SetCreateTime(time_t t){m_tCreateTime=t;}
	inline time_t GetCreateTime(){return m_tCreateTime;}

	inline void SetUserGroup(CString szGroup){m_szUserGroup=szGroup;}
	inline CString GetUserGroup(){return m_szUserGroup;}

	inline void SetLevel(int n){m_nLevel=n;}
	inline int GetLevel(){return m_nLevel;}

	inline void SetManagePermission(unsigned int n){m_nManagePermission=n;}
	inline unsigned int GetManagePermission(){return m_nManagePermission;}

	inline XPrivilegeView& GetPrivilegeView(){return m_PrivilegeView;}
	inline XPrivilegeCtrl& GetPrivilegeCtrl(){return m_PrivilegeCtrl;}
	inline XPrivilegeLogin& GetPrivilegeLogin(){return m_PrivilegeLogin;}

private:
	CString m_szType=_T("");
	int m_nUserID=0;
	CString m_szUserName=_T("");
	CString m_szPassWd=_T("");
	int m_nCreateID=0;
	time_t m_tCreateTime=0;
	CString m_szUserGroup=_T("");
	int m_nLevel=0;;
	unsigned int m_nManagePermission=0;

	XPrivilegeView m_PrivilegeView;
	XPrivilegeCtrl m_PrivilegeCtrl;
	XPrivilegeLogin m_PrivilegeLogin;
};