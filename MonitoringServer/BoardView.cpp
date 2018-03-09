// BoardView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "BoardView.h"


// CBoardView

IMPLEMENT_DYNAMIC(CBoardView, CWnd)

CBoardView::CBoardView()
{
	m_pViewWnd = NULL;
}

CBoardView::~CBoardView()
{
	if (m_pViewWnd) delete m_pViewWnd;
}


BEGIN_MESSAGE_MAP(CBoardView, CWnd)
	
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CBoardView message handlers






void CBoardView::SetViewWnd(CWnd *pViewWnd) {
	this->m_pViewWnd = pViewWnd;
	this->m_pViewWnd->ShowWindow(SW_SHOW);
	CRect r;
	GetClientRect(&r);
	this->PostMessage(WM_SIZE, r.Width(), r.Height());
}


int CBoardView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	return 0;
}


void CBoardView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(&r);


	if (m_pViewWnd != NULL) {
		m_pViewWnd->SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), 0);
		m_pViewWnd->PostMessage(UM_COMMAND_CHNAGED, 0, 0);
	}
	
}


void CBoardView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages

	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(255, 0, 0));
}
