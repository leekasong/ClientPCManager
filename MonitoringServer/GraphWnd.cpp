// GraphWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "GraphWnd.h"


// CGraphWnd

IMPLEMENT_DYNAMIC(CGraphWnd, CWnd)

CGraphWnd::CGraphWnd()
{
	m_pClientDB = new ClientDBData;
	
	////리얼타임 정보들은 동기화되므로 임의의 리소스에서 크기를 얻어오면 된다.
	//m_pClientDB->GetCPUUsage(_T("COM21"), NULL, &m_realTimeDataListSize);

	////클라이언트 피씨 정보 구조체 할당
	//m_pClientRealTimeDataList = new CLIENT_REALTIME_DATA[m_realTimeDataListSize];
	//::ZeroMemory(m_pClientRealTimeDataList, sizeof(CLIENT_REALTIME_DATA) * m_realTimeDataListSize);

	////CPU, Memory, Network
	//int *pCpuList = new int[m_realTimeDataListSize] {0};
	//int *pMemoryList = new int[m_realTimeDataListSize] {0};
	//int *pNetworkList = new int[m_realTimeDataListSize] {0};

	//m_pClientDB->GetCPUUsage(_T("COM21"), pCpuList, &m_realTimeDataListSize);
	//m_pClientDB->GetMemoryUsage(_T("COM21"), pMemoryList, &m_realTimeDataListSize);
	//m_pClientDB->GetNetworkUsage(_T("COM21"), pNetworkList, &m_realTimeDataListSize);


	////시간
	//CStringList list;
	//m_pClientDB->GetRealTime(_T("COM21"), list);
	//POSITION pos = list.GetHeadPosition();

	//for (int i = 0; i < m_realTimeDataListSize; i++) {
	//	//피씨 이름
	//	int comNameLen = _tcslen(_T("COM21"));
	//	m_pClientRealTimeDataList[i].pName = new TCHAR[comNameLen + 1]{ 0 };
	//	_tcscpy(m_pClientRealTimeDataList[i].pName, _T("COM21"));

	//	//CPU, Memory, Network
	//	m_pClientRealTimeDataList[i]._cpu = pCpuList[i];
	//	m_pClientRealTimeDataList[i].memory = pMemoryList[i];
	//	m_pClientRealTimeDataList[i].network = pNetworkList[i];

	//	//time
	//	CString tmp = list.GetNext(pos);
	//	int timeLen = tmp.GetLength();
	//	m_pClientRealTimeDataList[i].pTime = new TCHAR[timeLen + 1]{ 0 };
	//	_tcscpy(m_pClientRealTimeDataList[i].pTime, tmp);
	//}

	//delete[] pCpuList; 
	//delete[] pMemoryList; 
	//delete[] pNetworkList;


	//S/W
	m_pSWData = new CStringList;



	////Disk
	//m_pClientDB->GetDiskUsage(_T("COM19"), NULL, &m_diskSize);

	//m_pClientDisk = new CLIENT_DISK[m_diskSize];
	//for (int i = 0; i < m_diskSize; i++) {
	//	m_pClientDisk[i].pCapacity = new TCHAR[10]{ 0 };
	//	m_pClientDisk[i].pName = new TCHAR[10]{ 0 };
	//	m_pClientDisk[i].pUsed = new TCHAR[10]{ 0 };


	//}
	//
	//m_pClientDB->GetDiskUsage(_T("COM19"), m_pClientDisk, &m_diskSize);



	//Processor
	m_pClientDB->GetProcessorData(_T("COM19"), NULL, &m_processorSize);

	m_pClientProcessor = new CLIENT_PROCESSOR[m_processorSize];
	for (int i = 0; i < m_processorSize; i++) {
		m_pClientProcessor[i].pName = new TCHAR[30]{ 0 };
	}
	
	m_pClientDB->GetProcessorData(_T("COM19"), m_pClientProcessor, &m_processorSize);

	m_pClientDB->GetGPUData(_T("COM19"), NULL, &m_gpuSize);
	m_pClientGPU = new CLIENT_GPU[m_gpuSize]{ 0 };
	for (int i = 0; i < m_gpuSize; i++) {
		m_pClientGPU[i].pName = new TCHAR[30]{ 0 };
	}
	m_pClientDB->GetGPUData(_T("COM19"), m_pClientGPU, &m_gpuSize);
}

CGraphWnd::~CGraphWnd()
{
	/*
	for (int i = 0; i < m_realTimeDataListSize; i++) {
		delete[] m_pClientRealTimeDataList[i].pName;
		delete[] m_pClientRealTimeDataList[i].pTime;
	}

	delete[] m_pClientRealTimeDataList;*/

	delete m_pSWData;


	////disk
	//for (int i = 0; i < m_diskSize; i++) {
	//	delete[] m_pClientDisk[i].pCapacity;
	//	delete[] m_pClientDisk[i].pName;
	//	delete[] m_pClientDisk[i].pUsed;
	//}

	//delete[] m_pClientDisk;

	//프로세서
	for (int i = 0; i < m_processorSize; i++) {
		delete[] m_pClientProcessor[i].pName;
	}


	delete[] m_pClientProcessor;

	//지피유
	
	for (int i = 0; i < m_gpuSize; i++) {
		delete[] m_pClientGPU[i].pName;
	}
	delete[] m_pClientGPU;

	//db
	delete m_pClientDB;
}


BEGIN_MESSAGE_MAP(CGraphWnd, CWnd)
	ON_WM_PAINT()
	ON_MESSAGE(UM_COMMAND_CHNAGED, &CGraphWnd::OnUmCommandChnaged)
END_MESSAGE_MAP()



// CGraphWnd message handlers




void CGraphWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(255, 255, 0));
	CString str;
	str.Format(_T("%d"), this);

	//for (int i = 0; i < m_realTimeDataListSize; i++) {
	//	str.Format(_T("CPU : %d | Memory : %d | Network : %d | Time : %s"),
	//		m_pClientRealTimeDataList[i]._cpu, m_pClientRealTimeDataList[i].memory
	//		, m_pClientRealTimeDataList[i].network, m_pClientRealTimeDataList[i].pTime);

	//	dc.TextOutW(r.left + 500*i, r.top + 10, str);
	//}
	//

	m_pClientDB->GetInstalledSW(_T("COM20"), *m_pSWData);
	POSITION pos = m_pSWData->GetHeadPosition();
	int cnt = 1;
	while (pos != NULL) {
		str = m_pSWData->GetNext(pos);
		dc.TextOutW(r.left + 500, r.top + 100 * cnt, str);
		cnt++;
	}
	m_pSWData->RemoveAll();

	////for (int i = 0; i < m_diskSize; i++) {
	////	dc.TextOutW(r.left + 500 * i, r.top + 200, m_pClientDisk[i].pCapacity);
	////	dc.TextOutW(r.left + 500 * i, r.top + 300, m_pClientDisk[i].pName);
	////	dc.TextOutW(r.left + 500 * i, r.top + 400, m_pClientDisk[i].pUsed);
	////}
	CString procData;
	for (int i = 0; i < m_processorSize; i++) {

		procData.Format(_T("%d"), m_pClientProcessor[i].number);
		dc.TextOutW(r.left + 500 * i, r.top + 200, procData);
		dc.TextOutW(r.left + 500 * i, r.top + 300, m_pClientProcessor[i].pName);
	}

	for (int i = 0; i < m_gpuSize; i++) {

		procData.Format(_T("%d"), m_pClientGPU[i].number);
		dc.TextOutW(r.left + 500 * i, r.top + 200, procData);
		dc.TextOutW(r.left + 500 * i, r.top + 300, m_pClientGPU[i].pName);
	}
}


afx_msg LRESULT CGraphWnd::OnUmCommandChnaged(WPARAM wParam, LPARAM lParam)
{
	RedrawWindow();
	return 0;
}
