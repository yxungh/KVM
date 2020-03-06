#pragma once
#include "XConstant.h"

class XDelegateReciveDataManage;

class XReciveDataManage
{
public:
	XReciveDataManage(void);
	~XReciveDataManage(void);

public:

	void Init();

	void SetDelegate(XDelegateReciveDataManage* p);

	void Operate(OPERATETYPE type, void* pData);

	BOOL HandleUDPData(unsigned char* pData, int nDataLen, SOCKADDR_IN addr);


private:

	unsigned char* AddDataOfFull(unsigned char* pData,int nLen);

	unsigned char* AddDataOfPacket(unsigned char* pData,int nLen);

private:

	void DecodeLogin(unsigned char* pData,int nDataLen);

	void DecodeLoginOut(unsigned char* pData,int nDataLen);

	void DecodeHeart(unsigned char* pData,int nDataLen);

	//用户权限（包含登录用户与子用户）
	void DecodePower(unsigned char* pData,int nDataLen);

	void DecodeUserSecurity(unsigned char* pData,int nDataLen);

	void DecodeUserList(unsigned char* pData,int nDataLen);

	void DecodeStoreList(unsigned char* pData,int nDataLen);

	void DecodeGetDeviceInfo(unsigned char* pData,int nDataLen);

	void DecodeGetNodeByChannel(unsigned char* pData,int nDataLen);

	void DecodeNodeInfo(unsigned char* pData,int nDataLen);

	void DecodeNodeDetailInfo(unsigned char* pData,int nDataLen);

	void DecodeNodeStatus(unsigned char* pData,int nDataLen);

	void DecodeGetLoginUser(unsigned char* pData,int nDataLen);

	void DecodeGetLoginUserStatus(unsigned char* pData,int nDataLen);

	void DecodeGetNodeLogin(unsigned char* pData,int nDataLen);

	void DecodeGetNodeLogOut(unsigned char* pData,int nDataLen);

	void DecodeTakeOver(unsigned char* pData,int nDataLen);

	void DecodeTakeOverCancel(unsigned char* pData,int nDataLen);

	void DecodePreview(unsigned char* pData,int nDataLen);

	void DecodeAlterNodeName(unsigned char* pData,int nDataLen);

	void DecodeMatrix(unsigned char* pData,int nDataLen);

	void DecodeGetMatrixStatus(unsigned char* pData,int nDataLen);

	void DecodeOSDImage(unsigned char* pData,int nDataLen);

	void DecodeHideOSDImage(unsigned char* pData,int nDataLen);

	void DecodeNodeGroup(unsigned char* pData,int nDataLen);

	void DecodeNodeGroupInfo(unsigned char* pData,int nDataLen);

	void DecodeRefreashGroup(unsigned char* pData,int nDataLen);

	void DecodeSystemStatus(unsigned char* pData,int nDataLen);

	void DecodeMainAndSecondList(unsigned char* pData,int nDataLen);

	void DecodeMainAndSecond(unsigned char* pData,int nDataLen);

	void DecodeNetConfig(unsigned char* pData,int nDataLen);

	void DecodeReLog(unsigned char* pData,int nDataLen);

	void DecodeRootFolder(unsigned char* pData,int nDataLen);
	
	void DecodeSplit(unsigned char* pData,int nDataLen);

	void DecodeSplitWindow(unsigned char* pData,int nDataLen);

	void DecodeSplitScene(unsigned char* pData,int nDataLen);

	void DecodeSplitInput(unsigned char* pData,int nDataLen);

	void DecodeAsServer(unsigned char* pData,int nDataLen);

	void DecodeAsClient(unsigned char* pData,int nDataLen);

private:

	XDelegateReciveDataManage* m_pDelegate;

};

