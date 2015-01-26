/**
 * \file Picture.h
 *
 * \author Charles Bean
 *
 * \brief There will be one picture object that contains all of
 *		our actors, which then contains the drawables.
 */

#pragma once

#include <vector>
#include "PictureObserver.h"
#include "Actor.h"
#include "Timeline.h"

using namespace Gdiplus;

/**
* \brief The picture we are drawing.
*
* There will be one picture object that contains all of
* our actors, which then contains the drawables.
*/
class CPicture
{
public:
	/** Iterator **/

	/** \brief Iterator for iteration over actors in our picture */
	class Iter
	{
	public:
		/** \brief Constructor for iterator
		* \param actors - The actors we are iterating over 
		* \param pos - The position of our iterator */
		Iter(vector<shared_ptr<CActor> > actors, int pos) : mActorCollection(actors), mPos(pos) {}

		/** \brief Tests for the end of the iterator 
		* \returns True if the current position is not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			// Return whether they are equal
			return mPos != other.mPos;
		}

		/** \brief Gets a value
		* \returns Value at mPos in the collection */
		std::shared_ptr<CActor> operator *() const { return mActorCollection[mPos]; }

		/** \brief Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			// Increase the position
			mPos++;

			// Return pointer to the tile
			return *this;
		}

	private:
		int mPos;	///< Our position in the collection
		vector<shared_ptr<CActor> > mActorCollection;	///< Our actors 

	};


	/** Iterator Implementation **/

	/** \brief Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(mActors, 0); }

	/** \brief Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(mActors, mActors.size()); }


	/** Constructor & Destructor **/

	/// \brief Constructor
	CPicture();

	/// \brief Virtual destructor
	virtual ~CPicture();


	/** Disabling **/

	/// \brief Copy Constructor (Disabled)
	CPicture(const CPicture &) = delete;

	/// \brief Assignment Operator (Disabled)
	CPicture &operator=(const CPicture &) = delete;


	/** General Functions **/

	/** \brief The picture size
	* \returns Size */
	Gdiplus::Size GetSize() { return mSize; }

	/** \brief The picture size
	* \param size The new picture size */
	void SetSize(Gdiplus::Size size) { mSize = size; }

	/** \brief Adds an observer to this picture
	* \param observer - The observer to add */
	void AddObserver(CPictureObserver *observer);

	/** \brief Removes an observer to this picture
	* \param observer - The observer to remove */
	void RemoveObserver(CPictureObserver *observer);

	/** \brief Calls the update functions in each of the existing observers
	*			to tell the observers about what has changed in the picture */
	void UpdateObservers();

	/** \brief Draws the picture with GDI 
	* \param grahpics - The device context to draw on */
	void Draw(Gdiplus::Graphics *graphics);

	/** \brief Creates the association between a picture and adds an actor
	* \param actor - The actor to add */
	void AddActor(shared_ptr<CActor> actor);

	/** \brief Set the current animation time
	*
	* This forces the animation of all
	* objects to the current animation location.
	* \param time The new time.
	*/
	void SetAnimationTime(double time);

	/** Getters & Setters **/

	/** \brief Get a pointer to the Timeline object
	* \returns Pointer to the Timeline object
	*/
	CTimeline *GetTimeline() { return &mTimeline; }

private:
	/// The picture size
	Gdiplus::Size mSize = Gdiplus::Size(800, 600);

	/// The observers of this picture
	vector<CPictureObserver *> mObservers;

	/// The actors in this picture 
	vector<shared_ptr<CActor> > mActors;

	/// The animation timeline
	CTimeline mTimeline;
};

