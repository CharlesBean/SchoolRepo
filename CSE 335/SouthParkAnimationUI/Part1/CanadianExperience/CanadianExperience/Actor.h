/**
 * \file Actor.h
 *
 * \author Charles Bean
 *
 * \brief An actor is some graphical object that consists of
 *		one or more parts. Actors can be animated.
 */

#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Drawable.h"

using namespace std;
using namespace Gdiplus;

class CPicture;

/**
* \brief Class for actors in our drawings.
*
* An actor is some graphical object that consists of
* one or more parts. Actors can be animated.
*/
class CActor
{
public:
	/** Constructor **/

	/** \brief Non-default constructor 
	* \param name - A string to set the actors name as */
	CActor(const wstring &name);


	/** Removal of Copy, Assignment, and original Constructor **/

	/** \brief Disable default constructor */
	CActor() = delete;

	/** \brief Delete the copy constructor*/
	CActor(const CActor &) = delete;

	/** \brief Delete the assignment operator */
	CActor &operator=(const CActor &) = delete;


	/** \brief Virtual Destructor */
	virtual ~CActor();


	/** General Functions **/

	/** \brief Draws our actor 
	* \param graphics - A graphics context (pointer) to draw upon */
	void Draw(Graphics *graphics);
	
	/** \brief A hit test for our actor
	* \param pos - A point to test
	* \return The object (CDrawable) that is hit */
	shared_ptr<CDrawable> HitTest(Point pos);

	/** \brief Adds a drawable to our actor 
	* \param drawable - The CDrawable object to add to our actor */
	void AddDrawable(shared_ptr<CDrawable> drawable);

	/** \brief Actor is enabled
	* \returns enabled status */
	bool IsEnabled() const { return mEnabled; }

	/** \brief Sets the root of our actor
	* \param root - A drawable object */
	void SetRoot(shared_ptr<CDrawable> root);


	/** Getters & Setters **/

	/** \brief Gets our actors name
	* \return String - our actors name */
	wstring GetName() const { return mName; }

	/** \brief Gets the enabled flag
	* \returns If the actor is enabled */
	bool GetEnabled() const { return mEnabled; }

	/** \brief Set Actor Enabled
	* \param enabled New enabled status */
	void SetEnabled(bool enabled) { mEnabled = enabled; }

	/** \brief Returns the position/point of our actor
	* \returns A point where our actor is located */
	Point GetPosition() const { return mPosition; }

	/** \brief Sets the position of our actor to a point
	* \param position - The point to set our actor to */
	void SetPosition(Point position) { mPosition = position; }

	/** \brief Returns if the actor is clickable or not
	* \returns boolean - Whether we can click the actor or not */
	bool GetClickable() const { return mClickable; }

	/** \brief Sets the clickable flag
	* \param flag - The boolean to set if we can click our actor */
	void SetClickable(bool flag) { mClickable = flag; }

	/** \brief Returnf our picture
	* \returns CPicture pointer to our picture */
	CPicture* GetPicture() const { return mPicture; }

	/** \brief Sets our picture
	* \param picture - The picture to set */
	void SetPicture(CPicture *picture) { mPicture = picture; }

private:
	/// Our actor's name
	wstring mName = NULL;

	/// Whether our actor is enabled
	bool mEnabled = true;

	/// Our actor's position
	Point mPosition = Point(0, 0);

	/// Whether the actor is clickable
	bool mClickable = true;


	/** Links **/

	/// Our drawable root
	shared_ptr<CDrawable> mRoot = nullptr;

	/// Our drawables in order
	vector<shared_ptr<CDrawable> > mDrawablesInOrder;

	/// Our picture
	CPicture *mPicture;

};

