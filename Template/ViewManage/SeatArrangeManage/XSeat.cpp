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
			//����X
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
			//Ĭ����ɫ����ʱ�����жϣ�
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
			if(szModel==_C(_T("122"),_T("��ɫ")))
			{
				SetModel(TRUE);
			}
			else if(_C(_T("123"),_T("ͼƬ")))
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

	//����Ԥ��ǽ
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
			if(szModel==_C(_T("122"),_T("��ɫ")))
			{
				SetModel(TRUE);
			}
			else if(_C(_T("123"),_T("ͼƬ")))
			{
				SetModel(FALSE);
			}
		}
		break;
	default:
		break;
	}
	//����Ԥ��ǽ
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
				//����ͼƬ������·��
				if(!FileHandle::copyFile(szFilePath,HandlePath::GetMapPhotoPath(szFileName)))
				{
					_M(_T("121"),_T("��������ͼƬʧ�ܣ�"),MB_OK);
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

	//����Ԥ��ǽ
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
				//����ͼƬ������·��
				if(!FileHandle::copyFile(szFilePath,HandlePath::GetMapPhotoPath(szFileName)))
				{
					_M(_T("121"),_T("��������ͼƬʧ�ܣ�"),MB_OK);
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

	//����Ԥ��ǽ
	if(NULL!=m_pManage)
		m_pManage->UpdateMultiWindowByPropertyChange(this,nData);
}

void XSeat::SetPropertiesWnd()
{
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();

	XPropertyGrid* pGroup1=new XPropertyGrid(_C(_T("750"),_T("������Ϣ")));

	//����
	XPropertyGrid* pSeatName=new XPropertyGrid(_C(_T("837"),_T("����")),_variant_t(GetGroupName()),
		_C(_T("838"),_T("��ϯ����")),ID_SEATNAME);
	pGroup1->AddSubItem(pSeatName);

	//����X
	XPropertyGrid* pRectX=new XPropertyGrid(_T("X"),_variant_t((int)m_rect.X),
		_C(_T("849"),_T("��ϯλ�����Ͻ�X���꣬X����0��С��800")),ID_SEATRECTX);
	pGroup1->AddSubItem(pRectX);

	int nMaxX=800-(int)m_rect.Width;
	pRectX->EnableSpinControl(TRUE,0,nMaxX);

	//����Y
	XPropertyGrid* pRectY=new XPropertyGrid(_T("Y"),_variant_t((int)m_rect.Y),
		_C(_T("850"),_T("��ϯλ�����Ͻ�X���꣬X����0��С��800")),ID_SEATRECTY);
	pGroup1->AddSubItem(pRectY);

	int nMaxY=810-(int)m_rect.Height;
	pRectY->EnableSpinControl(TRUE,0,nMaxY);

	//����W
	XPropertyGrid* pRectW=new XPropertyGrid(_C(_T("851"),_T("���")),_variant_t((int)m_rect.Width),
		_C(_T("852"),_T("��ϯ���ڿ��")),ID_SEATRECTW);
	pGroup1->AddSubItem(pRectW);

	int nMaxW=800-(int)m_rect.X;
	pRectW->EnableSpinControl(TRUE,0,nMaxW);

	//����H
	XPropertyGrid* pRectH=new XPropertyGrid(_C(_T("853"),_T("�߶�")),_variant_t((int)m_rect.Height),
		_C(_T("854"),_T("��ϯ���ڸ߶�")),ID_SEATRECTH);
	pGroup1->AddSubItem(pRectH);

	int nMaxH=810-(int)m_rect.Y;
	pRectH->EnableSpinControl(TRUE,0,nMaxH);

	//��
	XPropertyGrid* pSeatRow=new XPropertyGrid(_C(_T("839"),_T("��")),_variant_t(m_nSeatRow),
		_C(_T("840"),_T("��ϯ��Ļ��������")),ID_SEATROW);
	pGroup1->AddSubItem(pSeatRow);

	//��
	XPropertyGrid* pSeatColumn=new XPropertyGrid(_C(_T("841"),_T("��")),_variant_t(m_nSeatColumn),
		_C(_T("842"),_T("��ϯ��Ļ��������")),ID_SEATCOLUMN);
	pGroup1->AddSubItem(pSeatColumn);

	//��ʾģʽ
	CString szModel=_T("");
	if(m_bModel)
		szModel=_C(_T("122"),_T("��ɫ"));
	else
		szModel=_C(_T("123"),_T("ͼƬ"));

	XPropertyGrid* pShowModel=new XPropertyGrid(_C(_T("843"),_T("��ʾģʽ")),_variant_t(szModel),
		_C(_T("844"),_T("��ϯ��ʾģʽ����ɫ��ͼƬ")),ID_SEATMODEL);
	pGroup1->AddSubItem(pShowModel);
	pShowModel->AddOption(_C(_T("122"),_T("��ɫ")));
	pShowModel->AddOption(_C(_T("123"),_T("ͼƬ")));
	pShowModel->AllowEdit(FALSE);
	pShowModel->SetNode(NULL);
	pShowModel->SetSeat(this);

	//��ɫ
	CMFCPropertyGridColorProperty* pColorProp=new CMFCPropertyGridColorProperty(_C(_T("845"),_T("������ɫ")),RGB(91,155,213),NULL,
		_C(_T("846"),_T("ָ��Ĭ�ϵĴ�����ɫ���ڴ�ɫģʽ����Ч")),ID_SEATCOLOR);
	pGroup1->AddSubItem(pColorProp);
	pColorProp->EnableOtherButton(_C(_T("149"),_T("����"))+_T("..."));
	//�����Ϊʲô Ĭ�����ǰ�ɫ
	pColorProp->EnableAutomaticButton(_C(_T("148"),_T("Ĭ��")),RGB(91,155,213));
	pColorProp->SetColor(RGB(m_nColorR,m_nColorG,m_nColorB));

	//͸����
	XPropertyGrid* pTransparent=new XPropertyGrid(_C(_T("855"),_T("͸����")),_variant_t((int)m_nColorA),
		_C(_T("856"),_T("����͸���ȣ���Χ0-255���ڴ�ɫģʽ����Ч")),ID_SEATTRANS);
	pGroup1->AddSubItem(pTransparent);
	pTransparent->EnableSpinControl(TRUE,0,255);
	
	//����ͼƬ
	XPropertyGridFile* pPic=new XPropertyGridFile(_C(_T("847"),_T("����ͼƬ")),(_variant_t)m_szPhotoName,ID_SEATPIC,
		_C(_T("848"),_T("���ڱ���ͼƬ����ͼƬģʽ����Ч")));
	pGroup1->AddSubItem(pPic);
	pPic->SetNode(NULL);
	pPic->SetSeat(this);


	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup1);
}


BOOL XSeat::OpenSelectPhotoFileDialog(CString& szFileName,CString& szFilePath)
{
	CFileDialog fileDlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,FILTER_PHOTO);

	CString szTitle=_C(_T("79"),_T("ѡ��ͼƬ"));
	fileDlg.m_ofn.lpstrTitle=szTitle;

	if(fileDlg.DoModal()==IDOK)
	{
		szFilePath=fileDlg.GetPathName();
		szFileName=fileDlg.GetFileName();
		return TRUE;
	}
	return FALSE;
}