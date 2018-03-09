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

	int m_id; //�� ��ư�� �ĺ��� id
public:
	//�̹����� �޸� DC�� �����ϴ� �Լ�
	BOOL ImageToDC(TCHAR *pFileName, CDC *pImageDC);
	//�ؽ�Ʈ ���� �Լ�
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


