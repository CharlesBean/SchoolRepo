/**
 * \file HaroldFactory.h
 *
 * \author Charles Bean
 *
 * \brief Factory class that builds the Harold character
 */

#pragma once

#include <memory>
#include "Actor.h"
#include "ActorFactory.h"

using namespace std;
using namespace Gdiplus;

/**
* \brief Factory class that builds the Harold character
*/
class CHaroldFactory : public CActorFactory
{
public:
	/** \brief Constructor */
	CHaroldFactory();

	/** \brief Destructor */
	virtual ~CHaroldFactory();

	/** \brief Creates a harold
	* \return A shared-pointer to our new harold object */
	std::shared_ptr<CActor> Create();
};

