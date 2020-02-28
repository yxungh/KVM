#pragma once

#define _M(x,y,z) XMessageBox::GetInstance()->MessageBoxByKey(x,y,z)


class XMessageBox
{
public:
	~XMessageBox();

private:
	XMessageBox();

public:

	static XMessageBox* GetInstance();

	static void Release();

	int MessageBoxByKey(CString szTextKey,CString szDefault,UINT uType);
	int MessageBox(CString szText,CString szCaption,UINT uType);

	void SetTitle(CString szTitle){m_szTitle=szTitle;}

private:

	static XMessageBox* m_pMessageBox;
	CString m_szTitle;
};