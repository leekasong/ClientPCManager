// SupportView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "SupportView.h"


// CSupportView

IMPLEMENT_DYNAMIC(CSupportView, CWnd)

CSupportView::CSupportView()
{
}

CSupportView::~CSupportView()
{
	delete m_pLogoDC;
}


BEGIN_MESSAGE_MAP(CSupportView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CSupportView message handlers




void CSupportView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	MemDC.SelectObject(&bmp);
	MemDC.FillSolidRect(r, RGB(244, 244, 244));
	
	int logoWidth = 100;
	POINT logoPos = { r.left + r.Width() / 4, r.top + r.Height() / 4 };
	POINT mid = { r.left + r.Width() / 2, r.top + r.Height() / 2 };

	MemDC.SetStretchBltMode(COLORONCOLOR);
	MemDC.StretchBlt(logoPos.x, logoPos.y, logoWidth, logoWidth, m_pLogoDC, 0, 0, m_logoWidth, m_logoHeight, SRCCOPY);

	POINT textPos = { logoWidth + logoPos.x, logoPos.y };

	CFont font, *p_old_font;
	LOGFONT lf = { 0 };
	lf.lfWeight = FW_NORMAL;
	lf.lfHeight = logoWidth - 20;
	_stprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
	font.CreateFontIndirectW(&lf);
	p_old_font = MemDC.SelectObject(&font);
	MemDC.SetBkMode(TRANSPARENT);
	MemDC.SetTextColor(RGB(48, 48, 48));
	MemDC.DrawText(_T("Monitorings"), CRect(textPos.x, textPos.y, r.right, textPos.y + logoWidth), DT_SINGLELINE | DT_VCENTER | DT_LEFT);

	MemDC.SelectObject(p_old_font);
	
	font.DeleteObject();
	lf.lfWeight = FW_BOLD;
	lf.lfHeight = r.Height() / 20;
	font.CreateFontIndirectW(&lf);
	p_old_font = MemDC.SelectObject(&font);
	MemDC.SetTextColor(RGB(90, 151, 217));

	textPos.y += logoWidth + 10;
	MemDC.DrawText(_T("Resource Management with a clean interface"), CRect(r.left, textPos.y, r.right, textPos.y + logoWidth)
		, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	MemDC.SelectObject(p_old_font);


	textPos.y += logoWidth + 10;
	font.DeleteObject();
	lf.lfWeight = FW_NORMAL;
	lf.lfHeight = r.Height() / 30;
	font.CreateFontIndirectW(&lf);
	p_old_font = MemDC.SelectObject(&font);
	MemDC.SetTextColor(RGB(115, 115, 115));
	MemDC.DrawText(_T("For help, please visit")
		, CRect(r.left, textPos.y, textPos.x + logoWidth, textPos.y + logoWidth ), DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	MemDC.SelectObject(p_old_font);


	textPos.y += r.Height() / 10;
	font.DeleteObject();
	lf.lfHeight = r.Height() / 40;
	font.CreateFontIndirectW(&lf);
	p_old_font = MemDC.SelectObject(&font);
	
	MemDC.DrawText(_T("¡Ü blog : http://blog.naver.com/leekasong")
		,CRect(r.left + r.Width() / 6, textPos.y, r.right, textPos.y + logoWidth), DT_SINGLELINE | DT_VCENTER | DT_LEFT);

	textPos.y += r.Height() / 15;
	MemDC.DrawText(_T("¡Ü github : https://github.com/leekasong/ClientPCManager.git")
		, CRect(r.left + r.Width() / 6, textPos.y, r.right, textPos.y + logoWidth), DT_SINGLELINE | DT_VCENTER | DT_LEFT);
	
	textPos.y += r.Height() / 15;
	MemDC.DrawText(_T("¡Ü Contact : leekasong@naver.com")
		, CRect(r.left + r.Width() / 6, textPos.y, r.right, textPos.y + logoWidth), DT_SINGLELINE | DT_VCENTER | DT_LEFT);


	MemDC.SelectObject(p_old_font);


	dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &MemDC, 0, 0, SRCCOPY);
}


int CSupportView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
			_tcscat(buf, _T("\\logo.BMP"));
			break;
		}
	}
	image.Load(buf);
	m_logoWidth = image.GetWidth();
	m_logoHeight = image.GetHeight();
	m_pLogoDC = new CDC;
	
	
	CClientDC dc(this);
	
	m_pLogoDC->CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, m_logoWidth, m_logoHeight);
	m_pLogoDC->SelectObject(&bmp);
	

	image.BitBlt(m_pLogoDC->GetSafeHdc(), 0, 0, SRCCOPY);
	

	

	return 0;
}






