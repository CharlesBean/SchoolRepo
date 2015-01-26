/**
 * \file CPictureObserverTest.cpp
 *
 * \author Charles Bean
 */

#include "stdafx.h"
#include "CppUnitTest.h"

#include "PictureObserver.h" 
#include "Picture.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	class CPictureObserverMock : public CPictureObserver
	{
	public:
		CPictureObserverMock() : CPictureObserver() {}

		virtual void UpdateObserver() override { mUpdated = true; }

		bool mUpdated = false;

	};

	TEST_CLASS(CPictureObserverTest)
	{
	public:

		TEST_METHOD(TestConstruct)
		{
			CPictureObserverMock observer;
		}

		TEST_METHOD(TestCPictureObserverOneObserver)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer.mUpdated);
		}

		TEST_METHOD(TestCPictureObserverGetPicture)
		{
			// Create an observer mock
			CPictureObserverMock observer;

			// Allocate CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Set the observers picture
			observer.SetPicture(picture);

			// Get the size using the getpicture function
			Size testSize = observer.GetPicture()->GetSize();

			// Assert the size width is 800
			Assert::AreEqual(testSize.Width, 800);
		}

		TEST_METHOD(TestCPictureObserverUpdateObserver)
		{
			CPictureObserverMock observerA;
			CPictureObserverMock observerB; 

			shared_ptr<CPicture> picture = make_shared<CPicture>();
			
			observerA.SetPicture(picture);
			observerB.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observerA.mUpdated);
			Assert::IsTrue(observerB.mUpdated);
		}

		TEST_METHOD(TestCPictureObserverDestructor)
		{
			CPictureObserverMock observer1;

			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// And set it for the observer:
			observer1.SetPicture(picture);

			{
				CPictureObserverMock observer2;

				// And set it for the observer:
				observer2.SetPicture(picture);
			}

			picture->UpdateObservers();

			int wTest = observer1.GetPicture()->GetSize().Width;

			Assert::AreEqual(wTest, (int)800);
		}

	};
}