#pragma once
#include <afxdb.h>
extern CString g_id_str, g_pw_str, g_dsn_str[3];
extern CString g_cur_dsn;
extern CString g_client_table;

#define KS_DSN_REALTIME	0
#define KS_DSN_SW	1
#define KS_DSN_HW	2

#define KS_REALTIME_TABLE	_T("history")
#define KS_SW_TABLE _T("installed_sw")
#define KS_HW_DISK_TABLE	_T("client_disk")	
#define KS_HW_GPU_TABLE	_T("client_gpu")
#define KS_HW_PROCESSOR_TABLE _T("client_processor")

typedef struct _CLIENT_REALTIME_DATA {
	TCHAR *pName;
	int _cpu;
	int memory;
	int network;
	TCHAR *pTime;
} CLIENT_REALTIME_DATA, *PCLIENT_REALTIME_DATA;

typedef struct _CLIENT_SOFTWARE_DATA {
	TCHAR *pName;
	CStringList SWNameList;
} CLIENT_SOFTWARE_DATA, *PCLIENT_SOFTWARE_DATA;

typedef struct _CLIENT_DISK {
	TCHAR *pCapacity;
	TCHAR *pUsed;
	TCHAR *pName;
} CLIENT_DISK, *PCLIENT_DISK;


typedef struct _CLIENT_GPU {
	int number;
	TCHAR *pName;
} CLIENT_GPU, *PCLIENT_GPU;

typedef struct _CLIENT_PROCESSOR {
	int number;
	TCHAR *pName;
} CLIENT_PROCESSOR, *PCLIENT_PROCESSOR;

typedef struct _CLIENT_HARDWARE_DATA {
	TCHAR *pComName;
	PCLIENT_DISK pDiskList;
	PCLIENT_PROCESSOR processorList;
	PCLIENT_GPU gpuList;
} CLIENT_HARDWARE_DATA, *PCLIENT_HARDWARE_DATA;

void KS_DBInit(CString id, CString password);

void KS_SetTable(int dsnName, CString table);

//해당 엔트리가 있는지 없는지를 리턴으로 판단
//테이블에서 모든 튜플을 가져오는 함수
BOOL KS_SelectByComName(CString comName, CStringList& list, int dsnName, CString table);


//리얼타임
BOOL InsertRealTimeData(PCLIENT_REALTIME_DATA pData);

//솦트
BOOL InsertSWData(PCLIENT_SOFTWARE_DATA pData, CString table);

//하드웨어
void InsertDiskData(CString comName, PCLIENT_DISK pDiskList);

void InsertProcesssorData(CString comName, PCLIENT_PROCESSOR pProcessorList);

void InsertGPUData(CString comName, PCLIENT_GPU pGPUList);
BOOL InsertHWData(PCLIENT_HARDWARE_DATA pData);

void ClearCurrentTable();