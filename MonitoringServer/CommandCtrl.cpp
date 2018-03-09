// CommandCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "CommandCtrl.h"


// CCommandCtrl

IMPLEMENT_DYNAMIC(CCommandCtrl, CWnd)

CCommandCtrl::CCommandCtrl()
{
	TCHAR fileName[_MAX_FNAME] = { 0 };
	for (int i = 0; i < MAX_BUTTON_NUMBER; i++) {
		_stprintf(fileName, _T("%d.BMP"), i + 1);
		m_pCustomButton[i] = new CCustomButton(fileName);
	}

	
}

CCommandCtrl::~CCommandCtrl()
{
	for (int i = 0; i < MAX_BUTTON_NUMBER; i++) {
		delete m_pCustomButton[i];
		delete m_pViewList[i];
	}
	
}


BEGIN_MESSAGE_MAP(CCommandCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(UM_COMMAND_CHNAGED, &CCommandCtrl::OnUmCommandChnaged)
END_MESSAGE_MAP()



// CCommandCtrl message handlers




void CCommandCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	
}


int CCommandCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	TCHAR *text[MAX_BUTTON_NUMBER] = { _T("Monitoring"), _T("History"), _T("Information"), _T("Support") };
	for (int i = 0; i < MAX_BUTTON_NUMBER; i++) {
		m_pCustomButton[i]->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++g_wnd_id_a);
		m_pCustomButton[i]->SetButtonText(text[i], _tcslen(text[i]) + 1);
	}
	
	
	return 0;
}


void CCommandCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(&r);
	int h = r.Height() / MAX_BUTTON_NUMBER;
	for (int i = 0; i < MAX_BUTTON_NUMBER; i++) {
		m_pCustomButton[i]->SetWindowPos(NULL, r.left, r.top + h*i, r.Width() - 1, h, 0);
		
	}

	


}


afx_msg LRESULT CCommandCtrl::OnUmCommandChnaged(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= 1 && wParam <= 4) {
		int idx = wParam - 1;
		for (int i = 0; i < 4; i++) {
			m_pViewList[i]->ShowWindow(SW_HIDE);
			
			m_pViewList[i]->ClearCheckedList();
		}
		m_pViewList[idx]->Notify();
		m_pBoardView->SetViewWnd(m_pViewList[idx]);
	}
	return 0;
}

void CCommandCtrl::SetBoardViewWnd(CBoardView *pBoardView) {
	m_pBoardView = pBoardView;
	for (int i = 0; i < MAX_BUTTON_NUMBER; i++) {
		m_pViewList[i]->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), m_pBoardView, ++g_wnd_id_b);
		m_pBoardView->SetViewWnd(m_pViewList[i]);
	}
	
	
}

void CCommandCtrl::SetClientListCtrl(CClientListCtrl *pClientListCtrl) {
	for (int i = 0; i < MAX_BUTTON_NUMBER; i++) {
		m_pViewList[i]->SetClientListCtrl(pClientListCtrl);
	}
}