
// MonitoringServerView.cpp : implementation of the CMonitoringServerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MonitoringServer.h"
#endif

#include "MonitoringServerDoc.h"
#include "MonitoringServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMonitoringServerView

IMPLEMENT_DYNCREATE(CMonitoringServerView, CView)

BEGIN_MESSAGE_MAP(CMonitoringServerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMonitoringServerView construction/destruction

CMonitoringServerView::CMonitoringServerView()
{
	m_pClientListView = NULL;

}

CMonitoringServerView::~CMonitoringServerView()
{
	if (m_pClientListView) delete m_pClientListView;
}

BOOL CMonitoringServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMonitoringServerView drawing

void CMonitoringServerView::OnDraw(CDC* /*pDC*/)
{
	CMonitoringServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMonitoringServerView printing

BOOL CMonitoringServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMonitoringServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMonitoringServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMonitoringServerView diagnostics

#ifdef _DEBUG
void CMonitoringServerView::AssertValid() const
{
	CView::AssertValid();
}

void CMonitoringServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMonitoringServerDoc* CMonitoringServerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMonitoringServerDoc)));
	return (CMonitoringServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMonitoringServerView message handlers


int CMonitoringServerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	int nID = 25000;

	m_boardView.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, nID++);
	m_pClientListView = new CClientListView(&m_boardView);
	m_pClientListView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, nID++);

	
	
	return 0;
}



void CMonitoringServerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CRect r, board;
	GetClientRect(r);
	board = r;
	r.right = r.left + (r.Width()) / 7;
	board.left = r.right;
	m_pClientListView->SetWindowPos(NULL, r.left, r.top, r.Width() - 1, r.Height(), 0);
	
	m_boardView.SetWindowPos(NULL, board.left, board.top, board.Width()-1, board.Height(), 0);
}


void CMonitoringServerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	//dc.FillSolidRect(r, RGB(, 10, 10));
}



void CMonitoringServerView::OnDestroy()
{
	CView::OnDestroy();

	m_pClientListView->DestroyWindow();
	m_boardView.DestroyWindow();
}
