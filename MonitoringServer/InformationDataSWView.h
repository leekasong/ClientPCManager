#pragma once
#include "ClientDBData.h"

// CInformationDataSWView

class CInformationDataSWView : public CWnd
{
	DECLARE_DYNAMIC(CInformationDataSWView)
private:
	CClientDBData *m_pClientDB;
	CStringList m_installedDBList, m_installedList;
	int m_installedSWCount;
	
	BOOL m_bHover;
	POINT m_hoverPos;
	int m_biggerSize;
public:
	CInformationDataSWView();
	virtual ~CInformationDataSWView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnMouseLeave();
};


