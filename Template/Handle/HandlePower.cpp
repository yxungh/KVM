#include "stdafx.h"
#include "HandlePower.h"
#include "XTranslationManage.h"

HandlePower::HandlePower()
{

}

HandlePower::~HandlePower()
{

}

CString HandlePower::GetTranslationString(CString szKey,CString szDefault)
{
	return XTranslationManage::GetInstance()->GetTranslationString(szKey,szDefault);
}

CString HandlePower::GetPowerByByte(int nIndex,BOOL bByteFlag)
{
	CString szPower=_T("");

	switch(nIndex)
	{
		case 0:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("500"));
			}
			break;
		case 1:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("501"));
			}
			break;
		case 2:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("502"));
			}
			break;
		case 3:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("503"));
			}
			break;
		case 4:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("504"));
			}
			break;
		case 5:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("505"));
			}
			break;
		case 6:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("506"));
			}
			break;
		case 7:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("507"));
			}
			break;
		case 8:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("508"));
			}
			break;
		case 9:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("509"));
			}
			break;
		case 10:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("510"));
			}
			break;
		case 11:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("511"));
			}
			break;
		case 20:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("520"));
			}
			break;
		case 21:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("521"));
			}
			break;
		case 22:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("522"));
			}
			break;
		case 23:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("523"));
			}
			break;
		case 24:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("524"));
			}
			break;
		case 25:
			{
				if(bByteFlag)
					szPower=GetTranslationString(_T("525"));
			}
			break;
		default:
			break;
	}

	return szPower;
}
