#pragma once

class HandleIni
{
private:
	HandleIni(void);
	~HandleIni(void);

public:

	//��ȡintֵ
	static int GetInt(CString szAppName, CString szKeyName, int nDefault, 
		CString szPath);

	//��ȡ�ַ���ֵ
	static CString GetString(CString szAppName, CString szKeyName, CString szDefault, 
		CString szPath);

	//д������
	static BOOL WriteData(CString szAppName, CString szKeyName, CString szData, 
		CString szPath);
};

