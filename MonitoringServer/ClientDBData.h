#pragma once

#include "ClientResourceDB.h"

class CClientDBData
{

public:
	BOOL GetDiskUsage(CString comName, CStringList& list){
		KS_SetTable(KS_DSN_HW, KS_HW_DISK_TABLE);
		if (!KS_SelectByComName(comName, list, KS_DSN_HW, KS_HW_DISK_TABLE))
			return FALSE;
		return TRUE;
	}

	BOOL GetInstalledSW(CString comName, CStringList& list) {
		KS_SetTable(KS_DSN_SW, KS_SW_TABLE);
		if (!KS_SelectByComName(comName, list, KS_DSN_SW, KS_SW_TABLE))
			return FALSE;
		return TRUE;
	}

	BOOL GetCPUData(CString comName, CStringList& list) {
		KS_SetTable(KS_DSN_HW, KS_HW_PROCESSOR_TABLE);
		if (!KS_SelectByComName(comName, list, KS_DSN_HW, KS_HW_PROCESSOR_TABLE))
			return FALSE;
		return TRUE;
	}

	BOOL GetGPUData(CString comName, CStringList& list) {
		KS_SetTable(KS_DSN_HW, KS_HW_GPU_TABLE);
		if (!KS_SelectByComName(comName, list, KS_DSN_HW, KS_HW_GPU_TABLE))
			return FALSE;
		return TRUE;
	}
public:
	CClientDBData();
	~CClientDBData();
};

