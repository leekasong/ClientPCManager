// InformationDataSWView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "InformationDataSWView.h"


// CInformationDataSWView

IMPLEMENT_DYNAMIC(CInformationDataSWView, CWnd)

CInformationDataSWView::CInformationDataSWView()
{
	m_pClientDB = new CClientDBData;
	m_pClientDB->GetInstalledSW(_T("COM20"), m_installedDBList);
	m_installedSWCount = 0;
	m_bHover = FALSE;
	m_hoverPos = { -1,-1 };

	POSITION pos = m_installedDBList.GetHeadPosition();
	CString tmp, dst;
	while (pos != NULL) {
		tmp = m_installedDBList.GetNext(pos);
		AfxExtractSubString(dst, tmp, 2, _T('@@'));
		m_installedList.AddTail(dst);
		m_installedSWCount++;
	}
}

CInformationDataSWView::~CInformationDataSWView()
{
	if (m_pClientDB) delete m_pClientDB;
}


BEGIN_MESSAGE_MAP(CInformationDataSWView, CWnd)
	ON_WM_PAINT()
//	ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
//ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CInformationDataSWView message handlers




void CInformationDataSWView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	CDC MemDC;
	CBitmap bmp;
	MemDC.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	MemDC.SelectObject(&bmp);

	//배경
	COLORREF bk_color = RGB(40, 44,52);
	MemDC.FillSolidRect(r, bk_color);
	CString test;
	test.Format(_T("x : %d, y : %d"), m_hoverPos.x, m_hoverPos.y);
	MemDC.TextOutW(r.left, r.bottom - 30, test);


	//텍스트

	MemDC.SetBkMode(TRANSPARENT);
	CPen borderPen(PS_SOLID, 2, RGB(49, 54, 63)), *p_old_pen;
	CFont font, *p_old_font, bigFont;
	LOGFONT lf = { 0 };
	_stprintf(lf.lfFaceName, _T("%s"), _T("굴림체"));
	lf.lfHeight = r.Height() / 40;
	font.CreateFontIndirectW(&lf);

	lf.lfHeight = r.Height() / 30;
	bigFont.CreateFontIndirectW(&lf);

	p_old_font = MemDC.SelectObject(&font);
	p_old_pen = MemDC.SelectObject(&borderPen);

	HBRUSH h_old_brush;
	h_old_brush = (HBRUSH)MemDC.SelectObject(GetStockObject(NULL_BRUSH));

	CRect entryRect;
	entryRect.SetRect(r.left, r.top + 2, r.right, r.top + 2 + lf.lfHeight + 2);
	int nHeight = r.Height() / (lf.lfHeight + 2);
	POSITION pos = m_installedList.GetHeadPosition();

	CRect tmpRect;
	
	//207,148,16
	for (int i = 0; i < nHeight && pos != NULL; i++) {
		if (::PtInRect(&entryRect, m_hoverPos)) {
			m_biggerSize = 10;
			MemDC.SetTextColor(RGB(207, 148,16));
			MemDC.SelectObject(&bigFont);
		}
		else {
			m_biggerSize = 0;
			MemDC.SetTextColor(RGB(131, 190, 121));
			MemDC.SelectObject(&font);
		}
		MemDC.Rectangle(entryRect);
		//MemDC.Rectangle(CRect(entryRect.left, entryRect.top - m_biggerSize, entryRect.right, entryRect.bottom + m_biggerSize));
		MemDC.DrawText(m_installedList.GetNext(pos)
			, CRect(entryRect.left, entryRect.top - m_biggerSize, entryRect.right, entryRect.bottom + m_biggerSize)
			, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		entryRect += CPoint(0, lf.lfHeight + 2);
	}
	MemDC.SelectObject(p_old_pen);
	MemDC.SelectObject(p_old_font);
	MemDC.SelectObject(h_old_brush);

	dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &MemDC, 0, 0, SRCCOPY);
}


//void CInformationDataSWView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CWnd::OnLButtonDown(nFlags, point);
//}


void CInformationDataSWView::OnMouseMove(UINT nFlags, CPoint point)
{
	
	
		m_hoverPos = point;
		RedrawWindow();
	
	CWnd::OnMouseMove(nFlags, point);
}


//void CInformationDataSWView::OnMouseLeave()
//{
//	// TODO: Add your message handler code here and/or call default
//	m_bHover = FALSE;
//	RedrawWindow();
//
//	CWnd::OnMouseLeave();
//}
