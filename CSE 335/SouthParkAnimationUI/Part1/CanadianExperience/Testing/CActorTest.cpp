#include "stdafx.h"
#include "CppUnitTest.h"

#include "Actor.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CActorTest)
	{
	public:
		
		TEST_METHOD(TestCActorConstructor)
		{
			// Constructor (name)
			CActor actor(L"Harold");

			Assert::AreEqual(std::wstring(L"Harold"), actor.GetName());
		}

		TEST_METHOD(TestCActorEnabled)
		{
			CActor actor(L"Tommy");

			// Default
			Assert::IsTrue(actor.GetEnabled());

			// Getter and setter
			actor.SetEnabled(false);

			// Getter after setting
			Assert::IsFalse(actor.GetEnabled());
		}

		TEST_METHOD(TestCActorClickable)
		{
			CActor actor(L"Bill");

			// Default
			Assert::IsTrue(actor.GetClickable());

			// Getter and setter
			actor.SetClickable(false);

			// Getter after setting
			Assert::IsFalse(actor.GetClickable());
		}

		TEST_METHOD(TestCActorPosition)
		{
			CActor actor(L"Harold");

			// Default
			Assert::AreEqual(0, actor.GetPosition().X);
			Assert::AreEqual(0, actor.GetPosition().Y);

			actor.SetPosition(Point(10, 11));

			// After setting test
			Assert::AreEqual(10, actor.GetPosition().X);
			Assert::AreEqual(11, actor.GetPosition().Y);
		}

	};
}