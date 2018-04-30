#pragma once
#include "MinimapWnd.h"
class CMinmapWnd;
// CScrollBarWnd

class AFX_EXT_CLASS CScrollBarWnd : public CWnd
{
	DECLARE_DYNAMIC(CScrollBarWnd)
private:
	CRect m_bar_rect, m_window_rect;
	BOOL m_bClicked;
	CPoint m_base_pos, m_moved_pos, m_clicked_pos;
	CMinimapWnd *m_pMinmapWnd;
	BOOL m_bTimer;
public:
	void SetMinimapWnd(CMinimapWnd *p_minimapWnd);
	void StartDemo();
	void StopDemo();
public:
	CScrollBarWnd();
	virtual ~CScrollBarWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


