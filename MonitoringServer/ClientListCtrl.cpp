// ClientListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "ClientListCtrl.h"


// CClientListCtrl

IMPLEMENT_DYNAMIC(CClientListCtrl, CWnd)

CClientListCtrl::CClientListCtrl()
	: m_pMoveBtn(NULL)
	, m_pGradationDC(NULL)
	, m_pPCBitmapDC(NULL)
	, m_pListText(NULL)
	, m_pCheckedList(NULL)
{
	
	m_entryHeight = 30;
	m_pListText = new CStringList;
	CString item;
	for (int i = 0; i < MAX_ITEM_NUMBER; i++) {
		item.Format(_T("PC %02d Disconnected"), i+1);
		m_pListText->AddTail(item);
	}
	
	m_ListFirstIndex = 0;

	m_bClicked = FALSE;
	m_bHover = FALSE;
	m_alphaValue = 0;
	m_alphaEntryIndex = 0;
	m_checkHeight = 10; 

	m_pCheckedList = new BOOL[MAX_ITEM_NUMBER];
	::ZeroMemory(m_pCheckedList, sizeof(BOOL) * MAX_ITEM_NUMBER);
	m_checkedNumber = 0;
}

CClientListCtrl::~CClientListCtrl()
{
	if (m_pMoveBtn) delete m_pMoveBtn;
	if (m_pGradationDC) delete m_pGradationDC;
	if (m_pPCBitmapDC) delete m_pPCBitmapDC;
	if (m_pListText) delete m_pListText;
	if (m_pCheckedList) delete m_pCheckedList;
}


BEGIN_MESSAGE_MAP(CClientListCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// CClientListCtrl message handlers




void CClientListCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	CDC MemDC;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(&bmp);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���
	
	int nHeight = r.Height() / m_entryHeight;
	MemDC.SetStretchBltMode(COLORONCOLOR);
	for (int i = 0; i <= nHeight; i++) {
		MemDC.StretchBlt(r.left, r.top + m_entryHeight * i, r.Width(), m_entryHeight, m_pGradationDC, 0, 0, m_gradiantWidth, m_gradiantHeight, SRCCOPY);
		/*MemDC.MoveTo(r.left, r.top + m_entryHeight * i);
		MemDC.LineTo(r.left + r.Width(), r.top + m_entryHeight * i);*/
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//üũ�ڽ��� ������ �׸���
	CPen checkPen(PS_SOLID, 1, RGB(48, 48, 48)), *p_old_pen;
	p_old_pen = MemDC.SelectObject(&checkPen);
	CPen checkedPen(PS_SOLID, 3, RGB(150, 0, 0));

	//��ũ�ѵ� �͸�ŭ �Ѿ��
	POSITION pos = m_pListText->GetHeadPosition();
	//�� �ε����� ��ũ�ѵ� ���� ����Ͽ� üũ�迭�� ���� �ִ´�.
	int baseIndex = 0;
	for (int i = 0; i < m_ListFirstIndex; i++) {
		m_pListText->GetNext(pos);
		baseIndex++;
	}
	
	for (int i = 0; i < nHeight; i++) {
		int top = r.top + m_entryHeight / 2 - m_checkHeight + m_entryHeight*i;
		int bottom = r.top + m_entryHeight / 2 + m_checkHeight + m_entryHeight*i;
		int left = r.left + 5;
		int right = r.left + 5 + 2 * m_checkHeight;
		MemDC.Rectangle(r.left + 5, top, right, bottom);
		//baseIndex�� �������� �ε����Ͽ� üũ���� üũ�Ѵ�.
		if (m_pCheckedList[baseIndex + i]) {
			MemDC.SelectObject(&checkedPen);
			MemDC.MoveTo(left + 4, top + 4);
			MemDC.LineTo(left + 6, bottom - 4);
			MemDC.LineTo(right - 4, top + 2);
			MemDC.SelectObject(&checkPen);
		}

		//������ �̹��� �׸���
		MemDC.TransparentBlt(right + 10, top, m_pcBitmapWidth, m_pcBitmapHeight
			, m_pPCBitmapDC, 0, 0, m_pcBitmapWidth, m_pcBitmapHeight, RGB(255, 255, 255));
	}
	MemDC.SelectObject(p_old_pen);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�۾� ����
	int newLeft = r.left + 5 + 2 * m_checkHeight + 10 + m_pcBitmapWidth + 5;
	CFont font, *p_old_font;
	LOGFONT lf = { 0 };
	_stprintf(lf.lfFaceName, _T("%s"), _T("Arail"));
	lf.lfHeight = m_entryHeight / 2;
	lf.lfWeight = FW_NORMAL;

	font.CreateFontIndirectW(&lf);
	p_old_font = MemDC.SelectObject(&font);
	
	MemDC.SetBkMode(TRANSPARENT);
	for (int i = 0; i < nHeight; i++) {
		if (pos == NULL) break;
	
		MemDC.DrawText(m_pListText->GetNext(pos), CRect(newLeft, r.top + m_entryHeight * i, r.right, r.top + m_entryHeight * (i+1)), DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	}

	MemDC.SelectObject(p_old_font);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//������ ��Ʈ�� ó��

	CDC alphaDC;
	CBitmap alphaBmp;
	alphaDC.CreateCompatibleDC(&dc);
	alphaBmp.CreateCompatibleBitmap(&dc, r.Width(), m_entryHeight);
	alphaDC.SelectObject(&alphaBmp);
	alphaDC.FillSolidRect(0, 0, r.Width(), m_entryHeight, RGB(222,235,247));
	BLENDFUNCTION bf = { 0 };
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = m_alphaValue;
	
	//���콺�� �����̴� ������ ������ ��Ʈ�� �׸���
	MemDC.AlphaBlend(r.left, r.top + m_alphaEntryIndex * m_entryHeight, r.Width(), m_entryHeight,
		&alphaDC, 0, 0, r.Width(), m_entryHeight, bf);

	//20��ŭ ������ ���� �̵� ��ư�� �ٽ� �׸��� ���� �ʱ� ����.
	dc.BitBlt(r.left, r.top, r.Width(), r.Height() - 20, &MemDC, 0, 0, SRCCOPY);
					  
}


int CClientListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	CClientDC dc(this);

	//�׶��̼� ��Ʈ��DC
	m_pGradationDC = new CDC;
	LoadBitmapToDC(&dc, m_pGradationDC, IDB_GRADATION_BITMAP, (DWORD *)&m_gradiantWidth, (DWORD *)&m_gradiantHeight);

	//�Ǿ� ������ �̹���DC
	m_pPCBitmapDC = new CDC;
	LoadBitmapToDC(&dc, m_pPCBitmapDC, IDB_PC_BITMAP, (DWORD *)&m_pcBitmapWidth, (DWORD *)&m_pcBitmapHeight);

	//���� �̵� ��ư ������
	m_pMoveBtn = new CListCtrlMoveBtn;
	m_pMoveBtn->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, ++g_wnd_id_a);
		
	


	
	return 0;
}


void CClientListCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(&r);
	m_pMoveBtn->SetWindowPos(NULL, r.left, r.bottom - 20, r.Width(), 20, 0);
}

void CClientListCtrl::LoadBitmapToDC(CDC *pCompatibleDC, CDC *pTargetDC, DWORD dwResourceId, DWORD *pBmpWidth, DWORD *pBmpHeight) {
	pTargetDC->CreateCompatibleDC(pCompatibleDC);
	CBitmap bmp;
	bmp.LoadBitmapW(dwResourceId);
	pTargetDC->SelectObject(&bmp);

	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	*pBmpWidth = bmpInfo.bmWidth;
	*pBmpHeight = bmpInfo.bmHeight;
}



BOOL CClientListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR *pData = (NMHDR *)lParam;
	if (pData->idFrom == 1) {
		int code = pData->code;
		CRect r;
		GetClientRect(&r);
		int nHeight = r.Height() / m_entryHeight;
		switch (code)
		{
			//��ư���� ���޵� �޽����� UP ����� ��
		case NOTIFY_UP:
			m_ListFirstIndex--;
			if (m_ListFirstIndex < 0) m_ListFirstIndex = 0;
		
			break;

			//��ư���� ���޵� �޽����� DOWN ����� ��
		case NOTIFY_DOWN:
			m_ListFirstIndex++;
			if (m_ListFirstIndex + nHeight >= MAX_ITEM_NUMBER) m_ListFirstIndex = MAX_ITEM_NUMBER - nHeight;
		
			break;
		}

		
		RedrawWindow();
	}

	return CWnd::OnNotify(wParam, lParam, pResult);
}


void CClientListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bHover == FALSE) {
		//����Ʈ��Ʈ�ѹ����� ��� ���� �ν��ϱ� ���� ȣ�� ���
		m_bHover = TRUE;
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = 0;
		tme.dwFlags = TME_LEAVE;
		TrackMouseEvent(&tme);
		
	}
	//���콺 ������¸� �ش� ������ ������ ��Ʈ�� ó��
	m_alphaValue = 100;
	m_alphaEntryIndex = point.y / m_entryHeight;
	RedrawWindow();

	CWnd::OnMouseMove(nFlags, point);
}


void CClientListCtrl::OnMouseLeave()
{
	if (m_bHover) {
		//����Ʈ��Ʈ�� ���� �����ٸ� ���� ó��
		m_bHover = FALSE;
		m_alphaValue = 0;

		RedrawWindow();
	}
	

	CWnd::OnMouseLeave();
}


void CClientListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect r;
	GetClientRect(&r);
	//����Ʈ��Ʈ���� �ѹ��� �����ִ� ��Ʈ���� ����
	int nHeight = r.Height() / m_checkHeight;
	//üũ�ڽ� left, right
	int left = r.left + 5;
	int right = r.left + 5 + 2 * m_checkHeight;
	for (int i = 0; i < nHeight; i++) {
		//üũ�ڽ� ž, ����
		int top = r.top + m_entryHeight / 2 - m_checkHeight + m_entryHeight*i;
		int bottom = r.top + m_entryHeight / 2 + m_checkHeight + m_entryHeight*i;
		CRect checkRect = CRect(left, top, right, bottom);
		//�ش� ��Ʈ���� üũ�ڽ��� Ŭ������ ��
		if (PtInRect(&checkRect, point)) {
			//Ŭ���� y��ǥ�� ��Ʈ�� ���̷� ���� ���� ��ũ�ѵ� ������ ���Ͽ� ����Ʈ��Ʈ�� ���� �ε����� ���Ѵ�. 
			int index = point.y / m_entryHeight + m_ListFirstIndex;

			//üũ���� ���� üũ�ڽ���
			if (m_pCheckedList[index] == FALSE) {
				//üũ�� ���� üũ
				if (m_checkedNumber < MAX_CHECKED_NUMBER) {
					m_checkedNumber++;
					m_pCheckedList[index] = TRUE;
				}
				else {
					AfxMessageBox(_T("üũ�� �� �ִ� ������ �ִ��Դϴ�."));
				}
			}
			//üũ�� üũ�ڽ���
			else {
				m_checkedNumber--;
				if (m_checkedNumber < 0) m_checkedNumber = 0;
				m_pCheckedList[index] = FALSE;
			}
			RedrawWindow();
			break;
		}
		
	}

	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CClientListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CRect r;
	GetClientRect(&r);
	int nHeight = r.Height() / m_entryHeight;
	if (zDelta <= 0) {
		//�ٴٿ�
		m_ListFirstIndex++;
		if (m_ListFirstIndex + nHeight >= MAX_ITEM_NUMBER) m_ListFirstIndex = MAX_ITEM_NUMBER - nHeight;
	}
	else {
		m_ListFirstIndex--;
		if (m_ListFirstIndex < 0) m_ListFirstIndex = 0;

	}

	RedrawWindow();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
