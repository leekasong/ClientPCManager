// ListCtrlMoveBtn.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "ListCtrlMoveBtn.h"


// CListCtrlMoveBtn

IMPLEMENT_DYNAMIC(CListCtrlMoveBtn, CWnd)

CListCtrlMoveBtn::CListCtrlMoveBtn()
{
	m_bClicked[0] = m_bClicked[1] = FALSE;
	m_pNotifyData = new NMHDR;
}

CListCtrlMoveBtn::~CListCtrlMoveBtn()
{
	delete m_pNotifyData;
}


BEGIN_MESSAGE_MAP(CListCtrlMoveBtn, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CListCtrlMoveBtn message handlers




void CListCtrlMoveBtn::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC MemDC;
	CBitmap bmp;
	CRect r;
	GetClientRect(&r);
	bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(&bmp);
	
	CRect m_upRect = r, m_downRect = r;
	m_upRect.bottom = r.top + r.Height() / 2;
	m_downRect.top = m_upRect.bottom;
	////////////////////////////////////////////////////////////////////////
	//상 버튼 그리기

	//0,122,204 : 짙은
	//RGB(119, 201, 255) : 옅은
	
	CPen borderPen(PS_SOLID, 1, RGB(255, 255, 255)), *p_old_pen;
	p_old_pen = MemDC.SelectObject(&borderPen);
	MemDC.Rectangle(m_upRect);

	int border = 1;
	m_upRect.left += border;
	m_upRect.right -= border;
	m_upRect.top += border;
	m_upRect.bottom -= border;

	//외곽선 그리기
	CPen upPen(PS_SOLID, 1, RGB(119, 201, 255));
	MemDC.SelectObject(&upPen);
	MemDC.Rectangle(m_upRect);
	m_upRect.top += m_bClicked[0];
	MemDC.SelectObject(p_old_pen);

	//배경색채우기
	MemDC.FillSolidRect(m_upRect, RGB(218, 227, 243));

	//삼각형 그리기
	m_upRect.top += m_bClicked[0];
	POINT mid = { m_upRect.left + m_upRect.Width() / 2, m_upRect.top + m_upRect.Height() / 2 };
	int triWidth = 4;
	CBrush triBrush(RGB(48, 48, 48)), *p_old_brush;
	p_old_brush = MemDC.SelectObject(&triBrush);
	POINT triPos[3] = { {mid.x - triWidth / 2, mid.y + triWidth / 4}, {mid.x + triWidth / 2, mid.y + triWidth / 4}, {mid.x , mid.y - triWidth / 2} };
	MemDC.Polygon(triPos, 3);
	MemDC.SelectObject(p_old_brush);

	m_upRect.top -= m_bClicked[0]*2;

	

	////////////////////////////////////////////////////////////////////////
	//하 버튼 그리기

	p_old_pen = MemDC.SelectObject(&borderPen);
	MemDC.Rectangle(m_downRect);
	m_downRect.left += border;
	m_downRect.right -= border;
	m_downRect.top += border;
	m_downRect.bottom -= border;
	
	CPen downPen(PS_SOLID, 1, RGB(119, 201, 255));
	MemDC.SelectObject(&downPen);
	MemDC.Rectangle(m_downRect);
	m_downRect.top += m_bClicked[1];
	MemDC.SelectObject(p_old_pen);

	MemDC.FillSolidRect(m_downRect, RGB(218, 227, 243));

	m_downRect.top += m_bClicked[1];
	mid = { m_downRect.left + m_downRect.Width() / 2, m_downRect.top + m_downRect.Height() / 2 };
	p_old_brush = MemDC.SelectObject(&triBrush);
	POINT triPosDownRect[3] = { { mid.x - triWidth / 2, mid.y - triWidth / 4 },{ mid.x + triWidth / 2, mid.y - triWidth / 4 },{ mid.x , mid.y + triWidth / 2 } };
	MemDC.Polygon(triPosDownRect, 3);
	MemDC.SelectObject(p_old_brush);

	m_upRect.top -= m_bClicked[1] * 2;

	
	
	dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &MemDC, 0, 0, SRCCOPY);
}


void CListCtrlMoveBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect r;
	GetClientRect(&r);
	CRect m_upRect = r, m_downRect = r;
	m_upRect.bottom = r.top + r.Height() / 2;
	m_downRect.top = m_upRect.bottom;
	if (PtInRect(&m_upRect, point)) {
		m_bClicked[0] = TRUE;
	}
	else if (PtInRect(&m_downRect, point)) {
		m_bClicked[1] = TRUE;
	}

	SetCapture();
	RedrawWindow();
	CWnd::OnLButtonDown(nFlags, point);
}


void CListCtrlMoveBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bClicked[0]) {
		m_bClicked[0] = FALSE;
		m_pNotifyData->code = NOTIFY_UP;
		m_pNotifyData->hwndFrom = m_hWnd;
		m_pNotifyData->idFrom = 1;
		GetParent()->SendMessage(WM_NOTIFY, 1, (LPARAM)m_pNotifyData);
	}
	if (m_bClicked[1]) {
		m_bClicked[1] = FALSE;
		m_pNotifyData->code = NOTIFY_DOWN;
		m_pNotifyData->hwndFrom = m_hWnd;
		m_pNotifyData->idFrom = 1;
		GetParent()->SendMessage(WM_NOTIFY, 1, (LPARAM)m_pNotifyData);
	}

	ReleaseCapture();
	RedrawWindow();

	CWnd::OnLButtonUp(nFlags, point);
}



