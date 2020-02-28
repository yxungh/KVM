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
	////////�ж�CString�ַ������͵������Ƿ���Ϲ淶///////
	//��������Ƿ���Ϲ淶(���Ȳ�С��8λ���ұ���ͬʱ������Сд��ĸ�����ּ��������)
	int iLength=szTemp.GetLength();
	if(iLength<4)
	{
		//���볤��Ϊ4λ
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

	//	if(iCharacter>=0x30&&iCharacter<=0x39) //���ּ���[0x30, 0x39](ASCII���ַ���Ӧ��ʮ������ֵ)
	//	{
	//		iNumber=1; //�ַ����������ּ����У�������������
	//	}

	//	if(iCharacter>=0x61&&iCharacter<=0x7a) //Сд��ĸ����[0x61, 0x7a]
	//	{
	//		iLowerChar=1; //�ַ�������Сд��ĸ�����У���������Сд��ĸ
	//	}

	//	if(iCharacter>=0x41&&iCharacter<=0x5a) //��д��ĸ����[0x41, 0x5a]
	//	{
	//		iUpperChar=1; //�ַ������ڴ�д��ĸ�����У��������˴�д��ĸ
	//	}

	//	if(iCharacter>=0x21&&iCharacter<=0x7e  //�ɼ��ַ�����[0x21, 0x7e]
	//	   &&iNumber==0&&iLowerChar==0&&iUpperChar==0) //�ɼ��ַ������г�ȥ���֡���Сд��ĸʣ�µļ�Ϊ�����ַ�
	//	{
	//		iSpecCharacter=1; //�ַ������������ַ������У��������������ַ�
	//	}
	//}

	//if(iNumber==0||iUpperChar==0||iLowerChar==0||iSpecCharacter==0)
	//{
	//	MessageBox(_T("�������ͬʱ�����д�Сд��ĸ�����ֺ�������ţ�"),NULL,MB_OK|MB_ICONERROR);
	//	return;
	//}
	//else
	//{
	//	MessageBox(_T("��ϲ������������Ϲ淶��"),NULL,MB_OK|MB_ICONERROR);
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