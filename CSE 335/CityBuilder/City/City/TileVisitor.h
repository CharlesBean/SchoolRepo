/**
* \file TileVisitor.h
*
* \author Charles Bean
*
* \brief Tile visitor base class.
*/


#pragma once

// Forward references to all tile types
class CTileBuilding;
class CTileCoalmine;
class CTileLandscape;
class CTileRoad;

/** \brief Tile visitor base class */
class CTileVisitor
{
public:
	/** \brief Constructor */
	CTileVisitor();

	/** \brief Destructor */
	virtual ~CTileVisitor();

	/** \brief Visit a CTileBuilding object
	* \param building Building we are visiting */
	virtual void VisitBuilding(CTileBuilding *building) {}

	/** \brief Visit a CTileCoalmine object
	* \param coalmine Coal mine we are visiting */
	virtual void VisitCoalmine(CTileCoalmine *coalmine) {}

	/** \brief Visit a CTileLandscape object
	* \param landscape Landscape tile we are visiting */
	virtual void VisitLandscape(CTileLandscape *landscape) {}

	/** \brief Visit a CTileRoad object
	* \param road Road we are visiting */
	virtual void VisitRoad(CTileRoad *road) {}
};