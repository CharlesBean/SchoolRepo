/**
 * \file RoadVisitor.h
 *
 * \author Charles Bean
 *
 * \brief File containing code for a road
 *			visitor class
 *
 * Uses a visitor pattern to visit roads in the city
 */

#pragma once

#include "TileVisitor.h"
#include "IsRoadVisitor.h"
#include "Tile.h"
#include "TileRoad.h"


/**
 * \brief A class for visiting the roads in a city 
 *			using the visitor pattern
 *
 * This class uses a visitor pattern to visit roads
 */
class CRoadVisitor : public CTileVisitor
{
public:
	/** \brief Constructor */
	CRoadVisitor();

	/** \brief Destructor */
	virtual ~CRoadVisitor();

	/** \brief Function for visiting a road (must be accepted) 
	*
	* \param road - A pointer to the road tile
	*/
	virtual void VisitRoad(CTileRoad *road) override;
};

