#pragma once
#define INITIAL_CAPACITY	20480 * 2 
#define MAX_DATA_CAPACITY	((UINT)0xffffffff)


/*
DATA : WORD
TIME : tm
defined at stdafx.h
*/
typedef WORD DATA;
typedef tm TIME;

class CClientComData
{
protected:
	DATA *m_pCPUData;
	DATA *m_pMemoryData;
	DATA *m_pNetworkData;
	int m_graphHead, m_graphTail;
	//-1 -> 설정안한상태
	int m_graphCurIndex; 
	TIME m_time;

public:
	inline DATA GetCPU(int time) { return m_pCPUData[time]; }
	inline DATA GetMemory(int time) { return m_pMemoryData[time]; }
	inline DATA GetNetwork(int time) { return m_pNetworkData[time]; }

	
public:
	CClientComData();
	~CClientComData();
};

