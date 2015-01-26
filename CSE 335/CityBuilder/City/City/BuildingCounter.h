/**
 * \file BuildingCounter.h
 *
 * \author Charles Bean
 *
 * \brief File for the building counter visitor class
 *
 * This file contains code for creating a building counter
 *	using a visitor pattern
 */

#pragma once

#include "TileVisitor.h"


/**
 * \brief Visitor class for counting the buildings in a city
 *
 * This visitor visits tiles and increases the count if the tile is a building
 */
class CBuildingCounter : public CTileVisitor
{
public:
	/** \brief Constructor */
	CBuildingCounter();

	/** \brief Destructor */
	virtual ~CBuildingCounter();

	/** \brief Get the number of buildings
	* \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

	/** \brief Visit a building tile - increase the count if so 
	*
	* \param building - A pointer to the building tile
	*/
	void VisitBuilding(CTileBuilding *building) { mNumBuildings++; }

private:
	/// Buildings counter
	int mNumBuildings = 0;
};

