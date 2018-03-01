
// MonitoringServer.h : main header file for the MonitoringServer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMonitoringServerApp:
// See MonitoringServer.cpp for the implementation of this class
//

class CMonitoringServerApp : public CWinApp
{
public:
	CMonitoringServerApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMonitoringServerApp theApp;
