#pragma once


class XDelegateInternalManage
{
public:

	XDelegateInternalManage();
	~XDelegateInternalManage();

public:

	//��ȡCWnd
	virtual CWnd* GetCWND()=0;

	//��ȡ���ھ��
	virtual HWND GetHWND()=0;

	//��ʾ��Ϣ�Ի���
	virtual int MessageBox(CString szText,CString szCaption,UINT uType)=0;

	virtual void ChangeTheme(int nIndex)=0;

};