/**
 * \file AnimChannelPoint.h
 *
 * \author Charles Bean
 *
 * \brief Animation channel for points
 */

#pragma once

#include "AnimChannel.h"
#include <vector>
#include <memory>

using namespace std;
using namespace Gdiplus;

/** \brief Animation channel for points.
*/
class CAnimChannelPoint : public CAnimChannel
{
public:
	/** Keyframe Point Nested Class **/

	/* \brief A class for our keyframe point*/
	class KeyframePoint : public Keyframe
	{
	public:
		/** Constructors & Destructors **/

		/** \brief Constructor
		* \param channel The channel we are for
		* \param angle The angle for the keyframe */
		KeyframePoint(CAnimChannelPoint *channel, Point point) :
			Keyframe(channel), mChannel(channel), mPoint(point) {}

		/** \brief Default constructor disabled */
		KeyframePoint() = delete;

		/** \brief Copy constructor disabled */
		KeyframePoint(const KeyframePoint &) = delete;

		/** \brief Assignment operator disabled */
		void operator=(const KeyframePoint &) = delete;


		/** General Functions **/


		/** \brief Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** \brief Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** \brief Use this keyframe as the point */
		virtual void UseOnly() override { mChannel->mPoint = mPoint; }


		/** Getters & Setters **/

		/** \brief Get the point
		* \return Point - the point of the keyframe */
		Point GetPoint() { return mPoint; }

	private:
		/// The point
		Point mPoint = Point(0,0);

		/// The channel
		CAnimChannelPoint *mChannel;
	};


	/** Constructors & Destructors **/

	/* \brief Constructor */
	CAnimChannelPoint();

	/* \brief Destructor */
	virtual ~CAnimChannelPoint();

	/** \brief Copy constructor disabled */
	CAnimChannelPoint(const CAnimChannelPoint &) = delete;

	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannelPoint &) = delete;


	/** General Functions **/

	/* \brief Sets a keyframe
	* \param point - the point to set a keyframe with */
	void SetKeyframe(Point point);


	/** Getters & Setters **/

	/* \brief Gets the point of our angle animation channel
	* return point - The point of the channel */
	Point GetPoint() { return mPoint; }

protected:
	/* \brief Tweens - creates the movement between keyframes (OVERRIDE)
	* \param t - a double representing our time */
	virtual void Tween(double t) override;

private:
	/// Our point
	Point mPoint = Point(0,0);

	/// The first angle keyframe
	KeyframePoint *mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframePoint *mKeyframe2 = nullptr;
};

