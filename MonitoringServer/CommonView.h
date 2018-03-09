#pragma once
#include "ClientListCtrl.h"

// CCommonView

class CCommonView : public CWnd
{
	DECLARE_DYNAMIC(CCommonView)
protected:
	BOOL *m_pCheckedList;
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


