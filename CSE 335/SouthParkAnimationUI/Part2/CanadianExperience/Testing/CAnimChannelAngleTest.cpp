#include "stdafx.h"
#include "CppUnitTest.h"

#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CAnimChannelpointTest)
	{
	public:
		
		// Test if the getter and setter work
		TEST_METHOD(CAnimChannelpointGetterAndSetter)
		{
			// Create channel
			CAnimChannelAngle animAngleChannel;

			// Test name
			wstring testName = L"Tom";

			// Setter test
			animAngleChannel.SetName(testName);

			// Getter test
			Assert::AreEqual(testName, animAngleChannel.GetName());
		}

	};
}