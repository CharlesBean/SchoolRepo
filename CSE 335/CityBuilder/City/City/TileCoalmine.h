/**
* \file TileCoalmine.h
*
* \author Charles B. Owen
*
* \brief Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"


/**
* \brief A Landscape tile
*/
class CTileCoalmine : public CTile
{
public:
	/* \brief Constructor with a city parameter
	*
	* \param city - A pointer to a city object
	*/
    CTileCoalmine(CCity *city);

    /// \brief Default constructor (disabled)
    CTileCoalmine() = delete;

    /// \brief Copy constructor (disabled)
    CTileCoalmine(const CTileCoalmine &) = delete;

    ~CTileCoalmine();

	/** \brief XML save overridable function
	* \param node - A reference to a CXmlNode */
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** \brief Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitCoalmine(this); }
};

