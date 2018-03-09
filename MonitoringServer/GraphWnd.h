#pragma once
#include "CommonView.h"
#include "ClientResourceDB.h"
// CGraphWnd

//한 컴퓨터에 CPU, Memory 등은 수백가지 정보를 담는 구조체
typedef struct _CLIENT_REALTIME_DATA_EX {
	TCHAR *pName;
	int *cpuList;
	int *memoryList;
	int *networkList;
	TCHAR **pTimeList;
	int timeNumber;
}CLIENT_REALTIME_DATA_EX, *PCLIENT_REALTIME_DATA_EX;
class CGraphWnd : public CCommonView
{
	DECLARE_DYNAMIC(CGraphWnd)
private:
	
	
	PCLIENT_REALTIME_DATA_EX m_pClientRealTimeData;
	
public:
	
public:
	CGraphWnd();
	virtual ~CGraphWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
protected:
	afx_msg LRESULT OnUmCommandChnaged(WPARAM wParam, LPARAM lParam);
};


