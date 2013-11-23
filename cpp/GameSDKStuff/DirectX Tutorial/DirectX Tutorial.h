// DirectX Tutorial.h : main header file for the DIRECTX TUTORIAL application
//

#if !defined(AFX_DIRECTXTUTORIAL_H__2870BFA6_0014_11D3_BEA3_0040052C8ABC__INCLUDED_)
#define AFX_DIRECTXTUTORIAL_H__2870BFA6_0014_11D3_BEA3_0040052C8ABC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirectXTutorialApp:
// See DirectX Tutorial.cpp for the implementation of this class
//

class CDirectXTutorialApp : public CWinApp
{
public:
	CDirectXTutorialApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectXTutorialApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDirectXTutorialApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTXTUTORIAL_H__2870BFA6_0014_11D3_BEA3_0040052C8ABC__INCLUDED_)
