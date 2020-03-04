
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "XDelegateInternalManage.h"
#include "XDelegateView.h"

class XBaseInternalManage;


class CMainFrame: public CMDIFrameWndEx,
	public XDelegateView,
	public XDelegateInternalManage
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա

	//CMFCStatusBar     m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp,LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	//afx_msg void OnSettingChange(UINT uFlags,LPCTSTR lpszSection);
	afx_msg LRESULT OnUDP(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAddDocument(WPARAM wParam,LPARAM lParam);
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnClose();
	afx_msg void OnAbout();

	afx_msg void OnEditDeviceIP();
	afx_msg void OnEditDevicePort();
	afx_msg void OnEditSecondDeviceIP();
	afx_msg void OnEditSecondDevicePort();

	//afx_msg void OnBtnOpenNet();
	//afx_msg void OnBtnCloseNet();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLoginOut();
	afx_msg void OnBtnPowerManage();
	afx_msg void OnBtnOsdImage();

	//afx_msg void OnBtnControl();
	afx_msg void OnBtnSaveScene();
	afx_msg void OnBtnLog();
	afx_msg void OnBtnUpdate();
	afx_msg void OnBtnFolder();

	afx_msg void OnBtnArray();

	afx_msg void OnEditSeatRow();
	afx_msg void OnEditSeatColumn();
	afx_msg void OnBtnSaveSeat();
	afx_msg void OnBtnSendSeat();
	afx_msg void OnBtnClearSeat();
	//************************
	afx_msg void OnBtnTheme();
	afx_msg void OnThemeWin7();
	afx_msg void OnThemeBlue();
	afx_msg void OnThemeBlack();
	afx_msg void OnThemeSliver();
	afx_msg void OnThemeAque();

	afx_msg void OnBtnLanguage();
	afx_msg void OnLanguageZN();
	afx_msg void OnLanguageTW();
	afx_msg void OnLanguageEN();
	afx_msg void OnBtnScale();
	afx_msg void OnBtnSeatScale();
	afx_msg void OnBtnMatrixScale();
	afx_msg void OnScale200();
	afx_msg void OnScale175();
	afx_msg void OnScale150();
	afx_msg void OnScale125();
	afx_msg void OnScale100();
	afx_msg void OnScale75();
	afx_msg void OnScale50();

	afx_msg void OnBtnBg();
	afx_msg void OnBtnSeat();
	afx_msg void OnBtnMatrixArray();

	afx_msg void OnUpdateBtnSeat(CCmdUI *pCmdUI);

	afx_msg void OnUpdateThemeWin7(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThemeBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThemeBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThemeSliver(CCmdUI *pCmdUI);
	afx_msg void OnUpdateThemeAque(CCmdUI *pCmdUI);

	afx_msg void OnUpdateLanguageZN(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLanguageTW(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLanguageEN(CCmdUI *pCmdUI);

	afx_msg void OnUpdateScale200(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScale175(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScale150(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScale125(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScale100(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScale75(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScale50(CCmdUI *pCmdUI);
	//************************
	//////////////////////////////////////////////////////////////////////////
	//afx_msg void OnUpdataBtnOpenNet(CCmdUI *pCmdUI);
	//afx_msg void OnUpdataBtnCloseNet(CCmdUI *pCmdUI);
	afx_msg void OnUpdataBtnLogin(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnLoginOut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnFolder(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnPowerManage(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnOsdImage(CCmdUI* pCmdUI);
	//afx_msg void OnUpdataBtnControl(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnUpdate(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnSaveScene(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnLog(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnSaveSeat(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnSendSeat(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnClearSeat(CCmdUI* pCmdUI);
	afx_msg void OnUpdataBtnMatrixArray(CCmdUI* pCmdUI);
	//*************************
	afx_msg void OnBtnAlign();
	afx_msg void OnUpdataBtnALign(CCmdUI* pCmdUI);

	afx_msg void OnBtnAlignLeft();
	afx_msg void OnBtnAlignHorizon();
	afx_msg void OnBtnALignRight();
	afx_msg void OnBtnALignUp();
	afx_msg void OnBtnALignVertical();
	afx_msg void OnBtnAlignDown();
	afx_msg void OnBtnAlignSame();
	afx_msg void OnBtnAlignHSame();
	afx_msg void OnBtnAlignVSame();
	afx_msg void OnBtnAlignWidth();
	afx_msg void OnBtnAlignHeight();

	afx_msg void OnUpdateAlignHeight(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignWidth(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignVSame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignHSame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignleft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignhorizon(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignright(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignvertical(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAligndown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignsame(CCmdUI *pCmdUI);

	afx_msg void OnUpdateStatusNet(CCmdUI *pCmdUI);
	//*************************
	afx_msg void OnBtnDeviceNet();
	//////////////////////////////////////////////////////////////////////////
	//�˵�
	afx_msg void OnMeunOut();
	//////////////////////////////////////////////////////////////////////////
	//ƴ��
	afx_msg void OnBtnAddSplit();
	afx_msg void OnUpdateAddSplit(CCmdUI *pCmdUI);
	afx_msg void OnBtnSplitScale();
	afx_msg void OnBtnUpdateSplitScale(CCmdUI *pCmdUI);
	afx_msg void OnBtnClearSignal();
	afx_msg void OnBtnUpdateClearSignal(CCmdUI *pCmdUI);
	//�źŲ˵�
	afx_msg void OnMenuUp();
	afx_msg void OnMenuDown();
	afx_msg void OnMenuTop();
	afx_msg void OnMenuBottom();
	afx_msg void OnMenuFullSceeen();
	afx_msg void OnMenuRestore();
	afx_msg void OnMenuExtend();
	afx_msg void OnMenuCloseSignal();



	//���ģʽ
	//afx_msg void OnAddModel();
	//afx_msg void OnUpdateAddModel(CCmdUI *pCmdUI);
	//afx_msg void OnAddDefault();
	//afx_msg void OnUpdateAddDefault(CCmdUI *pCmdUI);
	//afx_msg void OnFullScreen();
	//afx_msg void OnUpdateFullScreen(CCmdUI *pCmdUI);

	afx_msg void OnLimit();
	afx_msg void OnUpdateLimit(CCmdUI *pCmdUI);
	afx_msg void OnLimitModel();
	afx_msg void OnUpdateLimitModel(CCmdUI *pCmdUI);
	afx_msg void OnDelTop();
	afx_msg void OnUpdateDelTop(CCmdUI *pCmdUI);
	afx_msg void OnDelBottom();
	afx_msg void OnUpdateDelBottom(CCmdUI *pCmdUI);

	//�����ö�
	afx_msg void OnBtnQuickTop();
	afx_msg void OnUpdateQuickTop(CCmdUI *pCmdUI);
	//����ƴ�ӳ���
	afx_msg void OnBtnSplitScene();
	afx_msg void OnUpdateSplitScene(CCmdUI *pCmdUI);


	DECLARE_MESSAGE_MAP()

	// ��д
public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	virtual BOOL LoadFrame(UINT nIDResource,DWORD dwDefaultStyle=WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE,CWnd* pParentWnd=NULL,CCreateContext* pContext=NULL);

	//��ȡCWnd
	virtual CWnd* GetCWND();

	//��ȡ���ھ��
	virtual HWND GetHWND();

	//��ʾ��Ϣ�Ի���
	virtual int MessageBox(CString szText,CString szCaption,UINT uType);

	//��������
	virtual void ChangeTheme(int nIndex);

	virtual void AdjustMultiVideoWindowSize();
	virtual void HideMenuWnd();


public:

	//��ͼ����
	virtual void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY);

	//��ͼ��ȡ��С
	virtual CSize ViewGetSize();

	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//��ͼ˫��
	virtual void ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//��ͼ�������
	virtual void ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//��ͼ����ƶ�
	virtual void ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//��ͼ����뿪
	virtual void ViewMouseLeave();

	//������
	virtual BOOL ViewMouseWheel(short zDelta);

	//��ͼ��������
	virtual void ViewKeyUp(UINT nChar);

	//��ͼ�Ҽ�����
	virtual void ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);


private:

	void InitManage();

	void SetViewColor(int nID);

	void InitPane();

	void Clear();

	void BeginTimer();

private:

	XBaseInternalManage* m_pBaseInternalManage;
};


