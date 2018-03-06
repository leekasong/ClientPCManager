#pragma once
#include "CommonView.h"

// CGraphWnd

class CGraphWnd : public CCommonView
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


