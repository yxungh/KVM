// XLog.cpp: 实现文件
//

#include "stdafx.h"
#include "XLog.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XSetListCtrl.h"
#include "XDelegateLog.h"
#include "XPower.h"
#include "XNode.h"
#include "XLogInfo.h"
#include "XSendDataManage.h"
#include "XLogPack.h"
#include "XJsonManage.h"
#include <algorithm>
#include "HandleCalculate.h"
#include "XMessageBox.h"

#define SECONDONEDAY  86400

// XLog 对话框

IMPLEMENT_DYNAMIC(XLog, XBaseDialog)

XLog::XLog(CWnd* pParent /*=nullptr*/)
	: XBaseDialog(XLog::IDD, pParent)
{

}

XLog::~XLog()
{
	ClearVec();
}

void XLog::ClearVecFront()
{
	for(auto& vec:m_vecFront)
	{
		delete vec;
	}
	m_vecFront.clear();
}

void XLog::ClearVecBack()
{
	for(auto& vec:m_VecBack)
	{
		delete vec;
	}
	m_VecBack.clear();
}

void XLog::ClearVecLog()
{
	for(auto& vec:m_VecLog)
	{
		delete vec;
	}
	m_VecLog.clear();
}

void XLog::ClearVec()
{
	ClearVecLog();
	ClearVecFront();
	ClearVecBack();
}

void XLog::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_USER,m_ListUser);
	DDX_Control(pDX,IDC_LIST_NODE,m_ListNode);
	DDX_Control(pDX,IDC_LIST_LOGVIEW,m_ListLog);
	DDX_Control(pDX,IDC_STATIC_GROUP1,m_TextGroup1);
	DDX_Control(pDX,IDC_STATIC_GROUP2,m_TextGroup2);
	DDX_Control(pDX,IDC_STATIC_GROUP3,m_TextGroup3);
	DDX_Control(pDX,IDC_STATIC_QUERYUSER,m_TextUser);
	DDX_Control(pDX,IDC_STATIC_QUERYNODE,m_TextNode);
	DDX_Control(pDX,IDC_STATIC_CONN,m_TextCon);
	DDX_Control(pDX,IDC_STATIC_PAGE,m_TextPage);
	DDX_Control(pDX,IDC_STATIC_PER,m_TextPre);
	DDX_Control(pDX,IDC_STATIC_TOTALPAGE,m_TextTotalPage);
	DDX_Control(pDX,IDC_BTN_REFREASH,m_BtnRefreash);
	DDX_Control(pDX,IDC_BTN_QUERYBYUSER,m_BtnQueryByUser);
	DDX_Control(pDX,IDC_BTN_QUERYBYNODE,m_BtnQueryByNode);
	DDX_Control(pDX,IDC_BTN_JUMP,m_BtnJump);
	DDX_Control(pDX,IDC_BTN_BACK,m_BtnBack);
	DDX_Control(pDX,IDC_BTN_FRONT,m_BtnFront);
}


BEGIN_MESSAGE_MAP(XLog, XBaseDialog)
	ON_BN_CLICKED(IDC_BTN_FRONT,OnBnClickedBtnFront)
	ON_BN_CLICKED(IDC_BTN_BACK,OnBnClickedBtnBack)
	ON_NOTIFY(NM_CLICK,IDC_LIST_USER,OnNMClickListUser)
	ON_NOTIFY(NM_CLICK,IDC_LIST_NODE,OnNMClickListNode)
	ON_BN_CLICKED(IDC_BTN_REFREASH,OnBnClickedBtnRefreash)
	ON_BN_CLICKED(IDC_BTN_QUERYBYUSER,OnBnClickedBtnQueryByUser)
	ON_BN_CLICKED(IDC_BTN_QUERYBYNODE,OnBnClickedBtnQueryByNode)
	ON_BN_CLICKED(IDC_BTN_JUMP,OnBnClickedBtnJump)
	ON_EN_CHANGE(IDC_EDIT_QUERYUSER,OnChangeEditQueryUser)
	ON_EN_CHANGE(IDC_EDIT_QUERYNODE,OnChangeEditQueryNode)
END_MESSAGE_MAP()


// XLog 消息处理程序
BOOL XLog::OnInitDialog()
{
	XBaseDialog::OnInitDialog();
	Init();
	return TRUE;
}

void XLog::Init()
{
	InitList();
	InitData();
	
	//InitVecLog();
	SendDataOfGetLogByData();
	ReloadInterface();
}

void XLog::InitList()
{
	XSetListCtrl::InitList(&m_ListUser,1,FALSE);
	m_ListUser.EnableToolTips(TRUE);
	//////////////////////////////////////////////////////////////////////////
	XSetListCtrl::InitList(&m_ListNode,1,FALSE);
	m_ListNode.EnableToolTips(TRUE);
	//////////////////////////////////////////////////////////////////////////
	XSetListCtrl::InitList(&m_ListLog,5,FALSE);
	m_ListLog.EnableToolTips(TRUE);
}

void XLog::InitData()
{
	//初始化用户表
	MAP_POWER& MapPower=m_pDelegate->GetMapPower();
	for(auto& map:MapPower)
	{
		XPower* pPower=map.second;
		CString szUserName=map.first;
		AddListInfo(szUserName,1);
		//TRACE(_T("UserName=%s\n"),szUserName);
	}
	//////////////////////////////////////////////////////////////////////////
	//初始化节点
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	for(auto& map:MapNode)
	{
		XNode* pNode=map.second;
		CString szNodeName=pNode->GetNodeName();
		AddListInfo(szNodeName,2);
	}
}

void XLog::AddListInfo(CString szName,int nType)
{
	if(nType==1)
	{
		int nCount=m_ListUser.GetItemCount();
		if(nCount>23)
			m_ListUser.SetColumnWidth(0,140);		
		else
			m_ListUser.SetColumnWidth(0,156);

		m_ListUser.InsertItem(nCount,_T(""));
		SetListInfo(nCount,szName,nType);
	}
	else if(nType==2)
	{
		int nCount=m_ListNode.GetItemCount();
		if(nCount>23)
			m_ListNode.SetColumnWidth(0,140);
		else
			m_ListNode.SetColumnWidth(0,156);
		
		m_ListNode.InsertItem(nCount,_T(""));
		SetListInfo(nCount,szName,nType);
	}	
}

void XLog::SetListInfo(int nCount,CString szInfo,int nType)
{
	if(nType==1)
	{
		m_ListUser.SetItemText(nCount,0,szInfo);
	}
	else if(nType==2)
	{
		m_ListNode.SetItemText(nCount,0,szInfo);
	}
}

void XLog::ReloadInterface()
{
	SetWindowText(_C(_T("251"),_T("日志")));
	m_TextGroup1.SetText(_C(_T("258"),_T("用户列表")),TRUE);
	m_TextGroup2.SetText(_C(_T("259"),_T("节点列表")),TRUE);
	m_TextGroup3.SetText(_C(_T("260"),_T("日志列表")),TRUE);
	m_TextUser.SetText(_C(_T("261"),_T("查找用户"))+_T(":"));
	m_TextNode.SetText(_C(_T("262"),_T("查找节点"))+_T(":"));
	m_TextCon.SetText(_T("--"),TRUE);
	m_TextPre.SetText(_T("/"));

	m_BtnRefreash.SetCaption(_C(_T("263"),_T("刷新")));
	m_BtnQueryByUser.SetCaption(_C(_T("264"),_T("按用户查找")));
	m_BtnQueryByNode.SetCaption(_C(_T("265"),_T("按节点查找")));
	m_BtnJump.SetCaption(_C(_T("310"),_T("跳页")));
	m_BtnBack.SetCaption(_T("<"));
	m_BtnFront.SetCaption(_T(">"));

	ReloadListInterface();
}

void XLog::ReloadListInterface()
{
	CString szTemp=_T("");

	LVCOLUMN col;
	col.mask=LVCF_TEXT;

	szTemp=_C(_T("231"),_T("用户列表"));
	col.pszText=szTemp.GetBuffer();
	m_ListUser.SetColumn(0,&col);
	szTemp.ReleaseBuffer();
	//////////////////////////////////////////////////////////////////////////
	szTemp=_C(_T("226"),_T("节点列表"));
	col.pszText=szTemp.GetBuffer();
	m_ListNode.SetColumn(0,&col);
	szTemp.ReleaseBuffer();
	//////////////////////////////////////////////////////////////////////////
	szTemp=_C(_T("255"),_T("日期"));
	col.pszText=szTemp.GetBuffer();
	m_ListLog.SetColumn(0,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("256"),_T("事件"));
	col.pszText=szTemp.GetBuffer();
	m_ListLog.SetColumn(1,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("68"),_T("用户"));
	col.pszText=szTemp.GetBuffer();
	m_ListLog.SetColumn(2,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("95"),_T("节点"));
	col.pszText=szTemp.GetBuffer();
	m_ListLog.SetColumn(3,&col);
	szTemp.ReleaseBuffer();

	szTemp=_C(_T("257"),_T("详细"));
	col.pszText=szTemp.GetBuffer();
	m_ListLog.SetColumn(4,&col);
	szTemp.ReleaseBuffer();
}

void XLog::SendDataOfGetLogByData()
{
	//默认获取当天全部日志
	CTime t=CTime::GetCurrentTime();
	time_t time=t.GetTime();

	XLogPack logPack;
	logPack.m_time=time;

	ClearData();
	XSendDataManage::GetInstance()->AddSendDataOfGetLogByData(logPack);
}

BOOL compare(XLogInfo* pInfo1,XLogInfo* pInfo2)
{
	if(pInfo1->m_Time>pInfo2->m_Time)
		return TRUE;
	else
		return FALSE;
}

void XLog::OperateOfReLog(const char* pData)
{
	m_nReciveIndex++;
	XLogPack logPack;
	//先装在vecback里面
	XJsonManage::GetInstance()->ParseJsonToLog(pData,m_VecBack,logPack);
	m_nTotalList+=logPack.m_nCount;

	//TRACE(_T("TotalList=%d\n"),m_nTotalList);

	//最后一次才执行
	if(m_nDays==m_nReciveIndex||m_nDays==0)
	{
		//根据时间排序
		sort(m_VecBack.begin(),m_VecBack.end(),compare);
		//先设置总页数
		SetTotalPage(m_nTotalList);
		//把前面23个装在veclog里面显示 只执行一次
		InsertVecLog();
		//显示
		InsertLogList();
		SetBtnStatus();
		m_nReciveIndex=0;
		m_nTotalList=0;
	}
}

void XLog::InsertLogList()
{
	m_ListLog.DeleteAllItems();

	int nSize=m_VecLog.size();
	if(nSize==0)
		return;

	for(auto& Log:m_VecLog)
	{
		XLogInfo* pInfo=Log;
		AddLogListInfo(pInfo);
	}
}

void XLog::AddLogListInfo(XLogInfo* pInfo)
{
	int nCount=m_ListLog.GetItemCount();
	if(nCount>23)
	{
		m_ListLog.SetColumnWidth(0,122);
		m_ListLog.SetColumnWidth(1,95);
		m_ListLog.SetColumnWidth(2,70);
		m_ListLog.SetColumnWidth(3,85);
		m_ListLog.SetColumnWidth(4,180);
	}
	else
	{
		m_ListLog.SetColumnWidth(0,122);
		m_ListLog.SetColumnWidth(1,95);
		m_ListLog.SetColumnWidth(2,70);
		m_ListLog.SetColumnWidth(3,85);
		m_ListLog.SetColumnWidth(4,196);
	}
	m_ListLog.InsertItem(nCount,_T(""));

	struct tm t;
	localtime_s(&t,&pInfo->m_Time);
	CString szTime;
	szTime.Format(_T("%4d/%02d/%02d %02d:%02d:%02d"),t.tm_year+1900,t.tm_mon+1,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);

	CString szEvent=HandleCalculate::AnalysisEvent(pInfo->m_szEvent);
	CString szNodeName=GetNodeNameByRealName(pInfo->m_szTermID);
	//根据事件获取详细信息
	CString szNote=GetNoteByEvent(pInfo);

	SetLogListInfo(nCount,
				   szTime,
				   szEvent,
				   pInfo->m_szUser,
				   szNodeName,
				   szNote);
}

void XLog::SetLogListInfo(int nCount,CString szTime,CString szEvent,CString szUser,CString szNode,CString szNote)
{
	m_ListLog.SetItemText(nCount,0,szTime);
	m_ListLog.SetItemText(nCount,1,szEvent);
	m_ListLog.SetItemText(nCount,2,szUser);
	m_ListLog.SetItemText(nCount,3,szNode);
	m_ListLog.SetItemText(nCount,4,szNote);
}

CString XLog::GetNoteByEvent(XLogInfo* pInfo)
{
	//根据事件获取详细解释
	CString szNote=_T("");
	if(pInfo->m_szEvent==EVENT_USER_LOGIN||pInfo->m_szEvent==EVENT_USER_LOGOUT)
	{
		//ok
		szNote.Format(_T("IP:%s"),pInfo->m_szIpAddr);
	}
	else if(pInfo->m_szEvent==EVENT_TERM_LOGIN||pInfo->m_szEvent==EVENT_TERM_LOGOUT)
	{
		//TRACE(_T("EVENT_TERM_LOGIN"));
	}
	else if(pInfo->m_szEvent==EVENT_CTRL||pInfo->m_szEvent==EVENT_REMOVE_CTRL)
	{
		CString szCtrlName=GetNodeNameByRealName(pInfo->m_szTermID);
		CString szTargetCtrlName=GetNodeNameByRealName(pInfo->m_szTargetTermID);

		if(szCtrlName!=_T("")&&szTargetCtrlName!=_T(""))
			szNote.Format(_T("(%s)%s(%s)"),szCtrlName,_C(_T("69"),_T("接管")),szTargetCtrlName);
		else
			szNote=_T("");
	}
	else if(pInfo->m_szEvent==EVENT_TERM_CONNECT||pInfo->m_szEvent==EVENT_TERM_DISCON)
	{
		//ok
		szNote.Format(_T("%s:%d"),_C(_T("185"),_T("通道")),pInfo->m_nTermCh);
	}
	else if(pInfo->m_szEvent==EVENT_VIEW||pInfo->m_szEvent==EVENT_REMOVE_VIEW)
	{
		CString szCtrlName=GetNodeNameByRealName(pInfo->m_szTermID);
		CString szTargetCtrlName=GetNodeNameByRealName(pInfo->m_szTargetTermID);

		if(szCtrlName!=_T("")&&szTargetCtrlName!=_T(""))
			szNote.Format(_T("(%s)%s(%s)"),szCtrlName,_C(_T("86"),_T("预览")),szTargetCtrlName);
		else
			szNote=_T("");
	}
	else if(pInfo->m_szEvent==EVENT_MATRIX_EVENT)
	{
		TRACE(_T("EVENT_MATRIX_EVENT"));
	}
	else if(pInfo->m_szEvent==EVENT_CREATE_USER)	
	{
		//TRACE(_T("EVENT_CREATE_USER"));
		szNote.Format(_T("%s:%s"),_C(_T("44"),_T("添加用户")),pInfo->m_szTargetUser);
	}
	else if(pInfo->m_szEvent==EVENT_DELETE_USER)
	{
		TRACE(_T("EVENT_DELETE_USER"));
	}
	else if(pInfo->m_szEvent==EVENT_MODIFY_USER)
	{
		//TRACE(_T("EVENT_MODIFY_USER"));
		szNote.Format(_T("%s:%s"),_C(_T("118"),_T("修改用户")),pInfo->m_szTargetUser);
	}
	else if(pInfo->m_szEvent==EVENT_PUSH)
	{

	}
	else if(pInfo->m_szEvent==EVENT_TERM_SET_ID)
	{
		TRACE(_T("EVENT_DELETE_USER"));
	}
	else if(pInfo->m_szEvent==EVENT_TERM_RENAME)
	{
		//TRACE(_T("rename\n"));
		szNote.Format(_T("%s:%s"),_C(_T("268"),_T("节点名称更改为")),pInfo->m_szNote);
	}
	else if(pInfo->m_szEvent==EVENT_TERM_CREATE||pInfo->m_szEvent==EVENT_TERM_DELETE||
			pInfo->m_szEvent==EVENT_TERM_MODIFY)
	{
		TRACE(_T("EVENT_TERM_CREATE"));
	}
	else
	{
		szNote=pInfo->m_szNote;
	}
	return szNote;
}

CString XLog::GetNodeNameByRealName(CString szName)
{
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	for(auto& node:MapNode)
	{
		XNode* pNode=node.second;
		if(pNode->GetRealID()==szName)
			return pNode->GetNodeName();
	}
	return _T("");
}

void XLog::InsertVecLog()
{
	//读回来先装23个
	int nSize=m_VecBack.size();
	if(nSize==0)
		return;

	for(int i=0;i<PAGELISTCOUNT;i++)
	{
		if(i<nSize)
		{
			XLogInfo* pLogBack=m_VecBack.front();
			m_VecLog.push_back(pLogBack);
			m_VecBack.erase(m_VecBack.begin());
		}
	}
}

void XLog::OnBnClickedBtnFront()
{
	int nBackSize=m_VecBack.size();
	if(nBackSize==0)
		return;
	int nSize=m_VecLog.size();
	if(nSize==0)
		return;
	//保存当前显示log
	for(int i=0;i<PAGELISTCOUNT;i++)
	{
		if(i<nSize)
		{
			XLogInfo* pInfo=m_VecLog.front();
			m_vecFront.push_back(pInfo);
			m_VecLog.erase(m_VecLog.begin());
		}
	}

	//设置新的
	for(int i=0;i<PAGELISTCOUNT;i++)
	{
		if(i<nBackSize)
		{
			XLogInfo* pLogBack=m_VecBack.front();
			m_VecLog.push_back(pLogBack);
			m_VecBack.erase(m_VecBack.begin());
		}
	}

	//显示 只显示veclog
	InsertLogList();
	//更新按钮
	SetBtnStatus();
}

void XLog::OnBnClickedBtnBack()
{
	int nFrontSize=m_vecFront.size();
	if(nFrontSize==0)
		return;

	int nSize=m_VecLog.size();
	if(nSize==0)
		return;

	for(int i=0;i<PAGELISTCOUNT;i++)
	{
		if(i<nSize)
		{
			XLogInfo* pInfo=m_VecLog.back();
			//m_VecBack.push_back(pInfo);

			m_VecBack.insert(m_VecBack.begin(),pInfo);

			m_VecLog.pop_back();
		}
	}

	for(int i=0;i<PAGELISTCOUNT;i++)
	{
		if(i<nFrontSize)
		{
			XLogInfo* pInfo=m_vecFront.back();
			//m_VecLog.push_back(pInfo);

			m_VecLog.insert(m_VecLog.begin(),pInfo);
			m_vecFront.pop_back();
		}
	}

	//显示 只显示veclog
	InsertLogList();
	//更新按钮
	SetBtnStatus();
}

void XLog::SetBtnStatus()
{
	//页数
	int nFrontSize=m_vecFront.size();
	int nSize=m_VecLog.size();
	int nBackSize=m_VecBack.size();

	//TRACE(_T("FrontCount=%d\n"),m_vecFront.size());

	CString szPage;
	szPage.Format(_T("%d"),(nFrontSize/PAGELISTCOUNT)+1);
	GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(szPage);
	m_TextPage.SetText(szPage);

	if(nFrontSize==0&&nBackSize!=0)
	{
		GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FRONT)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_JUMP)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT_JUMP)->EnableWindow(TRUE);
	}
	else if(nFrontSize!=0&&nBackSize==0)
	{
		GetDlgItem(IDC_BTN_BACK)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_FRONT)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_JUMP)->EnableWindow(FALSE);
		//GetDlgItem(IDC_EDIT_JUMP)->EnableWindow(FALSE);
	}
	else if(nFrontSize==0&&nBackSize==0)
	{
		GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FRONT)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_JUMP)->EnableWindow(FALSE);
		//GetDlgItem(IDC_EDIT_JUMP)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_BACK)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_FRONT)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_JUMP)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT_JUMP)->EnableWindow(TRUE);
	}
}

void XLog::SetTotalPage(int nTotalList)
{
	//如果没查到显示1/1页，共一页，没有项
	//int nSize=m_VecBack.size();
	int nSize=0;
	if(nTotalList==0)
		nSize=1;
	else
		nSize=(nTotalList%PAGELISTCOUNT)==0?(nTotalList/PAGELISTCOUNT):(nTotalList/PAGELISTCOUNT)+1;
	//m_nTotalPage=nSize;
	//nSize+=1;

	CString szTotalPage;
	szTotalPage.Format(_T("%d"),nSize);
	GetDlgItem(IDC_STATIC_TOTALPAGE)->SetWindowText(szTotalPage);
	m_TextTotalPage.SetText(szTotalPage,FALSE);
}

void XLog::OnNMClickListUser(NMHDR* pNMHDR,LRESULT* pResult)
{
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW*)pNMHDR;
	int nItem=pNMListView->iItem;
	POSITION pos=m_ListUser.GetFirstSelectedItemPosition();
	int nPos=m_ListUser.GetNextSelectedItem(pos);
	if(nItem>=0&&nItem<m_ListUser.GetItemCount())
	{
		CString szText=m_ListUser.GetItemText(nItem,0);
		GetDlgItem(IDC_EDIT_QUERYUSER)->SetWindowText(szText);
	}
	*pResult=0;
}

void XLog::OnNMClickListNode(NMHDR* pNMHDR,LRESULT* pResult)
{
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW*)pNMHDR;
	int nItem=pNMListView->iItem;
	POSITION pos=m_ListNode.GetFirstSelectedItemPosition();
	int nPos=m_ListNode.GetNextSelectedItem(pos);
	if(nItem>=0&&nItem<m_ListNode.GetItemCount())
	{
		CString szText=m_ListNode.GetItemText(nItem,0);
		GetDlgItem(IDC_EDIT_QUERYNODE)->SetWindowText(szText);
	}
	*pResult=0;
}

void XLog::OnBnClickedBtnRefreash()
{
	DWORD dwTime=GetTickCount();
	if((long)dwTime-(long)m_dwTime<3000)
	{
		return;
	}
	m_dwTime=GetTickCount();

	//TRACE(_T("time=%d\n"),m_dwTime);
	//刷新按日期查找
	SYSTEMTIME time_begin={0};
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIME_BEGIN))->GetTime(&time_begin);
	CTime timeBegin=time_begin;

	SYSTEMTIME time_end={0};
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIME_END))->GetTime(&time_end);
	CTime timeEnd=time_end;

	CTimeSpan timeSpan;
	timeSpan=timeEnd-timeBegin;
	int nDays=(int)timeSpan.GetDays();
	if(nDays<0)
		return;

	nDays+=1;
	m_nDays=nDays;

	ClearData();
	for(int i=0;i<nDays;i++)
	{
		time_t time=timeBegin.GetTime()+i*SECONDONEDAY;
		XLogPack logPack;
		logPack.m_time=time;
		XSendDataManage::GetInstance()->AddSendDataOfGetLogByData(logPack);
	}
}

void XLog::OnBnClickedBtnQueryByUser()
{
	DWORD dwTime=GetTickCount();
	if((long)dwTime-(long)m_dwTime<3000)
	{
		return;
	}
	m_dwTime=GetTickCount();

	SYSTEMTIME time_begin={0};
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIME_BEGIN))->GetTime(&time_begin);
	CTime timeBegin=time_begin;

	SYSTEMTIME time_end={0};
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIME_END))->GetTime(&time_end);
	CTime timeEnd=time_end;

	CTimeSpan timeSpan;
	timeSpan=timeEnd-timeBegin;
	int nDays=(int)timeSpan.GetDays();
	if(nDays<0)
		return;

	nDays+=1;
	m_nDays=nDays;
	
	CString szUserName;
	GetDlgItem(IDC_EDIT_QUERYUSER)->GetWindowText(szUserName);
	szUserName.Trim();
	if(szUserName==_T(""))
	{
		_M(_T("266"),_T("请选择或者输入用户！"),MB_OK);
		return;
	}

	ClearData();
	for(int i=0;i<nDays;i++)
	{
		time_t time=timeBegin.GetTime()+i*SECONDONEDAY;
		XLogPack logPack;
		logPack.m_time=time;
		logPack.m_szUserName=szUserName;
		XSendDataManage::GetInstance()->AddSendDataOfGetLogByUser(logPack);
	}
}

void XLog::OnBnClickedBtnQueryByNode()
{
	DWORD dwTime=GetTickCount();
	if((long)dwTime-(long)m_dwTime<3000)
	{
		return;
	}

	m_dwTime=GetTickCount();

	SYSTEMTIME time_begin={0};
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIME_BEGIN))->GetTime(&time_begin);
	CTime timeBegin=time_begin;

	SYSTEMTIME time_end={0};
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIME_END))->GetTime(&time_end);
	CTime timeEnd=time_end;

	CTimeSpan timeSpan;
	timeSpan=timeEnd-timeBegin;
	int nDays=(int)timeSpan.GetDays();
	if(nDays<0)
		return;

	nDays+=1;
	m_nDays=nDays;

	CString szNodeName;
	GetDlgItem(IDC_EDIT_QUERYNODE)->GetWindowText(szNodeName);
	szNodeName.Trim();
	if(szNodeName==_T(""))
	{
		_M(_T("267"),_T("请选择或者输入节点！"),MB_OK);
		return;
	}

	CString szRealName=GetNodeRealNameByName(szNodeName);

	ClearData();
	for(int i=0;i<nDays;i++)
	{
		time_t time=timeBegin.GetTime()+i*SECONDONEDAY;
		XLogPack logPack;
		logPack.m_time=time;
		logPack.m_szRealName=szRealName;
		XSendDataManage::GetInstance()->AddSendDataOfGetLogByNode(logPack);
	}
}

CString XLog::GetNodeRealNameByName(CString szName)
{
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	for(auto& node:MapNode)
	{
		XNode* pNode=node.second;
		if(pNode->GetNodeName()==szName)
			return pNode->GetRealID();
	}
	return _T("");
}

void XLog::ClearData()
{
	ClearVec();
	m_nReciveIndex=0;
	m_nTotalList=0;
}

void XLog::OnBnClickedBtnJump()
{
	CString szTotalPage;
	GetDlgItem(IDC_STATIC_TOTALPAGE)->GetWindowText(szTotalPage);
	szTotalPage.Trim();
	int nTotalPage=_ttoi(szTotalPage);

	CString szJumpPage;
	GetDlgItem(IDC_EDIT_JUMP)->GetWindowText(szJumpPage);
	szJumpPage.Trim();
	int nJumpPage=_ttoi(szJumpPage);

	if(nJumpPage>nTotalPage)
		return;

	CString szCurPage;
	GetDlgItem(IDC_STATIC_PAGE)->GetWindowText(szCurPage);
	//m_TextPage.SetText(szCurPage);
	szCurPage.Trim();
	int nCurPage=_ttoi(szCurPage);

	//跳页也集合大小关系
	if(nJumpPage==nCurPage)
		return;

	if(nJumpPage<nCurPage)
	{
		//往后跳
		int nJump=nCurPage-nJumpPage;
		for(int j=0;j<nJump;j++)
		{
			//循环多次
			int nFrontSize=m_vecFront.size();
			if(nFrontSize==0)
				return;

			int nSize=m_VecLog.size();
			if(nSize==0)
				return;


			for(int i=0;i<PAGELISTCOUNT;i++)
			{
				if(i<nSize)
				{
					XLogInfo* pInfo=m_VecLog.back();
					m_VecBack.insert(m_VecBack.begin(),pInfo);
					m_VecLog.pop_back();
				}
			}

			for(int i=0;i<PAGELISTCOUNT;i++)
			{
				if(i<nFrontSize)
				{
					XLogInfo* pInfo=m_vecFront.back();
					m_VecLog.insert(m_VecLog.begin(),pInfo);
					m_vecFront.pop_back();
				}
			}
		}
	}
	else
	{
		int nJump=nJumpPage-nCurPage;
		for(int j=0;j<nJump;j++)
		{
			int nBackSize=m_VecBack.size();
			if(nBackSize==0)
				return;
			int nSize=m_VecLog.size();
			if(nSize==0)
				return;
			//保存当前显示log
			for(int i=0;i<PAGELISTCOUNT;i++)
			{
				if(i<nSize)
				{
					XLogInfo* pInfo=m_VecLog.front();
					m_vecFront.push_back(pInfo);
					m_VecLog.erase(m_VecLog.begin());
				}
			}

			//设置新的
			for(int i=0;i<PAGELISTCOUNT;i++)
			{
				if(i<nBackSize)
				{
					XLogInfo* pLogBack=m_VecBack.front();
					m_VecLog.push_back(pLogBack);
					m_VecBack.erase(m_VecBack.begin());
				}
			}
		}
	}

	//显示 只显示veclog
	InsertLogList();
	//更新按钮
	SetBtnStatus();
}

void XLog::OnChangeEditQueryUser()
{
	CString szText;
	GetDlgItem(IDC_EDIT_QUERYUSER)->GetWindowText(szText);
	szText.Trim();
	if(szText!=_T(""))
	{
		int nCount=m_ListUser.GetItemCount();
		for(int i=0;i<nCount;i++)
		{
			CString szItemText=m_ListUser.GetItemText(i,0);
			if(szText==szItemText)
				XSetListCtrl::SetListItemSelect(&m_ListUser,i);
		}
	}
}

void XLog::OnChangeEditQueryNode()
{
	CString szText;
	GetDlgItem(IDC_EDIT_QUERYNODE)->GetWindowText(szText);
	szText.Trim();
	if(szText!=_T(""))
	{
		int nCount=m_ListNode.GetItemCount();
		for(int i=0;i<nCount;i++)
		{
			CString szItemText=m_ListNode.GetItemText(i,0);
			if(szText==szItemText)
				XSetListCtrl::SetListItemSelect(&m_ListNode,i);
		}
	}
}
