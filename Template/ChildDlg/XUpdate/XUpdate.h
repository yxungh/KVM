#pragma once
#include "XProgressCtrl.h"
#include "XSocketTCP.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"

class XDelegateUpdate;
// XUpdate 对话框

class XUpdate : public XBaseDialog
{
	DECLARE_DYNAMIC(XUpdate)

public:
	XUpdate(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~XUpdate();
	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	afx_msg void OnBnClickedBtnSelect();
	afx_msg void OnBnClickedBtnSend();
	afx_msg LRESULT OnTCP(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:
	inline void SetDelegate(XDelegateUpdate* p){m_pDelegate=p;}

private:
	void Init();
	void ReloadInterface();
	void SetBtnStatus(BOOL b1,BOOL b2=TRUE);
	BOOL OpenSelectPhotoFileDialog(CString& szFileName,CString& szFilePath);

	void ShowTips(CString szTip);

	BOOL ConnectTransmission();
	void ConnectTransmissionSuccess();
	void BeginTransmission();
	void StopTransmission();

	BOOL OpenTransmissionFile();

	int SetTransmissionData();

	void SendUpdateFile(int nPacketIndex);
	void AddSendData(char* pData,int nDataLen);

	void SetProgressByPacketIndex(int nPacketIndex);
private:
	XProgressCtrl m_Progress;
	CFile m_TransmissionFile;
	int m_nTransmissionFileLen=0;

	XDelegateUpdate* m_pDelegate=NULL;
	XSocketTCP m_SocketTCP;

	CString m_szFilePath=_T("");
	int m_nPackCount=0;
	DWORD m_dwRecvDataTime=0;
	int m_nPacketIndex=0;
	char m_recvData[1024]={0};
	BOOL m_bSendFile=TRUE;
	DWORD m_TimeOut=2000;

	XThemeText m_TextFile;
	XThemeText m_TextRate;
	XThemeText m_TextInfo;
	XThemeText m_TextTip;
	XThemeBtn m_BtnSel;

};
