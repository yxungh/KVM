#include "StdAfx.h"
#include "HandleCalculate.h"
#include "XNodeGroupInfo.h"
#include "XTranslationManage.h"

HandleCalculate::HandleCalculate(void)
{
}


HandleCalculate::~HandleCalculate(void)
{
}

CString HandleCalculate::GetIPByRTSPAddr(CString szRTSPAddr)
{
	if(_T("")==szRTSPAddr)
	{
		return _T("");
	}

	int nLen=szRTSPAddr.GetLength();

	if(nLen<8)
	{
		return _T("");
	}

	CString nPrefix=szRTSPAddr.Mid(0,7);
	nPrefix.MakeLower();

	if(nPrefix!=_T("rtsp://"))
	{
		return _T("");
	}

	int nFirstPos=7;

	int nPos=szRTSPAddr.Find('@',7);

	if(nPos!=-1)
	{

		nFirstPos=nPos+1;
	}

	int nlastPos=nLen-1;

	nPos=szRTSPAddr.Find(':',nFirstPos);

	if(nPos!=-1)
	{

		nlastPos=nPos-1;
	}
	else
	{
		nPos=szRTSPAddr.Find('/',nFirstPos);

		if(nPos!=-1)
		{

			nlastPos=nPos-1;
		}
	}

	CString szIP=szRTSPAddr.Mid(nFirstPos,nlastPos-nFirstPos+1);

	return szIP;
}

BOOL HandleCalculate::DecideRTSPAddr(CString szRTSPAddr)
{
	CString szIP=GetIPByRTSPAddr(szRTSPAddr);

	if(szIP==_T(""))
	{
		return FALSE;
	}

	USES_CONVERSION;
	char* pIP=W2A(szIP);

	if(INADDR_NONE==inet_addr(pIP))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void HandleCalculate::SetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,
									 CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,CDC& dc)
{
	int nOrgX=0;
	int nOrgY=0;

	GetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,nDrawDistanceX,nDrawDistanceY,nOrgX,nOrgY);

	dc.SetViewportOrg(nOrgX,nOrgY);
}

void HandleCalculate::GetViewPortOrg(CRect& rect,int& noffsetX,int& noffsetY,
									 CSize& size,float& dwScale,const int& nDrawDistanceX,const int& nDrawDistanceY,int& nOrgX,int& nOrgY)
{
	int nWidth=rect.Width();
	int nHeight=rect.Height();

	if(nWidth>size.cx)
	{
		nOrgX=(nWidth-size.cx)/2;
	}
	else
	{
		nOrgX=0;
	}

	if(nHeight>size.cy)
	{
		nOrgY=(nHeight-size.cy)/2;
	}
	else
	{
		nOrgY=0;
	}

	nOrgX=nOrgX-noffsetX+nDrawDistanceX;
	nOrgY=nOrgY-noffsetY+nDrawDistanceY;
}

BOOL HandleCalculate::DecideIP(CString szIP)
{
	struct in_addr addr;

	USES_CONVERSION;
	char* pIP=W2A(szIP);

	if(inet_pton(AF_INET,pIP,(void *)&addr)>0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int HandleCalculate::GetIDByJsonKey(CString szKey)
{
	int nID=0;
	int nLen=szKey.GetLength();
	int n=szKey.Find('_');
	CString szID=szKey.Right(nLen-n-1);
	nID=_ttoi(szID);
	return nID;
}

int HandleCalculate::GetTypeByJsonKey(CString szKey)
{
	int nLen=szKey.GetLength();
	int n=szKey.Find('_');
	CString szType=szKey.Left(nLen-n-1);
	int nType=_ttoi(szType);
	return nType;
}

CString HandleCalculate::GetSceneNameByJsonKey(CString szKey)
{
	CString szName=_T("");
	int nLen=szKey.GetLength();
	int n=szKey.Find('.');
	if(n==-1)
	{
		szName=szKey;
	}
	else
	{
		szName=szKey.Left(n);
	}

	return szName;
}

CString HandleCalculate::GetTimeBySecond(time_t time)
{
	struct tm t;
	localtime_s(&t,&time);

	CString szCreateTime;
	szCreateTime.Format(_T("%4d/%02d/%02d %02d:%02d:%02d"),t.tm_year+1900,t.tm_mon+1,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);

	return szCreateTime;
}

void HandleCalculate::GetRowAndColumnByMatrix(CString szMatrix,int& nRow,int& nColumn)
{
	int nPos=szMatrix.Find('x');

	CString szLeft=szMatrix.Left(nPos);
	nColumn=_ttoi(szLeft);

	CString szRight=szMatrix.Mid(nPos+1,szMatrix.GetLength()-nPos);
	nRow=_ttoi(szRight);
}

void HandleCalculate::GetMatrixByInfo(CString szInfo,VEC_ARRAGE& VecArrage)
{
	VecArrage.clear();

	CString szTempInfo=szInfo;
	CString szLeft=_T("");

	VEC_STRING VecString;

	int nPos=szTempInfo.Find('\n');
	if(nPos!=-1)
	{
		while(nPos!=-1)
		{
			szLeft=szTempInfo.Left(nPos);
			VecString.push_back(szLeft);

			szTempInfo=szTempInfo.Mid(nPos+1,szTempInfo.GetLength()-nPos);
			nPos=szTempInfo.Find('\n');

			if(nPos==-1)
				VecString.push_back(szTempInfo);
		}
	}
	else
	{
		VecString.push_back(szTempInfo);
	}

	for(auto iter=VecString.begin();iter!=VecString.end();++iter)
	{
		CString szString=*iter;

		CString szTempString=szString;
		CString szLeft;

		std::vector<int> VecInt;

		int nPos=szTempString.Find(';');
		while(nPos!=-1)
		{
			szLeft=szTempString.Left(nPos);

			int n=szLeft.Find('#');
			CString szValue=szLeft.Mid(n+1,szLeft.GetLength()-n);

			int nValue=_ttoi(szValue);
			VecInt.push_back(nValue);

			szTempString=szTempString.Mid(nPos+1,szTempString.GetLength()-nPos);
			nPos=szTempString.Find(';');
		}
		VecArrage.push_back(VecInt);
	}
}

XNodeGroupInfo* HandleCalculate::GetNodeInfoByID(MAP_NODEGROUP& MapGroup,int nNodeGroupID,CString& szOldName,BOOL b)
{
	for(auto iter=MapGroup.begin();iter!=MapGroup.end();++iter)
	{
		XNodeGroupInfo* pInfo=iter->second;

		if(b)
		{
			if(pInfo->GetMainSecond())
			{
				if(pInfo->GetGroupID()==nNodeGroupID)
				{
					szOldName=iter->first;
					return pInfo;
				}
			}
		}
		else
		{
			if(!pInfo->GetMainSecond())
			{
				if(pInfo->GetGroupID()==nNodeGroupID)
				{
					szOldName=iter->first;
					return pInfo;
				}
			}
		}
	}

	return NULL;
}

void HandleCalculate::SplitCString(CString szSrc,std::map<int,HTREEITEM>& Map)
{
	int nPos=0;

	CString szTemp;
	szTemp=szSrc.Tokenize(_T(","),nPos);
	while(szTemp.Trim()!=_T(""))
	{
		int nTemp=_ttoi(szTemp);
		
		//Vec.push_back(nTemp);
		if(Map.find(nTemp)==Map.end())
		{
			Map.insert(std::pair<int,HTREEITEM>(nTemp,NULL));
		}

		szTemp=szSrc.Tokenize(_T(","),nPos);
	}
}

int HandleCalculate::GetScaleType(int nScale)
{
	int nType=0;

	switch(nScale)
	{
		case 200:
			nType=OPERATETYPE_SCALE200;
			break;
		case 175:
			nType=OPERATETYPE_SCALE175;
			break;
		case 150:
			nType=OPERATETYPE_SCALE150;
			break;
		case 125:
			nType=OPERATETYPE_SCALE125;
			break;
		case 100:
			nType=OPERATETYPE_SCALE100;
			break;
		case 75:
			nType=OPERATETYPE_SCALE75;
			break;
		case 50:
			nType=OPERATETYPE_SCALE50;
			break;
		default:
			break;

	}

	return nType;
}

CString HandleCalculate::AnalysisEvent(CString szEvent)
{
	if(szEvent==EVENT_START)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1200"));
	else if(szEvent==EVENT_CPU_EVENT)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1201"));
	else if(szEvent==EVENT_MATRIX_EVENT)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1202"));
	else if(szEvent==EVENT_USER_LOGIN)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1203"));
	else if(szEvent==EVENT_USER_LOGOUT)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1204"));
	else if(szEvent==EVENT_TERM_LOGIN)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1205"));
	else if(szEvent==EVENT_TERM_LOGOUT)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1206"));
	else if(szEvent==EVENT_CREATE_USER)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1207"));
	else if(szEvent==EVENT_DELETE_USER)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1208"));
	else if(szEvent==EVENT_MODIFY_USER)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1209"));
	else if(szEvent==EVENT_REMOVE_CTRL)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1210"));
	else if(szEvent==EVENT_REMOVE_VIEW)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1211"));
	else if(szEvent==EVENT_CTRL)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1212"));
	else if(szEvent==EVENT_VIEW)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1213"));
	else if(szEvent==EVENT_PUSH)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1214"));
	else if(szEvent==EVENT_TERM_CONNECT)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1215"));
	else if(szEvent==EVENT_TERM_DISCON)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1216"));
	else if(szEvent==EVENT_TERM_SET_ID)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1217"));
	else if(szEvent==EVENT_TERM_RENAME)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1218"));
	else if(szEvent==EVENT_TERM_CREATE)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1219"));
	else if(szEvent==EVENT_TERM_DELETE)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1220"));
	else if(szEvent==EVENT_TERM_MODIFY)
		return XTranslationManage::GetInstance()->GetTranslationString(_T("1221"));

	return _T("");
}

