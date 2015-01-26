/**
* \file TileBuilding.h
*
* \author Charles B. Owen
*
* \brief Class that implements a Building tile
*/

#pragma once

#include "Tile.h"


/**
* \brief A Building tile
*/
class CTileBuilding : public CTile
{
public:
	/* \brief Constructor with a city parameter
	*
	* \param city - A pointer to a city object
	*/
    CTileBuilding(CCity *city);

    /// \brief Default constructor (disabled)
    CTileBuilding() = delete;

    /// \brief Copy constructor (disabled)
    CTileBuilding(const CTileBuilding &) = delete;

	/** \brief Destructor */
    ~CTileBuilding();

	/** \brief XML save overridable function 
	* \param node - A reference to a CXmlNode */
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** \brief XML load overridable function
	* \param node - A reference to a CXmlNode */
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** \brief Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitBuilding(this); }
};

