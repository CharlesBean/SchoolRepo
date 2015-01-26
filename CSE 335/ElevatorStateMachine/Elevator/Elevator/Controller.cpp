/**
 * \file Controller.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "Controller.h"

/// The time the door remains open
const double DoorOpenTime = 2.0;

/// The time till the doors open once it stops at a floor
const double StopOpenTime = 1.0;

/// The floor to go to in fireman mode
const int FiremanFloor = 1;

CController::CController()
{
	for (int f = 1; f <= NumFloors; f++)
	{
		mFloors[f - 1].SetController(this);
		mFloors[f - 1].SetFloor(f);
	}
}

CController::~CController()
{
}

/** \brief Set a state
* \param state The new state to set
*/
void CController::SetState(States state)
{
	mState = state;
	mStateTime = 0;

	// Entry activities for states
	switch (mState)
	{
	case DoorOpening:
		SetDoorMotor(mFloor, 1);

		WhatFloorToGoTo();
		mFloors[mFloor - 1].SetPanel(false);
		if (mGoingUp)
		{
			mFloors[mFloor - 1].SetUp(false);
		}
		else
		{
			mFloors[mFloor - 1].SetDown(false);
		}
		break;

	case DoorClosing:
		SetDoorMotor(mFloor, -1);
		break;

	case DoorOpen:
		SetDoorMotor(mFloor, 0);
		break;

	case Idle:
		SetDoorMotor(mFloor, 0);
		break;

	case Moving:
		SetBrake(false);
		SetMotorSpeed(mGoingUp ? 1 : -1);
		break;

	case Stop:
		SetMotorSpeed(0);
		SetBrake(true);
		break;

		/** Fireman Mode **/

	case FiremanModeOpening:
		SetDoorMotor(mFloor, 1); // Open the door
		break;

	case FiremanModeIdle:
		SetDoorMotor(mFloor, 0);
		break;

	case FiremanModeClosing:
		SetDoorMotor(mFloor, -1);
		break;

	case FiremanModeMoving:
		SetBrake(false);	// Turn off the brake

		// Reverse direction if necessary (movingDown)
		if (mGoingUp)
			mGoingUp = !mGoingUp;	// Falsify

		SetMotorSpeed(-1);	// Moving down
		break;

	case FiremanModeStop:
		SetBrake(true);		// Brake
		SetMotorSpeed(0);	// Turn off motor
		break;

	default:
		break;
	}
}

/**
* \brief Determine the floor to go to.
*
* Given the current direction we are going, determine what floor
* we should go to.
* \returns A floor to go to (1 to 3) or 0 if none
*/
int CController::WhatFloorToGoTo()
{
	if (mGoingUp)
	{
		// We are going up, so try for a floor in that direction
		int floor = WhatFloorUp();
		if (floor != 0)
			return floor;

		// Guess we can't go up, so see if we need to go down
		floor = WhatFloorDown();
		if (floor != 0)
		{
			// Reverse the direction
			mGoingUp = false;
			return floor;
		}
	}
	else
	{
		// We are going down, so try for floor in that dir
		int floor = WhatFloorDown();
		if (floor != 0)
			return floor;

		// Can't go down - lets try to go up
		floor = WhatFloorUp();
		if (floor != 0)
		{
			// Change direction
			mGoingUp = true;
			return floor;
		}
	}

	return 0;
}

/**
* \brief Determine floor to go to in the up direction.
*
* Assuming we are going up, determine any floor we would
* go to in the up direction.
* \returns Floor 1 to 3 or 0 if no floor is selected.
*/
int CController::WhatFloorUp()
{
	// What floor are we currently on?
	// We stop with FloorTolerance of a floor. Suppose I am at position
	// 3.42. That's just above 3.42 - 3.28 = 0.14 above floor 2, but it's within
	// the tolerance, so we think of it as on floor 2.
	int floor = int((GetPosition() + FloorTolerance) / FloorSpacing) + 1;

	// Is there a floor to goto in the up direction that has the panel
	// or the up button pressed?
	for (int f = floor; f <= NumFloors; f++)
	{
		if (mFloors[f - 1].IsUp() || mFloors[f - 1].IsPanel())
			return f;
	}

	// Is there a floor to go to in the up direction that has the down
	// button pressed. We don't look at the current floor, though.
	for (int f = NumFloors; f > floor; f--)
	{
		if (mFloors[f - 1].IsDown())
			return f;
	}

	// If nothing, return 0;
	return 0;
}

/** \brief What floor to go down to
* \return int representing the floor number */
int CController::WhatFloorDown()
{
	// What floor are we currently on?
	// We stop with FloorTolerance of a floor. Suppose I am at position
	// 3.42. That's just above 3.42 - 3.28 = 0.14 above floor 2, but it's within
	// the tolerance, so we think of it as on floor 2.
	int floor = int((GetPosition() + FloorTolerance) / FloorSpacing) + 1;

	// Is there a floor to goto in the down direction that has the panel
	// or the down button pressed?
	for (int f = floor; f >= 1; --f)
	{
		if (mFloors[f - 1].IsDown() || mFloors[f - 1].IsPanel())
			return f;
	}

	// Is there a floor to go to in the down direction that has the up
	// button pressed. We don't look at the current floor, though.
	for (int f = 1; f < floor; f++)
	{
		if (mFloors[f - 1].IsUp())
			return f;
	}

	// If nothing, return 0;
	return 0;
}

/** \brief Elevator service function
*
* This function is called once every 0.001 seconds and
* allows us to control elevator functionality.
*/
void CController::Service()
{
	// Increment state time by 1 millisecond
	mStateTime += 0.001;

	switch (mState)
	{
	case DoorOpening:
		if (IsDoorOpen(mFloor))
		{
			SetState(DoorOpen);
		}
		break;

	case DoorClosing:
		if (IsDoorClosed(mFloor))
		{
			SetState(Idle);
		}
		break;

	case DoorOpen:
		if (IsFireMode() && mFloor == FiremanFloor)			// If the door is open, and we just entered fireman mode on the first floor
		{
			SetState(FiremanModeIdle);							// Enter fireman mode (idle) - which maintains the open door 
			DisableButtons();									// Disable any buttons
		}
		else if (IsFireMode() && mFloor != FiremanFloor)	// If door open, but we entered fireman mode on a different floor
		{
			SetState(FiremanModeClosing);						// Close the door in fireman mode
			DisableButtons();									// Disable any buttons
		}
		else
		{
			// If we have been in this state long enough
			if (mStateTime >= DoorOpenTime)
			{
				// Close the door
				SetState(DoorClosing);
			}
		}
		break;

	case Idle:
	{
		if (IsFireMode() && mFloor == FiremanFloor) 		// If we are in firemode and on the first floor
		{
			SetState(FiremanModeOpening);						// Enter fireman state (opening door)
			DisableButtons();									// Disable any buttons
		}
		else if (IsFireMode() && mFloor != FiremanFloor)	// If we are in firemode and NOT on the first floor
		{
			SetState(FiremanModeClosing);						// Enter fireman state (closing door - if door already closed, it will cycle onwards)
			DisableButtons();									// Disable any buttons
		}
		else
		{
			int floor = WhatFloorToGoTo();
			if (floor == mFloor)
			{
				// Button pressed on this floor. Open the door
				SetState(DoorOpening);
			}
			else if (floor != 0)
			{
				SetState(Moving);
			}
		}
	}
		break;

	case Moving:
	{
		if (IsFireMode())									// If we are moving and in fireman mode
		{
			SetState(FiremanModeMoving);						// Enter fireman state (moving)
			DisableButtons();									// Disable any buttons
		}
		else
		{
			int floor = WhatFloorToGoTo();
			assert(floor != 0);

			// What's the position for that floor?
			double floorPosition = (floor - 1) * FloorSpacing;
			if (fabs(GetPosition() - floorPosition) < FloorTolerance)
			{
				mFloor = floor;
				SetState(Stop);
			}
		}
	}
		break;

	case Stop:
		if (IsFireMode())	// If we are stopped and now in fireman mode
		{
			SetState(FiremanModeMoving);	// Begin moving down - fireman mode (moving)
			DisableButtons();									// Disable any buttons
		}
		else
		{
			if (mStateTime >= StopOpenTime)
			{
				SetState(DoorOpening);
			}
		}
		break;

		/** Fireman Mode **/

	case FiremanModeOpening:
		// If the door is open (will only reach this on first floor - so no need to check floor)
		if (IsDoorOpen(mFloor))
		{
			// Enter idle
			SetState(FiremanModeIdle);
		}
		break;

	case FiremanModeIdle:
		// If we are idling and firemode is turned off
		if (!IsFireMode())
		{
			// Close the door - exit fireman mode state cycle
			SetState(FiremanModeClosing);
		}
		break;

	case FiremanModeMoving:
	{
		// If we are at the correct floor (position 0)
		double floorPosition = (FiremanFloor - 1) * FloorSpacing; // 0
		if (fabs(GetPosition() - floorPosition) < FloorTolerance)
		{
			mFloor = FiremanFloor;				// Set the floor
			SetState(FiremanModeStop);			// Stop
		}
		break;
	}

	case FiremanModeStop:
		if (mStateTime >= StopOpenTime)	// If we have waited
		{
			SetState(FiremanModeOpening); // Stay in fireman mode - but open door
		}
		break;

	case FiremanModeClosing:
		// If the door is closed and we have left firemode
		if (IsDoorClosed(mFloor) && !IsFireMode())
			SetState(Idle);	// The door has been closed - we are in fireman mode still
		else if (IsDoorClosed(mFloor) && mFloor != FiremanFloor)
			SetState(FiremanModeMoving);
		break;

	default:
		break;
	}
}

/** \brief Initializes the controller */
void CController::Initialize()
{

}

/** \brief This function is called when the open button is pressed.
*/
void CController::OnOpenPressed()
{
	if (!IsFireMode())
	{
		switch (mState)
		{
		case Idle:
			// Transition to the DoorOpening state
			SetState(DoorOpening);
			break;

		case DoorOpen:
			SetState(DoorOpen);
			break;

		case DoorClosing:
			SetState(DoorOpening);
			break;

		default:
			break;
		}
	}
}

/** \brief This function is called when the door close button is pressed.
*/
void CController::OnClosePressed()
{
	if (!IsFireMode())
	{
		switch (mState)
		{
		case DoorOpen:
			SetState(DoorClosing);
			break;

		case DoorOpening:
			SetState(DoorClosing);
			break;

		default:
			break;
		}
	}
}

/** \brief Function is called when the panel floor is pressed
* \param floor - The int of the floor it was pressed on */
void CController::OnPanelFloorPressed(int floor)
{
	if (!IsFireMode())
		mFloors[floor - 1].SetPanel(true);
}

/** \brief Function called when the call-up elevator button is pressed
* \param floor - The int of the floor */
void CController::OnCallUpPressed(int floor)
{
	if (!IsFireMode())
		mFloors[floor - 1].SetUp(true);
}

/** \brief Function called when the call-down elevator button is pressed
* \param floor - The floor called on (int) */
void CController::OnCallDownPressed(int floor)
{
	if (!IsFireMode())
		mFloors[floor - 1].SetDown(true);
}

void CController::DisableButtons()
{
	// TODO FIX??

	// For each floor
	for (int f = 1; f <= NumFloors; f++)
	{
		// Disable all call lights
		mFloors[f - 1].SetUp(false);
		mFloors[f - 1].SetDown(false);
		mFloors[f - 1].SetPanel(false);
	}
}