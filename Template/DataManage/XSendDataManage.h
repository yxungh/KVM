#pragma once
#include "XConstant.h"

class XDelegateSendDataManage;
class XNodeManage;
class XNodeGroup;
class XLogPack;
class XSplitResult;
class XSignal;
class XSignalLevel;

class XSendDataManage
{
private:
	XSendDataManage();
public:
	~XSendDataManage();

public:

	static XSendDataManage* GetInstance();

	static void Release();

	void SetDelegate(XDelegateSendDataManage* p);

private:

	BOOL SendData(char* pData,int nDataLen);

	void AddFullSendDataByProtocol(unsigned char* pSrcData,unsigned short nSrcDataLen,PROTOCOLTYPE ProtocolType);

	void AddPackSendDataByProtocol(unsigned char* pSrcData,unsigned short nSrcDataLen,unsigned int nPacket,unsigned int nPacketIndex,PROTOCOLTYPE ProtocolType);

	void AddData(CString szData,PROTOCOLTYPE nType);

	unsigned short CheckSum(unsigned char *pData,int nLen);

public:

	//心跳
	void SendDataOfHeart(DWORD dHeartTime);

	//登录
	void AddSendDataOfLogin(CString szUserName,CString szPassWd);

	//退出
	void AddSendDataOfLoginOut(CString szUserName);

	//获取全部用户
	void AddSendDataOfObtainAllUser();

	//获取登录用户权限
	void SendDataOfObtainUserPower(CString szUserName);

	//获取子用户权限
	void SendDataOfObtainSubUserPower(int nID);

	//获取添加用户权限
	void SendDataOfObtainAddUserPower(int nID);

	//获取用户列表
	void AddSendDataOfObtainUserList(int nIndex,int nSize);

	//添加用户
	void AddSendDataOfAddUser(XPower* pPower);

	//更改用户
	void AddSendDataOfAlterUser(XPower* pPower,CString szPassWd);

	//删除用户
	void AddSendDataOfDelUser(CString szUserName);

	//获取收藏列表
	void AddSendDataOfObtainStoreList(int nUserID);

	//删除收藏列表
	void AddSendDataOfDelStoreList(XStoreListInfo* pListInfo);

	//添加用户收藏列表
	void AddSendDataOfAddStoreList(XNode* pNode,int nUserID);

	//获取全部节点（数据库中在线或不在线）
	void AddSendDataOfGetAllNode();

	//获取设备信息
	void AddSendDataOfGetDeviceInfo();

	//获取节点连接状态
	void AddSendDataOfGetNodeByChannel();

	//根据通道连接情况获取节点部分信息
	void AddSendDataOfGetNodeInfo(XNodeManage* pNodeManage);

	//获取节点详细信息
	void AddSendDataOfGetNodeDetailInfo(XNodeManage* pNodeManage);

	//获取所有节点信息
	void AddSendDataOfGetNodeAllDetailInfo(int nNodeID);

	//更改节点信息
	void AddSendDataOfUpdateNodeGroup(int nNodeID,int nGroupID,int nMark);
	void AddSendDataOfUpdateNodeGroupMaster(int nNodeID,int nMasterID,int nMark);

	//更改用户master
	//void AddSendDataOfUpdateNodeMaster(int nNodeID,int nMatser,int nMark);

	//查询节点状态
	void AddSendDataOfGetNodeStatus(XNodeManage* pNodeManage);
	void AddSendDataOfGetNodeStatus(int nNodeID1,int nNodeID2);

	//获取登录用户
	void AddSendDataOfGetLoginUser();

	//查询登录用户状态
	void AddSendDataOfGetLoginUserStatus(XNodeManage* pNodeManage);
	void AddSendDataOfGetLoginUserStatus(int nUserID);

	//节点登录
	void AddSendDataOfNodeLogin(int nNodeID,CString szUserName);

	//节点退出
	void AddSendDataOfNodeLogOut(int nNodeID);

	//接管
	void AddSendDataOfTakeOver(int nNodeID,int nTargetID,BOOL bExclusive);

	//退出接管
	void AddSendDataOfTakeOverCancel(int nNodeID);

	//预览
	void AddSendDataOfPreview(int nNodeID,int nTargetID);

	//更改名称
	void AddSendDataOfAlterNodeName(int nNodeID,CString szName);

	//设置输入音频模式
	void AddSendDataOfAlterAudioModel(int nNodeID,int nAudioModel);

	//更改音频源
	void AddSendDataOfAlterAudioSrc(int nNodeID,int nAudioSrc);

	//设置输入系统
	void AddSendDataOfAlterHidModel(int nNodeID,int nHidModel);

	//设置分屏模式
	void AddSendDataOfAlterSplitScreenModel(int nNodeID,int nScreenModel);

	//设置输出分辨率信息
	void AddSendDataOfAlterResoluationIndex(int nNodeID,int nResIndex);

	//设置输出模式
	void AddSendDataOfAlterOutModel(int nNodeID,int nOutModel);

	//获取矩阵切换状态
	void AddSendDataOfGetMatrixStatus();

	//矩阵切换
	void AddSendDataOfMatrix(int nInNodeChannel,int nOutNodeChannel);
	void AddSendDataOfMatrix(XNodeManage* pNodeManage,int nInputChannel);

	//发送OSD底图
	void AddSendDataOfOSDImage(XNodeManage* pNodeManage,int nIndex);

	//隐藏OSD底图
	void AddSendDataOfHideOSDImage(int nShow,int nChannel);

	void AddSendDataOfAlterBindCfg(int nNodeID,int bBindCfg);
	void AddSendDataOfAlterBindNodeID(int nNodeID,int bBindNodeID);

	//快捷键
	void AddSendDataOfAlterHotKey(int nNodeID,MAP_HOTKEY& MapHotKey);

	//读取节点组
	void AddSendDataOfReadNodeGroup();

	//读取在线节点组
	void AddSendDataOfReadOnLineNodeGroup();

	//获取节点详细信息
	void AddSendDataOfNodeGroupInfo(XNodeManage* pNodeManage);

	//更新坐席
	void AddSendDataOfUpdataSeatArrage(XNodeGroupInfo& nodeGroupInfo);
	void AddSendDataOfUpdataMasterSeatArrage(XNodeGroupInfo& nodeGroupInfo);

	//添加组坐席
	void AddSendDataOfAddSeatArrage(XNodeGroupInfo& nodeGroupInfo);

	//获取主副屏列表
	void AddSendDataOfMainAndSecondList();

	//查询主副屏
	void AddSendDataOfQueryMainAndSecond(int nGroupID);

	//添加主副屏
	void AddSendDataOfMainAndSecond(XNodeGroupInfo& nodeGroupInfo);

	//删除节点组
	void AddSendDataOfDelNodeGroup(XNodeGroupInfo& nodeGroupInfo);

	//删除主副屏
	void AddSendDataOfDelNodeGroupMainSecond(XNodeGroupInfo& nodeGroupInfo);

	//更改组名称 包括组和主副屏
	void AddSendDataOfUpdataNodeGroupName(XNodeGroupInfo& nodeGroupInfo);
	void AddSendDataOfUpdataMasterNodeGroupName(XNodeGroupInfo& nodeGroupInfo);

	//更改坐席主节点
	void AddSendDataOfUpdataSeatMasterNode(XNodeGroupInfo& nodeGroupInfo);

	//刷新组成员
	void AddSendDataOfRefreashGroup(int nGroupID);
	void AddSendDataOfRefreashMainSecGroup(int nGroupID);

	//获取设备温度
	void AddSendDataSystemStatus();

	//点击灯闪烁
	void AddSendDataOfBlink();

	//查询网络配置
	void AddSendDataOfNetConfig();
	//应用网络配置
	void AddSendDataOfApplyNetConfig(XNetConfig& config);
	void AddSendDataOfSaveNetConfig(XNetConfig& config);

	//控制灯
	void AddSendDataOfLightControl(int nIndex,int nStatus);

	//按日期获取日志
	void AddSendDataOfGetLogByData(XLogPack& logPack);
	void AddSendDataOfGetLogByUser(XLogPack& logPack);
	void AddSendDataOfGetLogByNode(XLogPack& logPack);

	//发送RTC时间
	void AddSendDataOfRTCTime();

	//通知TCP监听
	void AddSendDataOfNotifyMonitor();

	//获取文件夹
	void AddSendDataOfObtainRootFolder();
	//获取子文件夹和节点
	void AddSendDataOfObtainSubFolder(int nID);
	//删除目录
	void AddSendDataOfDeleteFolder(int nID);
	//添加目录
	void AddSendDataOfAddFolder(XSubFolder& sub);

	//获取拼接墙
	void AddSendDataOfObtainSplit();
	//获取拼接墙信息
	void AddSendDataOfQuerySplitWall(CString szName);
	//添加pinjie
	void AddSendDataOfAddSplit(XSplitResult& splitInfo);
	//绘制指令
	void AddSendDataOfDraw(CString szName);
	//拼接墙配置生效
	void AddSendDataOfRefreashSplit(CString szName);
	//删除拼接墙
	void AddSendDataOfDelSplit(CString szName);
	//获取拼接窗口
	void AddSendDataOfObtainSplitWindow(CString szName,BOOL bFirst=FALSE);
	//获取窗口信息
	void AddSendDataOfObtainSplitWindowInfo(CString szSplitName,int nSignalID);
	//开窗
	void AddSendDataOfAddSignal(CString szName,XSignal& signal);
	//关闭窗口
	void AddSendDataOfDelSignal(CString szName,int nID);
	//清空
	void AddSendDataOfClearSignal(CString szName);
	//拼接墙层次占用列表
	void AddSendDataOfLevelUseList(CString szName);
	//设置信号层次
	void AddSendDataOfAlterLevel(CString szName,XSignalLevel& level);
	//获取拼接场景
	void AddSendDataOfObtainSplitScene();
	//获取场景中的墙列表
	void AddSendDataOfObtainWallList(CString szName);
	//调用场景
	void AddSendDataOfOpenScene(CString szSceneName,CString szWallName,int nOpt);

	//查询场景中墙信息
	void AddSendDataOfQuerySceneWall(CString szSceneName,CString szWallName);

	//添加拼接场景
	void AddSendDataOfAddSplitScene(CString szSceneName);
	//场景保存墙
	void AddSendDataOfSaveWallToNewScene(CString szSceneName,CString szSplit,BOOL bLast);
	//获取场景组
	void AddSendDataOfObtainSceneGroup(CString szSceneName);
	//设置组
	void AddSendDataOfSetSceneGroup(CString szSceneName,CString szGroup,BOOL bAlter=FALSE);
	//删除场景
	void AddSendDataOfDeleteSplitScene(CString szSceneName);

private:

	static XSendDataManage* m_pSendDataManage;

	XDelegateSendDataManage* m_pDelegate;

	unsigned short m_nTotalPacket;

	unsigned short m_nCurPacket;

	unsigned short m_nPacketLen;
};