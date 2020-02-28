#pragma once
#include "XDelegateNodeLoginUser.h"


class XPropertyGrid;
class XPropertyGridFile;
class XNodeManage;


class XNode:public XDelegateNodeLoginUser
{
public:
	XNode();
	~XNode();

public:

	virtual MAP_SUBUSER& GetMapSubUser();

	virtual MAP_POWER& GetMapPower();

public:

	inline void SetNodeManage(XNodeManage* p){m_pNodeManage=p;}

	inline void SetTreeItem(HTREEITEM item){m_NodeItem=item;}
	inline HTREEITEM GetTreeItem(){return m_NodeItem;}

	inline void SetIndex(int n){m_nIndex=n;}
	inline int GetIndex(){return m_nIndex;}

	inline void SetRect(CRect rect){m_rect=rect;}
	inline CRect GetRect(){return m_rect;}

	inline void SetTextRect(CRect rect){m_TextRect=rect;}
	inline CRect GetTextRect(){return m_TextRect;}

	inline void SetSelected(BOOL b){m_bSelected=b;}
	inline BOOL GetSelected(){return m_bSelected;}

	inline void SetDrag(BOOL b){m_bDrag=b;}
	inline BOOL GetDrag(){return m_bDrag;}

public:

	inline void SetRealID(CString szID){m_szRealID=szID;}
	inline CString GetRealID(){return m_szRealID;}

	inline void SetNodeName(CString szName){m_szNodeName=szName;}
	inline CString GetNodeName(){return m_szNodeName;}

	inline void SetCreateTime(time_t time){m_tConnectTime=time;}
	inline time_t GetCreateTime(){return m_tConnectTime;}

	inline void SetGroup(int nGroup){m_nGroup=nGroup;}
	inline int GetGroup(){return m_nGroup;}

	inline void SetMaster(int n){m_nMaster=n;}
	inline int GetMaster(){return m_nMaster;}

	inline void SetControl(int n){m_nControl=n;}
	inline int GetControl(){return m_nControl;}


public:

	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetChannel(int n){m_nChannel=n;}
	inline int GetChannel(){return m_nChannel;}

	inline void SetNodeType(int n){m_nNodeType=n;}
	inline int GetNodeType(){return m_nNodeType;}

	inline void SetConnectTime(time_t time){m_tCreateTime=time;}
	inline time_t GetConnectTime(){return m_tCreateTime;}

	inline void SetMainCh(int n){m_nMainCh=n;}
	inline int GetMainCh(){return m_nMainCh;}

public:

	//in
	inline void SetNodeInStatus(int n){m_nInStatus=n;}
	inline int GetNodeInStatus(){return m_nInStatus;}

	inline void SetIsSignal(BOOL b){m_bSignal=b;}
	inline BOOL GetIsSignal(){return m_bSignal;}

	inline void SetInResolusationH(int n){m_nInResolusationH=n;}
	inline int GetInResolusationH(){return m_nInResolusationH;}

	inline void SetInResolusationV(int n){m_nInResolusationV=n;}
	inline int GetInResolusationV(){return m_nInResolusationV;}

	inline void SetAudioModel(int n){m_nAudioModel=n;}
	inline int GetAudioModel(){return m_nAudioModel;}

	inline void SetHidModel(int n){m_nHidModel=n;}
	inline int GetHidModel(){return m_nHidModel;}

	inline void SetSplitScreen(int n){m_nSplitScreen=n;}
	inline int GetSplitScreen(){return m_nSplitScreen;}

	inline void SetSoftVer(CString szVer){m_szSoftVer=szVer;}
	inline CString GetSoftVer(){return m_szSoftVer;}

	inline void SetHardVer(CString szVer){m_szHardVer=szVer;}
	inline CString GetHardVer(){return m_szHardVer;}

	inline void SetAudioSrc(int n){m_nAudioSrc=n;}
	inline int GetAudioSrc(){return m_nAudioSrc;}


	//out
	inline void SetOutStatus(int n){m_nOutStatus=n;}
	inline int GetOutStatus(){return m_nOutStatus;}

	inline void SetOutResoluationIndex(int n){m_nOutResoluationIndex=n;}
	inline int GetOutResoluationIndex(){return m_nOutResoluationIndex;}

	inline void SetOutModel(int n){ m_nOutModel=n;}
	inline int GetOutModel(){return m_nOutModel;}

	inline void SetIsNodeLogin(BOOL b){m_bNodeLogin=b;}
	inline BOOL GetIsNodeLogin(){return m_bNodeLogin;}

	inline void SetIsTakeOver(BOOL b){m_bTakeOver=b;}
	inline BOOL GetIsTakeOver(){return m_bTakeOver;}

	inline void SetLoginUserID(int n){m_nLoginUserID=n;}
	inline int GetLoginUserID(){return m_nLoginUserID;}

	inline void SetTakeOverNodeID(int n){m_nTakeOverNodeID=n;}
	inline int GetTakeOverNodeID(){return m_nTakeOverNodeID;}

	inline void SetPreviewNodeID(int n){m_nPreviewNodeID=n;}
	inline int GetPreviewNodeID(){return m_nPreviewNodeID;}

	inline void SetBindCfg(int n){m_nBindCfg=n;}
	inline int GetBindCfg(){return m_nBindCfg;}

	inline void SetBindNodeID(int n){m_nBindNodeID=n;}
	inline int GetBindNodeID(){return m_nBindNodeID;}

	inline void SetOutSoftVer(CString szVer) { m_szOutSoftVer=szVer; }
	inline CString GetOutSoftVer() { return m_szOutSoftVer; }

	inline void SetOutHardVer(CString szVer) { m_szOutHardVer=szVer; }
	inline CString GetOutHardVer() { return m_szOutHardVer; }

	inline std::vector<int>& GetVecHotKey(){return m_VecHotKey;}

private:

	//������Ϣ
	void PropertyInfo();
	//��¼�ڵ�
	void PropertyLoginStatus();
	//�ӹ�
	void PropertyTakeOver();
	//Ԥ��
	void PropertyPreview();
	//�����л�
	void PropertyMatrix();
	//��ʾ����OSD��ͼ
	void PropertyOSDImage();
	//������
	void PropertyBindSet();
	//�ȼ�
	void PropertyHotKey();

	//void UpdateOptionList(CString& szOptionText);

	XUserLogStatus* GetUserLoginStatusByNodeID(MAP_USERLOGINSTATUS& MapUserLogin,int nNodeID);
	int GetNodeIDByChannel(int nChannel);

public:

	//�������Կ�
	void SetPropertiesWnd();

	//����ֵ�ı�
	void OnPropertyChanged(CMFCPropertyGridProperty* pProperty);

	//˫������
	BOOL OnDblClkPropertyGrid(XPropertyGrid* pPropertyGrid);

	BOOL OnDblClkPropertyGridFile(XPropertyGridFile* pPropertyGridFile);

	//�������Կ�
	void OnClickButtonPropertyGridFile(XPropertyGridFile* pPropertyGridFile);

private:
	void ClearMapHotKey();
	CString GetKeyByValue(int nValue);
	void ParseVecValue();
	void ParseHotKey(int nIndex,CString& szFunction,CString& szValue,CString& szEnable);
	void WriteHotKey(int nIndex,CString szFunction,CString szValue,CString szEnable);

private:

	XNodeManage* m_pNodeManage=NULL;
	//�ڵ�������
	HTREEITEM m_NodeItem=NULL;
	//���
	int m_nIndex=0;
	//����
	CRect m_rect;
	//������������
	CRect m_TextRect;
	//�Ƿ�ѡ��
	BOOL m_bSelected=FALSE;
	//�ܷ���ק
	BOOL m_bDrag=TRUE;

private:

	//��ʵID
	CString m_szRealID=_T("");
	//�ڵ�����
	CString m_szNodeName=_T("");
	//����ʱ��
	time_t m_tCreateTime=0;
	//�ڵ�IP
	CString m_szNodeIP=_T("");
	//��
	int m_nGroup=0;
	//��
	int m_nMaster=0;
	//����
	int m_nControl=0;
	//�û���¼��Ϣ����
	//////////////////////////////////////////////////////////////////////////
	//��¼�û�
	CString m_szLoginUser=_T("");
	//�û��Ƿ������¼
	BOOL m_bNetLogin=FALSE;
	//�����¼IP
	CString m_szIP=_T("");
	//�����¼�˿�
	int m_nPort=0;
	//�Ƿ�ڵ��¼
	BOOL m_bNodeLogin=FALSE;
	//////////////////////////////////////////////////////////////////////////

//�������������ȡ���Ĳ��ֲ���
private:

	//ͨ��
	int m_nChannel=0;
	//ID�ı��
	int m_nNodeID=0;
	//����
	int m_nNodeType=-1;
	//����ʱ��
	time_t m_tConnectTime=0;
	//��ͨ��
	int m_nMainCh=0;

private:
	//�ڵ�״̬
	//In
	int m_nInStatus=-1;
	BOOL m_bSignal=FALSE;

	int m_nInResolusationH=0;
	int m_nInResolusationV=0;
	int m_nAudioModel=-1;//��Ƶģʽ
	int m_nHidModel=-1;//ϵͳ
	int m_nSplitScreen=1;//����ģʽ
	CString m_szSoftVer=_T("");//����汾
	CString m_szHardVer=_T("");//Ӳ���汾
	int m_nAudioSrc=0;//��ǰ������ƵԴ�ڵ�ID


	//out
	int m_nOutStatus=0;
	//DVI,HDMI
	int m_nOutModel=-1;
	//�ֱ�����Ϣ���
	int m_nOutResoluationIndex=-1;
	//�Ƿ�ӹ�
	BOOL m_bTakeOver=FALSE;
	//��¼���û�
	int m_nLoginUserID=0;
	//�ӹܽڵ�ID
	int m_nTakeOverNodeID=0;
	//Ԥ���ڵ�ID
	int m_nPreviewNodeID=0;
	//������
	int m_nBindCfg=0;
	//������ڵ�ID
	int m_nBindNodeID=0;
	CString m_szOutSoftVer=_T("");//����汾
	CString m_szOutHardVer=_T("");//Ӳ���汾

	//�ȼ� 
	VEC_HOTKEY m_VecHotKey;
	//�˵���ֵ
	MAP_HOTKEY m_MapHotKey;
};