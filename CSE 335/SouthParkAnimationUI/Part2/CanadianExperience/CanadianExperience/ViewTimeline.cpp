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
#include "Timeline.h"
#include "Picture.h"
#include <sstream>

using namespace std;
using namespace Gdiplus;


/// The window height
const int WindowHeight = 65;

/// The spacing between ticks in the timeline
const int TickSpacing = 3;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// The amount of space to leave under the tick marks
const int TickUnder = 10;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;


IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** \brief Constructor */
CViewTimeline::CViewTimeline()
{
	mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer.png"));
	assert(mPointer->GetLastStatus() == Ok);
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
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
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
	/** General **/

	// Get the timeline
	CTimeline *timeline = GetPicture()->GetTimeline();

	// Set the scroll system correctly
	CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
	SetScrollSizes(MM_TEXT, sizeTotal);

	// Setting buffer
    CDoubleBufferDC dbDC(pDC);

	// Setting graphics
    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    
	/*** Draw the timeline ***/


	// Get the window height and width
	CRect rect;
	GetClientRect(&rect);
	int hit = rect.Height();
	int wid = rect.Width();


	/** Drawing ticks **/

	// Initialize tick distance
	int x = BorderLeft;

	// Initialize spacing factor
	int factor = 1;

	// Loop over frames
	for (int tickNum = 0; tickNum <= timeline->GetNumFrames(); tickNum++)
	{
		// If we are on a big tick
		bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;

		// Set y-values
		int y = hit - TickUnder;


		// Pen for a tick
		Pen tickpen(Color::Black, 1);

		// If we are on a big line
		if (onSecond)
		{
			// Draw the long line
			graphics.DrawLine(&tickpen, x, y, x, y - TickLong);


			/** Draw the number **/

			// Create font
			FontFamily fontFamily(L"Arial");
			Gdiplus::Font font(&fontFamily, 12);

			// Convert the tick number to seconds in a string
			std::wstringstream str;
			str << tickNum / timeline->GetFrameRate();
			std::wstring wstr = str.str();

			// Sizing
			RectF size;
			PointF origin(0.0f, 0.0f);
			graphics.MeasureString(wstr.c_str(), wstr.size(), &font, origin, &size);

			// Origin
			PointF location((REAL)(x - (size.Width / 2)), (REAL)(y - TickLong - size.Height));

			// Brush
			SolidBrush brush(Color(0, 0, 0));

			// Draw 
			graphics.DrawString(wstr.c_str(), -1, &font, location, &brush);
		}
		else // We are in between
		{
			// Draw a short line
			graphics.DrawLine(&tickpen, x, y, x, y - TickShort);
		}



		/** Draw the pointer **/

		// X distance (double or int?)
		double pointerX = timeline->GetCurrentTime() * timeline->GetFrameRate() * TickSpacing + BorderLeft;

		// Drawing
		graphics.DrawImage(mPointer.get(), (REAL)(pointerX - ((double)mPointer->GetWidth() / 2)), (REAL)(y- TickLong), (REAL)mPointer->GetWidth(), (REAL)mPointer->GetHeight());



		/** Updating **/

		// Change x distance
		x = BorderLeft + (TickSpacing * factor);

		// Increment the factor
		factor += 1;
	}
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

/*! \brief Handle a press of the keyframe set button on the toolbar
*/
void CViewTimeline::OnEditSetkeyframe()
{
	for (auto actor : *GetPicture())
	{
		actor->SetKeyframe();
	}
}


 /** \brief Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
	 // Delete the frame we are over (if it is a keyframe)
	 GetPicture()->GetTimeline()->DeleteKeyframe();
 }

 /** \brief Force an update of this window when the picture changes.
 */
 void CViewTimeline::UpdateObserver()
 {
	 Invalidate();
	 UpdateWindow();
 }

 /** Handle a left button mouse press event
 * \param nFlags flags associated with the mouse press
 * \param point The location of the mouse press
 */
 void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
 {
	 // Convert mouse coordinates to logical coordinates
	 CClientDC dc(this);
	 OnPrepareDC(&dc);
	 dc.DPtoLP(&point);

	 int x = point.x;

	 // Get the timeline
	 CTimeline *timeline = GetPicture()->GetTimeline();
	 int pointerX = (int)(timeline->GetCurrentTime() * timeline->GetFrameRate() * TickSpacing + BorderLeft);

	 mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 && x <= pointerX + (int)mPointer->GetWidth() / 2;

	 __super::OnLButtonDown(nFlags, point);
 }

 /** Handle a mouse move event
 * \param nFlags flags associated with the mouse move
 * \param point The location of the mouse move
 */
 void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
 {
	 // Convert mouse coordinates to logical coordinates
	 CClientDC dc(this);
	 OnPrepareDC(&dc);
	 dc.DPtoLP(&point);

	 // If we are moving the pointer
	 if (mMovingPointer)
	 {
		 // Get timeline
		 CTimeline *timeline = GetPicture()->GetTimeline();

 		 // Calcualte the time from our frame
		 double pointerTime = (double)((double)((double)point.x - (double)BorderLeft) / (double)((double)timeline->GetFrameRate() * (double)TickSpacing));

		 // If the point is within the bounds
		 if (pointerTime >= 0 && pointerTime <= (timeline->GetNumFrames() / timeline->GetFrameRate()))
		 {
			 // Set the animation time
			 GetPicture()->SetAnimationTime(pointerTime);
		 }

	 }

	 __super::OnMouseMove(nFlags, point);
 }

 /** Handle a left button mouse release event
 * \param nFlags flags associated with the mouse release
 * \param point The location of the mouse release
 */
 void CViewTimeline::OnLButtonUp(UINT nFlags, CPoint point)
 {
	 // We are no longer moving pointer
	 mMovingPointer = false;

	 __super::OnLButtonUp(nFlags, point);
 }
