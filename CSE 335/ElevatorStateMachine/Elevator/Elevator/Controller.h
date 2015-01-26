/**
 * \file Controller.h
 *
 * \author Charles Bean
 *
 * \brief The controller for our elevator library - it extends
 *	the libraries controller
 */

#pragma once

#include "ElevatorController.h"
#include "Floor.h"

/**
 * \brief An extended elevator controller class
 */
class CController : public CElevatorController
{
public:
	/// The state machine states
	enum States { 
		Idle, 
		DoorOpening, 
		DoorOpen, 
		DoorClosing,
		Moving,
		Stop,
		FiremanModeIdle,		// Idle in fireman mode (first floor; door open; no lights)
		FiremanModeOpening,		// The door is opening in fireman mode (first floor only)
		FiremanModeClosing,		// The door is closing in fireman mode (floor other than first only)
		FiremanModeMoving,		// The elevator is moving in fireman mode (always going down; door closed)
		FiremanModeStop		// The elevator is in firemode and stopped (first floor only; door closed)
	};

	/** \brief Constructor */
	CController();

	/** \brief Virtual Destructor */
	virtual ~CController();


	/** General Functions **/

	/** \brief Elevator service function
	*
	* This function is called once every 0.001 seconds and
	* allows us to control elevator functionality.
	*/
	virtual void Service() override;

	/** \brief Initializes the controller */
	void Initialize();


	/** Event Handlers **/

	/** \brief This function is called when the open button is pressed */
	virtual void OnOpenPressed() override;

	/** \brief This function is called when the door close button is pressed.
	*/
	virtual void OnClosePressed() override;

	/** \brief Function is called when the panel floor is pressed 
	* \param floor - The int of the floor it was pressed on */
	virtual void OnPanelFloorPressed(int floor) override;

	/** \brief Function called when the call-up elevator button is pressed 
	* \param floor - The int of the floor */
	virtual void OnCallUpPressed(int floor) override;

	/** \brief Function called when the call-down elevator button is pressed 
	* \param floor - The floor called on (int) */
	virtual void OnCallDownPressed(int floor) override;


private:
	/** \brief Set a state
	* \param state The new state to set
	*/
	void SetState(States state);

	/**
	* \brief Determine the floor to go to.
	*
	* Given the current direction we are going, determine what floor
	* we should go to.
	* \returns A floor to go to (1 to 3) or 0 if none
	*/
	int WhatFloorToGoTo();

	/**
	* \brief Determine floor to go to in the up direction.
	*
	* Assuming we are going up, determine any floor we would
	* go to in the up direction.
	* \returns Floor 1 to 3 or 0 if no floor is selected.
	*/
	int WhatFloorUp();

	/** \brief What floor to go down to
	* \return int representing the floor number */
	int WhatFloorDown();
	
	int mFloor	= 1;			///< The current floor
	States mState = Idle;		///< The current state
	double mStateTime = 0;		///< The time in a current state
	CFloor mFloors[NumFloors];	///< An object for each floor
	bool mGoingUp = true;		///< If the elevator is going up

	/** \brief Simple function to disable buttons */
	void DisableButtons();
};

