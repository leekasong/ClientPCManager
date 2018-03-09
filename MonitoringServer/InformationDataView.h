#pragma once

#include "InformationDataSWView.h"
#include "InformationProcessorDataView.h"
#include "InformationDiskView.h"

// CInformationDataView

class CInformationDataView : public CWnd
{
	DECLARE_DYNAMIC(CInformationDataView)
private:
	CString m_comName;
	CInformationDataSWView *m_pSWView;
	CInformationProcessorDataView *m_pProcessorView;
	CInformationDiskView *m_pDiskView;
	
	

	//PCLIENT_PROCESSOR m_pClientProcessor;
	//int m_processorSize;

	//PCLIENT_GPU m_pClientGPU;
	//int m_gpuSize;


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


