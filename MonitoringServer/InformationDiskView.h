#pragma once
#include "ClientDBData.h"

#define PI	3.141592
// CInformationDiskView

typedef struct _CLIENT_DISK_USAGE {
	float usage;
	float total;
}CLIENT_DISK_USAGE;

class CInformationDiskView : public CWnd
{
	DECLARE_DYNAMIC(CInformationDiskView)
private:
	CStringList m_pDiskList;
	CClientDBData *m_pClientDB;
	CLIENT_DISK_USAGE m_diskUsageList[2];
	COLORREF m_bk_color;
private:
	void CInformationDiskView::DrawCircle(CRect baseRect, CLIENT_DISK_USAGE diskUsage, CDC *pDC);
public:
	CInformationDiskView();
	virtual ~CInformationDiskView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};


