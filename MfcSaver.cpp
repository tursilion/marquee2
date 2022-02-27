// MfcSaver.cpp : Defines the class behaviors for the application.
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
// EXMatrix Screen Saver
//
// (C) 2003 Mike Brent aka Tursi aka HarmlessLion.com
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
#include "shlwapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMfcSaver, CScreenSaverWnd)
//{{AFX_MSG_MAP(CMfcSaver)
ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// As required of CScreenSaverWnd-based screen savers, these are the two
// global instances of screen saver objects.  One is the saver itself,
// and one is the dialog for configuring the options of the screen saver.
//
// Unlike most MFC applications, there is no instance of any CWinApp object.
//
CMfcSaver theSaver;
CMfcSaverDlg theSaverDialog;

CMfcSaver::CMfcSaver()
{
	srand((unsigned int)time(NULL));
	m_bAutoBlack=TRUE;

	speed=10;
	location=1;	// centered
	randomquote=0;	// not random
	memset(filename, 0, 1024);
	strcpy(fontname, "Arial");
	fontsize=12;
	fontcolor=RGB(0,0,0);
	fontstrikeout=0;
	fontunderline=0;
	fontbold=0;
	fontitalic=0;
	bgcolor=RGB(0xff,0xff,0xff);
}

// Not called??
CMfcSaver::~CMfcSaver()
{
}

/////////////////////////////////////////////////////////////////////////////
//
// The CMfcSaverDlg will need to be able to access our customizable
// attributes.  We call OnInitialUpdate() again to reorganize internally if
// any of these change.
//

void CMfcSaver::SaveOptions()
{
	CString myStr;

	myStr.Format("%d", speed);
	SHRegSetUSValue("Software\\Marquee2", "Speed", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);

	SHRegSetUSValue("Software\\Marquee2", "Filename", REG_SZ, filename, strlen(filename), SHREGSET_FORCE_HKLM);

	myStr.Format("%d", location);
	SHRegSetUSValue("Software\\Marquee2", "Location", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);

	myStr.Format("%d", randomquote);
	SHRegSetUSValue("Software\\Marquee2", "RandomQuote", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);

	SHRegSetUSValue("Software\\Marquee2", "Fontname", REG_SZ, fontname, strlen(fontname), SHREGSET_FORCE_HKLM);

	myStr.Format("%d", fontsize);
	SHRegSetUSValue("Software\\Marquee2", "FontSize", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);

	myStr.Format("%d", fontcolor);
	SHRegSetUSValue("Software\\Marquee2", "FontColor", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);

	myStr.Format("%d", fontstrikeout);
	SHRegSetUSValue("Software\\Marquee2", "FontStrikeout", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);

	myStr.Format("%d", fontunderline);
	SHRegSetUSValue("Software\\Marquee2", "FontUnderline", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);
	
	myStr.Format("%d", fontbold);
	SHRegSetUSValue("Software\\Marquee2", "FontBold", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);
	
	myStr.Format("%d", fontitalic);
	SHRegSetUSValue("Software\\Marquee2", "FontItalic", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);

	myStr.Format("%d", bgcolor);
	SHRegSetUSValue("Software\\Marquee2", "BGColor", REG_SZ, (void*)(LPCSTR)myStr, myStr.GetLength(), SHREGSET_FORCE_HKLM);
}

void CMfcSaver::RestoreOptions()
{
	char tmp[1025];
	DWORD dwTmp, dwSize;
	int nTmp;

	speed=10;
	location=1;	// centered
	randomquote=0;	// not random
	memset(filename, 0, 1024);
	strcpy(fontname, "Arial");
	fontsize=12;
	fontcolor=RGB(0,0,0);
	bgcolor=RGB(0xff,0xff,0xff);
	fontstrikeout=0;
	fontunderline=0;
	fontbold=0;
	fontitalic=0;

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "Speed", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[dwSize]='\0';
		nTmp=atoi(tmp);
		if ((nTmp>0) && (nTmp<101)) speed=nTmp;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "Location", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[dwSize]='\0';
		nTmp=atoi(tmp);
		if ((nTmp==0) || (nTmp == 1)) location=nTmp;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "RandomQuote", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[dwSize]='\0';
		nTmp=atoi(tmp);
		if ((nTmp==0) || (nTmp == 1)) randomquote=nTmp;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "Fontsize", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[dwSize]='\0';
		nTmp=atoi(tmp);
		if ((nTmp>0) || (nTmp < 100)) fontsize=nTmp;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "FontColor", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[dwSize]='\0';
		nTmp=atoi(tmp);
		fontcolor=nTmp;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "BGColor", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[dwSize]='\0';
		nTmp=atoi(tmp);
		bgcolor=nTmp;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "Filename", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[1024]='\0';
		strcpy(filename, tmp);
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "Fontname", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[1024]='\0';
		strcpy(fontname, tmp);
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "FontStrikeout", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[1024]='\0';
		nTmp=atoi(tmp);
		fontstrikeout=nTmp?1:0;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "FontUnderline", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[1024]='\0';
		nTmp=atoi(tmp);
		fontunderline=nTmp?1:0;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "FontBold", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[1024]='\0';
		nTmp=atoi(tmp);
		fontbold=nTmp?1:0;
	}

	dwSize=1024;
	if (ERROR_SUCCESS == SHRegGetUSValue("Software\\Marquee2", "FontItalic", &dwTmp, tmp, &dwSize, true, NULL, NULL)) {
		tmp[1024]='\0';
		nTmp=atoi(tmp);
		fontitalic=nTmp?1:0;
	}
}

/////////////////////////////////////////////////////////////////////////////
//
// While this is just demonstrating how to override the virtual functions of
// CScreenSaverWnd, it also shows something about using CImageList to
// draw from a library of simple images.
//
// When our timer goes off, we just invalidate the window.  The OnDraw()
// override will be called appropriately when the system has some free cycles
// to spend on drawing.  Remember:  a screen saver should share the CPU, so
// the computer can work on other tasks like downloading or numbercrunching.
//

void CMfcSaver::OnInitialUpdate()
{
	do {
		GetNextText();
	} while (strlen(szString) == 0);
	SetTimer(1, 50, NULL);
}

void CMfcSaver::GetNextText() {
	static int nFilePos=0;

	position=GetSystemMetrics(SM_CXVIRTUALSCREEN);
#ifdef _DEBUG
	position/=3;
#endif
	ypos=location?GetSystemMetrics(SM_CYVIRTUALSCREEN)/2:rand()%GetSystemMetrics(SM_CYVIRTUALSCREEN);

	FILE *fp=fopen(filename, "r");
	if (NULL == fp) {
		strcpy(szString, "No Text File Loaded - please configure!");
	} else {
		if (randomquote) {
			int nEnd, nRatio;
			fseek(fp, 0, SEEK_END);
			nEnd=ftell(fp);
			nRatio=1;
			while (nEnd > 65535) {	// range of rand() is 16 bit
				nEnd/=2;
				nRatio++;
			}
			nFilePos=rand()*nRatio;
			fseek(fp, nFilePos, SEEK_SET);
			// Find a line end or EOF
			for (;;) {
				if ('\n' == fgetc(fp)) {
					break;
				}
				if (feof(fp)) {
					fseek(fp, 0, SEEK_SET);
					break;
				}
			}
			while (fgetc(fp) < ' ');
			fseek(fp, -1, SEEK_CUR);

			if (NULL == fgets(szString, 1024, fp)) {
				strcpy(szString, "File error reading source file - please reconfigure!");
				fclose(fp);
				return;
			}
		} else {
			fseek(fp, nFilePos, SEEK_SET);
			if (NULL == fgets(szString, 1024, fp)) {
				nFilePos=0;
				fseek(fp, nFilePos, SEEK_SET);
				if (NULL == fgets(szString, 1024, fp)) {
					strcpy(szString, "File error reading source file - please reconfigure!");
					fclose(fp);
					return;
				}
			}
		}
		// strip EOL
		while ((szString[strlen(szString)-1]) && (szString[strlen(szString)-1]<=' ')) {
			szString[strlen(szString)-1]='\0';
		}
		nFilePos=ftell(fp);
		fclose(fp);
	}
}

// Although we really *shouldn't* do this stuff here in the draw method,
// it works well enough since a screensaver won't likely be interrupted
// by other windows or extra paint requests
void CMfcSaver::OnDraw(CDC* pDC)
{
	int offset;
	int strsize=strlen(szString);
	CFont *pOld, cNew;

	LOGFONT font;
	ZeroMemory(&font, sizeof(font));
	font.lfHeight=-MulDiv(fontsize, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	font.lfCharSet=DEFAULT_CHARSET;
	font.lfUnderline=(unsigned char)(fontunderline?1:0);
	font.lfStrikeOut=(unsigned char)(fontstrikeout?1:0);
	font.lfWeight=fontbold?FW_BOLD:FW_NORMAL;
	font.lfItalic=(unsigned char)(fontitalic?1:0);
	strncpy(font.lfFaceName, fontname, 32);
	font.lfFaceName[31]='\0';
	cNew.CreateFontIndirect(&font);
	pOld=pDC->SelectObject(&cNew);
	CSize size=pDC->GetTextExtent(szString, strsize);

	pDC->SetTextColor(fontcolor);
	if (location) {
		offset=0;
	} else {
		offset=-(size.cy/2);
	}

	pDC->FillSolidRect(0, 0, GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN), bgcolor);
	pDC->TextOut(position, ypos+offset, szString, strsize);

	pDC->SelectObject(pOld);

	if (position+size.cx < 0) {
		do {
			GetNextText();
		} while (strlen(szString) == 0);
	}
}

void CMfcSaver::OnTimer(UINT nIDEvent) 
{
	CScreenSaverWnd::OnTimer(nIDEvent);

	position-=speed;
	
	Invalidate(FALSE);
}

