#include "StdAfx.h"
#include "XRibbonBarManage.h"
#include "XDelegateRibbonBarManage.h"
#include "../resource.h"
#include "XTranslationManage.h"
//#include "XStatusBar.h"



CMFCRibbonBar* XRibbonBarManage::m_pTempBar=NULL;
XRibbonBarManage::XRibbonBarManage(void)
{

}

XRibbonBarManage::~XRibbonBarManage(void)
{

}

void XRibbonBarManage::Init()
{
	InitRibbonBar();
	//InitStatusBar();
}

void XRibbonBarManage::InitRibbonBar()
{
	m_wndRibbonBar.Create(GetCWND());
	m_wndRibbonBar.SetDelegate(this);
	InitRibbonBar(&m_wndRibbonBar);
}

//void XRibbonBarManage::InitStatusBar()
//{
//	//״̬��
//	XStatusBar::GetInstance()->Create(GetCWND());
//	XStatusBar::GetInstance()->Init();
//}

void XRibbonBarManage::ResetRibbonBar()
{
	int nPageIndex=m_pDelegate->GetPageIndex();
	if(nPageIndex==1)
	{
		if(NULL==m_pCategorySeatArrage)
			return;
		//�����������
		if(NULL!=m_pPanelSeatRange&&NULL!=m_pBtnArray)
		{
			m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelSeatRange));
			m_pPanelSeatRange=NULL;
			m_pBtnArray=NULL;
		}
		//���ز������
		if(NULL!=m_pPanelOperate&&NULL!=m_pBtnSaveSeat/*&&NULL!=m_pBtnSendSeat*/&&NULL!=m_pBtnClearSeat)
		{
			m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelOperate));
			m_pPanelOperate=NULL;
			m_pBtnSaveSeat=NULL;
			//m_pBtnSendSeat=NULL;
			m_pBtnClearSeat=NULL;
		}
		//////////////////////////////////////////////////////////////////////////
		if(NULL==m_pPanelSeat&&NULL==m_pBtnSeat&&NULL==m_pBtnAlign)
		{
			//��ϯ
			m_pPanelSeat=m_pCategorySeatArrage->AddPanel(_C(_T("97"),_T("��ϯ")));
			m_pPanelSeat->SetJustifyColumns(TRUE);
			m_pPanelSeat->SetCenterColumnVert(TRUE);

			m_pBtnSeat=new CMFCRibbonButton(ID_BTN_SEAT,_C(_T("97"),_T("��ϯ")),AfxGetApp()->LoadIcon(IDI_ICON_SEAT));
			m_pPanelSeat->Add(m_pBtnSeat);

			m_pBtnAlign=new CMFCRibbonButton(ID_BTN_ALIGN,_C(_T("125"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_ALIGN));
			m_pPanelSeat->Add(m_pBtnAlign);
			m_pBtnAlign->SetMenu(IDR_MENU4);
		}
	}
	else if(nPageIndex==2)
	{
		if(NULL==m_pCategorySeatArrage)
			return;
		//�����������
		if(NULL==m_pPanelSeatRange&&NULL==m_pBtnArray)
		{
			//��Χ
			m_pPanelSeatRange=m_pCategorySeatArrage->AddPanel(_C(_T("92"),_T("��Ļ����")));
			m_pPanelSeatRange->SetJustifyColumns(TRUE);
			m_pPanelSeatRange->SetCenterColumnVert(TRUE);

			//����
			m_pBtnArray=new CMFCRibbonButton(ID_BTN_ARRAY,_C(_T("177"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_SCREENARRAY));
			m_pPanelSeatRange->Add(m_pBtnArray);
		}
		//���ز������
		if(NULL==m_pPanelOperate&&NULL==m_pBtnSaveSeat/*&&NULL==m_pBtnSendSeat*/&&NULL==m_pBtnClearSeat)
		{
			//����
			m_pPanelOperate=m_pCategorySeatArrage->AddPanel(_C(_T("98"),_T("����")));
			m_pPanelOperate->SetJustifyColumns(TRUE);
			m_pPanelOperate->SetCenterColumnVert(TRUE);

			//����
			m_pBtnSaveSeat=new CMFCRibbonButton(ID_BTN_SAVESEAT,_C(_T("99"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_SAVESEAT));
			m_pPanelOperate->Add(m_pBtnSaveSeat);

			//����
			//m_pBtnSendSeat=new CMFCRibbonButton(ID_BTN_SENDSEAT,_C(_T("100"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_SENDSEAT));
			//m_pPanelOperate->Add(m_pBtnSendSeat);

			//���
			m_pBtnClearSeat=new CMFCRibbonButton(ID_BTN_CLEARSEAT,_C(_T("107"),_T("���")),AfxGetApp()->LoadIcon(IDI_ICON_CLEAR));
			m_pPanelOperate->Add(m_pBtnClearSeat);
		}
		//////////////////////////////////////////////////////////////////////////
		if(NULL!=m_pPanelSeat&&NULL!=m_pBtnSeat&&NULL!=m_pBtnAlign)
		{
			m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelSeat));
			m_pPanelSeat=NULL;
			m_pBtnSeat=NULL;
			m_pBtnAlign=NULL;
		}
	}
	m_pTempBar->ForceRecalcLayout();
}

void XRibbonBarManage::InitRibbonBar(CMFCRibbonBar* pRibbonBar)
{
	m_pTempBar=pRibbonBar;

	//�Ƴ����пؼ�
	pRibbonBar->RemoveAllCategories();
	pRibbonBar->RemoveAllFromTabs();

	m_pAboutButton=new CMFCRibbonButton(ID_BTN_ABOUT,_T(""),AfxGetApp()->LoadIcon(IDI_ICON_ABOUT));
	pRibbonBar->AddToTabs(m_pAboutButton);

	//��һҳ��ʾ ҳ�����ϯ���ڶ�ҳ��ʾ��Ļ���кͲ���
	//��һҳ-----------------------------------------------------------------
	//��������ǩ
	m_pCategoryMain=pRibbonBar->AddCategory(_C(_T("6"),_T("��ҳ")),0,0);
	m_pCategoryMain->SetData(DWORD_PTR(_T("��ҳ")));

	//����
	m_pPanelMainSet=m_pCategoryMain->AddPanel(_C(_T("7"),_T("����")));
	m_pPanelMainSet->SetJustifyColumns(TRUE);
	m_pPanelMainSet->SetCenterColumnVert(TRUE);

	m_pBtnTheme=new CMFCRibbonButton(ID_BTN_THEME,_C(_T("108"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_THEME));
	m_pPanelMainSet->Add(m_pBtnTheme);
	m_pBtnTheme->SetMenu(IDR_MENU3);

	m_pBtnLanguage=new CMFCRibbonButton(ID_BTN_LANGUAGE,_C(_T("8"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_LANGUE));
	m_pPanelMainSet->Add(m_pBtnLanguage);
	m_pBtnLanguage->SetMenu(IDR_MENU1);

	m_pBtnScale=new CMFCRibbonButton(ID_BTN_SCALE,_C(_T("9"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_ZOOM));
	m_pPanelMainSet->Add(m_pBtnScale);
	m_pBtnScale->SetMenu(IDR_MENU2);

	//////////////////////////////////////////////////////////////////////////
	//�û�����
	m_pPanelUser=m_pCategoryMain->AddPanel(_C(_T("23"),_T("�û�����")));
	m_pPanelUser->SetJustifyColumns(TRUE);
	m_pPanelUser->SetCenterColumnVert(TRUE);

	m_pLogin=new CMFCRibbonButton(IDC_BTN_LOGIN,_C(_T("21"),_T("��¼")),AfxGetApp()->LoadIcon(IDI_ICON_LOGIN));
	m_pPanelUser->Add(m_pLogin);

	m_pPowerManage=new CMFCRibbonButton(IDC_BTN_POWER,_C(_T("34"),_T("Ȩ��")),AfxGetApp()->LoadIcon(IDI_ICON_POWER_1));
	m_pPanelUser->Add(m_pPowerManage);

	m_pFloder=new CMFCRibbonButton(ID_BTN_FOLDER,_C(_T("316"),_T("�ļ���")),AfxGetApp()->LoadIcon(IDI_ICON_FOLDER));
	m_pPanelUser->Add(m_pFloder);

	m_pLoginOut=new CMFCRibbonButton(IDC_BTN_LOGINOUT,_C(_T("22"),_T("ע��")),AfxGetApp()->LoadIcon(IDI_ICON_OUT));
	m_pPanelUser->Add(m_pLoginOut);

	m_pPanelImage=m_pCategoryMain->AddPanel(_C(_T("77"),_T("��ͼ")));
	m_pPanelImage->SetJustifyColumns(TRUE);
	m_pPanelImage->SetCenterColumnVert(TRUE);

	//osd��ͼ
	m_pBtnOSDImage=new CMFCRibbonButton(ID_BTN_OSDIMAGE,_C(_T("78"),_T("OSD��ͼ")),AfxGetApp()->LoadIcon(IDI_ICON_IMAGE));
	m_pPanelImage->Add(m_pBtnOSDImage);

	//�п�
	//m_pPanelControl=m_pCategoryMain->AddPanel(_C(_T("236"),_T("�п�")));
	//m_pPanelControl->SetJustifyColumns(TRUE);
	//m_pPanelControl->SetCenterColumnVert(TRUE);
	//m_pBtnControl=new CMFCRibbonButton(ID_BTN_CONTROL,_C(_T("237"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_CONTROL));
	//m_pPanelControl->Add(m_pBtnControl);
	//////////////////////////////////////////////////////////////////////////
	//Ԥ��
	m_pPanelScene=m_pCategoryMain->AddPanel(_C(_T("239"),_T("Ԥ��")));
	m_pPanelScene->SetJustifyColumns(TRUE);
	m_pPanelScene->SetCenterColumnVert(TRUE);
	m_pBtnScene=new CMFCRibbonButton(ID_BTN_SAVESCENE,_C(_T("240"),_T("����Ԥ��")),AfxGetApp()->LoadIcon(IDI_ICON_SAVESCENE));
	m_pPanelScene->Add(m_pBtnScene);
	//////////////////////////////////////////////////////////////////////////
	//��־
	m_pPanelLog=m_pCategoryMain->AddPanel(_C(_T("251"),_T("��־")));
	m_pPanelLog->SetJustifyColumns(TRUE);
	m_pPanelLog->SetCenterColumnVert(TRUE);
	m_pBtnLog=new CMFCRibbonButton(ID_BTN_LOG,_C(_T("251"),_T("��־")),AfxGetApp()->LoadIcon(IDI_ICON_LOG));
	m_pPanelLog->Add(m_pBtnLog);
	//////////////////////////////////////////////////////////////////////////
	//�豸����Ի���
	m_pPanelDevice=m_pCategoryMain->AddPanel(_C(_T("13"),_T("�豸")));
	m_pPanelDevice->SetJustifyColumns(TRUE);
	m_pPanelDevice->SetCenterColumnVert(TRUE);

	//����������
	m_pBtnUpdate=new CMFCRibbonButton(ID_BTN_UPDATE,_C(_T("269"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_UPDATE));
	m_pPanelDevice->Add(m_pBtnUpdate);

	//����
	m_pBtnNet=new CMFCRibbonButton(IDC_BTN_DEVICENET,_C(_T("18"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_NET));
	m_pPanelDevice->Add(m_pBtnNet);

	//������
	//m_pBtnOpenNet=new CMFCRibbonButton(IDC_BTN_OPENNET,_C(_T("19"),_T("��")),AfxGetApp()->LoadIcon(IDI_ICON_OPEN));
	//m_pPanelDevice->Add(m_pBtnOpenNet);

	//�ر�����
	//m_pBtnCloseNet=new CMFCRibbonButton(IDC_BTN_CLOSENET,_C(_T("20"),_T("�ر�")),AfxGetApp()->LoadIcon(IDI_ICON_CLOSE));
	//m_pPanelDevice->Add(m_pBtnCloseNet);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//��ϯ����������ҳ�浥����ʾ
	//�ڶ�ҳ------------------------------------------------------------------
	//��ϯ����
	m_pCategorySeatArrage=pRibbonBar->AddCategory(_C(_T("76"),_T("��ϯ����")),0,0);
	m_pCategorySeatArrage->SetData(DWORD_PTR(_T("��ϯ����")));

	//����
	m_pPanelMainSeat=m_pCategorySeatArrage->AddPanel(_C(_T("7"),_T("����")));
	m_pPanelMainSeat->SetJustifyColumns(TRUE);
	m_pPanelMainSeat->SetCenterColumnVert(TRUE);

	//����
	m_pBtnBg=new CMFCRibbonButton(ID_BTN_BG,_C(_T("120"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_BG));
	m_pPanelMainSeat->Add(m_pBtnBg);
	//m_pBtnSeatScale->SetMenu(IDR_MENU2);

	//����
	m_pBtnSeatScale=new CMFCRibbonButton(IDC_BTN_SEATSCALE,_C(_T("9"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_ZOOM));
	m_pPanelMainSeat->Add(m_pBtnSeatScale);
	m_pBtnSeatScale->SetMenu(IDR_MENU2);

	//��ϯ
	m_pPanelSeat=m_pCategorySeatArrage->AddPanel(_C(_T("97"),_T("��ϯ")));
	m_pPanelSeat->SetJustifyColumns(TRUE);
	m_pPanelSeat->SetCenterColumnVert(TRUE);

	m_pBtnSeat=new CMFCRibbonButton(ID_BTN_SEAT,_C(_T("97"),_T("��ϯ")),AfxGetApp()->LoadIcon(IDI_ICON_SEAT));
	m_pPanelSeat->Add(m_pBtnSeat);

	m_pBtnAlign=new CMFCRibbonButton(ID_BTN_ALIGN,_C(_T("125"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_ALIGN));
	m_pPanelSeat->Add(m_pBtnAlign);
	m_pBtnAlign->SetMenu(IDR_MENU4);

	//��Χ
	m_pPanelSeatRange=m_pCategorySeatArrage->AddPanel(_C(_T("92"),_T("��Ļ����")));
	m_pPanelSeatRange->SetJustifyColumns(TRUE);
	m_pPanelSeatRange->SetCenterColumnVert(TRUE);

	//����
	m_pBtnArray=new CMFCRibbonButton(ID_BTN_ARRAY,_C(_T("177"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_SCREENARRAY));
	m_pPanelSeatRange->Add(m_pBtnArray);

	//////////////////////////////////////////////////////////////////////////
	//����
	m_pPanelOperate=m_pCategorySeatArrage->AddPanel(_C(_T("98"),_T("����")));
	m_pPanelOperate->SetJustifyColumns(TRUE);
	m_pPanelOperate->SetCenterColumnVert(TRUE);

	//����
	m_pBtnSaveSeat=new CMFCRibbonButton(ID_BTN_SAVESEAT,_C(_T("99"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_SAVESEAT));
	m_pPanelOperate->Add(m_pBtnSaveSeat);

	//����
	//m_pBtnSendSeat=new CMFCRibbonButton(ID_BTN_SENDSEAT,_C(_T("100"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_SENDSEAT));
	//m_pPanelOperate->Add(m_pBtnSendSeat);

	//���
	m_pBtnClearSeat=new CMFCRibbonButton(ID_BTN_CLEARSEAT,_C(_T("107"),_T("���")),AfxGetApp()->LoadIcon(IDI_ICON_CLEAR));
	m_pPanelOperate->Add(m_pBtnClearSeat);

	//////////////////////////////////////////////////////////////////////////
	//��ʼ���� �ڶ�ҳ��ť
	//�����������
	if(NULL!=m_pPanelSeatRange&&NULL!=m_pBtnArray)
	{
		m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelSeatRange));
		m_pPanelSeatRange=NULL;
		m_pBtnArray=NULL;
	}
	//���ز������
	if(NULL!=m_pPanelOperate&&NULL!=m_pBtnSaveSeat/*&&NULL!=m_pBtnSendSeat*/&&NULL!=m_pBtnClearSeat)
	{
		m_pCategorySeatArrage->RemovePanel(m_pCategorySeatArrage->GetPanelIndex(m_pPanelOperate));
		m_pPanelOperate=NULL;
		m_pBtnSaveSeat=NULL;
		//m_pBtnSendSeat=NULL;
		m_pBtnClearSeat=NULL;
	}

	//����ҳ�����л�--------------------------------------------------------------
	m_pCategoryMatrix=pRibbonBar->AddCategory(_C(_T("252"),_T("�����л�")),0,0);
	m_pCategoryMatrix->SetData(DWORD_PTR(_T("�����л�")));

	//�ڵ�����
	m_pPanelMatrixArray=m_pCategoryMatrix->AddPanel(_C(_T("253"),_T("����")));
	m_pPanelMatrixArray->SetJustifyColumns(TRUE);
	m_pPanelMatrixArray->SetCenterColumnVert(TRUE);
	//����
	m_pBtnMatrixArray=new CMFCRibbonButton(ID_BTN_MATRIXARRAY,_C(_T("253"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_SCREENARRAY));
	m_pPanelMatrixArray->Add(m_pBtnMatrixArray);
	//�������
	m_pPanelMatrixScale=m_pCategoryMatrix->AddPanel(_C(_T("7"),_T("����")));
	m_pPanelMatrixScale->SetJustifyColumns(TRUE);
	m_pPanelMatrixScale->SetCenterColumnVert(TRUE);
	//����
	m_pBtnMatrixScale=new CMFCRibbonButton(ID_BTN_MATRIXSCALE,_C(_T("9"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_ZOOM));
	m_pPanelMatrixScale->Add(m_pBtnMatrixScale);
	m_pBtnMatrixScale->SetMenu(IDR_MENU2);


	//ƴ��ҳ��--------------------------------------------------------------
	m_pCategorySplit=pRibbonBar->AddCategory(_C(_T("325"),_T("ƴ��")),0,0);
	m_pCategorySplit->SetData(DWORD_PTR(_T("ƴ��")));
	//���ƴ����
	m_pPanelOne=m_pCategorySplit->AddPanel(_C(_T("326"),_T("�½�")));
	m_pPanelOne->SetJustifyColumns(TRUE);
	m_pPanelOne->SetCenterColumnVert(TRUE);
	//�½�
	m_pBtnAdd=new CMFCRibbonButton(ID_BTN_ADDSPLIT,_C(_T("327"),_T("�½�ƴ��")),AfxGetApp()->LoadIcon(IDI_ICON_ADDSPLIT));
	m_pPanelOne->Add(m_pBtnAdd);
	//����
	m_pPanelTwo=m_pCategorySplit->AddPanel(_C(_T("7"),_T("����")));
	m_pPanelTwo->SetJustifyColumns(TRUE);
	m_pPanelTwo->SetCenterColumnVert(TRUE);
	//����
	m_pBtnSplitScale=new CMFCRibbonButton(ID_BTN_SPLITSCALE,_C(_T("9"),_T("����")),AfxGetApp()->LoadIcon(IDI_ICON_ZOOM));
	m_pPanelTwo->Add(m_pBtnSplitScale);
	m_pBtnSplitScale->SetMenu(IDR_MENU2);
	//����
	m_pPanelThree=m_pCategorySplit->AddPanel(_C(_T("527"),_T("����")));
	m_pPanelThree->SetJustifyColumns(TRUE);
	m_pPanelThree->SetCenterColumnVert(TRUE);

	//����ģʽ
	//m_pBtnAddModel=new CMFCRibbonButton(ID_BTN_ADDMODEL,_C(_T("335"),_T("����ģʽ")),AfxGetApp()->LoadIcon(IDI_ICON_SIGNALMODEL));
	//m_pPanelThree->Add(m_pBtnAddModel);
	//m_pBtnAddModel->SetMenu(IDR_MENU6);
	//����ģʽ
	m_pBtnLimitModel=new CMFCRibbonButton(ID_BTN_LIMITMODEL,_C(_T("338"),_T("����ģʽ")),AfxGetApp()->LoadIcon(IDI_ICON_LEVEL));
	m_pPanelThree->Add(m_pBtnLimitModel);
	m_pBtnLimitModel->SetMenu(IDR_MENU5);

	m_pBtnQuickTop=new CMFCRibbonButton(ID_MENU_QUICKTOP,_C(_T("343"),_T("�����ö�")),AfxGetApp()->LoadIcon(IDI_ICON_QUICKTOP));
	m_pPanelThree->Add(m_pBtnQuickTop);
	//����ź�
	m_pBtnClearSignal=new CMFCRibbonButton(ID_BTN_CLEARSIGNAL,_C(_T("107"),_T("���")),AfxGetApp()->LoadIcon(IDI_ICON_CLEAR));
	m_pPanelThree->Add(m_pBtnClearSignal);
	//��������
	m_pBtnSplitScene=new CMFCRibbonButton(ID_MENU_SAVESCENE,_C(_T("350"),_T("��������")),AfxGetApp()->LoadIcon(IDI_ICON_SAVESCENE));
	m_pPanelThree->Add(m_pBtnSplitScene);

	//��������
	pRibbonBar->ForceRecalcLayout();
}

CWnd* XRibbonBarManage::GetCWND()
{
	return m_pDelegate->GetCWND();
}

void XRibbonBarManage::UpdateControlDataShowOfAll()
{

}

void XRibbonBarManage::ReloadInterface()
{
	InitRibbonBar(&m_wndRibbonBar);
	UpdateControlDataShowOfAll();
}

void XRibbonBarManage::RibbonBarShowCategory(DWORD_PTR dwData)
{
	m_pDelegate->RibbonBarShowCategory(dwData);
}

//void XRibbonBarManage::SetCurUserName(CString szUserName)
//{
//	m_szUserName=szUserName;
//}

//void XRibbonBarManage::SetStatusInfo()
//{
	//CString szTemp=XTranslationManage::GetInstance()->_C(_T("33"));

	//CString szInformation;
	//szInformation.Format(_T("%s %s"),m_szUserName,szTemp);

	//m_wndStatusBar.SetInformation(szInformation);

	//CMFCRibbonBaseElement* pUser=m_wndStatusBar.FindElement(ID_STATUSBAR_USER);
	//if(NULL!=pUser)
	//{
	//	pUser->SetText(m_szUserName);
	//}
//}

void XRibbonBarManage::SetActiveCategory(int nBaseIndex)
{
	if(nBaseIndex==0)
	{
		if(NULL!=m_pCategoryMain)
			m_wndRibbonBar.SetActiveCategory(m_pCategoryMain);
	}
	else if(nBaseIndex==1)
	{
		if(NULL!=m_pCategorySeatArrage)
			m_wndRibbonBar.SetActiveCategory(m_pCategorySeatArrage);
	}
	else if(nBaseIndex==2)
	{
		if(NULL!=m_pCategoryMatrix)
			m_wndRibbonBar.SetActiveCategory(m_pCategoryMatrix);
	}
	else
	{
		//����ƴ����
		if(NULL!=m_pCategorySplit)
			m_wndRibbonBar.SetActiveCategory(m_pCategorySplit);
	}
}

//////////////////////////////////////////////////////////////////////////
void XRibbonBarManage::ControlDataChange(XDATATYPE type)
{

}

void XRibbonBarManage::UpdateControlDataShow(XDATATYPE type)
{
	switch(type)
	{
		case XDATATYPE_ALL:
			{
				UpdateControlDataShowOfAll();
			}
			break;
		case XDATATYPE_LOGIN:
			{
				m_pDelegate->UpdateControlDataShow(type,m_pLogin);
			}
			break;
		case XDATATYPE_LOGINOUT:
			{
				m_pDelegate->UpdateControlDataShow(type,m_pLoginOut);
			}
			break;

		default:
			break;
	}
}
