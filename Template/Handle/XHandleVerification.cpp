#include "StdAfx.h"
#include "XHandleVerification.h"

XHandleVerification::XHandleVerification(void)
{
}


XHandleVerification::~XHandleVerification(void)
{
}

BOOL XHandleVerification::VerificationString(CString szTemp)
{
	int nLen=szTemp.GetLength();
	for(int i=0;i<nLen;i++)
	{
		TCHAR c=szTemp.GetAt(i);

		if(('('==c)
		   ||(')'==c)
		   ||('='==c)
		   ||('\''==c)
		   ||('-'==c)
		   ||(';'==c)
		   ||('>'==c)
		   ||('<'==c)
		   ||('*'==c)
		   ||('!'==c)
		   ||('%'==c))
		{
			return FALSE;
		}
	}

	return TRUE;
}

int XHandleVerification::VerificationPasswd(CString szTemp)
{
	////////判断CString字符串类型的密码是否符合规范///////
	//检查密码是否符合规范(长度不小于8位，且必须同时包含大小写字母、数字及特殊符号)
	int iLength=szTemp.GetLength();
	if(iLength<4)
	{
		//密码长度为4位
		return 1;
	}

	int nNumber=0;
	int nchar=0;
	for(int i=0;i<iLength;i++)
	{
		int iCharacter=(int)szTemp.GetAt(i);
		if(iCharacter>=0x30&&iCharacter<=0x39)
		{
			nNumber=1;
		}

		if((iCharacter>=0x61&&iCharacter<=0x7a)||(iCharacter>=0x41&&iCharacter<=0x5a))
		{
			nchar=1;
		}


	}

	if(nNumber==0||nchar==0)
	{
		return 2;
	}

	return 0;

	//////////////////////////////////////////////////////////////////////////

	//int iNumber=0;
	//int iUpperChar=0;
	//int iLowerChar=0;
	//int iSpecCharacter=0;

	//for(int i=0;i<iLength;i++)
	//{
	//	int iCharacter=(int)szTemp.GetAt(i);

	//	if(iCharacter>=0x30&&iCharacter<=0x39) //数字集合[0x30, 0x39](ASCII码字符对应的十六进制值)
	//	{
	//		iNumber=1; //字符存在于数字集合中，即包含了数字
	//	}

	//	if(iCharacter>=0x61&&iCharacter<=0x7a) //小写字母集合[0x61, 0x7a]
	//	{
	//		iLowerChar=1; //字符存在于小写字母集合中，即包含了小写字母
	//	}

	//	if(iCharacter>=0x41&&iCharacter<=0x5a) //大写字母集合[0x41, 0x5a]
	//	{
	//		iUpperChar=1; //字符存在于大写字母集合中，即包含了大写字母
	//	}

	//	if(iCharacter>=0x21&&iCharacter<=0x7e  //可见字符集合[0x21, 0x7e]
	//	   &&iNumber==0&&iLowerChar==0&&iUpperChar==0) //可见字符集合中除去数字、大小写字母剩下的即为特殊字符
	//	{
	//		iSpecCharacter=1; //字符存在于特殊字符集合中，即包含了特殊字符
	//	}
	//}

	//if(iNumber==0||iUpperChar==0||iLowerChar==0||iSpecCharacter==0)
	//{
	//	MessageBox(_T("密码必须同时包含有大小写字母、数字和特殊符号！"),NULL,MB_OK|MB_ICONERROR);
	//	return;
	//}
	//else
	//{
	//	MessageBox(_T("恭喜您，此密码符合规范！"),NULL,MB_OK|MB_ICONERROR);
	//}
	//////////////////////////////////////////////////////
}

BOOL XHandleVerification::HasChinese(CString szWord)
{
	int nLen=szWord.GetLength();
	//unsigned char ch1,ch2;
	for(int i=0;i!=nLen;++i)
	{
		TCHAR c=szWord.GetAt(i);
		if(c>=0xA0)
		{
			return TRUE;
		}
		else
		{
			continue;
		}
	}
	return FALSE;
}

int XHandleVerification::GetWordLength(CString szWord)
{
	int nWordLen=0;
	int nLen=szWord.GetLength();
	for(int i=0;i!=nLen;++i)
	{
		TCHAR c=szWord.GetAt(i);
		if(c>=0xA0)
		{
			nWordLen+=2;
		}
		else
		{
			nWordLen+=1;
		}
	}
	return nWordLen;
}