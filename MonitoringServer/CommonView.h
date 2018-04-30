#pragma once
#include "ClientListCtrl.h"
#define MAX_INFO_VIEW_NUMBER	4
// CCommonView

class CCommonView : public CWnd
{
	DECLARE_DYNAMIC(CCommonView)
protected:
	BOOL *m_pChekedList;
	CClientListCtrl *m_pClientListCtrl;
	
public:
	void Notify();
	void ClearCheckedList();
	void SetClientListCtrl(CClientListCtrl *pClientListCtrl);
public:
	CCommonView();
	virtual ~CCommonView();

protected:
	DECLARE_MESSAGE_MAP()
};


