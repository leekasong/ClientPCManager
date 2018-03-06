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
	int size; //CPU, Memory, Network 모두 같은 시기에 같이 측정하므로 개수는 동일
	m_pClientDB->GetCPUUsage(_T("COM21"), NULL, &size);

	//클라이언트 피씨 정보 구조체 할당
	m_pClientRealTimeData = new CLIENT_REALTIME_DATA_EX;
	::ZeroMemory(m_pClientRealTimeData, sizeof(CLIENT_REALTIME_DATA_EX));

	//피씨 이름
	int comNameLen = _tcslen(_T("COM21"));
	m_pClientRealTimeData->pName = new TCHAR[comNameLen + 1]{ 0 };
	_tcscpy(m_pClientRealTimeData->pName, _T("COM21"));

	//CPU, Memory, Network
	m_pClientRealTimeData->cpuList = new int[size] {0};
	m_pClientRealTimeData->memoryList = new int[size] {0};
	m_pClientRealTimeData->networkList = new int[size] {0};

	m_pClientDB->GetCPUUsage(_T("COM21"), m_pClientRealTimeData->cpuList, &size);
	m_pClientDB->GetMemoryUsage(_T("COM21"), m_pClientRealTimeData->memoryList, &size);
	m_pClientDB->GetNetworkUsage(_T("COM21"), m_pClientRealTimeData->networkList, &size);
	
	//측정된 값의 갯수
	CStringList list;
	m_pClientDB->GetRealTime(_T("COM21"), list);
	POSITION pos = list.GetHeadPosition();
	
	for (int i = 0; pos != NULL; i++) {
		list.GetNext(pos);
		m_pClientRealTimeData->timeNumber++;
	}

	//측정 시간
	m_pClientRealTimeData->pTimeList = new TCHAR *[m_pClientRealTimeData->timeNumber] {0};
	
	pos = list.GetHeadPosition();
	for (int i = 0; pos != NULL; i++) {
		CString tmp = list.GetNext(pos);
		int len = tmp.GetLength();
		m_pClientRealTimeData->pTimeList[i] = new TCHAR[len + 1]{ 0 };
		_stprintf(m_pClientRealTimeData->pTimeList[i], _T("%s"), tmp);
	}

}

CGraphWnd::~CGraphWnd()
{
	int cnt = m_pClientRealTimeData->timeNumber;
	for (int i = 0; i < cnt; i++) {
		delete[] m_pClientRealTimeData->pTimeList[i];
	}
	delete[] m_pClientRealTimeData->pTimeList;

	delete[] m_pClientRealTimeData->pName;
	delete[] m_pClientRealTimeData->cpuList;
	delete[] m_pClientRealTimeData->memoryList;
	delete[] m_pClientRealTimeData->networkList;
	if (m_pClientRealTimeData) delete m_pClientRealTimeData;
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
	

	int cnt = m_pClientRealTimeData->timeNumber;
	for (int i = 0; i < cnt; i++) {
		str.Format(_T("CPU : %d | Memory : %d | Network : %d | Time : %s"),
			m_pClientRealTimeData->cpuList[i], m_pClientRealTimeData->memoryList[i]
			, m_pClientRealTimeData->networkList[i], m_pClientRealTimeData->pTimeList[i]);

		dc.TextOutW(r.left + 500*i, r.top + 10, str);
	}
	
}


afx_msg LRESULT CGraphWnd::OnUmCommandChnaged(WPARAM wParam, LPARAM lParam)
{
	RedrawWindow();
	return 0;
}
