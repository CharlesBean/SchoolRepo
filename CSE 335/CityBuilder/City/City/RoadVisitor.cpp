/**
 * \file RoadVisitor.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "RoadVisitor.h"


CRoadVisitor::CRoadVisitor()
{
}


CRoadVisitor::~CRoadVisitor()
{
}

/** \brief Function for visiting a road 
* param road - The road to visit
*/
void CRoadVisitor::VisitRoad(CTileRoad *road)
{
	// Creating the booleans for marking if the adjacent tiles are roads
	bool ulIsRoad = false, urIsRoad = false, llIsRoad = false, lrIsRoad = false;

	// Get adjacent tiles
	auto ulTile = road->GetAdjacent(-1, -1);
	auto urTile = road->GetAdjacent(1, -1);
	auto llTile = road->GetAdjacent(-1, 1);
	auto lrTile = road->GetAdjacent(1, 1);

	// Upper left tile check
	if (ulTile != nullptr)
	{
		// Create IsRoad visitor to check if upper left tile is a road
		CIsRoadVisitor ulVisitor;

		// Have tile accept the visitor
		ulTile->Accept(&ulVisitor);

		// Have visitor check if the tile is a road
		ulIsRoad = ulVisitor.IsRoad();
	}

	// Upper right tile check
	if (urTile != nullptr)
	{
		// Create IsRoad visitor to check if upper right tile is a road
		CIsRoadVisitor urVisitor;

		// Have tile accept the visitor
		urTile->Accept(&urVisitor);

		// Have visitor check if the tile is a road
		urIsRoad = urVisitor.IsRoad();
	}

	// Lower left tile check
	if (llTile != nullptr)
	{
		// Create IsRoad visitor to check if lower left tile is a road
		CIsRoadVisitor llVisitor;

		// Have tile accept the visitor
		llTile->Accept(&llVisitor);

		// Have visitor check if the tile is a road
		llIsRoad = llVisitor.IsRoad();
	}

	// Lower right tile check
	if (lrTile != nullptr)
	{
		// Create IsRoad visitor to check if lower right tile is a road
		CIsRoadVisitor lrVisitor;

		// Have tile accept the visitor
		lrTile->Accept(&lrVisitor);

		// Have visitor check if the tile is a road
		lrIsRoad = lrVisitor.IsRoad();
	}

	// Fix the roads
	road->SetAdjacencies(ulIsRoad, urIsRoad, llIsRoad, lrIsRoad);
}
