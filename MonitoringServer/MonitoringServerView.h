
// MonitoringServerView.h : interface of the CMonitoringServerView class
//

#pragma once
#include "ClientListView.h"
#include "BoardView.h"



class CMonitoringServerView : public CView
{
public:
	CClientListView *m_pClientListView;
	CBoardView m_boardView;

protected: // create from serialization only
	CMonitoringServerView();
	DECLARE_DYNCREATE(CMonitoringServerView)

// Attributes
public:
	CMonitoringServerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMonitoringServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in MonitoringServerView.cpp
inline CMonitoringServerDoc* CMonitoringServerView::GetDocument() const
   { return reinterpret_cast<CMonitoringServerDoc*>(m_pDocument); }
#endif

