// ClientListView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "ClientListView.h"


// CClientListView

IMPLEMENT_DYNAMIC(CClientListView, CWnd)

CClientListView::CClientListView(CBoardView *pBoardView)
{
	m_pBoardView = pBoardView;
}

CClientListView::~CClientListView()
{
	if(m_pBoardView) delete m_pBoardView;
}


BEGIN_MESSAGE_MAP(CClientListView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	

END_MESSAGE_MAP()



// CClientListView message handlers




void CClientListView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	
					  
}


int CClientListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_clientListCtrl.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++g_wnd_id_a);
	m_commandCtrl.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++g_wnd_id_a);

	m_commandCtrl.SetBoardViewWnd(m_pBoardView);
	m_commandCtrl.SetClientListCtrl(&m_clientListCtrl);

	return 0;
}


void CClientListView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	CRect r, command;
	GetClientRect(&r);
	command = r;
	r.bottom = r.top + (r.Height() * 7) / 10;
	command.top = r.bottom;
	m_clientListCtrl.SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), 0);
	m_commandCtrl.SetWindowPos(NULL, command.left, command.top, command.Width(), command.Height(), 0);
}
