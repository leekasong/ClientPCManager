#pragma once
#include "ClientDBData.h"
#define KS_PROCESSOR_TITLE	_T("Processor Model")
#define KS_MAX_ITEM_NUMBER	8
// CInformationProcessorDataView

class CInformationProcessorDataView : public CWnd
{
	DECLARE_DYNAMIC(CInformationProcessorDataView)
private:
	int m_imageWidth, m_imageHeight;
	CDC *m_pImageDC;

	CClientDBData *m_pCilentDB;
	CStringList m_cpuList, m_gpuList;
public:
	CInformationProcessorDataView();
	virtual ~CInformationProcessorDataView();
public:
	void SetProcessorData(CString comName);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};


