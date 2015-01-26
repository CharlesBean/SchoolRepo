/**
* \file TileRoad.h
*
* \author Charles B. Owen
*
* \brief Class that implements a Road tile
*/

#pragma once

#include "Tile.h"


/**
* \brief A Road tile
*/
class CTileRoad : public CTile
{
public:
	/* \brief Constructor with a city parameter
	*
	* \param city - A pointer to a city object
	*/
    CTileRoad(CCity *city);

    /// \brief Default constructor (disabled)
    CTileRoad() = delete;

    /// \brief Copy constructor (disabled)
    CTileRoad(const CTileRoad &) = delete;

    ~CTileRoad();

	/** \brief XML save overridable function
	* \param node - A reference to a CXmlNode */
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** \brief Sets the adjacent tiles for the selected road 
	*
	* If a parameter is true, it means that tile is a road
	*
	* \param ul - Upper left tile is Road
	* \param ur - Upper right tile is Road
	* \param ll - Lower left tile is Road
	* \param lr - Lower right tile is Road
	*/
    void SetAdjacencies(bool ul, bool ur, bool ll, bool lr);

	/** \brief Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitRoad(this); }

private:
    /// The current adjacency integer or -1 if none
    int mCurrentAdj = -1;
};

