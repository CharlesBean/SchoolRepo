/**
 * \file PictureFactory.h
 *
 * \author Charles Bean
 *
 * \brief The class that holds code for a picture factory
 */

#pragma once

#include <memory>

#include "Picture.h"

using namespace std;

/**
* \brief A factory class that builds our picture.
*/
class CPictureFactory
{
public:
	/** \brief Constructor*/
	CPictureFactory();

	/** \brief Destructor */
	virtual ~CPictureFactory();


	/** \brief Factory method to create a new picture.
	* \return The created picture */
	shared_ptr<CPicture> CPictureFactory::Create();

};
