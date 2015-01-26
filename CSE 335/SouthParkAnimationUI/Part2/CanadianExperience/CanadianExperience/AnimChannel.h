/**
 * \file AnimChannel.h
 *
 * \author Charles Bean
 *
 * \brief File containing the class for an Animation Channel
 *
 * Animation channels help to control the animations in our project
 */

#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Timeline.h"

using namespace std;

/** \brief Base class for animation channels
*
* This class provides basic functionality and a polymorphic
* representation for animation channels. */
class CAnimChannel
{
public:
	/** Keyframe Nested Class **/

	/** \brief Class that represents a keyframe */
	class Keyframe
	{
	public:
		/* Disabling */

		/** \brief Default constructor disabled */
		Keyframe() = delete;

		/** \brief Copy constructor disabled */
		Keyframe(const Keyframe &) = delete;

		/** \brief Assignment operator disabled */
		void operator=(const Keyframe &) = delete;


		/** General Functions **/

		/* \brief Uses the keyframe as the first keyframe in the animation channel */
		virtual void UseAs1() = 0;

		/* \brief Uses the keyframe as the second keyframe in the animation channel */
		virtual void UseAs2() = 0;

		/* \brief Uses the keyframe only */
		virtual void UseOnly() = 0;


		/** Getters & Setters **/

		/* \brief Set the frame of the keyframe 
		* \param frame - The frame to set to */
		void SetFrame(int frame) { mFrame = frame; }

		/* \brief Get the frame of the keyframe
		* \return int - The frame this keyframe has */
		int GetFrame() { return mFrame; }

	protected:
		/** \brief Constructor
		* \param channel Channel we are associated with */
		Keyframe(CAnimChannel *channel) : mChannel(channel) {}

		/// Our frame
		int mFrame;

	private:
		/// The channel this keyframe is associated with
		CAnimChannel *mChannel;
	};


	/** Constructors & Destructors **/

	/* \brief Constructor */
	CAnimChannel();

	/* \brief Destructor */
	virtual ~CAnimChannel();

	/** \brief Copy constructor disabled */
	CAnimChannel(const CAnimChannel &) = delete;

	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannel &) = delete;


	/** General Functions **/

	/** \brief Is the channel valid, meaning has keyframes?
	* \returns true if the channel is valid. */
	bool IsValid() { return mKeyframe1 >= 0 || mKeyframe2 >= 0; }

	/** \brief Deletes a keyframe from our list of keyframes 
	* \param keyframe the keyframe to be deleted */
	void DeleteKeyframe(int keyframe);


	/** Getters & Setters **/

	/* \brief Sets a keyframe
	* \param currentFrame - the frame to set */
	void SetFrame(int currentFrame);

	/* \brief Gets the name of the animation channel
	* \return wstring - the name of the channel */
	wstring GetName() { return mName; }

	/* \brief Sets the name of the animation channel
	* \param name - The (wstring) name to set the channel name to */
	void SetName(wstring name) { mName = name; }

	/* \brief Gets the timeine this channel is associated with
	* \return a pointer to the timeline */
	CTimeline* GetTimeline() { return mTimeline; }

	/* \brief Sets this channels timeline 
	* \param timeline - The timeline to set */
	void SetTimeline(CTimeline* timeline) { mTimeline = timeline; }

protected:
	/* \brief Insert a keyframe into our animation channel
	* \param keyframe - A keyframe object to insert */
	void InsertKeyframe(shared_ptr<Keyframe> keyframe);

	/* \brief Tweens - creates the movement between keyframes
	* \param t - a double representing our time */
	virtual void Tween(double t);

private:
	/// Our animation channel name
	wstring mName;

	/// Our first keyframe
	int mKeyframe1 = -1;

	/// Our second keyframe
	int mKeyframe2 = -1;

	/// The timeline object
	CTimeline *mTimeline = nullptr;

	/// Our keyframes
	vector<shared_ptr<Keyframe> > mKeyframes;
};

