#pragma once

class CatchError
{
public:

	//���ò���Ӧ�ó����쳣��Ϣ
	static void	SetCatchError(CString folderPath);

	//��ȡDUMP�ļ�·��
	static CString DumpPath();

private:

	//DUMP�ļ���·��
	static CString m_DumpFolderPath;
};



