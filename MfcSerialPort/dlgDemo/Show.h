#if !defined(AFX_SHOW_H__D12336E8_D0FE_4AAF_99F0_9006BAE80908__INCLUDED_)
#define AFX_SHOW_H__D12336E8_D0FE_4AAF_99F0_9006BAE80908__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Show.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShow dialog

class CShow : public CDialog
{
// Construction
public:
	CShow(CWnd* pParent = NULL);   // standard constructor
	unsigned int With;
	unsigned int Height;
	unsigned int Withbytes;
	unsigned int dataByte;
	CString picsavepath;
    BYTE *pBmpData;
	void Once(int n);
	void IDWT (int n);
	void LowIncrease();

// Dialog Data
	//{{AFX_DATA(CShow)
	enum { IDD = IDD_SHOW };
	CStatic	m_picture;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShow)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnDenoise();
	afx_msg void OnIncrease();
	afx_msg void OnReserver();
	afx_msg void OnSave();
	afx_msg void OnExit();
	afx_msg void OnVisualColor();
	afx_msg void OnPictureIncrease();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStatiPicture();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOW_H__D12336E8_D0FE_4AAF_99F0_9006BAE80908__INCLUDED_)
