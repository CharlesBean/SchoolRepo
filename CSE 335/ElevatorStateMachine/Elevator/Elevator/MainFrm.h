/**
 * \file MainFrm.h
 *
 * \author Charles Bean
 *
 * \brief Main frame file
 */


// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ElevatorApp.h"
#include "ElevatorWnd.h"

/**
 * \brief The main frame class
 */
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	/** \brief Asserts that the frame is valid */
	virtual void AssertValid() const;
	/** \brief Dumps the frame */
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar        m_wndStatusBar;
	CElevatorWnd      mElevator;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

private:
    void Initialize();
};

