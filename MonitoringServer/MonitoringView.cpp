#include "stdafx.h"
#include "MonitoringView.h"


CMonitoringView::CMonitoringView()
{
}


CMonitoringView::~CMonitoringView()
{
}
BEGIN_MESSAGE_MAP(CMonitoringView, CCommonView)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CMonitoringView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(255, 255, 0));
}
