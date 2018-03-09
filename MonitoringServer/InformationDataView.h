#pragma once
#include "InformationDataSWView.h"
#include "InformationDiskView.h"
#include "InformationProcessorDataView.h"

// CInformationDataView

class CInformationDataView : public CWnd
{
	DECLARE_DYNAMIC(CInformationDataView)
private:
	CString m_comName;
	CInformationDataSWView *m_pInformationSWView;
	CInformationDiskView *m_pInformationDiskView;
	CInformationProcessorDataView *m_pProcessorView;

public:
	void SetComputer(CString m_comName);

	
public:
	CInformationDataView();
	virtual ~CInformationDataView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


