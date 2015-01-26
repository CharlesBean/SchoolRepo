/**
 * \file ViewTimeline.h
 *
 * \author Charles Bean
 *
 * \brief View window for the animation timeline
 */

#pragma once

#include "PictureObserver.h"

class CMainFrame;

/** \brief View window for the animation timeline */
class CViewTimeline : public CScrollView, public CPictureObserver
{
	DECLARE_DYNCREATE(CViewTimeline)

public:
    static const int Height = 90;      ///< Height to make this window

	/** \brief Set the mainFrame pointer
	* \param mainFrame Pointer to the CMainFrame window */
	void SetMainFrame(CMainFrame *mainFrame) { mMainFrame = mainFrame; }

	/** \brief Updates the observer */
	virtual void UpdateObserver() override;

protected:
	CViewTimeline();           // protected constructor used by dynamic creation
	virtual ~CViewTimeline();


protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct

	DECLARE_MESSAGE_MAP()

public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnEditSetkeyframe();
    afx_msg void OnEditDeletekeyframe();

private:
	/// The main frame window that uses this view
	CMainFrame *mMainFrame = nullptr;

	/// Bitmap image for the pointer
	std::unique_ptr<Gdiplus::Bitmap> mPointer;

	/// Flag to indicate we are moving the pointer
	bool mMovingPointer = false;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


