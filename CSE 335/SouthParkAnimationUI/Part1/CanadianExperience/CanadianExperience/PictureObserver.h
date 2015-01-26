/**
 * \file PictureObserver.h
 *
 * \author Charles Bean
 *
 * \brief This class implements the base class functionality for
 *		an observer in the observer pattern.
 */

#pragma once

#include <memory>

class CPicture;

/**
* \brief Observer base class for a picture.
*
* This class implements the base class functionality for
* an observer in the observer pattern.
*/
class CPictureObserver
{
public:
	/// \brief Virtual destructor
	virtual ~CPictureObserver();

	//! \brief Copy Constructor (Disabled)
	CPictureObserver(const CPictureObserver &) = delete;

	//! \brief Assignment Operator (Disabled)
	CPictureObserver &operator=(const CPictureObserver &) = delete;

	/// \brief This function is called to update any observers
	virtual void UpdateObserver() = 0;

	/// \brief Gets the picture we are observing
	std::shared_ptr<CPicture> GetPicture() { return mPicture; }

	/// Sets the picture we are observing
	void SetPicture(std::shared_ptr<CPicture> picture);

protected:
	/// \brief Constructor
	CPictureObserver();

private:
	/// Picture we are observing
	std::shared_ptr<CPicture> mPicture;
};

