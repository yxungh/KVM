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
					_M(_T("161"),_T("名称已存在！"),MB_OK);
					return;
				}
				
				//更改名称
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
					_M(_T("161"),_T("名称已存在！"),MB_OK);
					return;
				}

				//更改名称
				XNodeGroupInfo nodeGroupInfo;
				nodeGroupInfo.SetGroupID(GetGroupID());
				nodeGroupInfo.SetGroupName(szGroupName);
				//更改主副屏组名称
				XSendDataManage::GetInstance()->AddSendDataOfUpdataMasterNodeGroupName(nodeGroupInfo);
			}
		}
		break;
	case ID_NODEGROUPMASTER:
		{
			int nMaster=(_variant_t)(pProperty->GetValue());
			if(nMaster!=0)
			{
				//设置坐席主节点
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
	XPropertyGrid* pGroup1=new XPropertyGrid(GetTranslationString(_T("750"),_T("基本信息")));

	XPropertyGrid* pType=new XPropertyGrid(GetTranslationString(_T("857"),_T("组类别")),_variant_t(GetTranslationString(_T("221"),_T("主副屏节点组"))),
										   GetTranslationString(_T("958"),_T("节点组类型：普通节点组和主副屏节点组")));
	pType->Enable(FALSE);
	pGroup1->AddSubItem(pType);

	//ID
	XPropertyGrid* pGroupID=new XPropertyGrid(GetTranslationString(_T("773"),_T("ID")),_variant_t(GetGroupID()),
											  GetTranslationString(_T("824"),_T("节点组ID")),ID_MAINSECGROUPID);
	pGroupID->Enable(FALSE);
	pGroup1->AddSubItem(pGroupID);

	//名称
	XPropertyGrid* pGroupName=new XPropertyGrid(GetTranslationString(_T("753"),_T("名称")),_variant_t(GetGroupName()),
												GetTranslationString(_T("825"),_T("节点组名称")),ID_MAINSECGROUPNAME);
	pGroup1->AddSubItem(pGroupName);


	//类型
	CString szType=GetTranslationString(_T("759"),_T("输入"));
	XPropertyGrid* pGroupType=new XPropertyGrid(GetTranslationString(_T("757"),_T("类型")),_variant_t(szType),
												GetTranslationString(_T("826"),_T("节点组类型，输入或输出")));
	pGroupType->Enable(FALSE);
	pGroup1->AddSubItem(pGroupType);

	//主节点
	XPropertyGrid* pGroupMaster=new XPropertyGrid(GetTranslationString(_T("827"),_T("主节点")),_variant_t(GetMaster()),
												  GetTranslationString(_T("828"),_T("坐席中主节点")),ID_MAINSECGROUPMASTER);
	//pGroupMaster->Enable(FALSE);
	pGroup1->AddSubItem(pGroupMaster);

	//矩阵排列
	XPropertyGrid* pGroupMatrix=new XPropertyGrid(GetTranslationString(_T("829"),_T("排列")),_variant_t(GetMatrix()),
												  GetTranslationString(_T("830"),_T("坐席中节点排列")),ID_MAINSECGROUPMATRIX);
	pGroupMatrix->Enable(FALSE);
	pGroup1->AddSubItem(pGroupMatrix);

	//创建者
	XPropertyGrid* pGroupCreator=new XPropertyGrid(GetTranslationString(_T("831"),_T("创建者")),_variant_t(GetCreatorID()),
												   GetTranslationString(_T("832"),_T("创建节点组的用户ID")));
	pGroupCreator->Enable(FALSE);
	pGroup1->AddSubItem(pGroupCreator);

	//创建时间
	time_t CreateTime=GetCreateTime();
	CString szCreateTime=HandleCalculate::GetTimeBySecond(CreateTime);
	XPropertyGrid* pGroupCreateTime=new XPropertyGrid(GetTranslationString(_T("833"),_T("创建时间")),_variant_t(szCreateTime),
													  GetTranslationString(_T("834"),_T("创建时间")));
	pGroupCreateTime->Enable(FALSE);
	pGroup1->AddSubItem(pGroupCreateTime);




	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup1);
}

void XNodeGroupInfo::SetNodeGroupInfo()
{
	XPropertyGrid* pGroup1=new XPropertyGrid(GetTranslationString(_T("750"),_T("基本信息")));

	XPropertyGrid* pType=new XPropertyGrid(GetTranslationString(_T("857"),_T("组类别")),_variant_t(GetTranslationString(_T("220"),_T("普通节点组"))),
										   GetTranslationString(_T("958"),_T("节点组类型：普通节点组和主副屏节点组")));
	pType->Enable(FALSE);
	pGroup1->AddSubItem(pType);

	XPropertyGrid* pGroupID=new XPropertyGrid(GetTranslationString(_T("773"),_T("ID")),_variant_t(GetGroupID()),
											 GetTranslationString(_T("824"),_T("节点组ID")),ID_NODEGROUPID);
	pGroupID->Enable(FALSE);
	pGroup1->AddSubItem(pGroupID);

	//名称
	XPropertyGrid* pGroupName=new XPropertyGrid(GetTranslationString(_T("753"),_T("名称")),_variant_t(GetGroupName()),
											   GetTranslationString(_T("825"),_T("节点组名称")),ID_NODEGROUPNAME);
	//pGroupName->SetNodeGroup(this);
	pGroup1->AddSubItem(pGroupName);

	//类型
	CString szType=_T("");
	if(GetType()==1)
		szType=GetTranslationString(_T("759"),_T("输入"));
	else if(GetType()==3)
		szType=GetTranslationString(_T("760"),_T("输出"));

	XPropertyGrid* pGroupType=new XPropertyGrid(GetTranslationString(_T("757"),_T("类型")),_variant_t(szType),
												GetTranslationString(_T("826"),_T("节点组类型，输入或输出")));
	pGroupType->Enable(FALSE);
	pGroup1->AddSubItem(pGroupType);

	//主节点
	XPropertyGrid* pGroupMaster=new XPropertyGrid(GetTranslationString(_T("827"),_T("主节点")),_variant_t(GetMaster()),
												  GetTranslationString(_T("828"),_T("坐席中主节点")),ID_NODEGROUPMASTER);
	pGroup1->AddSubItem(pGroupMaster);

	//矩阵排列
	XPropertyGrid* pGroupMatrix=new XPropertyGrid(GetTranslationString(_T("829"),_T("排列")),_variant_t(GetMatrix()),
												  GetTranslationString(_T("830"),_T("坐席中节点排列")),ID_NODEGROUPMATRIX);
	pGroupMatrix->Enable(FALSE);
	pGroup1->AddSubItem(pGroupMatrix);

	//在线
	CString szOnLine=_T("");
	if(GetOnLine())
		szOnLine=_T("True");
	else
		szOnLine=_T("False");

	XPropertyGrid* pGroupOnLine=new XPropertyGrid(GetTranslationString(_T("835"),_T("在线")),_variant_t(szOnLine),
												  GetTranslationString(_T("836"),_T("在线")));
	pGroupOnLine->Enable(FALSE);
	pGroup1->AddSubItem(pGroupOnLine);

	//创建者
	XPropertyGrid* pGroupCreator=new XPropertyGrid(GetTranslationString(_T("831"),_T("创建者")),_variant_t(GetCreatorID()),
												  GetTranslationString(_T("832"),_T("创建节点组的用户ID")),ID_NODEGROUPCREATOR);
	pGroupCreator->Enable(FALSE);
	pGroup1->AddSubItem(pGroupCreator);

	//创建时间
	time_t CreateTime=GetCreateTime();
	CString szCreateTime=HandleCalculate::GetTimeBySecond(CreateTime);
	XPropertyGrid* pGroupCreateTime=new XPropertyGrid(GetTranslationString(_T("833"),_T("创建时间")),_variant_t(szCreateTime),
												      GetTranslationString(_T("834"),_T("创建时间")));
	pGroupCreateTime->Enable(FALSE);
	pGroup1->AddSubItem(pGroupCreateTime);

	
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup1);
}