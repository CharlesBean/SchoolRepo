/**
 * \file Drawable.h
 *
 * \author Charles Bean
 *
 * \brief A drawable is one part of an actor. Drawable parts can be moved
 *		independently.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace Gdiplus;

class CActor;

/**
* \brief Abstract base class for drawable elements of our picture.
*
* A drawable is one part of an actor. Drawable parts can be moved
* independently.
*/
class CDrawable
{
public:
	/** Removal of Constructor Default, Copy, and Assignment **/

	/** \brief Default constructor disabled */
	CDrawable() = delete;
	/** \brief Copy constructor disabled */
	CDrawable(const CDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CDrawable &) = delete;

	/** \brief Virtual Destructor */
	virtual ~CDrawable();


	/** General Functions **/

	/** \brief Draws the drawable
	* \param graphics - The graphics context to draw in */
	virtual void Draw(Gdiplus::Graphics *graphics) = 0;

	/** \brief Moves a point
	* \param offset - The point to choose
	* \param rotate - how much to rotate by */
	void Place(Gdiplus::Point offset, double rotate);

	/** \brief Adds a child 
	* \param child - The child to add */
	void AddChild(std::shared_ptr<CDrawable> child);

	/** \brief The hit-test function for our drawable (pure virtual)
	* \param pos - The position to test for hit 
	* \return bool - If we hit something */
	virtual bool HitTest(Gdiplus::Point pos) = 0;

	/** \brief Returns if our drawable is movable
	* \return bool - If the object can be moved */
	virtual bool IsMovable() { return false; }

	/** \brief Moves our drawable based off of a point
	* \param delta - A point */
	void Move(Gdiplus::Point delta);


	/** Getters & Setters **/

	/** \brief Sets the actor for this drawable
	* \param actor - A pointer to the actor we are selecting */
	void SetActor(CActor *actor);

	/** \brief Set the drawable position
	* \param pos The new drawable position*/
	void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

	/** \brief Get the drawable position
	* \returns The drawable position*/
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** \brief Set the rotation angle in radians
	* \param r The new rotation angle in radians*/
	void SetRotation(double r) { mRotation = r; }

	/** \brief Get the rotation angle in radians
	* \returns The rotation angle in radians*/
	double GetRotation() const { return mRotation; }

	/** \brief Get the drawable name
	* \returns The drawable name */
	std::wstring GetName() const { return mName; }

	/** \brief Sets the parent of a child 
	* \param parent - Pointer to the parent */
	void SetParent(CDrawable *parent) { mParent = parent; }

	/** \brief Gets the parent of a child (if exists)
	* \returns Pointer to the parent */
	CDrawable* GetParent() const { return mParent; }

protected:
	/// The actual position in the drawing
	Point mPlacedPosition = Point(0, 0);

	/// The actual rotation of our drawable
	double mPlacedR = 0;


	/** \brief Our constructor
	* \param name - Our drawable's name to be set */
	CDrawable(const std::wstring &name);

	/** \brief Function for rotating a point
	* \param point - the point to rotate
	* \param angle - the angle to rotate by
	* \return A rotated point */
	Point RotatePoint(Point point, double angle);

private:
	/// Our drawable location
	Point mPosition = Point(0, 0);

	/// Our drawable's name
	wstring mName = NULL;

	/// Our rotation factor
	double mRotation = 0;

	/// Our actor
	CActor *mActor = nullptr;

	/// Our children
	vector<shared_ptr<CDrawable> > mChildren;

	/// Our parent
	CDrawable *mParent = nullptr;

};

