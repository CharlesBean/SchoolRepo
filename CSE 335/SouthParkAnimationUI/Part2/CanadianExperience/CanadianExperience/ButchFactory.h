/**
 * \file ButchFactory.h
 *
 * \author Charles Bean
 *
 * \brief Class that creates a new actor - Butch 
 */

#pragma once
#include "ActorFactory.h"
#include "Actor.h"

#include <memory>

using namespace std;
using namespace Gdiplus;


/** 
* \brief Creates a new actor - Butch 
*/
class CButchFactory : public CActorFactory
{
public:
	/** \brief Constructor */
	CButchFactory();

	/** \brief Destructor */
	virtual ~CButchFactory();

	/** \brief Creates a butch
	* \return A shared-pointer to our new butch object */
	std::shared_ptr<CActor> Create();
};

