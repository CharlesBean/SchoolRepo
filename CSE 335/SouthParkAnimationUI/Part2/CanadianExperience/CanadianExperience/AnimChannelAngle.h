/**
 * \file AnimChannelAngle.h
 *
 * \author Charles Bean
 *
 * \brief A file containing a class for animation angle channels
 */

#pragma once

#include "AnimChannel.h"

/** \brief Animation channel for angles.
*/
class CAnimChannelAngle : public CAnimChannel
{
public:
	/** Keyframe Angle Nested Class **/

	/* \brief A class for our keyframe angle */
	class KeyframeAngle : public Keyframe
	{
	public:
		/** Constructors & Destructors **/

		/** \brief Constructor
		* \param channel The channel we are for
		* \param angle The angle for the keyframe */
		KeyframeAngle(CAnimChannelAngle *channel, double angle) :
			Keyframe(channel), mChannel(channel), mAngle(angle) {}

		/** \brief Default constructor disabled */
		KeyframeAngle() = delete;

		/** \brief Copy constructor disabled */
		KeyframeAngle(const KeyframeAngle &) = delete;

		/** \brief Assignment operator disabled */
		void operator=(const KeyframeAngle &) = delete;


		/** General Functions **/

		/** \brief Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** \brief Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** \brief Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mAngle = mAngle; }


		/** Getters & Setters **/

		/* \brief Get the angle 
		* \return double - the angle of the angle keyframe */
		double GetAngle() { return mAngle; }

	private:
		/// The angle
		double mAngle;

		/// The channel this keyframe is associated with
		CAnimChannelAngle *mChannel;
	};


	/** Constructors & Destructors **/

	/* \brief Constructor */
	CAnimChannelAngle();

	/* \brief Destructor */
	virtual ~CAnimChannelAngle();

	/** \brief Copy constructor disabled */
	CAnimChannelAngle(const CAnimChannelAngle &) = delete;

	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannelAngle &) = delete;


	/** General Functions **/

	/* \brief Sets a keyframe
	* \param angle - the angle to set a keyframe with */
	void SetKeyframe(double angle);


	/** Getters & Setters **/
	
	/* \brief Gets the angle of our angle animation channel
	* return double - The angle of the channel */
	double GetAngle() { return mAngle; }

protected:
	/* \brief Tweens - creates the movement between keyframes (OVERRIDE)
	* \param t - a double representing our time */
	virtual void Tween(double t) override;

private:
	/// Our angle
	double mAngle = 0;

	/// The first angle keyframe
	KeyframeAngle *mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframeAngle *mKeyframe2 = nullptr;
};

