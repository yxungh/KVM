#include "stdafx.h"
#include "XColumnChart.h"

int XColumnChart::m_nCloumnWidth=20;
int XColumnChart::m_nColumnSize=10;

XColumnChart::XColumnChart()
{
	//for(int i=1;i<=35;i++)
	//{
	//	InsertColumnData(i,50);
	//}
	//InsertColumnData(_T("m1"),50);
	//InsertColumnData(_T("2"),80);
	//InsertColumnData(_T("3"),30);
	//InsertColumnData(_T("4"),90);
	//InsertColumnData(_T("5"),20);
	//InsertColumnData(_T("6"),10);
	//InsertColumnData(_T("7"),80);
	//InsertColumnData(_T("8"),50);
	//InsertColumnData(_T("9"),66);
	//InsertColumnData(_T("100"),40);
	//InsertColumnData(_T("11"),50);
	//InsertColumnData(_T("12"),43);
	//InsertColumnData(_T("13"),55);
	//InsertColumnData(_T("14"),60);
	//InsertColumnData(_T("15"),70);
	//InsertColumnData(_T("16"),30);
	//InsertColumnData(_T("17"),50);
	//InsertColumnData(_T("18"),30);
	//InsertColumnData(_T("19"),80);
	//InsertColumnData(_T("20"),50);
}

XColumnChart::~XColumnChart()
{
	Clear();
}

RECTF XColumnChart::GetRect()
{
	return m_rect;
}

void XColumnChart::Clear()
{
	m_MapColumnData.clear();
	m_MapKeyColor.clear();
	
	m_VecTempKey.clear();
	m_VecKey.clear();
	m_VecData.clear();
	m_VecKeyBack.clear();
	m_VecKeyFront.clear();
	m_VecColor.clear();
	m_VecTempColor.clear();
	m_bFalg=FALSE;
}

//不能再Draw中添加数据（登录时候添加数据）,先调用clear
void XColumnChart::InsertColumnData(CString nKey,int nData,BOOL bMainSecond)
{
	UNUSED(bMainSecond);
	if(m_MapColumnData.find(nKey)==m_MapColumnData.end())
	{
		m_MapColumnData.insert(std::pair<CString,int>(nKey,nData));
	}
	else
	{
		m_MapColumnData[nKey]=nData;
	}

	int nSize=m_VecKey.size();
	if(nSize<m_nColumnSize)
	{
		m_VecKey.push_back(nKey);
		m_VecData.push_back(nData);
	}
	else
	{
		m_VecKeyBack.push_back(nKey);
	}
	//每次插入数据，要保证为第一页
	m_nShowIndex=1;
}

void XColumnChart::SetShowIndex()
{	
	//处理循环显示
	int nSize=m_MapColumnData.size();
	if(nSize==0)
		return;

	if(nSize<=m_nColumnSize)
		return;

	m_nShowIndex++;

	//次数
	int nCount=0;
	int nFre=0;
	if(nSize%m_nColumnSize==0)
	{
		nCount=nSize/m_nColumnSize;
		nFre=m_nColumnSize;
	}	
	else
	{
		nCount=nSize/m_nColumnSize+1;
		if(m_nShowIndex==nCount)
			nFre=nSize%m_nColumnSize;
		else
			nFre=m_nColumnSize;
	}

	//缓存集合
	if(m_VecTempKey.size()!=0)
	{
		m_VecKeyBack.clear();
		for(auto nKey:m_VecTempKey)
		{
			m_VecKeyBack.push_back(nKey);
		}
		m_VecTempKey.clear();
	}

	m_VecKeyFront.clear();
	for(auto nKey:m_VecKey)
	{
		m_VecKeyFront.push_back(nKey);
	}

	m_VecKey.clear();
	for(int i=0;i<nFre;i++)
	{
		CString nKey=m_VecKeyBack.front();
		m_VecKey.push_back(nKey);
		m_VecKeyBack.erase(m_VecKeyBack.begin());
	}

	m_VecData.clear();
	for(auto nKey:m_VecKey)
	{
		if(m_MapColumnData.find(nKey)!=m_MapColumnData.end())
		{
			m_VecData.push_back(m_MapColumnData[nKey]);
		}
	}

	if(m_nShowIndex==nCount)
	{
		m_nShowIndex=0;
		for(auto nKey:m_VecKeyFront)
		{
			m_VecTempKey.push_back(nKey);
		}
		for(auto nKey:m_VecKey)
		{
			m_VecTempKey.push_back(nKey);
		}
	}
}

void XColumnChart::SetColumnSelect(CString nID)
{
	//先重置颜色
	m_VecColor.clear();
	m_MapKeyColor.clear();
	int nSize=m_VecKey.size();
	for(int i=0;i<nSize;i++)
	{
		CString nKey=m_VecKey[i];
		Color color=m_VecTempColor[i];


		m_MapKeyColor.insert(std::pair<CString,Color>(nKey,color));
		m_VecColor.push_back(color);
	}
	//把选中颜色换成红色
	if(m_MapKeyColor.find(nID)!=m_MapKeyColor.end())
	{
		Color color=m_MapKeyColor[nID];
		for(auto& c:m_VecColor)
		{
			if(c.GetR()==color.GetR()&&c.GetG()==color.GetG()&&c.GetB()==color.GetB())
			{
				c=Color(255,0,0);
			}
		}
	}
}

void XColumnChart::Draw(Graphics& graphics)
{
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,(float)6.5*m_dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrush(Color(255,204,153,51));

	Gdiplus::StringFormat stringForamt;
	stringForamt.SetAlignment(StringAlignmentCenter);
	stringForamt.SetLineAlignment(StringAlignmentFar);

	Gdiplus::Pen penL(Gdiplus::Color(255,0,255,255),1.0f);
	Gdiplus::Pen penB(Gdiplus::Color(255,49,92,126),1.0f);

	int nBeforHeight=(int)m_rect.Height;
	RectScale(m_rect);
	int nWidth=(int)m_rect.Width;
	int nHeight=(int)m_rect.Height;
	//绘制坐标系
	graphics.DrawLine(&penL,m_rect.X,m_rect.GetBottom(),m_rect.X,m_rect.GetTop());
	int nPos=5;
	int nDiatance=nHeight/5;
	for(int i=0;i<=nPos;i++)
	{
		graphics.DrawLine(&penL,m_rect.X,m_rect.GetBottom()-i*nDiatance,m_rect.X+4,m_rect.GetBottom()-i*nDiatance);
	}
	graphics.DrawLine(&penB,m_rect.X,m_rect.GetBottom(),m_rect.GetRight(),m_rect.GetBottom());

	//没有数据不绘制柱形
	int nSize=m_VecKey.size();
	if(nSize==0)
		return;

	if(nSize>m_nColumnSize)
		nSize=m_nColumnSize;

	//随机产生10种颜色(只生成一次颜色)，重复利用10种颜色
	if(!m_bFalg)
	{
		m_VecColor.clear();
		m_MapKeyColor.clear();
		m_VecTempColor.clear();
		for(int i=0;i<nSize;i++)
		{
			uint8_t r=(rand()%(250-30)+30);
			uint8_t g=(rand()%(250-30)+30);
			uint8_t b=(rand()%(250-30)+30);
			if(r==204&&g==153&&b==51)
				continue;

			m_MapKeyColor.insert(std::pair<CString,Color>(m_VecKey[i],Color(r,g,b)));
			m_VecColor.push_back(Color(r,g,b));
			m_VecTempColor.push_back(Color(r,g,b));
		}
		m_bFalg=TRUE;
	}
	//////////////////////////////////////////////////////////////////////////
	//绘制柱形
	int nTempWidth=nWidth/(nSize+1);
	int nMax=GetMaxData();
	//求出所有比例高度以及键值
	std::vector<int> VecHeight;
	for(auto& nData:m_VecData)
	{
		//没有接管
		int nTemp=0;
		if(nMax==0)
		{
			nTemp=0;
		}
		else
		{
			nTemp=nData*nBeforHeight/nMax;
		}
		VecHeight.push_back(nTemp);
	}

	float nLeft=m_rect.X+(nTempWidth-m_nCloumnWidth/2);
	for(int i=0;i<nSize;i++)
	{
		//////////////////////////////////////////////////////////////////////////
		Gdiplus::SolidBrush brush(m_VecColor[i]);
		Gdiplus::Pen pen(m_VecColor[i]);
		//////////////////////////////////////////////////////////////////////////

		RECTF rect(nLeft,(float)(m_rect.GetBottom()-VecHeight[i]*m_dwScale),(float)m_nCloumnWidth,(float)VecHeight[i]);
		rect.Width*=m_dwScale;
		rect.Height*=m_dwScale;

		graphics.FillRectangle(&brush,rect);
		graphics.DrawRectangle(&pen,rect);

		//绘制数据
		RECTF rectData;
		rectData.X=rect.X;
		rectData.Y=rect.Y-15*m_dwScale;
		rectData.Width=rect.Width;
		rectData.Height=15*m_dwScale;
		CString szTemp;
		szTemp.Format(_T("%d"),m_VecData[i]);
		graphics.DrawString(szTemp,-1,&font,rectData,&stringForamt,&textbrush);
		
		RECTF rectKey;
		rectKey.X=rect.X;
		rectKey.Y=rect.GetBottom();
		rectKey.Width=rect.Width;
		rectKey.Height=15*m_dwScale;
		CString szKey=m_VecKey[i];
		//szKey.Format(_T("%d"),m_VecKey[i]);
		graphics.DrawString(szKey,-1,&font,rectKey,&stringForamt,&textbrush);

		nLeft+=nTempWidth;
	}
}

int XColumnChart::GetMaxData()
{
	int nMax=0;
	for(auto e:m_VecData)
	{
		if(nMax<e)
			nMax=e;
	}
	return nMax;
}