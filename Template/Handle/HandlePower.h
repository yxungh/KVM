#pragma once


class HandlePower
{
public:
	HandlePower();
	~HandlePower();

public:

	static CString GetPowerByByte(int nIndex,BOOL bByteFlag);

	static CString GetTranslationString(CString szKey,CString szDefault=_T(""));

};