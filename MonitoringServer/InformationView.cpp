// InformationView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "InformationView.h"


// CInformationView

IMPLEMENT_DYNAMIC(CInformationView, CWnd)

CInformationView::CInformationView()
{
	m_pInfoDataView = NULL;
	m_checkedSize = 0;
}

CInformationView::~CInformationView()
{
	if (m_pInfoDataView) {
		for (int i = 0; i < MAX_INFO_VIEW_NUMBER; i++) {
			m_pInfoDataView[i].DestroyWindow();
		}
		delete []m_pInfoDataView;

	}
}


BEGIN_MESSAGE_MAP(CInformationView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CInformationView message handlers



//이 함수가 돌고, 자식의 페인트가 돈다.
void CInformationView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(233, 233, 233));
	
	int size = m_pClientListCtrl->GetCheckedListSize();
	m_checkedSize = 0;
	int width = r.Width() / 8;
	CStringList list;
	for (int i = size-1; i >= 0; i--) {
		if (m_pChekedList[i]) {
			CString str;
			str.Format(_T("COM%d"), i+1);
			m_pInfoDataView[m_checkedSize].SetComputer(str);
			list.AddTail(str);
			/*CBrush brush, *p_old_brush;
			brush.CreateSolidBrush(RGB(242, 242, 242));
			p_old_brush = dc.SelectObject(&brush);
			dc.SelectObject(p_old_brush);
			*/
			dc.TextOutW(r.left + m_checkedSize * width, r.top + 5, str);
			m_checkedSize++;
		}
	}



	if (m_checkedSize == 0) {
		for (int i = 0; i < MAX_INFO_VIEW_NUMBER; i++) {
			m_pInfoDataView[i].ShowWindow(SW_HIDE);
		}
		dc.FillSolidRect(r, RGB(244, 244, 244));
		dc.DrawText(_T("선택된 클라이언트가 없습니다."), r, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}

	
}


int CInformationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pInfoDataView = new CInformationDataView[MAX_INFO_VIEW_NUMBER];
	for (int i = 0; i < MAX_INFO_VIEW_NUMBER; i++) {
		m_pInfoDataView[i].Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++g_wnd_id_b);
	}


	return 0;
}


void CInformationView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(&r);

	for (int i = 0; i < MAX_INFO_VIEW_NUMBER; i++) {
		m_pInfoDataView[i].ShowWindow(SW_SHOW);
		m_pInfoDataView[i].SetWindowPos(NULL, r.left, r.top + m_captionHeight, r.Width(), r.Height() - m_captionHeight, 0);
	}
}


void CInformationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect r;
	GetClientRect(&r);
	r.bottom = m_captionHeight;
	int width = r.Width() / 8;
	if (PtInRect(&r, point)) {
		CRect tab = r;
		for (int i = 0; i < m_checkedSize; i++) {
			tab.left = r.left + width * (i);
			tab.right = r.left + width * (i+1);
			if (PtInRect(&tab, point)) {
				m_pInfoDataView[i].ShowWindow(SW_SHOW);
			}else m_pInfoDataView[i].ShowWindow(SW_HIDE);
		}
	}

	CCommonView::OnLButtonDown(nFlags, point);
}
