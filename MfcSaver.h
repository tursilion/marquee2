// MfcSaver.h : main header file for the MFCSAVER application
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

#ifndef __MFCSAVER_H__
#define __MFCSAVER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////

#include "ScreenSaverWnd.h"

/////////////////////////////////////////////////////////////////////////////

class CMfcSaver : public CScreenSaverWnd
{
// Construction
public:
	CMfcSaver();
	virtual ~CMfcSaver();

	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();
	virtual void SaveOptions();
	virtual void RestoreOptions();
	virtual void GetNextText();
	//{{AFX_VIRTUAL(CMfcSaver)
	//}}AFX_VIRTUAL

	int speed;
	int location;
	int randomquote;
	char filename[1024];
	char fontname[1024];
	int fontsize;
	int fontstrikeout;
	int fontunderline;
	int fontbold;
	int fontitalic;
	COLORREF fontcolor;
	COLORREF bgcolor;
	int position;
	int ypos;
	char szString[1024];

protected:
	//{{AFX_MSG(CMfcSaver)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MFCSAVER_H__
