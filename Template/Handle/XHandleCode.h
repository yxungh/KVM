#pragma once

//����ת����
class XHandleCode
{
public:

	//���ֽ�תUnicode�ַ���
	static CString ConvertAsciitoUnicode(char* pData);

	//Unicode�ַ���ת���ֽ�
	static void ConvertUnicodeToAscii(const CString& szData, char* pData, int& nDataLen);

	//UnicodeתUTF8
	static void GetUTF8FromUnicode(const CString& szSrc,char* pDes);
};