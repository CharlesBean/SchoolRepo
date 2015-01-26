/**
 * \file ImageDrawable.h
 *
 * \author Charles Bean
 *
 * \brief Class representing an image drawable (not polygon)
 */

#pragma once

#include "Drawable.h"
#include <memory>
#include <string>

using namespace std;
using namespace Gdiplus;

/** 
* \brief Class representing an image drawable (not polygon)
*/
class CImageDrawable : public CDrawable
{
public:
	/** Remove Default, Copy, Assignment **/

	/** \brief Default constructor disabled */
	CImageDrawable() = delete;
	/** \brief Copy constructor disabled */
	CImageDrawable(const CImageDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CImageDrawable &) = delete;


	/** Constructor & Destructor **/

	/** \brief Destructor */
	virtual ~CImageDrawable();

	/** \brief Constructor
	* \param name - A string to name our image by 
	* \param filename - The filename of our image */
	CImageDrawable(const wstring &name, const wstring &filename);


	/** General Functions **/

	/** \brief Draws our image 
	* \param graphics - The graphics context to draw our image on */
	void Draw(Graphics *graphics);

	/** \brief A hit-test for our image 
	* \param pos - A point to test for hitting 
	* \return True if we hit something at coordinates */
	bool HitTest(Point pos);


	/** Getters & Setters **/

	/** \brief Gets the center of our image
	* \return Gdiplus::Point where the center of our image is */
	Point GetCenter() const { return mCenter; }

	/** \brief Sets the center location
	* \center The point to set the center to */
	void SetCenter(Point center) { mCenter = center; }

protected:
	/// The image for this drawable
	std::unique_ptr<Gdiplus::Bitmap> mImage;

private:
	/// The center of our image
	Point mCenter = Point(0, 0);
};

