// GraphWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "GraphWnd.h"


// CGraphWnd

IMPLEMENT_DYNAMIC(CGraphWnd, CWnd)

CGraphWnd::CGraphWnd()
{

}

CGraphWnd::~CGraphWnd()
{
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
	dc.TextOutW(r.left + 10, r.top + 10, str);
					   
}


afx_msg LRESULT CGraphWnd::OnUmCommandChnaged(WPARAM wParam, LPARAM lParam)
{
	RedrawWindow();
	return 0;
}
