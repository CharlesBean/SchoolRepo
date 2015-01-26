/**
 * \file Timeline.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "Timeline.h"
#include "AnimChannel.h"


CTimeline::CTimeline()
{
}


CTimeline::~CTimeline()
{
}

/* \brief Adds a channel to the timeline (two-way)
* \param animChannel - the channel to add */
void CTimeline::AddChannel(CAnimChannel *animChannel)
{
	mChannels.push_back(animChannel);
	animChannel->SetTimeline(this);
}

/** \brief Sets the current time
*
* Ensures all of the channels are
* valid for that point in time.
*/
void CTimeline::SetCurrentTime(double t)
{
	// Set the time
	mCurrentTime = t;

	for (auto channel : mChannels)
	{
		channel->SetFrame(GetCurrentFrame());
	}
}

/** \brief Delete any keyframe we are over */
void CTimeline::DeleteKeyframe()
{
	// For all keyframes
	for (auto keyframe : mChannels)
	{
		// Delete if it is the current channel
		keyframe->DeleteKeyframe(GetCurrentFrame());
	}
}