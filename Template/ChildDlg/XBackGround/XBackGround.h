#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"

// XBackGround �Ի���
class XDelegateBackGround;


class XBackGround : public XBaseDialog
{
	DECLARE_DYNAMIC(XBackGround)

public:
	XBackGround(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XBackGround();

	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_BG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnBtnOk();
	afx_msg void OnBtnSel();

	DECLARE_MESSAGE_MAP()

public:

	inline CString GetPhotoName(){return m_szPhotoName;}
	inline int GetComboIndex(){return m_nComboIndex;}
	inline COLORREF GetColor(){return m_BgColor;}
	inline void SetDelegate(XDelegateBackGround* p){m_pDelegate=p;}

private:

	void Init();

	void InitCombo();

	void InitData();

	void ReLoadInterface();

	BOOL OpenSelectPhotoFileDialog(CString& szFileName, CString& szFilePath);

	void SavePhotoName(CString szPhotoName);
	//void GetPhotoName();

private:

	XDelegateBackGround* m_pDelegate;


	CString m_szFilePath;
	CString m_szPhotoName;

	CComboBox m_Combox;
	CMFCColorButton m_Color;

	COLORREF m_BgColor;
	int m_nComboIndex;

	XThemeText m_TextModel;
	XThemeText m_TextColor;
	XThemeText m_TextImage;
	XThemeText m_TextTip;
	XThemeBtn m_BtnSel;

};
