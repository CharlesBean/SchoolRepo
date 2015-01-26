/**
 * \file ViewTimeline.cpp
 *
 * \author Charles Bean
 */


#include "stdafx.h"
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"

#include "MainFrm.h"

using namespace std;
using namespace Gdiplus;


IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** \brief Constructor */
CViewTimeline::CViewTimeline()
{

}

/** \brief Destructor */
CViewTimeline::~CViewTimeline()
{
}


BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
    ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
END_MESSAGE_MAP()


/** \brief Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** \brief Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{
    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    // TODO: Drawing code goes here
}


/** \brief Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \returns FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** \brief Handle the Edit>Set Keyframe menu option */
 void CViewTimeline::OnEditSetkeyframe()
 {
     // TODO: Add your command handler code here
 }


 /** \brief Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
     // TODO: Add your command handler code here
 }

 /** \brief Force an update of this window when the picture changes.
 */
 void CViewTimeline::UpdateObserver()
 {
	 Invalidate();
 }