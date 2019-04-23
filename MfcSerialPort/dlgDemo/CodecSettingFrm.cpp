// CodecSettingFrm.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "DXMediaCap.h"
#include "CodecSettingFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodecSettingFrm dialog


CCodecSettingFrm::CCodecSettingFrm(CWnd* pParent /*=NULL*/)
	: CDialog(CCodecSettingFrm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodecSettingFrm)
	//}}AFX_DATA_INIT
}


void CCodecSettingFrm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodecSettingFrm)
	DDX_Control(pDX, IDC_CAP_DIR_EDIT, m_RecEditPath);
	DDX_Control(pDX, IDC_EDIT_SNAPDIR, m_SnapEditPath);
	DDX_Control(pDX, IDC_COMBO_AUDIOCODEC, m_AudioCode_Comb);
	DDX_Control(pDX, IDC_COMBO_VIDEOCODEC, m_VideoCode_Comb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCodecSettingFrm, CDialog)
	//{{AFX_MSG_MAP(CCodecSettingFrm)
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIOCODEC, OnSelchangeComboAudiocodec)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEOCODEC, OnSelchangeComboVideocodec)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_SNAPDIR, OnButtonBrowseSnapdir)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_RECDIR, OnButtonBrowseRecdir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodecSettingFrm message handlers
BOOL CCodecSettingFrm::OnInitDialog() 
{
	CDialog::OnInitDialog();

	((CButton*)GetDlgItem(IDC_RADIO_H264))->SetCheck(1);  

	m_SnapEditPath.SetWindowText("d:\\Pic");
	m_RecEditPath.SetWindowText("d:\\Video");
	WIN32_FIND_DATA findFileData;

	HANDLE SnapFind = ::FindFirstFile("d:\\Pic", &findFileData);
	if (INVALID_HANDLE_VALUE == SnapFind)
	{
		CreateDirectory("d:\\Pic",NULL);
	}

	HANDLE RecFind = ::FindFirstFile("d:\\Video", &findFileData);
	if (INVALID_HANDLE_VALUE == RecFind)
	{
		if(!CreateDirectory("d:\\Video",NULL))
		{
				::AfxMessageBox("create the directory false ");
		}
	}
    
	PicSavePath=m_SnapPath;
	RecSavePath=m_CapPath;

	unsigned Videonum = 100;
	unsigned Audionum = 100;	
	CString strVideo ;
	CString strAudio;


	DXEnumAudioCodecs(CDlgDemoDlg::AudioTags, Audionum);
	DXEnumVideoCodecs(CDlgDemoDlg::VideoTags, Videonum);
	m_VideoCode_Comb.ResetContent();
	m_AudioCode_Comb.ResetContent ();

	for(unsigned i=0; i<Videonum; i++)
	{
		
		strVideo.Format (_T("%s"),CDlgDemoDlg::VideoTags[i].deviceName);
		
		m_VideoCode_Comb.AddString(strVideo);	
	
	}

	for(unsigned j=0; j<Audionum; j++)
	{
				
		strAudio.Format (_T("%s"),CDlgDemoDlg::AudioTags[j].deviceName);		
		m_AudioCode_Comb.AddString(strAudio);
		
		
	}

	m_VideoCode_Comb.SetCurSel(0);

	m_AudioCode_Comb.SetCurSel(0);

	return 0;
}
void CCodecSettingFrm::OnSelchangeComboAudiocodec() 
{
	// TODO: Add your control notification handler code here
	
}

void CCodecSettingFrm::OnSelchangeComboVideocodec() 
{
	// TODO: Add your control notification handler code here
	
}

void CCodecSettingFrm::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

void CCodecSettingFrm::OnOK() 
{
	// TODO: Add extra validation here
	CButton *pbtn;
	
	pbtn = (CButton*)GetDlgItem(IDC_RADIO_XVID);
	if( pbtn->GetCheck())
	//VideoCodecStr
	CDlgDemoDlg::DeviceInfo[dwCard].dwVideoCodecStr="Xvid MPEG-4 Codec";
	pbtn = (CButton*)GetDlgItem(IDC_RADIO_H264);
	if( pbtn->GetCheck())

	CDlgDemoDlg::DeviceInfo[dwCard].dwVideoCodecStr=X264CODEC_FILTER;	
	pbtn = (CButton*)GetDlgItem(IDC_RADIO_DIVX);



	if( pbtn->GetCheck())
	CDlgDemoDlg::DeviceInfo[dwCard].dwVideoCodecStr="DivX? 5.1.1 Codec";



	CDialog::OnOK();
}

void CCodecSettingFrm::OnButtonBrowseSnapdir() 
{
	// TODO: Add your control notification handler code here

			CString str;

	BROWSEINFO bi;
	
	char name[MAX_PATH];
	
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	
	bi.hwndOwner = GetSafeHwnd();
	
	bi.pszDisplayName = name;
	
	bi.lpszTitle = "Select folder";
	
	bi.ulFlags = BIF_RETURNONLYFSDIRS ;
	
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	
	if(idl == NULL)
		return;
	
	SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH));
	
	str.ReleaseBuffer();
	
	PicSavePath = str;
	
//	if(str.GetAt(str.GetLength()-1) != '\\')
	//	PicSavePath += "\\";

	m_SnapEditPath.SetWindowText(PicSavePath);
	
}

void CCodecSettingFrm::OnButtonBrowseRecdir() 
{
	// TODO: Add your control notification handler code here
		CString str;

	BROWSEINFO bi;
	
	char name[MAX_PATH];
	
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	
	bi.hwndOwner = GetSafeHwnd();
	
	bi.pszDisplayName = name;
	
	bi.lpszTitle = "Select folder";
	
	bi.ulFlags = BIF_RETURNONLYFSDIRS ;
	
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	
	if(idl == NULL)
		return;
	
	SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH));
	
	str.ReleaseBuffer();
	
	RecSavePath = str;
	
//	if(str.GetAt(str.GetLength()-1) != '\\')
	//	RecSavePath += "\\";

	m_RecEditPath.SetWindowText(RecSavePath);
}
