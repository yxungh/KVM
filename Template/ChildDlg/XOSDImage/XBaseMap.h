#pragma once
#include "..\resource.h"
#include "XDelegateImagePreview.h"
#include "XConstant.h"
#include "XDelegateImage.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"

class XDelegateBaseMap;
class XImage;


class XBaseMap:public XBaseDialog,
			   public XDelegateImagePreview,
			   public XDelegateImage
{
	DECLARE_DYNAMIC(XBaseMap)

public:
	XBaseMap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XBaseMap();

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	// 对话框数据
	enum { IDD = IDD_DIALOG_BASEMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedImage1();
	afx_msg void OnBnClickedImage2();
	afx_msg void OnBnClickedImage3();
	afx_msg void OnBnClickedImage4();
	afx_msg void OnBnClickedImage5();
	afx_msg void OnBnClickedImage6();
	//afx_msg void OnComboSelChange();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	virtual MAP_IMAGE& GetMapImage();

	virtual void SendDataOfOSDImage(int nIndex);

	virtual void SetMatrixInputToOutput(int nInputChannel);

public:

	inline void SetDelegate(XDelegateBaseMap* p){m_pDelegate=p;}

public:

	void SetOperate(int nPixIndex);
	void SendOSDPicOrder();

private:

	void Init();
	void InitData();
	void InitShowData();
	void InitCombo();
	void ReloadInterface();
	void SelectBaseMap(int nIndex);
	BOOL OpenSelectPhotoFileDialog(CString& szFileName, CString& szFilePath);
	void SaveFilePath(int nIndex,CString szFilePath);
	void SetImageMap();
	void SetImageMap(int nIndex,CString szFilePath);

private:

	XDelegateBaseMap* m_pDelegate;
	XImage* m_pImage;

private:

	CString m_szFilePath;
	CString m_szPhotoName;
	CComboBox m_ComboInput;

	XThemeText m_TextChannel;
	XThemeText m_TextMap1;
	XThemeText m_TextMap2;
	XThemeText m_TextMap3;
	XThemeText m_TextMap4;
	XThemeText m_TextMap5;
	XThemeText m_TextMap6;

	XThemeBtn m_BtnImage1;
	XThemeBtn m_BtnImage2;
	XThemeBtn m_BtnImage3;
	XThemeBtn m_BtnImage4;
	XThemeBtn m_BtnImage5;
	XThemeBtn m_BtnImage6;
	XThemeBtn m_BtnPreview;
	XThemeBtn m_BtnSend;
	XThemeBtn m_BtnCancel;


};
