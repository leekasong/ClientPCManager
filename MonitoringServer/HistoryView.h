#pragma once
#include "CommonView.h"
#include "GraphWnd.h"
#include "MinimapWnd.h"
#include "ScrollBarWnd.h"

class CHistoryView :public CCommonView
{
private:
	BOOL m_bStart;
	CGraphWnd m_wndGraph[4];
	CMinimapWnd m_wndMinimap;
	CScrollBarWnd m_wndScrollBar;
	int m_displayMode;

	int m_checkedSize;

	
public:
	void ChangeDisplayMode();
public:
	CHistoryView();
	virtual ~CHistoryView();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	afx_msg LRESULT OnUmChangeGraphMode(WPARAM wParam, LPARAM lParam);
};

