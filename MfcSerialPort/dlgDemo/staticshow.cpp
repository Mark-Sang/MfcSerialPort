// staticshow.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "staticshow.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cstaticshow dialog


Cstaticshow::Cstaticshow(CWnd* pParent /*=NULL*/)
	: CDlgDemoDlg(pParent)
{
	//{{AFX_DATA_INIT(Cstaticshow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cstaticshow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cstaticshow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cstaticshow, CDlgDemoDlg)
	//{{AFX_MSG_MAP(Cstaticshow)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cstaticshow message handlers
