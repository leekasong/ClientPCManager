#pragma once


// CClientListView
#include "ClientListCtrl.h"
#include "CommandCtrl.h"


class CClientListView : public CWnd
{
	DECLARE_DYNAMIC(CClientListView)
private:
	CClientListCtrl m_clientListCtrl;
	CCommandCtrl m_commandCtrl;
	CBoardView *m_pBoardView;
public:
	
public:
	CClientListView(CBoardView *pBoardView);
	virtual ~CClientListView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


/*
Ŭ���̾�Ʈ ����Ʈ ��Ʈ�� : Ŀ�ǵ� ��Ʈ�� = 7 : 3
*/