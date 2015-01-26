/**
 * \file PictureObserver.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "PictureObserver.h"

#include "Picture.h"


/** \brief Constructor */
CPictureObserver::CPictureObserver()
{
}

/** \brief Destructor */
CPictureObserver::~CPictureObserver()
{
	if (mPicture != nullptr)
	{
		mPicture->RemoveObserver(this);
	}
}

/** \brief Set the picture for this observer
* \param picture The picture to set */
void CPictureObserver::SetPicture(std::shared_ptr<CPicture> picture)
{
	mPicture = picture;
	mPicture->AddObserver(this);
}
