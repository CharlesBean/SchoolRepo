/**
 * \file PolyDrawable.h
 *
 * \author Charles Bean
 *
 * \brief This class has a list of points and draws a polygon
 *		drawable based on those points.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Drawable.h"

using namespace std;
using namespace Gdiplus;

/**
* \brief A drawable based on polygon images.
*
* This class has a list of points and draws a polygon
* drawable based on those points.
*/
class CPolyDrawable : public CDrawable
{
public:
	/** Disabling Default, Copy, Assignment **/

	/** \brief Default constructor disabled */
	CPolyDrawable() = delete;

	/** \brief Copy constructor disabled */
	CPolyDrawable(const CPolyDrawable &) = delete;

	/** \brief Assignment operator disabled */
	void operator=(const CPolyDrawable &) = delete;


	/** Constructor & Destructor **/

	/** \brief Our non-default constructor
	* \param name - The name to give our polydraw */
	CPolyDrawable(const wstring &name);

	/** \brief Virtual destructor */
	virtual ~CPolyDrawable();
	

	/** General Functions **/

	/** \brief Draws our polydrawable
	* \param graphics - the graphics to draw to */
	void Draw(Graphics *graphics);

	/** \brief A hit test for our polydraw
	* \param pos - The point to hit test
	* \return A boolean of true if we hit something */
	bool HitTest(Point pos);

	/** \brief Adds a point to our polydrawable
	* \param point - The point to add */
	void AddPoint(Point point);


	/** Getters & Setters **/

	/** \brief Gets our poly color 
	* \return Gdiplus::Color representing our polydraw color */
	Color GetColor() const { return mColor; }

	/** \brief Sets the color for our polydraw object 
	* \color The Gdiplus::Color we wish to change it to */
	void SetColor(Color color) { mColor = color; }

private:
	/// The polygon color
    Gdiplus::Color mColor = Gdiplus::Color::Black;

	/// The array of point objects
	std::vector<Gdiplus::Point> mPoints;
};

