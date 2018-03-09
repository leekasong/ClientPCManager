// InformationDataView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "InformationDataView.h"


// CInformationDataView

IMPLEMENT_DYNAMIC(CInformationDataView, CWnd)

CInformationDataView::CInformationDataView()
{
	m_pSWView = NULL;
	m_pProcessorView = NULL;
	m_pDiskView = NULL;
}

CInformationDataView::~CInformationDataView()
{
	if (m_pSWView) delete m_pSWView;
	if (m_pProcessorView) delete m_pProcessorView;
	if (m_pDiskView) delete m_pDiskView;


}


BEGIN_MESSAGE_MAP(CInformationDataView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CInformationDataView message handlers




void CInformationDataView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	//dc.FillSolidRect(r, RGB(255, 0, 0));

	dc.TextOutW(r.left, r.top, m_comName);

}

void CInformationDataView::SetComputer(CString comName) {
	m_comName = comName;
	m_pProcessorView->SetProcessorData(comName);
	
}

int CInformationDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pSWView = new CInformationDataSWView;
	m_pSWView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 25000);

	m_pProcessorView = new CInformationProcessorDataView;
	m_pProcessorView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 25000);

	m_pDiskView = new CInformationDiskView;
	m_pDiskView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 25000);


	return 0;
}


void CInformationDataView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(&r);
	int margin = 10;
	int leftMargin = 15;
	m_pSWView->SetWindowPos(NULL, r.left + r.Width() / 2 + leftMargin
		, r.top + margin, r.Width() / 2 - margin - leftMargin
		, r.Height() - 2 * margin, 0);

	m_pProcessorView->SetWindowPos(NULL, r.left + margin, r.top + margin,
		r.Width() / 2 - margin - leftMargin, r.Height() / 2 - margin - margin / 2, 0);

	m_pDiskView->SetWindowPos(NULL
		, r.left + margin, r.top + r.Height() / 2 + margin / 2,
		r.Width() / 2 - margin - leftMargin, r.Height() / 2 - margin / 2 - margin, 0);


}
