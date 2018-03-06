#pragma once


// CClientListCtrl
#include "ClientListCtrl.h"
#include "ListCtrlMoveBtn.h"
#define MAX_ITEM_NUMBER	30
#define NOTIFY_UP	1
#define NOTIFY_DOWN	2
#define MAX_CHECKED_NUMBER	4
class CClientListCtrl : public CWnd
{
	DECLARE_DYNAMIC(CClientListCtrl)
private:
	CListCtrlMoveBtn *m_pMoveBtn;
	int m_entryHeight;
	CStringList *m_pListText;
	int m_ListFirstIndex;
	int m_checkHeight; // check박스 한 변의 길이
	BOOL *m_pCheckedList; // 체크여부를 저장할 배열
	int m_checkedNumber; //체크된 개수 저장할 변수 : MAX값 4
	
	CDC *m_pGradationDC, *m_pPCBitmapDC;
	int m_gradiantWidth, m_gradiantHeight;
	int m_pcBitmapWidth, m_pcBitmapHeight;

	BOOL m_bClicked, m_bHover;
	BYTE m_alphaValue;
	int m_alphaEntryIndex;
public:
	void LoadBitmapToDC(CDC *pCompatibleDC, CDC *pTargetDC, DWORD dwResourceId, DWORD *pBmpWidth, DWORD *pBmpHeight);

	//체크된 목록에 대한 인터페이스
	inline int GetCheckedListSize() { return MAX_ITEM_NUMBER; }
	inline void GetCheckedList(BOOL *pCheckedList) { ::CopyMemory(pCheckedList, m_pCheckedList, sizeof(BOOL)*MAX_ITEM_NUMBER); }
public:
	CClientListCtrl();
	virtual ~CClientListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


