#pragma once


// CInformationDataView

class CInformationDataView : public CWnd
{
	DECLARE_DYNAMIC(CInformationDataView)
private:
	CString m_comName;
public:
	void SetComputer(CString m_comName);

	
public:
	CInformationDataView();
	virtual ~CInformationDataView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


