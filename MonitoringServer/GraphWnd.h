#pragma once


// CGraphWnd
#include "ClientComData.h"
#include "MinimapWnd.h"
class CMinimapWnd;

class AFX_EXT_CLASS CGraphWnd : public CWnd
{
	DECLARE_DYNAMIC(CGraphWnd)
private:
	CDC m_MemDC;
	CBitmap m_MemBmp;
	CMinimapWnd *m_pMinimapWnd;


	//0 - all, 1 - cpu, 2 - ram, 3 - network
	int m_displayItem; 
	CRect m_toggle_rect, m_text_rect;
	//0 - 닫는 버튼, 1 - 여는 버튼
	int m_toggle_flag; 
	HCURSOR m_hCursor;
	//0 - ALL, 1 - CPU, 2 - Memory, 3 - Network
	int m_drawType; 
	LPCTSTR m_itemNameList[4] = { _T("ALL"), _T("CPU"), _T("Memory"), _T("Network") };
	//CPU, Memory, Network
	COLORREF m_itemColor[3] = { RGB(237, 137, 7), RGB(60, 179, 253), RGB(124, 186, 44) };
	TIME m_time;

	
	CPoint m_select_pos, m_mouse_follow_pos;
	TCHAR m_selectedData[1024];
	int m_base_index;
public:
	CRect m_graph_rect;
public:
	CGraphWnd();
	virtual ~CGraphWnd();
public:
	void DrawItemNote(CRect graph_r, int w, CDC *pDC);
	void DrawGraphOutline(CRect graph_r, int w, int h, CDC *pDC);
	void DrawFigure(CRect r, CRect graph_r, int w, int h, CDC *pDC);
	void DrawCPU(CRect graph_r, CDC *pDC);
	void DrawMemory(CRect graph_r, CDC *pDC);
	void DrawNetwork(CRect graph_r, CDC *pDC);
	inline DATA ConvertToFigure(CRect graph_r, DATA data);

	//CClientComData의 배열에서 가져올 처음 값의 인덱스를 재설정했음을 통보받는다.
	void NotifyChangedPos(int baseIndex);
	void SetMinmapWnd(CMinimapWnd *p_minimapWnd);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
};


