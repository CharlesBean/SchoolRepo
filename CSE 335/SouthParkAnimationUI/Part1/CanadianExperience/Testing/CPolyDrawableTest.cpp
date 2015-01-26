#include "stdafx.h"
#include "CppUnitTest.h"

#include "PolyDrawable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Gdiplus;

namespace Testing
{
	TEST_CLASS(CPolyDrawableTest)
	{
	public:

		/** \brief Function for determining if two colors are the same */
		bool ColorsAreEqual(Color color1, Color color2)
		{
			return (color1.GetValue() == color2.GetValue());
		}
		
		TEST_METHOD(TestCPolyDrawableConstructor)
		{
			CPolyDrawable drawable(wstring(L"Box"));

			Assert::AreEqual(wstring(L"Box"), drawable.GetName());
		}

		TEST_METHOD(TestCPolyDrawableColor)
		{
			CPolyDrawable drawable(wstring(L"Triangle"));

			Assert::IsTrue(ColorsAreEqual(Color::Black, drawable.GetColor()));

			drawable.SetColor(Color::Purple);

			Assert::IsTrue(ColorsAreEqual(Color::Purple, drawable.GetColor()));
		}

	};
}