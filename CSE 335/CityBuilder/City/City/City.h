/**
 * \file City.h
 *
 * \author Charles B. Owen
 *
 * \brief Class that implements a simple city with tiles we can manipulate
 */

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <utility>

#include "XmlNode.h"
#include "Tile.h"

/**
 * \brief Implements a simple city with tiles we can manipulate
 */
class CCity
{
public:
	/// \brief Constructor
    CCity();

	/// \brief Destructor
    virtual ~CCity();

    /// The spacing between grid locations
    static const int GridSpacing = 32;

	/** \brief Add the item to the city 
	* \param item - An item to add */
    void Add(std::shared_ptr<CTile> item);

	/** \brief Test if the tile is hit 
	* \param x - The X coordinate
	* \param y - The Y coordinate
	*/
    std::shared_ptr<CTile> HitTest(int x, int y);

	/** \brief Move the item to the front of the screen
	* \param item - An item to move */
    void MoveToFront(std::shared_ptr<CTile> item);

	/** \brief Delete an item from the city
	* \param item - An item to delete */
    void DeleteItem(std::shared_ptr<CTile> item);

	/** \brief Draw graphics
	* \param graphics - The graphics to draw */
    void OnDraw(Gdiplus::Graphics *graphics);

	/** \brief Save the city to a file 
	* \param filename - The filename */
    void Save(const std::wstring &filename);

	/** \brief Load a city from a file
	* \param filename - The filename to load from */
    void Load(const std::wstring &filename);

	/** brief Clear the city of all items */
    void Clear();

	/** \brief Update the city
	* \param elapsed - The time elapsed since last update */
    void Update(double elapsed);

	/** \brief Sort the tiles */
    void SortTiles();

	/** \brief Gets the adjacent tile 
	* \param tile - The tile
	* \param dx - The x coordinate
	* \param dy - The y coordinate
	*/
    std::shared_ptr<CTile> GetAdjacent(std::shared_ptr<CTile> tile, int dx, int dy);

	/** \brief Gets the adjacent tile (pointer)
	* \param tile - The pointer to the tile
	* \param dx - The x coordinate
	* \param dy - The y coordinate
	*/
    std::shared_ptr<CTile> GetAdjacent(CTile *tile, int dx, int dy);


	/** \brief Iterator that iterates over the city tiles */
	class Iter
	{
	public:
		/** \brief Constructor
		* \param city The city we are iterating over */
		Iter(CCity *city, int pos) : mCity(city), mPos(pos) {}

		/** \brief Test for end of the iterator
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			// Return whether the position is equal to the other tile's position
			return mPos != other.mPos;
		}

		/** \brief Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTile> operator *() const { return mCity->mTiles[mPos]; }

		/** \brief Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			// Increase the position
			mPos++;

			// Return pointer to the tile
			return *this;
		}


	private:
		CCity *mCity;   ///< City we are iterating over
		int mPos;       ///< Position in the collection
	};

	/** \brief Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** \brief Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mTiles.size()); }

	/** \brief Iterator that iterates over tiles of a certain zone */
	class ZoningIter
	{
	public:
		/** \brief Constructor
		* \param city The city we are iterating over 
		* \param pos The position of the iterator 
		*/
		ZoningIter(CCity *city, int pos, CTile::Zonings zoning) : mCity(city), mPos(pos), mZoning(zoning) {}

		/** \brief Test for end of the iterator
		* \returns True if this position is not equal to the other position */
		bool operator!=(const ZoningIter &other) const
		{
			return mPos != other.mPos;
		}

		/** \brief Operator overload of the asterix
		* \return The position of the iterator */
		std::shared_ptr<CTile> operator *() const { return mCity->mTiles[mPos]; }

		/** \brief Incrementing overload 
		* \return A pointer to the tile with a new position */
		const ZoningIter& operator++()
		{
			// Increment the iterator
			mPos++;

			// For each tile (starting with the current one)
			for (unsigned i = mPos; i < mCity->mTiles.size(); i++)
			{
				// If the tile has the correct zone
				if (mCity->mTiles[i]->GetZoning() == mZoning)
				{
					// Move the position
					mPos = i;

					// Return a pointer to the tile
					return *this;
				}
			}
		}

	private:
		int mPos;		///< The position of the iterator in the collection
		CCity *mCity;	///< Selected city
		CTile::Zonings mZoning;	///< Desired zoning type

	};


	/** \brief A class we return to support iterating over
	* only specific zonings in the collection */
	class ZoningIterSupport
	{
	public:
		/** \brief Constructor
		* \param city The city we are iteratoring over
		* \param zoning The zoning we are interested in */
		ZoningIterSupport(CCity *city, CTile::Zonings zoning) : mCity(city), mZoning(zoning) {}

		/** \brief Get an iterator for the beginning of the collection
		* \returns Iter object at position 0 */
		ZoningIter begin()
		{
			// If there are tiles
			if (mCity->mTiles.size() > 0)
			{
				// Iterate over the tiles
				for (unsigned i = 0; i < mCity->mTiles.size(); i++)
				{
					// If a tile is of the desired type
					if (mCity->mTiles[i]->GetZoning() == mZoning)
					{
						// Return the iterator location (beginning) to it and break
						return ZoningIter(mCity, i, mZoning);
					}
				}
			}

			// If there aren't any tiles
			else
			{
				// Return pointer to 0th index
				return ZoningIter(mCity, 0, mZoning);
			}
		}

		/** \brief Get an iterator for the end of the collection
		* \returns Iter object at position past the end */
		ZoningIter end() 
		{
			// If there are tiles
			if (mCity->mTiles.size() > 0)
			{
				// Backwards iteration
				for (unsigned i = mCity->mTiles.size(); i-- > 0;)
				{
					// If a tile is of the desired type
					if (mCity->mTiles[i]->GetZoning() == mZoning)
					{
						// Return the iterator location (end) to it (plus 1) and break
						return ZoningIter(mCity, i + 1, mZoning);
					}
				}
			}

			// If there aren't any tiles
			else
			{
				// Endpoint
				int endPoint = mCity->mTiles.size();

				// Return pointer to 0th index
				return ZoningIter(mCity, endPoint, mZoning);
			}
		}

	private:
		CCity *mCity; ///< The instantiation of a pointer to the city 
		CTile::Zonings mZoning; ///< Our desired zoning
	};

	/** \brief Get a zoning iterator support object
	* \param zoning The zoning we are interested in
	* \returns ZoningIterSupport object
	*/
	ZoningIterSupport GetZoning(CTile::Zonings zoning) { return ZoningIterSupport(this, zoning); }

	/** \brief Accept a visitor for the collection
	* \param visitor The visitor for the collection
	*/
	void Accept(CTileVisitor *visitor);


private:
	/// The XmlTile 
    void XmlTile(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/// Build the adjacent tiles
    void BuildAdjacencies();

    /// All of the tiles that make up our city
    std::vector<std::shared_ptr<CTile> > mTiles;

    /// Adjacency lookup support
    std::map<std::pair<int, int>, std::shared_ptr<CTile> > mAdjacency;
};

