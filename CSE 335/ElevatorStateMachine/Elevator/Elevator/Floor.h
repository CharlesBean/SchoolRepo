/**
 * \file Floor.h
 *
 * \author Charles Bean
 *
 * \brief The class for handling a floor
 */

#pragma once

class CController;

/**
 * \brief Represents a floor
 */
class CFloor
{
public:
	/** \brief Cosntructor */
	CFloor();

	/** \brief Destructor */
	virtual ~CFloor();


	/** Getters & Setters **/

	/** \brief Gets the up flag (true if moving up)
	* \return true if we are going up*/
	bool IsUp() { return mUp; }

	/** \brief Sets the up flag (true if moving up)
	* \param flag - The flag to set to */
	void SetUp(bool flag);

	/** \brief Gets the down flag (true if moving down)
	* \return true if we are going down*/
	bool IsDown() { return mDown; }

	/** \brief Sets the down flag (true if moving down)
	* \param flag - The flag to set to */
	void SetDown(bool flag);

	/** \brief Gets the panel flag (...)
	* \return true if we are a panel*/
	bool IsPanel() { return mPanel; }

	/** \brief Sets the panel flag (...)
	* \param flag - The flag to set to */
	void SetPanel(bool flag);

	/** \brief Gets the floor number 
	* \return int representing the floor */
	int GetFloor() { return mFloor; }

	/** \brief Sets the floor number
	* \param floor - The floor number to set to */
	void SetFloor(int floor) { mFloor = floor; }

	/** \brief Gets the controller object
	* \return a pointer to the controller */
	CController* GetController() { return mController; }

	/** \brief Sets the controller object 
	* \param controller - the controller this guy belongs to */
	void SetController(CController *controller) { mController = controller; }

private:
	bool mUp = false;			///< If we are moving up
	bool mDown = false;			///< If we are moving down
	bool mPanel = false;		///< If a panel
	int mFloor = 0;				///< The floor number
	CController *mController;   ///< Controller for this object
};

