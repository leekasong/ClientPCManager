#pragma once
#include "GraphWnd.h"
#include "ClientComData.h"
#define MAX_GRAPH_NUMBER	4
class CGraphWnd;
// CMinimapWnd
class AFX_EXT_CLASS CMinimapWnd : public CWnd
{
	DECLARE_DYNAMIC(CMinimapWnd)
private:
	CRect m_focus_rect, m_map_rect;
	BOOL m_bClicked;
	CPoint m_clicked_pos, m_moved_pos, m_focus_pos;
	CGraphWnd *m_pGraphWndList[MAX_GRAPH_NUMBER];
	COLORREF m_itemColor[3] = { RGB(237, 137, 7), RGB(60, 179, 253), RGB(124, 186, 44) };
	int m_base_index;

	
public:
	CClientComData m_clientComData;
public:
	void SetGraphWnd(CGraphWnd *p_graphWnd, int index);
	void DrawFocusBar(CDC *pDC);
	void DrawOutline(CDC *pDC);
	UINT ConvertToFigure(DATA data);
	void NotifyChangedBaseIndex(int base_index);
	
public:
	CMinimapWnd();
	virtual ~CMinimapWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


