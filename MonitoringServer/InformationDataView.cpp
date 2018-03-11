// InformationDataView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "InformationDataView.h"


// CInformationDataView

IMPLEMENT_DYNAMIC(CInformationDataView, CWnd)

CInformationDataView::CInformationDataView()
{
	m_pInformationSWView = NULL;
	m_pInformationDiskView = NULL;
	m_pProcessorView = NULL;
}

CInformationDataView::~CInformationDataView()
{
	if (m_pInformationSWView) delete m_pInformationSWView;
	if (m_pProcessorView) delete m_pProcessorView;
	if (m_pInformationDiskView) delete m_pInformationDiskView;
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
	dc.FillSolidRect(r, RGB(240, 240, 240));

}

void CInformationDataView::SetComputer(CString comName) {
	m_comName = comName;
}

int CInformationDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pInformationSWView = new CInformationDataSWView;
	m_pProcessorView = new CInformationProcessorDataView;
	m_pInformationDiskView = new CInformationDiskView;
	


	m_pInformationSWView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++g_wnd_id_b);
	m_pProcessorView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++g_wnd_id_b);
	m_pInformationDiskView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++g_wnd_id_b);
	

	return 0;
}


void CInformationDataView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(&r);


	int margin = 10;
	int midMargin = 30;
	int w = r.Width(); int h = r.Height();
	int left = r.left;
	int top = r.top;
	m_pInformationSWView->SetWindowPos(NULL, left + w / 2 + midMargin / 2, top + margin
		, w / 2 - margin - midMargin / 2, h - margin * 2, 0);

	m_pProcessorView->SetWindowPos(NULL, left + margin, top + margin
		, w / 2 - margin - midMargin / 2, h / 2 - margin - margin / 2, 0);

	m_pInformationDiskView->SetWindowPos(NULL, left + margin, top + h / 2 + margin / 2
		, w / 2 - margin - midMargin / 2, h / 2 - margin - margin / 2, 0);

}
