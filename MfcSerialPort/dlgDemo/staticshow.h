#if !defined(AFX_STATICSHOW_H__C4AF9F71_ED56_4997_8656_E65404F5AA7D__INCLUDED_)
#define AFX_STATICSHOW_H__C4AF9F71_ED56_4997_8656_E65404F5AA7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// staticshow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cstaticshow dialog
#include "dlgDemoDlg.h"
class Cstaticshow : public CDlgDemoDlg
{
// Construction
public:
	Cstaticshow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cstaticshow)
	//enum { IDD = IDD_STATIC_CREATPICTURE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cstaticshow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cstaticshow)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICSHOW_H__C4AF9F71_ED56_4997_8656_E65404F5AA7D__INCLUDED_)
