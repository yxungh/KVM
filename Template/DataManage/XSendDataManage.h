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

	//����
	void SendDataOfHeart(DWORD dHeartTime);

	//��¼
	void AddSendDataOfLogin(CString szUserName,CString szPassWd);

	//�˳�
	void AddSendDataOfLoginOut(CString szUserName);

	//��ȡȫ���û�
	void AddSendDataOfObtainAllUser();

	//��ȡ��¼�û�Ȩ��
	void SendDataOfObtainUserPower(CString szUserName);

	//��ȡ���û�Ȩ��
	void SendDataOfObtainSubUserPower(int nID);

	//��ȡ����û�Ȩ��
	void SendDataOfObtainAddUserPower(int nID);

	//��ȡ�û��б�
	void AddSendDataOfObtainUserList(int nIndex,int nSize);

	//����û�
	void AddSendDataOfAddUser(XPower* pPower);

	//�����û�
	void AddSendDataOfAlterUser(XPower* pPower,CString szPassWd);

	//ɾ���û�
	void AddSendDataOfDelUser(CString szUserName);

	//��ȡ�ղ��б�
	void AddSendDataOfObtainStoreList(int nUserID);

	//ɾ���ղ��б�
	void AddSendDataOfDelStoreList(XStoreListInfo* pListInfo);

	//����û��ղ��б�
	void AddSendDataOfAddStoreList(XNode* pNode,int nUserID);

	//��ȡȫ���ڵ㣨���ݿ������߻����ߣ�
	void AddSendDataOfGetAllNode();

	//��ȡ�豸��Ϣ
	void AddSendDataOfGetDeviceInfo();

	//��ȡ�ڵ�����״̬
	void AddSendDataOfGetNodeByChannel();

	//����ͨ�����������ȡ�ڵ㲿����Ϣ
	void AddSendDataOfGetNodeInfo(XNodeManage* pNodeManage);

	//��ȡ�ڵ���ϸ��Ϣ
	void AddSendDataOfGetNodeDetailInfo(XNodeManage* pNodeManage);

	//��ȡ���нڵ���Ϣ
	void AddSendDataOfGetNodeAllDetailInfo(int nNodeID);

	//���Ľڵ���Ϣ
	void AddSendDataOfUpdateNodeGroup(int nNodeID,int nGroupID,int nMark);
	void AddSendDataOfUpdateNodeGroupMaster(int nNodeID,int nMasterID,int nMark);

	//�����û�master
	//void AddSendDataOfUpdateNodeMaster(int nNodeID,int nMatser,int nMark);

	//��ѯ�ڵ�״̬
	void AddSendDataOfGetNodeStatus(XNodeManage* pNodeManage);
	void AddSendDataOfGetNodeStatus(int nNodeID1,int nNodeID2);

	//��ȡ��¼�û�
	void AddSendDataOfGetLoginUser();

	//��ѯ��¼�û�״̬
	void AddSendDataOfGetLoginUserStatus(XNodeManage* pNodeManage);
	void AddSendDataOfGetLoginUserStatus(int nUserID);

	//�ڵ��¼
	void AddSendDataOfNodeLogin(int nNodeID,CString szUserName);

	//�ڵ��˳�
	void AddSendDataOfNodeLogOut(int nNodeID);

	//�ӹ�
	void AddSendDataOfTakeOver(int nNodeID,int nTargetID,BOOL bExclusive);

	//�˳��ӹ�
	void AddSendDataOfTakeOverCancel(int nNodeID);

	//Ԥ��
	void AddSendDataOfPreview(int nNodeID,int nTargetID);

	//��������
	void AddSendDataOfAlterNodeName(int nNodeID,CString szName);

	//����������Ƶģʽ
	void AddSendDataOfAlterAudioModel(int nNodeID,int nAudioModel);

	//������ƵԴ
	void AddSendDataOfAlterAudioSrc(int nNodeID,int nAudioSrc);

	//��������ϵͳ
	void AddSendDataOfAlterHidModel(int nNodeID,int nHidModel);

	//���÷���ģʽ
	void AddSendDataOfAlterSplitScreenModel(int nNodeID,int nScreenModel);

	//��������ֱ�����Ϣ
	void AddSendDataOfAlterResoluationIndex(int nNodeID,int nResIndex);

	//�������ģʽ
	void AddSendDataOfAlterOutModel(int nNodeID,int nOutModel);

	//��ȡ�����л�״̬
	void AddSendDataOfGetMatrixStatus();

	//�����л�
	void AddSendDataOfMatrix(int nInNodeChannel,int nOutNodeChannel);
	void AddSendDataOfMatrix(XNodeManage* pNodeManage,int nInputChannel);

	//����OSD��ͼ
	void AddSendDataOfOSDImage(XNodeManage* pNodeManage,int nIndex);

	//����OSD��ͼ
	void AddSendDataOfHideOSDImage(int nShow,int nChannel);

	void AddSendDataOfAlterBindCfg(int nNodeID,int bBindCfg);
	void AddSendDataOfAlterBindNodeID(int nNodeID,int bBindNodeID);

	//��ݼ�
	void AddSendDataOfAlterHotKey(int nNodeID,MAP_HOTKEY& MapHotKey);

	//��ȡ�ڵ���
	void AddSendDataOfReadNodeGroup();

	//��ȡ���߽ڵ���
	void AddSendDataOfReadOnLineNodeGroup();

	//��ȡ�ڵ���ϸ��Ϣ
	void AddSendDataOfNodeGroupInfo(XNodeManage* pNodeManage);

	//������ϯ
	void AddSendDataOfUpdataSeatArrage(XNodeGroupInfo& nodeGroupInfo);
	void AddSendDataOfUpdataMasterSeatArrage(XNodeGroupInfo& nodeGroupInfo);

	//�������ϯ
	void AddSendDataOfAddSeatArrage(XNodeGroupInfo& nodeGroupInfo);

	//��ȡ�������б�
	void AddSendDataOfMainAndSecondList();

	//��ѯ������
	void AddSendDataOfQueryMainAndSecond(int nGroupID);

	//���������
	void AddSendDataOfMainAndSecond(XNodeGroupInfo& nodeGroupInfo);

	//ɾ���ڵ���
	void AddSendDataOfDelNodeGroup(XNodeGroupInfo& nodeGroupInfo);

	//ɾ��������
	void AddSendDataOfDelNodeGroupMainSecond(XNodeGroupInfo& nodeGroupInfo);

	//���������� �������������
	void AddSendDataOfUpdataNodeGroupName(XNodeGroupInfo& nodeGroupInfo);
	void AddSendDataOfUpdataMasterNodeGroupName(XNodeGroupInfo& nodeGroupInfo);

	//������ϯ���ڵ�
	void AddSendDataOfUpdataSeatMasterNode(XNodeGroupInfo& nodeGroupInfo);

	//ˢ�����Ա
	void AddSendDataOfRefreashGroup(int nGroupID);
	void AddSendDataOfRefreashMainSecGroup(int nGroupID);

	//��ȡ�豸�¶�
	void AddSendDataSystemStatus();

	//�������˸
	void AddSendDataOfBlink();

	//��ѯ��������
	void AddSendDataOfNetConfig();
	//Ӧ����������
	void AddSendDataOfApplyNetConfig(XNetConfig& config);
	void AddSendDataOfSaveNetConfig(XNetConfig& config);

	//���Ƶ�
	void AddSendDataOfLightControl(int nIndex,int nStatus);

	//�����ڻ�ȡ��־
	void AddSendDataOfGetLogByData(XLogPack& logPack);
	void AddSendDataOfGetLogByUser(XLogPack& logPack);
	void AddSendDataOfGetLogByNode(XLogPack& logPack);

	//����RTCʱ��
	void AddSendDataOfRTCTime();

	//֪ͨTCP����
	void AddSendDataOfNotifyMonitor();

	//��ȡ�ļ���
	void AddSendDataOfObtainRootFolder();
	//��ȡ���ļ��кͽڵ�
	void AddSendDataOfObtainSubFolder(int nID);
	//ɾ��Ŀ¼
	void AddSendDataOfDeleteFolder(int nID);
	//���Ŀ¼
	void AddSendDataOfAddFolder(XSubFolder& sub);

	//��ȡƴ��ǽ
	void AddSendDataOfObtainSplit();
	//��ȡƴ��ǽ��Ϣ
	void AddSendDataOfQuerySplitWall(CString szName);
	//���pinjie
	void AddSendDataOfAddSplit(XSplitResult& splitInfo);
	//����ָ��
	void AddSendDataOfDraw(CString szName);
	//ƴ��ǽ������Ч
	void AddSendDataOfRefreashSplit(CString szName);
	//ɾ��ƴ��ǽ
	void AddSendDataOfDelSplit(CString szName);
	//��ȡƴ�Ӵ���
	void AddSendDataOfObtainSplitWindow(CString szName,BOOL bFirst=FALSE);
	//��ȡ������Ϣ
	void AddSendDataOfObtainSplitWindowInfo(CString szSplitName,int nSignalID);
	//����
	void AddSendDataOfAddSignal(CString szName,XSignal& signal);
	//�رմ���
	void AddSendDataOfDelSignal(CString szName,int nID);
	//���
	void AddSendDataOfClearSignal(CString szName);
	//ƴ��ǽ���ռ���б�
	void AddSendDataOfLevelUseList(CString szName);
	//�����źŲ��
	void AddSendDataOfAlterLevel(CString szName,XSignalLevel& level);
	//��ȡƴ�ӳ���
	void AddSendDataOfObtainSplitScene();
	//��ȡ�����е�ǽ�б�
	void AddSendDataOfObtainWallList(CString szName);
	//���ó���
	void AddSendDataOfOpenScene(CString szSceneName,CString szWallName,int nOpt);

	//��ѯ������ǽ��Ϣ
	void AddSendDataOfQuerySceneWall(CString szSceneName,CString szWallName);

	//���ƴ�ӳ���
	void AddSendDataOfAddSplitScene(CString szSceneName);
	//��������ǽ
	void AddSendDataOfSaveWallToNewScene(CString szSceneName,CString szSplit,BOOL bLast);
	//��ȡ������
	void AddSendDataOfObtainSceneGroup(CString szSceneName);
	//������
	void AddSendDataOfSetSceneGroup(CString szSceneName,CString szGroup,BOOL bAlter=FALSE);
	//ɾ������
	void AddSendDataOfDeleteSplitScene(CString szSceneName);

private:

	static XSendDataManage* m_pSendDataManage;

	XDelegateSendDataManage* m_pDelegate;

	unsigned short m_nTotalPacket;

	unsigned short m_nCurPacket;

	unsigned short m_nPacketLen;
};