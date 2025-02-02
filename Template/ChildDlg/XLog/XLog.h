#pragma once
#include "..\resource.h"
#include "XListCtrl.h"
#include "XConstant.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"

// XLog 对话框
class XDelegateLog;

class XLog: public XBaseDialog
{
	DECLARE_DYNAMIC(XLog)

public:
	XLog(CWnd* pParent=nullptr);   // 标准构造函数
	virtual ~XLog();

	// 对话框数据
	enum { IDD=IDD_DIALOG_LOG };
	virtual BOOL OnInitDialog();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedBtnFront();
	afx_msg void OnBnClickedBtnBack();
	afx_msg void OnNMClickListUser(NMHDR* pNMHDR,LRESULT* pResult);
	afx_msg void OnNMClickListNode(NMHDR* pNMHDR,LRESULT* pResult);
	afx_msg void OnBnClickedBtnRefreash();
	afx_msg void OnBnClickedBtnQueryByUser();
	afx_msg void OnBnClickedBtnQueryByNode();
	afx_msg void OnBnClickedBtnJump();
	afx_msg void OnChangeEditQueryUser();
	afx_msg void OnChangeEditQueryNode();
	DECLARE_MESSAGE_MAP()

public:
	inline void SetDelelgate(XDelegateLog* p) { m_pDelegate=p; }
	inline VEC_LOG& GetVecLog() { return m_VecLog; }

public:


	void OperateOfReLog(const char* pData);

private:
	void Init();
	void InitList();
	void InitData();
	//void InitVecLog();
	void SendDataOfGetLogByData();
	void InsertVecLog();

	void ReloadInterface();
	void ReloadListInterface();

	void ClearVecLog();
	void ClearVecFront();
	void ClearVecBack();
	void ClearVec();
	void ClearData();

	void AddListInfo(CString szName,int nType);
	void SetListInfo(int nCount,CString szInfo,int nType);

	void AddLogListInfo(XLogInfo* pInfo);
	void SetLogListInfo(int nCount,CString szTime,CString szEvent,CString szUser,CString szNode,CString szNote);

	void InsertLogList();

	CString GetNodeNameByRealName(CString szName);

	void SetBtnStatus();

	void SetTotalPage(int nTotalList=0);

	CString GetNoteByEvent(XLogInfo* pInfo);
	CString GetNodeRealNameByName(CString szName);
private:

	XDelegateLog* m_pDelegate=NULL;

	XListCtrl m_ListUser;
	XListCtrl m_ListNode;
	XListCtrl m_ListLog;

	//日志集合
	VEC_LOG m_VecLog;
	VEC_LOG m_vecFront;
	VEC_LOG m_VecBack;

	//记录点击次数
	//int m_nTotalPage=0;
	//查询天数
	int m_nDays=0;
	//返回次数 （二者相等）
	int m_nReciveIndex=0;

	//总条数
	int m_nTotalList=0;

	//点击时间
	DWORD m_dwTime=0;

	//////////////////////////////////////////////////////////////////////////
	XThemeText m_TextGroup1;
	XThemeText m_TextGroup2;
	XThemeText m_TextGroup3;
	XThemeText m_TextUser;
	XThemeText m_TextNode;
	XThemeText m_TextCon;
	XThemeText m_TextPage;
	XThemeText m_TextTotalPage;
	XThemeText m_TextPre;

	XThemeBtn m_BtnRefreash;
	XThemeBtn m_BtnQueryByUser;
	XThemeBtn m_BtnQueryByNode;
	XThemeBtn m_BtnJump;
	XThemeBtn m_BtnBack;
	XThemeBtn m_BtnFront;


};
