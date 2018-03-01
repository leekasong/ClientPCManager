// CustomButton.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "CustomButton.h"


// CCustomButton

IMPLEMENT_DYNAMIC(CCustomButton, CWnd)

CCustomButton::CCustomButton(TCHAR *pFileName)
{
	::ZeroMemory(m_modulePath, sizeof(m_modulePath));

	//실행파일 경로 추출하기
	GetModuleFileName(NULL, m_modulePath, sizeof(m_modulePath));
	int len = _tcslen(m_modulePath);
	for (int i = len; i >= 0; i--) {
		if (m_modulePath[i] == _T('\\')) {
			m_modulePath[i] = (TCHAR)0;
			break;
		}
	}
	
	::_tcscpy(m_fileName, pFileName);
	m_bClicked = FALSE;
	m_bHover = FALSE;

	m_transValue = 0;
	m_pText = NULL;
}

CCustomButton::~CCustomButton()
{
	if (m_pText) {
		delete[] m_pText;
	}
	delete m_pImageDC;
	
}


BEGIN_MESSAGE_MAP(CCustomButton, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CCustomButton message handlers




void CCustomButton::OnPaint()
{
	CPaintDC dc(this);
	//메모리DC 생성
	CRect r;
	GetClientRect(&r);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap bmp, *p_old_bmp;
	bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	MemDC.SelectObject(&bmp);
	
	//배경 그라데이션
	TRIVERTEX vert[2];
	GRADIENT_RECT rect;
	vert[0].x = r.left;
	vert[0].y = r.top;
	WORD color = 0xf000;
	vert[0].Red = 0xf000;
	vert[0].Green = 0xf000;
	vert[0].Blue = 0xf000;
	vert[0].Alpha = 0x0000;

	vert[1].x = r.right;
	vert[1].y = r.bottom;
	color  = 0xe900;
	vert[1].Red = color;
	vert[1].Green = color;
	vert[1].Blue = color;
	vert[1].Alpha = 0;

	rect.UpperLeft = 0;
	rect.LowerRight = 1;
	GradientFill(MemDC.m_hDC, vert, 2, &rect, 1, GRADIENT_FILL_RECT_H);

	//경계선 그리기
	CPen border(PS_SOLID, 3, RGB(248, 248, 248)), *p_old_pen;
	CRect b_rect = r;
	int padding = 1;
	p_old_pen = MemDC.SelectObject(&border);
	b_rect.SetRect(r.left + padding, r.top + padding, r.right, r.bottom);
	MemDC.MoveTo(b_rect.left, b_rect.top);
	MemDC.LineTo(b_rect.right, b_rect.top);
	MemDC.SelectObject(p_old_pen);
	

	//이미지 아이콘 출력
	int h = r.Height() / 2;
	h -= m_imageHeight / 2;
	MemDC.BitBlt(r.left + 10 - m_bHover + m_bClicked, r.top + h - m_bHover + m_bClicked, r.Width() / 3, r.Height(), m_pImageDC, 0, 0, SRCCOPY);

	//글씨 출력
	CFont font, *p_old_font;
	LOGFONT lf = { 0 };
	lf.lfWeight = FW_BOLD;
	lf.lfHeight = r.Height() / 10 + r.Height() / 5;
	_stprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
	font.CreateFontIndirectW(&lf);
	p_old_font = MemDC.SelectObject(&font);
	MemDC.SetBkMode(TRANSPARENT);
	MemDC.DrawText(m_pText, CRect(r.left + 20 + m_imageWidth, r.top, r.right, r.top + r.Height()), DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	MemDC.SelectObject(p_old_font);
	dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &MemDC, 0, 0, SRCCOPY);
	
	//마우스 hover시 반투명비트맵 적용
	BLENDFUNCTION bf = { 0 };
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = m_transValue; //투명도 조절
	bf.AlphaFormat = 0;
	CBitmap alphaBmp;
	alphaBmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());

	MemDC.SelectObject(&alphaBmp);
	//217,234,234
	MemDC.FillSolidRect(r, RGB(180, 240, 180));
	dc.AlphaBlend(r.left, r.top, r.Width(), r.Height(), &MemDC, 0, 0, r.Width(), r.Height(), bf);
}


void CCustomButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bClicked = 2;
	SetCapture();
	RedrawWindow();
	CWnd::OnLButtonDown(nFlags, point);
}


void CCustomButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bClicked) {
		m_bClicked = FALSE;
		ReleaseCapture();
		RedrawWindow();
		::PostMessage(GetParent()->m_hWnd, UM_COMMAND_CHNAGED, 0, 0);
	}

	CWnd::OnLButtonUp(nFlags, point);
}


void CCustomButton::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if (m_bHover == FALSE) {
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = 0;

		m_bHover = ::TrackMouseEvent(&tme);
		m_transValue = 100;
		RedrawWindow();
	}

	
	CWnd::OnMouseMove(nFlags, point);
}


int CCustomButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_pImageDC = new CDC;
	
	ImageToDC(m_fileName, m_pImageDC);
	
	return 0;
}


BOOL CCustomButton::ImageToDC(TCHAR *pFileName, CDC * pImageDC) {
	CClientDC dc(this);
	//CImage에 있는 비트맵을 복사할 메모리 DC를 만든다.
	pImageDC->CreateCompatibleDC(&dc);
	//이미지 파일 경로를 얻는다.
	TCHAR filePath[MAX_PATH + _MAX_FNAME] = { 0 };
	_stprintf(filePath, _T("%s\\%s"), m_modulePath, pFileName);

	CImage image;
	CBitmap bmp;
	//경로로 이미지를 로드한다.
	image.Load(filePath);
	//width, height 저장한다.
	m_imageWidth = image.GetWidth();
	m_imageHeight = image.GetHeight();
	//메모리DC로 복사하기 위한 비트맵을 만든다.
	bmp.CreateCompatibleBitmap(&dc, m_imageWidth, m_imageHeight);
	pImageDC->SelectObject(&bmp);
	
	//메모리DC로 복사
	image.BitBlt(pImageDC->GetSafeHdc(), 0, 0, SRCCOPY);

	return TRUE;
}



void CCustomButton::OnMouseLeave()
{
	m_bHover = FALSE;
	m_transValue = 0;
	RedrawWindow();

	CWnd::OnMouseLeave();
}

void CCustomButton::SetButtonText(TCHAR *pText, DWORD dwlength) {
	if (m_pText != NULL) delete[] m_pText;

	m_pText = new TCHAR[dwlength]{ 0 };

	_tcscpy(m_pText, pText);
}