#pragma once


// CSupportView

class CSupportView : public CWnd
{
	DECLARE_DYNAMIC(CSupportView)
private:
	CDC *m_pLogoDC;
	int m_logoWidth, m_logoHeight;
	CRect m_linkStaticRect;
	
public:
	CSupportView();
	virtual ~CSupportView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	
};


