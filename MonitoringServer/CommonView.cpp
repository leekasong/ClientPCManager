// CommonView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "CommonView.h"


// CCommonView

IMPLEMENT_DYNAMIC(CCommonView, CWnd)

CCommonView::CCommonView()
{
	/*m_pClientListCtrl = new CClientListCtrl;
	int size= m_pClientListCtrl->GetCheckedListSize();
	m_pChekedList = new BOOL[size]{ FALSE };*/
	m_pCheckedList = NULL;
}

CCommonView::~CCommonView()
{
	if (m_pCheckedList) delete[] m_pCheckedList;
}


BEGIN_MESSAGE_MAP(CCommonView, CWnd)
END_MESSAGE_MAP()



// CCommonView message handlers


void CCommonView::Notify() {
	m_pClientListCtrl->GetCheckedList(m_pCheckedList);
	RedrawWindow();
}
void CCommonView::ClearCheckedList() {
	int size = m_pClientListCtrl->GetCheckedListSize();
	::ZeroMemory(m_pCheckedList, sizeof(BOOL)*size);
}

void CCommonView::SetClientListCtrl(CClientListCtrl *pClientListCtrl) {
	m_pClientListCtrl = pClientListCtrl;
	int size = m_pClientListCtrl->GetCheckedListSize();
	m_pCheckedList = new BOOL[size]{ FALSE };
}

