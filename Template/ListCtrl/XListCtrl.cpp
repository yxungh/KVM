// XListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XListCtrl.h"
#include "..\resource.h"


// XListCtrl
//��¼�����
static int m_nSortColumn=-1;
//��¼�ȽϷ���
static BOOL m_bMethod=FALSE;

IMPLEMENT_DYNAMIC(XListCtrl,CListCtrl)

XListCtrl::XListCtrl():
	m_OddItemBkColor(0xFEF1E3),
	m_EvenItemBkColor(0xD2D2D2),
	m_HoverItemBkColor(0x1E00FF),
	m_SelectItemBkColor(GetSysColor(COLOR_HIGHLIGHT)),
	m_OddItemTextColor(GetSysColor(COLOR_BTNTEXT)),
	m_EvenItemTextColor(GetSysColor(COLOR_BTNTEXT)),
	m_HoverItemTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)),
	m_SelectItemTextColor(GetSysColor(COLOR_BTNTEXT)),
	m_nHoverIndex(-1),
	m_bTracking(FALSE),
	m_bEnableTips(FALSE)
{
}

XListCtrl::~XListCtrl()
{
}

BEGIN_MESSAGE_MAP(XListCtrl,CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,&XListCtrl::OnNMCustomdraw)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK,OnColumnclickList)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// XListCtrl ��Ϣ�������
void XListCtrl::OnNMCustomdraw(NMHDR *pNMHDR,LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD=reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	*pResult=CDRF_DODEFAULT;

	int nItemIndex=pNMCD->nmcd.dwItemSpec;
	if(CDDS_PREPAINT==pNMCD->nmcd.dwDrawStage)
	{
		*pResult=CDRF_NOTIFYITEMDRAW;
	}
	else if(CDDS_ITEMPREPAINT==pNMCD->nmcd.dwDrawStage)
	{
		*pResult=CDRF_NOTIFYSUBITEMDRAW;
	}
	else if((CDDS_ITEMPREPAINT|CDDS_SUBITEM)==pNMCD->nmcd.dwDrawStage)
	{
		if(nItemIndex==m_nHoverIndex)
		{
			pNMCD->clrTextBk=m_HoverItemBkColor;
			pNMCD->clrText=m_HoverItemTextColor;
		}
		else if(GetItemState(nItemIndex,LVIS_SELECTED)==LVIS_SELECTED)
		{
			pNMCD->clrTextBk=m_SelectItemBkColor;
			pNMCD->clrText=pNMCD->clrFace=m_SelectItemTextColor;
			::SetTextColor(pNMCD->nmcd.hdc,m_SelectItemTextColor);
		}
		else if(nItemIndex%2==0)
		{
			pNMCD->clrTextBk=m_EvenItemBkColor;
			pNMCD->clrText=m_EvenItemTextColor;
		}
		else
		{
			pNMCD->clrTextBk=m_OddItemBkColor;
			pNMCD->clrText=m_OddItemTextColor;
		}
		*pResult=CDRF_NEWFONT;
	}
}

void XListCtrl::OnMouseMove(UINT nFlags,CPoint point)
{
	int nIndex=HitTest(point);
	if(nIndex!=m_nHoverIndex)
	{
		int nOldIndex=m_nHoverIndex;
		m_nHoverIndex=nIndex;

		CRect rc;
		if(nOldIndex!=-1)
		{
			GetItemRect(nOldIndex,&rc,LVIR_BOUNDS);
			InvalidateRect(&rc);
		}

		if(m_nHoverIndex!=-1)
		{
			GetItemRect(m_nHoverIndex,&rc,LVIR_BOUNDS);
			InvalidateRect(&rc);
		}
	}

	if(!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize=sizeof(tme);
		tme.hwndTrack=m_hWnd;
		tme.dwFlags=TME_LEAVE/*|TME_HOVER*/;
		tme.dwHoverTime=1;
		m_bTracking=_TrackMouseEvent(&tme);
	}

	//==================��ʾ=========================
	if(m_bEnableTips)
	{
		CString szTips;

		LVHITTESTINFO lvhti;
		lvhti.pt=point;
		SubItemHitTest(&lvhti);

		if((lvhti.iItem!=m_nItem)||(lvhti.iSubItem!=m_nSubItem))
		{
			m_nItem=lvhti.iItem;
			m_nSubItem=lvhti.iSubItem;
			if((m_nItem!=-1)&&(m_nSubItem!=-1))
			{
				szTips=GetItemText(m_nItem,m_nSubItem);
				int strWidth=GetStringWidth(szTips);
				int columnWidth=GetColumnWidth(m_nSubItem);

				//��֪��Ϊʲô��ʾ��ȫ�����еĿ�Ȼ��Ǵ����ַ�����ȣ������ַ��������Ӷ�20
				if(columnWidth<(strWidth+20))
				{
					m_ToolTip.AddTool(this,szTips);
					m_ToolTip.Pop();
				}
				else
				{
					m_ToolTip.AddTool(this,_T(""));
					m_ToolTip.Pop();
				}
			}
			else
			{
				m_ToolTip.AddTool(this,_T(""));
				m_ToolTip.Pop();
			}
		}
	}

	CListCtrl::OnMouseMove(nFlags,point);
}

void XListCtrl::OnMouseLeave()
{
	m_bTracking=FALSE;
	if(m_nHoverIndex!=-1)
	{
		CRect rc;
		GetItemRect(m_nHoverIndex,&rc,LVIR_BOUNDS);
		m_nHoverIndex=-1;
		InvalidateRect(&rc);
	}

	CListCtrl::OnMouseLeave();
}

BOOL XListCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(m_bEnableTips && m_ToolTip.GetSafeHwnd())
	{
		m_ToolTip.RelayEvent(pMsg);
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}

void XListCtrl::EnableToolTips(BOOL b)
{
	m_bEnableTips=b;
	if(m_bEnableTips)
	{
		m_ToolTip.Create(this,TTS_ALWAYSTIP);
	}
}

void XListCtrl::InitImageList()
{
	CHeaderCtrl *pHeaderCtrl=GetHeaderCtrl();
	m_ImageList.Create(16,16,ILC_COLOR16|ILC_MASK,0,4);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_UP));
	//m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));

	pHeaderCtrl->SetImageList(&m_ImageList);
}

int CALLBACK CompareProc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
	int row1=(int)lParam1;
	int row2=(int)lParam2;
	CListCtrl* pListCtrl=(CListCtrl*)lParamSort;

	CString szText=pListCtrl->GetItemText(0,0);

	CString szText1=pListCtrl->GetItemText(row1,m_nSortColumn);
	CString szText2=pListCtrl->GetItemText(row2,m_nSortColumn);

	if(szText1==szText1.SpanIncluding(_T("0123456789"))&&
	   szText2==szText2.SpanIncluding(_T("0123456789")))
	{
		int n1=_ttoi(szText1);
		int n2=_ttoi(szText2);

		if(m_bMethod)
			return n2-n1;
		else
			return n1-n2;
	}
	else
	{
		USES_CONVERSION;
		std::string s1(W2A(szText1));
		const char* cstr1=s1.c_str();

		std::string s2(W2A(szText2));
		const char* cstr2=s2.c_str();

		//�Ƚϣ��Բ�ͬ���в�ͬ�Ƚϣ�ע���¼ǰһ����������һ��Ҫ�෴����		 
		if(m_bMethod)
			return strcmp(cstr2,cstr1);
		else
			return strcmp(cstr1,cstr2);
	}

}

void XListCtrl::OnColumnclickList(NMHDR* pNMHDR,LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV=reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	m_nSortColumn=pNMLV->iSubItem;//�������

	int nCount=GetItemCount();
	for(int i=0;i<nCount;i++)
	{
		SetItemData(i,i);
	}

	//�����ͷ��ʽ
	CHeaderCtrl* pHdrCtrl=GetHeaderCtrl();
	if(pHdrCtrl&&pHdrCtrl->GetSafeHwnd())
	{
		int n=pHdrCtrl->GetItemCount();

		HDITEM hdi={0};
		TCHAR szBuf[129]={0};
		hdi.mask=HDI_TEXT; //ȡ�ַ�����     
		hdi.pszText=szBuf; //�ַ�������     
		hdi.cchTextMax=128; //��������С 

		for(int i=0;i<n;i++)
		{
			hdi.mask=HDI_IMAGE|HDI_FORMAT; //��ȡ�����ͷͼ��״̬������ָ��  
			pHdrCtrl->GetItem(i,&hdi);
			if(i==m_nSortColumn)
			{
				if(hdi.fmt&HDF_IMAGE) //ǰ��2�ε��ͬһ��ʱ�Ѿ�����ı��������л���ͷͼ�ꡣ  
				{
					hdi.iImage=1-hdi.iImage;
					m_bMethod=!m_bMethod;
				}
				else //ǰ������ͬ��ʱͼ����ʾ���µ����ͷ
				{
					hdi.iImage=0;
					hdi.fmt|=HDF_IMAGE|HDF_BITMAP_ON_RIGHT;
					if(m_bMethod)//Ϊ�˱�֤�µ���������ϴ���ʾһ��
					{
						hdi.iImage=1-hdi.iImage;
					}
				}
			}
			else
			{
				hdi.mask=HDI_FORMAT;
				hdi.fmt&=~HDF_IMAGE&~HDF_BITMAP_ON_RIGHT;
			}
			pHdrCtrl->SetItem(i,&hdi);
		}
	}
	SortItems(CompareProc,(DWORD)this);//����ڶ��������ǱȽϺ����ĵ���������
	*pResult=0;
}
