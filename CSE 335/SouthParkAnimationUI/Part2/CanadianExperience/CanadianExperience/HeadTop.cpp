/**
 * \file HeadTop.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "HeadTop.h"
#include "Actor.h"
#include "Timeline.h"

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/** \brief Destructor */
CHeadTop::~CHeadTop()
{
}

/** \brief Constructor */
CHeadTop::CHeadTop(const std::wstring &name, const std::wstring &filename) : CImageDrawable(name, filename)
{

}

/** \brief Draws our head
* \param graphics - The graphics context to draw the head on */
void CHeadTop::Draw(Graphics *graphics)
{
	// Upcall
	CImageDrawable::Draw(graphics);

	// Draw the eyes
	DrawEye(graphics, mRightEye);
	DrawEye(graphics, mLeftEye);

	// Draw eyebrows
	DrawEyebrow(graphics, mRightEyebrowLeftLocation, mRightEyebrowRightLocation);
	DrawEyebrow(graphics, mLeftEyebrowLeftLocation, mLeftEyebrowRightLocation);

}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param  p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
	// Make p relative to the image center
	p = p - GetCenter();

	// Rotate as needed and offset
	return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/** \brief Draws an eyebrow
* \param graphics - The context
* \param location - The place to draw it with respect to the image (not background) */
void CHeadTop::DrawEyebrow(Graphics *graphics, Point locationLeft, Point locationRight)
{
	// Eyebrows 
	auto state = graphics->Save();

	// Creating a point relative to screen from a point in the image
	Point leftP = TransformPoint(locationLeft);
	Point rightP = TransformPoint(locationRight);

	// Actual drawing
	Pen pen(Color::Black, 4);

	// Always horizontal (fix)
	graphics->DrawLine(&pen, leftP, rightP);

	graphics->Restore(state);
}

/** \brief Draws an eye at a location relative to our head top
* \param graphics - The contexxt
* \param location - The location to put the eye */
void CHeadTop::DrawEye(Graphics *graphics, Point location)
{
	float wid = 15.0f;
	float hit = 20.0f;

	auto state = graphics->Save();

	// Transform
	Point p = TransformPoint(location);

	// Create black brush
	SolidBrush brush(Color::Black);

	// Allow for movement and rotation
	graphics->TranslateTransform((REAL)p.X, (REAL)p.Y);
	graphics->RotateTransform((float)(-mPlacedR * RtoD));

	// Draw ellipse
	graphics->FillEllipse(&brush, -wid / 2, -hit / 2, wid, hit);

	graphics->Restore(state);
}

/** \brief Set the keyframe based on the current status.
*/
void CHeadTop::SetKeyframe()
{
	CDrawable::SetKeyframe();

	Point headPos = GetPosition();

	mChannel.SetKeyframe(headPos);
}

/** \brief Get the current channel from the animation system.
*/
void CHeadTop::GetKeyframe()
{
	CDrawable::GetKeyframe();

	if (mChannel.IsValid())
		SetPosition(mChannel.GetPoint());
}

/** Add the channels for this drawable to a timeline
* \param timeline The timeline class.
*/
void CHeadTop::SetTimeline(CTimeline *timeline)
{
	CDrawable::SetTimeline(timeline);

	timeline->AddChannel(&mChannel);
}

/** \brief Sets the actor for this head
* \param actor - A pointer to the actor we are selecting */
void CHeadTop::SetActor(CActor *actor)
{
	CDrawable::SetActor(actor);
}
