#include "stdafx.h"
#include "CppUnitTest.h"

#include "Picture.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	// Dont need mock - not abstract 

	TEST_CLASS(CPictureTest)
	{
	public:
		
		TEST_METHOD(TestPictureInstantiation)
		{
			CPicture picture;
		}

		TEST_METHOD(TestCPictureSize)
		{
			// Create
			CPicture picture;

			// Test default
			Assert::AreEqual(800, picture.GetSize().Width);
			Assert::AreEqual(600, picture.GetSize().Height);

			// Setter
			picture.SetSize(Size(123, 456));

			// Getter
			Assert::AreEqual(123, picture.GetSize().Width);
			Assert::AreEqual(456, picture.GetSize().Height);
		}

		TEST_METHOD(TestCPictureIterator)
		{
			CPicture picture;

			auto iter1 = picture.begin();
			auto iter2 = picture.end();

			// Test to ensure an iterator on an empty picture works
			Assert::IsFalse(iter1 != iter2);

			// Add some actors
			shared_ptr<CActor> actor1 = make_shared<CActor>(L"Bob");
			shared_ptr<CActor> actor2 = make_shared<CActor>(L"Ted");
			shared_ptr<CActor> actor3 = make_shared<CActor>(L"Carol");
			shared_ptr<CActor> actor4 = make_shared<CActor>(L"Alice");

			picture.AddActor(actor1);
			picture.AddActor(actor2);
			picture.AddActor(actor3);
			picture.AddActor(actor4);

			// Test the associations
			Assert::IsTrue(actor1->GetPicture() == &picture);
			Assert::IsTrue(actor2->GetPicture() == &picture);
			Assert::IsTrue(actor3->GetPicture() == &picture);
			Assert::IsTrue(actor4->GetPicture() == &picture);

			iter1 = picture.begin();
			iter2 = picture.end();

			Assert::IsTrue(*iter1 == actor1);
			++iter1;
			Assert::IsTrue(*iter1 == actor2);
			++iter1;
			Assert::IsTrue(*iter1 == actor3);
			++iter1;
			Assert::IsTrue(*iter1 == actor4);
			++iter1;

			// Ensure we are at the end
			Assert::IsFalse(iter1 != iter2);
		}

		TEST_METHOD(TestCPictureGetTimeline)
		{
			CPicture picture;

			CTimeline *timeline = picture.GetTimeline();
			Assert::IsNotNull(timeline);
		}
	};
}