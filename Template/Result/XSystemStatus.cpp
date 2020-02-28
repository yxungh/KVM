#include "stdafx.h"
#include "XSystemStatus.h"


XSystemStatus::XSystemStatus()
{
}


XSystemStatus::~XSystemStatus()
{
}

XSystemStatus* XSystemStatus::GetInstance()
{
	static XSystemStatus systemStatus;
	return &systemStatus;
}