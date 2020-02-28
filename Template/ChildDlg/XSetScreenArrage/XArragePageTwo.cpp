// XArragePageTwo.cpp : 实现文件
#include "stdafx.h"
#include "XArragePageTwo.h"
#include "afxdialogex.h"
#include "XTranslationManage.h"
#include "XScreenInfo.h"
#include "XDelegateArragePageTwo.h"
#include "XNode.h"
#include "XDragWnd.h"
#include "XConstantData.h"
#include "XArragePageOne.h"
#include "XNodeGroupInfo.h"
#include "XSendDataManage.h"



// XArragePageTwo 对话框

IMPLEMENT_DYNAMIC(XArragePageTwo, CPropertyPage)

XArragePageTwo::XArragePageTwo()
	: CPropertyPage(XArragePageTwo::IDD),
	m_nScreenRow(0),
	m_nScreenColumn(0),
	m_pDelegate(NULL),
	m_szGroupName(_T("")),
	m_pDragWnd(NULL)
{

}

XArragePageTwo::~XArragePageTwo()
{
	ClearVecScreenInfo();
	ClearVecArrage();
	RELEASE(m_pDragWnd);
}

void XArragePageTwo::ClearVecScreenInfo()
{
	for(auto iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();++iter)
	{
		delete *iter;
	}
	m_VecScreenInfo.clear();
}

void XArragePageTwo::ClearVecArrage()
{
	for(auto iter=m_VecArrage.begin();iter!=m_VecArrage.end();++iter)
	{
		std::vector<int> VecInt=*iter;
		VecInt.clear();
	}
	m_VecArrage.clear();
}

void XArragePageTwo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(XArragePageTwo, CPropertyPage)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_SHOWWINDOW()

END_MESSAGE_MAP()

// XArragePageTwo 消息处理程序
BOOL XArragePageTwo::OnSetActive()
{
	CPropertySheet* pSheet=(CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
	pSheet->GetDlgItem(ID_WIZBACK)->ShowWindow(SW_SHOW);
	pSheet->GetDlgItem(ID_WIZBACK)->SetWindowText(_T("<")+GetTranslationString(_T("155"),_T("上一步")));
	pSheet->GetDlgItem(ID_WIZFINISH)->SetWindowText(GetTranslationString(_T("159"),_T("完成")));

	return CPropertyPage::OnSetActive();
}

BOOL XArragePageTwo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	Init();
	return TRUE;
}

void XArragePageTwo::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CPropertyPage::OnShowWindow(bShow,nStatus);

	//if(bShow)
	//{
	//	GetParent()->ShowWindow(SW_HIDE);
	//	GetParent()->SetWindowPos(NULL,0,0,700,510,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
	//	GetParent()->ShowWindow(SW_SHOW);
	//}
}

void XArragePageTwo::Init()
{
	InitData();
	InitTree();
	AdjustLayout();

	ReloadInterface();
}
void XArragePageTwo::InitData()
{

	//初始化屏幕信息集合
	ClearVecScreenInfo();
	int nIndex=1;
	for(int i=0;i<m_nScreenRow;i++)
	{
		for(int j=0;j<m_nScreenColumn;j++)
		{
			XScreenInfo* pInfo=new XScreenInfo;
			pInfo->SetIndex(i);

			pInfo->SetRowIndex(i+1);
			pInfo->SetColumnIndex(j+1);
			m_VecScreenInfo.push_back(pInfo);

			nIndex++;
		}
	}


}

void XArragePageTwo::InitTree()
{
	MAP_NODE& MapNode=m_pDelegate->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			if(pNode->GetGroup()==0)
			{
				HTREEITEM hItem=m_TreeCtrl.InsertItem(pNode->GetNodeName());
				m_TreeCtrl.SetItemData(hItem,1);
			}
		}
	}
}

void XArragePageTwo::ReloadInterface()
{
	SetWindowText(GetTranslationString(_T("153"),_T("屏幕编排")));
}

CString XArragePageTwo::GetTranslationString(CString szKey,CString szDefault/*=_T("")*/)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

void XArragePageTwo::OnPaint()
{
	CPaintDC dc(this); 

	CDC* pDC=&dc;

	CRect rect;
	GetClientRect(rect);

	int nWidth=rect.Width();
	int nHeight=rect.Height();
	HDC hdc=pDC->GetSafeHdc();
	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);

	HDC hMemdc=tempDC.GetSafeHdc();
	HBITMAP hMembmp=CreateCompatibleBitmap(hdc,nWidth,nHeight);
	HBITMAP hOldbmp=(HBITMAP)SelectObject(hMemdc,hMembmp);
	Graphics graphics(hMemdc);

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.Clear(Color(255,240,240,240));

	CRect rectScreen;
	GetDlgItem(IDC_STATIC_SCREEN)->GetWindowRect(&rectScreen);
	ScreenToClient(&rectScreen);
	///////////////////////////////////////////////////////
	DrawArea(graphics,rectScreen);
	DrawScreen(graphics,rectScreen);
	///////////////////////////////////////////////////////
	BitBlt(hdc,rectScreen.left,rectScreen.top,nWidth,nHeight,hMemdc,0,0,SRCCOPY);
	graphics.ReleaseHDC(hMemdc);
	SelectObject(hMemdc,hOldbmp);
	tempDC.DeleteDC();
	DeleteObject(hMembmp);
}

int XArragePageTwo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CPropertyPage::OnCreate(lpCreateStruct)==-1)
		return -1;

	if(!InitImageList())
		return -1; 

	if(!InitTreeCtrl())
		return -1;
	return 0;
}

BOOL XArragePageTwo::InitTreeCtrl()
{
	m_TreeCtrl.SetScreenArrage(this);
	if(m_TreeCtrl.Create(WS_CHILD|WS_VISIBLE|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS,CRect(0,0,0,0),this,ID_TREE))
	{
		m_TreeCtrl.SetImageList(&m_ImageList,TVSIL_NORMAL);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL XArragePageTwo::InitImageList()
{
	if(!m_ImageList.Create(24,24,ILC_COLOR32|ILC_MASK,0,1))
		return FALSE;

	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_NODE));

	return TRUE;
}

void XArragePageTwo::AdjustLayout()
{
	if(NULL==GetSafeHwnd())
		return;

	CRect rect;
	GetDlgItem(IDC_STATIC_TREE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_TreeCtrl.SetWindowPos(NULL,rect.left+1,rect.top+1,rect.Width()-2,rect.Height()-1,SWP_NOACTIVATE|SWP_NOZORDER);
}

void XArragePageTwo::DrawArea(Graphics& graphics,CRect rect)
{
	//分隔线
	Gdiplus::Pen pen(Gdiplus::Color(255,0,0,0),1.0f);
	//虚线
	//Gdiplus::Pen pendash(Gdiplus::Color(255,0,0,0),1.0f);
	//Gdiplus::REAL dashVal[4]={1,4,1,4}; 
	//pendash.SetDashPattern(dashVal,4);

	int nShowColumn=m_nScreenColumn;
	int nShowRow=m_nScreenRow;

	if(nShowColumn==0||nShowRow==0)
		return;

	int distanceWidth=rect.Width()/nShowColumn;
	int distanceHeight=rect.Height()/nShowRow;

	int left=0;
	int top=0;
	int right=(int)rect.Width()-1;
	int bottom=(int)rect.Height()-1;
	int temp=0;

	for(int i=1;i<nShowColumn;i++)
	{
		temp=i*distanceWidth;
		graphics.DrawLine(&pen,temp,top,temp,bottom);
	}

	for(int i=1;i<nShowRow;i++)
	{
		temp=i*distanceHeight;
		graphics.DrawLine(&pen,left,temp,right,temp);
	}
}

void XArragePageTwo::DrawScreen(Graphics& graphics,CRect rect)
{
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	Gdiplus::Font font(_T("宋体"),12,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush brushRect(Gdiplus::Color(255,191,191,191));//区域颜色

	Gdiplus::Color brushColor(255,0,0,0);
	Gdiplus::SolidBrush brush(brushColor);

	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(StringAlignmentCenter);
	stringFormat.SetLineAlignment(StringAlignmentCenter);

	int nScreenColumn=m_nScreenColumn;
	int nScreenRow=m_nScreenRow;
	if(nScreenColumn==0||nScreenRow==0)
		return;

	int left=0;
	int top=0;

	int nScreenWidth=rect.Width()/nScreenColumn;
	int nScreenHeight=rect.Height()/nScreenRow;

	int nIndex=0;
	if (font.GetLastStatus()==Gdiplus::Ok)
	{
		for(int i=0;i<nScreenRow;i++)
		{
			for(int j=0;j<nScreenColumn;j++)
			{
				Gdiplus::RectF rectDraw((Gdiplus::REAL)left,(Gdiplus::REAL)top,(Gdiplus::REAL)nScreenWidth,(Gdiplus::REAL)nScreenHeight);

				XScreenInfo* pInfo=m_VecScreenInfo[nIndex++];
				if(pInfo->GetHave())
				{
					graphics.FillRectangle(&brushRect,rectDraw.X,rectDraw.Y,rectDraw.Width-1,rectDraw.Height-1);
				}

				//绘制文字
				CString szText=pInfo->GetNodeName();
				graphics.DrawString(szText,-1,&font,rectDraw,&stringFormat,&brush);

				left+=nScreenWidth;
			}
			left=0;
			top+=nScreenHeight;
		}
	}
}

void XArragePageTwo::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPropertyPage::OnLButtonDown(nFlags,point);

	CRect rect;
	GetDlgItem(IDC_STATIC_SCREEN)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	if(!rect.PtInRect(point))
		return;

	int nScreenColumn=m_nScreenColumn;
	int nScreenRow=m_nScreenRow;

	float nChildWidth=1.0f*rect.Width()/nScreenColumn;
	float nChildHeight=1.0f*rect.Height()/nScreenRow;

	int nRowIndex=(int)((point.y-rect.top)/nChildHeight);
	int nColumnIndex=(int)((point.x-rect.left)/nChildWidth);

	XScreenInfo* pInfo=NULL;
	pInfo=m_VecScreenInfo[nRowIndex*nScreenColumn+nColumnIndex];
	if(NULL!=pInfo)
		TRACE(_T("Index=%d\n"),pInfo->GetIndex());



}
void XArragePageTwo::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CPropertyPage::OnLButtonDblClk(nFlags,point);


}
void XArragePageTwo::OnMouseMove(UINT nFlags, CPoint point)
{
	CPropertyPage::OnMouseMove(nFlags,point);

}

XDragWnd* XArragePageTwo::CreateDragWnd()
{
	if(m_pDragWnd==NULL)
	{
		CreateWnd();
	}
	m_pDragWnd->Show();
	return m_pDragWnd;
}

void XArragePageTwo::CreateWnd()
{
	int nWidth=80;
	int nHeight=30;

	CRect rect(CPoint(0,0),CSize(nWidth,nHeight));

	m_pDragWnd=new XDragWnd;
	m_pDragWnd->Create(WS_CHILD|WS_VISIBLE,rect,m_pDelegate->GetCWND()->GetDesktopWindow(),0);
	m_pDragWnd->ShowWindow(SW_HIDE);
	m_pDragWnd->UpdateWindow();
}

void XArragePageTwo::DragEnd(CPoint point)
{
	ScreenToClient(&point);

	CRect rect;
	GetDlgItem(IDC_STATIC_SCREEN)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	if(!rect.PtInRect(point))
		return;

	int nScreenColumn=m_nScreenColumn;
	int nScreenRow=m_nScreenRow;
	if(nScreenColumn==0||nScreenRow==0)
		return;

	float nChildWidth=1.0f*rect.Width()/nScreenColumn;
	float nChildHeight=1.0f*rect.Height()/nScreenRow;

	int nRowIndex=(int)((point.y-rect.top)/nChildHeight);
	int nColumnIndex=(int)((point.x-rect.left)/nChildWidth);

	XScreenInfo* pInfo=NULL;
	pInfo=m_VecScreenInfo[nRowIndex*nScreenColumn+nColumnIndex];
	if(NULL==pInfo)
		return;

	//////////////////////////////////////////////////////////////////////////
	//判断是不是第一个
	if(!DecidedMaster())
	{
		pInfo->SetMaster(TRUE);
	}
	
	//判断拖拽是否存在
	int nNodeID=XConstantData::GetInstance()->GetAvliNodeID();
	XScreenInfo* pScreenInfo=NULL;
	if(DecidedNodeExist(pInfo,pScreenInfo,nNodeID))
	{
		//存在
		pScreenInfo->SetHave(FALSE);
		pScreenInfo->SetNodeID(0);
		pScreenInfo->SetNodeName(_T(""));
	}

	pInfo->SetHave(TRUE);
	pInfo->SetNodeName(XConstantData::GetInstance()->GetNodeCaption());
	pInfo->SetNodeID(nNodeID);

	Invalidate(FALSE);
}

BOOL XArragePageTwo::OnWizardFinish()
{
	//添加坐席
	CString szGroupName=m_szGroupName;
	if(_T("")==szGroupName)
		return FALSE;

	//保存屏幕排列信息
	SetVecArrage();
	//查找主节点
	int nMaster=GetMasterNode();
	//当前用户
	int nCreateID=m_pDelegate->GetCurUserID();
	
	CString szArray=GetArrayInfo();
	CString szMatrix=GetArrayMatrix();
	//更新
	XNodeGroupInfo nodeGroupInfo;
	nodeGroupInfo.SetGroupName(szGroupName);
	nodeGroupInfo.SetType(3);//输出为3
	nodeGroupInfo.SetMaster(nMaster);
	nodeGroupInfo.SetArray(szArray);
	nodeGroupInfo.SetMatrix(szMatrix);
	nodeGroupInfo.SetCreatorID(nCreateID);
	nodeGroupInfo.SetCreateMode(CREATEMODE_ARRAGE);

	//更新坐席排列
	XSendDataManage::GetInstance()->AddSendDataOfAddSeatArrage(nodeGroupInfo);

	return __super::OnWizardFinish();
}

MAP_NODE& XArragePageTwo::GetMapNode()
{
	return m_pDelegate->GetMapNode();
}

BOOL XArragePageTwo::DecidedNodeExist(XScreenInfo* pInfo,XScreenInfo*& pScreenInfo,int nNodeID)
{
	for(auto iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();++iter)
	{
		XScreenInfo* pTemp=*iter;
		if(pTemp==pInfo)
			continue;

		if(pTemp->GetNodeID()==nNodeID)
		{
			pScreenInfo=pTemp;
			return TRUE;
		}	
	}
	return FALSE;
}

BOOL XArragePageTwo::DecidedMaster()
{
	for(auto iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();++iter)
	{
		XScreenInfo* pInfo=*iter;
		if(pInfo->GetHave())
			return TRUE;
	}
	return FALSE;
}

void XArragePageTwo::SetVecArrage()
{
	ClearVecArrage();
	for(int i=0;i<m_nScreenRow;i++)
	{
		int nRow=i+1;
		std::vector<int> VecInt;
		for(auto iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();++iter)
		{
			XScreenInfo* pInfo=*iter;
			if(nRow==pInfo->GetRowIndex())
			{
				if(pInfo->GetHave())
					VecInt.push_back(pInfo->GetNodeID());
				else
					VecInt.push_back(0);
			}
		}
		m_VecArrage.push_back(VecInt);
	}
}

int XArragePageTwo::GetMasterNode()
{
	int nMaster=0;
	for(auto iter=m_VecScreenInfo.begin();iter!=m_VecScreenInfo.end();++iter)
	{
		XScreenInfo* pInfo=*iter;
		if(pInfo->GetMaster())
			nMaster=pInfo->GetNodeID();
	}
	return nMaster;
}

CString XArragePageTwo::GetArrayInfo()
{
	CString szValue=_T("");
	for(auto iter=m_VecArrage.begin();iter!=m_VecArrage.end();++iter)
	{
		CString szTempValue;
		std::vector<int> Vec=*iter;
		for(auto iter=Vec.begin();iter!=Vec.end();++iter)
		{
			int nValue=*iter;
			CString szTemp;
			szTemp.Format(_T("#%d;"),nValue);
			szTempValue+=szTemp;
		}
		szValue+=szTempValue;
		szValue+=_T("\n");
	}

	int nPos=szValue.ReverseFind('\n');
	return szValue.Left(nPos);
}

CString XArragePageTwo::GetArrayMatrix()
{
	CString szMatrix=_T("");
	int nColumn=0;
	for(auto iter=m_VecArrage.begin();iter!=m_VecArrage.end();++iter)
	{
		std::vector<int> Vec=*iter;
		nColumn=Vec.size();
	}

	int nRow=m_VecArrage.size();
	szMatrix.Format(_T("%dx%d"),nColumn,nRow);

	return szMatrix;
}