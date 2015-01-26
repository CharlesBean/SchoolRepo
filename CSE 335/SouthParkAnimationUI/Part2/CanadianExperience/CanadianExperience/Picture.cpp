/**
 * \file Picture.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "Picture.h"

/** \brief Constructor */
CPicture::CPicture()
{
}

/** \brief Destructor */
CPicture::~CPicture()
{
}

/** \brief Add an observer to this picture.
* \param observer The observer to add
*/
void CPicture::AddObserver(CPictureObserver *observer)
{
	mObservers.push_back(observer);
}

/** \brief Remove an observer from this picture
* \param observer The observer to remove
*/
void CPicture::RemoveObserver(CPictureObserver *observer)
{
	auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
	if (loc != std::end(mObservers))
	{
		mObservers.erase(loc);
	}
}

/** \brief Update all observers to indicate the picture has changed.
*/
void CPicture::UpdateObservers()
{
	for (auto observer : mObservers)
	{
		observer->UpdateObserver();
	}
}

/** \brief Draws our picture 
* \param graphics - Our graphics context */
void CPicture::Draw(Gdiplus::Graphics *graphics)
{
	for (auto actor : mActors)
	{
		actor->Draw(graphics);
	}
}

/** \brief Adds and actor to our picture 
* \param actor - The actor to add (create link) */
void CPicture::AddActor(shared_ptr<CActor> actor)
{
	mActors.push_back(actor);
	actor->SetPicture(this);
}

/** \brief Set the current animation time
*
* This forces the animation of all
* objects to the current animation location.
* \param time The new time.
*/
void CPicture::SetAnimationTime(double time)
{
	mTimeline.SetCurrentTime(time);
	UpdateObservers();

	for (auto actor : mActors)
	{
		actor->GetKeyframe();
	}
}

