/**
 * \file Floor.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "Floor.h"
#include "ElevatorController.h"
#include "Controller.h"


CFloor::CFloor()
{
}


CFloor::~CFloor()
{
}


/** \brief Sets the up flag (true if moving up)
* \param flag - The flag to set to */
void CFloor::SetUp(bool flag) 
{
	mUp = flag;
	mController->SetCallLight(mFloor, CElevatorController::Up, mUp);
}

/** \brief Set the value of Panel for a floor.
* \param flag - The new value for mPanel
*/
void CFloor::SetDown(bool flag)
{
	mDown = flag;
	mController->SetCallLight(mFloor, CElevatorController::Down, mDown);
}

/** \brief Set the value of Panel for a floor.
* \param flag The new value for mPanel
*/
void CFloor::SetPanel(bool flag)
{
	mPanel = flag;
	mController->SetPanelFloorLight(mFloor, mPanel);
}