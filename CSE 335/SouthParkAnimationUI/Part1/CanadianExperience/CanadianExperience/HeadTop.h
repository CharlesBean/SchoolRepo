/**
 * \file HeadTop.h
 *
 * \author Charles Bean
 *
 * \brief A class for representing the top of an actor's head 
 */

#pragma once

#include "ImageDrawable.h"

#include <memory>

using namespace Gdiplus;

/** 
* \brief A class for representing the top of an actor's head 
*/
class CHeadTop : public CImageDrawable
{
public:
	/** Delete Default, Copy, Assignemtn **/

	/** \brief Default constructor disabled */
	CHeadTop() = delete;

	/** \brief Copy constructor disabled */
	CHeadTop(const CHeadTop &) = delete;

	/** \brief Assignment operator disabled */
	void operator=(const CHeadTop &) = delete;


	/** Constructor & Destructor**/

	/** \brief Destructor */
	virtual ~CHeadTop();

	/** \brief Non-default Constructor */
	CHeadTop(const std::wstring &name, const std::wstring &filename);


	/** General Functions **/

	/** \brief Draws our head
	* \param graphics - The graphics context to draw the head on */
	void Draw(Graphics *graphics);

	/** \brief Draws an eyebrow 
	* \param graphics - The context 
	* \param locationLeft - Location of the left eye
	* \param locationRight - Location of the right eye */
	void DrawEyebrow(Graphics *graphics, Point locationLeft, Point locationRight);

	/** \brief Draws an eye at a location relative to our head top 
	* \param graphics - The contexxt
	* \param location - The location to put the eye */
	void DrawEye(Graphics *graphics, Point location);

	/** \brief Determines if we can move our head (override)
	* \return True because heads should be able to move on their own */
	bool IsMovable() override { return true; }

	/** Transform a point from a location on the bitmap to
	*  a location on the screen.
	* \param  p Point to transform
	* \returns Transformed point
	*/
	Point TransformPoint(Gdiplus::Point p);


	/** Getters & Setters **/

	/** \brief Sets our eye locations 
	* \param leftEyeLocation - The location of the left eye
	* \param rightEyeLocation - The location of the right eye */
	void SetEyes(Point leftEyeLocation, Point rightEyeLocation) { mLeftEye = leftEyeLocation; mRightEye = rightEyeLocation; }
	
	/** \brief Sets our left eyebrows left and right endpoints 
	* \param leftEndpoint - The left end of the eyebrow
	* \param rightEndpoint - The right end */
	void SetLeftEyebrow(Point leftEndpoint, Point rightEndpoint) { mLeftEyebrowLeftLocation = leftEndpoint; mLeftEyebrowRightLocation = rightEndpoint; }

	/** \brief Sets our right eyebrows left and right endpoints
	* \param leftEndpoint - The left end of the eyebrow
	* \param rightEndpoint - The right end */
	void SetRightEyebrow(Point leftEndpoint, Point rightEndpoint) { mRightEyebrowLeftLocation = leftEndpoint; mRightEyebrowRightLocation = rightEndpoint; }

private:
	/** Eyes **/

	/// Our right eye (Default at 0, 0)
	Point mRightEye = Point(0, 0);

	/// Our left eye (change to set in factories)
	Point mLeftEye = Point(0, 0);


	/** Eyebrows **/

	/// Right eyebrow location (left end point)
	Point mRightEyebrowLeftLocation = Point(0, 0);

	/// Right eyebrow location (right end point)
	Point mRightEyebrowRightLocation = Point(0, 0);


	/// Left eyebrow location (left end point)
	Point mLeftEyebrowLeftLocation = Point(0, 0);

	/// Left eyebrow location (right end point)
	Point mLeftEyebrowRightLocation = Point(0, 0);
};

