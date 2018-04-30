// InformationDiskView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "InformationDiskView.h"


// CInformationDiskView

IMPLEMENT_DYNAMIC(CInformationDiskView, CWnd)

CInformationDiskView::CInformationDiskView()
{
	//m_pDiskList = new CStringList;
	m_pClientDB = new CClientDBData;
	
	m_pClientDB->GetDiskUsage(_T("COM19"), m_pDiskList);

	m_bk_color = RGB(229, 68, 68);
}

CInformationDiskView::~CInformationDiskView()
{

}


BEGIN_MESSAGE_MAP(CInformationDiskView, CWnd)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CInformationDiskView message handlers

void CInformationDiskView::DrawCircle(CRect baseRect, CLIENT_DISK_USAGE diskUsage, CDC *pDC) {
	CPen borderPen(PS_SOLID, 2, RGB(188, 188, 188)), *p_old_pen;
	CBrush usageBrush(RGB(38, 16, 218)), totalBrush(RGB(230, 230, 230)), holeBrush(m_bk_color), *p_old_brush;
	p_old_pen = pDC->SelectObject(&borderPen);
	p_old_brush = pDC->SelectObject(&usageBrush);

	POINT start = { baseRect.left + baseRect.Width() / 2, baseRect.top }, end;
	int w = baseRect.Width();
	float angle = (diskUsage.usage / diskUsage.total) * 360.0 * (PI / 180.0);
	int radius = w / 2;
	end.x = start.x + radius * sin(angle);
	end.y = start.y + radius - radius*cos(angle);


	pDC->SelectObject(&totalBrush);
	pDC->Ellipse(baseRect);
	pDC->SelectObject(&usageBrush);
	pDC->Pie(baseRect, end, start);

	////////
	//hole
	////////
	pDC->SelectObject(&holeBrush);

	CRect holeRect = CRect(baseRect.left + w / 4, baseRect.top + w / 4, baseRect.right - w / 4, baseRect.bottom - w / 4);
	pDC->Ellipse(holeRect);
	CString percentStr;
	float percent = diskUsage.usage / diskUsage.total * 100;
	percentStr.Format(_T("%.2f (%%)"), percent);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(percentStr, holeRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	////////
	//반환
	////////
	pDC->SelectObject(p_old_pen);
	pDC->SelectObject(p_old_brush);
}


void CInformationDiskView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	CDC MemDC;
	CBitmap bmp;
	MemDC.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	MemDC.SelectObject(&bmp);
	MemDC.FillSolidRect(r, m_bk_color);

	

	POSITION pos = m_pDiskList.GetHeadPosition();
	CString dst;
	//디스크 데이터 문자열 처리
	for(int i = 0; i < 2; i++){
		CString tmp = m_pDiskList.GetNext(pos);
		AfxExtractSubString(dst, tmp, 2, _T('@@'));
		m_diskUsageList[i].total = _ttoi(dst);
		AfxExtractSubString(dst, tmp, 4, _T('@@')); //@@이기 때문에 2의 배수로 인덱싱
		m_diskUsageList[i].usage = _ttoi(dst);
	}

	
	CRect bigCircleRect, smallCircleRect, tempRect;
	int w = r.Width() > r.Height() ? r.Height() : r.Width();
	bigCircleRect.SetRect(r.left, r.top, r.left + w, r.top + w);

	//남은 공간
	tempRect.SetRect(bigCircleRect.right, bigCircleRect.top, r.right, r.bottom);
	w = tempRect.Width() > tempRect.Height() ? tempRect.Height() : tempRect.Width();

	//남은 공간의 절반 크기
	smallCircleRect.SetRect(tempRect.left + w/4, tempRect.top + w / 4, tempRect.left + w - w/4, tempRect.top + w - w / 4);

	//큰 용량 디스크 usage 그리기
	DrawCircle(bigCircleRect, m_diskUsageList[0], &MemDC);
	//작은 용량 디스크 Usage 그리기
	DrawCircle(smallCircleRect, m_diskUsageList[1], &MemDC);



	dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &MemDC, 0, 0, SRCCOPY);

	
}


void CInformationDiskView::OnDestroy()
{
	CWnd::OnDestroy();
	if (m_pClientDB) {
		delete m_pClientDB;
		m_pClientDB = NULL;
	}
}
