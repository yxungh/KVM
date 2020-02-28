#pragma once

class XData
{
public:

	XData();
	~XData();


public:

	inline void SetDataLen(int n){m_nDataLen=n;}

	inline int GetDataLen(){return m_nDataLen;}

	void SetData(unsigned char* pData);

	inline unsigned char* GetData(){return m_pData;}

	inline void SetPacket(int n){m_nPacket=n;}

	inline int GetPacket(){return m_nPacket;}

	inline void SetPacketIndex(int n){m_nPacketIndex=n;}

	inline int GetPacketIndex(){return m_nPacketIndex;}

	void DeleteData();

private:

	unsigned char* m_pData;

	unsigned int m_nDataLen;

	int m_nPacket;

	int m_nPacketIndex;
};