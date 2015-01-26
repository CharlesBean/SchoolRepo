/**
 * \file TimelineDlg.h
 *
 * \author Charles Bean
 *
 * \brief Our Timeline Dialog class
 */

#pragma once

#include "Timeline.h"

// CTimelineDlg dialog

/**
 * \brief A class representing a dialog for our timeline
 */
class CTimelineDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimelineDlg)

public:
	CTimelineDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTimelineDlg();

	// Dialog Data
	enum { IDD = IDD_TIMELINEDLG };
	
	/**
	* \brief Pass a timeline object to this dialog box class.
	* \param timeline The timeline object.
	*/
	void SetTimeline(CTimeline *timeline);

	/** \brief Transfer dialog values to the Timeline object
	*/
	void Take();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	/// Our dialog passed number of frames
	int mNumFrames;

	/// The timeline we are editing
	CTimeline *mTimeline = nullptr;
	
	/// Our dialog passed frame rate
	int mFrameRate;
};
