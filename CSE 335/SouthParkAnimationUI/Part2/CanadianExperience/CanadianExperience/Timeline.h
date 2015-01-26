/**
 * \file Timeline.h
 *
 * \author Charles Bean
 *
 * \brief The file containing a Timeline class - which
 *			represents our timeline for creating keyframes
 *
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */

#pragma once

#include <vector>

using namespace std;

/// Forward Reference
class CAnimChannel;


/** \brief This class implements a timeline that manages the animation
*
* A timeline consists of animation channels for different parts of our
* actors, each with keyframes that set the position, orientation, etc
* at that point in time. */
class CTimeline
{
public:
	/** Constructors & Destructors **/

	/** \brief Constructor */
	CTimeline();

	/** \brief Copy constructor disabled */
	CTimeline(const CTimeline &) = delete;

	/** \brief Assignment operator disabled */
	void operator=(const CTimeline &) = delete;

	/** \brief Destructor */
	virtual ~CTimeline();


	/** General Functions **/

	/*! \brief Get the current frame.
	*
	* This is the frame associated with the current time
	* \returns Current frame
	*/
	int GetCurrentFrame() const { return (int)(mCurrentTime * mFrameRate); }

	/*! \brief Get the animation duration
	* \returns Animation duration in seconds
	*/
	double GetDuration() const { return ((double)mNumFrames / (double)mFrameRate); }

	/** \brief Adds a new channel to our timeline
	* \param animChannel - Our animation channel to add */
	void AddChannel(CAnimChannel *animChannel);


	/** Getters & Setters **/

	/** \brief Get the number of frames in the animation
	* \returns Number of frames in the animation
	*/
	int GetNumFrames() const { return mNumFrames; }

	/** \brief Set the number of frames in the animation
	* \param numFrames Number of frames in the animation
	*/
	void SetNumFrames(int numFrames) { mNumFrames = numFrames; }

	/** \brief Get the frame rate
	* \returns Animation frame rate in frames per second
	*/
	int GetFrameRate() const { return mFrameRate; }

	/** \brief Set the frame rate
	* \param frameRate Animation frame rate in frames per second
	*/
	void SetFrameRate(int frameRate) { mFrameRate = frameRate; }

	/** \brief Get the current time
	* \returns Current animation time in seconds
	*/
	double GetCurrentTime() const { return mCurrentTime; }

	/** \brief Set the current time
	* \param currentTime new current animation time in seconds
	*/
	void SetCurrentTime(double currentTime);

	/** \brief Delete any keyframe we are over */
	void DeleteKeyframe();

private:
	/// Our timeline's number of frames
	int mNumFrames = 300;
	
	/// The desired framerate
	int mFrameRate = 30;

	/// The current time
	double mCurrentTime = 0;

	/// Our animation channels
	vector<CAnimChannel *> mChannels;
};

