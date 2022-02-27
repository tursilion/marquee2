// MfcSaverDlg.cpp : implementation file
//
//////////
//
// Copyright (C) 1991-98 Ed Halley.
//   http://www.explorati.com/people/ed/
//   ed@explorati.com
//
// This published source code represents original intellectual
// property, owned and copyrighted by Ed Halley.
//
// The owner has authorized this source code for general public
// use without royalty, under two conditions:
//    * The source code maintains this copyright notice in full.
//    * The source code is only distributed for free or
//      reasonable duplication cost, not for distribution profit.
//
// Unauthorized use, copying or distribution is a violation of
// U.S. and international laws and is strictly prohibited.
//
//////////
//
// Marquee2 Screen Saver
//
// (C) 2005 Mike Brent aka Tursi aka HarmlessLion.com
// This software is provided AS-IS. No warranty
// express or implied is provided.
//
// You may redistribute this software provided the original
// archive is UNCHANGED and a link back to my web page,
// http://harmlesslion.com, is provided as the author's site.
//
// Source code, if available, is provided for educational purposes
// only. You are welcome to read it, learn from it, mock
// it, and hack it up - for your own use only.
//
// Please contact me before distributing derived works or
// ports so that we may work out terms. I don't mind people
// using my code but it's been outright stolen before.
//
// -COMMERCIAL USE- Contact me first. I didn't make
// any money off it - why should you? ;) If you just learned
// something from this, then go ahead. If you just pinched
// a routine or two, let me know, I'll probably just ask
// for credit. If you want to derive a commercial tool
// or use large portions, we need to talk. ;)
//
// If this, itself, is a derived work from someone else's,
// then their original copyrights and licenses are left intact
// and in full force.
//
// http://harmlesslion.com - hit the web page for contact info
//

#include "StdAfx.h"
#include "MfcSaver.h"
#include "MfcSaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMfcSaverDlg, CScreenSaverDlg)
	//{{AFX_MSG_MAP(CMfcSaverDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnURL)
	ON_BN_CLICKED(IDC_BTNBROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_BTNFONT, OnFont)
	ON_BN_CLICKED(IDC_BTNBGCOLOR, OnBGColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMfcSaverDlg::CMfcSaverDlg()
{
	//{{AFX_DATA_INIT(CMfcSaverDlg)
	//}}AFX_DATA_INIT
}

BOOL CMfcSaverDlg::OnInitDialog()
{
	CMfcSaver* pSaver = (CMfcSaver*)AfxGetScreenSaverWnd();

	CScreenSaverDlg::OnInitDialog();

	if (pSaver) {
		pSaver->RestoreOptions();
	}

	return TRUE;
}

void CMfcSaverDlg::OnURL() 
{
	CString sURL;
	GetDlgItemText(IDC_BUTTON1, sURL);
	::ShellExecute(m_hWnd, NULL, sURL, NULL, NULL, 0);
}

void CMfcSaverDlg::OnBrowse() 
{
	CString csFile;

	GetDlgItemText(IDC_FILENAME, csFile);
	// This asserts! But it works. What's the deal?
	// AFX_MANAGE_STATE makes it worse!
	CFileDialog dlg(true, "txt", csFile, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, "Text Files|*.txt||", this);

	if (IDOK == dlg.DoModal()) {
		SetDlgItemText(IDC_FILENAME, dlg.GetPathName());
	}
}

void CMfcSaverDlg::OnFont() 
{
	LOGFONT font;
	CMfcSaver* pSaver = (CMfcSaver*)AfxGetScreenSaverWnd();

	ZeroMemory(&font, sizeof(font));

	CClientDC dc(this);
	font.lfHeight=-MulDiv(pSaver->fontsize, dc.GetDeviceCaps(LOGPIXELSY), 72);
	font.lfCharSet=DEFAULT_CHARSET;
	font.lfUnderline=(unsigned char)(pSaver->fontunderline?1:0);
	font.lfStrikeOut=(unsigned char)(pSaver->fontstrikeout?1:0);
	font.lfWeight=pSaver->fontbold?FW_BOLD:FW_NORMAL;
	font.lfItalic=(unsigned char)(pSaver->fontitalic?1:0);
	strncpy(font.lfFaceName, pSaver->fontname, 32);
	font.lfFaceName[31]='\0';
	
	CFontDialog dlg(&font, CF_EFFECTS|CF_SCREENFONTS);
	dlg.m_cf.rgbColors=pSaver->fontcolor;

	if (IDOK == dlg.DoModal()) {
		pSaver->fontsize=dlg.GetSize()/10;
		strcpy(pSaver->fontname, dlg.GetFaceName());
		pSaver->fontcolor=dlg.GetColor();
		pSaver->fontunderline=dlg.IsUnderline();
		pSaver->fontstrikeout=dlg.IsStrikeOut();
		pSaver->fontbold=dlg.IsBold();
		pSaver->fontitalic=dlg.IsItalic();
	}
}

void CMfcSaverDlg::OnBGColor() 
{
	CMfcSaver* pSaver = (CMfcSaver*)AfxGetScreenSaverWnd();
	CHOOSECOLOR col;
	static COLORREF pal[16];
	static bool colorinit=false;

	if (false == colorinit) {
		// copy the color into the user defined colors
		pal[0]=pSaver->bgcolor;
	}
	
	ZeroMemory(&col,sizeof(col));
	col.lStructSize=sizeof(col);
	col.rgbResult=pSaver->bgcolor;
	col.Flags=CC_RGBINIT;
	col.lpCustColors=pal;

	if (ChooseColor(&col)) {
		pSaver->bgcolor=col.rgbResult;
	}
}

/////////////////////////////////////////////////////////////////////////////

//
// As with most MFC dialog boxes, the DoDataExchange() is where all the work
// happens.  There's no easy DDX_Trackbar thing to set up the control, so
// we do it ourselves.  See how the SaveOptions() and RestoreOptions() are
// called on the CMfcSaver to keep those options persistent.
//

void CMfcSaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CScreenSaverDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcSaverDlg)
	//}}AFX_DATA_MAP

	CMfcSaver* pSaver = (CMfcSaver*)AfxGetScreenSaverWnd();
	if (!pSaver) {
		return;
	}

	CSliderCtrl* pSlider;
	CButton* pButton;
	CEdit *pEdit;
	if (!pDX->m_bSaveAndValidate)
	{
		pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
		pSlider->SetRange(1, 100);
		pSlider->SetPos(pSaver->speed);

		pButton=(CButton*)GetDlgItem(IDC_CENTERED); 
		pButton->SetCheck(pSaver->location ? 1 : 0);

		pButton=(CButton*)GetDlgItem(IDC_RANDOM);
		pButton->SetCheck(pSaver->location ? 0 : 1);

		pButton=(CButton*)GetDlgItem(IDC_RANDOMQUOTE);
		pButton->SetCheck(pSaver->randomquote ? 1 : 0);

		pEdit=(CEdit*)GetDlgItem(IDC_FILENAME);
		pEdit->SetWindowText(pSaver->filename);
	}
	else
	{
		pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
		pSaver->speed = pSlider->GetPos();

		pButton=(CButton*)GetDlgItem(IDC_CENTERED);
		pSaver->location = pButton->GetCheck() ? 1 : 0;

		pButton=(CButton*)GetDlgItem(IDC_RANDOM);
		pSaver->location = pButton->GetCheck() ? 0 : 1;

		pButton=(CButton*)GetDlgItem(IDC_RANDOMQUOTE);
		pSaver->randomquote = pButton->GetCheck() ? 1 : 0;

		pEdit=(CEdit*)GetDlgItem(IDC_FILENAME);
		pEdit->GetWindowText(pSaver->filename, 1024);

		pSaver->SaveOptions();
	}
}

