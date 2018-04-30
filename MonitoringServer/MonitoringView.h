#pragma once
#include "CommonView.h"
class CMonitoringView : public CCommonView
{
	
public:
	CMonitoringView();
	virtual ~CMonitoringView();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

