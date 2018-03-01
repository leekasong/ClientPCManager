#pragma once


// CGraphWnd

class CGraphWnd : public CWnd
{
	DECLARE_DYNAMIC(CGraphWnd)

public:
	CGraphWnd();
	virtual ~CGraphWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
protected:
	afx_msg LRESULT OnUmCommandChnaged(WPARAM wParam, LPARAM lParam);
};


