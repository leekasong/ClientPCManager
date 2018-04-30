#pragma once
#include "InformationDataView.h"
#include "CommonView.h"
// CInformationView

class CInformationView : public CCommonView
{
	DECLARE_DYNAMIC(CInformationView)
private:
	CInformationDataView *m_pInfoDataView;
	int m_captionHeight = 30;
	int m_checkedSize;
public:
	CInformationView();
	virtual ~CInformationView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


