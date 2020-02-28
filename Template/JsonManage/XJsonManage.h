#pragma once
#include "XConstant.h"

class XLoginInfo;
class XResult;
class XPower;
class XSubUserInfo;
class XDevicePara;
class XNodeConnect;
class XNodeManage;
class XNodeLogin;
class XUpdateUserInfo;
class XTakeOver;
class XAlterNodeName;
class XOSDImage;
class XMatrix;
class XNodeGroup;
class XNodeInfo;
class XNodeManage;
class XUserManage;
class XSystemStatus;
class XStoreList;
class XStoreListInfo;
class XLogPack;
class XNodeStatus;
class XFolderResult;
class XSplitResult;
class XSplitWindow;
class XSignal;
class XSignalLevel;
class XSplitSceneResult;
class XInternalManage;



class XJsonManage
{
public:
	~XJsonManage();
private:
	XJsonManage();

public:

	static XJsonManage* GetInstance();

	static void Relase();

public:

	void ParseJsonToLogin(const char* pData,XLoginInfo& userInfo);

	void ParseJsonToLoginOut(const char* pData,XResult& result);

	void ParseJsonToPower(const char* pData,XUserManage* pManage,XUpdateUserInfo& updateUserInfo);

	void ParseJsonToUserList(const char* pData,MAP_SUBUSER& MapSubUser);

	void ParseJsonToStoreList(const char* pData,MAP_STORE& MapStore,XStoreList& storeList);

	void ParseJsonToReDeviceInfo(const char* pData,XDevicePara& devicePara);

	void ParseJsonToReNodeByChannel(const char* pData,XNodeConnect& nodeConnect);

	void ParseJsonToReNodeInfo(const char* pData,MAP_NODE& MapNode);

	void ParseJsonToReNodeDetailInfo(const char* pData,XNodeManage* pManage,XNodeInfo& nodeInfo);

	void ParseJsonToReNodeStatus(const char* pData,MAP_NODE& MapNode,XNodeStatus& result);

	void ParseJsonToReLoginUser(const char* pData,MAP_USERLOGINSTATUS& MapLoginUser);

	void ParseJsonToReLoginUserStatus(const char* pData,MAP_USERLOGINSTATUS& MapLoginUser);

	void ParseJsonToReNodeLogin(const char* pData,XNodeLogin& nodeLogin);

	void ParseJsonToReNodeLogOut(const char* pData,XResult& result);

	void ParseJsonToReTakeOver(const char* pData,XTakeOver& takeOver);

	void ParseJsonToReTakeOverCancel(const char* pData,XTakeOver& takeOver);

	void ParseJsonToPreview(const char* pData,XTakeOver& takeOver);

	void ParseJsonToAlterNodeName(const char* pData,XAlterNodeName& alterNodeName);

	void ParseJsonToReMatrixStatus(const char* pData,MAP_MATRIX& MapMatrix);

	void ParseJsonToReMatrix(const char* pData,MAP_MATRIX& MapMatrix,XMatrix& matrix);

	void ParseJsonToReOSDImage(const char* pData,XOSDImage& osdImage);

	void ParseJsonToReReadNodeGroup(const char* pData,MAP_NODEGROUP& MapNodeGroup);

	void ParseJsonToReNodeGroupInfo(const char* pData,MAP_NODEGROUP& MapNodeGroup,XNodeGroup& nodeGroup);

	void ParseJsonToReMainAndSecondList(const char* pData,MAP_GROUPMAINSEC& MapList);

	void ParseJsonToReMainAndSecond(const char* pData,MAP_GROUPMAINSEC& MapNodeGroup,XNodeGroup& nodeGroup);

	void ParseJsonToReSystemStatus(const char* pData,XSystemStatus* systemStatus);

	void ParseJsonToReNetConfig(const char* pData,VEC_NETCONFIG& vecConfig,XResult& result);

	void ParseJsonToLog(const char* pData,VEC_LOG& VecLog,XLogPack& logPack);

	void ParseJsonToFolder(const char* pData,XUserManage* pManage,XFolderResult& result);

	void ParseJsonToReSplit(const char* pData,MAP_BASEVIEW& MapBaseView,XSplitResult& result);

	void ParseJsonToReSplitWondow(const char* pData,MAP_BASEVIEW& MapBaseView,XSplitWindow& result);

	void ParseJsonToReSplitScene(const char* pData,XInternalManage* pInternal,XSplitSceneResult& result);

public:

	void WriteJsonToLogin(CString& szUserName,CString& szPassWd,CString& szData);

	void WriteJsonToLoginOut(CString& szUserName,CString& szData);

	void WriteJsonToObtainAllUser(CString& szData);

	void WriteJsonToObtainPower(CString szUserName,CString &szData);

	void WriteJsonToObtainSubPower(int nID,CString& szData);

	void WriteJsonToObtainAddUserPower(int nID,CString& szData);

	void WriteJsonToObtainUserList(int nIndex,int nSize,CString &szData);

	void WriteJsonToAddUser(XPower* pPower,CString& szData);

	void WriteJsonToAlterUser(XPower* pPower,CString& szData,CString szPassWd);

	void WriteJsonToDelUser(CString szUserName,CString& szData);

	void WriteJsonToObtainStore(int nUserID,CString& szData);

	void WriteJsonToDelStoreList(XStoreListInfo* pListInfo,CString& szData);

	void WriteJsonToAddStoreList(XNode* pNode,int nUserID,CString& szData);

	void WriteJsonToGetAllNode(CString& szData);

	void WriteJsonToGetDeviceInfo(CString& szData);

	void WriteJsonToGetNodeByChannel(CString &szData);

	void WriteJsonToGetNodeInfo(XNodeManage* pNodeManage,CString &szData);

	void WriteJsonToGetNodeDetailInfo(int nNodeID,CString &szData);

	void WriteJsonToGetNodeAllDetailInfo(int nNodeID,CString& szData);

	void WriteJsonToUpdataNodeGroup(int nNodeID,int nGroupID,int nMark,CString& szData);

	void WriteJsonToUpdataNodeMaster(int nNodeID,int nMaster,int nMark,CString& szData);

	void WriteJsonToGetNodeStatus(XNodeManage* pNodeManage,CString &szData);
	void WriteJsonToGetNodeStatus(int nNodeID1,int nNodeID2,CString &szData);

	void WriteJsonToGetLoginUser(CString& szData);

	void WriteJsonToGetLoginUserStatus(XNodeManage* pNodeManage,CString &szData);
	void WriteJsonToGetLoginUserStatus(int nUserID,CString& szData);

	void WriteJsonToNodeLogin(int nNodeID,CString szUSerName,CString& szData);

	void WriteJsonToNodeLogOut(int nNodeID,CString& szData);

	void WriteJsonToTakeOver(int nNodeID,int nTargetID,BOOL bExclusive,CString& szData);

	void WriteJsonToTakeOverCancel(int nNodeID,CString& szData);

	void WriteJsonToPreview(int nNodeID,int nTargetID,CString& szData);

	void WriteJsonToAlterNodeName(int nNodeID,CString szNodeName,CString& szData);
	
	void WriteJsonToAlterAudioModel(int nNodeID,int nAudioModel,CString& szData);

	void WriteJsonToAlterAudioSrc(int nNodeID,int nAudioSrc,CString& szData);

	void WriteJsonToAlterHidModel(int nNodeID,int nHidModel,CString& szData);

	void WriteJsonToAlterSplitScreenModel(int nNodeID,int nScreenModel,CString& szData);

	void WriteJsonToAlterResoluationIndex(int nNodeID,int nResIndex,CString& szData);

	void WriteJsonToAlterOutModel(int nNodeID,int nOutModel,CString& szData);

	void WriteJsonToAlterBindCfg(int nNodeID,int nBindCfg,CString& szData);

	void WriteJsonToAlterBindNodeID(int nNodeID,int nBindNodeID,CString& szData);

	void WriteJsonToAlterHotKey(int nNodeID,MAP_HOTKEY& HotKey,CString& szData);

	void WriteJsonToGetMatrixStatus(CString& szData);

	void WriteJsonMatrix(int nInNodeChannel,int nOutNodeChannel,CString& szData);

	void WriteJsonMatrix(XNodeManage* pNodeManage,int nInputChannel,CString &szData);

	void WriteJsonOSDImage(XNodeManage* pNodeManage,int nIndex,CString &szData);

	void WriteJsonHideOSDImage(int nShow,int nChaannel,CString& szData);

	void WriteJsonReadNodeGroup(CString& szData);

	void WriteJsonReadOnLineNodeGroup(CString& szData);

	void WriteJsonNodeGroupInfo(int nNodeGroupID,CString& szData);

	void WriteJsonUpdataSeatArrage(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonUpdataMasterSeatArrage(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonAddSeatArrage(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonMainAndSecondList(CString& szData);

	void WriteJsonQueryMainAndSecond(int nGroupID,CString& szData);

	void WriteJsonAddMainAndSecond(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonDelNodeGroup(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonDelNodeGroupMainSecond(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonUpdataNodeGroupName(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonUpdataMasterNodeGroupName(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonUpdataSeatMasterNode(XNodeGroupInfo& nodeGroupInfo,CString& szData);

	void WriteJsonRefreashGroup(int nGroupID,CString& szData);

	void WriteJsonRefreashMainSecGroup(int nGroupID,CString& szData);

	void WriteJsonSystemStatu(CString& szData);

	void WriteJsonBlink(CString& szData);

	void WriteJsonGetNetConfig(CString& szData);

	void WriteJsonApplyNetConfig(XNetConfig& config,CString& szData);

	void WriteJsonSaveNetConfig(XNetConfig& config,CString& szData);

	void WriteJsonLightControl(int nIndex,int nStatus,CString& szData);

	void WriteJsonLogByData(XLogPack& logPack,CString& szData);

	void WriteJsonLogByUser(XLogPack& logPack,CString& szData);

	void WriteJsonLogByNode(XLogPack& logPack,CString& szData);

	void WriteJsonRTCTime(CString& szData);

	void WriteJsonNotifyMonitor(CString& szData);

	void WriteJsonObtainRootFolder(CString& szData);
	
	void WriteJsonObtainSubFolder(CString& szData,int nID);

	void WriteJsonDeleteFolder(CString& szData,int nID);

	void WriteJsonAddFolder(CString& szData,XSubFolder& sub);


	void WriteJsonObtainSplit(CString& szData);

	void WriteJsonQuerySplitWall(CString& szData,CString szName);

	void WriteJsonAddSplitWall(CString& szData,XSplitResult& splitInfo);

	void WriteJsonDraw(CString& szData,CString szName);

	void WriteJsonRefreashSplit(CString& szData,CString szName);

	void WriteJsonDelSplit(CString& szData,CString szName);

	void WriteJsonObtainSplitWindow(CString& szData,CString szName,BOOL bFirst);

	void WriteJsonObtainSplitWindowInfo(CString& szData,CString szSplitName,int nSignalID);

	void WriteJsonAddSignal(CString& szData,CString szName,XSignal& signal);

	void WriteJsonDelSignal(CString& szData,CString szSplitName,int nSignalID);

	void WriteJsonCLearSignal(CString& szData,CString szSplitName);

	void WriteJsonLevelUseList(CString& szData,CString szSplitName);

	void WriteJsonAlterLevel(CString& szData,CString szSplitName,XSignalLevel& level);

	void WriteJsonObtainSplitScene(CString& szData);

	void WriteJsonObtainWallList(CString& szData,CString szSceneName);

	void WriteJsonOpenScene(CString& szData,CString szSceneName,CString szWallName,int nOpt);

	void WriteJsonQuerySceneWall(CString& szData,CString szSceneName,CString szWallName);

	void WriteJsonSplitScene(CString& szData,CString szSceneName);

	void WriteJsonSaveWallToNewScene(CString& szData,CString szSceneName,CString szSplit,BOOL bLast);

	void WriteJsonObtainSceneGroup(CString& szData,CString szSceneName);

	void WriteJsonSetSceneGroup(CString& szData,CString szSceneName,CString& szGroup,BOOL bAlter=FALSE);

	void WriteJsonDeleteSplitScene(CString& szData,CString szSceneName);

private:

	static XJsonManage* m_pJsomManage;
};