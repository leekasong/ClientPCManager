#pragma once


// 
#include "GraphWnd.h"

class CBoardView : public CWnd
{
	DECLARE_DYNAMIC(CBoardView)
	//전략 패턴
	CWnd *m_pViewWnd;
public:
	void SetViewWnd(CWnd *pViewWnd);
public:
	CBoardView();
	virtual ~CBoardView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


