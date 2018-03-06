// InformationDataView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "InformationDataView.h"


// CInformationDataView

IMPLEMENT_DYNAMIC(CInformationDataView, CWnd)

CInformationDataView::CInformationDataView()
{

}

CInformationDataView::~CInformationDataView()
{
}


BEGIN_MESSAGE_MAP(CInformationDataView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CInformationDataView message handlers




void CInformationDataView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(255, 0, 0));

	dc.TextOutW(r.left, r.top, m_comName);
}

void CInformationDataView::SetComputer(CString comName) {
	m_comName = comName;
}