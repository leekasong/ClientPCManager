#pragma once


// CTestView

class AFX_EXT_CLASS CTestView : public CWnd
{
	DECLARE_DYNAMIC(CTestView)

public:
	CTestView();
	virtual ~CTestView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


