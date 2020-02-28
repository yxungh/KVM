#pragma once


class XDelegateInternalManage
{
public:

	XDelegateInternalManage();
	~XDelegateInternalManage();

public:

	//获取CWnd
	virtual CWnd* GetCWND()=0;

	//获取窗口句柄
	virtual HWND GetHWND()=0;

	//显示消息对话框
	virtual int MessageBox(CString szText,CString szCaption,UINT uType)=0;

	virtual void ChangeTheme(int nIndex)=0;

};