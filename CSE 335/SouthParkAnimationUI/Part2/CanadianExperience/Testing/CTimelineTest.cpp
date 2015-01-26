#include "stdafx.h"
#include "CppUnitTest.h"

#include "Timeline.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
	{
	public:
		
		TEST_METHOD(TestCTimelineNumFrames)
		{
			// Create timeline
			CTimeline timeline;

			// Init check
			Assert::AreEqual((int)300, timeline.GetNumFrames());

			// Getter & Setter check
			timeline.SetNumFrames((int)700);

			Assert::AreEqual((int)700, timeline.GetNumFrames());
		}

		TEST_METHOD(TestCTimelineFrameRate)
		{
			CTimeline timeline;

			// Init check
			Assert::AreEqual((int)30, timeline.GetFrameRate());

			// Getter & Setter Checking
			timeline.SetFrameRate(60);

			Assert::AreEqual((int)60, timeline.GetFrameRate());
		}

		TEST_METHOD(TestCTimelineCurrentTime)
		{
			CTimeline timeline;

			// Init check
			Assert::AreEqual((double)0, timeline.GetCurrentTime());

			// Setter
			timeline.SetCurrentTime((double)9.27);

			// Getter
			Assert::AreEqual((double)9.27, timeline.GetCurrentTime());
		}

		TEST_METHOD(TestCTimelineGetDuration)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(10, timeline.GetDuration(), 0.0001);

			// Changed duration
			timeline.SetFrameRate(375);
			Assert::AreEqual(300.0 / 375.0, timeline.GetDuration(), 0.0001);

			timeline.SetNumFrames(789);
			Assert::AreEqual(789.0 / 375.0, timeline.GetDuration(), 0.0001);
		}

		TEST_METHOD(TestCTimelineGetCurrentFrame)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(0, timeline.GetCurrentFrame());

			// Changed time
			timeline.SetCurrentTime(9.27);
			Assert::AreEqual(278, timeline.GetCurrentFrame());
		}
	};
}