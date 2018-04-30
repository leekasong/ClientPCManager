#include "stdafx.h"
#include "HistoryView.h"
#include "resource.h"

CHistoryView::CHistoryView()
{
	m_displayMode = 4;
	m_checkedSize = 0;
}


CHistoryView::~CHistoryView()
{
	
}

BEGIN_MESSAGE_MAP(CHistoryView, CCommonView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_MESSAGE(UM_CHANGE_GRAPH_MODE, &CHistoryView::OnUmChangeGraphMode)
END_MESSAGE_MAP()


void CHistoryView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r, tabRect;
	GetClientRect(&r);
	tabRect.SetRect(r.left, r.top, r.right, r.top + 30);
	dc.FillSolidRect(r, RGB(244, 244, 244));
	dc.FillSolidRect(tabRect, RGB(233, 233, 233));


	int size = m_pClientListCtrl->GetCheckedListSize();
	m_checkedSize = 0;
	int width = r.Width() / 8;
	CStringList list;
	dc.SetTextColor(RGB(0, 0, 0));
	for (int i = size - 1; i >= 0; i--) {
		if (m_pChekedList[i]) {
			CString str;
			str.Format(_T("COM%d"), i + 1);
			list.AddTail(str);
			dc.TextOutW(r.left + m_checkedSize * width, r.top + 5, str);
			m_checkedSize++;
		}
	}

	if (m_checkedSize == 0) {
		/*for (int i = 0; i < MAX_INFO_VIEW_NUMBER; i++) {
			m_pInfoDataView[i].ShowWindow(SW_HIDE);
		}*/
		dc.FillSolidRect(r, RGB(244, 244, 244));
		dc.DrawText(_T("선택된 클라이언트가 없습니다."), r, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}

}


int CHistoryView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CCommonView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndMinimap.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), this, ++g_wnd_id_b);
	int nID = g_wnd_id_b;
	for (int i = 0; i < 4; i++) {
		nID++;
		m_wndGraph[i].Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID);
		m_wndMinimap.SetGraphWnd(&m_wndGraph[i], i);
		m_wndGraph[i].SetMinmapWnd(&m_wndMinimap);
	}
	m_wndScrollBar.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++nID);
	m_wndScrollBar.SetMinimapWnd(&m_wndMinimap);

	
	return 0;
}


void CHistoryView::OnDestroy()
{
	CCommonView::OnDestroy();

}


void CHistoryView::OnSize(UINT nType, int cx, int cy)
{
	CCommonView::OnSize(nType, cx, cy);


	ChangeDisplayMode();
}

void CHistoryView::ChangeDisplayMode() {
	CRect r;
	GetClientRect(&r);

	int left = 10, top = 40;
	m_wndMinimap.SetWindowPos(NULL, left + 30, top, r.Width() - (left + 30), 50, 0);

	top += 50;

	//막대 세로 크기는 10 정도 잡는다. 막대와 미니맵, 막대와 그래프사이를 벌리기 위해 각각 10, 18씩 띄운다.
	//따라서 막대의 위치는 (100, 60) ~ (width - 100, 70)
	top += 10;

	m_wndScrollBar.SetWindowPos(NULL, left + 30, top, r.Width() - (left + 30), 12, 0);


	top += 30;
	//그래프 위치는 (100, 80) ~ 

	int top_margin = 50;
	int graph_height = 0;
	int graph_width = 0;
	//m_displayMode = 1;
	switch (m_displayMode)
	{
	case 1:
		graph_height = r.Height() - top;
		m_wndGraph[0].SetWindowPos(NULL, left, top, r.Width() - left, graph_height, 0);
		m_wndGraph[1].SetWindowPos(NULL, 0, 0, 0, 0, 0);
		m_wndGraph[2].SetWindowPos(NULL, 0, 0, 0, 0, 0);
		m_wndGraph[3].SetWindowPos(NULL, 0, 0, 0, 0, 0);
		break;
	case 2:
		graph_height = (r.Height() - top) / 2;
		m_wndGraph[0].SetWindowPos(NULL, left, top, r.Width() - left, graph_height, 0);
		top += graph_height;
		m_wndGraph[1].SetWindowPos(NULL, left, top + 10, r.Width() - left, graph_height - 10, 0);
		m_wndGraph[2].SetWindowPos(NULL, 0, 0, 0, 0, 0);
		m_wndGraph[3].SetWindowPos(NULL, 0, 0, 0, 0, 0);
		break;
	case 4:
		graph_height = (r.Height() - top) / 2;
		graph_width = (r.Width() - left) / 2;
		m_wndGraph[0].SetWindowPos(NULL, left, top, graph_width, graph_height, 0);
		m_wndGraph[1].SetWindowPos(NULL, left + graph_width + 10, top, graph_width - 10, graph_height, 0);
		m_wndGraph[2].SetWindowPos(NULL, left, top + graph_height + 10, graph_width, graph_height - 10, 0);
		m_wndGraph[3].SetWindowPos(NULL, left + graph_width + 10, top + graph_height + 10, graph_width - 10, graph_height - 10, 0);
		break;

	}

}







afx_msg LRESULT CHistoryView::OnUmChangeGraphMode(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1 || wParam == 2 || wParam == 4) {
		m_displayMode = wParam;
		ChangeDisplayMode();
	}
	return 0;
}
