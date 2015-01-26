#include "stdafx.h"
#include "CppUnitTest.h"

#include "Drawable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Gdiplus;

namespace Testing
{
	class CDrawableMock : public CDrawable
	{
	public:
		CDrawableMock(const wstring &name) : CDrawable(name) {}

		virtual void Draw(Gdiplus::Graphics *graphics) override {}

		virtual bool HitTest(Gdiplus::Point pos) override { return false; }
	};

	TEST_CLASS(CDrawableTest)
	{
	public:
		
		TEST_METHOD(TestCDrawableConstructor)
		{
			CDrawableMock drawable(wstring(L"Tom"));

			Assert::AreEqual(wstring(L"Tom"), drawable.GetName());
		}

		TEST_METHOD(TestCDrawablePosition)
		{
			CDrawableMock drawable(wstring(L"Bill"));

			Assert::AreEqual(0, drawable.GetPosition().X);
			Assert::AreEqual(0, drawable.GetPosition().Y);

			drawable.SetPosition(Point(10, 11));

			Assert::AreEqual(10, drawable.GetPosition().X);
			Assert::AreEqual(11, drawable.GetPosition().Y);
		}

		TEST_METHOD(TestCDrawableRotation)
		{
			CDrawableMock drawable(wstring(L"Yan"));

			Assert::AreEqual(double(0), drawable.GetRotation(), .00001);

			drawable.SetRotation(1.50);

			Assert::AreEqual(double(1.5), drawable.GetRotation(), .00001);
		}

		TEST_METHOD(TestCDrawableAssociation)
		{
			CDrawableMock body(L"Body");
			auto arm = std::make_shared<CDrawableMock>(L"Arm");
			auto leg = std::make_shared<CDrawableMock>(L"Leg");

			body.AddChild(arm);
			body.AddChild(leg);

			Assert::IsTrue(arm->GetParent() == &body);
			Assert::IsTrue(leg->GetParent() == &body);
		}
	};
}