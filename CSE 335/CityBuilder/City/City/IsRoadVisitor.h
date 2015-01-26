/**
 * \file IsRoadVisitor.h
 *
 * \author Charles Bean
 *
 * \brief This file contains the code for a visitor
 *	that checks to see if a tile is a road
 *
 *	The tile has to accept this road visitor in order
 *	for the road to be checked
 */

#pragma once

#include "TileVisitor.h"

/** \brief The visitor class for checking if a tile
*			is a road
*
* This class uses a visitor pattern to check if a tile
*	is of the type Road
*/
class CIsRoadVisitor : public CTileVisitor
{
public:
	/** \brief Constructor */
	CIsRoadVisitor();

	/** \brief Destructor */
	virtual ~CIsRoadVisitor();

	/** \brief Visits a road
	*
	* \param road - A pointer to the Road Tile
	*/
	virtual void VisitRoad(CTileRoad *road) override { mIsRoad = true; }
	
	/** \brief The getter for retrieving the boolean mIsRoad
	*
	* True if a road
	*/
	bool IsRoad() const { return mIsRoad; }

private:
	/// Boolean for determining if a tile is a road
	bool mIsRoad = false;
};