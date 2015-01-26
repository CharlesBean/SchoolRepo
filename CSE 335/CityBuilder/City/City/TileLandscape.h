/**
* \file TileLandscape.h
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
class CTileLandscape : public CTile
{
public:
	/* \brief Constructor with a city parameter
	*
	* \param city - A pointer to a city object
	*/
    CTileLandscape(CCity *city);

    /// \brief Default constructor (disabled)
    CTileLandscape() = delete;

    /// \brief Copy constructor (disabled)
    CTileLandscape(const CTileLandscape &) = delete;

    ~CTileLandscape();

	/** \brief XML save overridable function
	* \param node - A reference to a CXmlNode */
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** \brief XML load overridable function
	* \param node - A reference to a CXmlNode */
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** \brief Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitLandscape(this); }

};

