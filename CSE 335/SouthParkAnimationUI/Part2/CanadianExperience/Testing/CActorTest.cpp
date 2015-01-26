#include "stdafx.h"
#include "CppUnitTest.h"

#include "Actor.h"
#include <string>
#include "PolyDrawable.h"
#include "Picture.h"
#include <memory>

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

		TEST_METHOD(TestCActorSetPicture)
		{
			// Create a picture object
			auto picture = make_shared<CPicture>();

			// Create an actor and add it to the picture
			auto actor = make_shared<CActor>(L"Actor");

			// Create a drawable for the actor
			auto drawable = make_shared<CPolyDrawable>(L"Drawable");
			actor->SetRoot(drawable);
			actor->AddDrawable(drawable);

			picture->AddActor(actor);

			auto channel = drawable->GetAngleChannel();
			Assert::IsTrue(channel->GetTimeline() == picture->GetTimeline());
		}

		/** This tests that the animation of the position of an actor works */
		TEST_METHOD(TestCActorAnimation)
		{
			// Create a picture object
			auto picture = make_shared<CPicture>();

			// Create an actor and add it to the picture
			auto actor = make_shared<CActor>(L"Actor");
			picture->AddActor(actor);

			auto channel = actor->GetPositionChannel();

			// First we will ensure it works with no keyframes set
			picture->SetAnimationTime(0);
			actor->SetPosition(Point(1234, 9833));

			// The channel should not be valid
			Assert::IsFalse(channel->IsValid());

			// Getting a keyframe should not changle the position
			actor->GetKeyframe();
			Assert::AreEqual(1234, actor->GetPosition().X);
			Assert::AreEqual(9833, actor->GetPosition().Y);

			// Now we'll set one keyframe and see if that works
			picture->SetAnimationTime(1.5);
			actor->SetPosition(Point(101, 655));
			actor->SetKeyframe();

			// Change position
			actor->SetPosition(Point(1234, 9833));
			Assert::AreEqual(1234, actor->GetPosition().X);
			Assert::AreEqual(9833, actor->GetPosition().Y);

			// Wherever we move, now, the keyframe angle should be used
			picture->SetAnimationTime(0);
			Assert::AreEqual(101, actor->GetPosition().X);
			Assert::AreEqual(655, actor->GetPosition().Y);
		}

	};
}