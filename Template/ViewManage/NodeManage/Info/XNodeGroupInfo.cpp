#include "stdafx.h"
#include "XNodeGroupInfo.h"
#include "XPropertiesWnd.h"
#include "XPropertyGrid.h"
#include "XProprtyGridFile.h"
#include "XTranslationManage.h"
#include "HandleCalculate.h"
#include "XSendDataManage.h"
#include "XLeftWnd.h"
#include "XConstantData.h"
#include "XNodeGroup.h"
#include "XMessageBox.h"


XNodeGroupInfo::XNodeGroupInfo()
{

}

XNodeGroupInfo::~XNodeGroupInfo()
{
	m_VecArrage.clear();
}

CString XNodeGroupInfo::GetTranslationString(CString szKey,CString szDefault/*=_T("")*/)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

void XNodeGroupInfo::OnPropertyChanged(CMFCPropertyGridProperty* pProperty)
{
	int nData=(int)pProperty->GetData();

	switch(nData)
	{
	case ID_NODEGROUPNAME:
		{
			CString szGroupName=(_variant_t)(pProperty->GetValue());
			if(szGroupName!=_T(""))
			{

				if(XLeftWnd::GetInstance()->DecidedGroupNameExist(szGroupName))
				{
					_M(_T("161"),_T("�����Ѵ��ڣ�"),MB_OK);
					return;
				}
				
				//��������
				XNodeGroupInfo nodeGroupInfo;
				nodeGroupInfo.SetGroupID(GetGroupID());
				nodeGroupInfo.SetGroupName(szGroupName);
				XSendDataManage::GetInstance()->AddSendDataOfUpdataNodeGroupName(nodeGroupInfo);
			}
		}
		break;
	case ID_MAINSECGROUPNAME:
		{
			CString szGroupName=(_variant_t)(pProperty->GetValue());
			if(szGroupName!=_T(""))
			{
				if(XLeftWnd::GetInstance()->DecidedGroupNameExist(szGroupName))
				{
					_M(_T("161"),_T("�����Ѵ��ڣ�"),MB_OK);
					return;
				}

				//��������
				XNodeGroupInfo nodeGroupInfo;
				nodeGroupInfo.SetGroupID(GetGroupID());
				nodeGroupInfo.SetGroupName(szGroupName);
				//����������������
				XSendDataManage::GetInstance()->AddSendDataOfUpdataMasterNodeGroupName(nodeGroupInfo);
			}
		}
		break;
	case ID_NODEGROUPMASTER:
		{
			int nMaster=(_variant_t)(pProperty->GetValue());
			if(nMaster!=0)
			{
				//������ϯ���ڵ�
				XNodeGroupInfo nodeGroupInfo;

				nodeGroupInfo.SetGroupID(GetGroupID());
				nodeGroupInfo.SetMaster(nMaster);
				XSendDataManage::GetInstance()->AddSendDataOfUpdataSeatMasterNode(nodeGroupInfo);
			}
		}
		break;
	default:
		break;
	}
}

void XNodeGroupInfo::SetProprityWnd()
{
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();

	if(m_bMainSecond)
	{
		SetMainSecondGroupInfo();
	}
	else
	{
		SetNodeGroupInfo();
	}
}

void XNodeGroupInfo::SetMainSecondGroupInfo()
{
	XPropertyGrid* pGroup1=new XPropertyGrid(GetTranslationString(_T("750"),_T("������Ϣ")));

	XPropertyGrid* pType=new XPropertyGrid(GetTranslationString(_T("857"),_T("�����")),_variant_t(GetTranslationString(_T("221"),_T("�������ڵ���"))),
										   GetTranslationString(_T("958"),_T("�ڵ������ͣ���ͨ�ڵ�����������ڵ���")));
	pType->Enable(FALSE);
	pGroup1->AddSubItem(pType);

	//ID
	XPropertyGrid* pGroupID=new XPropertyGrid(GetTranslationString(_T("773"),_T("ID")),_variant_t(GetGroupID()),
											  GetTranslationString(_T("824"),_T("�ڵ���ID")),ID_MAINSECGROUPID);
	pGroupID->Enable(FALSE);
	pGroup1->AddSubItem(pGroupID);

	//����
	XPropertyGrid* pGroupName=new XPropertyGrid(GetTranslationString(_T("753"),_T("����")),_variant_t(GetGroupName()),
												GetTranslationString(_T("825"),_T("�ڵ�������")),ID_MAINSECGROUPNAME);
	pGroup1->AddSubItem(pGroupName);


	//����
	CString szType=GetTranslationString(_T("759"),_T("����"));
	XPropertyGrid* pGroupType=new XPropertyGrid(GetTranslationString(_T("757"),_T("����")),_variant_t(szType),
												GetTranslationString(_T("826"),_T("�ڵ������ͣ���������")));
	pGroupType->Enable(FALSE);
	pGroup1->AddSubItem(pGroupType);

	//���ڵ�
	XPropertyGrid* pGroupMaster=new XPropertyGrid(GetTranslationString(_T("827"),_T("���ڵ�")),_variant_t(GetMaster()),
												  GetTranslationString(_T("828"),_T("��ϯ�����ڵ�")),ID_MAINSECGROUPMASTER);
	//pGroupMaster->Enable(FALSE);
	pGroup1->AddSubItem(pGroupMaster);

	//��������
	XPropertyGrid* pGroupMatrix=new XPropertyGrid(GetTranslationString(_T("829"),_T("����")),_variant_t(GetMatrix()),
												  GetTranslationString(_T("830"),_T("��ϯ�нڵ�����")),ID_MAINSECGROUPMATRIX);
	pGroupMatrix->Enable(FALSE);
	pGroup1->AddSubItem(pGroupMatrix);

	//������
	XPropertyGrid* pGroupCreator=new XPropertyGrid(GetTranslationString(_T("831"),_T("������")),_variant_t(GetCreatorID()),
												   GetTranslationString(_T("832"),_T("�����ڵ�����û�ID")));
	pGroupCreator->Enable(FALSE);
	pGroup1->AddSubItem(pGroupCreator);

	//����ʱ��
	time_t CreateTime=GetCreateTime();
	CString szCreateTime=HandleCalculate::GetTimeBySecond(CreateTime);
	XPropertyGrid* pGroupCreateTime=new XPropertyGrid(GetTranslationString(_T("833"),_T("����ʱ��")),_variant_t(szCreateTime),
													  GetTranslationString(_T("834"),_T("����ʱ��")));
	pGroupCreateTime->Enable(FALSE);
	pGroup1->AddSubItem(pGroupCreateTime);




	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup1);
}

void XNodeGroupInfo::SetNodeGroupInfo()
{
	XPropertyGrid* pGroup1=new XPropertyGrid(GetTranslationString(_T("750"),_T("������Ϣ")));

	XPropertyGrid* pType=new XPropertyGrid(GetTranslationString(_T("857"),_T("�����")),_variant_t(GetTranslationString(_T("220"),_T("��ͨ�ڵ���"))),
										   GetTranslationString(_T("958"),_T("�ڵ������ͣ���ͨ�ڵ�����������ڵ���")));
	pType->Enable(FALSE);
	pGroup1->AddSubItem(pType);

	XPropertyGrid* pGroupID=new XPropertyGrid(GetTranslationString(_T("773"),_T("ID")),_variant_t(GetGroupID()),
											 GetTranslationString(_T("824"),_T("�ڵ���ID")),ID_NODEGROUPID);
	pGroupID->Enable(FALSE);
	pGroup1->AddSubItem(pGroupID);

	//����
	XPropertyGrid* pGroupName=new XPropertyGrid(GetTranslationString(_T("753"),_T("����")),_variant_t(GetGroupName()),
											   GetTranslationString(_T("825"),_T("�ڵ�������")),ID_NODEGROUPNAME);
	//pGroupName->SetNodeGroup(this);
	pGroup1->AddSubItem(pGroupName);

	//����
	CString szType=_T("");
	if(GetType()==1)
		szType=GetTranslationString(_T("759"),_T("����"));
	else if(GetType()==3)
		szType=GetTranslationString(_T("760"),_T("���"));

	XPropertyGrid* pGroupType=new XPropertyGrid(GetTranslationString(_T("757"),_T("����")),_variant_t(szType),
												GetTranslationString(_T("826"),_T("�ڵ������ͣ���������")));
	pGroupType->Enable(FALSE);
	pGroup1->AddSubItem(pGroupType);

	//���ڵ�
	XPropertyGrid* pGroupMaster=new XPropertyGrid(GetTranslationString(_T("827"),_T("���ڵ�")),_variant_t(GetMaster()),
												  GetTranslationString(_T("828"),_T("��ϯ�����ڵ�")),ID_NODEGROUPMASTER);
	pGroup1->AddSubItem(pGroupMaster);

	//��������
	XPropertyGrid* pGroupMatrix=new XPropertyGrid(GetTranslationString(_T("829"),_T("����")),_variant_t(GetMatrix()),
												  GetTranslationString(_T("830"),_T("��ϯ�нڵ�����")),ID_NODEGROUPMATRIX);
	pGroupMatrix->Enable(FALSE);
	pGroup1->AddSubItem(pGroupMatrix);

	//����
	CString szOnLine=_T("");
	if(GetOnLine())
		szOnLine=_T("True");
	else
		szOnLine=_T("False");

	XPropertyGrid* pGroupOnLine=new XPropertyGrid(GetTranslationString(_T("835"),_T("����")),_variant_t(szOnLine),
												  GetTranslationString(_T("836"),_T("����")));
	pGroupOnLine->Enable(FALSE);
	pGroup1->AddSubItem(pGroupOnLine);

	//������
	XPropertyGrid* pGroupCreator=new XPropertyGrid(GetTranslationString(_T("831"),_T("������")),_variant_t(GetCreatorID()),
												  GetTranslationString(_T("832"),_T("�����ڵ�����û�ID")),ID_NODEGROUPCREATOR);
	pGroupCreator->Enable(FALSE);
	pGroup1->AddSubItem(pGroupCreator);

	//����ʱ��
	time_t CreateTime=GetCreateTime();
	CString szCreateTime=HandleCalculate::GetTimeBySecond(CreateTime);
	XPropertyGrid* pGroupCreateTime=new XPropertyGrid(GetTranslationString(_T("833"),_T("����ʱ��")),_variant_t(szCreateTime),
												      GetTranslationString(_T("834"),_T("����ʱ��")));
	pGroupCreateTime->Enable(FALSE);
	pGroup1->AddSubItem(pGroupCreateTime);

	
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup1);
}