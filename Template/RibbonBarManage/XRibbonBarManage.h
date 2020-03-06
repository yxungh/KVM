#pragma once

#include "XBaseRibbonBarManage.h"
#include "XRibbonBar.h"
#include "XDelegateRibbonBar.h"
#include "XConstant.h"

class XRibbonBarManage: public XBaseRibbonBarManage,XDelegateRibbonBar
{
public:
	XRibbonBarManage(void);
	~XRibbonBarManage(void);

	//��ʼ��
	virtual void Init();

	//�ؼ����ݸı�
	virtual void ControlDataChange(XDATATYPE type);

	//���ؽ���
	virtual void ReloadInterface();

	//�����������͸��¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type);

	//Ribbon��ʾ�����
	virtual void RibbonBarShowCategory(DWORD_PTR dwData);

	//virtual void SetStatusInfo();

	//virtual void SetCurUserName(CString szUserName);

	virtual void SetActiveCategory(int nBaseIndex);

	virtual void ResetRibbonBar();


private:

	//��ʼ��RibbonBar
	void InitRibbonBar();

	//��ʼ��״̬��
	//void InitStatusBar();

	//��ʼ��RibbonBar
	void InitRibbonBar(CMFCRibbonBar* pRibbonBar);

	BOOL InitImageList();

	//��ȡCWnd
	CWnd* GetCWND();

	//�������пؼ�������ʾ
	void UpdateControlDataShowOfAll();

private:

	CString m_szUserName=_T("");

	//������
	XRibbonBar m_wndRibbonBar;

	static CMFCRibbonBar* m_pTempBar;

	//״̬��
	//CMFCRibbonStatusBar m_wndStatusBar;

	//����
	CMFCRibbonButton* m_pAboutButton=NULL;
	//��ҳ
	CMFCRibbonCategory* m_pCategoryMain=NULL;
	//����
	CMFCRibbonPanel* m_pPanelMainSet=NULL;
	//����
	CMFCRibbonButton* m_pBtnLanguage=NULL;
	//����
	CMFCRibbonButton* m_pBtnTheme=NULL;
	//����
	CMFCRibbonButton* m_pBtnScale=NULL;
	//��¼
	CMFCRibbonPanel* m_pPanelLogin=NULL;
	//��½
	CMFCRibbonButton* m_pLogin=NULL;
	//ע��
	CMFCRibbonButton* m_pLoginOut=NULL;

	//�û�����
	CMFCRibbonPanel* m_pPanelUser=NULL;
	//�û�Ȩ��
	CMFCRibbonButton* m_pPowerManage=NULL;
	//��ȫ����
	CMFCRibbonButton* m_pPowerSecurity=NULL;
	//�ļ���
	CMFCRibbonButton* m_pFloder=NULL;

	//////////////////////////////////////////////////////////////////////////
	//��ͼ
	CMFCRibbonPanel* m_pPanelImage=NULL;
	//OSD��ͼ
	CMFCRibbonButton* m_pBtnOSDImage=NULL;
	//////////////////////////////////////////////////////////////////////////
	////�п�
	//CMFCRibbonPanel* m_pPanelControl=NULL;
	////����
	//CMFCRibbonButton* m_pBtnControl=NULL;
	//////////////////////////////////////////////////////////////////////////
	//����Ԥ��
	CMFCRibbonPanel* m_pPanelScene=NULL;
	CMFCRibbonButton* m_pBtnScene=NULL;
	//////////////////////////////////////////////////////////////////////////
	//��־
	CMFCRibbonPanel* m_pPanelLog=NULL;
	CMFCRibbonButton* m_pBtnLog=NULL;
	//////////////////////////////////////////////////////////////////////////
	//�豸
	CMFCRibbonPanel* m_pPanelDevice=NULL;
	//����
	CMFCRibbonButton* m_pBtnConn=NULL;
	//����������
	CMFCRibbonButton* m_pBtnUpdate=NULL;
	//����
	CMFCRibbonButton* m_pBtnNet=NULL;
	
	//������
	//CMFCRibbonButton* m_pBtnOpenNet=NULL;
	//�ر�����
	//CMFCRibbonButton* m_pBtnCloseNet=NULL;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//�ڶ�ҳ
	//��ϯ����
	CMFCRibbonCategory* m_pCategorySeatArrage=NULL;
	//����
	CMFCRibbonPanel* m_pPanelMainSeat=NULL;
	//����
	CMFCRibbonButton* m_pBtnSeatScale=NULL;
	//����
	CMFCRibbonButton* m_pBtnBg=NULL;
	//��ϯ
	CMFCRibbonPanel* m_pPanelSeat=NULL;
	//��ϯ
	CMFCRibbonButton* m_pBtnSeat=NULL;
	//����
	CMFCRibbonButton* m_pBtnAlign=NULL;
	//��Χ
	CMFCRibbonPanel* m_pPanelSeatRange=NULL;
	////��ϯ��Χ��
	CMFCRibbonButton* m_pBtnArray=NULL;
	//CMFCRibbonEdit* m_pEditSeatRow;

	////��ϯ��Χ��
	//CMFCRibbonEdit* m_pEditSeatColumn;
	//����
	CMFCRibbonPanel* m_pPanelOperate=NULL;
	//������ϯ
	CMFCRibbonButton* m_pBtnSaveSeat=NULL;
	//����
	//CMFCRibbonButton* m_pBtnSendSeat=NULL;
	//���
	CMFCRibbonButton* m_pBtnClearSeat=NULL;
	//////////////////////////////////////////////////////////////////////////
	//����ҳ����
	CMFCRibbonCategory* m_pCategoryMatrix=NULL;
	//����
	CMFCRibbonPanel* m_pPanelMatrixArray=NULL;
	//��������
	CMFCRibbonButton* m_pBtnMatrixArray=NULL;
	//����
	CMFCRibbonPanel* m_pPanelMatrixScale=NULL;
	CMFCRibbonButton* m_pBtnMatrixScale=NULL;
	//////////////////////////////////////////////////////////////////////////
	//ƴ�ӽ���
	CMFCRibbonCategory* m_pCategorySplit=NULL;
	//���ƴ����
	CMFCRibbonPanel* m_pPanelOne=NULL;
	//�½�
	CMFCRibbonButton* m_pBtnAdd=NULL;
	//����
	CMFCRibbonPanel* m_pPanelTwo=NULL;
	//����
	CMFCRibbonButton* m_pBtnSplitScale=NULL;
	//����
	CMFCRibbonPanel* m_pPanelThree=NULL;
	//����ģʽ
	CMFCRibbonButton* m_pBtnLimitModel=NULL;
	//����ģʽ
	//CMFCRibbonButton* m_pBtnAddModel=NULL;

	//�����ö�
	CMFCRibbonButton* m_pBtnQuickTop=NULL;
	//����ź�
	CMFCRibbonButton* m_pBtnClearSignal=NULL;
	//��������
	CMFCRibbonButton* m_pBtnSplitScene=NULL;

};



