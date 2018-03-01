#pragma once


// CListCtrlMoveBtn
#define NOTIFY_UP	1
#define NOTIFY_DOWN	2
class CListCtrlMoveBtn : public CWnd
{
	DECLARE_DYNAMIC(CListCtrlMoveBtn)
private:
	BOOL m_bClicked[2];
	CRect m_upRect, m_downRect;
	NMHDR *m_pNotifyData;
public:
	CListCtrlMoveBtn();
	virtual ~CListCtrlMoveBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
};


