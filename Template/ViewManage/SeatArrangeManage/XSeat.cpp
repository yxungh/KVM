#include "stdafx.h"
#include "XSeat.h"
#include "HandlePath.h"
#include "XPropertiesWnd.h"
#include "XPropertyGrid.h"
#include "XProprtyGridFile.h"
#include "XTranslationManage.h"
#include "XSeatArrageManage.h"
#include "FileHandle.h"
#include "XMessageBox.h"



XSeat::XSeat()
{
}

XSeat::~XSeat()
{

}

void XSeat::SetColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	m_nColorR=r;
	m_nColorG=g;
	m_nColorB=b;
	m_nColorA=a;
}

CString XSeat::GetPhotoPath()
{
	return HandlePath::GetMapPhotoPath(m_szPhotoName);
}

void XSeat::OnPropertyChanged(CMFCPropertyGridProperty* pProperty)
{
	int nData=(int)pProperty->GetData();
	switch(nData)
	{
	case ID_SEATRECTX:
		{
			//更改X
			RECTF rect=m_rect;
			int nX=_variant_t(pProperty->GetValue());

			if(nX<0)
				nX=0;
			if(nX+(int)rect.Width>800)
				nX=800-(int)rect.Width;

			rect.X=(float)nX;
			m_rect=rect;
		}
		break;
	case ID_SEATRECTY:
		{
			RECTF rect=m_rect;
			int nY=_variant_t(pProperty->GetValue());

			if(nY<0)
				nY=0;
			if(nY+(int)rect.Height>810)
				nY=810-(int)rect.Height;

			rect.Y=(float)nY;
			m_rect=rect;
		}
		break;
	case ID_SEATRECTW:
		{
			RECTF rect=m_rect;
			int nWidth=_variant_t(pProperty->GetValue());

			if(nWidth+(int)rect.X>800)
				nWidth=800-(int)rect.X;
			
			rect.Width=(float)nWidth;
			m_rect=rect;
		}
		break;
	case ID_SEATRECTH:
		{
			RECTF rect=m_rect;
			int nHeight=_variant_t(pProperty->GetValue());

			if(nHeight+(int)rect.Y>810)
				nHeight=810-(int)rect.Y;

			rect.Height=(float)nHeight;
			m_rect=rect;
		}
		break;
	case ID_SEATCOLOR:
		{
			COLORREF color=_variant_t(((CMFCPropertyGridColorProperty*)pProperty)->GetColor());
			//默认颜色（暂时这样判断）
			if((unsigned long)(color)>16777215)
			{
				m_nColorR=91;
				m_nColorG=155;
				m_nColorB=213;
			}
			else
			{
				m_nColorR=GetRValue(color);
				m_nColorG=GetGValue(color);
				m_nColorB=GetBValue(color);
			}
			m_nColorA=255;
		}
		break;
	case ID_SEATTRANS:
		{
			int nTrans=_variant_t(pProperty->GetValue());

			if(nTrans>255)
				nTrans=255;
			if(nTrans<0)
				nTrans=0;

			m_nColorA=nTrans;
		}
		break;
	case ID_SEATMODEL:
		{
			CString szModel=_variant_t(pProperty->GetValue());
			if(szModel==_C(_T("122"),_T("纯色")))
			{
				SetModel(TRUE);
			}
			else if(_C(_T("123"),_T("图片")))
			{
				SetModel(FALSE);
			}
		}
		break;
	case ID_SEATROW:
		{
			int nRow=_variant_t(pProperty->GetValue());
			if(nRow>9)
				nRow=9;
				
			SetSeatRow(nRow);
		}
		break;
	case ID_SEATCOLUMN:
		{
			int nColumn=_variant_t(pProperty->GetValue());
			if(nColumn>5)
				nColumn=5;

			SetSeatColumn(nColumn);
		}
		break;
	default:
		break;
	}

	//更新预览墙
	if(NULL!=m_pManage)
		m_pManage->UpdateMultiWindowByPropertyChange(this,nData);
}

BOOL XSeat::OnDblClkPropertyGrid(XPropertyGrid* pPropertyGrid)
{
	int nData=(int)pPropertyGrid->GetData();
	switch(nData)
	{
	case ID_SEATMODEL:
		{
			CString szModel=(_variant_t)(pPropertyGrid->GetValue());
			if(szModel==_C(_T("122"),_T("纯色")))
			{
				SetModel(TRUE);
			}
			else if(_C(_T("123"),_T("图片")))
			{
				SetModel(FALSE);
			}
		}
		break;
	default:
		break;
	}
	//更新预览墙
	if(NULL!=m_pManage)
		m_pManage->UpdateMultiWindowByPropertyChange(this,nData);

	return TRUE;
}

BOOL XSeat::OnDblClkPropertyGridFile(XPropertyGridFile* pPropertyGridFile)
{
	int nData=(int)pPropertyGridFile->GetData();

	switch(nData)
	{
	case ID_SEATPIC:
		{
			CString szFileName;
			CString szFilePath;
			if(OpenSelectPhotoFileDialog(szFileName,szFilePath))
			{
				//复制图片到程序路径
				if(!FileHandle::copyFile(szFilePath,HandlePath::GetMapPhotoPath(szFileName)))
				{
					_M(_T("121"),_T("拷贝背景图片失败！"),MB_OK);
					return FALSE;
				}

				pPropertyGridFile->SetValue(_variant_t(szFileName));
				SetPhotoName(szFileName);
			}
		}
		break;
	default:
		break;
	}

	//更新预览墙
	if(NULL!=m_pManage)
		m_pManage->UpdateMultiWindowByPropertyChange(this,nData);

	return TRUE;
}

void XSeat::OnClickButtonPropertyGridFile(XPropertyGridFile* pPropertyGridFile)
{
	int nData=(int)pPropertyGridFile->GetData();

	switch(nData)
	{
	case ID_SEATPIC:
		{
			CString szFileName;
			CString szFilePath;
			if(OpenSelectPhotoFileDialog(szFileName,szFilePath))
			{
				//复制图片到程序路径
				if(!FileHandle::copyFile(szFilePath,HandlePath::GetMapPhotoPath(szFileName)))
				{
					_M(_T("121"),_T("拷贝背景图片失败！"),MB_OK);
					return;
				}

				pPropertyGridFile->SetValue(_variant_t(szFileName));
				SetPhotoName(szFileName);
			}
		}
		break;
	default:
		break;
	}

	//更新预览墙
	if(NULL!=m_pManage)
		m_pManage->UpdateMultiWindowByPropertyChange(this,nData);
}

void XSeat::SetPropertiesWnd()
{
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();

	XPropertyGrid* pGroup1=new XPropertyGrid(_C(_T("750"),_T("基本信息")));

	//名称
	XPropertyGrid* pSeatName=new XPropertyGrid(_C(_T("837"),_T("名称")),_variant_t(GetGroupName()),
		_C(_T("838"),_T("坐席名称")),ID_SEATNAME);
	pGroup1->AddSubItem(pSeatName);

	//窗口X
	XPropertyGrid* pRectX=new XPropertyGrid(_T("X"),_variant_t((int)m_rect.X),
		_C(_T("849"),_T("坐席位置左上角X坐标，X大于0，小于800")),ID_SEATRECTX);
	pGroup1->AddSubItem(pRectX);

	int nMaxX=800-(int)m_rect.Width;
	pRectX->EnableSpinControl(TRUE,0,nMaxX);

	//窗口Y
	XPropertyGrid* pRectY=new XPropertyGrid(_T("Y"),_variant_t((int)m_rect.Y),
		_C(_T("850"),_T("坐席位置左上角X坐标，X大于0，小于800")),ID_SEATRECTY);
	pGroup1->AddSubItem(pRectY);

	int nMaxY=810-(int)m_rect.Height;
	pRectY->EnableSpinControl(TRUE,0,nMaxY);

	//窗口W
	XPropertyGrid* pRectW=new XPropertyGrid(_C(_T("851"),_T("宽度")),_variant_t((int)m_rect.Width),
		_C(_T("852"),_T("坐席窗口宽度")),ID_SEATRECTW);
	pGroup1->AddSubItem(pRectW);

	int nMaxW=800-(int)m_rect.X;
	pRectW->EnableSpinControl(TRUE,0,nMaxW);

	//窗口H
	XPropertyGrid* pRectH=new XPropertyGrid(_C(_T("853"),_T("高度")),_variant_t((int)m_rect.Height),
		_C(_T("854"),_T("坐席窗口高度")),ID_SEATRECTH);
	pGroup1->AddSubItem(pRectH);

	int nMaxH=810-(int)m_rect.Y;
	pRectH->EnableSpinControl(TRUE,0,nMaxH);

	//行
	XPropertyGrid* pSeatRow=new XPropertyGrid(_C(_T("839"),_T("行")),_variant_t(m_nSeatRow),
		_C(_T("840"),_T("坐席屏幕排列行数")),ID_SEATROW);
	pGroup1->AddSubItem(pSeatRow);

	//列
	XPropertyGrid* pSeatColumn=new XPropertyGrid(_C(_T("841"),_T("列")),_variant_t(m_nSeatColumn),
		_C(_T("842"),_T("坐席屏幕排列列数")),ID_SEATCOLUMN);
	pGroup1->AddSubItem(pSeatColumn);

	//显示模式
	CString szModel=_T("");
	if(m_bModel)
		szModel=_C(_T("122"),_T("纯色"));
	else
		szModel=_C(_T("123"),_T("图片"));

	XPropertyGrid* pShowModel=new XPropertyGrid(_C(_T("843"),_T("显示模式")),_variant_t(szModel),
		_C(_T("844"),_T("坐席显示模式：纯色，图片")),ID_SEATMODEL);
	pGroup1->AddSubItem(pShowModel);
	pShowModel->AddOption(_C(_T("122"),_T("纯色")));
	pShowModel->AddOption(_C(_T("123"),_T("图片")));
	pShowModel->AllowEdit(FALSE);
	pShowModel->SetNode(NULL);
	pShowModel->SetSeat(this);

	//颜色
	CMFCPropertyGridColorProperty* pColorProp=new CMFCPropertyGridColorProperty(_C(_T("845"),_T("窗口颜色")),RGB(91,155,213),NULL,
		_C(_T("846"),_T("指定默认的窗口颜色，在纯色模式下生效")),ID_SEATCOLOR);
	pGroup1->AddSubItem(pColorProp);
	pColorProp->EnableOtherButton(_C(_T("149"),_T("其他"))+_T("..."));
	//不清楚为什么 默认总是白色
	pColorProp->EnableAutomaticButton(_C(_T("148"),_T("默认")),RGB(91,155,213));
	pColorProp->SetColor(RGB(m_nColorR,m_nColorG,m_nColorB));

	//透明度
	XPropertyGrid* pTransparent=new XPropertyGrid(_C(_T("855"),_T("透明度")),_variant_t((int)m_nColorA),
		_C(_T("856"),_T("窗口透明度，范围0-255，在纯色模式下生效")),ID_SEATTRANS);
	pGroup1->AddSubItem(pTransparent);
	pTransparent->EnableSpinControl(TRUE,0,255);
	
	//背景图片
	XPropertyGridFile* pPic=new XPropertyGridFile(_C(_T("847"),_T("背景图片")),(_variant_t)m_szPhotoName,ID_SEATPIC,
		_C(_T("848"),_T("窗口背景图片，在图片模式下生效")));
	pGroup1->AddSubItem(pPic);
	pPic->SetNode(NULL);
	pPic->SetSeat(this);


	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup1);
}


BOOL XSeat::OpenSelectPhotoFileDialog(CString& szFileName,CString& szFilePath)
{
	CFileDialog fileDlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,FILTER_PHOTO);

	CString szTitle=_C(_T("79"),_T("选择图片"));
	fileDlg.m_ofn.lpstrTitle=szTitle;

	if(fileDlg.DoModal()==IDOK)
	{
		szFilePath=fileDlg.GetPathName();
		szFileName=fileDlg.GetFileName();
		return TRUE;
	}
	return FALSE;
}