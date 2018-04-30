// InformationProcessorDataView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "InformationProcessorDataView.h"


// CInformationProcessorDataView

IMPLEMENT_DYNAMIC(CInformationProcessorDataView, CWnd)

CInformationProcessorDataView::CInformationProcessorDataView()
{
	m_pCilentDB = new CClientDBData;
	m_pCilentDB->GetCPUData(_T("COM19"), m_cpuList);
	m_pCilentDB->GetGPUData(_T("COM19"), m_gpuList);
}

CInformationProcessorDataView::~CInformationProcessorDataView()
{
	if (m_pCilentDB) delete m_pCilentDB;
}


BEGIN_MESSAGE_MAP(CInformationProcessorDataView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CInformationProcessorDataView message handlers




void CInformationProcessorDataView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);

	CDC MemDC;
	CBitmap bmp;
	MemDC.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	MemDC.SelectObject(&bmp);

	MemDC.FillSolidRect(r, RGB(250, 221, 125));
	CFont titleFont, textFont, *p_old_font;
	LOGFONT lf = { 0 };
	_stprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
	lf.lfHeight = r.Height() / 10;
	titleFont.CreateFontIndirectW(&lf);
	p_old_font = MemDC.SelectObject(&titleFont);

	//title 그리기
	MemDC.SetBkMode(TRANSPARENT);
	MemDC.DrawText(KS_PROCESSOR_TITLE, CRect(r.left + 10, r.top + 5, r.right - 10, r.top + lf.lfHeight), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	//이미지 넣기
	CSize textSize = MemDC.GetTextExtent(KS_PROCESSOR_TITLE);
	int imageX = r.left + r.Width() / 2 - textSize.cx * 6 / 7;
	MemDC.StretchBlt(imageX, r.top + 5, textSize.cx / 4, textSize.cy, m_pImageDC, 0, 0, m_imageWidth, m_imageHeight, SRCCOPY);

	//경계선 긋기
	CPen halfPen(PS_SOLID, 2, RGB(104, 161, 180)), *p_old_pen;
	p_old_pen = MemDC.SelectObject(&halfPen);
	MemDC.MoveTo(r.CenterPoint().x, r.top + 5 + textSize.cx / 4 + 10);
	MemDC.LineTo(r.CenterPoint().x, r.bottom - 5);

	//모델명 적기
	MemDC.SetTextColor(RGB(254, 254, 254));
	lf.lfHeight = r.Height() / 15;
	lf.lfWidth = (r.Width() / 2) / 45;
	textFont.CreateFontIndirectW(&lf);
	MemDC.SelectObject(&textFont);

	CRect cpuRect = CRect(r.left + 10, r.top + 5 + textSize.cy + r.Height() / 10, 
		r.left + r.Width() / 2 - 10, r.top + 5 + textSize.cy + r.Height() / 10 + textSize.cy);
	CRect gpuRect = cpuRect;


	//CPU 정보 출력
	CString dst, tmp;
	POSITION pos = m_cpuList.GetHeadPosition();
	for (int i = 0; i < KS_MAX_ITEM_NUMBER && pos != NULL; i++) {
		tmp = m_cpuList.GetNext(pos);
		AfxExtractSubString(dst, tmp, 4, _T('@@'));
		MemDC.DrawText(dst, cpuRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		cpuRect += CPoint(0, textSize.cy);
	}

	//GPU 정보 출력
	gpuRect += CPoint(r.Width() / 2, 0);
	pos = m_gpuList.GetHeadPosition();
	for (int i = 0; i < KS_MAX_ITEM_NUMBER && pos != NULL; i++) {
		tmp = m_gpuList.GetNext(pos);
		AfxExtractSubString(dst, tmp, 4, _T('@@'));
		MemDC.DrawText(dst, gpuRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		gpuRect += CPoint(0, textSize.cy);
	}


	MemDC.SelectObject(p_old_pen);
	MemDC.SelectObject(p_old_font);


	
	dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &MemDC, 0, 0, SRCCOPY);
}

void CInformationProcessorDataView::SetProcessorData(CString comName) {

}

int CInformationProcessorDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CImage image;
	TCHAR buf[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buf, MAX_PATH);
	int len = _tcslen(buf);
	for (int i = len; i >= 0; i--) {
		if (buf[i] == _T('\\')) {
			buf[i] = 0;
			_tcscat(buf, _T("\\processor.BMP"));
			break;
		}
	}
	image.Load(buf);
	m_imageWidth = image.GetWidth();
	m_imageHeight = image.GetHeight();
	m_pImageDC = new CDC;


	CClientDC dc(this);

	m_pImageDC->CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, m_imageWidth, m_imageHeight);
	m_pImageDC->SelectObject(&bmp);


	image.BitBlt(m_pImageDC->GetSafeHdc(), 0, 0, SRCCOPY);

	return 0;
}


void CInformationProcessorDataView::OnDestroy()
{
	CWnd::OnDestroy();

	if (m_pImageDC) {
		m_pImageDC->DeleteDC();
		delete m_pImageDC;
	}
}
