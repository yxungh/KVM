#pragma once

//�ļ�����
class FileHandle
{

public:

	//����·�������ļ���
	static BOOL	createFolder(CString& path);

	//�����ļ�
	static BOOL copyFile(CString& szUrl,CString& szNewUrl);

	//ɾ���ļ�
	static BOOL delFile(CString path);

	//�����ļ���
	static BOOL CopyDirectory(CString SrcDirectry,CString DstDirectory);

	//�������ļ�
	static BOOL renamefile(CString path,CString name);

private:
	FileHandle(void);
	~FileHandle(void);

};

