#pragma once

class XHandleVerification
{
private:
	XHandleVerification(void);
	~XHandleVerification(void);

public:

	//�����ַ���
	static BOOL VerificationString(CString szTemp);

	static int VerificationPasswd(CString szTemp);
	static BOOL HasChinese(CString szWord);
	static int GetWordLength(CString szWorld);
};

