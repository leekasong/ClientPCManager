#pragma once


// CCustomButton

class CCustomButton : public CWnd
{
	DECLARE_DYNAMIC(CCustomButton)
private:
	TCHAR m_modulePath[MAX_PATH+_MAX_FNAME];
	TCHAR m_fileName[_MAX_FNAME];
	CDC *m_pImageDC;
	int m_imageWidth, m_imageHeight;

	BOOL m_bClicked, m_bHover;
	BYTE m_transValue;

	TCHAR *m_pText;

	int m_id; //이 버튼을 식별할 id
public:
	//이미지를 메모리 DC로 복사하는 함수
	BOOL ImageToDC(TCHAR *pFileName, CDC *pImageDC);
	//텍스트 설정 함수
	void SetButtonText(TCHAR *pText, DWORD dwlength);

public:
	CCustomButton(TCHAR *pFileName);
	virtual ~CCustomButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseLeave();
};


