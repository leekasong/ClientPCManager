#pragma once
#include "CustomButton.h"
#include "BoardView.h"
#include "GraphWnd.h"
#define MAX_BUTTON_NUMBER	4
// CCommandCtrl

class CCommandCtrl : public CWnd
{
	DECLARE_DYNAMIC(CCommandCtrl)
private:
	CCustomButton *m_pCustomButton[MAX_BUTTON_NUMBER];
	CBoardView *m_pBoardView;
	CGraphWnd *m_pGraphWnd;
public:
	void SetBoardViewWnd(CBoardView *pBoardView);
public:
	CCommandCtrl();
	virtual ~CCommandCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg LRESULT OnUmCommandChnaged(WPARAM wParam, LPARAM lParam);
};


